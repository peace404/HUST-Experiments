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
    int value = 0; // ���ֵ�ֵ
    literal* next = {}; // ָ����һ�����ֵ�ָ��
};

// ����һ���ṹ�壬��ʾһ���Ӿ�
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
    literal* head; // ָ���һ�����ֵ�ָ��
    clause* next; // ָ����һ���Ӿ��ָ��
};

// ����һ���ṹ�壬��ʾһ����ȡ��ʽ
struct cnf {
    cnf(int a = 0, int b = 0, int c = 0) {
        head = new clause(1);
        size = a;
        varmax = b;
        satisfied = c;
    }
    clause* head; // ��ȡ��ʽ�ĵ�һ���Ӿ�
    int size; // ��ȡ��ʽ�е��Ӿ����
    int varmax; //��Ԫ��Ŀ
    int satisfied;//�Ƿ������
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
    int* value;//��¼��ֵ
    int time;//������ʱ
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