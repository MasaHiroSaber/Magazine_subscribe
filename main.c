#include "mag.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
FILE *sub;
FILE *sub_temp;
FILE *sub_over_date;
FILE *mag;
FILE *mag_temp;

///////////////////////////////////////////////////////////////////////////////////////////////////
int mag_read();
int now_time(int *y, int *m, int *d);
int menu();
int mag_find_sim(long long int a);
int sub_read();
void sub_add();
void sub_sum();
void mag_add();
void mag_del();
void FILE_change(char Old_filename[], char New_filename[]);
void sys_pause();
void overdue_sub_del();
void sub_mag_sum();
void sub_mag_sum_date();
void overdue_sub();

///////////////////////////////////////////////////////////////////////////////////////////////////
int now_time(int *y, int *m, int *d) {  //��ȡ��ǰʱ��

    time_t timep;               //time_t time(time_t *seconds)
    time(&timep);

    struct tm *p;               //gmtime��õ���һ����������ʱ������ɵĽṹ��
    p = gmtime(&timep);
    *y = p->tm_year;
    *m = p->tm_mon;
    *d = p->tm_mday;
    return 0;
}

void sys_pause() {         //  �����������...
    printf("\n\n�����������...");
    _getch();
}

void FILE_change(char Old_filename[], char New_filename[]) {        //�ļ���ɾ����������(�Ƚ�ԭʼ�ķ���ɾ���ļ��������)
    int del_ret = remove(New_filename);  //ɾ��
    rename(Old_filename, New_filename);  //������
    if (del_ret == 0) {
        printf("\n�ɹ�\n");
    } else
        printf("\nʧ��\n");
}
///////////////////////////////////////////////////////////////////////////////////////////////////

//�����༭
int sub_read() {
    int k = 0;
    sub = fopen("Reader.txt", "r");
    while (!feof(sub)) {
        fscanf_s(sub, "%s%s%lld%lld%d%d%d%d%d%d%d\n", sub_list[k].name, 20, sub_list[k].address, 40,
                 &sub_list[k].phone_num, &sub_list[k].mag_num,
                 &sub_list[k].sub_n, &sub_list[k].start_date.year, &sub_list[k].start_date.month,
                 &sub_list[k].end_date.year,
                 &sub_list[k].end_date.month,
                 &sub_list[k].date_sum, &sub_list[k].price);
        if (sub_list[k].phone_num != 0) {
            printf("\n ����:%-10s��ַ:%-20s�绰����:%-12lld�ڿ���:%-16lld���ķ���:%-5d������:%d��%d�� ֹ������:%d��%d�� �ܶ��ķ���:%-4d���:%-4d",
                   sub_list[k].name, sub_list[k].address,
                   sub_list[k].phone_num, sub_list[k].mag_num,
                   sub_list[k].sub_n, sub_list[k].start_date.year, sub_list[k].start_date.month,
                   sub_list[k].end_date.year,
                   sub_list[k].end_date.month,
                   sub_list[k].date_sum, sub_list[k].price);
            k += 1;
        }
    }
    if (k == 0)
        printf("\n�ļ������޶���\n");
    fclose(sub);
    return k;
}

