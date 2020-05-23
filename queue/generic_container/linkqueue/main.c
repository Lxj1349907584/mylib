#include "linkqueue.h"

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
int StuMsgDataPriority(void *data1, void *data2)
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
int FigureMsgDataPriority(void *data1, void *data2)
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

	FigureMsg fig1 = {1, "张飞", "男", "丈八长矛", "beijing"};
	FigureMsg fig2 = {2, "赵云", "男", "青刚剑", "sichuan"};
	FigureMsg fig3 = {3, "关羽", "男", "青龙阉月刀", "chongqing"};
	FigureMsg fig4 = {4, "黄盖", "男", "宝雕弓", "xian"};
	FigureMsg fig5 = {5, "吕布", "男", "方天画戟", "nanjing"};


	QueueOps stuMsgOps = {NULL, StuMsgDataDisplay, StuMsgDataPriority, StuMsgDataAssign};
	Queue stuMsgLinkQueue;
	QueueOps figMsgOps = {NULL, FigureMsgDataDisplay, FigureMsgDataPriority, FigureMsgDataAssign};
	Queue figureMsgLinkQueue;


	QueueInit(&stuMsgLinkQueue, sizeof(StuMsg), stuMsgOps);
	Enqueue(&stuMsgLinkQueue, (void*)&stu1);
	Enqueue(&stuMsgLinkQueue, (void*)&stu2);
	Enqueue(&stuMsgLinkQueue, (void*)&stu3);
	Enqueue(&stuMsgLinkQueue, (void*)&stu4);
	Enqueue(&stuMsgLinkQueue, (void*)&stu5);
	Enqueue(&stuMsgLinkQueue, (void*)&stu6);
	Enqueue(&stuMsgLinkQueue, (void*)&stu7);
	Enqueue(&stuMsgLinkQueue, (void*)&stu8);
	Enqueue(&stuMsgLinkQueue, (void*)&stu9);
	Enqueue(&stuMsgLinkQueue, (void*)&stu10);
	ShowQueue(&stuMsgLinkQueue);
	StuMsg stuMsg;

	printf("\n");
	Dequeue(&stuMsgLinkQueue, (void*)&stuMsg);
	stuMsgLinkQueue.ops.dataDisplay((void*)&stuMsg);

	printf("\n");
	Dequeue(&stuMsgLinkQueue, (void*)&stuMsg);
	stuMsgLinkQueue.ops.dataDisplay((void*)&stuMsg);

	printf("\n");
	InsertSortLinkQueue(&stuMsgLinkQueue);
	ShowQueue(&stuMsgLinkQueue);

	QueueInit(&figureMsgLinkQueue, sizeof(FigureMsg), figMsgOps);
	printf("\n");
	Enqueue(&figureMsgLinkQueue, (void*)&fig1);
	Enqueue(&figureMsgLinkQueue, (void*)&fig2);
	Enqueue(&figureMsgLinkQueue, (void*)&fig3);
	Enqueue(&figureMsgLinkQueue, (void*)&fig4);
	Enqueue(&figureMsgLinkQueue, (void*)&fig5);
	printf("\n");
	ShowQueue(&figureMsgLinkQueue);
	printf("InsertSort***************************\n");
	InsertSortLinkQueue(&figureMsgLinkQueue);
	ShowQueue(&figureMsgLinkQueue);
	Clear(&stuMsgLinkQueue);
	Clear(&figureMsgLinkQueue);
}


int main()
{
	test1();
}
