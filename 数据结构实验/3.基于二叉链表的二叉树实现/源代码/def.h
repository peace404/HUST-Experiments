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

typedef int status;
typedef int KeyType;
typedef struct {
	KeyType  key;
	char others[20];
} TElemType; //二叉树结点类型定义


typedef struct BiTNode {  //二叉链表结点的定义
	TElemType  data;
	struct BiTNode* lchild, * rchild;
} BiTNode, * BiTree;

typedef struct {  //线性表的管理表定义
    struct {
        char name[30];
        BiTree L;
    } elem[10];
    int length;
    int listsize;
}LISTS;

BiTNode* LocateNode(BiTree T, KeyType e);
BiTNode* LocateNodep(BiTree T, KeyType e);
