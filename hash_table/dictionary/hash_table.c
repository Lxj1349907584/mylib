#include "hash_table.h"

void InitHashTable(HashTable *hashTable, HashTableOps ops, int dataSize, int tableSize)
{
	hashTable->table = (Node*)malloc(sizeof(Node) * tableSize);
	memset(hashTable->table, 0, sizeof(Node) * tableSize);
	hashTable->dataSize = dataSize;
	hashTable->tableSize = tableSize;
	hashTable->ops = ops;
}

void InsertHashTable(HashTable *hashTable, void *key, void *data)
{
	int hashAddr = hashTable->ops.getHashAddrByKey(key);
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
		if (hashTable->ops.dataCmp(pTmp->data, key) == 0) {
			hashTable->ops.dataAssign(outData, pTmp->data);
			return;
		}
	}
	memset(outData, 0, hashTable->dataSize);
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
