#include "cleetc.h"

#define DEFAULT_STACK_SIZE 100
#define min(a, b) ((a) < (b) ? (a) : (b))

struct stack;
struct stack *create_stack();
int top(struct stack *);
void pop(struct stack *);
void push(struct stack *, int);
bool is_empty(struct stack *);
void clear(struct stack *);
void free_stack(struct stack *);

struct stack *stack;

int maximal_histogram_square(int *histo, int length) {
    int i, max_edge = 0;
    clear(stack);
    push(stack, -1);
    for(i = 0; i <= length; i++) {
        int c = i < length ? histo[i] : 0;
        while(top(stack) != -1 && c < histo[top(stack)]) {
            int h = histo[top(stack)];
            pop(stack);
            int w = i - top(stack) - 1;
            int edge = min(h, w);
            if(edge > max_edge) max_edge = edge;
        }
        push(stack, i);
    }
    return max_edge * max_edge;
}

int maximalSquare(char **matrix, int matrixRowSize, int matrixColSize) {
    int i, j;
    int **mat = (int **) malloc(sizeof(int *) * matrixRowSize);
    for(i = 0; i < matrixRowSize; i++) {
        mat[i] = (int *) malloc(sizeof(int) * matrixColSize);
    }

    for(i = 0; i < matrixColSize; i++) {
        mat[0][i] = matrix[0][i] == '1' ? 1 : 0;
    }

    for(i = 1; i < matrixRowSize; i++) {
        for(j = 0; j < matrixColSize; j++) {
            if(matrix[i][j] == '1') {
                mat[i][j] = mat[i-1][j] + 1;
            }
        }
    }

    for(i = 0; i < matrixRowSize; i++) {
        for(j = 0; j < matrixColSize; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }

    stack = create_stack();
    int max_square = 0;
    for(int i = 0; i < matrixRowSize; i++) {
        int square = maximal_histogram_square(mat[i], matrixColSize);
        if(square > max_square) max_square = square;
    }

    for(i = 0; i < matrixRowSize; i++) {
        free(mat[i]);
    }
    free(mat);
    free_stack(stack);
    return max_square;
}

int main(void) {
    char *matrix[2] = {"00", "00"};
    printf("%d\n", maximalSquare(matrix, 2, 2));
    return 0;
}

/**
 * implementing of stack
 */

struct stack {
    int *array;
    int array_size;
    int top;
};

struct stack *create_stack() {
    struct stack *stk = (struct stack *) malloc(sizeof(struct stack));
    stk->array = (int *) malloc(sizeof(int) * DEFAULT_STACK_SIZE);
    memset(stk->array, 0, sizeof(int) * DEFAULT_STACK_SIZE);
    stk->array_size = DEFAULT_STACK_SIZE;
    stk->top = 0;
    return stk;
}

void resize(struct stack *stk, int new_size) {
    int *new_array = (int *) malloc(sizeof(int) * new_size);
    memset(new_array, 0, sizeof(int) * new_size);
    memcpy(new_array, stk->array, sizeof(int) * stk->top);
    free(stk->array);
    stk->array = new_array;
    stk->array_size = new_size;
}

int top(struct stack *stk) {
    return stk->array[stk->top-1];
}

void pop(struct stack *stk) {
    stk->top -= 1;
    if(stk->top * 4 + 1 < stk->array_size) {
        int new_size = stk->array_size / 2;
        if(new_size < stk->array_size && new_size >= DEFAULT_STACK_SIZE) {
            resize(stk, new_size);
        }
    }
}

void push(struct stack *stk, int x) {
    if(stk->top >= stk->array_size) {
        int new_size = stk->array_size * 2 + 1;
        resize(stk, new_size);
    }
    stk->array[stk->top] = x;
    stk->top += 1;
}

// lazy clear
void clear(struct stack *stk) {
    stk->top = 0;
}

bool is_empty(struct stack *stk) {
    return stk->top <= 0;
}

void free_stack(struct stack *stk) {
    free(stk->array);
    free(stk);
    stk = NULL;
}
