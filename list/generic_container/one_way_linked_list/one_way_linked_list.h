#ifndef ONE_WAY_LINKED_LIST_H
#define ONE_WAY_LINKED_LIST_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define EMPTY_LIST 2147483647
typedef enum {FALSE = 0, TURE = 1} BOOL;

typedef int(*PDataCmp)(void*, void*);
typedef void (*PDataDisplay)(void*);
typedef void (*PSeeKByKey)(void*, void**);
typedef void (*PDataAssign)(void*, const void*);

typedef struct LinkNode {
	void *data;
	struct LinkNode *next;
} Node;

typedef struct {
	PDataCmp dataCmp;
	PDataDisplay dataDisplay;
	PSeeKByKey seekByKey;
	PDataAssign dataAssign;
} ListOps;

typedef struct {
	Node *head;
	Node *tail;
	int dataSize;
	ListOps ops;
} List;

BOOL empty(const List *linkList);
void ListInit(List *linkList, int dataSize, ListOps ops);
void PushFront(List *linkList, void *data);
void PopFront(List *linkList);
void Getfront(List *linkList, void *outData);
void PushBack(List *linkList, void *data);
void RemoveMatchNode(List *linkList, void *data);
void RemoveRepeatNode(List *linkList);
Node *FindLinkList(List *linkList, void *data);
void ReviseLinkList(List *linkList, void *oldData, void *newData);
void ConvertLinkList(List *linkList);
void InsertSortLinkList(List *linkList); 
void Clear(List *linkList);
size_t GetSize(const List *linkList); 
void ShowList(const List *linkList);

#endif
