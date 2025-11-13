#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const vector<string> MYSTERY_VEC{
    "a",          "about",     "above",     "after",   "again",    "against",
    "all",        "am",        "an",        "and",     "any",      "are",
    "aren't",     "as",        "at",        "be",      "because",  "been",
    "before",     "being",     "below",     "between", "both",     "but",
    "by",         "can't",     "cannot",    "could",   "couldn't", "did",
    "didn't",     "do",        "does",      "doesn't", "doing",    "don't",
    "down",       "during",    "each",      "few",     "for",      "from",
    "further",    "had",       "hadn't",    "has",     "hasn't",   "have",
    "haven't",    "having",    "he",        "he'd",    "he'll",    "he's",
    "her",        "here",      "here's",    "hers",    "herself",  "him",
    "himself",    "his",       "how",       "how's",   "i",        "i'd",
    "i'll",       "i'm",       "i've",      "if",      "in",       "into",
    "is",         "isn't",     "it",        "it's",    "its",      "itself",
    "let's",      "me",        "more",      "most",    "mustn't",  "my",
    "myself",     "no",        "nor",       "not",     "of",       "off",
    "on",         "once",      "only",      "or",      "other",    "ought",
    "our",        "ours",      "ourselves", "out",     "over",     "own",
    "same",       "shan't",    "she",       "she'd",   "she'll",   "she's",
    "should",     "shouldn't", "so",        "some",    "such",     "than",
    "that",       "that's",    "the",       "their",   "theirs",   "them",
    "themselves", "then",      "there",     "there's", "these",    "they",
    "they'd",     "they'll",   "they're",   "they've", "this",     "those",
    "through",    "to",        "too",       "under",   "until",    "up",
    "very",       "was",       "wasn't",    "we",      "we'd",     "we'll",
    "we're",      "we've",     "were",      "weren't", "what",     "what's",
    "when",       "when's",    "where",     "where's", "which",    "while",
    "who",        "who's",     "whom",      "why",     "why's",    "with",
    "won't",      "would",     "wouldn't",  "you",     "you'd",    "you'll",
    "you're",     "you've",    "your",      "yours",   "yourself", "yourselves",
    "!",          "\"",        "#",         "$",       "%",        "&",
    "'",          "(",         ")",         "*",       "+",        ",",
    "-",          ".",         "/",         ":",       ";",        "<",
    "=",          ">",         "?",         "@",       "[",        "\\",
    "]",          "^",         "_",         "`",       "{",        "|",
    "}",          "~"};

vector<int> createCountVec(const string& text) {
  /*
   * CHALLENGE #2:
   * For every string in the MYSTERY_VEC (above), determine if that
   * string appears in the passed-in text. If it does, then append
   * 1 to a vector, and 0 otherwise. Return that vector of 1s and 0s.
   */

  vector<int> result;

  for (const string& feature : MYSTERY_VEC) {
    result.push_back(search(text.begin(), text.end(), feature.begin(),
                            feature.end()) != text.end()
                         ? 1
                         : 0);
  }
  return result;
}

const vector<int> CORRECT_CHAL2 = {
    1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0,
    0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
    0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

int main() {
  auto student_vec = createCountVec(
      "to be or not to be just be who you want to be or not okay you want "
      "okay");
  if (student_vec == CORRECT_CHAL2)
    cout << "Matched challenge 2!" << endl;
  else
    cout << "Try again!" << endl;
  return 0;
}