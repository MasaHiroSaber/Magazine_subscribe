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
int now_time(int *y, int *m, int *d) {  //获取当前时间

    time_t timep;               //time_t time(time_t *seconds)
    time(&timep);

    struct tm *p;               //gmtime获得的是一个由年月日时分秒组成的结构体
    p = gmtime(&timep);
    *y = p->tm_year;
    *m = p->tm_mon;
    *d = p->tm_mday;
    return 0;
}

void sys_pause() {         //  按任意键继续...
    printf("\n\n按任意键继续...");
    _getch();
}

void FILE_change(char Old_filename[], char New_filename[]) {        //文件的删除与重命名(比较原始的方法删除文件里的内容)
    int del_ret = remove(New_filename);  //删除
    rename(Old_filename, New_filename);  //重命名
    if (del_ret == 0) {
        printf("\n成功\n");
    } else
        printf("\n失败\n");
}
///////////////////////////////////////////////////////////////////////////////////////////////////

//订户编辑
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
            printf("\n 姓名:%-10s地址:%-20s电话号码:%-12lld期刊号:%-16lld订阅份数:%-5d起订年月:%d年%d月 止订年月:%d年%d月 总订阅份数:%-4d金额:%-4d",
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
        printf("\n文件内暂无订户\n");
    fclose(sub);
    return k;
}

void sub_add() {
    int n, k = 0;

    for (int i = 0; i < MAX_SUB; i++) {
        mag = fopen("MAG.txt", "r");
        int j = 0;
        printf("\n*------请输入新订户信息------*\n");

        printf("\n请输入订户姓名:");
        scanf_s("%s", &sub_list[i].name, 20);
        /////////////////////////////////
        printf("\n请输入订户地址:");
        scanf_s("%s", &sub_list[i].address, 40);
        /////////////////////////////////
        printf("\n请输入订户电话号码:");
        scanf_s("%lld", &sub_list[i].phone_num);
        /////////////////////////////////
        printf("\n请输入订户订阅期刊的期刊号:");
        scanf_s("%lld", &sub_list[i].mag_num);
        /////////////////////////////////
        printf("\n请输入订户的订阅份数:");
        scanf_s("%d", &sub_list[i].sub_n);
        /////////////////////////////////
        printf("\n请输入订户的起订年月:");
        scanf_s("%d.%d", &sub_list[i].start_date.year, &sub_list[i].start_date.month);
        /////////////////////////////////
        printf("\n请输入订户的止订年月:");
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
                printf("\n----------------------------------------------找到书籍----------------------------------------------\n");
                res = 1;
                if (strcmp(mag_list[j].mag_n, "月刊") == 0)
                    cmp = 1;
                else if (strcmp(mag_list[j].mag_n, "半月刊") == 0)
                    cmp = 2;
                else if (strcmp(mag_list[j].mag_n, "周刊") == 0)
                    cmp = 4;
                p = &sub_list[i].date_sum;
                *p = ((sub_list[i].end_date.year - sub_list[i].start_date.year) * 12 +     //计算一共订阅的份数
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
            printf("\n您输入的期刊号有误\n");
        printf("再次增加信息请输入1，退出请输入其他任意数字:");
        scanf_s("%d", &n);
        printf("\n\n");

        if (n == 1)
            continue;
        else
            break;
    }
    sys_pause();
}

void overdue_sub_del() {    //now_time()函数获取系统当前时间，判断订户是否已经过期
    int y, m, d;            //清理已经过期的订户，将过期的订户信息储存到Reader_over.txt中
    int k = 0;              //将未过期的订户信息储存到Reader_temp.txt
    now_time(&y, &m, &d);   //然后删除Reader.txt,重命名Reader_temp,完成过期订户的删除
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
            printf("\n检测到信息有误，停止工作\n");
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

void sub_sum() {            //当前有效订户查询
    int sum;                //只需要调用now_time(),overdue_sub_del(),sub_read()三个函数即可实现功能
    int y, m, d;
    now_time(&y, &m, &d);
    overdue_sub_del();
    printf("\n截止%d年%d月%d日,有效的订户为:\n", y, m, d);
    sum = sub_read();
    printf("\n合计%d户\n", sum);
    sys_pause();
}

void sub_mag_sum() {        //统计各个期刊的有效总订阅数
    int k = 0;              //总订阅数为：总订阅月数 * 订阅份数 * 期刊种类K (K=1,2,4;月刊，半月刊，周刊)
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

    int sum[MAX_MAG] = {0}; //存放各个期刊的总订阅数
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
        printf("期刊号:ISSN-%lld 期刊名:%s 有效订阅份数:%d\n", mag_list[i].mag_num, mag_list[i].mag_name, sum[i]);
    }

}

void sub_mag_sum_date() {       //查询某时间段内各个期刊的订阅人数
    int s_year, s_month;        //只要期刊订阅时间在输入的时间段内就符合要求
    int e_year, e_month;
    int k = 0;
    overdue_sub_del();
    printf("请输入你要查询时间段的起始日期XXXX.X:");
    scanf_s("%d.%d", &s_year, &s_month);
    printf("请输入你要查询时间段的终止日期XXXX.X:");
    scanf_s("%d.%d", &e_year, &e_month);
    if(s_year > e_year)
        printf("\n您输入的时间有误\n");
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
        //因为要求订阅的年月都在输入的时间段内
        //所以res_s(res_s即为Result_Start)为(订阅年份 - 时间段年份）*12 - (订阅月份 - 时间段月份) 小于等于0即可 (年份乘12是一年有12个月)
        //res_e(Result_End)同原理res_s
        for (int j = 0; j < k; j++) {
            if (sub_list[i].mag_num == mag_list[j].mag_num) {
                //printf("*-----------查询成功-------------*\n");
                if (res_s <= 0 && res_e <=0) {
                    //printf("*-----------有效-------------*\n");
                    sum[j] += 1;
                    break;
                }
            }
        }
    }


    int temp;                                       //因为期刊号与订阅人数是一一对应的关系
    struct magazine temp_m;                         //所以使用冒泡法对期订阅人数进行排序的同时，改变期刊号的顺序
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
        printf("期刊号:ISSN-%lld 期刊名:%s 有效订阅份数:%d\n", mag_list[i].mag_num, mag_list[i].mag_name, sum[i]);
    }

}

