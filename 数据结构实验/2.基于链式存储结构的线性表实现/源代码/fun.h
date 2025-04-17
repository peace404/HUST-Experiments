#pragma once

extern int n;
extern LISTS Lists;

status InitList(LinkList& L)//1
{
	if (L)
		return INFEASIBLE;
	L = (LinkList)malloc(sizeof(LNode));
	L->next = NULL;
	return OK;
}

status DestroyList(LinkList& L)//2
{
	if (!L)
		return INFEASIBLE;
	LinkList p;
	while (L)
	{
		p = L->next;
		free(L);
		L = p;
	}
	return OK;
}


status ClearList(LinkList& L)//3
{
	if (!L)
		return INFEASIBLE;
	if (!L->next)
		return ERROR;
	LinkList p=L->next,q;
	while (p)
	{
		q = p->next;
		free(p);
		p = q;
	}
	L->next = NULL;
	return OK;
}

status ListEmpty(LinkList L)//4
{
	if (!L)
		return INFEASIBLE;
	if (L->next == NULL)
		return TRUE;
	else
		return FALSE;
}

int ListLength(LinkList L)//5
{
	if (!L)
		return INFEASIBLE;
	int count = 0;
	while (L->next)
	{
		count++;
		L = L->next;
	}
	return count;
}

status GetElem(LinkList L, ElemType& e)//6
{
	if (!L)
		return INFEASIBLE;
	int i = 0;
	printf("	请输入您要查找的元素的位次？\n");
	scanf("%d", &i);
	LinkList p = L->next;
	for (int j = 1; j < i && p; j++)
	{
		p = p->next;
	}
	if (i < 1 || !p)
		return ERROR;
	e = p->data;
	return OK;
}

status LocateElem(LinkList L)//7
{
	if (!L)
		return INFEASIBLE;
	int e = 0;
	printf("	请输入您要查找的元素？\n");
	scanf("%d", &e);
	LinkList p = L->next;
	for (int i = 1; p; i++)
	{
		if (p->data == e)
			return i;
		p = p->next;
	}
	return ERROR;
}

status PriorElem(LinkList L,ElemType& pre)//8
{
	if (!L)
		return INFEASIBLE;
	int e = 0;
	printf("	请输入要查找的元素\n");
	scanf("%d", &e);
	LinkList p;
	if (L->next == NULL)
		return ERROR;
	p = L->next;
	for (; p->next && p->next->data != e; p = p->next);
	if (!L->next || !p->next)
		return ERROR;
	pre = p->data;
	return OK;
}

status NextElem(LinkList L, ElemType& next)//9
{
	if (!L)
		return INFEASIBLE;
	int e;
	printf("	请输入要查找的元素：");
	scanf("%d", &e);
	LinkList p;
	if (L->next == NULL)
		return ERROR;
	p = L;
	for (; p->next && p->data != e; p = p->next);
	if (!p->next)
		return ERROR;
	next = p->next->data;
	return OK;
}

status ListInsert(LinkList& L)//10
{
	if (!L)
		return INFEASIBLE;
	int e = 0, i = 0;
	printf("	请输入你要插入的元素\n");
	scanf("%d", &e);
	printf("	请输入你要插入的位次序号\n");
	scanf("%d", &i);
	LinkList p = L;
	for (int j = 0; j < i - 1 && p; j++, p = p->next);
	if (!p || i < 1)
		return ERROR;
	LinkList q = (LinkList)malloc(sizeof(LNode));
	q->data = e;
	q->next = p->next;
	p->next = q;
	return OK;
}

status ListDelete(LinkList& L, ElemType& e)//11
{
	if (!L)
		return INFEASIBLE;
	int i = 0;
	printf("	请输入你要删除的元素的位次序号\n");
	scanf("%d", &i);
	LinkList p = L;
	for (int j = 0; j < i - 1 && p; j++, p = p->next);
	if (!p->next || i < 1)
		return ERROR;
	LinkList q = p->next;
	e = q->data;
	p->next = q->next;
	free(q);
	return OK;
}

status ListTraverse(LinkList L)//12
{
	if (!L)
		return INFEASIBLE;
	LinkList p = L->next;
	while (p)
	{
		printf("%d ", p->data);
		p = p->next;
	}
	return OK;
}

status reverseList(LinkList& L)//13
{
	if (!L)
		return INFEASIBLE;
	if (!L->next)
		return ERROR;
	LinkList temp = NULL, new_head = NULL, p = L->next;
	while(p)
	{
		temp = p;
		p = p->next;
		temp->next = new_head;
		new_head = temp;
	}
	L->next = new_head;
	return OK;
}

status RemoveNthFromEnd(LinkList& L)//14
{
	if (!L)
		return INFEASIBLE;
	if (!L->next)
		return ERROR;
	printf("	您要删除的是该链表中倒数第几个节点? ");
	int n;
	scanf("%d", &n);
	LinkList p, q;
	p = q = L;
	for (int i = 0; i < n; i++)
		q = q->next;
	while (q->next)
	{
		q = q->next;
		p = p->next;
	}
	p->next = p->next->next;
	return OK;
}

status sortList(LinkList& L)//15
{
	if (!L)
		return INFEASIBLE;
	if (!L->next)
		return ERROR;
	LinkList pre, p, q;
	p = L->next->next;
	L->next->next = NULL;
	while (p)
	{
		q = p->next;
		pre = L;
		while (pre->next && pre->next->data < p->data)
			pre = pre->next;
		p->next = pre->next;
		pre->next = p;
		p = q;
	}
	return OK;
}

status SaveList(LinkList L)//16
{
	if (!L)
		return INFEASIBLE;
	char filename[20];
	printf("	您要写入的文件夹名称为：");
	scanf("%s", filename);
	LinkList p;
	p = L->next;
	FILE* w = fopen(filename, "w");
	while (p)
	{
		fprintf(w, "%d ", p->data);
		p = p->next;
	}
	fprintf(w, "\n");
	fclose(w);
	return OK;
}

status LoadList(LinkList& L)
{
	if (!L)
		return INFEASIBLE;
	if (L->next)
		return ERROR;
	char filename[20];
	printf("	您要读入的文件夹名称为：");
	scanf("%s", filename);
	LinkList p;
	L = (LinkList)malloc(sizeof(LNode));
	p = L;
	FILE* r = fopen(filename,"r");
	int t;
	while (fscanf(r, "%d", &t) != EOF)
	{
		p->next = (LinkList)malloc(sizeof(LNode));
		p = p->next;
		p->data = t;
	}
	p->next = NULL;
	fclose(r);
	return OK;
}

status AddList(LISTS& Lists)//15
{
	if (Lists.length >= 10)
		return ERROR;
	char ListName[100];
	printf("	请输入您想添加的线性表的名称：");
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
	InitList(Lists.elem[Lists.length].L);
	Lists.length++;
	return OK;
}

status ShiftList()//16
{
	int i;
	printf("	请输入您要操作的线性表的序号：");
	scanf("%d", &i);
	if (i > Lists.length)
		return ERROR;
	n = i - 1;
	return OK;
}

status RemoveList(LISTS& Lists)//17
{
	char ListName[20];
	printf("	请输入您要删除的线性表的名称：");
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

int LocateList(LISTS Lists)//18
{
	char ListName[20];
	printf("	请输入您要查找的线性表的名称：");
	scanf("%s", ListName);
	int i, f = 1;
	for (i = 0; i < Lists.length; i++)
	{
		if (strcmp(ListName, Lists.elem[i].name) == 0)
			return i + 1;
	}
	return 0;
}

