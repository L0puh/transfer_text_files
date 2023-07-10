#ifndef TTF_H
#define TTF_H

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
    public: 
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

};
class Client : public Net {

};

#endif
