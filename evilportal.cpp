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

#include <Arduino.h>
#include <WiFi.h>
#include <ESPmDNS.h>
#include "evilportal.hpp"

#define DNS_PORT 53

#ifdef ARDUINO_NANO_ESP32
#define SERIAL_DEVICE Serial
#else
#define SERIAL_DEVICE Serial0
#endif

void EvilPortal::initialize_server()
{
    dnsServer.start(DNS_PORT, "*", WiFi.softAPIP());
    if (!MDNS.begin(mdns))
    {
        SERIAL_DEVICE.printf("Error starting mDNS");
        return;
    }
    handler.server.addHandler(new CaptiveRequestHandler()).setFilter(ON_AP_FILTER);
    handler.server.begin();
}

EvilPortal::EvilPortal(const char *mdns_name, const char *static_path)
{
    mdns = mdns_name;
    handler.set_static_path(static_path);
}

EvilPortal::EvilPortal(const char *mdns_name)
{
    mdns = mdns_name;
}

EvilPortal::~EvilPortal()
{
    SERIAL_DEVICE.printf("Stopping captive portal\n");
    handler.server.end();
    dnsServer.stop();
}

void EvilPortal::start_portal()
{
    initialize_server();
    for (;;)
    {
        dnsServer.processNextRequest();
    }
}

void EvilPortal::stop_portal()
{
    SERIAL_DEVICE.println("Stop portal");
    handler.server.end();
    dnsServer.stop();
}