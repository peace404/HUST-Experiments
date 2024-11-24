#define _CRT_SECURE_NO_WARNINGS
//#define DEBUG
//#define PRO
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define TRUE 1
#define FALSE 0
#define UNKNOWN -1
#include <io.h>
#include <direct.h>
struct literal {
    literal(int x = 0) : value(x), next(nullptr) {}
    int value = 0; // 文字的值
    literal* next = {}; // 指向下一个文字的指针
};

// 定义一个结构体，表示一个子句
struct clause {
    clause(){
        head = new literal();
        next = nullptr;
    }
    clause(int) {
        head = nullptr;
        next = nullptr;
    }
    ~clause() {
        literal* l;
        if (head)
        {
            while (head->next)
            {
                l = head->next;
                delete head;
                head = l;
            }
            delete head;
        }
    }
    literal* head; // 指向第一个文字的指针
    clause* next; // 指向下一个子句的指针
};

// 定义一个结构体，表示一个合取范式
struct cnf {
    cnf(int a = 0, int b = 0, int c = 0) {
        head = new clause(1);
        size = a;
        varmax = b;
        satisfied = c;
    }
    clause* head; // 合取范式的第一个子句
    int size; // 合取范式中的子句个数
    int varmax; //变元数目
    int satisfied;//是否可满足
    ~cnf() {
        if (head)
        {
            clause* c;
            while (head->next)
            {
                c = head->next;
                delete head;
                head = c;
            }
            delete head;
        }
    }
};

struct answer {
    answer(int x) {
        value = new int[x]();
        time = 0;
    }
    ~answer() {
        delete[] value;
    }
    int* value;//记录真值
    int time;//程序用时
};

void assign_answer(const int l, answer& answer, const int trueth);
int find_unit_clause(cnf* formula, answer& answer);
void unit_propagation(cnf* formula, answer& answer);
int is_formula_satisfied(cnf* formula);
cnf* cpycnf(cnf* formula);
cnf* assign_cnf(const int var, cnf* formula, answer& answer);
//void free_cnf(cnf* formula);
void print_cnf(cnf* formula);
int dpll(cnf* formula, answer& answer);
cnf* read_cnf(const char* filename);
int print_answer(cnf* formula, answer& ans, const char* filename);
int solve();
int solve_hanidoku(int* known,const char* filename);