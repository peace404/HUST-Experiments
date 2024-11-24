#include "solver.h"

#ifdef PRO
struct cho {
    int pos = 0, cnt = 0, dat = 0;
};

bool cmp(cho a, cho b){
    return a.cnt > b.cnt;
}

int branch(cnf* formula, answer& answer)
{
    cho* choose = new cho[formula->varmax];
    for (clause* p = formula->head->next; p; p = p->next)
    {
        for (literal* l = p->head->next; l; l = l->next)
        {
            choose[abs(l->value) - 1].cnt++;
            choose[abs(l->value) - 1].dat = abs(l->value);
            l->value > 0 ? choose[abs(l->value) - 1].pos++ : choose[abs(l->value) - 1].pos--;
        }
    }
    std::sort(choose, choose + formula->varmax, cmp);
    int var = choose[0].pos > 0 ? choose[0].dat : -choose[0].dat;
    int i = formula->varmax;
    while (choose[i - 1].cnt == 0){
        i--;
    }
    while (choose[i - 1].cnt == 1)
    {
        assign_answer(var, answer, TRUE);
        assign_cnf(var, formula, answer);
        i--;
    }
    delete[] choose;
    return var;
}

#else
int branch(cnf* formula,answer& ans)//选择假设的变元
{
    return formula->head->next->head->next->value;
}
#endif // PRO

void assign_answer(int l, answer& answer, int trueth)//在答案数组中赋值
{
    if (trueth == TRUE)
    {
        if (l > 0)
            answer.value[l - 1] = 1;
        else
            answer.value[-l - 1] = -1;
    }
    else
    {
        if (l > 0)
            answer.value[l - 1] = -1;
        else
            answer.value[-l - 1] = 1;
    }
}

int find_unit_clause(cnf* formula, answer& answer)//寻找单子句
{
    for (clause* cla = formula->head; cla->next; cla = cla->next)
    {
        if (!cla->next->head->next)
            return 0;
        if (!cla->next->head->next->next)
        {
            int var = cla->next->head->next->value;
            clause* dcla = cla->next;
            cla->next = dcla->next;
            delete dcla;
            formula->size--;
            return var;
        }
    }
    return 0;
}

void unit_propagation(cnf* formula, answer& answer)//单子句传播
{
    int var = find_unit_clause(formula, answer);
    while (var)
    {
        assign_cnf(var, formula, answer);//改变链表
        var = find_unit_clause(formula, answer);
    }
}

int is_formula_satisfied(cnf* formula)//判断cnf状态
{
    if (!formula->head->next)//子句集为空
    {
        return TRUE;
    }
    int i = 0;
    for (clause* c = formula->head->next; c; c = c->next)
    {
        i++;
        if (!c->head->next)//存在空子句
            return FALSE;
    }
    return UNKNOWN;//无法判断
}

cnf* cpycnf(cnf* formula)//复制链表
{
    cnf* new_formula = new cnf(formula->size, formula->varmax, formula->satisfied);
    clause* node_c = new_formula->head;
    clause* c = formula->head->next;
    while (c)
    {
        clause* current_c = new clause();
        literal* node_l = current_c->head;
        literal* l = c->head->next;
        while (l)
        {
            literal* current_l = new literal(l->value);
            node_l->next = current_l;
            node_l = node_l->next;
            l = l->next;
        }
        node_c->next = current_c;
        node_c = node_c->next;
        c = c->next;
    }
    return new_formula;
}

cnf* assign_cnf(int var, cnf* formula,answer& ans)//根据假设变元更改链表
{
    assign_answer(var, ans, TRUE);
    int flag = 0; 
    clause* c = formula->head;
    while (c->next)
    {
        literal* l = c->next->head;
        while (l->next)
        {
            if (l->next->value == var)//相同，删去子句
            {
                clause* dc = c->next;
                c->next = dc->next;
                flag = 1;
                delete dc;
                formula->size--;
                break;
            }
            else if (l->next->value == -var)//相反，删去文字
            {
                literal* dl = l->next;
                l->next = dl->next;
                delete dl;
            }
            else
                l = l->next;
        }
        if (flag)
        {
            flag = 0;
            continue;
        }
        c = c->next;
    }
    return formula;
}

