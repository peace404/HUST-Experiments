#include"def.h"
#define max(a,b) ((a)>(b)?(a):(b)) 
LISTS Lists;
int n,sta,i;
int maxSum = 9999;
BiTree T;
#include "fun.h"
int main()
{
	int op = 1;
	Lists.length = 0;
	while (op)
	{
		system("cls");	printf("\n\n");
		printf("      Menu for Linear Table On Sequence Structure \n");
		printf("-------------------------------------------------\n");
		printf("    	  1. AddList                2. ShiftList\n");
		printf("    	  3. RemoveList             4. LocateList\n");
		printf("    	  5. DestroyBiTree          6. ClearBiTree\n");
		printf("    	  7. BiTreeEmpty            8. BiTreeDepth\n");
		printf("    	  9. LocateNode             10. Assign\n");
		printf("    	  11. GetSibling            12. InsertNode\n");
		printf("    	  13. DeleteNode            14. PreOrderTraverse\n");
		printf("    	  15. InOrderTraverse       16. PostOrderTraverse\n");
		printf("    	  17. LevelOrderTraverse    18. maxPathSum\n");
		printf("    	  19. LowestCommonAncestor  20. invertTree\n");
		printf("    	  21. SaveBiTree            22. LoadBiTree\n");
		printf("    	  23. CreateBiTree          0. exit\n");
		printf("-------------------------------------------------\n");
		printf("    请选择你的操作[0~23](当前操作二叉树为%d[1~%d]):", n + 1, Lists.length);
		scanf("%d", &op);
		switch (op)
		{
		case 1://AddList
			sta = AddList(Lists);
			if (sta == ERROR)
				printf_red("	添加失败，二叉树数量已达上限！\n");
			else
				printf_green("	添加成功！\n");
			getchar(); getchar();
			break;
		case 2://ShiftList
			sta = ShiftList();
			if (sta == ERROR)
				printf_red("	该二叉树不存在！\n");
			else
				printf_green("	转换成功！\n");
			getchar(); getchar();
			break;
		case 3://RemoveList
			sta = RemoveList(Lists);
			if (sta == OK)
				printf_green("	删除成功！\n");
			else
				printf_red("	未找到该二叉树!\n");
			getchar(); getchar();
			break;
		case 4://LocateList
			sta = LocateList(Lists);
			if (sta == 0)
				printf_red("	未找到该二叉树!\n");
			else
				printf("	这是第%d个二叉树\n", sta);
			getchar(); getchar();
			break;
		case 5://DestroyBiTree
            if(Lists.elem[n].L==NULL)
                printf_red("	二叉树不存在！\n");
            else
            {
			    DestroyBiTree(Lists.elem[n].L);
				printf_green("	二叉树已销毁!\n");
            }
			getchar(); getchar();
			break;
		case 6://ClearBiTree
            if (Lists.elem[n].L == NULL)
                printf_red("	二叉树不存在！\n");
            else
            {
                ClearBiTree(Lists.elem[n].L);
                printf_green("	二叉树已清空!\n");
            }
            getchar(); getchar();
            break;
        case 7://BiTreeEmpty
			sta = BiTreeEmpty(Lists.elem[n].L);
			if (sta == OK)
				printf_green("    二叉树为空！\n");
			else
				printf_yellow("    二叉树不为空！\n");
			getchar(); getchar();
			break;
		case 8://BiTreeDepth
			sta = BiTreeDepth(Lists.elem[n].L);
			if (sta == 0)
				printf_red("	二叉树不存在!\n");
			else
				printf("	二叉树深度为 %d", sta);
			getchar(); getchar();
			break;
		case 9://LocateNode
		{
            BiTree temp = NULL;
			KeyType e;
			printf("您要查找的关键字为：");
			scanf("%d", &e);
			temp = LocateNode(Lists.elem[n].L,e);
			if (temp == NULL)
				printf_red("	二叉树不存在!\n");
			else
				printf("%d %s\n", temp->data.key, temp->data.others);
			getchar(); getchar();
			break;
		}
		case 10://Assign
			sta = Assign(Lists.elem[n].L);
			if (sta == ERROR)
				printf_red("	替换失败!\n");
			else
				printf_green("	替换成功！\n");
			getchar(); getchar();
			break;
		case 11://GetSibling
		{
			BiTree temp;
			KeyType e;
			printf("您要查找的关键字为：");
			scanf("%d", &e);
			temp = GetSibling(Lists.elem[n].L,e);
			if (temp == NULL)
				printf_red("	结点不存在!\n");
			else
				printf("	兄弟节点为： %d %s\n", temp->data.key, temp->data.others);
			getchar(); getchar();
			break;
		}
		case 12://InsertNode
		{
			KeyType e;
			int LR;
			TElemType c;
			printf("请输入待插入结点关键字：");
			scanf("%d", &e);
			printf("请输入插入方式LR=");
			scanf("%d", &LR);
			printf("请输入插入的结点信息：");
			scanf("%d %s", &c.key, c.others);
			sta = InsertNode(Lists.elem[n].L, e, LR, c);
			if (sta == ERROR)
				printf_red("	插入失败!\n");
			else
				printf_green("	插入成功\n");
			getchar(); getchar();
			break;
		}
		case 13://DeleteNode
		{
			KeyType e;
			printf("请输入您要删除的结点的关键字：");
			scanf("%d", &e);
			sta = DeleteNode(Lists.elem[n].L,e);
			if (sta == ERROR)
				printf_red("	删除失败!\n");
			else
				printf_green("	删除成功!\n");
			getchar(); getchar();
			break;
		}
		case 14://PreOrderTraverse
		{
            if (!Lists.elem[n].L)
                printf_red("二叉树为空！");
            PreOrderTraverse(Lists.elem[n].L);
			getchar(); getchar();
			break;
		}
		case 15://InOrderTraverse
            if (!Lists.elem[n].L)
                printf_red("二叉树为空！");
            InOrderTraverse(Lists.elem[n].L);
			getchar(); getchar();
			break;
		case 16://PostOrderTraverse
            if (!Lists.elem[n].L)
                printf_red("二叉树为空！");
            PostOrderTraverse(Lists.elem[n].L);
			getchar(); getchar();
			break;
		case 17://LevelOrderTraverse
            if (!Lists.elem[n].L)
                printf_red("二叉树为空！");
			LevelOrderTraverse(Lists.elem[n].L);
			getchar(); getchar();
			break;
		case 18://maxPathSum
			sta = maxPathSum(Lists.elem[n].L);
			if (sta == 0)
				printf_red("    二叉树不存在!\n");
			else
				printf("    最大路径和为%d\n",sta);
			getchar(); getchar();
			break;
		case 19://LowestCommonAncestor
		{
			BiTree temp;
			KeyType pk, qk;
			printf("请输入查找的两个结点的关键字：");
			scanf("%d %d", &pk, &qk);
			temp = LowestCommonAncestor(Lists.elem[n].L, pk, qk);
			if (temp == NULL)
				printf_red("不存在！\n");
			else
				printf("该节点为：%d %s\n", temp->data.key, temp->data.others);
			getchar(); getchar();
			break;
		}
		case 20://invertTree
			Lists.elem[n].L = invertTree(Lists.elem[n].L);
			printf_green("转置成功！\n");
			getchar(); getchar();
			break;
		case 21://SaveBiTree
		{
			char filename[100] = { 0 };
            char name[20] = { 0 };
			printf("请输入要写入的文件：");
			scanf("%s", name);
            sprintf(filename, "%s%s%s", "./", name, ".txt");
			sta = SaveBiTree(Lists.elem[n].L, filename);
			if (sta == OK)
				printf_green("写入成功！\n");
            else
                printf_red("写入失败！\n");
			getchar(); getchar();
			break;
		}
		case 22://LoadBiTree
		{
            TElemType definition[1000] = { 0 };
			char filename[100] = { 0 };
            char name[20] = { 0 };
			printf("请输入要读的文件：");
			scanf("%s", name);
            sprintf(filename, "%s%s%s", "./", name, ".txt");
            FILE* file = fopen(filename, "r");
            int j = 0;
            while (fscanf(file, "%d %s\n", &definition[j].key, &definition[j].others) != EOF)
            {
                j++;
            }
            i = -1;
			sta = LoadBiTree(Lists.elem[n].L, definition);
			if (sta == OK)
				printf_green("读入成功！\n");
            else
                printf_red("写入失败！\n");
			getchar(); getchar();
			break;
		}
		case 23:
		{
			TElemType definition[9999];
			int i = 0;
			do {
				scanf("%d%s", &definition[i].key, definition[i].others);
			} while (definition[i++].key != -1);
			sta = CreateBiTree(T, definition);
			if (sta == OK)
				printf("创建成功！\n");
			else
				printf("创建失败！\n");
		}
		case 0://exit
			break;
		}//end of switch
	}//end of while
	printf("欢迎下次再使用本系统！\n");
}//end of main()
/*--------page 23 on textbook --------------------*/


