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
    for(i=0;i<5;i++) //����ѧ�����ݣ����Ҽ���ƽ���ɼ�
    {
        printf("�����%d��ѧ����ѧ�ź�����\n",i+1);
        scanf("%d %s",&s[i].num,&s[i].name);
        printf("�����������ſγɼ�\n");
        int k=0;
        float sum=0;
        for(k=0;k<3;k++)
        {
            scanf("%f",&s[i].score[k]);
            sum=sum+s[i].score[k];
        }
        // printf("sum=%.2f\n",sum);
        s[i].pj=sum/3;
        printf("%s��ƽ���ɼ�Ϊpj=%.2f\n",s[i].name,s[i].pj);
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
        printf("ѧ�ţ�%d ������%s �ɼ���%.1f %.1f %.1f ƽ���ɼ���%.1f\n",s[w].num,s[w].name,s[w].score[0],s[w].score[1],s[w].score[2],s[w].pj);
    }

    fclose(fp);
    fp=NULL;
    return 0;
}