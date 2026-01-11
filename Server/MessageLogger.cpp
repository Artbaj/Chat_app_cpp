//
// Created by Lenovo on 04.01.2026.
//

#include "MessageLogger.h"


void MessageLogger::Log(Message msg) {
    loggers.emplace_back([this, msg]() {
        logmtx.lock();

        if(plik.is_open()){

            plik<<msg.converted<<endl;
        }
        logmtx.unlock();

    });

}
