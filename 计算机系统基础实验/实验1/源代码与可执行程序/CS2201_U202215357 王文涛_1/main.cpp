#include<stdio.h>
#include<string.h>
#include<stdlib.h>
const int N = 5;
const int N1 = 2; 
const int N2 = 3;
char message[500];

struct student {
    char  name[8];
    short  age;
    float  score;
    char  remark[200]; 
}old_s[N], new_s[N];

int  pack_student_bytebybyte(student* s, int sno, char* buf)
{
    int i = 0;
    for (int k = 0; k < sno; k++)
    {
        char* p = (char*)(s+k);
        char* q = p;
        do {
            buf[i++] = *q;
        } while (*(q++));
        q = p + 8;
        for (int k = 0; k < 2; k++)
            buf[i++] = *(q++);
        q += 2;
        for (int k = 0; k < 4; k++)
            buf[i++] = *(q++);
        do {
            buf[i++] = *q;
        } while (*(q++));
    }
    return i; 
}

int  pack_student_whole(student* s, int sno, char* buf)
{
    int len = 0,len1,len2;
    for (int i = 0; i < sno; i++)
    {
        len1 = strlen(s[i].name)+1;
        strcpy(buf+len, s[i].name);
        memcpy(buf + len + len1, &s[i].age, 2);
        memcpy(buf + len + len1 + 2, &s[i].score, 4);
        len2 = strlen(s[i].remark)+1;
        strcpy(buf + len +len1+6, s[i].remark);
        len +=  len1+ 6 + len2;
    }
    return len;
}

int restore_student(char* buf, int len, student* s)
{
    int num = 0,len1,len2;
    char* p = buf;
    while (len>0)
    {
        len1 = strlen(p)+1;
        strcpy(s[num].name, p);
        p += len1;
        memcpy(&s[num].age, p, 2);
        memcpy(&s[num].score, p + 2, 4);
        p += 6;
        len2 = strlen(p)+1;
        strcpy(s[num].remark, p);
        p += len2;
        len -= len1 + len2 + 6;
        num++;
    }
    return num;
}

void print_message(char* buf)
{
    printf("缓冲区前20字节：");
    for (int i = 0; i < 20; i++)
        printf("% 02x ", (unsigned char)buf[i]);
}

void print_student(student* s,int sno)
{
    for(int i=0;i<sno;i++)
        printf("name: %s\nage: %d\nscore: %f\nremark: %s\n\n", s[i].name, s[i].age, s[i].score, s[i].remark);
}
int main()
{
    int len1,len2;
    freopen("1.in", "r", stdin);
    for (int i = 0; i < N; i++)
        scanf("%s\n%hd\n%f\n%s", &old_s[i].name, &old_s[i].age, &old_s[i].score, &old_s[i].remark);
    printf("解压前数据:\n");
    print_student(old_s, N);
    len1 = pack_student_bytebybyte(old_s, N1, message);
    len2 = pack_student_whole(old_s+ N1, N2, message+len1);
    restore_student(message, len1 + len2, new_s);
    printf("压缩后长度为%d字节\n\n", len1 + len2);
    printf("解压后数据:\n");
    print_student(new_s, N);
    print_message(message);
    freopen("CON", "r", stdin);
    system("pause");
    return 0;
}