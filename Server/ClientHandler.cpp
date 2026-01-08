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
void handlerLoop(const int& socket,const string& name,binary_semaphore& msg_semaphore,vector<Message>& msgs,atomic<bool>& is_active){
    while(is_active){
        int size;

        vector<char> buff(1);
        size = recv(socket,buff.data(),sizeof(int),0);

        if(size<0){
            cout<<WSAGetLastError();
        }
        size = buff[0];
        buff.clear();
        buff.resize(size);


        if(recv(socket,buff.data(),size,0)<0){
            cout<<WSAGetLastError();
        }

        string out(buff.begin(), buff.end());


        msg_semaphore.acquire();
        msgs.emplace_back(out);
        msg_semaphore.release();
    }

}

void handleIncomingMessage(vector<Message>& msgs,atomic<bool>& is_active,binary_semaphore& msg_semaphore,ChatServer* server) {
    while(is_active){
        msg_semaphore.acquire();
        if(!msgs.empty()){
            for(auto msg:msgs){
                if(msg.type==MessageType::PRIVATE) server->sendPrivate(msg);
            }
        }
        msg_semaphore.release();
    }
}

void ClientHandler::start() {
    msgs.reserve(Protocol::DEFAULT_MSG_QUEUE_SIZE);
    is_active = true;
    thread  readingThread(handlerLoop,cref(clientSocket), cref(clientName),ref(msg_semaphore),ref(msgs),ref(is_active));
    thread parsingThread(handleIncomingMessage,ref(msgs),ref(is_active),ref(msg_semaphore),server);
    readingThread.join();
    parsingThread.join();
}

void ClientHandler::sendMessage(const Message &msg) {

}





