#include "../headers/ttf.h"
#include "../headers/net_info.h"
#include <cstring>

Net::Net(){
    init_hints();
    sockfd = socket(servinfo->ai_family, 
                    servinfo->ai_socktype, 
                    servinfo->ai_protocol);
    printiferror(sockfd);

}
Net::~Net(){
    close(sockfd);
    exit(1);
}

void Net::init_hints(){
    memset(&hints, 0, sizeof(this->hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    printiferror(getaddrinfo(IP, PORT, &hints, &servinfo), 1);
}


void Net::printiferror(int res, int type){
    if (res == -1) {
        switch (type){
            case 1:
                fprintf(stderr, "[-] error in getadderinfo: %s\n", gai_strerror(res));
                exit(1);
            default:
                fprintf(stderr, "[-] error: %s\n", strerror(errno));
                exit(1);
        }
    }
}
