#include "one_way_linked_list.h"

BOOL empty(const List *linkList)
{
	return (linkList->head == NULL) && (linkList->tail == NULL);
}

// 创建链表
void ListInit(List *linkList, int dataSize, ListOps ops)
{
	linkList->head = NULL;
	linkList->tail = NULL;
	linkList->dataSize = dataSize;
	linkList->ops.dataCmp = ops.dataCmp;
	linkList->ops.dataDisplay = ops.dataDisplay;
	linkList->ops.seekByKey = ops.seekByKey;
	linkList->ops.dataAssign = ops.dataAssign;
}

// 释放节点
void FreeNode(Node *node)
{
	free(node->data);
	free(node);
}

// 从首部压入
void PushFront(List *linkList, void *data)
{
	Node *pTmp = (Node*)malloc(sizeof(Node));
	pTmp->data = malloc(linkList->dataSize);
	linkList->ops.dataAssign(pTmp->data, data);
	pTmp->next = linkList->head;
	if (linkList->head == NULL) {
		linkList->tail = pTmp;
	}
    linkList->head = pTmp;
}

// 从首部弹出
void PopFront(List *linkList)
{
	if (empty(linkList)) {
		return;
	}
	Node *next = linkList->head->next;
	FreeNode(linkList->head);
	linkList->head = next;

	if (linkList->head == NULL) {
		linkList->tail = NULL;
	}
}

// 获取首元素
void GetFront(List *linkList, void *outData)
{
	if (empty(linkList)) {
		outData = NULL;
		return;
	}
	linkList->ops.dataAssign(outData, linkList->head->data);
}

// 从尾部压入
void PushBack(List *linkList, void *data)
{
	Node *pTmp = (Node*)malloc(sizeof(Node));
	pTmp->data = malloc(linkList->dataSize);
	linkList->ops.dataAssign(pTmp->data, data);
	pTmp->next = NULL;
	if (linkList->tail == NULL) {
		linkList->head = pTmp;
	} else {
		linkList->tail->next = pTmp;
	}
	linkList->tail = pTmp;
}

// 删除匹配节点
void RemoveMatchNode(List *linkList, void *data)
{
	BOOL isJumpFirstData;
	while (linkList->head != NULL && linkList->ops.dataCmp(linkList->head->data, data) == 0) {
		PopFront(linkList);
	}

	if (linkList->head == NULL) {
		return;
	}

	Node *pPrev = linkList->head;
	Node *pTmp = pPrev->next;
	Node *pNext = NULL;
	while (pTmp != NULL) {
		if (linkList->ops.dataCmp(pTmp->data, data) == 0) {
			pNext = pTmp->next;
			FreeNode(pTmp);
			pPrev->next = pNext;
			pTmp = pNext;
			// 如果删除的节点是尾节点，则需要将tail更新为上一个节点
			if (pTmp == NULL) {
				linkList->tail = pPrev;	
			}
			continue;
		}
		pPrev = pPrev->next;
		pTmp = pTmp->next;
	}
}

// 删除重复节点
void RemoveRepeatNode(List *linkList)
{
	Node *pPrev = linkList->head;
	Node *pTmp = NULL;
	Node *pPrevTmp = NULL;

	while (pPrev != NULL) {
		pPrevTmp = pPrev;
		pTmp = pPrevTmp->next;
		while (pTmp != NULL) {
			if (linkList->ops.dataCmp(pPrev->data, pTmp->data) == 0) {
				pPrevTmp->next = pTmp->next;
				FreeNode(pTmp);
				pTmp = pPrevTmp->next;
				if (pTmp == NULL) {
					linkList->tail = pPrevTmp;
				}
			} else {
				pPrevTmp = pPrevTmp->next;
				pTmp = pTmp->next;
			}
		}
		pPrev = pPrev->next;
	}
}

// 查找节点
Node *FindLinkList(List *linkList, void *data)
{
	Node *pTmp = linkList->head;
	while (pTmp != NULL) {
		if (linkList->ops.dataCmp(pTmp->data, data) == 0) {
			return pTmp;
		}
		pTmp = pTmp->next;
	}
	return NULL;
}

// 修改节点
void ReviseLinkList(List *linkList, void *oldData, void *newData)
{
	Node *pTmp = NULL;

	while ((pTmp = FindLinkList(linkList, oldData)) != NULL) {
		linkList->ops.dataAssign(pTmp->data, newData);
	}
}

// 链表倒置
void ConvertLinkList(List *linkList)
{
	List tmpLinkList;
	Node *node = NULL;
	ListInit(&tmpLinkList, linkList->dataSize, linkList->ops);
	Node *pTmp = linkList->head;
	
	while (pTmp != NULL) {
		PushFront(&tmpLinkList, linkList->head->data);
		PopFront(linkList);
		pTmp = pTmp->next;
	}

	*linkList = tmpLinkList;
}

// 链表插入排序
void InsertSortLinkList(List *linkList)
{
	Node *pTmp = NULL;
	Node *pInsert = NULL;
	Node **pPos = NULL;
	if (empty(linkList)) {
		return;
	}

	pTmp = linkList->head->next;
	linkList->head->next = NULL;
	while (pTmp != NULL) {
		pPos = &linkList->head;
		while (*pPos != NULL && linkList->ops.dataCmp(pTmp->data, (*pPos)->data) > 0) {
			pPos = &(*pPos)->next;
		}
		pInsert = pTmp;
		pTmp = pTmp->next;
		pInsert->next = *pPos;
		*pPos = pInsert;
		if (pInsert == linkList->head) {
			linkList->head = pInsert;
		}
		if (pInsert->next == NULL) {
			linkList->tail = pInsert;
		}
	}
}

// 清空
void Clear(List *linkList)
{
	while(empty(linkList) != TURE) {
		PopFront(linkList);
	}
}

size_t GetSize(const List *linkList) 
{
	size_t nodes = 0;
	Node *node = NULL;
	for (node = linkList->head; node; node = node->next) {
		nodes++;
	}
	return nodes;
}

// 显示链表
void ShowList(const List *linkList)
{  
	Node *node = NULL;
	for (node = linkList->head; node; node = node->next) {
		linkList->ops.dataDisplay(node->data);
	}
}

