/*
 * This file is part of the Capibara zero (https://github.com/CapibaraZero/fw or https://capibarazero.github.io/).
 * Copyright (c) 2024 Andrea Canale.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "evilportal.hpp"
#include "FS.h"
#include "SD.h"

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
    server.serveStatic("/", SD, path);
    server.on("/", HTTP_GET, [path](AsyncWebServerRequest *request){
        Serial0.printf("Client connected. Ip: %s\n", request->client()->remoteIP().toString());
        request->send(SD, (String)path + "/index.html", "text/html");
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
