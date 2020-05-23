#include "linkstack.h"

void StackInit(Stack *stack, int datasize, StackOps ops)
{
	stack->top = NULL;
	stack->bottom = NULL;
	stack->dataSize = datasize;
	stack->ops.dataDisplay = ops.dataDisplay;
	stack->ops.dataAssign = ops.dataAssign;
}

BOOL IsEmpty(Stack *stack)
{
	return stack->top == NULL && stack->bottom == NULL;
}

void FreeNode(Node *node)
{
	free(node->data);
	free(node);
}

void PushFront(Stack *stack, void *data)
{
	Node *pTmp = (Node*)malloc(sizeof(Node));
	pTmp->data = malloc(stack->dataSize);
	stack->ops.dataAssign(pTmp->data, data);
	pTmp->next = stack->top;
	if (stack->top == NULL) {
		stack->bottom = pTmp;
	}
	stack->top = pTmp;
}

void GetFront(Stack *stack, void *outdata)
{
	if (IsEmpty(stack)) {
		outdata = NULL;
		return;
	}
	stack->ops.dataAssign(outdata, stack->top->data);
}

void PopFront(Stack *stack)
{
	if (IsEmpty(stack)) {
		return;
	}
	Node *next = stack->top->next;
	FreeNode(stack->top);
	stack->top = next;
	if (stack->top) {
		stack->bottom = NULL;
	}
}

void EnStack(Stack *stack, void *data)
{
	PushFront(stack, data);
}

void DeStack(Stack *stack, void *outdata)
{
	GetFront(stack, outdata);
	PopFront(stack);
}

void Clear(Stack *stack)
{
	while(IsEmpty(stack) != TURE) {
		PopFront(stack);
	}
}

void ShowStack(Stack *stack)
{
	Node *pTmp = stack->top;
	for (pTmp; pTmp; pTmp = pTmp->next){ 
		stack->ops.dataDisplay(pTmp->data);
	}
}