void sub_add() {
    int n, k = 0;

    for (int i = 0; i < MAX_SUB; i++) {
        mag = fopen("MAG.txt", "r");
        int j = 0;
        printf("\n*------�������¶�����Ϣ------*\n");

        printf("\n�����붩������:");
        scanf_s("%s", &sub_list[i].name, 20);
        /////////////////////////////////
        printf("\n�����붩����ַ:");
        scanf_s("%s", &sub_list[i].address, 40);
        /////////////////////////////////
        printf("\n�����붩���绰����:");
        scanf_s("%lld", &sub_list[i].phone_num);
        /////////////////////////////////
        printf("\n�����붩�������ڿ����ڿ���:");
        scanf_s("%lld", &sub_list[i].mag_num);
        /////////////////////////////////
        printf("\n�����붩���Ķ��ķ���:");
        scanf_s("%d", &sub_list[i].sub_n);
        /////////////////////////////////
        printf("\n�����붩����������:");
        scanf_s("%d.%d", &sub_list[i].start_date.year, &sub_list[i].start_date.month);
        /////////////////////////////////
        printf("\n�����붩����ֹ������:");
        scanf_s("%d.%d", &sub_list[i].end_date.year, &sub_list[i].end_date.month);
        /////////////////////////////////
        int *p, *t;
        int cmp = 0;
        int res = 0;
        /////////////////////////////////
        while (!feof(mag)) {
            fscanf_s(mag, "%lld%s%s%d", &mag_list[j].mag_num, mag_list[j].mag_name, 60, mag_list[j].mag_n, 10,
                     &mag_list[j].mag_price);

            if (mag_list[j].mag_num == sub_list[i].mag_num) {
                printf("\n----------------------------------------------�ҵ��鼮----------------------------------------------\n");
                res = 1;
                if (strcmp(mag_list[j].mag_n, "�¿�") == 0)
                    cmp = 1;
                else if (strcmp(mag_list[j].mag_n, "���¿�") == 0)
                    cmp = 2;
                else if (strcmp(mag_list[j].mag_n, "�ܿ�") == 0)
                    cmp = 4;
                p = &sub_list[i].date_sum;
                *p = ((sub_list[i].end_date.year - sub_list[i].start_date.year) * 12 +     //����һ�����ĵķ���
                      (sub_list[i].end_date.month - sub_list[i].start_date.month)) * cmp;
                t = &sub_list[i].price;
                *t = sub_list[i].date_sum * mag_list[j].mag_price;
                break;
            }
            j += 1;
        }
        fclose(mag);
        k += 1;
        printf("res=%d",res);
        if (res == 1) {
            sub = fopen("Reader.txt", "a+");
            fprintf(sub, "%10s%30s%15lld%20lld%5d%6d%3d%6d%3d%5d%5d\n", sub_list[i].name, sub_list[i].address,
                    sub_list[i].phone_num, sub_list[i].mag_num,
                    sub_list[i].sub_n, sub_list[i].start_date.year, sub_list[i].start_date.month,
                    sub_list[i].end_date.year,
                    sub_list[i].end_date.month,
                    sub_list[i].date_sum, sub_list[i].price);
            fclose(sub);
        }
        else
            printf("\n��������ڿ�������\n");
        printf("�ٴ�������Ϣ������1���˳�������������������:");
        scanf_s("%d", &n);
        printf("\n\n");

        if (n == 1)
            continue;
        else
            break;
    }
    sys_pause();
}

void overdue_sub_del() {    //now_time()������ȡϵͳ��ǰʱ�䣬�ж϶����Ƿ��Ѿ�����
    int y, m, d;            //�����Ѿ����ڵĶ����������ڵĶ�����Ϣ���浽Reader_over.txt��
    int k = 0;              //��δ���ڵĶ�����Ϣ���浽Reader_temp.txt
    now_time(&y, &m, &d);   //Ȼ��ɾ��Reader.txt,������Reader_temp,��ɹ��ڶ�����ɾ��
    sub = fopen("Reader.txt", "r+");
    sub_temp = fopen("Reader_temp.txt", "a+");
    sub_over_date = fopen("Reader_over.txt", "a+");
    while (!feof(sub)) {
        /////////////////////////////////
        fscanf_s(sub, "%s%s%lld%lld%d%d%d%d%d%d%d\n", sub_list[k].name, 20, sub_list[k].address, 40,
                 &sub_list[k].phone_num, &sub_list[k].mag_num,
                 &sub_list[k].sub_n, &sub_list[k].start_date.year, &sub_list[k].start_date.month,
                 &sub_list[k].end_date.year,
                 &sub_list[k].end_date.month,
                 &sub_list[k].date_sum, &sub_list[k].price);
        if (sub_list[k].phone_num == 0) {
            printf("\n��⵽��Ϣ����ֹͣ����\n");
            break;
        }
        /////////////////////////////////
        if (sub_list[k].end_date.year < 1900 + y ||
            (sub_list[k].end_date.year == 1900 + y && sub_list[k].end_date.month <= m)) {
            fprintf(sub_over_date, "%10s%30s%15lld%20lld%5d%6d%3d%6d%3d%5d%5d\n", sub_list[k].name, sub_list[k].address,
                    sub_list[k].phone_num, sub_list[k].mag_num,
                    sub_list[k].sub_n, sub_list[k].start_date.year, sub_list[k].start_date.month,
                    sub_list[k].end_date.year,
                    sub_list[k].end_date.month,
                    sub_list[k].date_sum, sub_list[k].price);
        } else {
            fprintf(sub_temp, "%10s%30s%15lld%20lld%5d%6d%3d%6d%3d%5d%5d\n", sub_list[k].name, sub_list[k].address,
                    sub_list[k].phone_num, sub_list[k].mag_num,
                    sub_list[k].sub_n, sub_list[k].start_date.year, sub_list[k].start_date.month,
                    sub_list[k].end_date.year,
                    sub_list[k].end_date.month,
                    sub_list[k].date_sum, sub_list[k].price);
        }
        k += 1;
    }

    fclose(sub);
    fclose(sub_temp);
    fclose(sub_over_date);
    char new[] = "Reader.txt";
    char old[] = "Reader_temp.txt";
    FILE_change(old, new);
}

