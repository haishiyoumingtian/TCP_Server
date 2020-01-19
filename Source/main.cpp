#include "iostream"
#include "sys.h"
#include "server.h"

using namespace std;

int main()
{
    //创建套接字
    int sockfd;
    pthread_t Ctr;
    //头报文
    cout << "A test for threads and TCP" << endl;

    //开辟一个线程作为控制台程序
    int ret = pthread_create(&Ctr, NULL, Ctrl, (void*)NULL);
    if (ret != 0)
    {
         cout << "pthread_create error: error_code=" << ret << endl;
    }

    //进入TCP函数
    sockfd=tcp_config();

    //server_config();

    //保留线程到线程运行结束
    pthread_exit(NULL);

}