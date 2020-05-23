#ifndef LINKQUEUE_H
#define LINKQUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {FALSE = 0, TURE = 1} BOOL;

typedef int(*PDataCmp)(void*, void*);
typedef void (*PDataDisplay)(void*);
typedef int (*PDataPriority)(void*, void*);
typedef void (*PDataAssign)(void*, const void*);

typedef struct QueueNode {
	void *data;
	struct QueueNode *next;
} Node;

typedef struct {
	PDataCmp dataCmp;
	PDataDisplay dataDisplay;
	PDataPriority dataPriority;
	PDataAssign dataAssign;
} QueueOps;

typedef struct {
	Node *head;
	Node *tail;
	int dataSize;
	QueueOps ops;
} Queue;

void QueueInit(Queue *linkQueue, int dataSize, QueueOps ops);
BOOL IsEmpty(const Queue *linkQueue);
void Enqueue(Queue *linkQueue, void *data);
void Dequeue(Queue *linkQueue, void *outData);
void Clear(Queue* linkQueue);
size_t Size(Queue *linkQueue);
void ShowQueue(const Queue *linkQueue);
void InsertSortLinkQueue(Queue *linkQueue); 

#endif
