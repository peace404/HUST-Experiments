#define _CRT_SECURE_NO_WARNINGS

#include"def.h"
LISTS Lists;
int n;
#include"fun.h"
status sta;

int main()
{
	int op = 1;
	Lists.length = 0;

	while (op)
	{
		system("cls");	printf("\n\n");
		printf("          Menu for Linear Table On Sequence Structure \n");
		printf("-----------------------------------------------------------\n");
		printf("    	  1. AddList                     2. ShiftList\n");
		printf("    	  3. RemoveList                  4. LocateList\n");
		printf("    	  5. CreateCraph                 6. DestroyGraph\n");
		printf("    	  7. LocateVex                   8. PutVex\n");
		printf("    	  9. FirstAdjVex                 10. NextAdjVex\n");
		printf("    	  11. InsertVex                  12. DeleteVex\n");
		printf("    	  13. InsertArc                  14. DeleteArc\n");
		printf("    	  15. DFSTraverse                16. BFSTraverse\n");
		printf("    	  17. VerticesSetLessThanK       18. ShortestPathLength\n");
		printf("    	  19. SaveGraph                  20. LoadGraph\n");		
		printf("    	  0. exit\n");
		printf("-------------------------------------------------\n");
		printf("    请选择你的操作[0~20](当前操作图为%d[1~%d]):", n + 1, Lists.length);
		scanf("%d", &op);
		switch (op)
		{
		case 1://AddList
			sta = AddList(Lists);
			if (sta == ERROR)
				printf_red("	添加失败，图数量已达上限！\n");
			else
				printf_green("	添加成功！\n");
			getchar(); getchar();
			break;
		case 2://ShiftList
			sta = ShiftList();
			if (sta == ERROR)
				printf_red("	该图不存在！\n");
			else
				printf_green("	转换成功！\n");
			getchar(); getchar();
			break;
		case 3://RemoveList
			sta = RemoveList(Lists);
			if (sta == OK)
				printf_green("	删除成功！\n");
			else
				printf_red("	未找到该图!\n");
			getchar(); getchar();
			break;
		case 4://LocateList
			sta = LocateList(Lists);
			if (sta == 0)
				printf_red("	未找到该图!\n");
			else
				printf("	这是第%d个图\n", sta);
			getchar(); getchar();
			break;
		case 5://CreateCraph
		{
			sta=CreateCraph(Lists.elem[n].L);
			if (sta == OK)
				printf_green("	创建成功！\n");
			getchar(); getchar();
			break;
		}
		case 6://DestroyGraph
			if (!Lists.elem[n].L.vertices)
				printf_red("	图不存在！\n");
			else
			{
				DestroyGraph(Lists.elem[n].L);
				printf_green("	图已销毁!\n");
			}
			getchar(); getchar();
			break;
		case 7://LocateVex
		{
			KeyType u;
			printf("	请输入要查找的顶点关键字：\n");
			scanf("%d", &u);
			sta=LocateVex(Lists.elem[n].L,u);
			if (sta == -1)
				printf_red("	顶点不存在！\n");
			else
				printf("	这是第%d个顶点\n",sta);
			getchar(); getchar();
			break;
		}
		case 8://PutVex
		{
			KeyType u;
			VertexType value;
			printf("	请输入要操作的顶点关键字：\n");
			scanf("%d", &u);
			printf("	请输入要赋的值：\n");
			scanf("%d %s", &value.key, value.others);
			sta = PutVex(Lists.elem[n].L,u,value);
			if (sta == OK)
				printf_green("    赋值成功！\n");
			else
				printf_red("    赋值失败！\n");
			getchar(); getchar();
			break;

		}
		case 9://FirstAdjVex
		{
			KeyType u;
			printf("	请输入要查找的顶点关键字：\n");
			scanf("%d", &u);
			sta = FirstAdjVex(Lists.elem[n].L,u);
			if (sta == -1)
				printf_red("	不存在!\n");
			else
				printf("	第一个邻接顶点位序为 %d", sta);
			getchar(); getchar();
			break;

		}
		case 10://NextAdjVex
		{
			KeyType v,w;
			printf("	请输入要查找的两个顶点关键字：\n");
			scanf("%d %d", &v, &w);
			sta = NextAdjVex(Lists.elem[n].L, v, w);
			if (sta == -1)
				printf_red("	不存在!\n");
			else
				printf("	下一邻接点的位序为%d\n",sta);
			getchar(); getchar();
			break;
		}
		case 11://InsertVex
		{
			VertexType v;
			printf("	请输入要增加的顶点信息：");
			scanf("%d %s", &v.key, v.others);
			sta = InsertVex(Lists.elem[n].L,v);
			if (sta == ERROR)
				printf_red("	增加失败!\n");
			else
				printf_green("	增加成功！\n");
			getchar(); getchar();
			break;
		}
		case 12://DeleteVex
		{
			KeyType v;
			printf("	请输入要删除的关键字：");
			scanf("%d", &v);
			sta = DeleteVex(Lists.elem[n].L, v);
			if (sta == ERROR)
				printf_red("	删除失败!\n");
			else
				printf_green("	删除成功！\n");
			getchar(); getchar();
			break;
		}
		case 13://InsertArc
		{
			KeyType v,w;
			printf("	请输入要插入的弧的两个关键字：");
			scanf("%d %d", &v, &w);
			sta = InsertArc(Lists.elem[n].L, v,w);
			if (sta == ERROR)
				printf_red("	插入失败!\n");
			else
				printf_green("	插入成功！\n");
			getchar(); getchar();
			break;
		}
		case 14://DeleteArc
		{
			KeyType v, w;
			printf("	请输入要删除的弧的两个关键字：");
			scanf("%d %d", &v, &w);
			sta = DeleteArc(Lists.elem[n].L, v, w);
			if (sta == ERROR)
				printf_red("	删除失败!\n");
			else
				printf_green("	删除成功！\n");
			getchar(); getchar();
			break;
		}
		case 15://DFSTraverse
		{	
			if (!Lists.elem[n].L.vexnum)
				printf_red("	图为空！");
			DFSTraverse(Lists.elem[n].L, visit);
			getchar(); getchar();
			break;
		}
		case 16://BFSTraverse
			if (!Lists.elem[n].L.vexnum)
				printf_red("	图为空！");
			BFSTraverse(Lists.elem[n].L,visit);
			getchar(); getchar();
			break;
		case 17://VerticesSetLessThanK
		{
			int v, k;
			printf("	请输入开始的顶点关键字：");
			scanf("%d", &v);
			printf("	请输入距离：");
			scanf("%d", &k);
			VerticesSetLessThanK(Lists.elem[n].L, v, k, visit);
			getchar(); getchar();
			break;
		}
		case 18://ShortestPathLength
		{
			int v, w;
			printf("	请输入要查找的两个顶点的关键字：");
			scanf("%d %d", &v, &w);
			if (ShortestPathLength(Lists.elem[n].L, v, w) == ERROR)
				printf_red("	两顶点不相连！");
		}
			getchar(); getchar();
			break;
		case 19://SaveGraph
		{
			char filename[100] = { 0 };
			char name[20] = { 0 };
			printf("	请输入要写入的文件：");
			scanf("%s", name);
			sprintf(filename, "%s%s%s", "./", name, ".txt");
			sta = SaveGraph(Lists.elem[n].L, filename);
			if (sta == OK)
				printf_green("	写入成功！\n");
			else
				printf_red("	写入失败！\n");
			getchar(); getchar();
			break;
		}
		case 20://LoadGraph
		{
			char filename[100] = { 0 };
			char name[20] = { 0 };
			printf("	请输入要读的文件：");
			scanf("%s", name);
			sprintf(filename, "%s%s%s", "./", name, ".txt");
			sta = LoadGraph(Lists.elem[n].L, filename);
			if (sta == OK)
				printf_green("	读入成功！\n");
			else
				printf_red("	写入失败！\n");
			getchar(); getchar();
			break;
		}
		case 0://exit
			break;
		}//end of switch
	}//end of while
	printf("	欢迎下次再使用本系统！\n");
}//end of main()
