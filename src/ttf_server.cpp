#include "../headers/ttf.h"
#include "../headers/net_info.h"
#include <fstream>
#include <string>
#include <sys/socket.h>

Server::Server(){
    init_crc();
}
void Server::accept_connection(){
    sockfd_client = accept(sockfd, (sockaddr *)&their_addr, &their_addr_size);
    printiferror(sockfd_client);
    printf("new connection\n");
   
    connection_t conn;
    conn.id = index++;
    conn.current_socket = sockfd_client;
    connections.push_back(conn);

    std::thread client_th(&Server::handle_client, this, conn.id, conn.current_socket);
    client_th.detach();
}


std::vector<connection_t> Server::get_connections(){
   return connections;
}
connection_t Server::get_connection(int id){
    int i=0;
    for (auto itr = connections.begin(); itr != connections.end(); itr ++){
        if (itr->id == id)
            return connections.at(i);
        i++;
    }
    connection_t conn{0, 0};
    return conn; 
}

void Server::start_server(){
    printiferror(bind(sockfd, servinfo->ai_addr, servinfo->ai_addrlen));
    freeaddrinfo(servinfo);
    
    printiferror(listen(sockfd, BACKLOG));
    printf("wait for connection...\n");
}
void Server::handle_client(int current_id, int current_socket){
    int msg_size, bytes_recv;
    while((bytes_recv = recv(current_socket, (char*)&msg_size, sizeof(int), 0)) > 0){
        save_file(current_socket);
        check_crc(current_socket);
    }
    printiferror(bytes_recv);
    close_connection(current_id, current_socket);
}

Server::~Server(){
    close(sockfd_client);
    exit(1);
}

void Server::close_connection(int current_id, int current_socket){
    {
        std::lock_guard<std::mutex> lock(mtx); 
        std::vector<connection_t>::iterator itr = connections.begin();
        while (itr != connections.end()){
            if (itr->id == current_id){
                connections.erase(itr);
                index--;
            } else 
                itr++;
        }
    }
    printf("%d: user is disconnected\n", current_id);
    close(current_socket);
}

char* Server::recv_data(int current_socket){
    int data_size = recv_data_size(current_socket);
    char* text = new char[data_size+1];
    text[data_size]='\0';
    printiferror(recv(current_socket, text, data_size, 0));
    sum_size +=data_size;
    return text;
}

int Server::recv_data_size(int current_socket){
   int file_size;
   printiferror(recv(current_socket, (char*)&file_size, sizeof(int), 0));
   return file_size;
}

int Server::save_file(int current_socket){
    char* file_name = recv_data(current_socket);
    char* text = recv_data(current_socket);
    { 
        std::lock_guard<std::mutex> lock(mtx); 
        std::ofstream file;
        file.open(server_dir + file_name);
        if (!file)
            return ERROR;
        if (text[0] == '\n'){
            std::string txt = text;
            file << txt.erase(0, 1);  
        } else 
            file << text;
       
        file.close();
        printf("recieved file %s - %d bytes \n", file_name, sum_size);
        sum_size=0;
        delete[]file_name;
        delete[]text;
    }
    send_state(current_socket, OK);
    return OK;
}
int Server::send_state(int current_socket, int state){
    printiferror(send(current_socket, (char*)&state, sizeof(int), 0)); 
    return 0;
}
