#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct student{
    char num[9];
    char name[6];
    char prof[30];
    char sex;
    float mgrade;
    float cgrade;
    float egrade;
    float avg;
};
typedef struct node
{
    struct student data;
    struct node *next;
}Node;
/*按学号加入学生信息*/
bool Add(Node *&p)
{
    char num1[9],name1[6],prof[30],c1='M',c2='F';
    Node *r=p,*s;
    s=(Node *)malloc(sizeof(Node));
    printf("\ninput num(eight numbers):");
    while(1)
    {//输入正确学号
        scanf("%s",num1);
        strcpy(s->data.num,num1);
        if(strlen(num1)!=8)
            printf("number length must be eight!input again:");
        else break;
    }
    printf("\ninput name:");
    while(1)
    {//输入正确姓名
        scanf("%s",name1);
        strcpy(s->data.name,name1);
        if(strlen(name1)>5)
            printf("name length must be less five!input again:");
        else break;
    }
    printf("\ninput profession:");
    while(1)
    {//输入正确专业
        scanf("%s",prof);
        strcpy(s->data.prof,prof);
        if(strlen(prof)>30)
            printf("profession length must be less thirty!input again:");
        else break;
    }
    printf("\ninput sex(F/M):");
    while(1)
    {//输入正确性别
        getchar();
        scanf("%c",&s->data.sex);
        if(s->data.sex!='F')
        {
            if(s->data.sex!='M')
                printf("input error!input again:");
            else break;
        }
        else break;
    }
    printf("\ninput mgrade:");
    scanf("%f",&s->data.mgrade);//数学成绩
    printf("\ninput cgrade:");
    scanf("%f",&s->data.cgrade);//语文成绩
    printf("\ninput egrade:");
    scanf("%f",&s->data.egrade);//英语成绩
    s->data.avg=(s->data.mgrade+s->data.cgrade+s->data.egrade)/3;
    s->next=NULL;
     while(r->next!=NULL&&strcmp(s->data.num,r->next->data.num)>0)
    {//插入到比该学号大的之前
        r=r->next;
    }
    s->next=r->next;
    r->next=s;
}
/*根据学号查找学生信息*/
void Search(Node *p)
{
    char num[9]="0";
    Node *s=p;
    s=s->next;
    printf("input the number which you want to find(eight numbers):");
    while(1)
    {//输入正确学号信息
        scanf("%s",num);
        if(strlen(num)!=8)
            printf("number length must be eight! input again:");
        else break;
    }
    while(s!=NULL&&strcmp(s->data.num,num)!=0)s=s->next;
    if(s==NULL)//未查到
    {
        printf("no whom you want to check");
        return;
    }
    printf("num       name      profession         sex    math  Chinese  English    avg");
    printf("\n%-10s%-10s%-20s%-7c%-8.2f%-8.2f%-7.2f%-5.2f",
                   s->data.num,s->data.name,s->data.prof,
                   s->data.sex,s->data.mgrade,s->data.cgrade,s->data.egrade,s->data.avg);
}
/*输出所有学生信息*/
void Output(Node *p)
{
    Node *s=p;
    if(s->next==NULL)printf("No student information!");//系统为空
    else
    {
        s=s->next;
        printf("num       name      professional       sex    math  Chinese  English    avg");
        while(s!=NULL)
        {//输出所有学生信息
            printf("\n%-10s%-10s%-20s%-7c%-8.2f%-8.2f%-7.2f%-5.2f",
                   s->data.num,s->data.name,s->data.prof,
                   s->data.sex,s->data.mgrade,s->data.cgrade,s->data.egrade,s->data.avg);
            s=s->next;     //指向下一个节点
        }
    }
    printf("\n");
}
/*菜单、调用*/
void Menu(Node *&p)
{
    Node *s=p;
    int operate;
    char flag;
    while(1)
    {
        system("cls");
        printf("\t\t\t***********MENU***********\n");
        printf("\t\t\t* 1.search  student      *\n");
        printf("\t\t\t* 2.add     student      *\n");
        printf("\t\t\t* 3.output  all          *\n");
        printf("\t\t\t* 4.quit and save        *\n");
        printf("\t\t\t*    please choose(1-4)  *\n");
        printf("\t\t\t**************************\n");

        scanf("%d",&operate);
        while(operate<1||operate>4)
        {//输出正确菜单号
            getchar();
            printf("input error! please input again:");
            scanf("%d",&operate);
        }
        switch(operate)
        {
            case 1:Search(s);break;
            case 2:Add(s);break;
            case 3:Output(s);break;
            case 4:return;
        }
        getchar();
        while(1)
        {//循环继续
            printf("\n\nwhether to continue:y/n?");
            flag=getchar();
            if(flag=='y')
            {
                printf("\n\n");
                break;
            }
            else if(flag=='n') return;
            else printf("\ninput error! please input again:y/n?");
        }
    }
}
int main()
{
    FILE *fp;    //文件指针
    /*读取文件内容*/
    fp=fopen("student system","ab+");//以追加方式打开二进制文件，可读可写
    Node *p=(Node *)malloc(sizeof(Node)),*r,*s;//r、s作为记录指针变量
    p->next=NULL;
    s=p;
    while(!feof(fp))
    {//读文件
        r=(Node *)malloc(sizeof(Node));
        if(fread(r,sizeof(Node),1,fp))
        {
            r->next=NULL;
            s->next=r;
            s=r;
        }
    }
    free(r);
    fclose(fp);

    Menu(p);

    /*将修改后内容写入文件*/
    fp=fopen("student system","wb");
    p=p->next;
    while(p!=NULL)
    {
        fwrite(p,sizeof(Node),1,fp);
        p=p->next;
    }
    free(p);
    fclose(fp);
    return 0;
}
