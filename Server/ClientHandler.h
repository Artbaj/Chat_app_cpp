//
// Created by Lenovo on 04.01.2026.
//

#ifndef SO2_CLIENTHANDLER_H
#define SO2_CLIENTHANDLER_H

#include <string>
#include <atomic>
#include <vector>
#include <iostream>
#include "../Common/Message.h"
#include <semaphore>

using namespace std;
class ChatServer;

class ClientHandler {
public:

    ClientHandler(int socket,string cName,ChatServer *server): clientSocket(socket), clientName(cName), msg_semaphore(1), server(server){};



    void start();


    void sendMessage(const Message& msg);


    string getClientName() const { return clientName; }

private:
    ChatServer* server;
    int clientSocket;
    string clientName;
    binary_semaphore msg_semaphore;
    vector<Message> msgs;
    atomic<bool> is_active;

    void run();


};


#endif //SO2_CLIENTHANDLER_H
