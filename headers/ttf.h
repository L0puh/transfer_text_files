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

#include <fstream>
#include <thread>
#include <mutex>
#include <vector>

#define ERROR 1
#define OK 0

std::string const client_dir = "files/client_files/";
std::string const server_dir = "files/server_files/";

struct connection_t  {
            int id;
            int current_socket;
};

class Net {
    protected: 
        std::mutex mtx;
        int sum_size=0;
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
        int index=0;
        int sockfd_client;
        struct sockaddr_in their_addr;
        socklen_t their_addr_size = sizeof(their_addr);
        std::vector<connection_t> connections;

    private:
        void handle_client(int current_id, int current_socket);
        char* recv_data(int current_socket);
        int recv_data_size(int current_socket);

    public:
        std::vector<connection_t> get_connections();
        connection_t get_connection(int id);

    public:
        void start_server();
        void accept_connection();
        int save_file(int current_socket);
        int send_state(int current_socket, int state); 
        void close_connection(int current_id, int current_socket);

    public:
        Server();
        ~Server();

};

class Client : public Net {
    private:
        std::string get_file(std::string file_name);
    public:
        int recv_state();
        int send_file_size(int file_size);
        int send_file(std::string file_name);
        int send_file_name(std::string file_name);
    public:
        Client();
        ~Client();
};

#endif
