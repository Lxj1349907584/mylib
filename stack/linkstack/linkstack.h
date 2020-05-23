#ifndef LINKSTACK_H
#define LINKSTACK_H

// 栈：先进后出，后进先出
// 入栈：调用链表的PushFront()
// 出栈：调用链表的PopFront()
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {FALSE = 0, TURE = 1} BOOL;
typedef void (*PDataAssign)(void*, void*);
typedef void (*PDataDisplay)(void*);
typedef struct StackNode {
	void *data;
	struct StackNode *next;
} Node;

typedef struct {
	PDataDisplay dataDisplay;
	PDataAssign dataAssign;
} StackOps;

typedef struct {
	Node *top;
	Node *bottom;
	int dataSize;
	StackOps ops;
} Stack;

void StackInit(Stack *stack, int dataSize, StackOps ops);
void EnStack(Stack *stack, void *data);
void DeStack(Stack *stack, void *data);
BOOL IsEmpty(Stack *stack);
void Clear(Stack *stack);
void ShowStack(Stack *stack);

#endif


