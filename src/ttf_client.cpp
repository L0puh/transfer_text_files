#include "../headers/ttf.h"
#include "../headers/net_info.h"

Client::Client(){
   init_crc();
    printiferror(connect(sockfd, servinfo->ai_addr, servinfo->ai_addrlen));
   int msg = OK;
   send(sockfd, (char*)&msg, sizeof(int), 0);

}

Client::~Client(){
    close(sockfd);
    exit(0);
}
int Client::recv_state(){
    int state;
    printiferror(recv(sockfd,(char*)&state, sizeof(int), 0));
    if (state == ERROR) {
        printf("error in recieving data, try again\n");
    } else {
        printf("the server had recieved data\n");
    }
    return 0;
}

std::string Client::get_file(std::string file_name) {
    std::ifstream file;
    std::string line, text;
    file.open(client_dir + file_name);
    if (!file.is_open()){
        return "";
    }
    while(getline(file, line)){
        if (file.eof())
            break;
        text = text + '\n' + line;
    }
    file.close();
    return text;
}
int Client::send_file(std::string file_name){
    std::string text = get_file(file_name);
    if (text == ""){
        printf("there is no '%s' file\n", file_name.c_str());
        return ERROR;
    }

    if (send_file_name(file_name) != ERROR && send_file_size(std::size(text)) != ERROR ) {
        printiferror(send(sockfd, text.c_str(), std::size(text), 0));
        sum_size+=std::size(text);
        send_crc(text, sockfd);
        printf("file %s (%d bytes) and crc were sent\n", file_name.c_str(), sum_size);
        sum_size=0;
    }
    return OK;
}
int Client::send_file_size(int file_size){
    printiferror(send(sockfd, (char*)&file_size, sizeof(int), 0));
    return OK;
}
int Client::send_file_name(std::string file_name){
    if(send_file_size(size(file_name)) != ERROR) {
        sum_size += size(file_name);
        printiferror(send(sockfd, file_name.c_str(), size(file_name), 0));
    } else 
        return ERROR;
    return OK;
}

