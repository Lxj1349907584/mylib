#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EMPTY_QUEUE 2147483647
typedef enum {FALSE = 0, TRUE = 1} BOOL;
typedef int Type;
typedef void (*PDataDisplay)(Type data);
typedef struct {
	Type *data;
	int head;
	int tail;
	int tLen;
	PDataDisplay dataDisplay;
} Queue;

void DataDisplay(Type data)
{
	printf("(%d) ", data);
}

Queue *CreateSeqQueue(int maxLen)
{
	Queue *seqQueue = (Queue*)malloc(sizeof(Queue));
	seqQueue->data = (Type*)malloc((maxLen + 1)* sizeof(Type));
	seqQueue->head = 0;
	seqQueue->tail = 0;
	seqQueue->tLen = maxLen + 1;
	seqQueue->dataDisplay = DataDisplay;
	return seqQueue;
}

BOOL IsFull(const Queue *seqQueue)
{
	return (seqQueue->tail + 1) % seqQueue->tLen == seqQueue->head;
}

BOOL IsEmpty(const Queue *seqQueue)
{
	return seqQueue->tail == seqQueue->head;
}

void Enqueue(Queue *seqQueue, Type data)
{
	if (IsFull(seqQueue)) {
		return;
	}
	seqQueue->data[seqQueue->tail] = data;
	seqQueue->tail = (seqQueue->tail + 1) % seqQueue->tLen;
}

Type Dequeue(Queue *seqQueue)
{
	Type data;
	if (IsEmpty(seqQueue)) {
		return EMPTY_QUEUE;
	}

	data = seqQueue->data[seqQueue->head];
	seqQueue->head = (seqQueue->head + 1) % seqQueue->tLen;
	return data;
}

void ShowQueue(const Queue *seqQueue)
{
	int head = seqQueue->head;
	int tail = seqQueue->tail;

	printf("队内元素\n");
	while (head != tail) {
		seqQueue->dataDisplay(seqQueue->data[head]);
		head = (head + 1) % seqQueue->tLen;
	}
	printf("\n");
}

void Clear(Queue *seqQueue)
{
	seqQueue->head = 0;
	seqQueue->tail = 0;
}

int main() 
{
	Queue *seqQueue = CreateSeqQueue(10);
	int i;
	for (i = 0; i < 10; i++) {
		Enqueue(seqQueue, i);
	}
	
	ShowQueue(seqQueue);
	printf("出队\n");
	for (i = 0; i < 10; i++) {
		printf("<%d> ", Dequeue(seqQueue));
	}
	ShowQueue(seqQueue);
	for (i = 5; i < 10; i++) {
		Enqueue(seqQueue, i);
	}
	ShowQueue(seqQueue);
	Clear(seqQueue);
	ShowQueue(seqQueue);
}



