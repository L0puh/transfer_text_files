# Transfer text files from one device to another using LAN
## usage:
#### unix system:
##### with `cmake`
1. build project 
```sh
mkdir build
cd build 
cmake ..
cmake --build .
```
2. use `server` 

```sh
./server
```
3. and `client` 

```sh
./client
```

##### with `gcc` v11+ 
1. compile a server 
```sh
g++ src/server.cpp src/ttf_net.cpp src/ttf_server.cpp -o server 
./server
```
2. compile a client 
```sh 
g++ src/client.cpp src/ttf_net.cpp src/ttf_client.cpp -o client
./client
```
