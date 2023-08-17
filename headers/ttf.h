#ifndef TTF_H
#define TTF_H

#include <cstdint>
#include <cstdlib>
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

typedef uint8_t crc;

struct connection_t  {
    int id;
    int current_socket;
};


class Net {
    protected: 
        std::vector<crc> table;
        std::mutex mtx;
        int sum_size=0;
        int sockfd;
        struct addrinfo hints, *servinfo;
        std::string server_dir;
        std::string client_dir;        
    private:
        std::string get_config_client();
        std::string get_config_server();
    public: 
        Net();
        ~Net();
    protected:
        void init_crc();
        void send_crc(std::string message, int sockfd);
        crc get_crc(uint8_t msg, uint8_t rem);
        void check_crc(int sockfd);

    protected:
        void init_hints();
        void printiferror(int res, int type=0);
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
