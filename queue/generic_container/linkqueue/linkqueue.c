#include "linkqueue.h"

// 队列：先进先出，后进后出
// 入对：调用链表的PushBack()
// 出对：调用链表的PopFront()

void QueueInit(Queue *linkQueue, int dataSize, QueueOps ops)
{
	linkQueue->head = NULL;
	linkQueue->tail = NULL;
	linkQueue->dataSize = dataSize;
	linkQueue->ops.dataCmp = ops.dataCmp;
	linkQueue->ops.dataDisplay = ops.dataDisplay;
	linkQueue->ops.dataPriority = ops.dataPriority;
	linkQueue->ops.dataAssign = ops.dataAssign;
}

BOOL IsEmpty(const Queue *linkQueue)
{
	return linkQueue->head == NULL && linkQueue->tail == NULL;
}

void FreeNode(Node *node)
{
	free(node->data);
	free(node);
}

// 从尾部压入
void PushBack(Queue *linkQueue, void *data)
{
	Node *pTmp = (Node*)malloc(sizeof(Node));
	pTmp->data = malloc(linkQueue->dataSize);
	linkQueue->ops.dataAssign(pTmp->data, data);
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
	if (IsEmpty(linkQueue)) {
		return;
	}
	Node *next = linkQueue->head->next;
	FreeNode(linkQueue->head);
	linkQueue->head = next;
	if (linkQueue->head == NULL) {
		linkQueue->tail = NULL;
	}
}

// 获取首元素
void GetFront(Queue *linkQueue, void *outData)
{
	if (IsEmpty(linkQueue)) {
		outData = NULL;
		return;
	}
	linkQueue->ops.dataAssign(outData, linkQueue->head->data);
}

// 出对
void Enqueue(Queue *linkQueue, void *data)
{
	PushBack(linkQueue, data);
}

// 入对
void Dequeue(Queue *linkQueue, void *outData)
{
	GetFront(linkQueue, outData);
	PopFront(linkQueue);
}

// 清空
void Clear(Queue* linkQueue)
{
	while (IsEmpty(linkQueue) != TURE) {
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
void ShowQueue(const Queue *linkQueue)
{
	Node *pTmp = NULL;
	for (pTmp = linkQueue->head; pTmp; pTmp = pTmp->next) {
		linkQueue->ops.dataDisplay(pTmp->data);
	}
}

// 链表插入排序
void InsertSortLinkQueue(Queue *linkQueue)
{
	Node *pTmp = NULL;
	Node *pInsert = NULL;
	Node **pPos = NULL;
	if (IsEmpty(linkQueue)) {
		return;
	}

	pTmp = linkQueue->head->next;
	linkQueue->head->next = NULL;
	while (pTmp != NULL) {
		pPos = &linkQueue->head;
		while (*pPos != NULL && linkQueue->ops.dataPriority(pTmp->data, (*pPos)->data) > 0) {
			pPos = &(*pPos)->next;
		}
		pInsert = pTmp;
		pTmp = pTmp->next;
		pInsert->next = *pPos;
		*pPos = pInsert;
		if (pInsert == linkQueue->head) {
			linkQueue->head = pInsert;
		}
		if (pInsert->next == NULL) {
			linkQueue->tail = pInsert;
		}
	}
}
