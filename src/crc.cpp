#include "headers/ttf.h" 
#include <vector>

const int width = sizeof(crc) * 8;
const int top_bit = (1 << (width - 1));
const int pol = 0xDB;


void Net::init_crc(){
    crc remainder;
    for (int div=0; div < 256; div++){
        remainder = (div << (width- 8));
        for (uint8_t bit=0; bit != 8; bit++) {
            if (remainder & top_bit) 
                remainder = (remainder << 1) ^ pol; 
            else 
                remainder = (remainder << 1) ;
        }
        table.push_back(remainder);
    }
}
crc Net::get_crc(uint8_t msg, uint8_t rem) {
    uint8_t data; 
    data = msg ^ (rem >> (width - 8));
    rem = table.at(data) ^ (rem << 8);
    return rem;
}
void Net::send_crc(std::string message, int sockfd) {
    crc rem=0; 
    for (const char c: message ){
        rem = get_crc(c, rem); 
    }
    printiferror(send(sockfd, &rem, sizeof(crc), 0)); 
}
void Net::check_crc(int sockfd){
    uint8_t rem;
    int bytes_recv = recv(sockfd, &rem, sizeof(crc), 0);
    if (get_crc(rem, rem) != 0) {
        printf("transport error\n");
        //TODO ask again
    } else {
        printf("crc is OK\n");
    }
}
