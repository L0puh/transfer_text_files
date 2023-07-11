#include "../headers/ttf.h"
#include "../headers/net_info.h"
#include <sys/socket.h>

Client::Client(){
   printiferror(connect(sockfd, servinfo->ai_addr, servinfo->ai_addrlen));
}
Client::~Client(){
    close(sockfd);
    exit(1);
}
