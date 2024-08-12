//
//  main.cpp
//  Task-3.3-Chain
//
//  Created by Маргарет  on 12.08.2024.
//

#include <iostream>
#include <fstream>

enum LogmMessage {
    WARNING = 0,
    ERROR = 1,
    FATALERROR = 2,
    UNKNOWNMESSAGE = 3
};

class LogHandler {
private:
    LogHandler* nextHandler = nullptr;
public:
    void add(LogHandler* handler) {
        if(nextHandler) {
            nextHandler->add(handler);
        } else {
            nextHandler = handler;
        }
    }
    
    void setNextHandler(LogHandler* handler) {
        nextHandler = handler;
    }
    virtual void handleLog(LogmMessage &logmessage) {
        nextHandler->handleLog(logmessage);
    }
    
};

class FatalErrorHandler : public LogHandler {
public:
    void handleLog(LogmMessage &logmessage) override {
        if(logmessage != FATALERROR) {
            std::cout << "FatalErrorHandler passed " << static_cast<int>(logmessage) << "\n";
            LogHandler::handleLog(logmessage);
        } else {
            std::cout << "FatalErrorHandler handled: throw exception\n";
        }
    }
};

class ErrorHandler : public LogHandler {
public:
    void handleLog(LogmMessage &logmessage) override {
        if(logmessage != ERROR) {
            std::cout << "ErrorHandler passed " << static_cast<int>(logmessage) << "\n";
            LogHandler::handleLog(logmessage);
        } else {
            std::ofstream f;
            f.open("errorfile.txt", std::fstream::app);
            if (f.is_open()) {
                f << "Error!\n";
            }
            f.close();
        }
        
    }
};

class WarningHandler : public LogHandler {
public:
    void handleLog(LogmMessage &logmessage) override {
        if(logmessage != WARNING) {
            std::cout << "WarningHandler passed " << static_cast<int>(logmessage) << "\n";
            LogHandler::handleLog(logmessage);
        } else {
            std::cout << "WARNING!";
        }
    }
};

class UnknownHandler : public LogHandler {
public:
    void handleLog(LogmMessage &logmessage) override {
        if(logmessage != UNKNOWNMESSAGE) {
            std::cout << "UnknownHandler passed " << static_cast<int>(logmessage) << "\n";
            LogHandler::handleLog(logmessage);
        } else {
            std::cout << "UnknownHandler handled: throw exception\n";
        }
    }
};

int main(int argc, const char * argv[]) {
    LogHandler root;
    FatalErrorHandler h1;
    ErrorHandler h2;
    root.add(&h1);
    root.add(&h2);
    h2.setNextHandler(&root);
    LogmMessage fatal = FATALERROR;
    LogmMessage error = ERROR;
    h1.handleLog(error);
    return 0;
}
