#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "solver.h"
#include "hanidoku.h"

int main() 
{
    write_sudoku();//生成基础cnf文件
    int op = 1;
    while (op) 
    {
        printf("\n\n");
        printf("               Main Menu                     \n");
        printf("---------------------------------------------\n");
        printf("         1.  Hanidoku   2.  SAT                \n");
        printf("         0.  Exit                            \n");
        printf("---------------------------------------------\n");
        printf("         请选择功能[0--2]:");
        scanf("%d", &op);
        system("cls");
        switch (op)
        {
        case 1:
            hanidoku();
            break;
        case 2:
        {
            char c='y';
            while (c == 'y')
            {
                solve();
                printf("是否继续？(y/n)   ");
                getchar();
                c = getchar();
            }
            system("pause");
            break;
        }
        case 0:
            exit(0);
        default:
            printf("请输入数字[0--2]:");
            scanf("%d", &op);
        }
    }
    return 0;
}