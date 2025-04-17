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
		printf("    ��ѡ����Ĳ���[0~23](��ǰ����������Ϊ%d[1~%d]):", n + 1, Lists.length);
		scanf("%d", &op);
		switch (op)
		{
		case 1://AddList
			sta = AddList(Lists);
			if (sta == ERROR)
				printf_red("	���ʧ�ܣ������������Ѵ����ޣ�\n");
			else
				printf_green("	��ӳɹ���\n");
			getchar(); getchar();
			break;
		case 2://ShiftList
			sta = ShiftList();
			if (sta == ERROR)
				printf_red("	�ö����������ڣ�\n");
			else
				printf_green("	ת���ɹ���\n");
			getchar(); getchar();
			break;
		case 3://RemoveList
			sta = RemoveList(Lists);
			if (sta == OK)
				printf_green("	ɾ���ɹ���\n");
			else
				printf_red("	δ�ҵ��ö�����!\n");
			getchar(); getchar();
			break;
		case 4://LocateList
			sta = LocateList(Lists);
			if (sta == 0)
				printf_red("	δ�ҵ��ö�����!\n");
			else
				printf("	���ǵ�%d��������\n", sta);
			getchar(); getchar();
			break;
		case 5://DestroyBiTree
            if(Lists.elem[n].L==NULL)
                printf_red("	�����������ڣ�\n");
            else
            {
			    DestroyBiTree(Lists.elem[n].L);
				printf_green("	������������!\n");
            }
			getchar(); getchar();
			break;
		case 6://ClearBiTree
            if (Lists.elem[n].L == NULL)
                printf_red("	�����������ڣ�\n");
            else
            {
                ClearBiTree(Lists.elem[n].L);
                printf_green("	�����������!\n");
            }
            getchar(); getchar();
            break;
        case 7://BiTreeEmpty
			sta = BiTreeEmpty(Lists.elem[n].L);
			if (sta == OK)
				printf_green("    ������Ϊ�գ�\n");
			else
				printf_yellow("    ��������Ϊ�գ�\n");
			getchar(); getchar();
			break;
		case 8://BiTreeDepth
			sta = BiTreeDepth(Lists.elem[n].L);
			if (sta == 0)
				printf_red("	������������!\n");
			else
				printf("	���������Ϊ %d", sta);
			getchar(); getchar();
			break;
		case 9://LocateNode
		{
            BiTree temp = NULL;
			KeyType e;
			printf("��Ҫ���ҵĹؼ���Ϊ��");
			scanf("%d", &e);
			temp = LocateNode(Lists.elem[n].L,e);
			if (temp == NULL)
				printf_red("	������������!\n");
			else
				printf("%d %s\n", temp->data.key, temp->data.others);
			getchar(); getchar();
			break;
		}
		case 10://Assign
			sta = Assign(Lists.elem[n].L);
			if (sta == ERROR)
				printf_red("	�滻ʧ��!\n");
			else
				printf_green("	�滻�ɹ���\n");
			getchar(); getchar();
			break;
		case 11://GetSibling
		{
			BiTree temp;
			KeyType e;
			printf("��Ҫ���ҵĹؼ���Ϊ��");
			scanf("%d", &e);
			temp = GetSibling(Lists.elem[n].L,e);
			if (temp == NULL)
				printf_red("	��㲻����!\n");
			else
				printf("	�ֵܽڵ�Ϊ�� %d %s\n", temp->data.key, temp->data.others);
			getchar(); getchar();
			break;
		}
		case 12://InsertNode
		{
			KeyType e;
			int LR;
			TElemType c;
			printf("�������������ؼ��֣�");
			scanf("%d", &e);
			printf("��������뷽ʽLR=");
			scanf("%d", &LR);
			printf("���������Ľ����Ϣ��");
			scanf("%d %s", &c.key, c.others);
			sta = InsertNode(Lists.elem[n].L, e, LR, c);
			if (sta == ERROR)
				printf_red("	����ʧ��!\n");
			else
				printf_green("	����ɹ�\n");
			getchar(); getchar();
			break;
		}
		case 13://DeleteNode
		{
			KeyType e;
			printf("��������Ҫɾ���Ľ��Ĺؼ��֣�");
			scanf("%d", &e);
			sta = DeleteNode(Lists.elem[n].L,e);
			if (sta == ERROR)
				printf_red("	ɾ��ʧ��!\n");
			else
				printf_green("	ɾ���ɹ�!\n");
			getchar(); getchar();
			break;
		}
		case 14://PreOrderTraverse
		{
            if (!Lists.elem[n].L)
                printf_red("������Ϊ�գ�");
            PreOrderTraverse(Lists.elem[n].L);
			getchar(); getchar();
			break;
		}
		case 15://InOrderTraverse
            if (!Lists.elem[n].L)
                printf_red("������Ϊ�գ�");
            InOrderTraverse(Lists.elem[n].L);
			getchar(); getchar();
			break;
		case 16://PostOrderTraverse
            if (!Lists.elem[n].L)
                printf_red("������Ϊ�գ�");
            PostOrderTraverse(Lists.elem[n].L);
			getchar(); getchar();
			break;
		case 17://LevelOrderTraverse
            if (!Lists.elem[n].L)
                printf_red("������Ϊ�գ�");
			LevelOrderTraverse(Lists.elem[n].L);
			getchar(); getchar();
			break;
		case 18://maxPathSum
			sta = maxPathSum(Lists.elem[n].L);
			if (sta == 0)
				printf_red("    ������������!\n");
			else
				printf("    ���·����Ϊ%d\n",sta);
			getchar(); getchar();
			break;
		case 19://LowestCommonAncestor
		{
			BiTree temp;
			KeyType pk, qk;
			printf("��������ҵ��������Ĺؼ��֣�");
			scanf("%d %d", &pk, &qk);
			temp = LowestCommonAncestor(Lists.elem[n].L, pk, qk);
			if (temp == NULL)
				printf_red("�����ڣ�\n");
			else
				printf("�ýڵ�Ϊ��%d %s\n", temp->data.key, temp->data.others);
			getchar(); getchar();
			break;
		}
		case 20://invertTree
			Lists.elem[n].L = invertTree(Lists.elem[n].L);
			printf_green("ת�óɹ���\n");
			getchar(); getchar();
			break;
		case 21://SaveBiTree
		{
			char filename[100] = { 0 };
            char name[20] = { 0 };
			printf("������Ҫд����ļ���");
			scanf("%s", name);
            sprintf(filename, "%s%s%s", "./", name, ".txt");
			sta = SaveBiTree(Lists.elem[n].L, filename);
			if (sta == OK)
				printf_green("д��ɹ���\n");
            else
                printf_red("д��ʧ�ܣ�\n");
			getchar(); getchar();
			break;
		}
		case 22://LoadBiTree
		{
            TElemType definition[1000] = { 0 };
			char filename[100] = { 0 };
            char name[20] = { 0 };
			printf("������Ҫ�����ļ���");
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
				printf_green("����ɹ���\n");
            else
                printf_red("д��ʧ�ܣ�\n");
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
				printf("�����ɹ���\n");
			else
				printf("����ʧ�ܣ�\n");
		}
		case 0://exit
			break;
		}//end of switch
	}//end of while
	printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
}//end of main()
/*--------page 23 on textbook --------------------*/


