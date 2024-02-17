#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "snake_utils.h"
#include "state.h"

#define BOARD_ROW (10)
#define BOARD_COL (14)

const char SNAKE_TAIL[4] = {'w', 'a', 's', 'd'};
const char SNAKE_BODY[5] = {'^', '<', 'v', '>', 'x'};

/* Helper function definitions */
static char get_board_at(game_state_t *state, int x, int y);
static void set_board_at(game_state_t *state, int x, int y, char ch);
static bool is_tail(char c);
static bool is_snake(char c);
static char body_to_tail(char c);
static int incr_x(char c);
static int incr_y(char c);
static void find_head(game_state_t *state, int snum);
static char next_square(game_state_t *state, int snum);
static void update_tail(game_state_t *state, int snum);
static void update_head(game_state_t *state, int snum);

/* Helper function to get a character from the board (already implemented for you). */
static char get_board_at(game_state_t *state, int x, int y)
{
  return state->board[y][x];
}

/* Helper function to set a character on the board (already implemented for you). */
static void set_board_at(game_state_t *state, int x, int y, char ch)
{
  state->board[y][x] = ch;
}

/* Task 1 */
game_state_t *create_default_state()
{
  game_state_t *state = (game_state_t *)malloc(sizeof(game_state_t));

  /* set board properties and create wall */
  state->x_size = BOARD_COL;
  state->y_size = BOARD_ROW;
  state->board = (char **)malloc(BOARD_ROW * sizeof(char *));
  for (int i = 0; i < BOARD_ROW; i++)
  {
    state->board[i] = (char *)malloc(sizeof(char) * BOARD_COL);
    if (i == 0 || i == BOARD_ROW - 1)
    {
      memset(state->board[i], '#', sizeof(char) * BOARD_COL);
    }
    else
    {
      memset(state->board[i], ' ', sizeof(char) * BOARD_COL);
      // overwrite the first and last element
      memset(state->board[i], '#', sizeof(char));
      memset(state->board[i] + BOARD_COL - 1, '#', sizeof(char));
    }
  }

  /* Create fruit */
  set_board_at(state, 9, 2, '*');

  /* Create snake state */
  state->num_snakes = 1;
  state->snakes = (snake_t *)malloc(sizeof(snake_t));
  state->snakes->tail_x = 4;
  state->snakes->tail_y = 4;
  state->snakes->head_x = 5;
  state->snakes->head_y = 4;
  state->snakes->live = true;
  set_board_at(state, state->snakes->head_x,
               state->snakes->head_y, '>');
  set_board_at(state, state->snakes->tail_x,
               state->snakes->tail_y, 'd');

  return state;
}

/* Task 2 */
void free_state(game_state_t *state)
{
  if (state == NULL)
  {
    return;
  }
  /* free snakes struct */
  free(state->snakes);

  /* free board struct */
  for (int i = 0; i < state->y_size; i++)
  {
    if (state->board[i])
    {
      free(state->board[i]);
    }
  }
  if (state->board)
  {
    free(state->board);
  }
  /* free state struct */
  free(state);
  return;
}

/* Task 3 */
void print_board(game_state_t *state, FILE *fp)
{
  for (int i = 0; i < state->y_size; i++)
  {
    for (int j = 0; j < state->x_size; j++)
    {
      fprintf(fp, "%c", state->board[i][j]);
    }
    fprintf(fp, "\n");
  }
  return;
}

/* Saves the current state into filename (already implemented for you). */
void save_board(game_state_t *state, char *filename)
{
  FILE *f = fopen(filename, "w");
  print_board(state, f);
  fclose(f);
}

/* Task 4.1 */
static bool is_tail(char c)
{
  if (c == SNAKE_TAIL[TAIL_UP] || c == SNAKE_TAIL[TAIL_LEFT] ||
      c == SNAKE_TAIL[TAIL_RIGHT] || c == SNAKE_TAIL[TAIL_DOWN])
  {
    return true;
  }
  else
  {
    return false;
  }
}

