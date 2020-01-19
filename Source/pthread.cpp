#include "pth.h"
#include "tcp.h"
#include <arpa/inet.h>
#include "server.h"

/*
author:zhouzj
file:开辟线程并传入参数
*/

//当前连接数量：0
int Connected = 0;

//开辟单独的聊天线程
void* chatwithme(void *argv)
{
    //变量申明
    char str[4096];
    int n;
    char  buff[4096];
    time_t timep;
    struct tm *p;

    client *user=(client *)argv; //客户端信息录入线程
    printf("IP:%s  %s\n",inet_ntoa(user->addr.sin_addr),user->name); //打印客户端的用户名
    //循环接受消息
    while(1){
        //n = recv(*user->connfd, buff, MAXLINE, 0);        //读取传输信息
        n = read(user->connfd, buff, MAXLINE);    //读取传输信息
        //判断信息长度
        if(n!=0){
            time (&timep);          //获取当前计算机时间
            p=gmtime(&timep);
            //加上字符串结尾
            buff[n] = '\0';
            //若信息首字符为‘0’则断开连接
            if(buff[0]=='0'){
                printf("%s has cut off\n",user->name);
                break;
            }
            //打印控制台信息
            sprintf(str,"User:%s Time:%d:%d:%02d: Message:%s",user->name,p->tm_hour,p->tm_min,p->tm_sec, buff);
            printf("%s",str);

            // //广播输入的信息
            // int num=0;
            // for(int i=0;i<9;i++){
            //     if(user[i].online>=0){
            //         write(user[i].connfd,buff,strlen(buff));
            //         num++;
            //     }
            // }
            
            user->m.lock();
            user->messagehandle(buff);
            user->m.unlock();

            //打印发送的数量
            //sprintf(str,"Sendnum：%d",num);
            //write(user->connfd,str,strlen(str));
        }
    }
    //断开后
    user->online=-1;
    Connected--;
    close(user->connfd);
    user->connfd=0;
    return 0;
}
void* Ctrl(void *argv){
    Console();
}

//测试函数，指针为空，请使用全局变量
void* tcp_test(void *argv){
    thread_test();
    return 0;
}
//测试函数，不设参数，请使用全局变量
void thread_test(void){
    cout << "test sth" << endl;
}
// 线程的运行函数(测试用)
void* say_hello(void *argv)
{
    (char*)argv;
    char str[10];
    
    memcpy(str, (char *)argv, sizeof(char)*10);

    cout << str << endl;
    cout << "Hello Runoob！" << endl;
    return 0;
}


