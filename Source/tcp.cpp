#include "iostream"
#include "tcp.h"

using namespace std;

/*
author:zhouzj
file:初始化服务监听套接字，并且作为主程序循环等待accept新的客户端连接到服务器。
*/

//tcp运行函数（简易版本）
int tcp_config(void){
    int  sockfd, connfd;
    struct sockaddr_in  servaddr;
    struct sockaddr_in addr; //client's
    char  buff[4096];
    int  n;
    int sin_size;
    int opt;
    int toconnect=-1;

    //创建一个新的套接字
    if( (sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP )) == -1 ){
        printf("create socket error: %s(errno: %d)\n",strerror(errno),errno);
        return 0;
    }
    cout << "socket..." << endl;

    opt = SO_REUSEADDR;
    setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));

    //设置本机的地址
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(6666);
    //bind()
    if( bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1){
        printf("bind socket error: %s(errno: %d)\n",strerror(errno),errno);
        return 0;
    }
    cout << "bind....." << endl;

    //listen()
    if( listen(sockfd, 10) == -1){
        printf("listen socket error: %s(errno: %d)\n",strerror(errno),errno);
        return 0;
    }
    cout << "listen..." << endl;

    //等待客户机的连接秦请求
    printf("======waiting for client's request======\n");

    while(1){
        //查询可用连接端
        for(int i=0;i<=9;i++){
            if(user[i].online<0){
                toconnect=i;
                break;
            }
        }

        //等待连接后接受
        if( (user[toconnect].connfd = accept(sockfd, (struct sockaddr*)&addr, (socklen_t*)&sin_size)) == -1){
            printf("accept socket error: %s(errno: %d)",strerror(errno),errno);
            continue;
        }

        //在可用连接端创建用户
        printf("Create user at No.%d\n",toconnect);

        //创建一个用户与之对应
        memcpy((void*)&user[toconnect].addr,&addr,sizeof(addr));
        user[toconnect].online=1;
        //获取用户名
        n = read(user[toconnect].connfd, buff, MAXLINE);
        buff[n] = '\0';
        strcpy(user[toconnect].name,buff);

        //开辟一个线程传入用户参数
        int ret = pthread_create(&tids[toconnect], NULL, chatwithme, (void*)&user[toconnect]);
        if (ret != 0)
        {
            cout << "pthread_create error: error_code=" << ret << endl;
        }
        
        Connected++;
        //pthread_join(tids[toconnect],NULL); 

        //用户数量到达上限
        if(Connected==MAXCLIENT){
            cout << "用户数量到达上限" << endl;
            while(1){
                if(Connected<MAXCLIENT){
                    break;
                }
            }
        }
    }
    close(sockfd);
}