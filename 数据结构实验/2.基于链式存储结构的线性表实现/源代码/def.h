#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10

typedef int status;
typedef int ElemType; //数据元素类型定义
typedef int ElemType;

typedef struct LNode {  //单链表（链式结构）结点的定义
    ElemType data;
    struct LNode* next;
}LNode, * LinkList;

typedef struct {  //线性表的管理表定义
    struct {
        char name[30];
        LinkList L;
    } elem[10];
    int length;
    int listsize;
}LISTS;

status InitList(LinkList&);//1
status DestroyList(LinkList&);//2
status ClearList(LinkList&);//3
status ListEmpty(LinkList);//4
int ListLength(LinkList);//5
status GetElem(LinkList, ElemType&);//6
status LocateElem(LinkList); //7
status PriorElem(LinkList, ElemType&);//8
status NextElem(LinkList, ElemType&);//9
status ListInsert(LinkList&);//10
status ListDelete(LinkList&, ElemType&);//11
status ListTraverse(LinkList);//12
status reverseList(LinkList&);//13
status RemoveNthFromEnd(LinkList&, ElemType);//14
status sortList(LinkList&);//15
status SaveList(LinkList);//16

int compare(const void* a, const void* b);
/*--------------------------------------------*/

void printf_red(const char* s);
void printf_green(const char* s);
void printf_yellow(const char* s);
