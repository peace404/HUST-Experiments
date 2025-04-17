#pragma once

status InitList(SqList& L) //1
{
	L.elem = (ElemType*)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if (!L.elem) exit(OVERFLOW);
	L.length = 0;
	L.listsize = LIST_INIT_SIZE;
	return OK;
}

status DestroyList(SqList& L)//2
{
	if (!L.elem)
		return INFEASIBLE;
	free(L.elem);
	L.elem = NULL;
	L.length = 0;
	L.listsize = 0;
	return OK;
}

status ClearList(SqList& L)//3
{
	if (!L.elem)
		return INFEASIBLE;
	L.length = 0;
	L.listsize = 0;
	return OK;
}

status ListEmpty(SqList L)//4
{
	if (!L.elem)
		return INFEASIBLE;
	if (L.length == 0)
		return TRUE;
	else
		return FALSE;
}

status ListLength(SqList L)//5
{
	if (!L.elem)
		return INFEASIBLE;
	return L.length;
}

status GetElem(SqList L, ElemType& e)//6
{
	int i = 0;
	printf("	请输入您要查找的元素的位次？\n");
	scanf("%d", &i);
	if (!L.elem)
		return INFEASIBLE;
	if (i > L.length || i < 1)
		return ERROR;
	e = L.elem[i - 1];
	return OK;
}

int LocateElem(SqList L)//7
{
	int e = 0;
	printf("	请输入您要查找的元素？\n");
	scanf("%d", &e);
	if (!L.elem)
		return INFEASIBLE;
	for (int i = 0; i < L.length; i++)
		if (e == L.elem[i])
			return i + 1;
	return 0;
}

status PriorElem(SqList L, ElemType& pre)//8
{
	if (!L.elem)
		return INFEASIBLE;
	int e = 0;
	printf("	请输入要查找的元素\n");
	scanf("%d", &e);
	for (int i = 0; i < L.length; i++)
	{
		if (e == L.elem[i])
		{
			if (i == 0 )
				return OVERFLOW;
			pre = L.elem[i - 1];
			return OK;
		}
	}
	return ERROR;
}

status NextElem(SqList L, ElemType& next)//9
{
	if (!L.elem)
		return INFEASIBLE;
	int e;
	printf("	请输入要查找的元素：");
	scanf("%d", &e);
	for (int i = 0; i < L.length; i++)
	{
		if (e == L.elem[i])
		{
			if (i > L.length - 2)
				return ERROR;
			next = L.elem[i + 1];
			return OK;
		}
	}
	return ERROR;
}

status ListInsert(SqList& L)//10
{
	if (!L.elem)
		return INFEASIBLE;
	int e = 0, i = 0;
	printf("	请输入你要插入的元素\n");
	scanf("%d", &e);
	printf("	请输入你要插入的位次序号\n");
	scanf("%d", &i);
	if (i<1 || i>L.length + 1)
		return ERROR;
	if (L.length >= L.listsize)
	{
		L.elem = (ElemType*)realloc(L.elem, (L.listsize + LIST_INIT_SIZE) * sizeof(ElemType));
		L.listsize += LIST_INIT_SIZE;
	}
	int j;
	if (L.length == 0)
	{
		L.length++;
		L.elem[0] = e;
		return OK;
	}
	for (j = L.length; j >= i; j--)
		L.elem[j] = L.elem[j - 1];
	L.elem[i - 1] = e;
	L.length += 1;
	return OK;
}

status ListDelete(SqList& L, ElemType& e)//11
{
	int i = 0;
	printf("	请输入你要删除的元素的位次序号\n");
	scanf("%d", &i);
	if (!L.elem)
		return INFEASIBLE;
	if (i<1 || i>L.length)
		return ERROR;
	e = L.elem[i - 1];
	for (int j = i - 1; j < L.length; j++)
		L.elem[j] = L.elem[j + 1];
	L.length--;
	return OK;
}

status MaxSubArray(SqList L)
{
	if (!L.elem)
		return INFEASIBLE;
	if (!L.length)
		return ERROR;
	int max_sum = 0, now_sum;
	for (int i = 0; i < L.length; i++)
	{
		now_sum = 0;
		for (int j = i; j < L.length; j++)
		{
			now_sum += L.elem[j];
			if (now_sum > max_sum)
				max_sum = now_sum;
		}
	}
	return max_sum;
}

