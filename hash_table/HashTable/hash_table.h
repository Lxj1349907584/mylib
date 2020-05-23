#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int (*PDataCmp)(void*, void*);
typedef void (*PDataDisplay)(void*);
typedef void (*PDataAssign)(void*, void*);
typedef int (*PGetHashAddrByKey)(void*);

typedef struct node {
	void *data;
	struct node *next;
} Node;

typedef struct {
	PDataCmp dataCmp;
	PDataDisplay dataDisplay;
	PDataAssign dataAssign;
	PGetHashAddrByKey getHashAddrByKey;
} HashTableOps;

typedef struct {
	Node *table;
	int dataSize;
	int tableSize;
	HashTableOps ops;
} HashTable;

#endif
