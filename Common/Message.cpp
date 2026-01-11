//
// Created by Lenovo on 04.01.2026.
//

#include <sstream>
#include <vector>
#include "Message.h"

string Message::getSender() {
    return sender;
}

string Message::getRecipient() {
    return recipient;
}

string Message::getContent() {
    return content;
}

MessageType Message::getType() {
    return type;
}

int Message::getSize() {
    cout<<"MSG gerting size"<<size<<endl;
    return size;
}



Message::Message(string msg) {

    string res = msg.substr(1);
    string frag;
    stringstream ss(msg);
    size = msg.size();
    vector<string> wyniki;
    while (std::getline(ss, frag, '|')) {
        wyniki.push_back(frag);
    }
    if(msg[0]=='P'){
        type = MessageType::PRIVATE;
        recipient = wyniki[1];

        sender = wyniki[2];
        content = wyniki[3];

    }
    else if(msg[0]=='B'){
        type = MessageType::GROUP;
        sender = wyniki[1];
        content = wyniki[2];
    }
    else{
        type = MessageType::SYSTEM;
        content=wyniki[1];
    }

}

string Message::toString() {
    string out;
    if(type == MessageType::PRIVATE){
        out+='P';
        out+='|';
        out+= recipient;

    }
    else if(type==MessageType::GROUP) out+='B';
    else if(type==MessageType::SYSTEM){
        out+='C';
        out+=content;
        return out;
    }
    out+='|';
    out+=sender;
    out+="|";
    out+=content;
    size = out.length();
    converted=out;
    return out;
}

void Message::print() {
    if(!content.empty()){
        cout<<endl<<"======NEW MESSAGE========="<<endl;
        if(type==MessageType::PRIVATE){
             cout<<"PRIVATE from:"<<sender<<endl;

        }
        else if(type==MessageType::GROUP) cout<<"BROADCAST"<<endl;
        else cout<<"SYSTEM"<<endl;
        cout<<content<<endl;
    }
};



