#include "Logger.h"

#include "MsgService.h"

void LoggerService::log(const String& msg) {
    MsgService.sendMsg("LOG:" + msg);
}

void LoggerService::bin(const String& msg) {
    MsgService.sendMsg("BIN:" + msg);
}

void LoggerService::temp(const String& msg) {
    MsgService.sendMsg("TEMP:" + msg);
}

void LoggerService::emergency(const String& msg) {
    MsgService.sendMsg("EMERGENCY:" + msg);
}