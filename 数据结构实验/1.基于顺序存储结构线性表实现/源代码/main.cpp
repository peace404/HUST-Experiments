#define _CRT_SECURE_NO_WARNINGS

#include"def.h"
int  pre, next, sta, e;
int n;
SqList L;
LISTS Lists;
#include"fun.h"

int main()
{
	int op = 1;
	Lists.length = 0;
	L.elem = NULL;

	while (op)
	{
		system("cls");	printf("\n\n");
		printf("      Menu for Linear Table On Sequence Structure \n");
		printf("-------------------------------------------------\n");
		printf("    	  1. AddList        11. PriorElem\n");
		printf("    	  2. ShiftList      12. NextElem\n");
		printf("    	  3. RemoveList     13. ListInsert\n");
		printf("    	  4. LocateList     14. ListDelete\n");
		printf("    	  5. DestroyList    15. MaxSubArray\n");
		printf("    	  6. ClearList      16. SubArrayNum\n");
		printf("    	  7. ListEmpty      17. sortList\n");
		printf("    	  8. ListLength     18. ListTraverse\n");
		printf("    	  9. GetElem        19. SaveList\n");
		printf("    	  10. LocateElem    20. LoadList\n");
		printf("    	  0. Exit           21. InitList\n");
		printf("-------------------------------------------------\n");
		printf("    请选择你的操作[0~12](当前操作的线性表为%d[1~%d]):", n + 1, Lists.length);
		scanf("%d", &op);
		switch (op)
		{
		case 1://AddList
			sta = AddList(Lists);
			if (sta == ERROR)
				printf_red("	添加失败，线性表数量已达上限！\n");
			else
				printf_green("添加成功！\n");
			getchar(); getchar();
			break;
		case 2://ShiftList
			sta = ShiftList();
			if (sta == ERROR)
				printf_red("	该线性表不存在！\n");
			else
				printf_green("	转换成功！\n");
			getchar(); getchar();
			break;
		case 3://RemoveList
			sta = RemoveList(Lists);
			if (sta == OK)
				printf_green("	删除成功！\n");
			else
				printf_red("	未找到该线性表!\n");
			getchar(); getchar();
			break;
		case 4://LocateList
			sta = LocateList(Lists);
			if (sta == 0)
				printf_red("	未找到该线性表!\n");
			else
			{
				printf("	这是第%d个线性表，内容如下：\n", sta);
				printf("%s ", Lists.elem[sta - 1].name);
				ListTraverse(Lists.elem[sta - 1].L);
				putchar('\n');
			}
			getchar(); getchar();
			break;
		case 5://DestroyList
			sta = DestroyList(Lists.elem[n].L);
			if (sta == OK)
				printf_green("	线性表已销毁!\n");
			else
				printf_red("	线性表不存在！\n");
			getchar(); getchar();
			break;
		case 6://ClearList
			sta = ClearList(Lists.elem[n].L);
			if (sta == OK)
				printf_green("	线性表已清空!\n");
			else
				printf_red("	线性表不存在！\n");
			getchar(); getchar();
			break;
		case 7://ListEmpty
			sta = ListEmpty(Lists.elem[n].L);
			if (sta == INFEASIBLE)
				printf_red("    线性表不存在!\n");
			else if (sta == TRUE)
				printf_green("    线性表为空！\n");
			else
				printf_yellow("    线性表不为空！\n");
			getchar(); getchar();
			break;
		case 8://ListLength
			sta = ListLength(Lists.elem[n].L);
			if (sta == INFEASIBLE)
				printf_red("	线性表不存在!\n");
			else
				printf("	线性表的长度为 %d", ListLength(Lists.elem[n].L));
			getchar(); getchar();
			break;
		case 9://GetElem
			e = 0;
			sta = GetElem(Lists.elem[n].L, e);
			if (sta == INFEASIBLE)
				printf_red("	线性表不存在!\n");
			else if (sta == ERROR)
				printf_red("	不存在该元素!\n");
			else
				printf("这个元素是 %d\n", e);
			getchar(); getchar();
			break;
		case 10://LocateElem
			sta = LocateElem(Lists.elem[n].L);
			if (sta == INFEASIBLE)
				printf_red("	线性表不存在!\n");
			else if (sta == ERROR)
				printf_yellow("	没有找到该元素!\n");
			else
				printf("	这是第 %d 个元素\n", sta);
			getchar(); getchar();
			break;
		case 11://PriorElem
			pre = 0;
			sta = PriorElem(Lists.elem[n].L, pre);
			if (sta == INFEASIBLE)
				printf_red("	线性表不存在!\n");
			else if (sta == ERROR)
				printf_red("	没有找到该元素!\n");
			else if(sta==OVERFLOW)
				printf_red("	该元素没有前驱!\n");
			else
				printf("	该元素的前驱为 %d \n", pre);
			getchar(); getchar();
			break;
		case 12://NextElem
			next = 0;
			sta = NextElem(Lists.elem[n].L, next);
			if (sta == INFEASIBLE)
				printf_red("	线性表不存在!\n");
			else if (sta == ERROR)
				printf_red("	没有找到后继!\n");
			else
				printf("	该元素的后继为 %d \n", next);
			getchar(); getchar();
			break;
		case 13://ListInsert
			sta = ListInsert(Lists.elem[n].L);
			if (sta == INFEASIBLE)
				printf_red("	线性表不存在!\n");
			else if (sta == ERROR)
				printf_yellow("	插入位置不正确!\n");
			else
				printf_green("	插入成功!\n");
			getchar(); getchar();
			break;
		case 14://ListDelete
			sta = ListDelete(Lists.elem[n].L, e);
			if (sta == INFEASIBLE)
				printf_red("	线性表不存在!\n");
			else if (sta == ERROR)
				printf_yellow("	删除位置不正确!\n");
			else
			{
				printf_green("	删除成功!\n");
				printf("	你删除的元素是 %d !\n", e);
			}
			getchar(); getchar();
			break;
		case 15://MaxSubArray
			sta = MaxSubArray(Lists.elem[n].L);
			if (sta == INFEASIBLE)
				printf_red("    线性表不存在!\n");
			else if (sta == ERROR)
				printf_yellow("    线性表为空！\n");
			else
				printf("    该数组最大连续子数组和为 %d \n", sta);
			getchar(); getchar();
			break;
		case 16://SubArrayNum
			sta = SubArrayNum(Lists.elem[n].L);
			if (sta == INFEASIBLE)
				printf_red("    线性表不存在!\n");
			else if (sta == 0)
				printf_yellow("    没有这样的子数组！\n");
			else
				printf("    这样的子数组个数为 %d \n", sta);
			getchar(); getchar();
			break;
		case 17://sortList
			sta = sortList(Lists.elem[n].L);
			if (sta == INFEASIBLE)
				printf_red("    线性表不存在!\n");
			else if (sta == ERROR)
				printf_yellow("    线性表为空！\n");
			else
				printf("    从小到大排序成功！\n");
			getchar(); getchar();
			break;
		case 18://ListTraverse
			printf("\n-----------all elements -----------------------\n");
			for (int i = 0; i < Lists.length; i++)
			{
				printf("%d.", i + 1);
				printf("%s ", Lists.elem[i].name);
				sta = ListTraverse(Lists.elem[i].L);
				if (sta == INFEASIBLE)
					printf_red("该线性表不存在！\n");
				putchar('\n');
			}
			printf("\n------------------ end ------------------------\n");
			getchar(); getchar();
			break;
		case 19://SaveList
		{
			char filename[100] = { 0 };
			char name[20] = { 0 };
			printf("	请输入要写入的文件：");
			scanf("%s", name);
			sprintf(filename, "%s%s%s", "./", name, ".txt");
			sta = SaveList(Lists.elem[n].L, filename);
			if (sta == OK)
				printf_green("	写入成功！\n");
			else
				printf_red("	写入失败！\n");
			getchar(); getchar();
			break;
		}
		case 20://LoadList
		{
			char filename[100] = { 0 };
			char name[20] = { 0 };
			printf("	请输入要读的文件：");
			scanf("%s", name);
			sprintf(filename, "%s%s%s", "./", name, ".txt");
			sta = LoadList(Lists.elem[n].L, filename);
			if (sta == OK)
				printf_green("	读入成功！\n");
			else
				printf_red("	写入失败！\n");
			getchar(); getchar();
			break;
		}
		case 21://InitList
			if (InitList(Lists.elem[n].L) == OK)
				printf_green("	线性表创建成功！\n");
			else
				printf_red("	线性表创建失败！\n");
			getchar(); getchar();
			break;
		case 0://exit
			break;
		}//end of switch
	}//end of while
	printf("欢迎下次再使用本系统！\n");
}//end of main()
