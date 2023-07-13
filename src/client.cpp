#include "../headers/ttf.h"
#include "../headers/net_info.h"
#include <iostream>

std::string get_file_name();

int main(int argc, char* argv[]){
    Client client;
    std::string filename = get_file_name();
    client.send_file(filename);
    client.recv_state();
    return 0;
}

std::string get_file_name(){
    std::string filename;
    printf("enter a filename:\n");
    std::getline(std::cin, filename);
    return filename;
}