void sub_sum() {            //��ǰ��Ч������ѯ
    int sum;                //ֻ��Ҫ����now_time(),overdue_sub_del(),sub_read()������������ʵ�ֹ���
    int y, m, d;
    now_time(&y, &m, &d);
    overdue_sub_del();
    printf("\n��ֹ%d��%d��%d��,��Ч�Ķ���Ϊ:\n", y, m, d);
    sum = sub_read();
    printf("\n�ϼ�%d��\n", sum);
    sys_pause();
}

void sub_mag_sum() {        //ͳ�Ƹ����ڿ�����Ч�ܶ�����
    int k = 0;              //�ܶ�����Ϊ���ܶ������� * ���ķ��� * �ڿ�����K (K=1,2,4;�¿������¿����ܿ�)
    overdue_sub_del();
    mag = fopen("MAG.txt", "r");
    while (!feof(mag)) {
        fscanf_s(mag, "%lld%s%s%d", &mag_list[k].mag_num, mag_list[k].mag_name, 60, mag_list[k].mag_n, 10,
                 &mag_list[k].mag_price);
        if (mag_list[k].mag_num != 0) {
            k += 1;
        }
    }
    fclose(mag);

    int sum[MAX_MAG] = {0}; //��Ÿ����ڿ����ܶ�����
    int m = 0;

    sub = fopen("Reader.txt", "r");
    while (!feof(sub)) {
        fscanf_s(sub, "%s%s%lld%lld%d%d%d%d%d%d%d\n", sub_list[m].name, 20, sub_list[m].address, 40,
                 &sub_list[m].phone_num, &sub_list[m].mag_num,
                 &sub_list[m].sub_n, &sub_list[m].start_date.year, &sub_list[m].start_date.month,
                 &sub_list[m].end_date.year,
                 &sub_list[m].end_date.month,
                 &sub_list[m].date_sum, &sub_list[m].price);
        if (sub_list[m].phone_num != 0) {
            m += 1;
        }
    }
    fclose(sub);

    for (int i = 0; i < m; i++)
        for (int j = 0; j < k; j++) {
            if (sub_list[i].mag_num == mag_list[j].mag_num) {
                sum[j] += sub_list[i].date_sum;
                break;
            }
        }
    for (int i = 0; i < k; i++) {
        printf("�ڿ���:ISSN-%lld �ڿ���:%s ��Ч���ķ���:%d\n", mag_list[i].mag_num, mag_list[i].mag_name, sum[i]);
    }

}

