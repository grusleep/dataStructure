#include <stdio.h>
#define MAX_SIZE 1000

int N, M;
int Matrix[MAX_SIZE][MAX_SIZE];
int sum[MAX_SIZE+1][MAX_SIZE+1];

void makeSum()
{
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			sum[i][j] = Matrix[i-1][j-1] + sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1];
		}
	}
}

int range(int r0, int r1, int c0, int c1)
{
	return sum[r1][c1] - sum[r1][c0] - sum[r0][c1] + sum[r0][c0];
}

int main() {
  int i, j;
  int r0, r1, c0, c1;
	
	scanf("%d", &N);
	
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			scanf("%d", &Matrix[i][j]);
		}
	}
	
	makeSum();
	
	scanf("%d", &M);
	
	for (i = 0; i < M; i++)
	{
		scanf("%d%d%d%d", &r0, &r1, &c0, &c1);
		
		printf("%d\n", range(r0, r1, c0, c1));
	}
	
  return 0;
}