#include "hash_table.h"

void InitHashTable(HashTable *hashTable, HashTableOps ops, int dataSize, int tableSize)
{
	hashTable->table = (Node*)malloc(sizeof(Node) * tableSize);
	memset(hashTable->table, 0, sizeof(Node) * tableSize);
	hashTable->dataSize = dataSize;
	hashTable->tableSize = tableSize;
	hashTable->ops = ops;
}

void InsertHashTable(HashTable *hashTable, void *data)
{
	int hashAddr = hashTable->ops.getHashAddrByKey(data);
	Node **pTmpNode = NULL;
	Node *pTmp = NULL;

	for (pTmpNode = &(hashTable->table[hashAddr].next); *pTmpNode != NULL && 
		 (hashTable->ops.dataCmp(data, (*pTmpNode)->data) > 0); 
		 pTmpNode = &((*pTmpNode)->next)) {
	}
	
	pTmp = (Node*)malloc(sizeof(Node));
	pTmp->data = malloc(hashTable->dataSize);
	hashTable->ops.dataAssign(pTmp->data, data);
	pTmp->next = *pTmpNode;
	*pTmpNode = pTmp;
}

void ShowHashTable(HashTable *hashTable)
{
	Node *pTmp = NULL;
	int i;

	for (i = 0; i < hashTable->tableSize; i++) {
		for (pTmp = hashTable->table[i].next; pTmp != NULL; pTmp = pTmp->next) {
			hashTable->ops.dataDisplay(pTmp->data);
		}
		printf("\n");
	}
}

void SearchHashTable(HashTable *hashTable, void *key, void *outData)
{
	int hashAddr = hashTable->ops.getHashAddrByKey(key);
	Node *pTmp = NULL;

	for (pTmp = hashTable->table[hashAddr].next; pTmp != NULL; pTmp = pTmp->next) {
		printf("debug: %p:%d\n", pTmp->data, *((int*)pTmp->data));
		if (hashTable->ops.dataCmp(pTmp->data, key) == 0) {
			hashTable->ops.dataAssign(outData, pTmp->data);
			return;
		}
	}
	outData = NULL;
}

void FreeNode(Node *node)
{
	free(node->data);
	free(node);
}

void DesTroyHashTable(HashTable *hashTable)
{
	Node *pTmp = NULL;
	Node *pPre = NULL;

	int i;
	for (i = 0; i < hashTable->tableSize; i++) {
		pTmp = hashTable->table[i].next;
		while (pTmp != NULL) {
			pPre = pTmp;
			pTmp = pTmp->next;
			FreeNode(pPre);
		}
	}
	free(hashTable->table);
}

int DataCmp(void *data1, void *data2)
{
	if (*((int*)data1) > *((int*)data2)) {
		return 1;
	} else if (*((int*)data1) == *((int*)data2)) {
		return 0;
	} else {
		return -1;
	}
}

void DataDisplay(void *data)
{
	printf("%d ", *((int*)data));
}

void DataAssign(void *data1, void *data2)
{
	memmove(data1, data2, sizeof(int));
}

int GetHashAddrByKey(void *key)
{
	return *((int*)key) % 10;
}

int main(int argc, const char *argv[])
{
	HashTable hashTable;
	HashTableOps ops = {DataCmp, DataDisplay, DataAssign, GetHashAddrByKey};
	InitHashTable(&hashTable, ops, sizeof(int), 10);
	int num = 0;
	int key;
	while (1) {
		printf("请输入数字:\n");
		scanf("%d", &num);
		
		if (num == -1) {
			break;
		}
		InsertHashTable(&hashTable, (void*)&num);
	}
	ShowHashTable(&hashTable);
	
	while (1) {
		printf("请输入要查找的关键字\n");
		scanf("%d", &key);
		printf("key:%d\n", key);
		if (key == -1) {
			break;
		}
		SearchHashTable(&hashTable, (void*)&key, (void*)&num);
		printf("搜索结果:(key:%d, num:%d)\n", key, num);
	}
	DesTroyHashTable(&hashTable);
	ShowHashTable(&hashTable);
	return 0;
}
