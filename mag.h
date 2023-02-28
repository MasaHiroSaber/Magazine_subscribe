#ifndef MAGAZINE_SUBSCRIBE_MAG_H
#define MAGAZINE_SUBSCRIBE_MAG_H
#define _CRT_SECURE_NO_WARNINGS  //在CLion中使用fopen与会警告，此定义消除警告
#define MAX_MAG 200
#define MAX_SUB 2000

///////////////////////////////////////////////////////////////////////////////////////////////////


#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>


///////////////////////////////////////////////////////////////////////////////////////////////////


struct magazine {
    long long int mag_num;           //期刊号
    char mag_name[60];      //期刊名
    char mag_n[10];              //期刊种类（月刊，半月刊，周刊）
    int mag_price;          //期刊单价
} mag_list[MAX_MAG];


struct sub_date {
    int year;
    int month;
};


struct subscribe {
    char name[20];
    char address[40];
    long long int phone_num;
    long long int mag_num;
    int sub_n;
    struct sub_date start_date;
    struct sub_date end_date;
    int date_sum;
    int price;
} sub_list[MAX_SUB];



#endif //MAGAZINE_SUBSCRIBE_MAG_H
