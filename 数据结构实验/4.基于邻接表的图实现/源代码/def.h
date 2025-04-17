#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAX_VERTEX_NUM 20
typedef int status;
typedef int KeyType;
typedef enum { DG, DN, UDG, UDN } GraphKind;
typedef struct {
	KeyType  key;
	char others[20];
} VertexType; //�������Ͷ���

typedef struct ArcNode {         //�������Ͷ���
	int adjvex;              //����λ�ñ�� 
	struct ArcNode* nextarc;	   //��һ������ָ��
} ArcNode;
typedef struct VNode {				//ͷ��㼰���������Ͷ���
	VertexType data;       	//������Ϣ
	ArcNode* firstarc;      	 //ָ���һ����
} VNode, AdjList[MAX_VERTEX_NUM];
typedef  struct {  //�ڽӱ�����Ͷ���
	AdjList vertices;     	 //ͷ�������
	int vexnum, arcnum;   	  //������������
	GraphKind  kind;        //ͼ������
} ALGraph;

typedef struct {  //���Ա�Ĺ������
	struct {
		char name[30];
		ALGraph L;
	} elem[10];
	int length;
	int listsize;
}LISTS;
int LocateVex(ALGraph G, KeyType u);
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
void visit(VertexType v)
{
	printf(" %d %s", v.key, v.others);
}
