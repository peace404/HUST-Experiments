#define _CRT_SECURE_NO_WARNINGS

#include "hanidoku.h"
#include "solver.h"

//位置转换
int x[9][9] = { 11,12,13,14,15,0,0,0,0,21,22,23,24,25,26,0,0,0,31,32,33,34,35,36,37,0,0,41,42,43,44,45,46,47,48,0,51,52,53,54,55,56,57,58,59,61,62,63,64,65,66,67,68,0,71,72,73,74,75,76,77,0,0,81,82,83,84,85,86,0,0,0,91,92,93,94,95,0,0,0,0 };
int y[9][9] = { 11,21,31,41,51,0,0,0,0,12,22,32,42,52,61,0,0,0,13,23,33,43,53,62,71,0,0,14,24,34,44,54,63,72,81,0,15,25,35,45,55,64,73,82,91,26,36,46,56,65,74,83,92,0,37,47,57,66,75,84,93,0,0,48,58,67,76,85,94,0,0,0,59,68,77,86,95,0,0,0,0 };
int z[9][9] = { 51,61,71,81,91,0,0,0,0,41,52,62,72,82,92,0,0,0,31,42,53,63,73,83,93,0,0,21,32,43,54,64,74,84,94,0,11,22,33,44,55,65,75,85,95,12,23,34,45,56,66,76,86,0,13,24,35,46,57,67,77,0,0,14,25,36,47,58,68,0,0,0,15,26,37,48,59,0,0,0,0 };
int current[9][9];
int sw[96] = { 0,0,0,0,0,0,0,0,0,0,0,0,1,2,3,4,0,0,0,0,0,5,6,7,8,9,10,0,0,0,0,11,12,13,14,15,16,17,0,0,0,18,19,20,21,22,23,24,25,0,0,26,27,28,29,30,31,32,33,34,0,35,36,37,38,39,40,41,42,0,0,43,44,45,46,47,48,49,0,0,0,50,51,52,53,54,55,0,0,0,0,56,57,58,59,60 };