void overdue_sub(){                 //统计今年没有订阅的用户
    int y,m,d;
    now_time(&y,&m,&d);
    overdue_sub_del();
    int k = 0;
    sub_over_date = fopen("Reader_over.txt", "r");
    printf("今年没有订阅的订户有:\n");
    while (!feof(sub_over_date)) {
        fscanf_s(sub_over_date, "%s%s%lld%lld%d%d%d%d%d%d%d\n", sub_list[k].name, 20, sub_list[k].address, 40,
                 &sub_list[k].phone_num, &sub_list[k].mag_num,
                 &sub_list[k].sub_n, &sub_list[k].start_date.year, &sub_list[k].start_date.month,
                 &sub_list[k].end_date.year,
                 &sub_list[k].end_date.month,
                 &sub_list[k].date_sum, &sub_list[k].price);
        if (sub_list[k].phone_num != 0 && sub_list[k].end_date.year < 1900+y) {
            printf("\n 姓名:%-10s地址:%-20s电话号码:%-12lld期刊号:%-16lld订阅份数:%-5d起订年月:%d年%d月 止订年月:%d年%d月 总订阅份数:%-4d金额:%-4d",
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
        printf("\n今年没有没订阅期刊的用户\n");
    fclose(sub);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

//期刊编辑
int mag_read() {            //查询当前MAG.txt内有的期刊
    int k = 0;
    mag = fopen("MAG.txt", "r");
    while (!feof(mag)) {
        fscanf_s(mag, "%lld%s%s%d", &mag_list[k].mag_num, mag_list[k].mag_name, 60, mag_list[k].mag_n, 10,
                 &mag_list[k].mag_price);
        if (mag_list[k].mag_num != 0) {
            printf("\n期刊号:ISSN-%-20lld期刊名:%-40s类型:%-10s单价:%-10d", mag_list[k].mag_num, mag_list[k].mag_name,
                   mag_list[k].mag_n, mag_list[k].mag_price);
            k += 1;
        }
    }
    if (k == 0)
        printf("\n暂无期刊，请新增期刊\n");
    fclose(mag);
    sys_pause();
    return k;
}

void mag_add() {
    long long int a;//增加期刊
    int m = 0, n, mag_nn, y;
    for (int i = 0; i < MAX_MAG; i++) {
        printf("\n请输入要新增期刊的信息\n");
        printf("请输入期刊号:");
        scanf_s("%lld", &a);
        y = mag_find_sim(a);
        if (y == 1) {
            printf("\n该期刊已经存在\n");
            printf("重新增加信息请输入1，退出请输入其他任意数字:");
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
        printf("请输入期刊名称:");
        scanf_s("%s", &mag_list[i].mag_name, 60);
        /////////////////////////////////
        printf("请输入期刊类型:");
        scanf_s("%d", &mag_nn);

        switch (mag_nn) {
            case 1:
                strcpy(mag_list[i].mag_n, "月刊");
                break;
            case 2:
                strcpy(mag_list[i].mag_n, "半月刊");
                break;
            case 4:
                strcpy(mag_list[i].mag_n, "周刊");
                break;
            default:
                printf("您输入的信息有问题，请输入1(monthly-月刊),2(semimonthly-半月刊),4(weekly-周刊)中的一个数");
        }
        /////////////////////////////////
        printf("请输入期刊单价:");
        scanf_s("%d", &mag_list[i].mag_price);

        m += 1;

        printf("再次增加信息请输入1，退出请输入其他任意数字:");
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

void mag_del() {                    //期刊删除
    int sum = 0, k = 0;
    long long int mag_del;
    mag = fopen("MAG.txt", "r");
    mag_temp = fopen("MAG_temp.txt", "w");
    while (!feof(mag)) {
        fscanf_s(mag, "%lld%s%s%d", &mag_list[k].mag_num, mag_list[k].mag_name, 60, mag_list[k].mag_n, 10,
                 &mag_list[k].mag_price);
        if (mag_list[k].mag_num != 0) {
            printf("期刊号:ISSN-%lld\t\t\t期刊名:%s\t\t\t类型:%s\t单价:%d\n", mag_list[k].mag_num, mag_list[k].mag_name,
                   mag_list[k].mag_n, mag_list[k].mag_price);
            k += 1;
        }
    }
    /////////////////////////////////下面把原MAG.txt除了要删除的期刊全部输出到mag_temp.txt中，然后删除MAG.txt,再把mag_temp.txt重命名为MAG.txt,完成删除。
    printf("\n请输入需要删除期刊的期刊号:");
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
        printf("\n无此期刊\n");
    else {
        char new[] = "MAG.txt";
        char old[] = "MAG_temp.txt";
        FILE_change(old, new);    //FILE_change函数完成上面对两个文件的操作
    }
    sys_pause();
}

int mag_find_sim(long long int a) {                            //寻找输入的期刊号是否已经在MAG.txt文件里
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
    printf("\n                                              今天是%d年%d月%d日\n", 1900 + y, m, d);
    printf("\t\t\t\t*--------------------菜单--------------------*\n");
    printf("\t\t\t\t                  1.期刊编辑                  \n");
    printf("\t\t\t\t                  2.订户编辑                  \n");
    printf("\t\t\t\t                  3.退出系统                  \n");
    printf("\t\t\t\t*-------------------------------------------*\n");
    printf("\n请选择你需要的服务:");
    scanf_s("%d", &n);

    if (n == 1) {
        printf("\n\n\n\n");
        printf("\t\t\t\t*-----------------期刊编辑菜单-----------------*\n");
        printf("\t\t\t\t                  1.查询现有期刊                     \n");
        printf("\t\t\t\t                  2.新增期刊                       \n");
        printf("\t\t\t\t                  3.删除期刊                       \n");
        printf("\t\t\t\t                  4.统计期刊有效总订阅数               \n");
        printf("\t\t\t\t                  5.查询时间内各期刊订阅数            \n");
        printf("\t\t\t\t                  6.返回主菜单                      \n");
        printf("\t\t\t\t*---------------------------------------------*\n");
        printf("\n请选择你需要的服务:");
        scanf_s("%d", &n);
        if (n == 1)                     //期刊编辑菜单
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
        printf("\t\t\t\t*--------------------订户编辑菜单--------------------*\n");
        printf("\t\t\t\t                    1.查询现有订户                     \n");
        printf("\t\t\t\t                    2.新增订户                        \n");
        printf("\t\t\t\t                    3.清理过期订户                     \n");
        printf("\t\t\t\t                    4.统计有效订户                     \n");
        printf("\t\t\t\t                    5.统计今年未订阅订户                \n");
        printf("\t\t\t\t                    6.返回主菜单                      \n");
        printf("\t\t\t\t*---------------------------------------------------*\n");
        printf("\n请选择你需要的服务:");
        scanf_s("%d", &n);//订户编辑菜单
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
        printf("您的输入有误,请输入1-3之间的数\n");
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
                printf("\n系统已退出\n");
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
                printf("\n没有此选项\n");
                break;

        }
    }

    return 0;
}