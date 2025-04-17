#pragma once
status CreateCraph(ALGraph& G)
{
    VertexType V[MAX_VERTEX_NUM]; KeyType VR[MAX_VERTEX_NUM][2];
    printf("    请输入顶点序列和关系对序列：");
    int i = 0;
    do {
        scanf("%d %s", &V[i].key, V[i].others);
    } while (V[i++].key != -1);
    i = 0;
    do {
        scanf("%d %d", &VR[i][0], &VR[i][1]);
    } while (VR[i++][1] != -1);
    int j, k;
    int check[MAX_VERTEX_NUM] = {0};
    for (i = 0; V[i].key != -1; i++)
    {
        if (check[V[i].key] != 0)
            return ERROR;
        check[V[i].key]++;
    }
    if (i == 0 || i >= 21)
        return ERROR;
    G.vexnum = 0, G.arcnum = 0;
    for (i = 0; i < MAX_VERTEX_NUM; i++)
        G.vertices[i].firstarc = NULL;
    i = 0;
    while (V[i].key != -1)
    {
        G.vertices[i].data.key = V[i].key;
        strcpy(G.vertices[i].data.others, V[i].others);
        i++;
    }
    G.vexnum = i;
    for (k = 0; VR[k][0] != -1; k++)
    {
        i = LocateVex(G, VR[k][0]);
        j = LocateVex(G, VR[k][1]);
        if (i == -1 || j == -1)
            return ERROR;
        ArcNode* p = (ArcNode*)malloc(sizeof(ArcNode));
        p->adjvex = j, p->nextarc = G.vertices[i].firstarc, G.vertices[i].firstarc = p;
        p = (ArcNode*)malloc(sizeof(ArcNode));
        p->adjvex = i, p->nextarc = G.vertices[j].firstarc, G.vertices[j].firstarc = p;
        G.arcnum++;
    }
    return OK;
}
status DestroyGraph(ALGraph& G)
{
    int i;
    ArcNode* p, * q;
    for (i = 0; i < G.vexnum; i++) {
        p = G.vertices[i].firstarc;
        while (p) {
            q = p->nextarc;
            free(p);
            p = q;
        }
    }
    G.vexnum = 0;
    G.arcnum = 0;
    return OK;
}
int LocateVex(ALGraph G, KeyType u)
{
    int i;
    for (i = 0; i < G.vexnum; i++) 
    {
        if (u == G.vertices[i].data.key)
            return i;
    }
    return -1;
}
status PutVex(ALGraph& G, KeyType u, VertexType value)
{
    int check[MAX_VERTEX_NUM] = { 0 };
    for (int i = 0; i < G.vexnum; i++)
        check[G.vertices[i].data.key]++;
    for (int i = 0; i < G.vexnum; i++) {
        if (G.vertices[i].data.key == u && !check[value.key])
        {
            G.vertices[i].data.key = value.key;
            strcpy(G.vertices[i].data.others, value.others);
            return OK;
        }
    }
    return ERROR;
}
int FirstAdjVex(ALGraph G, KeyType u)
{
    int i;
    for (i = 0; i < G.vexnum && G.vertices[i].data.key != u; i++);
    if (i == G.vexnum) {
        return -1;
    }
    ArcNode* p = G.vertices[i].firstarc;
    if (p) {
        return p->adjvex;
    }
    else {
        return -1;
    }
}
int NextAdjVex(ALGraph G, KeyType v, KeyType w)
{
    int i;
    for (i = 0; i < G.vexnum && G.vertices[i].data.key != v; i++);
    if (i == G.vexnum)
        return -1;
    ArcNode* p = G.vertices[i].firstarc;
    while (p && G.vertices[p->adjvex].data.key != w) {
        p = p->nextarc;
    }
    if (!p || !p->nextarc) {
        return -1;
    }
    return p->nextarc->adjvex;
}
status InsertVex(ALGraph& G, VertexType v)
{
    for (int i = 0; i < G.vexnum; i++)
    {
        if (G.vertices[i].data.key == v.key)
            return ERROR;
    }

    if (G.vexnum == MAX_VERTEX_NUM) return ERROR;
    G.vertices[G.vexnum].data.key = v.key;
    strcpy(G.vertices[G.vexnum].data.others, v.others);
    G.vertices[G.vexnum].firstarc = NULL;
    G.vexnum++;
    return OK;
}
status DeleteVex(ALGraph& G, KeyType v)
{
    int i, j, k;
    ArcNode* p, * q;
    for (i = 0; i < G.vexnum && G.vertices[i].data.key != v; i++);
    if (i == G.vexnum)
        return ERROR;
    p = G.vertices[i].firstarc;
    while (p)
    {
        q = p;
        p = p->nextarc;
        free(q);
        G.arcnum--;
    }
    if (!G.arcnum)
        return ERROR;
    for (j = i; j < G.vexnum - 1; j++)
    {
        G.vertices[j] = G.vertices[j + 1];
    }
    G.vexnum--;
    for (k = 0; k < G.vexnum; k++)
    {
        p = G.vertices[k].firstarc;
        ArcNode* pre = NULL;
        while (p)
        {
            if (p->adjvex == i)
            {
                if (pre == NULL)
                    G.vertices[k].firstarc = p->nextarc;
                else
                    pre->nextarc = p->nextarc;
                    q = p;
                    p = p->nextarc;
                    free(q);
            }
            else
            {
                pre = p;
                p = p->nextarc;
            }
        }
    }
    return OK;
}
status InsertArc(ALGraph& G, KeyType v, KeyType w)
{
    int i, j;
    ArcNode* p;
    i = LocateVex(G, v);
    j = LocateVex(G, w);
    if (i < 0 || j < 0)
        return ERROR;
    for (ArcNode* q = G.vertices[i].firstarc; q; q = q->nextarc)
    {
        if (q->adjvex == j)
            return ERROR;
    }
    p = (ArcNode*)malloc(sizeof(ArcNode));
    p->adjvex = j;
    p->nextarc = G.vertices[i].firstarc;
    G.vertices[i].firstarc = p;
    p = (ArcNode*)malloc(sizeof(ArcNode));
    p->adjvex = i;
    p->nextarc = G.vertices[j].firstarc;
    G.vertices[j].firstarc = p;
    G.arcnum++;
    return OK;
}
status DeleteArc(ALGraph& G, KeyType v, KeyType w)
{
    int i, j;
    ArcNode* p1, * p2, * q;
    i = LocateVex(G, v);
    j = LocateVex(G, w);
    if (i < 0 || j < 0)
        return ERROR;
    p1 = G.vertices[i].firstarc;
    q = NULL;
    while (p1 != NULL)
    {
        if (p1->adjvex == j)
            break;
        q = p1;
        p1 = p1->nextarc;
    }
    if (p1 == NULL)
        return ERROR;
    if (q == NULL)
        G.vertices[i].firstarc = p1->nextarc;
    else
        q->nextarc = p1->nextarc;
    free(p1);
    p2 = G.vertices[j].firstarc;
    q = NULL;
    while (p2 != NULL)
    {
        if (p2->adjvex == i)
            break;
        q = p2;
        p2 = p2->nextarc;
    }
    if (p2 == NULL)
        return ERROR;
    if (q == NULL)
        G.vertices[j].firstarc = p2->nextarc;
    else
        q->nextarc = p2->nextarc;
    free(p2);
    G.arcnum--;
    return OK;
}
status DFSTraverse(ALGraph& G, void (*visit)(VertexType))
{
    int visited[MAX_VERTEX_NUM] = { 0 };
    int stack[MAX_VERTEX_NUM] = { 0 };
    int  top = 0, i = 0, pos;
    visit(G.vertices[i].data);
    stack[top++] = i;
    while (top > 0)
    {
        pos = stack[top - 1];
        visited[pos] = 1;
        ArcNode* e = G.vertices[pos].firstarc;
        while (e && visited[e->adjvex])
        {
            e = e->nextarc;
        }
        if (e == NULL)
            top--;
        else
        {
            visit(G.vertices[e->adjvex].data);
            stack[top++] = e->adjvex;
        }
    }
    return OK;
}
status BFSTraverse(ALGraph& G, void (*visit)(VertexType))
{
    int visited[MAX_VERTEX_NUM] = { 0 };
    int que[MAX_VERTEX_NUM] = { 0 };
    int head = 0, tail = 0, pos, i = 0;
    visit(G.vertices[i].data);
    que[tail++] = i;
    while (head < tail)
    {
        pos = que[head++];
        visited[pos] = 1;
        ArcNode* e = G.vertices[pos].firstarc;
        while (e)
        {
            if (!visited[e->adjvex])
            {
                que[tail++] = e->adjvex;
                visit(G.vertices[e->adjvex].data);
            }
            e = e->nextarc;
        }
    }
    return OK;
}
status VerticesSetLessThanK(ALGraph G, KeyType v, int k, void (*visit)(VertexType))
{
    int dis[MAX_VERTEX_NUM], que[MAX_VERTEX_NUM], head = 0, tail = 0;
    memset(dis, -1, sizeof(dis));
    int p=LocateVex(G, v),pos;
    dis[p] = 0;
    que[tail++] = p;
    while (head < tail)
    {
        int pos;
        pos = que[head++];
        ArcNode* e = G.vertices[pos].firstarc;
        while (e)
        {
            if (dis[e->adjvex] == -1)
            {
                dis[e->adjvex] = dis[pos] + 1;
                if(dis[e->adjvex]<k)
                    visit(G.vertices[e->adjvex].data);
                que[tail++] = e->adjvex;
            }
            e = e->nextarc;
        }
    }
    return OK;
}
status ShortestPathLength(ALGraph G, KeyType v, KeyType w)
{
    int dis[MAX_VERTEX_NUM], que[MAX_VERTEX_NUM], head = 0, tail = 0;
    memset(dis, -1, sizeof(dis));
    int p = LocateVex(G, v), q = LocateVex(G, w), pos;
    dis[p] = 0;
    que[tail++] = p;
    while (head < tail)
    {
        int pos;
        pos = que[head++];
        ArcNode* e = G.vertices[pos].firstarc;
        while (e)
        {
            if (dis[e->adjvex] == -1)
            {
                dis[e->adjvex] = dis[pos] + 1;
                que[tail++] = e->adjvex;
            }
            e = e->nextarc;
        }
    }
    if (dis[q] < 0)
        return ERROR;
    printf("最短路径长度为%d\n",dis[q]);
    return OK;
}
status SaveGraph(ALGraph G, char FileName[])
{
    int ct = 0;
    FILE* fp = fopen(FileName, "w");
    if (fp == NULL)
        return ERROR;
    fprintf(fp, "%d %d\n", G.vexnum, G.arcnum);
    for (int i = 0; i < G.vexnum; i++)
    {
        fprintf(fp, "%d %s ", G.vertices[i].data.key, G.vertices[i].data.others);
        ArcNode* p = G.vertices[i].firstarc;
        while (p)
        {
            fprintf(fp, "%d ", p->adjvex);
            p = p->nextarc;
        }
        fprintf(fp, "-1\n");
    }
    fclose(fp);
    return OK;
}
status LoadGraph(ALGraph& G, char FileName[])
{
    FILE* fp = fopen(FileName, "r");
    if (fp == NULL)
        return ERROR;
    ArcNode* p, * q;
    fscanf(fp, "%d %d", &G.vexnum, &G.arcnum);
    for (int i = 0; i < G.vexnum; i++)
    {
        fscanf(fp, "%d %s ", &G.vertices[i].data.key, G.vertices[i].data.others);
        G.vertices[i].firstarc = NULL;
        int adjvex;
        fscanf(fp, "%d", &adjvex);
        q = NULL;
        while (adjvex != -1)
        {
            p = (ArcNode*)malloc(sizeof(ArcNode));
            p->adjvex = adjvex;
            p->nextarc = NULL;
            if (q == NULL)
                G.vertices[i].firstarc = p;
            else
                q->nextarc = p;
            q = p;
            fscanf(fp, "%d", &adjvex);
        }
    }
    fclose(fp);
    return OK;
}
status AddList(LISTS& Lists)//15
{
    if (Lists.length >= 10)
        return ERROR;
    char ListName[100];
    printf("    请输入您想添加的线性表的名称：");
    scanf("%s", ListName);
    if (strlen(ListName) >= 20)
    {
        printf_red("    名字过长！\n");
        return ERROR;
    }
    strcpy(Lists.elem[Lists.length].name, ListName);
    CreateCraph(Lists.elem[Lists.length].L);
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
            DestroyGraph(Lists.elem[i].L);
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
