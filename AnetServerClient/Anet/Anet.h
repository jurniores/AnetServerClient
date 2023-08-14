#ifndef __ANET__H__
#define __ANET__H__

#include <ESP8266WebServer.h>

using string = const char*;
struct Args
{
    String args[10];
    String names[10];
    byte index;
    String GetName(const char* compareStr);
    String GetArg(const char* compareStr);
};


class Anet : public ESP8266WebServer{
    private:
    using fn = void();
    using fnArgs = void(Args* req, Anet* res);
    public:
    bool Connect(string ssid, string pass);
    void ConnectAp(string ssid, string pass);
    void send(int codeHTTP, string typeHtml, string msg);
    void send(int codeHTTP, string msg);
    void send(string msg);
    void sendError(string msg);
    void get(string router,fnArgs f);
    void post(string router, fnArgs f);
    void listen(int port);
    void listen(int port, fn f);
    void Config(IPAddress ip, IPAddress sub);

};

#endif //__ANET__H__