#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int main()
{
    struct student
    {
        int num;
        char name[6];
        float score[3];
        float pj;
    };
    struct student s[5];
    int i;
    for(i=0;i<5;i++) //输入学生数据，并且计算平均成绩
    {
        printf("输入第%d个学生的学号和姓名\n",i+1);
        scanf("%d %s",&s[i].num,&s[i].name);
        printf("依次输入三门课成绩\n");
        int k=0;
        float sum=0;
        for(k=0;k<3;k++)
        {
            scanf("%f",&s[i].score[k]);
            sum=sum+s[i].score[k];
        }
        // printf("sum=%.2f\n",sum);
        s[i].pj=sum/3;
        printf("%s的平均成绩为pj=%.2f\n",s[i].name,s[i].pj);
    }
    FILE* fp=fopen("D:\\stud","w");
//	struct student q[5];
    int p=0;
    for(p=0;p<5;p++)
    {
        fwrite(&s[p],sizeof(struct student),1,fp);
    }
    fclose(fp);
    fp=NULL;
    fp =fopen("D:\\stud","r");
    if(fp==NULL)
    {
        perror("fopen");
        return 1;
    }
    int w;
    for(w=0;w<5;w++)
    {
        fread(&s[w],sizeof(struct student),1,fp);
        printf("学号：%d 姓名：%s 成绩：%.1f %.1f %.1f 平均成绩：%.1f\n",s[w].num,s[w].name,s[w].score[0],s[w].score[1],s[w].score[2],s[w].pj);
    }

    fclose(fp);
    fp=NULL;
    return 0;
}