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
		printf("    ��ѡ����Ĳ���[0~20](��ǰ����ͼΪ%d[1~%d]):", n + 1, Lists.length);
		scanf("%d", &op);
		switch (op)
		{
		case 1://AddList
			sta = AddList(Lists);
			if (sta == ERROR)
				printf_red("	���ʧ�ܣ�ͼ�����Ѵ����ޣ�\n");
			else
				printf_green("	��ӳɹ���\n");
			getchar(); getchar();
			break;
		case 2://ShiftList
			sta = ShiftList();
			if (sta == ERROR)
				printf_red("	��ͼ�����ڣ�\n");
			else
				printf_green("	ת���ɹ���\n");
			getchar(); getchar();
			break;
		case 3://RemoveList
			sta = RemoveList(Lists);
			if (sta == OK)
				printf_green("	ɾ���ɹ���\n");
			else
				printf_red("	δ�ҵ���ͼ!\n");
			getchar(); getchar();
			break;
		case 4://LocateList
			sta = LocateList(Lists);
			if (sta == 0)
				printf_red("	δ�ҵ���ͼ!\n");
			else
				printf("	���ǵ�%d��ͼ\n", sta);
			getchar(); getchar();
			break;
		case 5://CreateCraph
		{
			sta=CreateCraph(Lists.elem[n].L);
			if (sta == OK)
				printf_green("	�����ɹ���\n");
			getchar(); getchar();
			break;
		}
		case 6://DestroyGraph
			if (!Lists.elem[n].L.vertices)
				printf_red("	ͼ�����ڣ�\n");
			else
			{
				DestroyGraph(Lists.elem[n].L);
				printf_green("	ͼ������!\n");
			}
			getchar(); getchar();
			break;
		case 7://LocateVex
		{
			KeyType u;
			printf("	������Ҫ���ҵĶ���ؼ��֣�\n");
			scanf("%d", &u);
			sta=LocateVex(Lists.elem[n].L,u);
			if (sta == -1)
				printf_red("	���㲻���ڣ�\n");
			else
				printf("	���ǵ�%d������\n",sta);
			getchar(); getchar();
			break;
		}
		case 8://PutVex
		{
			KeyType u;
			VertexType value;
			printf("	������Ҫ�����Ķ���ؼ��֣�\n");
			scanf("%d", &u);
			printf("	������Ҫ����ֵ��\n");
			scanf("%d %s", &value.key, value.others);
			sta = PutVex(Lists.elem[n].L,u,value);
			if (sta == OK)
				printf_green("    ��ֵ�ɹ���\n");
			else
				printf_red("    ��ֵʧ�ܣ�\n");
			getchar(); getchar();
			break;

		}
		case 9://FirstAdjVex
		{
			KeyType u;
			printf("	������Ҫ���ҵĶ���ؼ��֣�\n");
			scanf("%d", &u);
			sta = FirstAdjVex(Lists.elem[n].L,u);
			if (sta == -1)
				printf_red("	������!\n");
			else
				printf("	��һ���ڽӶ���λ��Ϊ %d", sta);
			getchar(); getchar();
			break;

		}
		case 10://NextAdjVex
		{
			KeyType v,w;
			printf("	������Ҫ���ҵ���������ؼ��֣�\n");
			scanf("%d %d", &v, &w);
			sta = NextAdjVex(Lists.elem[n].L, v, w);
			if (sta == -1)
				printf_red("	������!\n");
			else
				printf("	��һ�ڽӵ��λ��Ϊ%d\n",sta);
			getchar(); getchar();
			break;
		}
		case 11://InsertVex
		{
			VertexType v;
			printf("	������Ҫ���ӵĶ�����Ϣ��");
			scanf("%d %s", &v.key, v.others);
			sta = InsertVex(Lists.elem[n].L,v);
			if (sta == ERROR)
				printf_red("	����ʧ��!\n");
			else
				printf_green("	���ӳɹ���\n");
			getchar(); getchar();
			break;
		}
		case 12://DeleteVex
		{
			KeyType v;
			printf("	������Ҫɾ���Ĺؼ��֣�");
			scanf("%d", &v);
			sta = DeleteVex(Lists.elem[n].L, v);
			if (sta == ERROR)
				printf_red("	ɾ��ʧ��!\n");
			else
				printf_green("	ɾ���ɹ���\n");
			getchar(); getchar();
			break;
		}
		case 13://InsertArc
		{
			KeyType v,w;
			printf("	������Ҫ����Ļ��������ؼ��֣�");
			scanf("%d %d", &v, &w);
			sta = InsertArc(Lists.elem[n].L, v,w);
			if (sta == ERROR)
				printf_red("	����ʧ��!\n");
			else
				printf_green("	����ɹ���\n");
			getchar(); getchar();
			break;
		}
		case 14://DeleteArc
		{
			KeyType v, w;
			printf("	������Ҫɾ���Ļ��������ؼ��֣�");
			scanf("%d %d", &v, &w);
			sta = DeleteArc(Lists.elem[n].L, v, w);
			if (sta == ERROR)
				printf_red("	ɾ��ʧ��!\n");
			else
				printf_green("	ɾ���ɹ���\n");
			getchar(); getchar();
			break;
		}
		case 15://DFSTraverse
		{	
			if (!Lists.elem[n].L.vexnum)
				printf_red("	ͼΪ�գ�");
			DFSTraverse(Lists.elem[n].L, visit);
			getchar(); getchar();
			break;
		}
		case 16://BFSTraverse
			if (!Lists.elem[n].L.vexnum)
				printf_red("	ͼΪ�գ�");
			BFSTraverse(Lists.elem[n].L,visit);
			getchar(); getchar();
			break;
		case 17://VerticesSetLessThanK
		{
			int v, k;
			printf("	�����뿪ʼ�Ķ���ؼ��֣�");
			scanf("%d", &v);
			printf("	��������룺");
			scanf("%d", &k);
			VerticesSetLessThanK(Lists.elem[n].L, v, k, visit);
			getchar(); getchar();
			break;
		}
		case 18://ShortestPathLength
		{
			int v, w;
			printf("	������Ҫ���ҵ���������Ĺؼ��֣�");
			scanf("%d %d", &v, &w);
			if (ShortestPathLength(Lists.elem[n].L, v, w) == ERROR)
				printf_red("	�����㲻������");
		}
			getchar(); getchar();
			break;
		case 19://SaveGraph
		{
			char filename[100] = { 0 };
			char name[20] = { 0 };
			printf("	������Ҫд����ļ���");
			scanf("%s", name);
			sprintf(filename, "%s%s%s", "./", name, ".txt");
			sta = SaveGraph(Lists.elem[n].L, filename);
			if (sta == OK)
				printf_green("	д��ɹ���\n");
			else
				printf_red("	д��ʧ�ܣ�\n");
			getchar(); getchar();
			break;
		}
		case 20://LoadGraph
		{
			char filename[100] = { 0 };
			char name[20] = { 0 };
			printf("	������Ҫ�����ļ���");
			scanf("%s", name);
			sprintf(filename, "%s%s%s", "./", name, ".txt");
			sta = LoadGraph(Lists.elem[n].L, filename);
			if (sta == OK)
				printf_green("	����ɹ���\n");
			else
				printf_red("	д��ʧ�ܣ�\n");
			getchar(); getchar();
			break;
		}
		case 0://exit
			break;
		}//end of switch
	}//end of while
	printf("	��ӭ�´���ʹ�ñ�ϵͳ��\n");
}//end of main()
