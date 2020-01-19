#ifndef _pth_H_
#define _pth_H_

#include <iostream>
#include <time.h>
#include <string.h>
#include <string>
#include <pthread.h>
#include <sys.h>

using namespace std;

extern int Connected;

extern void* say_hello(void * argv);
extern void* tcp_test(void *argv);
extern void* chatwithme(void *argv);
extern void thread_test(void);
extern void* Ctrl(void *argv);


#endif // !_pthread_H_
#define _pth_H_

    // 定义线程的 id 变量，多个变量使用数组
    //pthread_t tids[NUM_THREADS];
    
    // for(int i = 0; i < NUM_THREADS; ++i)
    // {
    //     //参数依次是：创建的线程id，线程参数，调用的函数，传入的函数参数
    //     int ret = pthread_create(&tids[i], NULL, say_hello, NULL);
    //     if (ret != 0)
    //     {
    //        cout << "pthread_create error: error_code=" << ret << endl;
    //     }
    // }
    //等各个线程退出后，进程才结束，否则进程强制结束了，线程可能还没反应过来；
    //pthread_exit(NULL);
