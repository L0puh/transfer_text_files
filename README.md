## TTF
`Transfer text files` - provides sending text files from one device to another using LAN, which is useful when you want to quickly and clearly receive your file on another computer. Just run the server on one device and the client on the other.

## Usage:
#### Unix system:
##### With `cmake`
1. build project 
```sh
mkdir build 
cd build 
cmake ..
cmake --build .
```
2. use `server` on a device where you want recieve a file
```sh
./server
```
3. and `client` for sending some file
```sh
./client
```

##### With `gcc` v11+ 
1. Compile a server 
```sh
g++ src/server.cpp src/ttf_net.cpp src/ttf_server.cpp -o server 
./server
```
2. Compile a client 
```sh 
g++ src/client.cpp src/ttf_net.cpp src/ttf_client.cpp -o client
./client
```

## in the future:
- [ ] script for bash 
- [ ] web client?
- [ ] tg-bot / discord bot
