#ifndef __ANETCLIENT__H__
#define __ANETCLIENT__H__

#include <ESP8266HTTPClient.h>

class AnetClient: public HTTPClient{
    private:
    String url;
    using fn = void(String res);
    public:
    void Connect(const char* ssid, const char* pass, const char* urlP);
    void stateWifi();
    void get(String router, String query, fn f);
    void post(String router, String query, fn f);
};

#endif //__ANETCLIENT__H__