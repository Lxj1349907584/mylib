#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define EMPTY_LIST  2147483647
typedef enum {FALSE = 0, TURE = 1} BOOL;
typedef int DataType;
typedef int KeyType;

typedef int(*PDataCmp)(DataType firstData, DataType SecondData);
typedef void(*PDataDisplay)(DataType data);
typedef DataType(*PSeekByKey)(KeyType key);

typedef struct DoublyLinkedListNode{
	DataType data;
	struct DoublyLinkedListNode *prev;
	struct DoublyLinkedListNode *next;
} DoulistNode;

typedef struct {
	DoulistNode *head;
	DoulistNode *tail;
	PDataCmp dataCmp;
	PDataDisplay dataDisplay;
	PSeekByKey seekBykey;
} DoublyLinkedList;

DoublyLinkedList *DOULIST_Creat(PDataCmp dataCmp, PDataDisplay dataDisplay, PSeekByKey seekBykey);
size_t DOULIST_GetSize(const DoublyLinkedList *linkList);
void DOULIST_PushFront(DoublyLinkedList *linkList, DataType data);
void DOULIST_PopFront(DoublyLinkedList *linkList);
DataType DOULIST_GetFront(DoublyLinkedList *linkList); 
void DOULIST_PushBack(DoublyLinkedList *linkList, DataType data);
void DOULIST_PopBack(DoublyLinkedList *linkList);
DataType DOULIST_Getback(DoublyLinkedList *linkList);
void DOULIST_ShowList(const DoublyLinkedList *linkList);
void DOULIST_Clear(DoublyLinkedList *linkList);
void DOULIST_RemoveNode(DoublyLinkedList *linkList, DataType data);
BOOL DOULIST_IsEmpty(const DoublyLinkedList *linkList);

#endif
