
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
//#define DEBUG
//#define PRO

constexpr auto unknown = -1;

struct literal {
    int value = 0; // 文字的值
    literal* next = {}; // 指向下一个文字的指针
};
struct clause {
    literal* head; // 指向第一个文字的指针
    clause* next; // 指向下一个子句的指针
};
struct cnf {
    clause* head; // 合取范式的第一个子句
    int size; // 合取范式中的子句个数
    int var_max; //变元数目
    int satisfied;//是否可满足
};

int* assign_true(int l, int* assignment)
{
    if (l > 0)
        assignment[abs(l)] = 1;
    else
        assignment[abs(l)] = 0;
    return assignment;
}

int* assign_false(int l, int* assignment)
{
    if (l > 0)
        assignment[abs(l)] = 0;
    else
        assignment[abs(l)] = 1;
    return assignment;
}

int is_literal_satisfied(literal* l, const int* assignment)
{
    if (l->value > 0 && assignment[abs(l->value)] == true || l->value < 0 && assignment[abs(l->value)] == false)
        return true;
    else if (assignment[abs(l->value)] == unknown)
        return unknown;
    else
        return false;
}

int is_clause_satisfied(clause* p, int* assignment)
{
    for (literal* l = p->head; l; l = l->next)
        if (is_literal_satisfied(l, assignment) == true)
            return true;
    return false;
}

int is_formula_satisfied(cnf* formula, int* assignment)
{
    for (clause* p = formula->head; p; p = p->next)
    {
        if (!is_clause_satisfied(p, assignment))
        {
            return false;
        }
    }
    return true;
}

int find_unit_clause(cnf* formula, int* assignment)
{
    for (clause* p = formula->head; p; p = p->next)
    {
        if (is_clause_satisfied(p, assignment))
        {
            continue;
        }
        int unit_literal = 0;
        for (literal* l = p->head; l; l = l->next)
        {
            if (is_literal_satisfied(l, assignment) == unknown)
            {
                if (unit_literal == 0)
                {
                    unit_literal = l->value;
                }
                else
                {
                    unit_literal = 0;
                    break;
                }

            }
        }
        if (unit_literal != 0)
        {
            return unit_literal;
        }
    }
    return 0;
}

void unit_propagation(cnf* formula, int* assignment)
{
    int unit_literal = find_unit_clause(formula, assignment);
    while (unit_literal != 0)
    {
        assign_true(unit_literal, assignment);
        unit_literal = find_unit_clause(formula, assignment);
    }
}

#ifdef PRO

struct ce {
    int count, data, pos;
};

int cmp(const void* a, const void* b)
{
    ce* p1 = (ce*)a;
    ce* p2 = (ce*)b;
    return (p2->count - p1->count);
}

int branching(cnf* formula, int* assignment)
{
    ce* choose = (ce*)calloc(formula->varmax, sizeof(ce));
    for (clause* p = formula->head; p; p = p->next)
    {
        for (literal* l = p->head; l; l = l->next)
        {
            if (is_literal_satisfied(l, assignment) == unknown)
            {
                choose[abs(l->value) - 1].count++;
                choose[abs(l->value) - 1].data = abs(l->value);
                if (l->value > 0)
                    choose[abs(l->value) - 1].pos++;
                else
                    choose[abs(l->value) - 1].pos--;
            }
        }
    }
    qsort(choose, formula->varmax, sizeof(ce), cmp);
    int cho;
    if (choose[0].pos > 0)
        cho = choose[0].data;
    else
        cho = -choose[0].data;
    free(choose);
    return cho;
}

#else
int branching(cnf* formula, int* assignment)
{
    for (clause* p = formula->head; p; p = p->next)
    {
        for (literal* l = p->head; l; l = l->next)
        {
            if (is_literal_satisfied(l, assignment) == unknown)
                return l->value;
        }
    }
    return 0;
}


#endif // PRO

