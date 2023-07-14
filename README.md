# TRANSFER TEXT FILES
<img style = "padding:10px;" src = "media/example.gif" width="77%" align = "left">  

:computer:
`Transfer text files` - provides sending text files from one device to another using LAN, which is useful when you want to quickly and clearly share your file locally. Just run a server on one device and the client on the other...
<br>   
*example.gif - example of getting started*
<br>
<br>
#### Usage (unix system):
execute the shell script in your terminal for compiling. then use binary files by `./server` and `./client`
```sh
bash script.sh
```
or you can use `g++`
1. compile a server 
```sh
g++ src/server.cpp src/ttf_net.cpp src/ttf_server.cpp -o server 
```
2. compile a client 
```sh 
g++ src/client.cpp src/ttf_net.cpp src/ttf_client.cpp -o client
```
> **:exclamation: NB**: all files put in "files/client_files/" and "files/server_files/" folders or check out configuration to declarate your path. for sending a file, just type the filename and file extension (`file.txt`)

## configuration:
set in your `./bashrc` or `./zshrc` a path to files. `$TTF_client` for folder with files to send and `$TTF_server` for path to recieving files on another computer. 
```bash
export TTF_client="path/to/your/folder" #send files
export TTF_server="path/to/your/folder" #recieve files
```

## in the future:
- [ ] script for bash 
- [ ] web client?
- [ ] tg-bot / discord bot
