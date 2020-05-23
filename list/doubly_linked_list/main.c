#include "doubly_linked_list.h"

//判断是否相等
int DataCmp(const DataType a, const DataType b) 
{
	if (a > b) {
		return 1;
	} else if (a == b) {
		return 0;
	} else {
		return -1;
	}
}

void DataDisplay(const DataType data)
{
	printf("(%d) ", data);
}

void test1()
{
	DoublyLinkedList *linkList = DOULIST_Creat(DataCmp, DataDisplay, NULL);
	DOULIST_PushFront(linkList, 1);	
	DOULIST_PushFront(linkList, 2);
	DOULIST_PushFront(linkList, 3);
	DOULIST_PushFront(linkList, 4);
	DOULIST_PushFront(linkList, 5);
	DOULIST_PushBack(linkList, 1);
	DOULIST_PushBack(linkList, 2);
	DOULIST_PushBack(linkList, 3);
	DOULIST_PushBack(linkList, 4);
	DOULIST_PushBack(linkList, 5);
	DOULIST_ShowList(linkList);
	printf("size=[%d]\n", DOULIST_size(linkList));

	printf("<%d>", DOULIST_GetFront(linkList));
	DOULIST_PopFront(linkList);
	printf("<%d>", DOULIST_GetFront(linkList));
	DOULIST_PopFront(linkList);
	printf("<%d>", DOULIST_GetFront(linkList));
	DOULIST_PopFront(linkList);
	DOULIST_ShowList(linkList);
	printf("size=[%d]\n", DOULIST_size(linkList));

	printf("<%d>", DOULIST_GetBack(linkList));
	DOULIST_PopBack(linkList);
	printf("<%d>", DOULIST_GetBack(linkList));
	DOULIST_PopBack(linkList);
	printf("<%d>", DOULIST_GetBack(linkList));
	DOULIST_PopBack(linkList);
	printf("<%d>", DOULIST_GetBack(linkList));
	DOULIST_PopFront(linkList);
	printf("<%d>", DOULIST_GetBack(linkList));
	DOULIST_PopBack(linkList);
	printf("<%d>", DOULIST_GetBack(linkList));
	DOULIST_PopBack(linkList);
	printf("<%d>", DOULIST_GetBack(linkList));
	DOULIST_PopBack(linkList);
	DOULIST_ShowList(linkList);
	printf("size=[%d]\n", DOULIST_size(linkList));
}

test2()
{
	DoublyLinkedList *linkList = DOULIST_Creat(DataCmp, DataDisplay, NULL);
	int i;
	for (i = 1; i <= 10; i++) {
		DOULIST_PushFront(linkList, i);
	}
	for (i = 10; i >= 1; i--) {
		DOULIST_PushBack(linkList, i);
	}
	DOULIST_ShowList(linkList);	
	printf("size=[%d]\n", DOULIST_size(linkList));
	DOULIST_clear(linkList);
	DOULIST_ShowList(linkList);	
	printf("size=[%d]\n", DOULIST_size(linkList));
	DOULIST_PushBack(linkList, 10);	
	DOULIST_ShowList(linkList);	
	printf("size=[%d]\n", DOULIST_size(linkList));
}


test3()
{	
	DoublyLinkedList *linkList = DOULIST_Creat(DataCmp, DataDisplay, NULL);
	int i;
	for (i = 1; i <= 20; i++) {
		DOULIST_PushFront(linkList, i);
	}
	for (i = 10; i >= 6; i--) {
		DOULIST_PushBack(linkList, i);
	}
	for (i = 6; i <= 10; i++) {
		DOULIST_PushBack(linkList, i);
	}	
	DOULIST_ShowList(linkList);	
	printf("size=[%d]\n", DOULIST_size(linkList));
	DOULIST_RemoveNode(linkList, 10);
	DOULIST_ShowList(linkList);	
	printf("size=[%d]\n", DOULIST_size(linkList));
}

int main(void) 
{
	//test1();
	//test2();
	test3();
}

