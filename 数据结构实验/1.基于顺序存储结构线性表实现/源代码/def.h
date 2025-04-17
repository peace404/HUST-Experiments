#pragma once
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int status;
typedef int ElemType; //����Ԫ�����Ͷ���

#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10

typedef struct {  //˳���˳��ṹ���Ķ���
    ElemType* elem;
    int length;
    int listsize;
}SqList;

typedef struct {  //���Ա�Ĺ������
    struct {
        char name[30];
        SqList L;
    } elem[10];
    int length;
    int listsize;
}LISTS;

//�����Ķ���
status InitList(SqList& L);
status DestroyList(SqList& L);
status ClearList(SqList& L);
status ListEmpty(SqList L);
int ListLength(SqList L);
status GetElem(SqList L, ElemType& e);
status LocateElem(SqList L); //�򻯹�
status PriorElem(SqList L, ElemType& pre_e);
status NextElem(SqList L, ElemType& next_e);
status ListInsert(SqList& L);
status ListDelete(SqList& L, ElemType& e);
status MaxSubArray(SqList L);
status SubArrayNum(SqList L);
status sortList(SqList& L);
status RemoveList(LISTS& Lists);
status ShiftList();
status ListTraverse(SqList L);
status AddList(LISTS& Lists);
int LocateList(LISTS Lists);
status  SaveList(SqList L, char FileName[]);
status  LoadList(SqList& L, char FileName[]);

int compare(const void* a, const void* b);
/*--------------------------------------------*/

void printf_red(const char* s);
void printf_green(const char* s);
void printf_yellow(const char* s);
