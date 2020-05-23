#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum {FALSE = 0, TURE = 1} BOOL;

typedef int (*PDataCmp)(void*, void*);
typedef void (*PDataDisplay)(void*);
typedef void* (*PSeekByKey)(void*);
typedef void (*PDataAssign)(void*, const void*);

typedef struct DoulistNode {
	void *data;
	struct DoulistNode *prev;
	struct DoulistNode *next;
} Node;

typedef struct {	
	PDataCmp dataCmp;
	PDataDisplay dataDisplay;
	PSeekByKey seekByKey;
	PDataAssign dataAssign;
} ListOps;

typedef struct {
	Node *head;
	Node *tail;
	int dataSize;
	ListOps ops;
} List;

void ListInit(List *linkList, int dataSize, ListOps ops);
size_t Size(const List *linkList);
void PushFront(List *linkList, void *data);
void PopFront(List *linkList);
void GetFront(List *linkList, void *outData); 
void PushBack(List *linkList, void *data);
void PopBack(List *linkList);
void Getback(List *linkList, void *outData);
void ShowList(const List *linkList);
void Clear(List *linkList);
void RemoveNode(List *linkList, void *data);
BOOL IsEmpty(const List *linkList);

#endif