void print(cnf* formula, const int* assignment)
{
    int count = 0;
    for (int i = 1; i <= formula->var_max; i++)
    {
        if (assignment[i] == true)
        {
            printf("%5d ", i);
            count++;
        }
        else if (assignment[i] == false)
        {
            printf("%5d ", -i);
            count++;
        }
        else
        {
            continue;
        }
        if (!(count % 20))
        {
            printf("\n");
        }
    }
    printf("\nsum:%d\n\n", count);
}

bool is_formula_unsatisfied(cnf* formula, int* assignment)
{
    for (clause* p = formula->head; p; p = p->next)
    {
        int flag = 0;
        for (literal* l = p->head; l; l = l->next)
        {
            if (is_literal_satisfied(l, assignment) != false)
            {
                flag = 1;
                break;
            }
        }
        if (flag == 0)
        {
            return false;
        }
    }
    return true;
}

#ifdef DEBUG

static int step = -1;
void print(cnf* formula, int* assignment)
{
    int count = 0;
    int flag = 0;
    for (int i = 1; i <= formula->varmax; i++)
    {
        if (assignment[i] == true)
        {
            printf("%5d ", i);
            count++;
        }
        else if (assignment[i] == false)
        {
            printf("%5d ", -i);
            count++;
        }
        else
        {
            continue;
        }
        if (!(count % 20))
        {
            printf("\n");
        }
    }
    printf("\nsum:%d\n\n", count);
}
bool dpll(cnf* formula, int* assignment)
{
    step++;
    printf("\nstep=%d\n", step);
    unit_propagation(formula, assignment);
    //print(formula, assignment);
    if (is_formula_satisfied(formula, assignment))
    {
        step--;
        return true;
    }
    if (is_formula_unsatisfied(formula, assignment) == false)
    {
        step--;
        return false;
    }
    int branching_variable = branching(formula, assignment);
    int* new_assignment = (int*)malloc(sizeof(int) * (formula->varmax + 1));
    if (!new_assignment)
    {
        printf("空间分配失败！");
        return 0;
    }
    for (int i = 1; i <= formula->varmax; i++)
    {
        new_assignment[i] = assignment[i];
    }
    assign_true(branching_variable, new_assignment);
    printf("\n%d->true\n", branching_variable);
    if (dpll(formula, new_assignment))
    {
        for (int i = 1; i <= formula->varmax; i++)
        {
            assignment[i] = new_assignment[i];
        }
        free(new_assignment);
        new_assignment = NULL;
        step--;
        return true;
    }
    for (int i = 1; i <= formula->varmax; i++)
    {
        new_assignment[i] = assignment[i];
    }
    assign_false(branching_variable, new_assignment);
    printf("\n%d->false\n", branching_variable);
    if (dpll(formula, new_assignment))
    {
        for (int i = 1; i <= formula->varmax; i++)
        {
            assignment[i] = new_assignment[i];
        }
        free(new_assignment);
        new_assignment = NULL;
        step--;
        return true;
    }
    free(new_assignment);
    step--;
    return false;
}
#else
bool dpll(cnf *formula, int *assignment)
{
    unit_propagation(formula, assignment);
    if (is_formula_satisfied(formula, assignment))
    {
        return true;
    }
    if (!is_formula_unsatisfied(formula, assignment))
    {
        return false;
    }
    int branching_variable = branching(formula, assignment);
    int* new_assignment = new int[formula->var_max + 1];
    for (int i = 1; i <= formula->var_max; i++)
    {
        new_assignment[i] = assignment[i];
    }
    assign_true(branching_variable, new_assignment);
    if (dpll(formula, new_assignment))
    {
        for (int i = 1; i <= formula->var_max; i++)
        {
            assignment[i] = new_assignment[i];
        }
        delete[] new_assignment;
        return true;
    }
    else
    {
        delete[] new_assignment;
        return dpll(formula, assign_false(branching_variable, assignment));
    }
    //for (int i = 1; i <= formula->varmax; i++)
    //{
    //    new_assignment[i] = assignment[i];
    //}
    //assign_false(branching_variable, new_assignment);
    //if (dpll(formula, new_assignment))
    //{
    //    for (int i = 1; i <= formula->varmax; i++)
    //    {
    //        assignment[i] = new_assignment[i];
    //    }
    //    delete[] new_assignment;
    //    return true;
    //}
    //free(new_assignment);
    //return false;
}
#endif // DEBUG

