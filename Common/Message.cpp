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
    return size;
}

string Message::toString() {
    string out;
    if(type==MessageType::PRIVATE) {
        out.append("P");
        out.append(recipient);
        out.append("|");
    }
    else out.append("G");
    out.append(sender);
    out.append("|");

    out.append(content);
    out.append("\0");
    size = out.size();
    return out;
}

Message::Message(string msg) {
    string res = msg.substr(1);
    string frag;
    stringstream ss(msg);
    vector<string> wyniki;
    while (std::getline(ss, frag, '|')) {
        wyniki.push_back(frag);
    }
    if(msg[0]=='P'){
        type = MessageType::PRIVATE;
        recipient = wyniki[0];
        sender = wyniki[1];
        content = wyniki[2];
    }
    else{
        type = MessageType::GROUP;
        sender = wyniki[0];
        content = wyniki[1];
    }
};



