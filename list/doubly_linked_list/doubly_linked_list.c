#include "doubly_linked_list.h"

//创建链表
DoublyLinkedList *DOULIST_Creat(PDataCmp dataCmp, PDataDisplay dataDisplay, PSeekByKey seekByKey)
{
	DoublyLinkedList *linkList = (DoublyLinkedList*)malloc(sizeof(DoublyLinkedList));
	linkList->head = NULL;
	linkList->tail = NULL;
	linkList->dataCmp = dataCmp;
	linkList->dataDisplay = dataDisplay;
	linkList->seekBykey = seekByKey;
	return linkList;
}

//判空
BOOL DOULIST_IsEmpty(const DoublyLinkedList *linkList)
{
	return (linkList->head == NULL) && (linkList->tail == NULL); 
}

//大小
size_t DOULIST_size(const DoublyLinkedList *linkList)
{
	size_t nodes = 0;
	DoulistNode *node = NULL;
	for (node = linkList->head; node; node = node->next) {
		nodes++;
	}
	return nodes;
}

//从首部压入
void DOULIST_PushFront(DoublyLinkedList *linkList, DataType data)
{
	DoulistNode *tmpNode = (DoulistNode*)malloc(sizeof(DoulistNode));
	tmpNode->data = data;
	tmpNode->prev = NULL;
	tmpNode->next = linkList->head;
	if (tmpNode->next != NULL) {
		tmpNode->next->prev = tmpNode;
	} else {
		linkList->tail = tmpNode;
	}
	linkList->head = tmpNode;
}

//从首部弹出
void DOULIST_PopFront(DoublyLinkedList *linkList)
{
	if (DOULIST_IsEmpty(linkList)) {
		return;
	} 
	DoulistNode *next = linkList->head->next;
	free(linkList->head);
	linkList->head = next;
	if (linkList->head != NULL) {
		linkList->head->prev = NULL;
	} else {
		linkList->tail = NULL;
	}
}

//获取首元素
DataType DOULIST_GetFront(DoublyLinkedList *linkList) 
{
	if (DOULIST_IsEmpty(linkList)) {
		return (DataType)EMPTY_LIST; 
	}
	return linkList->head->data;
}

//从尾部压入
void DOULIST_PushBack(DoublyLinkedList *linkList, DataType data)
{
	DoulistNode *tmpNode = (DoulistNode*)malloc(sizeof(DoulistNode));
	tmpNode->data = data;
	tmpNode->prev = linkList->tail;
	tmpNode->next = NULL;
	if (tmpNode->prev != NULL) {
		tmpNode->prev->next = tmpNode;
	} else {
		linkList->head = tmpNode;
	}
	linkList->tail = tmpNode;
}

//从尾部弹出
void DOULIST_PopBack(DoublyLinkedList *linkList)
{
	if (DOULIST_IsEmpty(linkList)) {
		return;
	}
	DoulistNode *prev = linkList->tail->prev;
	free(linkList->tail);
	linkList->tail = prev;
	if (linkList->tail != NULL) {
		linkList->tail->next = NULL;
	} else {
		linkList->head = NULL;
	}
}

//获取尾巴元素
DataType DOULIST_GetBack(DoublyLinkedList *linkList)
{
	if (DOULIST_IsEmpty(linkList)) {
		return (DataType)EMPTY_LIST;
	}
	return linkList->tail->data;
}

void DOULIST_ShowList(const DoublyLinkedList *linkList)
{
	DoulistNode *node = NULL;
	for (node = linkList->head; node; node = node->next) {
		linkList->dataDisplay(node->data);
	}
}

//清空
void DOULIST_clear(DoublyLinkedList *linkList)
{
	while(DOULIST_IsEmpty(linkList) != TURE) {
		DOULIST_PopBack(linkList);
	}
}


//删除所有的匹配元素
void DOULIST_RemoveNode(DoublyLinkedList *linkList, DataType data)
{
	DoulistNode *node = NULL;
	DoulistNode *next = NULL;
	for (node = linkList->head, next = NULL; node; node = next) {
		next = node->next;
		if (linkList->dataCmp(node->data, data) == 0) {
			if (node->prev != NULL) {
				node->prev->next = node->next;
			} else {
				linkList->head = node->next;
			}
			
			if (node->next != NULL) {
				node->next->prev = node->prev;
			} else {
				linkList->tail = node->prev;
			}
			free(node);
		}
	}
}
