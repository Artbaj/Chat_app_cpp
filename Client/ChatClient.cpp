#include <iostream>
#include <ostream>
#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib") // Linkowanie biblioteki w MSVC
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif

#include "ChatClient.h"

void ChatClient::start() {
  cout<<"daj adres";
  cin>>ChatClient::IPA;
    showMenu();
}

void ChatClient::setupConnection(uint16_t server_port) {
    ChatClient::clientSocket =  socket(AF_INET, SOCK_STREAM, 0);
    if (ChatClient::clientSocket < 0) {

        cout << "Error creating socket " <<errno<< endl;
        exit(errno);
    }

    sockaddr_in server_address;
    int result =  inet_pton(AF_INET, IPA.c_str(), &server_address.sin_addr);
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(Protocol::DEFAULT_PORT);
    if(result<=0){
        exit(2115);
    }


   cout<<connect(clientSocket, (struct sockaddr*)&server_address, sizeof(server_address));
    if(send(clientSocket,name.c_str(),4,0)<0){
        cout<<"blad w wysylaniu";
    }




}

void ChatClient::showMenu() {

    int choice;
    bool exitRequested = false;

    while (!exitRequested) {
        cout << "\n================================" << endl;
        cout << "   CLIENT: " << name << " (Port: " << port << ")" << endl;
        cout << "================================" << endl;
        cout << "1. Polacz z serwerem" << endl;
        cout << "2. Napisz wiadomosc (Interaktywnie)" << endl;
        cout << "3. Wyslij szybki test (Ping)" << endl;
        cout << "4. Zakoncz" << endl;
        cout << "--------------------------------" << endl;
        cout << "Wybor: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        switch (choice) {
            case 1:
                // Możesz tu dodać pytanie o port serwera, jeśli nie domyślny
                setupConnection();
                break;
            case 2:
                writeMessage(); // Twoja metoda do pobierania tekstu i wysyłki
                break;
            case 3: {
                //Message msg();
                //sendMessage(msg);
                cout << "[!] Testowa wiadomosc wyslana." << endl;
                break;
            }
            case 4:
                exitRequested = true;
                cout << "[!] Zamykanie klienta..." << endl;
                break;
            default:
                cout << "[X] Niepoprawna opcja!" << endl;
        }
    }
}
void ChatClient::writeMessage() {
    string recipient,content;

    cout<<"podaj odbiorce wpisz 0 jesli broadcast"<<endl;
    cin>>recipient;
    cout<<"podaj content";
    cin>>content;
    if(recipient=="0") {
        Message msg = Message(ChatClient::name,content);
        sendMessage(msg);
    }
    else{
        Message msg = Message(ChatClient::name,recipient,content);
        sendMessage(msg);
    }



}

void ChatClient::sendMessage(Message msg) {
    string sendContent = msg.toString();
    int size = msg.getSize();

    if(send(clientSocket,reinterpret_cast<char*>(&size),sizeof(int),0)<0){
       // cout<<"blad w wysylaniu rozmiaru wiadomosci";
    }
    if(send(clientSocket,sendContent.c_str(),size,0)<0){
        cout<<"blad w wysylaniu wiadomosci";
    }
    cout<<sendContent<<" "<<size<<" "<<reinterpret_cast<char*>(&size)<<endl;

}




int main(){
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        std::cerr << "WSAStartup failed: " << result << std::endl;
        return 1;
    }
    ChatClient client = ChatClient("abba",4000);
    client.start();

    WSACleanup();
}