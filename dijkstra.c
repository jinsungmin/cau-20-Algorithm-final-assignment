#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define TRUE 1
#define FALSE 0
#define INF 9999
#define NUM_VERTICES 5 

int weight[NUM_VERTICES][NUM_VERTICES] = { 
	{0, 3,5,INF, INF},
	{INF, 0, 2, 6, INF},
	{INF, 1, 0, 4,6},
	{INF, INF, INF, 0, 2},
	{3, INF,INF, 7, 0},
};

int distance[NUM_VERTICES];
int found[NUM_VERTICES];
int path[NUM_VERTICES][NUM_VERTICES];
char converted_path[NUM_VERTICES][NUM_VERTICES];

int check[NUM_VERTICES];

void convert();
void path_init(int path[][NUM_VERTICES]); 
int choose(int distance[], int n, int found[]); 
void shortest_path(int start, int n);

void main() {
	int start = 0;
	path_init(path);
	
	shortest_path(start, NUM_VERTICES);

	convert();

	printf("[s -> y] Shortest Distance: %d \n", distance[2]);
	printf("[s -> y] Node : ");

	for (int i = 0; i < NUM_VERTICES; i++) {
		if (converted_path[2][i] != 'x') {
			printf("%c->", converted_path[2][i]);
		}
	}
	printf("%c\n", 'y');

	printf("[s -> z] Shortest Distance: %d \n", distance[4]);
	printf("[s -> z] Node : ");

	for (int i = 0; i < NUM_VERTICES; i++) {
		if (converted_path[4][i] != 'x') {
			printf("%c->", converted_path[4][i]);
		}
	}
	printf("%c\n", 'z');

	system("pause");
	return 0;
}

void convert() {
	for (int i = 0; i < NUM_VERTICES; i++) {
		for (int j = 0; j < NUM_VERTICES; j++) {
			converted_path[i][j] = 'x';
			switch (path[i][j]) {
				case 0:
					converted_path[i][j] = 's';
					break;
				case 1:
					converted_path[i][j] = 't';
					break;
				case 2:
					converted_path[i][j] = 'y';
					break;
				case 3:
					converted_path[i][j] = 'x';
					break;
				case 4:
					converted_path[i][j] = 'z';
					break;
			}
		}
	}
}

void path_init(int path[][NUM_VERTICES]) {
	for (int i = 0; i < NUM_VERTICES; i++) {
		for (int j = 0; j < NUM_VERTICES; j++) {
			path[i][j] = INF;
		}
	}

}

int choose(int distance[], int n, int found[]) {
	int min, minpos;
	min = INF;
	minpos = -1;
	for (int i = 0; i < n; i++)
		if (distance[i] < min && !found[i]) {
			min = distance[i];
			minpos = i;
		}
	return minpos;
}

void shortest_path(int start, int n) {
	for (int i = 0; i < n; i++) {
		distance[i] = weight[start][i];
		found[i] = FALSE;
		check[i] = 1;
		path[i][0] = start;

	}
	found[start] = TRUE;
	distance[start] = 0;

	for (int i = 0; i < n - 2; i++) {
		int k = choose(distance, n, found);
		found[k] = TRUE;
		for (int w = 0; w < n; w++) {
			if (!found[w]) {
				if (distance[k] + weight[k][w] < distance[w]) {
					if (i == 0) {
						path[w][check[w]] = k; 
						check[w]++;
					}
					else {
						for (int j = 0; j < (check[k] + 1); j++) {
							path[w][j] = path[k][j]; 
							path[w][j + 1] = k; 
							check[w]++;
						}
					}
					distance[w] = distance[k] + weight[k][w];
				}
			}
		}
	}
}
