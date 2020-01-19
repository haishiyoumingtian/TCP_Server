#ifndef _tcp_H_
#define _tcp_H_

#include    <stdio.h>
#include    <stdlib.h>
#include    <string.h>
#include    <errno.h>
#include    <sys/types.h>
#include    <sys/socket.h>
#include    <netinet/in.h>
#include    <unistd.h>
#include    "server.h"
#include     "sys.h"

#define MAXLINE 4096

int tcp_config(void);

#endif // !_tcp_H_



