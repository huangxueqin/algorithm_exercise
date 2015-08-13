#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ABS(a) ((a) >= 0 ? (a) : (-(a)))
#define MIN(a, b) ((a) <= (b) ? (a) : (b))

void swap_rows(int **a, const int col_num, const int offset, const int row1, const int row2) {
	int j;
	for(j = offset; j < col_num; j++) {
		int tmp = a[row1][j];
		a[row1][j] = a[row2][j];
		a[row2][j] = tmp;
	}
}

void row_mul(int **a, const int col_num, const int offset, const int row, const int mul) {
	int j;
	for(j = offset; j < col_num; j++) {
		a[row][j] *= mul;
	}
}

void row_sub(int **a, const int col_num, const int offset, const int row_subber, const int row_subbee) {
	int j;
	for(j = offset; j < col_num; j++) {
		a[row_subber][j] -= a[row_subbee][j];
	}
}

int main(void) {
	int i, j, N, M;
	scanf("%d %d", &N, &M);
	int **a = (int **) malloc(sizeof(int *) * M);
	for(i = 0; i < M; i++)
		a[i] = (int *) malloc(sizeof(int) * (N+1));
	for(i = 0; i < M; i++)
		for(j = 0; j <= N; j++)
			scanf("%d", &(a[i][j]));

	int var_num = N;
	int r = 0, c = 0;
	while(r < M-1) {
		int pivot_row = r;
		for(i = r+1; i < M; i++)
			if(ABS(a[pivot_row][c]) < ABS(a[i][c])) pivot_row = i;
		if(a[pivot_row][c] == 0) {
			var_num--;
			c++;
			continue;
		}
		swap_rows(a, N+1, c, pivot_row, r);
		for(i = r+1; i < M; i++) {
			if(a[i][c] == 0) continue;
			row_mul(a, N+1, c, i, a[r][c] / a[i][c]);
			row_sub(a, N+1, c, i, r);
		}
		r++;
		c++;
		if(c >= N) break;
	}
	var_num = MIN(var_num, M);
	if(var_num != N) {
		bool no_solution = false;
		for(i = var_num; i < M; i++) {
			if(a[i][N] != 0) {
				no_solution = true;
				break;
			}
		}
		printf(no_solution ? "No Solutions\n" : "Many Solutions\n");
		goto exit;
	}
	int *solutions = (int *) malloc(sizeof(int) * N);
	solutions[N-1] = a[N-1][N] / a[N-1][N-1];
	for(i = N-2; i >= 0; i--) {
		for(j = i+1; j < N; j++) {
			a[i][N] -= solutions[j] * a[i][j];
		}
		solutions[i] = a[i][N] / a[i][i];
	}

	for(i = 0; i < N; i++) {
		printf("%d\n", solutions[i]);
	}

	free(solutions);
exit:
	for(i = 0; i < M; i++)
		free(a[i]);
	free(a);
	return 0;
}
