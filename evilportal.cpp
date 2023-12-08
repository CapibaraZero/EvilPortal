#include <Arduino.h>
#include <WiFi.h>
#include <ESPmDNS.h>
#include "sdcard_helper.hpp"
#include "evilportal.hpp"

#define DNS_PORT 53

void EvilPortal::initialize_server()
{
    handler.server.addHandler(new CaptiveRequestHandler()).setFilter(ON_AP_FILTER);
    handler.server.begin();
}

EvilPortal::EvilPortal(const char *mdns_name, const char *static_path)
{
    dnsServer.start(DNS_PORT, "*", WiFi.softAPIP());
    if (!MDNS.begin(mdns_name))
    {
        Serial0.printf("Error starting mDNS");
        return;
    }

    handler.set_static_path(static_path);
    initialize_server();

    Serial0.printf("AP IP address: %s\n", WiFi.softAPIP().toString());

    for (;;)
    {
        dnsServer.processNextRequest();
    }
}

EvilPortal::EvilPortal(const char *mdns_name)
{
    dnsServer.start(DNS_PORT, "*", WiFi.softAPIP());
    if (!MDNS.begin(mdns_name))
    {
        Serial0.printf("Error starting mDNS");
        return;
    }

    initialize_server();

    Serial0.printf("AP IP address: %s\n", WiFi.softAPIP().toString());

    for (;;)
    {
        dnsServer.processNextRequest();
    }
}

EvilPortal::~EvilPortal()
{
    Serial0.printf("Stopping captive portal\n");
    handler.server.end();
    dnsServer.stop();
    WiFi.softAPdisconnect(true);
}