cnf* read_cnf(char* filename)
{
    std::ifstream file(filename);
    if (!file)
    {
        std::cerr << "无法打开文件 " << filename << std::endl;
        return nullptr;
    }
    // 创建一个空的cnf结构体
    cnf* formula = new cnf();
    formula->head = nullptr;

    std::string line;
    while (std::getline(file,line)) {
        if (line.empty() || line[0] == 'c') continue;
        if (line[0] == 'p') {
            std::istringstream iss(line);
            std::string temp;
            iss >> temp >> temp >> formula->var_max >> formula->size;
            break;
        }
    }
        clause* current_clause = nullptr;

        while (std::getline(file, line)) {
            std::istringstream iss(line);
            int value;
            clause* new_clause = new clause();
            new_clause->head = nullptr;
            new_clause->next = nullptr;

            if (!formula->head)
                formula->head = new_clause;
            else
                current_clause->next = new_clause;
            current_clause = new_clause;

            literal* current_literal = nullptr;
            while (iss >> value && value != 0) {
                literal* new_literal = new literal();
                new_literal->value = value;
                new_literal->next = nullptr;
                if (!new_clause->head)
                    new_clause->head = new_literal;
                else
                    current_literal->next = new_literal;

                current_literal = new_literal;
            }
        }

    return formula;
}

int print_answer(cnf* formula, int* assignment, char* filename, int time)
{
    FILE* fp;
    char file_out[256];
    sprintf(file_out, "%s_1.res", filename);
    fp = fopen(file_out, "w");
    if (!fp)
    {
        printf("打开失败！");
        return 0;
    }
    fprintf(fp, "s %d\n", formula->satisfied);
    fprintf(fp, "v ");
    for (int i = 1; i <= formula->var_max; i++)
    {
        if (assignment[i] == true)
            fprintf(fp, "%d ", i);
        else
            fprintf(fp, "%d ", -i);
    }
    fprintf(fp, "\n");
    fprintf(fp, "t %dms", time);
    fclose(fp);
    return 1;
}

//void checkanswer(cnf* formula, char* filename)
//{
//    FILE* fp;
//    char file_check[256];
//    sprintf(file_check, "D:\\%s_check.txt", filename);
//    fp = fopen(file_check, "w");
//    if (!fp)
//    {
//        printf("写入失败！");
//        return;
//    }
//    fprintf(fp, "p cnf %d %d\n", formula->var_max, formula->size);
//    for (clause* p = formula->head; p; p = p->next)
//    {
//        for (literal* l = p->head; l; l = l->next)
//        {
//            fprintf(fp, "%d ", l->value);
//        }
//        fprintf(fp, "0\n");
//    }
//}

int main()
{
    while (1)
    {
        char filename[256];
        std::cin >> filename;
        cnf* formula = read_cnf(filename);
        if (!formula)
        {
            printf("打开失败！\n");
            return 0;
        }
        int* assignment = new int[formula->var_max + 1];
        for (int i = 1; i <= formula->var_max; i++)
        {
            assignment[i] = unknown;
        }
        int time_start = 0, time_end = 0;
        time_start = clock();
        formula->satisfied = dpll(formula, assignment);
        time_end = clock();
        int time = time_end - time_start;
        if (print_answer(formula, assignment, filename, time))
            printf("文件已写入！\n");
        else
            printf("写入失败！\n");
        return 0;
    }
}