status SubArrayNum(SqList L)
{
	printf("	请输入您想要查找的连续子数组的和：");
	int e = 0;
	scanf("%d", &e);
	if (!L.elem)
		return INFEASIBLE;
	if (!L.length)
		return ERROR;
	int  now_sum, count = 0;
	for (int i = 0; i < L.length; i++)
	{
		now_sum = 0;
		for (int j = i; j < L.length; j++)
		{
			now_sum += L.elem[j];
			if (now_sum == e)
				count++;
		}
	}
	return count;
}

status sortList(SqList& L)
{
	if (!L.elem)
		return INFEASIBLE;
	if (!L.length)
		return ERROR;
	qsort(L.elem, L.length, sizeof(ElemType), compare);
	return OK;
}

status ListTraverse(SqList L)//12
{
	if (!L.elem)
		return INFEASIBLE;
	int i;
	if (L.length == 0)
	{
		printf_yellow("	线性表为空！\n");
		return OK;
	}
	for (i = 0; i < L.length - 1; i++)
		printf("%d ", L.elem[i]);
	printf("%d", L.elem[i]);
	return OK;
}

status  SaveList(SqList L, char FileName[])//13
// 如果线性表L存在，将线性表L的的元素写到FileName文件中，返回OK，否则返回INFEASIBLE。
{
	// 请在这里补充代码，完成本关任务
	/********** Begin *********/
	if (!L.elem)
		return INFEASIBLE;
	FILE* w = fopen(FileName, "w");
	if (!w)
		return ERROR;
	for (int i = 0; i < L.length; i++)
	{
		fprintf(w, "%d ", L.elem[i]);
	}
	fclose(w);
	return OK;
	/********** End **********/
}
status  LoadList(SqList& L, char FileName[])//14
{
	int t, i = 0;
	FILE* r = fopen(FileName, "r");
	if (!r)
		return ERROR;
	while (fscanf(r, "%d", &t) != EOF)
	{
		L.elem[i++] = t;
	}
	L.length = i;
	fclose(r);
	return OK;
}

status AddList(LISTS& Lists)//15
{
	if (Lists.length >= 10)
		return ERROR;
	char ListName[100];
	printf("请输入您想添加的线性表的名称：");
	scanf("%s", ListName);
	if (strlen(ListName) >= 20)
	{
		printf_red("名字过长！\n");
		return ERROR;
	}
	ElemType i;
	for (i = 0; ListName[i]; i++)
	{
		Lists.elem[Lists.length].name[i] = ListName[i];
	}
	Lists.elem[Lists.length].name[i] = ListName[i];
	Lists.elem[Lists.length].L.elem = NULL;
	InitList(Lists.elem[Lists.length].L);
	Lists.length++;
	return OK;
}

status RemoveList(LISTS& Lists)//16
{
	char ListName[20];
	printf("请输入您要删除的线性表的名称：");
	scanf("%s", ListName);
	int i, j;
	for (i = 0, j = 0; i < Lists.length; i++)
	{
		if (strcmp(ListName, Lists.elem[i].name) == 0)
		{
			DestroyList(Lists.elem[i].L);
			for (int j = i; j < Lists.length - 1; j++)
			{
				Lists.elem[j] = Lists.elem[j + 1];
			}
			Lists.length--;
			return OK;
		}
	}
	return ERROR;
}

int LocateList(LISTS Lists)
{
	char ListName[20];
	printf("请输入您要查找的线性表的名称：");
	scanf("%s", ListName);
	int i, j, f = 1;
	for (i = 0; i < Lists.length; i++)
	{
		if (strcmp(ListName, Lists.elem[i].name) == 0)
			return i + 1;
	}
	return 0;
}

status ShiftList()
{
	int i;
	printf("请输入您要操作的线性表的序号：");
	scanf("%d", &i);
	if (i > Lists.length)
		return ERROR;
	n = i - 1;
	return OK;
}

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