void write_sudoku()//打印基本cnf文件
{
    FILE* fp;
    fp = fopen(".sudoku_rule.cnf", "w");
    fprintf(fp, "p cnf 549 7474\n");
    //每个格子只有一个值为真
    for (int n = 0; n < 61; n++)
    {
        for (int k = 1; k < 9; k++)
        {
            for (int kk = k + 1; kk <= 9; kk++)
            {
                fprintf(fp, "-%d -%d 0\n", n * 9 + k, n * 9 + kk);
            }
        }
    }
    //每个格子有一个值为真
    for (int n = 0; n < 61; n++)
    {
        for (int k = 1; k <= 9; k++)
        {
            fprintf(fp, "%d ", n * 9 + k);
        }
        fprintf(fp, "0\n");
    }
    //连续性约束
    for (int i = 0; i < 3; i++)
    {
        switch (i)
        {
        case 0:
            for (int i = 0; i < 9; i++)
            {
                for (int j = 0; j < 9; j++)
                    current[i][j] = x[i][j];
            }
            break;
        case 1:
            for (int i = 0; i < 9; i++)
            {
                for (int j = 0; j < 9; j++)
                    current[i][j] = y[i][j];
            }
            break;
        case 2:
            for (int i = 0; i < 9; i++)
            {
                for (int j = 0; j < 9; j++)
                    current[i][j] = z[i][j];
            }
            break;
        }
        for (int i = 0; i < 9; i++)
        {
            if (abs(i - 4) == 4)//1&9
            {
                //必定有一个五
                for (int j = 0; j < 5; j++)
                {
                    fprintf(fp, "%d ", sw[current[i][j]] * 9 + 5);
                }
                fprintf(fp, "0\n");
                //一条线上的数字不重复
                for (int k = 1; k <= 9; k++)
                {
                    for (int j = 0; j < 4; j++)
                    {
                        for (int jj = j + 1; jj < 5; jj++)
                        {
                            fprintf(fp, "-%d -%d 0\n", sw[current[i][j]] * 9 + k, sw[current[i][jj]] * 9 + k);
                        }
                    }
                }
                //选填方案
                for (int k = 0; k < 11; k++)
                {
                    int kk[11][2] = { 3,6,3,7,3,8,4,6,4,7,4,8,2,7,3,7,4,7,1,6,4,9 };
                    for (int j = 0; j < 5; j++)
                    {
                        fprintf(fp, "%d %d ", sw[current[i][j]] * 9 + kk[k][0], sw[current[i][j]] * 9 + kk[k][1]);
                    }
                    fprintf(fp, "0\n");
                }
            }
            if (abs(i - 4) == 3)//2&8
            {
                for (int k = 4; k <= 6; k++)
                {
                    for (int j = 0; j < 6; j++)
                    {
                        fprintf(fp, "%d ", sw[current[i][j]] * 9 + k);//必有一个
                    }
                    fprintf(fp, "0\n");
                }
                for (int k = 1; k <= 9; k++)
                {
                    for (int j = 0; j < 5; j++)
                    {
                        for (int jj = j + 1; jj < 6; jj++)
                        {
                            fprintf(fp, "-%d -%d 0\n", sw[current[i][j]] * 9 + k, sw[current[i][jj]] * 9 + k);
                        }
                    }
                }
                for (int k = 0; k < 6; k++)
                {
                    int kk[6][2] = { 2,7,3,7,2,8,3,8,1,7,3,9 };
                    for (int j = 0; j < 6; j++)
                    {
                        fprintf(fp, "%d %d ", sw[current[i][j]] * 9 + kk[k][0], sw[current[i][j]] * 9 + kk[k][1]);
                    }
                    fprintf(fp, "0\n");
                }
            }
            if (abs(i - 4) == 2)//3&7
            {
                for (int k = 3; k <= 7; k++)
                {
                    for (int j = 0; j < 7; j++)
                    {
                        fprintf(fp, "%d ", sw[current[i][j]] * 9 + k);
                    }
                    fprintf(fp, "0\n");
                }
                for (int k = 1; k <= 9; k++)
                {
                    for (int j = 0; j < 6; j++)
                    {
                        for (int jj = j + 1; jj < 7; jj++)
                        {
                            fprintf(fp, "-%d -%d 0\n", sw[current[i][j]] * 9 + k, sw[current[i][jj]] * 9 + k);
                        }
                    }
                }
                for (int k = 0; k < 3; k++)
                {
                    int kk[3][2] = { 1,8,2,8,2,9 };
                    for (int j = 0; j < 7; j++)
                    {
                        fprintf(fp, "%d %d ", sw[current[i][j]] * 9 + kk[k][0], sw[current[i][j]] * 9 + kk[k][1]);
                    }
                    fprintf(fp, "0\n");
                }
            }
            if (abs(i - 4) == 1)//4&6
            {
                for (int k = 2; k <= 8; k++)
                {
                    for (int j = 0; j < 8; j++)
                    {
                        fprintf(fp, "%d ", sw[current[i][j]] * 9 + k);
                    }
                    fprintf(fp, "0\n");
                }
                for (int k = 1; k <= 9; k++)
                {
                    for (int j = 0; j < 7; j++)
                    {
                        for (int jj = j + 1; jj < 8; jj++)
                        {
                            fprintf(fp, "-%d -%d 0\n", sw[current[i][j]] * 9 + k, sw[current[i][jj]] * 9 + k);
                        }
                    }
                }
                int kk[1][2] = { 1,9 };
                for (int j = 0; j < 8; j++)
                {
                    fprintf(fp, "%d %d ", sw[current[i][j]] * 9 + kk[0][0], sw[current[i][j]] * 9 + kk[0][1]);
                }
                fprintf(fp, "0\n");
            }
            if (abs(i - 4) == 0)//5
            {
                for (int k = 1; k <= 9; k++)
                {
                    for (int j = 0; j < 9; j++)
                    {
                        fprintf(fp, "%d ", sw[current[i][j]] * 9 + k);
                    }
                    fprintf(fp, "0\n");
                    for (int j = 0; j < 8; j++)
                    {
                        for (int jj = j + 1; jj < 9; jj++)
                        {
                            fprintf(fp, "-%d -%d 0\n", sw[current[i][j]] * 9 + k, sw[current[i][jj]] * 9 + k);
                        }
                    }
                }
            }
        }
    }
    fclose(fp);
}
void print_play_menu()//menu部分
{
    printf("\n\n");
    printf("               Hanisudoku                        \n");
    printf("-----------------------------------------------  \n");
    printf("      1.  Play         2. Check                  \n");
    printf("      0.  Back                                   \n");
    printf("-----------------------------------------------  \n");
    printf("              请选择功能[0--3]:                   \n");
}
void play(const char* filename)//play部分
{
    int known[96] = { 0 };
    char file_in[256];
    sprintf(file_in, "%s.txt", filename);
    int op = 1;
    while (op)
    {
        print_play_menu();
        print_hanisudoku(file_in, known);
        scanf("%d", &op);
        switch (op)
        {
        case 1:
        {
            char c = 'y';
            while (c == 'y')
            {
                printf("请输入您要填入的位置与数字(形式为\"i j k\"i(行)j(列)k(数字)：");
                int i, j, k;
                scanf("%d %d %d", &i, &j, &k);
                system("cls");
                known[i * 10 + j] = k;
                print_hanisudoku(file_in, known);
                printf("是否继续？（y/n）: ");
                getchar();
                scanf("%c", &c);
            }
            system("cls");
            break;
        }
        case 2:
        {
            int knowncpy[96] = { 0 };
            for (int i = 0; i < 96; i++)
            {
                knowncpy[i] = known[i];
            }
            if (solve_hanidoku(knowncpy, filename))
            {
                print_hanisudoku(file_in, knowncpy);
                printf("答案已写在文件%s.res中\n", filename);
            }
            else
            {
                printf("无解\n");
            }
            system("pause");
            system("cls");
            break;
        }
        case 0:
            system("cls");
            return;
        default:
            printf("请输入数字[0--2]:");
            scanf("%d", &op);
        }
    }

}

