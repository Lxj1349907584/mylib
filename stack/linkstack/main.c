#include "linkstack.h"

typedef struct {
	int id;
	char name[20];
	char sex;
} Fig;

// 整型操作
void Display(void *data)
{
	printf("(%d) ", *((int*)data));
}

void Assign(void *data1, void *data2)
{
	memmove(data1, data2, sizeof(int));
}

// 结构体操作
void FigDisPlay(void *data)
{
	Fig *fig = (Fig*)data;
	printf("id: %d\t", fig->id);
	printf("name: %s\t", fig->name);
	printf("sex: %c\t", fig->sex);
	printf("\n");
}

void FigAssign(void *data1, void *data2)
{
	memmove(data1, data2, sizeof(Fig));
}

int main()
{
	Stack stack;
	StackOps ops = {Display, Assign};
	StackInit(&stack, sizeof(int), ops);
	int i;
	int j;

	for (i = 0; i < 10; i++) {
		EnStack(&stack, &i);
	}	
 	ShowStack(&stack);

	for (i = 0; i < 10; i++) {
		DeStack(&stack, (void*)&j);
		stack.ops.dataDisplay((void*)&j);
	}

	printf("\n");
	Stack figStack;
	Fig fig[3] = {{1, "lixujun", 'm'},{2, "xubaoni", 'w'},{3, "xufeini", 'w'}};
	StackOps figOps = {FigDisPlay, FigAssign};
	StackInit(&figStack, sizeof(fig), figOps);

	for (i = 0; i < 3; i++) {
		EnStack(&figStack, (void*)&fig[i]);
	}
	ShowStack(&figStack);
	for (i = 0; i < 3; i++) {
		DeStack(&figStack, (void*)&fig[0]);
		figStack.ops.dataDisplay((void*)&fig[0]);
	}

	printf("ShowStack\n");
	ShowStack(&figStack);
	return 0;
}
