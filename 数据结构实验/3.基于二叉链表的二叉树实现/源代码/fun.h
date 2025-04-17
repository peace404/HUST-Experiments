#pragma once
void PT(BiTree T,int a[])
{
    if (T == NULL)
        return;
    a[T->data.key]++;
    PT(T->lchild,a);
    PT(T->rchild,a);
}

status CreateBiTree(BiTree& T, TElemType definition[])
{
    int a[9999] = { 0 };
    for (int k = 0; definition[k].key != -1; k++)
    {
        if (definition[k].key && a[definition[k].key] > 0)
            return ERROR;
        a[definition[k].key]++;
    }
    static int i = -1;
    i++;
    if (definition[i].key == 0)
        T = NULL;
    else
    {
        T = (BiTree)malloc(sizeof(BiTNode));
        T->data.key = definition[i].key; //生成根结点
        strcpy(T->data.others, definition[i].others); //生成根结点
        CreateBiTree(T->lchild, definition); //递归构造左子树
        CreateBiTree(T->rchild, definition); //递归构造右子树
    }
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
BiTNode* LocateNodep(BiTree T, KeyType e)
{
    if (!T)
        return NULL;
    if (T->lchild != NULL && T->lchild->data.key == e || T->rchild != NULL && T->rchild->data.key == e)
        return T;
    BiTree temp;
    temp = LocateNodep(T->lchild, e);
    if (temp)
        return temp;
    else
        return LocateNodep(T->rchild, e);
}


/*-------------------------------------------------------*/
void DestroyBiTree(BiTree& T)
{
    if (T == NULL) 
        return;
    DestroyBiTree(T->lchild);
    DestroyBiTree(T->rchild);
    free(T);
    T = NULL;
}
void ClearBiTree(BiTree& T)
{
    if (T == NULL) 
        return;
    ClearBiTree(T->lchild);
    ClearBiTree(T->rchild);
    T = NULL;

}
status BiTreeEmpty(BiTree T)
{
    if (T == NULL)
        return OK;
    else
        return ERROR;
}
int BiTreeDepth(BiTree T)
{
    int lH = 0, rH = 0, maxH = 0;//左子树，右子树，最大深度
    if (T == NULL) //如果为空树
        return 0;
    else
    {
        lH = BiTreeDepth(T->lchild);//左子树深度
        rH = BiTreeDepth(T->rchild);//右子树深度
        maxH = lH > rH ? lH : rH;
        return maxH + 1;//二叉树深度=最大深度+1
    }
}
BiTNode* LocateNode(BiTree T, KeyType e)
{
    BiTree tT;
    if (T == NULL)
        return NULL;
    if (T->data.key == e)
        return T;
    tT = LocateNode(T->lchild, e);
    if (tT)
        return tT;
    tT = LocateNode(T->rchild, e);
    if (tT)
        return tT;
}
status Assign(BiTree& T)
{
    KeyType e;
    TElemType value;
    BiTree t = NULL;
    printf("请输入您要替换的关键字：");
    scanf("%d", &e);
    printf("请输入新的关键字与字符串：");
    scanf("%d %s", &value.key, value.others);
    t = LocateNode(T, e);
    int a[9999] = { 0 };
    PT(T, a);
    if(a[value.key])
        return ERROR;
    t->data.key = value.key;
    strcpy(t->data.others, value.others);
    return OK;
}
BiTNode* GetSibling(BiTree T, KeyType e)
{
    BiTNode* p=NULL, * q=NULL;
    p = LocateNodep(T, e);
    q = LocateNode(T, e);
    if (p == NULL || q == NULL)
        return NULL;
    if (q == p->lchild && p->rchild != NULL)
        return p->rchild;
    if(q == p->rchild && p->lchild != NULL)
        return p->lchild;
    return NULL;
}
status InsertNode(BiTree& T, KeyType e, int LR, TElemType c)
{
    if (c.key <= e)
        return ERROR;
    BiTree t=NULL;
    t = LocateNode(T, e);
    BiTree nw;
    nw = (BiTree)malloc(sizeof(BiTNode));
    nw->data.key = c.key;
    strcpy(nw->data.others, c.others);
    if (LR == 0)
    {
        nw->rchild = t->lchild;
        t->lchild = nw;
        nw->lchild = NULL;
    }
    else if (LR == 1)
    {
        nw->rchild = t->rchild;
        t->rchild = nw;
        nw->rchild = NULL;
    }
    else if (LR == -1)
    {
        nw->rchild = T;
        T = nw;
    }
    return OK;
}
status DeleteNode(BiTree& T, KeyType e)
{
    BiTree t=NULL,p=NULL, tp=NULL;
    t = LocateNode(T, e);
    tp = LocateNodep(T, e);
    if (!t)
        return ERROR;
    if (!tp)
    {
        if (!(t->lchild || t->rchild))
            free(T);
        else if (!t->lchild && t->rchild)
        {
            p = T;
            free(p);
            T = T->rchild;
        }
        else if (!t->rchild && t->lchild)
        {
            p = T;
            free(p);
            T = T->lchild;
        }
        else
        {
            p = t->lchild;
            while (p->rchild)
            {
                p = p->rchild;
            }
            p->rchild = t->rchild;
            p = t->lchild;
            free(t);
            T = p;
        }

    }
    else
    {
        if (!(t->lchild || t->rchild))
        {
            if (t == tp->lchild)
            {
                free(t);
                tp->lchild = NULL;
            }
            else
            {
                free(t);
                tp->rchild = NULL;
            }
        }
        else if (!t->lchild && t->rchild)
        {
            p = t->rchild;
            if (t == tp->lchild)
            {
                free(t);
                tp->lchild = p;
            }
            else
            {
                free(t);
                tp->rchild = p;
            }
        }
        else if (t->lchild && !t->rchild)
        {
            p = t->lchild;
            if (t == tp->lchild)
            {
                free(t);
                tp->lchild = p;
            }
            else
            {
                free(t);
                tp->rchild = p;
            }
        }
        else
        {
            p = t->lchild;
            while (p->rchild)
            {
                p = p->rchild;
            }
            p->rchild = t->rchild;
            p = t->lchild;
            free(t);
            if (t == tp->lchild)
                tp->lchild = p;
            else
                tp->rchild = p;
        }
    }
    return OK;
    /********** End **********/
}
void PreOrderTraverse(BiTree T)
{
    if (T == NULL)
        return;
    printf("%d %s ", T->data.key, T->data.others);
    PreOrderTraverse(T->lchild);
    PreOrderTraverse(T->rchild);
}
void InOrderTraverse(BiTree T)
{
    if (T == NULL)
        return;
    InOrderTraverse(T->lchild);
    printf("%d %s ", T->data.key, T->data.others);
    InOrderTraverse(T->rchild);
}
void PostOrderTraverse(BiTree T)
{
    BiTree  St[9999], pre;
    int flag, top = 0;
    do
    {
        while (T != NULL)
        {
            St[top++] = T;
            T = T->lchild;
        }
        pre = NULL;
        flag = 1;
        while (top && flag)
        {
            T = St[top - 1];
            if (T->rchild == pre)
            {
                printf("%d %s ", T->data.key, T->data.others);
                top--;
                pre = T;
            }
            else
            {
                T = T->rchild;
                flag = 0;
            }
        }
    } while (top);
    return ;
}
void LevelOrderTraverse(BiTree T)
{
    BiTree que[9999] = { 0 };
    BiTree p;
    int front = 0, rear = 0;
    que[rear++] = T;
    while (front != rear)
    {
        p = que[front];
        printf("%d %s ", que[front]->data.key, que[front]->data.others);
        front++;
        if (p->lchild)
            que[rear++] = p->lchild;
        if (p->rchild)
            que[rear++] = p->rchild;
    }
    return ;
}
/*-------------------------------------------------------*/
int maxPathSum(BiTree T)
{
    if (!T) 
        return 0;
    int left = max(0, maxPathSum(T->lchild));
    int right = max(0, maxPathSum(T->rchild));
    maxSum = max(maxSum, left + right + T->data.key);
    return T->data.key + max(left, right);
}
BiTree LowestCommonAncestor(BiTree T, KeyType pk, KeyType qk)
{
    BiTree q = NULL, p = NULL;
    q = LocateNode(T, pk);
    p = LocateNode(T, qk);
    if (T == q || T == p || T == NULL)
        return T;
    BiTree left = LowestCommonAncestor(T->lchild, pk, qk);
    BiTree right = LowestCommonAncestor(T->rchild, pk, qk);
    if (left != NULL && right != NULL)
        return T;
    if (left == NULL)
        return right;
    return left;
}
BiTree invertTree(BiTree T)
{
    if (T == NULL)
        return NULL;
    BiTree left = invertTree(T->lchild);
    BiTree right = invertTree(T->rchild);
    T->lchild = right;
    T->rchild = left;
    return T;
}
status SaveBiTree(BiTree T, char FileName[])
{
    static FILE* file = fopen(FileName, "w");
    if (!file)
        return ERROR;
    static int fs = 0;
    int ff = fs++;
    if (T == NULL)
    {
        fprintf(file, "0 null ");
        return OK;
    }
    fprintf(file, "%d %s ", T->data.key, T->data.others);
    SaveBiTree(T->lchild, FileName);
    SaveBiTree(T->rchild, FileName);
    if (ff == 0)
    {
        fprintf(file, "-1 null ");
        fclose(file);
    }
    return OK;
}
status LoadBiTree(BiTree& T, TElemType definition[])
{
    i++;
    if (definition[i].key == 0)
        T = NULL;
    else
    {
        T = (BiTree)malloc(sizeof(BiTNode));
        T->data.key = definition[i].key; //生成根结点
        strcpy(T->data.others, definition[i].others); //生成根结点
        LoadBiTree(T->lchild, definition);
        LoadBiTree(T->rchild, definition);
    }
    return OK;
}
/*-------------------------------------------------------*/
status AddList(LISTS& Lists)//15
{
    if (Lists.length >= 10)
        return ERROR;
    char ListName[100];
    printf("	请输入您想添加的线性表的名称：");
    scanf("%s", ListName);
    if (strlen(ListName) >= 20)
    {
        printf_red("    名字过长！\n");
        return ERROR;
    }
    strcpy(Lists.elem[Lists.length].name, ListName);
    TElemType definition[9999] = { 0 };
    int j = 0;
    printf("    请输入二叉树内容：");
    do {
        scanf("%d%s", &definition[j].key, definition[j].others);
    } while (definition[j++].key != -1);
    CreateBiTree(Lists.elem[Lists.length].L, definition);
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
            DestroyBiTree(Lists.elem[i].L);
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
