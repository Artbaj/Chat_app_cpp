//
// Created by Lenovo on 04.01.2026.
//
#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib") // Linkowanie biblioteki w MSVC
#else
#include <sys/socket.h>
#include <netinet/in.hg>
#include <arpa/inet.h>
#include <unistd.h>
#endif
#include "ChatServer.h"
#include "../Common/Protocol.h"

#include <thread>
#include <iostream>
#include "ClientHandler.h"
using namespace std;
void handlerLoop(const int& socket,const string& name){
    int size;

    vector<char> buff(1);
    size = recv(socket,buff.data(),1,0);

    if(size<0){
        cout<<WSAGetLastError();
    }
    buff.resize(size);

    size = recv(socket,buff.data(),size,0);
    if(size<0){
        cout<<WSAGetLastError();
    }


}
void ClientHandler::start() {
    cout<<clientName;
    thread  readingThread(handlerLoop,cref(clientSocket), cref(clientName));
    readingThread.join();
}


