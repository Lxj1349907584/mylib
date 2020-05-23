#include "hash_table.h"

typedef struct {
	char word[100];
	char paraphrase[1024];
} WordPra;

int DataCmp(void *data1, void *data2)
{
	WordPra *str1 = (WordPra*)data1;
	WordPra *str2 = (WordPra*)data2;

	return strcmp(str1->word, str2->word);
}

void DataDisplay(void *data)
{
	WordPra *wordPra = (WordPra*)data;
	printf("%s%s", wordPra->word, wordPra->paraphrase);
}

void DataAssign(void *data1, void *data2)
{
	memmove(data1, data2, sizeof(WordPra));
}

int GetHashAddrByKey(void *key)
{
	int hashAddr;
	char *keyStr = (char*)key;
	if (*keyStr >= 'A' && *keyStr <= 'Z') {
		hashAddr = *keyStr - 'A';
	} else if (*keyStr >= 'a' && *keyStr <= 'z') {
		hashAddr = *keyStr - 'a';
	}
	return hashAddr; 
}

void ParseStrToStruct(char *str, WordPra *wordPra)
{
	char *wordStr = NULL;
	char *parStr = NULL;

	wordStr = strtok(str, " ");
	parStr = strtok(NULL, "\r");
	strcpy(wordPra->word, wordStr);
	strcpy(wordPra->paraphrase, parStr);
}

int main()
{
	char buff[1024] = {0};
	FILE *fp = NULL;
	char word[100] = {0};
	int j = 0;
	WordPra wordPra = {0};
	HashTable hashTable;
	HashTableOps ops = {DataCmp, DataDisplay, DataAssign, GetHashAddrByKey};
	
	fp = fopen("dict.txt", "r");
	if (fp == NULL) {
		return -1;
	}

	InitHashTable(&hashTable, ops, sizeof(WordPra), 52);
	while (fgets(buff, sizeof(buff), fp) != NULL) {
		ParseStrToStruct(buff, &wordPra);
		InsertHashTable(&hashTable, (void*)wordPra.word, (void*)&wordPra);
		j++;
	}

	printf("%d\n", j);
	while(1) {
		printf("请输入要查找的单词\n");
		gets(word);
		if (strcmp(word, "qq") == 0) {
			break;
		}	
		SearchHashTable(&hashTable, (void*)word, (void*)&wordPra);
		hashTable.ops.dataDisplay((void*)&wordPra);
	}
	
	DesTroyHashTable(&hashTable);
	fclose(fp);
	return 0;
}
