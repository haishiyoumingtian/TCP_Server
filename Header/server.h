#ifndef _server_H_
#define _server_H_

#include "stdio.h"
#include "stdlib.h"
#include "sys.h"
#include "tcp.h"
#include "mutex"

using namespace std;

#define MAXCLIENT 10

//用户类
class client{
private:

public:
    char name[10];
    struct sockaddr_in addr;
    mutex m;
    int online;
    int connfd;
    class client *pre;
    class client *nxt;
    client(void){
        connfd=0;
        online = -1;
    }
    void messagehandle(char *str);

protected:
};

extern pthread_t tids[];
extern class client user[];
extern void Console(void);
extern int server_config(void);

#endif