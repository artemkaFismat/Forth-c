#ifndef STACK

#include <string.h>
#include <stdbool.h>

#define MAX_BUFFER 512

typedef struct {
	int stack[MAX_BUFFER];
	int pos;
} STACK;

void stack_init(STACK* s) {
	memset(s -> stack, 0, MAX_BUFFER);
	s -> pos = -1;
}

bool is_empty(STACK* s) {
	return s -> pos == -1;
}

bool is_full(STACK* s) {
	return s -> pos;
}

void push(STACK* s, int val) {
	s -> stack[++s -> pos] = val;
}

int pop(STACK* s) {
	int pop = s -> stack[s -> pos];
	--s -> pos;
	return pop;
}

int peek(STACK* s) {
	return s -> stack[s -> pos];
}

#endif