void sub_mag_sum_date() {       //��ѯĳʱ����ڸ����ڿ��Ķ�������
    int s_year, s_month;        //ֻҪ�ڿ�����ʱ���������ʱ����ھͷ���Ҫ��
    int e_year, e_month;
    int k = 0;
    overdue_sub_del();
    printf("��������Ҫ��ѯʱ��ε���ʼ����XXXX.X:");
    scanf_s("%d.%d", &s_year, &s_month);
    printf("��������Ҫ��ѯʱ��ε���ֹ����XXXX.X:");
    scanf_s("%d.%d", &e_year, &e_month);
    if(s_year > e_year)
        printf("\n�������ʱ������\n");
    mag = fopen("MAG.txt", "r");
    while (!feof(mag)) {
        fscanf_s(mag, "%lld%s%s%d", &mag_list[k].mag_num, mag_list[k].mag_name, 60, mag_list[k].mag_n, 10,
                 &mag_list[k].mag_price);
        if (mag_list[k].mag_num != 0) {
            k += 1;
        }
    }
    fclose(mag);
    int m = 0;
    sub = fopen("Reader.txt", "r");
    while (!feof(sub)) {
        fscanf_s(sub, "%s%s%lld%lld%d%d%d%d%d%d%d\n", sub_list[m].name, 20, sub_list[m].address, 40,
                 &sub_list[m].phone_num, &sub_list[m].mag_num,
                 &sub_list[m].sub_n, &sub_list[m].start_date.year, &sub_list[m].start_date.month,
                 &sub_list[m].end_date.year,
                 &sub_list[m].end_date.month,
                 &sub_list[m].date_sum, &sub_list[m].price);
        if (sub_list[m].phone_num != 0)
            m += 1;
        else
            break;
    }
    fclose(sub);

    int sum[MAX_MAG] = {0};
    int res_s,res_e;

    for (int i = 0; i < m; i++) {
        res_s = 12*(sub_list[i].start_date.year - s_year) + (sub_list[i].start_date.month-s_month);
        res_e = 12*(e_year - sub_list[i].end_date.year)+(e_month - sub_list[i].end_date.month);
        //��ΪҪ���ĵ����¶��������ʱ�����
        //����res_s(res_s��ΪResult_Start)Ϊ(������� - ʱ�����ݣ�*12 - (�����·� - ʱ����·�) С�ڵ���0���� (��ݳ�12��һ����12����)
        //res_e(Result_End)ͬԭ��res_s
        for (int j = 0; j < k; j++) {
            if (sub_list[i].mag_num == mag_list[j].mag_num) {
                //printf("*-----------��ѯ�ɹ�-------------*\n");
                if (res_s <= 0 && res_e <=0) {
                    //printf("*-----------��Ч-------------*\n");
                    sum[j] += 1;
                    break;
                }
            }
        }
    }


    int temp;                                       //��Ϊ�ڿ����붩��������һһ��Ӧ�Ĺ�ϵ
    struct magazine temp_m;                         //����ʹ��ð�ݷ����ڶ����������������ͬʱ���ı��ڿ��ŵ�˳��
    for (int i = 0; i < MAX_MAG - 1; i++)
        for (int j = 0; j < MAX_MAG - 1 - i; j++)
            if (sum[j] < sum[j + 1]) {
                temp = sum[j];
                sum[j] = sum[j + 1];
                sum[j + 1] = temp;

                temp_m = mag_list[j];
                mag_list[j]=mag_list[j+1];
                mag_list[j+1] = temp_m;
            }


    for (int i = 0; i < k; i++) {
        printf("�ڿ���:ISSN-%lld �ڿ���:%s ��Ч���ķ���:%d\n", mag_list[i].mag_num, mag_list[i].mag_name, sum[i]);
    }

}

