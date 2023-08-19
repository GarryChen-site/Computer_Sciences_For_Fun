
64 * 64 is hard to understand

every line has 64 int, cache only save 4 lines

so use 8 * * will conflict

use 4 * 4 will not conflict but will not use all the cache

so the solution is use all cache and 4 * 4

| A           | B           |
| :---        |    :----:   |
| C           | D           |

to

| A           | C           |
| :---        |    :----:   |
| B           | D           |

this golang code use to debug

```go

package main

import "log"

func main() {
	var N, M int
	var i, j int
	var A [][]int
	var B [][]int

	N = 64
	M = 64

	A = make([][]int, N)
	B = make([][]int, N)

	for i = 0; i < N; i++ {
		A[i] = make([]int, M)
		B[i] = make([]int, M)
	}
	x := 0
	for i = 0; i < N; i++ {
		for j = 0; j < M; j++ {
			A[i][j] = x
			x++
		}
	}

	transpose(A, B, N, M)

	println("Success")
}

func transpose(A [][]int, B [][]int, N int, M int) {
	var i, j, x, y int
	var x1, x2, x3, x4, x5, x6, x7, x8 int

	for i = 0; i < N; i += 8 {
		for j = 0; j < M; j += 8 {
			println("---- start ----")
			for x = i; x < i+4; x++ {
				x1 = A[x][j]
				x2 = A[x][j+1]
				x3 = A[x][j+2]
				x4 = A[x][j+3]
				x5 = A[x][j+4]
				x6 = A[x][j+5]
				x7 = A[x][j+6]
				x8 = A[x][j+7]

				B[j][x] = x1
				log.Printf("B[%d][%d] = %d\n", j, x, x1)
				B[j+1][x] = x2
				log.Printf("B[%d][%d] = %d\n", j+1, x, x2)
				B[j+2][x] = x3
				log.Printf("B[%d][%d] = %d\n", j+2, x, x3)
				B[j+3][x] = x4
				log.Printf("B[%d][%d] = %d\n", j+3, x, x4)

				B[j][x+4] = x5
				log.Printf("B[%d][%d] = %d\n", j, x+4, x5)
				B[j+1][x+4] = x6
				log.Printf("B[%d][%d] = %d\n", j+1, x+4, x6)
				B[j+2][x+4] = x7
				log.Printf("B[%d][%d] = %d\n", j+2, x+4, x7)
				B[j+3][x+4] = x8
				log.Printf("B[%d][%d] = %d\n", j+3, x+4, x8)
			}

			println("---- second loop ----")
			for y = j; y < j+4; y++ {
				x1 = A[i+4][y]
				x2 = A[i+5][y]
				x3 = A[i+6][y]
				x4 = A[i+7][y]

				x5 = B[y][i+4]
				x6 = B[y][i+5]
				x7 = B[y][i+6]
				x8 = B[y][i+7]

				B[y][i+4] = x1
				log.Printf("B[%d][%d] = %d\n", y, i+4, x1)
				B[y][i+5] = x2
				log.Printf("B[%d][%d] = %d\n", y, i+5, x2)
				B[y][i+6] = x3
				log.Printf("B[%d][%d] = %d\n", y, i+6, x3)
				B[y][i+7] = x4
				log.Printf("B[%d][%d] = %d\n", y, i+7, x4)

				println("---- between second and third ----")

				B[y+4][i] = x5
				log.Printf("B[%d][%d] = %d\n", y+4, i, x5)
				B[y+4][i+1] = x6
				log.Printf("B[%d][%d] = %d\n", y+4, i+1, x6)
				B[y+4][i+2] = x7
				log.Printf("B[%d][%d] = %d\n", y+4, i+2, x7)
				B[y+4][i+3] = x8
				log.Printf("B[%d][%d] = %d\n", y+4, i+3, x8)
			}

			println("---- third loop ----")
			for x = i + 4; x < i+8; x++ {
				x1 = A[x][j+4]
				x2 = A[x][j+5]
				x3 = A[x][j+6]
				x4 = A[x][j+7]

				B[j+4][x] = x1
				log.Printf("B[%d][%d] = %d\n", j+4, x, x1)
				B[j+5][x] = x2
				log.Printf("B[%d][%d] = %d\n", j+5, x, x2)
				B[j+6][x] = x3
				log.Printf("B[%d][%d] = %d\n", j+6, x, x3)
				B[j+7][x] = x4
				log.Printf("B[%d][%d] = %d\n", j+7, x, x4)
			}
			println("---- final ----")
		}
	}
}

```