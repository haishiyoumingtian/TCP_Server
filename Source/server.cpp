#include "iostream"
#include "server.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

using namespace std;

/*
author：zhouzj
file：控制台线程和客户端处理线程
*/


//最大线程数量：10
pthread_t tids[MAXCLIENT];

//最大客户端数量：10
class client user[MAXCLIENT];


void Console(void){
    char str[10];
    while(1){
        printf(">");
        scanf("%s",str);
        if(strcmp(str,"help")==0){
            cout << "help:" << endl;
            cout << "--------------------------------" << endl;
            cout << "|cmd  |function                 |" << endl;
            cout << "--------------------------------" << endl;
            cout << "|help |Help                     |" << endl;
            cout << "|user |Print number of users    |" << endl;
            cout << "|cut  |Disconnect a user(cut 1) |" << endl;
            cout << "|log  |view log                 |" << endl;
            cout << "|list |View user list           |" << endl;
            cout << "|close|close                    |" << endl;
            cout << "--------------------------------" << endl;
        }
        else if(strcmp(str,"user")==0){
            cout << "user:" << endl;
            cout << "The number of users currently online is:"<< Connected << endl;
            for(int i=0;i<=9;i++){
                printf("%d:%d\n",i,user[i].online);
            }
        }
        else if(strcmp(str,"cut")==0){
            cout << "cut:" << endl;
        }
        else if(strcmp(str,"log")==0){
            cout << "log:" << endl;
        }
        else if(strcmp(str,"list")==0){
            cout << "list:" << endl;
            int n=0;
            for(int i=0;i<=9;i++){
                if(user[i].online==1){
                    n++;
                    cout << n << ":" << user[i].name << "    " << "connfd:" << user[i].connfd << endl; 
                }
            }
        }
        else if(strcmp(str,"close")==0){
            exit(1);
        }
        else{
            cout << "Error instruction!" << endl;
        }

    }
}
// 消息处理函数（后期要加互斥）
void client::messagehandle(char *str){
    //广播输入的信息
    int num=0;
    for(int i=0;i<9;i++){
        if(user[i].online>=0){
            write(user[i].connfd,str,strlen(str));
            num++;
        }
    }
}