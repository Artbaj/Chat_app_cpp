//
// Created by Lenovo on 04.01.2026.
//

#include <iostream>
#include "UserManager.h"
#include "ClientHandler.h"
using namespace std;
void UserManager::addUser(const string &name, unique_ptr<ClientHandler> handler) {
    activeClients[name] = move(handler);

    activeClients[name]->start();

}

bool UserManager::isUsernameTaken(const string &name) {
    return activeClients.contains(name);
}
