#ifndef EVILPORTALHANDLER_H
#define EVILPORTALHANDLER_H

#include <AsyncTCP.h>
#include "ESPAsyncWebServer.h"

#define PORTAL_PORT 80

class CaptiveRequestHandler : public AsyncWebHandler
{
public:
    CaptiveRequestHandler();
    virtual ~CaptiveRequestHandler();
    bool canHandle(AsyncWebServerRequest *request);
    void handleRequest(AsyncWebServerRequest *request); 
    AsyncWebServer server = AsyncWebServer(PORTAL_PORT);
    void set_static_path(const char *path);
};

#endif
