#include "one_way_linked_list.h"

typedef struct student {
	int id;
	char name[12];
	int age;
	char sex[12];
} StuMsg;

typedef struct {
	int id;
	char name[20];
	char sex[12];
	char weapon[40];
	char category[40];
} FigureMsg; 

/* StuMsg ops  */
int StuMsgDataCmp(void *data1, void *data2)
{
	StuMsg *stuMsg1 = (StuMsg*)data1;
	StuMsg *stuMsg2 = (StuMsg*)data2;

	if (stuMsg1->age > stuMsg2->age) {
		return 1;
	} else if (stuMsg1->age == stuMsg2->age) {
		return 0;
	} else {
		return -1;
	}
}

void StuMsgDataDisplay(void *data)
{
	StuMsg *stuMsg = (StuMsg*)data;
	printf("(id:%d\t", stuMsg->id);
	printf("name:%s\t", stuMsg->name);
	printf("age:%d\t", stuMsg->age);
	printf("sex:%s)\n", stuMsg->sex);
}

void StuMsgDataAssign(void *data1, const void *data2)
{	
	memmove(data1, data2, sizeof(StuMsg));
}

/* FigureMsg ops  */
int FigureMsgDataCmp(void *data1, void *data2)
{
	FigureMsg *figureMsg1 = (FigureMsg*)data1;
	FigureMsg *figureMsg2 = (FigureMsg*)data2;

	if (strcmp(figureMsg1->category, figureMsg2->category) > 0) {
		return 1;
	} else if (strcmp(figureMsg1->category, figureMsg2->category) == 0) {
		return 0;
	} else {
		return -1;
	}
}

void FigureMsgDataDisplay(void *data)
{
	FigureMsg *figureMsg = (FigureMsg*)data;
	printf("(id:%d\t", figureMsg->id);
	printf("name:%s\t", figureMsg->name);
	printf("sex:%s\t", figureMsg->sex);
	printf("weapon:%s\t", figureMsg->weapon);
	printf("category:%s)\n", figureMsg->category);
}

void FigureMsgDataAssign(void *data1, const void *data2)
{	
	memmove(data1, data2, sizeof(FigureMsg));
}

test1()
{
	StuMsg stu1 = {1, "TianMing", 10, "男"};
	StuMsg stu2 = {2, "ShaoYu", 13, "男"};
	StuMsg stu3 = {3, "YuEr", 10, "女"};
	StuMsg stu4 = {4, "GeNie", 30, "男"};
	StuMsg stu5 = {5, "WeiZhuang", 28, "男"};
	StuMsg stu6 = {6, "GaoJianLi", 25, "男"};
	StuMsg stu7 = {7, "XuNv", 20, "女"};
	StuMsg stu8 = {8, "BaiFen", 25, "男"};
	StuMsg stu9 = {9, "MoYa", 27, "男"};
	StuMsg stu10 = {10, "NongYu", 22, "女"};

	FigureMsg fig1 = {1, "张飞", "男", "丈八长矛", "蜀国"};
	FigureMsg fig2 = {2, "赵云", "男", "青刚剑", "蜀国"};
	FigureMsg fig3 = {3, "关羽", "男", "青龙阉月刀", "蜀国"};
	FigureMsg fig4 = {4, "黄该", "男", "宝雕弓", "蜀国"};
	FigureMsg fig5 = {5, "吕布", "男", "方天画戟", "东汉"};
	
	ListOps StuMsgOps = {StuMsgDataCmp, StuMsgDataDisplay, NULL, StuMsgDataAssign};
	List StuMsgLinkList;
	
	ListInit(&StuMsgLinkList, sizeof(StuMsg), StuMsgOps);
	PushFront(&StuMsgLinkList, (void*)&stu1);
	PushFront(&StuMsgLinkList, (void*)&stu2);
	PushFront(&StuMsgLinkList, (void*)&stu3);
	PushFront(&StuMsgLinkList, (void*)&stu4);
	PushFront(&StuMsgLinkList, (void*)&stu5);
	PushBack(&StuMsgLinkList, (void*)&stu6);
	PushBack(&StuMsgLinkList, (void*)&stu7);
	PushBack(&StuMsgLinkList, (void*)&stu8);
	PushBack(&StuMsgLinkList, (void*)&stu9);
	PushBack(&StuMsgLinkList, (void*)&stu10);
	ShowList(&StuMsgLinkList);
	
	ListOps FigMsgOps = {FigureMsgDataCmp, FigureMsgDataDisplay, NULL, FigureMsgDataAssign};
	List FigureMsgLinkList;
	ListInit(&FigureMsgLinkList, sizeof(FigureMsg), FigMsgOps);
	PushFront(&FigureMsgLinkList, (void*)&fig1);
	PushFront(&FigureMsgLinkList, (void*)&fig2);
	PushFront(&FigureMsgLinkList, (void*)&fig3);
	PushBack(&FigureMsgLinkList, (void*)&fig4);
	PushBack(&FigureMsgLinkList, (void*)&fig5);
	ShowList(&FigureMsgLinkList);

	RemoveMatchNode(&StuMsgLinkList, (void*)&stu1);
	RemoveMatchNode(&StuMsgLinkList, (void*)&stu2);
	RemoveMatchNode(&FigureMsgLinkList, (void*)&fig2);
	ShowList(&StuMsgLinkList);
	ShowList(&FigureMsgLinkList);
}

