# Transfer text files from one device to another using local net
## usage:
#### unix system:
using `cmake`
```sh
mkdir build
cd build 
cmake ..
cmake --build .
./server
```
using `gcc`
```sh
g++ src/server.cpp src/ttf_net.cpp src/ttf_server.cpp -o server 
./server
```
