#ifndef TTF_H
#define TTF_H

#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h> //close

#include <string>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h> //stderr
#include <cstring> //memset 

class Net {
    protected: 
        int sockfd;
        struct addrinfo hints, *servinfo;
    public: 
        Net();
        ~Net();
    public:
        void printiferror(int res, int type=0);
    protected:
        void init_hints();
};
class Server : public Net {
    private:
        int sockfd_client;
        struct sockaddr_in their_addr;
        socklen_t their_addr_size = sizeof(their_addr);
    public:
        Server();
        ~Server();

};
class Client : public Net {

};

#endif
