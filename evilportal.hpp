#ifndef EVILPORTAL_H
#define EVILPORTAL_H

#include <DNSServer.h>
#include "handler.hpp"

class EvilPortal
{
private:
    void initialize_server();
    CaptiveRequestHandler handler;
    DNSServer dnsServer;
public:
    EvilPortal(const char *mdns_name);
    EvilPortal(const char *mdns_name, const char *static_path);
    ~EvilPortal();
};

#endif