void overdue_sub(){                 //ͳ�ƽ���û�ж��ĵ��û�
    int y,m,d;
    now_time(&y,&m,&d);
    overdue_sub_del();
    int k = 0;
    sub_over_date = fopen("Reader_over.txt", "r");
    printf("����û�ж��ĵĶ�����:\n");
    while (!feof(sub_over_date)) {
        fscanf_s(sub_over_date, "%s%s%lld%lld%d%d%d%d%d%d%d\n", sub_list[k].name, 20, sub_list[k].address, 40,
                 &sub_list[k].phone_num, &sub_list[k].mag_num,
                 &sub_list[k].sub_n, &sub_list[k].start_date.year, &sub_list[k].start_date.month,
                 &sub_list[k].end_date.year,
                 &sub_list[k].end_date.month,
                 &sub_list[k].date_sum, &sub_list[k].price);
        if (sub_list[k].phone_num != 0 && sub_list[k].end_date.year < 1900+y) {
            printf("\n ����:%-10s��ַ:%-20s�绰����:%-12lld�ڿ���:%-16lld���ķ���:%-5d������:%d��%d�� ֹ������:%d��%d�� �ܶ��ķ���:%-4d���:%-4d",
                   sub_list[k].name, sub_list[k].address,
                   sub_list[k].phone_num, sub_list[k].mag_num,
                   sub_list[k].sub_n, sub_list[k].start_date.year, sub_list[k].start_date.month,
                   sub_list[k].end_date.year,
                   sub_list[k].end_date.month,
                   sub_list[k].date_sum, sub_list[k].price);
            k += 1;
        }
    }
    if (k == 0)
        printf("\n����û��û�����ڿ����û�\n");
    fclose(sub);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

//�ڿ��༭
int mag_read() {            //��ѯ��ǰMAG.txt���е��ڿ�
    int k = 0;
    mag = fopen("MAG.txt", "r");
    while (!feof(mag)) {
        fscanf_s(mag, "%lld%s%s%d", &mag_list[k].mag_num, mag_list[k].mag_name, 60, mag_list[k].mag_n, 10,
                 &mag_list[k].mag_price);
        if (mag_list[k].mag_num != 0) {
            printf("\n�ڿ���:ISSN-%-20lld�ڿ���:%-40s����:%-10s����:%-10d", mag_list[k].mag_num, mag_list[k].mag_name,
                   mag_list[k].mag_n, mag_list[k].mag_price);
            k += 1;
        }
    }
    if (k == 0)
        printf("\n�����ڿ����������ڿ�\n");
    fclose(mag);
    sys_pause();
    return k;
}

void mag_add() {
    long long int a;//�����ڿ�
    int m = 0, n, mag_nn, y;
    for (int i = 0; i < MAX_MAG; i++) {
        printf("\n������Ҫ�����ڿ�����Ϣ\n");
        printf("�������ڿ���:");
        scanf_s("%lld", &a);
        y = mag_find_sim(a);
        if (y == 1) {
            printf("\n���ڿ��Ѿ�����\n");
            printf("����������Ϣ������1���˳�������������������:");
            scanf_s("%d", &n);
            printf("\n\n");
            if (n == 1)
                continue;
            else
                break;
        } else if (y == 2) {
            mag_list[i].mag_num = a;
        }
        /////////////////////////////////
        printf("�������ڿ�����:");
        scanf_s("%s", &mag_list[i].mag_name, 60);
        /////////////////////////////////
        printf("�������ڿ�����:");
        scanf_s("%d", &mag_nn);

        switch (mag_nn) {
            case 1:
                strcpy(mag_list[i].mag_n, "�¿�");
                break;
            case 2:
                strcpy(mag_list[i].mag_n, "���¿�");
                break;
            case 4:
                strcpy(mag_list[i].mag_n, "�ܿ�");
                break;
            default:
                printf("���������Ϣ�����⣬������1(monthly-�¿�),2(semimonthly-���¿�),4(weekly-�ܿ�)�е�һ����");
        }
        /////////////////////////////////
        printf("�������ڿ�����:");
        scanf_s("%d", &mag_list[i].mag_price);

        m += 1;

        printf("�ٴ�������Ϣ������1���˳�������������������:");
        scanf_s("%d", &n);
        printf("\n\n");
        if (n == 1)
            continue;
        else
            break;
    }
    mag = fopen("MAG.txt", "a+");
    for (int k = 0; k < m; k++) {
        fprintf(mag, "%20lld%40s%10s%10d\n", mag_list[k].mag_num, mag_list[k].mag_name, mag_list[k].mag_n,
                mag_list[k].mag_price);
    }
    fclose(mag);
}

void mag_del() {                    //�ڿ�ɾ��
    int sum = 0, k = 0;
    long long int mag_del;
    mag = fopen("MAG.txt", "r");
    mag_temp = fopen("MAG_temp.txt", "w");
    while (!feof(mag)) {
        fscanf_s(mag, "%lld%s%s%d", &mag_list[k].mag_num, mag_list[k].mag_name, 60, mag_list[k].mag_n, 10,
                 &mag_list[k].mag_price);
        if (mag_list[k].mag_num != 0) {
            printf("�ڿ���:ISSN-%lld\t\t\t�ڿ���:%s\t\t\t����:%s\t����:%d\n", mag_list[k].mag_num, mag_list[k].mag_name,
                   mag_list[k].mag_n, mag_list[k].mag_price);
            k += 1;
        }
    }
    /////////////////////////////////�����ԭMAG.txt����Ҫɾ�����ڿ�ȫ�������mag_temp.txt�У�Ȼ��ɾ��MAG.txt,�ٰ�mag_temp.txt������ΪMAG.txt,���ɾ����
    printf("\n��������Ҫɾ���ڿ����ڿ���:");
    scanf_s("%lld", &mag_del);
    for (int j = 0; j < k; j++) {
        if (mag_del != mag_list[j].mag_num) {
            fprintf(mag_temp, "%20lld%40s%10s%10d\n", mag_list[j].mag_num, mag_list[j].mag_name, mag_list[j].mag_n,
                    mag_list[j].mag_price);
            sum += 1;
        }
    }
    fclose(mag);
    fclose(mag_temp);
    if (sum == k)
        printf("\n�޴��ڿ�\n");
    else {
        char new[] = "MAG.txt";
        char old[] = "MAG_temp.txt";
        FILE_change(old, new);    //FILE_change�����������������ļ��Ĳ���
    }
    sys_pause();
}

int mag_find_sim(long long int a) {                            //Ѱ��������ڿ����Ƿ��Ѿ���MAG.txt�ļ���
    int i = 0, m = 0;
    struct magazine temp[MAX_MAG];
    mag = fopen("MAG.txt", "r");
    while (!feof(mag)) {
        fscanf_s(mag, "%lld%s%s%d", &temp[m].mag_num, temp[m].mag_name, 60, temp[m].mag_n, 10,
                 &temp[m].mag_price);
        m += 1;
    }
    for (int k = 0; k < m; k++) {
        if (a == temp[k].mag_num) {
            i = 1;
            break;
        } else
            i = 2;
    }
    fclose(mag);
    return i;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
int menu() {
    int y, m, d;
    int n, result;
    now_time(&y, &m, &d);
    printf("\n                                              ������%d��%d��%d��\n", 1900 + y, m, d);
    printf("\t\t\t\t*--------------------�˵�--------------------*\n");
    printf("\t\t\t\t                  1.�ڿ��༭                  \n");
    printf("\t\t\t\t                  2.�����༭                  \n");
    printf("\t\t\t\t                  3.�˳�ϵͳ                  \n");
    printf("\t\t\t\t*-------------------------------------------*\n");
    printf("\n��ѡ������Ҫ�ķ���:");
    scanf_s("%d", &n);

    if (n == 1) {
        printf("\n\n\n\n");
        printf("\t\t\t\t*-----------------�ڿ��༭�˵�-----------------*\n");
        printf("\t\t\t\t                  1.��ѯ�����ڿ�                     \n");
        printf("\t\t\t\t                  2.�����ڿ�                       \n");
        printf("\t\t\t\t                  3.ɾ���ڿ�                       \n");
        printf("\t\t\t\t                  4.ͳ���ڿ���Ч�ܶ�����               \n");
        printf("\t\t\t\t                  5.��ѯʱ���ڸ��ڿ�������            \n");
        printf("\t\t\t\t                  6.�������˵�                      \n");
        printf("\t\t\t\t*---------------------------------------------*\n");
        printf("\n��ѡ������Ҫ�ķ���:");
        scanf_s("%d", &n);
        if (n == 1)                     //�ڿ��༭�˵�
            result = 11;
        else if (n == 2)
            result = 12;
        else if (n == 3)
            result = 13;
        else if (n == 4)
            result = 14;
        else if (n == 5)
            result = 15;
        else if  (n == 6)
            result = 16;
        else
            result = 0;
    } else if (n == 2) {
        printf("\n\n\n\n");
        printf("\t\t\t\t*--------------------�����༭�˵�--------------------*\n");
        printf("\t\t\t\t                    1.��ѯ���ж���                     \n");
        printf("\t\t\t\t                    2.��������                        \n");
        printf("\t\t\t\t                    3.������ڶ���                     \n");
        printf("\t\t\t\t                    4.ͳ����Ч����                     \n");
        printf("\t\t\t\t                    5.ͳ�ƽ���δ���Ķ���                \n");
        printf("\t\t\t\t                    6.�������˵�                      \n");
        printf("\t\t\t\t*---------------------------------------------------*\n");
        printf("\n��ѡ������Ҫ�ķ���:");
        scanf_s("%d", &n);//�����༭�˵�
        if (n == 1)
            result = 21;
        else if (n == 2)
            result = 22;
        else if (n == 3)
            result = 23;
        else if (n == 4)
            result = 24;
        else if (n == 5)
            result = 25;
        else if (n == 6)
            result = 26;
        else
            result = 0;
    }
    else if (n == 3)
        result = 0;
    else {
        printf("������������,������1-3֮�����\n");
        result = 26;
    }
    return result;
}

int main() {
    int result_menu = 1;
    while (result_menu) {
        result_menu = menu();
        switch (result_menu) {
            case 0:
                printf("\nϵͳ���˳�\n");
                break;
            case 11:
                mag_read();
                break;
            case 12:
                mag_add();
                break;
            case 13:
                mag_del();
                break;
            case 14:
                sub_mag_sum();
                break;
            case 15:
                sub_mag_sum_date();
                break;
            case 16:
                continue;
            case 21:
                sub_read();
                break;
            case 22:
                sub_add();
                break;
            case 23:
                overdue_sub_del();
                break;
            case 24:
                sub_sum();
                break;
            case 25:
                overdue_sub();
                break;
            case 26:
                continue;
            default:
                printf("\nû�д�ѡ��\n");
                break;

        }
    }

    return 0;
}