ytest2()
{	
	StuMsg stu1 = {1, "TianMing", 10, "男"};
	StuMsg stu2 = {2, "ShaoYu", 13, "男"};
	StuMsg stu3 = {3, "YuEr", 10, "女"};
	StuMsg stu4 = {4, "GeNie", 30, "男"};
	StuMsg stu5 = {5, "WeiZhuang", 28, "男"};
	StuMsg stu6 = {6, "GaoJianLi", 25, "男"};
	StuMsg stu7 = {7, "XuNv", 20, "女"};
	StuMsg stu8 = {8, "BaiFen", 25, "男"};
	StuMsg stu9 = {9, "MoYa", 27, "男"};
	StuMsg stu10 = {10, "NongYu", 22, "女"};

	ListOps StuMsgOps = {StuMsgDataCmp, StuMsgDataDisplay, NULL, StuMsgDataAssign};
	List StuMsgLinkList;

	ListInit(&StuMsgLinkList, sizeof(StuMsg), StuMsgOps);
	PushFront(&StuMsgLinkList, (void*)&stu1);
	PushFront(&StuMsgLinkList, (void*)&stu2);
	PushFront(&StuMsgLinkList, (void*)&stu3);
	PushFront(&StuMsgLinkList, (void*)&stu4);
	PushFront(&StuMsgLinkList, (void*)&stu5);
	PushBack(&StuMsgLinkList, (void*)&stu6);
	PushBack(&StuMsgLinkList, (void*)&stu7);
	PushBack(&StuMsgLinkList, (void*)&stu8);
	PushBack(&StuMsgLinkList, (void*)&stu9);
	PushBack(&StuMsgLinkList, (void*)&stu10);
	ShowList(&StuMsgLinkList);
	StuMsg *stuMsg = NULL;

	printf("PopFront_delete:\n");
	GetFront(&StuMsgLinkList, (void**)&stuMsg);
	StuMsgLinkList.ops.dataDisplay((void*)stuMsg);
	PopFront(&StuMsgLinkList);
	printf("in list:\n");
	ShowList(&StuMsgLinkList);

	printf("remove:\n");
	RemoveMatchNode(&StuMsgLinkList, (void*)&stu1);
	printf("in list:\n");
	ShowList(&StuMsgLinkList);

	PushBack(&StuMsgLinkList, (void*)&stu1);
	printf("in list:\n");
	ShowList(&StuMsgLinkList);

	PushFront(&StuMsgLinkList, (void*)&stu3);
	printf("in list:\n");
	ShowList(&StuMsgLinkList);
	printf("size:%d\n", GetSize(&StuMsgLinkList));

	Clear(&StuMsgLinkList);
}

test3()
{	
	StuMsg stu1 = {1, "TianMing", 10, "男"};
	StuMsg stu2 = {2, "ShaoYu", 13, "男"};
	StuMsg stu3 = {3, "YuEr", 10, "女"};
	StuMsg stu4 = {4, "GeNie", 30, "男"};
	StuMsg stu5 = {5, "WeiZhuang", 28, "男"};
	StuMsg stu6 = {6, "GaoJianLi", 25, "男"};
	StuMsg stu7 = {7, "XuNv", 20, "女"};
	StuMsg stu8 = {8, "BaiFen", 25, "男"};
	StuMsg stu9 = {9, "MoYa", 27, "男"};
	StuMsg stu10 = {10, "NongYu", 22, "女"};

	ListOps StuMsgOps = {StuMsgDataCmp, StuMsgDataDisplay, NULL, StuMsgDataAssign};
	List StuMsgLinkList;

	ListInit(&StuMsgLinkList, sizeof(StuMsg), StuMsgOps);
	PushFront(&StuMsgLinkList, (void*)&stu1);
	PushFront(&StuMsgLinkList, (void*)&stu2);
	PushFront(&StuMsgLinkList, (void*)&stu3);
	PushFront(&StuMsgLinkList, (void*)&stu4);
	PushFront(&StuMsgLinkList, (void*)&stu5);
	PushBack(&StuMsgLinkList, (void*)&stu6);
	PushBack(&StuMsgLinkList, (void*)&stu7);
	PushBack(&StuMsgLinkList, (void*)&stu8);
	PushBack(&StuMsgLinkList, (void*)&stu9);
	PushBack(&StuMsgLinkList, (void*)&stu10);

	ShowList(&StuMsgLinkList);
	printf("************************************\n");
	InsertSortLinkList(&StuMsgLinkList);
	ShowList(&StuMsgLinkList);

	printf("************************************\n");
	ConvertLinkList(&StuMsgLinkList);
	ShowList(&StuMsgLinkList);
	printf("\n");
	StuMsg stuMsg;
	GetFront(&StuMsgLinkList, (void*)&stuMsg);
	StuMsgDataDisplay((void*)&stuMsg);
	printf("size:%d\n", GetSize(&StuMsgLinkList));
	RemoveRepeatNode(&StuMsgLinkList);
	ShowList(&StuMsgLinkList);
	Clear(&StuMsgLinkList);	
}

int main()
{
	test3();
}
