#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

char X[8] = "ABCBDAB";
char Y[7] = "BDCABA";

int c[9][8];
char b[9][8];

void print(char b[][8], char X[], int i, int j) {
	
	if (i == 0 || j == 0)
		return;
	if (b[i][j] == 'D') {
		print(b, X, i - 1, j - 1);
		printf("%c", X[i]);
	}
	else if (b[i][j] == 'U') {
		print(b, X, i - 1, j);
	}
	else {
		print(b, X, i, j - 1);
	}

}

int main(void) {
	char temp1[9] = "0";
	char temp2[8] = "0";
	strcat(temp1, X);
	strcat(temp2, Y);

	for (int i = 1; i < strlen(temp1); i++) {
		c[i][0] = 0;
	}
	for (int j = 0; j < strlen(temp2); j++) {
		c[0][j] = 0;
	}
	for (int i = 1; i < strlen(temp1); i++) {
		for (int j = 1; j < strlen(temp2); j++) {
			if (temp1[i] == temp2[j]) {
				c[i][j] = c[i - 1][j - 1] + 1;
				b[i][j] = 'D';
			}
			else if (c[i - 1][j] >= c[i][j-1]) {
				c[i][j] = c[i - 1][j];
				b[i][j] = 'U';
			}
			else {
				c[i][j] = c[i][j - 1];
				b[i][j] = 'L';
			}
		}
	}

	for (int i = 0; i < strlen(temp1); i++) {
		for (int j = 0; j < strlen(temp2); j++) {
			printf("%d ", c[i][j]);
		}
		printf("\n");
	}

	for (int i = 0; i < strlen(temp1); i++) {
		for (int j = 0; j < strlen(temp2); j++) {
			printf("%c ", b[i][j]);
		}
		printf("\n");
	}

	printf("\n[Result] ");
	print(b, temp1, 7, 6);
	
	return 0;
}