//void free_cnf(cnf* formula)//释放二维链表
//{
//    clause* c = formula->head, *bc = NULL;
//    while(c)
//    {
//        literal* l = c->head, *bl = NULL;
//        while (l)
//        {
//            bl = l;
//            l = l->next;
//            free(bl);
//            bl = NULL;
//        }
//        bc = c;
//        c = c->next;
//        free(bc);
//        bc = NULL;
//    }
//    free(formula);
//    formula = NULL;
//}

#ifdef DEBUG
void print_cnf(cnf* formula)
{
    for (clause* c = formula->head->next; c; c = c->next)
    {
        for (literal* l = c->head->next; l; l = l->next)
        {
            printf("%d ", l->value);
        }
        printf("\n");
    }
}
void printf_answer(cnf* formula, answer ans)
{
    for (int i = 0; i < formula->varmax; i++)
    {
        printf("%4d ", ans.value[i] * (i + 1));
        if (!((i + 1) % 20))
            printf("\n");
    }
}
static int step = -1;
int dpll(cnf* formula, answer answer)
{
    step++;
    printf("\nstep==%d\n", step);
    unit_propagation(formula, answer);
    printf_answer(formula,answer);
    if (is_formula_satisfied(formula) == TRUE)
    {
        step--;
        return TRUE;
    }
    if (is_formula_satisfied(formula) == FALSE)
    {
        step--;
        return FALSE;
    }
    int var = formula->head->next->head->next->value;
    cnf* cpy = cpycnf(formula);
    printf("\n%d->true\n", var);
    if (dpll(assign_cnf(var, cpy, answer), answer))
    {
        free(cpy);
        cpy = NULL; 
        step--;
        return TRUE;
    }
    else
    {
        printf("\n%d->false\n", var);
        free(cpy);
        cpy = NULL;
        step--;
        return dpll(assign_cnf(-var, formula, answer), answer);
    }
}
#else
int dpll(cnf* formula, answer& answer)
{
    unit_propagation(formula, answer);
    if (is_formula_satisfied(formula) == TRUE)
        return TRUE;
    if (is_formula_satisfied(formula) == FALSE)
        return FALSE;
    int var = branch(formula, answer);
    cnf* cpy = cpycnf(formula);
    if (dpll(assign_cnf(var, cpy, answer), answer))
    {
        delete cpy;
        return TRUE;
    }
    else
    {
        delete cpy;
        return dpll(assign_cnf(-var, formula, answer), answer);
    }
}

#endif // DEBUG

cnf* read_cnf(const char* filename)
{
    FILE* fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("无法打开文件 %s\n", filename);
        system("pause");
        system("cls");
        return NULL;
    }
    cnf* formula = new cnf();
    //读取注释段
    char c;
    while (fscanf(fp, "%c", &c) && c != 'p');
    fscanf(fp, " cnf "); //开始读到文件的信息段
    fscanf(fp, "%d %d", &formula->varmax, &formula->size);
    fgetc(fp);
    clause* current_clause = formula->head; // 存储当前处理的子句
    int value = 0; // 存储每个文字的值
    for (int i = 0; i < formula->size; i++)
    {
        clause* new_clause = new clause;
        literal* current_literal = new_clause->head;
        while (fscanf(fp, "%d", &value) && value)
        {
            literal* new_literal = new literal(value);
            current_literal->next = new_literal;
            current_literal = current_literal->next;
        }
        current_clause->next = new_clause;
        current_clause = current_clause->next;
    }
    fclose(fp);
    return formula;
}

int print_answer(cnf* formula, answer& ans, const char* filename)//将答案生成到res文件中
{
    FILE* fp;
    char file_out[256];
#ifndef PRO
    sprintf(file_out, "%s.res", filename);
#else
    sprintf(file_out, "%s_pro.res", filename);
#endif // !PRO
    fp = fopen(file_out, "w");
    if (!fp)
        return 0;
    fprintf(fp, "s %d\n", formula->satisfied);
    fprintf(fp, "v ");
    for (int i = 0; i < formula->varmax; i++)
    {
        fprintf(fp, "%d ", (i+1)*ans.value[i]);
    }
    fprintf(fp, "\n");
    fprintf(fp, "t %dms", ans.time);
    fclose(fp);
    return 1;
}

