#include"def.h"
#include"fun.h"

int sta, n;
LISTS Lists;
LinkList L;
int main()
{
	int op = 1;
	Lists.length = 0;
	while (op)
	{
		system("cls");	printf("\n\n");
		printf("      Menu for Linear Table On Sequence Structure \n");
		printf("-------------------------------------------------\n");
		printf("    	  1. AddList        11. PriorElem\n");
		printf("    	  2. ShiftList      12. NextElem\n");
		printf("    	  3. RemoveList     13. ListInsert\n");
		printf("    	  4. LocateList     14. ListDelete\n");
		printf("    	  5. DestroyList    15. ListTraverse\n");
		printf("    	  6. ClearList      16. reverseList\n");
		printf("    	  7. ListEmpty      17. RemoveNthFromEnd\n");
		printf("    	  8. ListLength     18. sortList\n");
		printf("    	  9. GetElem        19. SaveList\n");
		printf("    	  10. LocateElem    20. LoadList\n");
		printf("    	  0. Exit           21. InitList\n");
		printf("-------------------------------------------------\n");
		printf("    ��ѡ����Ĳ���[0~12](��ǰ�������Ա�Ϊ%d):", n + 1);
		scanf("%d", &op);
		switch (op)
		{
		case 1://AddList
			sta = AddList(Lists);
			if (sta == ERROR)
				printf_red("	���ʧ�ܣ����Ա������Ѵ����ޣ�\n");
			else
				printf_green("	��ӳɹ���\n");
			getchar(); getchar();
			break;
		case 2://ShiftList
			sta = ShiftList();
			if (sta == ERROR)
				printf_red("	�����Ա����ڣ�\n");
			else
				printf_green("	ת���ɹ���\n");
			getchar(); getchar();
			break;
		case 3://RemoveList
			sta = RemoveList(Lists);
			if (sta == OK)
				printf_green("	ɾ���ɹ���\n");
			else
				printf_red("	δ�ҵ������Ա�!\n");
			getchar(); getchar();
			break;
		case 4://LocateList
			sta = LocateList(Lists);
			if (sta == 0)
				printf_red("	δ�ҵ������Ա�!\n");
			else
			{
				printf("	���ǵ�%d�����Ա��������£�\n", sta);
				printf("%s ", Lists.elem[sta - 1].name);
				ListTraverse(Lists.elem[sta - 1].L);
				putchar('\n');
			}
			getchar(); getchar();
			break;
		case 5://DestroyList
			sta = DestroyList(Lists.elem[n].L);
			if (sta == OK)
				printf_green("	���Ա�������!\n");
			else
				printf_red("	���Ա����ڣ�\n");
			getchar(); getchar();
			break;
		case 6://ClearList
			sta = ClearList(Lists.elem[n].L);
			if (sta == OK)
				printf_green("	���Ա������!\n");
			else if (sta == ERROR)
				printf_yellow("	���Ա���Ϊ�գ�\n");
			else
				printf_red("	���Ա����ڣ�\n");
			getchar(); getchar();
			break;
		case 7://ListEmpty
			sta = ListEmpty(Lists.elem[n].L);
			if (sta == INFEASIBLE)
				printf_red("    ���Ա�����!\n");
			else if (sta == TRUE)
				printf_green("    ���Ա�Ϊ�գ�\n");
			else
				printf_yellow("    ���Ա�Ϊ�գ�\n");
			getchar(); getchar();
			break;
		case 8://ListLength
			sta = ListLength(Lists.elem[n].L);
			if (sta == INFEASIBLE)
				printf_red("	���Ա�����!\n");
			else
				printf("	���Ա�ĳ���Ϊ %d", ListLength(Lists.elem[n].L));
			getchar(); getchar();
			break;
		case 9://GetElem
		{
			ElemType e;
			sta = GetElem(Lists.elem[n].L, e);
			if (sta == INFEASIBLE)
				printf_red("	���Ա�����!\n");
			else if (sta == ERROR)
				printf_red("	�����ڸ�Ԫ��!\n");
			else
				printf("���Ԫ���� %d\n", e);
			getchar(); getchar();
			break;
		}
		case 10://LocateElem
			sta = LocateElem(Lists.elem[n].L);
			if (sta == INFEASIBLE)
				printf_red("	���Ա�����!\n");
			else if (sta == ERROR)
				printf_yellow("	û���ҵ���Ԫ��!\n");
			else
				printf("	���ǵ� %d ��Ԫ��\n", sta);
			getchar(); getchar();
			break;
		case 11://PriorElem
		{
			int pre = 0;
			sta = PriorElem(Lists.elem[n].L, pre);
			if (sta == INFEASIBLE)
				printf_red("	���Ա�����!\n");
			else if (sta == ERROR)
				printf_red("	û���ҵ�ǰ��!\n");
			else
				printf("	��Ԫ�ص�ǰ��Ϊ %d \n", pre);
			getchar(); getchar();
			break;
		}
		case 12://NextElem
		{
			int next = 0;
			sta = NextElem(Lists.elem[n].L, next);
			if (sta == INFEASIBLE)
				printf_red("	���Ա�����!\n");
			else if (sta == ERROR)
				printf_red("	û���ҵ����!\n");
			else
				printf("	��Ԫ�صĺ��Ϊ %d \n", next);
			getchar(); getchar();
			break;
		}
		case 13://ListInsert
			sta = ListInsert(Lists.elem[n].L);
			if (sta == INFEASIBLE)
				printf_red("	���Ա�����!\n");
			else if (sta == ERROR)
				printf_yellow("	����λ�ò���ȷ!\n");
			else
				printf_green("	����ɹ�!\n");
			getchar(); getchar();
			break;
		case 14://ListDelete
		{
			int e;
			sta = ListDelete(Lists.elem[n].L,e);
			if (sta == INFEASIBLE)
				printf_red("	���Ա�����!\n");
			else if (sta == ERROR)
				printf_yellow("	ɾ��λ�ò���ȷ!\n");
			else
			{
				printf_green("	ɾ���ɹ�!\n");
				printf("	��ɾ����Ԫ���� %d !\n", e);
			}
			getchar(); getchar();
			break;
		}
		case 15://ListTraverse
			printf("\n-----------all elements -----------------------\n");
			for (int i = 0; i < Lists.length; i++)
			{
				printf("%d.", i + 1);
				printf("%s ", Lists.elem[i].name);
				sta = ListTraverse(Lists.elem[i].L);
				if (sta == INFEASIBLE)
					printf_red("�����Ա����ڣ�\n");
				putchar('\n');
			}
			printf("\n------------------ end ------------------------\n");
			getchar(); getchar();
			break;
		case 16://reverseList
			sta = reverseList(Lists.elem[n].L);
			if (sta == INFEASIBLE)
				printf_red("    ���Ա�����!\n");
			else if (sta == ERROR)
				printf_yellow("    ���Ա�Ϊ�գ�\n");
			else
				printf_green("    ��ת�ɹ���\n");
			getchar(); getchar();
			break;
		case 17://RemoveNthFromEnd
			sta = RemoveNthFromEnd(Lists.elem[n].L);
			if (sta == INFEASIBLE)
				printf_red("    ���Ա�����!\n");
			else if (sta == ERROR)
				printf_yellow("    ���Ա�Ϊ�գ�\n");
			else
				printf_green("    ɾ���ɹ���\n");
			getchar(); getchar();
			break;
		case 18://sortList
			sta = sortList(Lists.elem[n].L);
			if (sta == INFEASIBLE)
				printf_red("    ���Ա�����!\n");
			else if (sta == ERROR)
				printf_yellow("    ���Ա�Ϊ�գ�\n");
			else
				printf_green("    ��С��������ɹ���\n");
			getchar(); getchar();
			break;
		case 19://SaveList
			sta = SaveList(Lists.elem[n].L);
			if (sta == INFEASIBLE)
				printf_red("    ���Ա�����!\n");
			else
				printf_green("	д��ɹ���\n");
			getchar(); getchar();
			break;
		case 20://LoadList
			sta = LoadList(Lists.elem[n].L);
			if (sta == INFEASIBLE)
				printf_red("    ���Ա�����!\n");
			else if (sta == ERROR)
				printf_red("	���Ա��������ݣ�\n");
			else
				printf_green("	����ɹ���\n");
			getchar(); getchar();
			break;
		case 21://InitList
			if (InitList(Lists.elem[n].L) == OK)
				printf_green("	���Ա����ɹ���\n");
			else
				printf_red("	���Ա���ʧ�ܣ�\n");
			getchar(); getchar();
			break;
		case 0://exit
			break;
		}//end of switch
	}//end of while
	printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
}//end of main()
/*--------page 23 on textbook --------------------*/


int compare(const void* a, const void* b)
{
	return *(int*)b - *(int*)a;
}

void printf_red(const char* s)
{
	printf("\033[1;31m%s\033[0m", s);
}

void printf_green(const char* s)
{
	printf("\033[1;32m%s\033[0m", s);
}

void printf_yellow(const char* s)
{
	printf("\033[1;33m%s\033[0m", s);
}
