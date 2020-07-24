#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define MAX 100

int vector[MAX][MAX] = { 0 };
int check[MAX];
int count[MAX];
int predecessor[MAX];
char predecessor_converted[MAX];
int route[MAX][MAX];
int route_count[MAX];
int n, m, k, a, b;

typedef enum {
	false,
    true,
} bool;

typedef struct {
    int front;
    int rear;
    int data[MAX];
} Queue;

void init_queue(Queue* q) { q->rear = 0; q->front = 0; }

int isFull(Queue* q) {
    return((q->rear + 1) % MAX == q->front);
}

int isEmpty(Queue* q) {
    return(q->front == q->rear);
}

void enqueue(Queue* q, int data) {
    if (isFull(q))
        printf("error");
    q->rear = (q->rear + 1) % MAX;
    q->data[q->rear] = data;

}

int dequeue(Queue* q) {
    if (isEmpty(q))
        printf("error");
    
    q->front = (q->front + 1) % MAX;
    return q->data[q->front];
}

int peek(Queue* q) {
    if (isEmpty(q))
        printf("error");
    
    return q->data[(q->front + 1) % MAX];
}

void bfs() {
    Queue queue;
    check[k] = 0;
    enqueue(&queue, k);

    while (!isEmpty(&queue)) {
        int node = peek(&queue);
        dequeue(&queue);
        
        for (int i = 0; i < count[node]; i++) {
            int next = vector[node][i]; // 정점
            
            if (check[next] == -1) {    // check[next] 경로 수
                check[next] = check[node] + 1;
               
                enqueue(&queue, next);

                route[node][route_count[node]] = next;
                route_count[node]++;
            }
        }
    }
}

void init_vector() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            vector[i][j] = 0;
        }
    }

    vector[0][0] = 1;
    vector[0][1] = 3;
    count[0] = 2;

    vector[1][0] = 2;
    vector[1][1] = 0;
    count[1] = 2;

    vector[2][0] = 1;
    count[2] = 1;

    vector[3][0] = 4;
    vector[3][1] = 0;
    vector[3][2] = 7;
    count[3] = 3;
    
    vector[4][0] = 5;
    vector[4][1] = 6;
    vector[4][2] = 7;
    vector[4][3] = 3;
    count[4] = 4;

    vector[5][0] = 6;
    vector[5][1] = 4;
    count[5] = 2;

    vector[6][0] = 7;
    vector[6][1] = 4;
    vector[6][2] = 5;
    count[6] = 3;
        
    vector[7][0] = 3;       
    vector[7][1] = 4;
    vector[7][2] = 6;
    count[7] = 3;
}

void print_result() {
    for (int i = 0; i < 8; i++) {
        if (!check[i]) {
            predecessor_converted[i] = 'X';
        }
        else {
            switch (predecessor[i]) {
            case 0:
                predecessor_converted[i] = 's';
                break;
            case 1:
                predecessor_converted[i] = 'r';
                break;
            case 2:
                predecessor_converted[i] = 'v';
                break;
            case 3:
                predecessor_converted[i] = 'w';
                break;
            case 4:
                predecessor_converted[i] = 'x';
                break;
            case 5:
                predecessor_converted[i] = 'y';
                break;
            case 6:
                predecessor_converted[i] = 'u';
                break;
            case 7:
                predecessor_converted[i] = 't';
                break;
            }
        }
    }

    printf("d[s] : %d\n", check[0]);
    printf("π[s] : %c\n", predecessor_converted[0]);
    
    printf("d[r] : %d\n", check[1]);
    printf("π[r] : %c\n", predecessor_converted[1]);

    printf("d[v] : %d\n", check[2]);
    printf("π[v] : %c\n", predecessor_converted[2]);

    printf("d[w] : %d\n", check[3]);
    printf("π[w] : %c\n", predecessor_converted[3]);

    printf("d[x] : %d\n", check[4]);
    printf("π[x] : %c\n", predecessor_converted[4]);

    printf("d[y] : %d\n", check[5]);
    printf("π[y] : %c\n", predecessor_converted[5]);

    printf("d[u] : %d\n", check[6]);
    printf("π[u] : %c\n", predecessor_converted[6]);

    printf("d[t] : %d\n", check[7]);
    printf("π[t] : %c\n", predecessor_converted[7]);
}

void fine_predecessor() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < route_count[i]; j++) {  
            predecessor[route[i][j]] = i;
        }
    }
}

int main(void) {
    
    for (int i = 0; i < MAX; i++) {
        count[i] = 0;
        route_count[i] = 0;
    }
    k = 0;
    for (int i = 0; i <= 8; i++) 
        check[i] = -1;

    init_vector();
    
    bfs();
    fine_predecessor();

    print_result();
   

    system("pause");
    return 0;
}
