//
// Created by Lenovo on 04.01.2026.
//

#ifndef SO2_MESSAGELOGGER_H
#define SO2_MESSAGELOGGER_H

#include <string>
#include <mutex>
#include "../Common/Message.h"
#include <vector>
#include <thread>
#include <fstream>

using namespace std;
class MessageLogger {
private:

    string path;
    mutex logmtx;
    vector<thread> loggers;
    ofstream plik;
public:
    MessageLogger(const string &p) : path(p) {
        plik.open(path,std::ios::out | std::ios::app);
    }
    void Log(Message& msg);
};


#endif //SO2_MESSAGELOGGER_H
