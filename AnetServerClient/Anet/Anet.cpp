#include <Anet.h>

using WebServer = ESP8266WebServer;

String Args::GetArg(const char *compareStr)
{
    if (index == 0)
        return "";
    for (size_t i = 0; i < index; i++)
    {
        if (names[i].equalsIgnoreCase(compareStr))
        {
            return args[i];
        }
    }
    return "Argumento nao existe!";
}
String Args::GetName(const char *compareStr)
{
    if (index == 0)
        return "";
    for (size_t i = 0; i < index; i++)
    {
        if (args[i].equalsIgnoreCase(compareStr))
        {
            return names[i];
        }
    }
    return "Argumento nao existe!";
}

bool Anet::Connect(string ssid, string pass)
{
    WiFi.begin(ssid,pass);  
    while (
           WiFi.status() != WL_CONNECTED
        && WiFi.status() != WL_CONNECT_FAILED
        && WiFi.status() != WL_NO_SSID_AVAIL
        && WiFi.status() != WL_CONNECT_FAILED
        && WiFi.status() != WL_CONNECTION_LOST
        && WiFi.status() != WL_MAX_ATTEMPT_CONNECTION
        && WiFi.status() != WL_WRONG_PASSWORD 
        )
    {
      delay(500);
      Serial.print(".");
      Serial.print(WiFi.status());
    }
    if(WiFi.status() == WL_CONNECTED){
        Serial.println("Conectei");
      return true;
    }
    return false;
    
}

void Anet::ConnectAp(string ssid, string pass)
{
    WiFi.softAP(ssid, pass);
    Serial.println("Rede conectada com sucesso! ");
    Serial.println("Ip da sua rede: " + WiFi.softAPIP().toString());
}
void Anet::Config(IPAddress ip, IPAddress sub)
{
    WiFi.config(ip, ip, sub);
}
void Anet::send(int codeHTTP, string typeHtml, string msg)
{
    WebServer::send(codeHTTP, typeHtml, msg);
}
void Anet::send(int codeHTTP, string msg)
{
    WebServer::send(codeHTTP, "text/html", msg);
}
void Anet::send(string msg)
{
    WebServer::send(200, "text/html", msg);
}
void Anet::sendError(string msg)
{
    WebServer::send(404, "text/html", msg);
}
void Anet::get(string router, fnArgs f)
{
    WebServer::on(router, [=]()
                  {
                      if (WebServer::method() == HTTP_GET)
                      {
                          Args req;
                          byte index = WebServer::args();
                          req.index = index;
                          if (index == 0)
                              return f(&req, this);

                          for (size_t i = 0; i < index; i++)
                          {
                              req.args[i] = WebServer::argName(i);
                              req.names[i] = WebServer::arg(i);
                          }

                          f(&req, this);
                      }
                  });
}
void Anet::post(string router, fnArgs f)
{

    WebServer::on(router, [=]()
                  {
                      if (WebServer::method() == HTTP_POST)
                      {
                          Args req;
                          byte index = WebServer::args();
                          req.index = index;
                          if (index == 0)
                              return f(&req, this);

                          for (size_t i = 0; i < index; i++)
                          {
                              req.args[i] = WebServer::argName(i);
                              req.names[i] = WebServer::arg(i);
                          }

                          f(&req, this);
                      }
                  });
}

void Anet::listen(int port)
{
    WebServer::begin(port);
}
void Anet::listen(int port, fn f)
{
    WebServer::begin(port);
    f();
}