#include "../headers/ttf.h"
#include "../headers/net_info.h"

Server::Server(){
    printiferror(bind(sockfd, servinfo->ai_addr, servinfo->ai_addrlen));
    freeaddrinfo(servinfo);
    
    printiferror(listen(sockfd, BACKLOG));
    printf("wait for connection...\n");
    while (true) {
        sockfd_client = accept(sockfd, (sockaddr *)&their_addr, &their_addr_size);
        printiferror(sockfd_client);
        printf("new connection\n");
    }
}
Server::~Server(){
    close(sockfd_client);
    exit(1);
}