void print_hanisudoku(const char* filename, int* known)//打印蜂窝数独
{
    FILE* fp = fopen(filename, "r");
    int n;
    while (fscanf(fp, "%d", &n) != EOF)
    {
        known[n / 10] = n % 10;
    }
    printf("\n\n");
    for (int i = 0; i < 5; i++)
    {
        for (int k = 0; k < (4 - i) * 2; k++)
            printf(" ");
        for (int k = 0; k < 9 - (4 - i); k++)
            printf(" / \\");
        printf("\n");
        for (int k = 0; k < (4 - i) * 2; k++)
            printf(" ");
        for (int k = 0; k < 9 - (4 - i); k++)
            printf("| %c ", known[(i + 1) * 10 + k + 1] ? known[(i + 1) * 10 + k + 1] + '0' : '.');
        printf("|\n");
    }
    for (int i = 5; i < 9; i++)
    {
        for (int k = 0; k < (i - 4) * 2 - 1; k++)
            printf(" ");
        for (int k = 0; k < 9 - (i - 4) + 1; k++)
            printf("\\ / ");
        printf("\n");
        for (int k = 0; k < (i - 4) * 2; k++)
            printf(" ");
        for (int k = 0; k < 9 - (i - 4); k++)
            printf("| %c ", known[(i + 1) * 10 + k + 1] ? known[(i + 1) * 10 + k + 1] + '0' : '.');
        printf("|\n");
    }
    for (int j = 0; j < 9; j++)
        printf(" ");
    for (int j = 0; j < 5; j++)
        printf("\\ / ");
    printf("\n");
    return;
}

void choose_level()//选择难度
{
    int op = 1;
    while (op)
    {
        printf("\n\n");
        printf("               Hanisudoku                        \n");
        printf("-----------------------------------------------  \n");
        printf("      1.  Easy    2. Mediun    3.Hard            \n");
        printf("      0.  Back                                   \n");
        printf("-----------------------------------------------  \n");
        printf("              请选择难度[0--3]:                   \n");
        scanf("%d", &op);
        system("cls");
        char filename[256] = { 0 };
        switch (op)
        {
        case 1:
        {
            printf("请选择数独[1-8]: ");
            char c;
            scanf("%1s", &c);
            sprintf(filename, ".\\hanisudoku\\easy\\%c", c);
            break;
        }
        case 2:
        {
            printf("请选择数独[1-8]: ");
            char c;
            scanf("%1s", &c);
            sprintf(filename, ".\\hanisudoku\\medium\\%c", c);
            break;
        }
        case 3:
        {
            printf("请选择数独[1-8]: ");
            char c;
            scanf("%1s", &c);
            sprintf(filename, ".\\hanisudoku\\hard\\%c", c);
            break;
        }
        case 0:
            return;
        default:
            printf("请输入数字[0--3]:");
            scanf("%d", &op);
        }
        play(filename);
    }
}

void hanidoku()//数独界面
{
    int op = 1;
    while (op)
    {
        printf("\n\n");
        printf("               Hanisudoku                        \n");
        printf("-----------------------------------------------  \n");
        printf("      1.  Choose hanisudoku                      \n");
        printf("      0.  Back                                   \n");
        printf("-----------------------------------------------  \n");
        printf("              请选择功能[0--2]:");
        scanf("%d", &op);
        system("cls");
        switch (op)
        {
        case 1:
        {
            choose_level();
            break;
        }
        case 0:
            return;
        default:
            printf("请输入数字[0--1]:");
            scanf("%d", &op);
        }
    }
}
