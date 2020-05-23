#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define EMPTY_LIST 2147483647
typedef enum {FALSE = 0, TURE = 1} BOOL;
typedef enum {REMOVE_MATCH = 0, REMOVE_REPEST = 1} RemoveType;
typedef int Type;
typedef void (*PDateDisplay)(Type date);
typedef struct LinkNode {
	Type date;
	struct LinkNode *next;
} Node;

typedef struct {
	Node *head;
	Node *tail;
	PDateDisplay dateDisplay;
} List;


void DateDisplay(Type date)
{
	printf("(%d) ", date);
}

int DateCmp(Type firstDate, Type secondDate)
{
	if (firstDate > secondDate) {
		return 1;
	} else if (firstDate == secondDate) {
		return 0;
	} else {
		return -1;
	}
}

BOOL empty(const List *linkList)
{
	return (linkList->head == NULL) && (linkList->tail == NULL);
}

// 创建链表
List *CreatLinkList()
{
	List *linkList = (List*)malloc(sizeof(List));
	linkList->head = NULL;
	linkList->tail = NULL;
	linkList->dateDisplay = DateDisplay;
	return linkList;
}

// 从首部压入
void PushFront(List *linkList, Type date)
{
	Node *pTmp = (Node*)malloc(sizeof(Node));
	pTmp->date = date;
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
	free(linkList->head);
	linkList->head = next;

	if (linkList->head == NULL) {
		linkList->tail = NULL;
	}
}

// 获取首元素
Type front(List *linkList)
{
	if (empty(linkList)) {
		return EMPTY_LIST;
	}
	return linkList->head->date;
}

// 从尾部压入
void PushBack(List *linkList, Type date)
{
	Node *pTmp = (Node*)malloc(sizeof(Node));
	pTmp->date = date;
	pTmp->next == NULL;
	if (linkList->tail == NULL) {
		linkList->head = pTmp;
	} else {
		linkList->tail->next = pTmp;
	}
	linkList->tail = pTmp;
}

// 删除匹配节点
void RemoveMatchNode(List *linkList, Type date)
{
	BOOL isJumpFirstDate;
	while (linkList->head != NULL && linkList->head->date == date) {
		PopFront(linkList);
	}

	if (linkList->head == NULL) {
		return;
	}

	Node *pPrev = linkList->head;
	Node *pTmp = pPrev->next;
	Node *pNext = NULL;
	while (pTmp != NULL) {
		if (pTmp->date == date) {
			pNext = pTmp->next;
			free(pTmp);
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
			if (pPrev->date == pTmp->date) {
				pPrevTmp->next = pTmp->next;
				free(pTmp);
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
Node *FindLinkList(List *linkList, Type date)
{
	Node *pTmp = linkList->head;
	while (pTmp != NULL) {
		if (pTmp->date == date) {
			return pTmp;
		}
		pTmp = pTmp->next;
	}
	return NULL;
}

// 修改节点
void ReviseLinkList(List *linkList, Type oldDate, Type newDate)
{
	Node *pTmp = NULL;
	if (oldDate == newDate) {
		return;
	}

	while ((pTmp = FindLinkList(linkList, oldDate)) != NULL) {
		pTmp->date = newDate;
	}
}

// 链表倒置
void ConvertLinkList(List **linkList)
{
	List *tmpLinkList = CreatLinkList();
	Node *pTmp = (*linkList)->head;
	
	while (pTmp != NULL) {
		PushFront(tmpLinkList, front(*linkList));
		PopFront(*linkList);
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
		while (*pPos != NULL && (pTmp->date > (*pPos)->date)) {
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
void clear(List *linkList)
{
	while(empty(linkList) != TURE) {
		PopFront(linkList);
	}
}

size_t size(const List *linkList) 
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
		linkList->dateDisplay(node->date);
	}
}

test8()
{
	List *linkList = CreatLinkList();
	int i;
	srand(time(NULL));
	for (i = 0; i < 1000; i++) {
		PushBack(linkList, rand() % 1000);
	}
	
	ShowList(linkList);
	printf("<size=%d>\n", size(linkList));
	printf("********************\n");

	InsertSortLinkList(linkList);
	ShowList(linkList);
	printf("<size=%d>\n", size(linkList));
	printf("********************\n");

	PushBack(linkList, 100000);
	PushBack(linkList, 100000);
	PushFront(linkList, 0);
	PushFront(linkList, 0);
	PushFront(linkList, 400);
	PushFront(linkList, 400);
	PushFront(linkList, 400);
	PushFront(linkList, 400);
	PushBack(linkList, 401);
	PushBack(linkList, 401);
	PushBack(linkList, 401);
	PushBack(linkList, 401);
	PushBack(linkList, 401);

	ShowList(linkList);
	printf("<size=%d>\n", size(linkList));
	printf("********************\n");
}

int main()
{
	test8();
}
