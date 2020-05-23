#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 队列：先进先出，后进后出
// 入对：调用链表的PushBack()
// 出对：调用链表的PopFront()

#define EMPTY_QUEUE 2147483647
typedef enum {FALSE = 0, TURE = 1} BOOL;
typedef int Type;
typedef void (*PDateDisplay)(Type date);
typedef struct QueueNode {
	Type date;
	struct QueueNode *next;
} Node;

typedef struct {
	Node *head;
	Node *tail;
	PDateDisplay dateDisplay;
} Queue;

void DateDisplay(Type date)
{
	printf("(%d) ", date);
}

Queue *CreatLinkQueue()
{
	Queue *linkQueue = (Queue*)malloc(sizeof(Queue));
	linkQueue->head = NULL;
	linkQueue->tail = NULL;
	linkQueue->dateDisplay = DateDisplay;
	return linkQueue;
}

BOOL Empty(const Queue *linkQueue)
{
	return linkQueue->head == NULL && linkQueue->tail == NULL;
}

// 从尾部压入
void PushBack(Queue *linkQueue, Type date)
{
	Node *pTmp = (Node*)malloc(sizeof(Node));
	pTmp->date = date;
	pTmp->next = NULL;
	if (linkQueue->tail == NULL) {
		linkQueue->head = pTmp;
	} else {
		linkQueue->tail->next = pTmp;
	}
	linkQueue->tail = pTmp;
}

// 从首部弹出
void PopFront(Queue *linkQueue)
{
	if (Empty(linkQueue)) {
		return;
	}
	Node *next = linkQueue->head->next;
	free(linkQueue->head);
	linkQueue->head = next;
	if (linkQueue->head == NULL) {
		linkQueue->tail = NULL;
	}
}

// 获取首元素
Type front(Queue *linkQueue)
{
	if (Empty(linkQueue)) {
		return EMPTY_QUEUE;
	}
	return linkQueue->head->date;
}

// 出对
void Enqueue(Queue *linkQueue, Type date)
{
	PushBack(linkQueue, date);
}

// 入对
Type Dequeue(Queue *linkQueue)
{
	Type date = front(linkQueue);
	PopFront(linkQueue);
	return date;
}

// 清空
void Clear(Queue* linkQueue)
{
	while (Empty(linkQueue) != TURE) {
		PopFront(linkQueue);
	}
}

// 队列大小
size_t Size(Queue *linkQueue)
{
	size_t nodes = 0;
	Node *pTmp = NULL;
	for (pTmp = linkQueue->head; pTmp; pTmp = pTmp->next) {
		nodes++;
	}
	return nodes;
}

// 显示队列元素
void ShowList(const Queue *linkQueue)
{
	Node *pTmp = NULL;
	for (pTmp = linkQueue->head; pTmp; pTmp = pTmp->next) {
		linkQueue->dateDisplay(pTmp->date);
	}
}

test1()
{
	Queue *linkQueue = CreatLinkQueue();
	int i = 0;
	for (i = 0; i < 10; i++) {
		Enqueue(linkQueue, i);
	}
	ShowList(linkQueue);
	printf("<%d>\n", Size(linkQueue));
}

test2()
{  
	Queue *linkQueue = CreatLinkQueue();
	int i = 0;
	for (i = 0; i < 10; i++) {
		Enqueue(linkQueue, i);
	}
	ShowList(linkQueue);
	printf("<%d>\n", Size(linkQueue));

	printf("dequeue\n");
	for (i = 0; i < 5; i++) {
		Type date = Dequeue(linkQueue);
		if (date != EMPTY_QUEUE) {
			printf("[%d] ", date);
		}
	}
	printf("in queue\n");
	ShowList(linkQueue);
	printf("<%d>\n", Size(linkQueue));
	Clear(linkQueue);
	ShowList(linkQueue);
	printf("<%d>\n", Size(linkQueue));
}

int main() 
{
	test2();
}
