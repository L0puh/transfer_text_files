#include "../headers/ttf.h"
#include "../headers/net_info.h"

int main(int argc, char* argv[]){
    Server server;
    server.start_server();
    while (true) {
        server.accept_connection();
    }
    return 0;
}