static bool is_snake(char c)
{
  if (is_tail(c) || c == SNAKE_BODY[BODY_UP] || c == SNAKE_BODY[BODY_LEFT] ||
      c == SNAKE_BODY[BODY_RIGHT] || c == SNAKE_BODY[BODY_DOWN] ||
      c == SNAKE_BODY[BODY_DEAD])
  {
    return true;
  }
  else
  {
    return false;
  }
}

static char body_to_tail(char c)
{
  if (c == SNAKE_BODY[BODY_UP])
  {
    return SNAKE_TAIL[TAIL_UP];
  }
  else if (c == SNAKE_BODY[BODY_LEFT])
  {
    return SNAKE_TAIL[TAIL_LEFT];
  }
  else if (c == SNAKE_BODY[BODY_DOWN])
  {
    return SNAKE_TAIL[TAIL_DOWN];
  }
  else if (c == SNAKE_BODY[BODY_RIGHT])
  {
    return SNAKE_TAIL[TAIL_RIGHT];
  }
  else
  {
    return '?';
  }
}

static int incr_x(char c)
{
  if (c == SNAKE_TAIL[TAIL_LEFT] || c == SNAKE_BODY[BODY_LEFT])
  {
    return -1;
  }
  else if (c == SNAKE_TAIL[TAIL_RIGHT] || c == SNAKE_BODY[BODY_RIGHT])
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

static int incr_y(char c)
{
  if (c == SNAKE_TAIL[TAIL_UP] || c == SNAKE_BODY[BODY_UP])
  {
    return -1;
  }
  else if (c == SNAKE_TAIL[TAIL_DOWN] || c == SNAKE_BODY[BODY_DOWN])
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

/* Task 4.2 */
static char next_square(game_state_t *state, int snum)
{
  if (snum >= state->num_snakes || snum < 0)
  {
    printf("snake id incorrect, called by %s at %d\n", __func__, __LINE__);
    return '?';
  }

  if (!state->snakes[snum].live)
  {
    printf("snake is dead, called by %s at %d\n", __func__, __LINE__);
    return '?';
  }

  char head = get_board_at(state, state->snakes[snum].head_x, state->snakes[snum].head_y);

  int dx = incr_x(head);
  int dy = incr_y(head);

  int x = state->snakes[snum].head_x + dx;
  int y = state->snakes[snum].head_y + dy;

  if (dx != 0)
  {
    return get_board_at(state, x, state->snakes[snum].head_y);
  }
  else if (dy != 0)
  {
    return get_board_at(state, state->snakes[snum].head_x, y);
  }
  else
  {
    printf("head direction incorrect, called by %s at %d\n", __func__, __LINE__);
    return '?';
  }
}

/* Task 4.3 */
static void update_head(game_state_t *state, int snum)
{
  if (snum >= state->num_snakes || snum < 0)
  {
    printf("snake id incorrect, called by %s at %d\n", __func__, __LINE__);
    return;
  }

  if (!state->snakes[snum].live)
  {
    printf("snake is dead, called by %s at %d\n", __func__, __LINE__);
    return;
  }

  char head = get_board_at(state, state->snakes[snum].head_x, state->snakes[snum].head_y);

  int dx = incr_x(head);
  int dy = incr_y(head);

  int x = state->snakes[snum].head_x + dx;
  int y = state->snakes[snum].head_y + dy;

  if (dx != 0)
  {
    set_board_at(state, x, state->snakes[snum].head_y, head);
    state->snakes[snum].head_x = x;
  }
  else if (dy != 0)
  {
    set_board_at(state, state->snakes[snum].head_x, y, head);
    state->snakes[snum].head_y = y;
  }
  return;
}

/* Task 4.4 */
static void update_tail(game_state_t *state, int snum)
{
  if (snum >= state->num_snakes || snum < 0)
  {
    printf("snake id incorrect, called by %s at %d\n", __func__, __LINE__);
    return;
  }

  if (!state->snakes[snum].live)
  {
    printf("snake has dead, called by %s at %d\n", __func__, __LINE__);
    return;
  }

  /* Get head direction */
  int x = state->snakes[snum].tail_x;
  int y = state->snakes[snum].tail_y;
  char tail_dir = get_board_at(state, x, y);
  set_board_at(state, x, y, ' ');

  int dx = incr_x(tail_dir);
  int dy = incr_y(tail_dir);

  if (dx != 0)
  {
    char next_tail = get_board_at(state, x + dx, y);
    set_board_at(state, x + dx, y, body_to_tail(next_tail));
    state->snakes[snum].tail_x += dx;
  }
  else if (dy != 0)
  {
    char next_tail = get_board_at(state, x, y + dy);
    set_board_at(state, x, y + dy, body_to_tail(next_tail));
    state->snakes[snum].tail_y += dy;
  }
}

/* Task 4.5 */
void update_state(game_state_t *state, int (*add_food)(game_state_t *state))
{
  if (state->num_snakes == 0)
  {
    return;
  }
  for (int i = 0; i < state->num_snakes; i++)
  {
    if (!state->snakes[i].live)
    {
      continue;
    }

    char next = next_square(state, i);
    if (next == '#' || is_snake(next))
    {
      set_board_at(state, state->snakes[i].head_x,
                   state->snakes[i].head_y, 'x');
      state->snakes[i].live = false;
    }
    else if (next == '*')
    {
      update_head(state, i);
      add_food(state);
    }
    else
    {
      update_head(state, i);
      update_tail(state, i);
    }
  }
  return;
}

/* Task 5 */
game_state_t *load_board(char *filename)
{
  int row, col;
  char ch;
  FILE *f = fopen(filename, "r");

  for (row = 0;; row++)
  {
    if ((ch = fgetc(f)) == EOF)
    {
      break;
    }

    for (col = 0;; ch = fgetc(f), col++)
    {
      if (ch == '\n')
      {
        break;
      }
    }
  }
  fclose(f);
  f = NULL;
  ch = '\0';

  game_state_t *state = (game_state_t *)malloc(sizeof(game_state_t));

  state->x_size = col;
  state->y_size = row;
  state->board = (char **)malloc(sizeof(char *) * row);
  for (int i = 0; i < row; i++)
  {
    state->board[i] = (char *)malloc(sizeof(char) * col);
  }

  row = col = 0;
  FILE *nf = fopen(filename, "r");
  for (row = 0;; row++)
  {
    if ((ch = fgetc(nf)) == EOF)
    {
      break;
    }
    for (col = 0;; ch = fgetc(nf), col++)
    {
      if (ch != '\n')
      {
        state->board[row][col] = ch;
      }
      else
      {
        break;
      }
    }
  }
  fclose(nf);
  nf = NULL;
  return state;
}

/* Task 6.1 */
static void find_head(game_state_t *state, int snum)
{
  int x = state->snakes[snum].tail_x;
  int y = state->snakes[snum].tail_y;
  int prev_x, prev_y;
  char current;

  while (true)
  {
    current = get_board_at(state, x, y);
    if (!is_snake(current))
    {
      break;
    }

    prev_x = x;
    prev_y = y;

    int dx = incr_x(current);
    int dy = incr_y(current);

    if (dx != 0)
    {
      x += dx;
    }
    else if (dy != 0)
    {
      y += dy;
    }
  }
  state->snakes[snum].head_x = prev_x;
  state->snakes[snum].head_y = prev_y;
  return;
}

/* Task 6.2 */
game_state_t *initialize_snakes(game_state_t *state)
{
  state->num_snakes = 0;
  state->snakes = (snake_t *)malloc(sizeof(snake_t));

  for (int row = 0; row < state->y_size; ++row)
  {
    for (int col = 0; col < state->x_size; ++col)
    {
      char tail_type = get_board_at(state, col, row);
      if (is_tail(tail_type))
      {
        state->num_snakes++;
        state->snakes = (snake_t *)realloc(state->snakes, sizeof(snake_t) * state->num_snakes);
        state->snakes[state->num_snakes - 1].tail_x = col;
        state->snakes[state->num_snakes - 1].tail_y = row;
        state->snakes[state->num_snakes - 1].live = true;
        find_head(state, state->num_snakes - 1);
      }
    }
  }
  return state;
}