void checkanswer(cnf* formula, const char* filename)//生成检查文件
{
    FILE* fp;
    char file_check[256];
    sprintf(file_check, "%s.txt", filename);
    fp = fopen(file_check, "w");
    if (!fp)
    {
        printf("写入失败！");
        return;
    }
    fprintf(fp, "p cnf %d %d\n", formula->varmax, formula->size);
    for (clause* p = formula->head->next; p; p = p->next)
    {
        for (literal* l = p->head->next; l; l = l->next)
        {
            fprintf(fp, "%d ", l->value);
        }
        fprintf(fp, "0\n");
    }
    fclose(fp);
}

int solve()
{
    char filename[256];
    printf("请输入cnf文件名：");
    scanf("%s", filename);
    char file_in[256];
    sprintf(file_in, "%s.cnf", filename);
    cnf* formula = read_cnf(file_in);
    if (!formula)
        return 0;
    answer ans(formula->varmax);
    checkanswer(formula, filename);
    int time_start = 0, time_end = 0;
    time_start = clock();
    formula->satisfied = dpll(formula,ans);
    time_end = clock();
    ans.time = time_end - time_start;
    if (print_answer(formula, ans, filename))
        printf("文件已写入！\n");
    else
        printf("写入失败！\n");
    return 0;
}

int solve_hanidoku(int* known, const char* filename)
{
    int sw[96] = { 0,0,0,0,0,0,0,0,0,0,0,0,1,2,3,4,0,0,0,0,0,5,6,7,8,9,10,0,0,0,0,11,12,13,14,15,16,17,0,0,0,18,19,20,21,22,23,24,25,0,0,26,27,28,29,30,31,32,33,34,0,35,36,37,38,39,40,41,42,0,0,43,44,45,46,47,48,49,0,0,0,50,51,52,53,54,55,0,0,0,0,56,57,58,59,60 };
    int nsw[61] = { 11,12,13,14,15,21,22,23,24,25,26,31,32,33,34,35,36,37,41,42,43,44,45,46,47,48,51,52,53,54,55,56,57,58,59,61,62,63,64,65,66,67,68,71,72,73,74,75,76,77,81,82,83,84,85,86,91,92,93,94,95 };
    char file[] = ".sudoku_rule.cnf";
    cnf* formula = read_cnf(file);
    answer ans(549);
    for (int i = 0; i < 96; i++)
    {
        if (known[i])
        {
            int var = (sw[i] * 9 + known[i]);
            assign_cnf(var, formula, ans);
        }
    }
    int time_start = 0, time_end = 0;
    time_start = clock();
    formula->satisfied = dpll(formula, ans);
    time_end = clock();
    ans.time = time_end - time_start;
    for (int i = 0; i < 549; i++)
    {
        if (ans.value[i] == 1)
        {
            int k = (i + 1) % 9;
            if (k == 0)
                k = 9;
            int xy = nsw[(i + 1 - k) / 9];
            known[xy] = k;
        }
    }
    if (formula->satisfied)
    {
        char file_ans[256];
        sprintf(file_ans, "%s_ans", filename);
        print_answer(formula, ans, filename);
        return 1;
    }
    else
    {
        return 0;
    }
}
//int main()
//{
//    char root[] = "D:\\o";
//    struct _finddata_t file;
//    intptr_t hFile;
//    char buf[256];
//    if (_chdir(root))
//        return 0;
//    hFile = _findfirst("*.cnf", &file);
//    solve(file.name);
//    while (_findnext(hFile, &file) == 0)
//    {
//        solve(file.name);
//    }
//    _findclose(hFile);
//    char filename[256];
//    strcpy(filename, "ais10.cnf");
//    solve(filename);
//    printf("请输入cnf文件名：");
//    scanf("%s", filename);
//    return 0;
//}
