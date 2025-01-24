#include <stdio.h>
#define m 5
#define n 5
#define MAX 100

struct stype
{
	int x, y, pre;
} queue[MAX];

int maze[m + 2][n + 2] = {
	{2, 2, 2, 2, 2, 2, 2},
	{2, 0, 0, 1, 0, 1, 2},
	{2, 1, 0, 1, 1, 1, 2},
	{2, 1, 0, 0, 0, 1, 2},
	{2, 0, 0, 1, 0, 0, 2},
	{2, 0, 1, 1, 1, 0, 2},
	{2, 2, 2, 2, 2, 2, 2}};

int zx[5] = {0, 0, 0, 1, -1};
int zy[5] = {0, -1, 1, 0, 0};

void print(int rear)
{
	int i = rear;
	int j;
	do
	{
		j = i;
		i = queue[i].pre;
		queue[j].pre = -1;
	} while (i != 0);
	printf("The path is:\nEntrance->\n\t");
	i = 0;
	while (i <= rear)
	{
		if (queue[i].pre == -1)
		{
			printf("(%d, %d)->", queue[i].x, queue[i].y);
			if ((i % 5) == 0)
			{
				printf("\n");
				printf("\t");
			}
		}
		i++;
	}
	printf("Exit");
};

int main()
{
	int rear, front;
	int find = 0;
	int x, y;
	int v;

	int i, j;
	for (i = 0; i < m + 2; i++)
	{
		for (j = 0; j < n + 2; j++)
		{
			int value = maze[i][j];
			if (value != 2)
			{
				printf("%d ", value);
			}
			else
			{
				printf("* ");
			}
		}
		printf("\n");
	}

	queue[1].x = 1;
	queue[1].y = 1;
	queue[1].pre = 0;
	front = 1;
	rear = 1;
	maze[1][1] = -1;
	while ((front <= rear) && !find)
	{
		x = queue[front].x;
		y = queue[front].y;

		for (v = 1; v <= 4; v++)
		{
			i = x + zx[v];
			j = y + zy[v];
			if (maze[i][j] == 0)
			{
				rear++;
				queue[rear].x = i;
				queue[rear].y = j;
				queue[rear].pre = front;

				maze[i][j] = -1;
			}
			if ((i == m) && (j == n))
			{
				find = 1;
				print(rear);
			}
		}
		front++;
	}
	
	if (!find)
		printf("Cannot find it");

	getchar();
	return 0;
}
