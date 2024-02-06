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

#ifndef EVILPORTAL_H
#define EVILPORTAL_H

#include <Arduino.h>
#include <DNSServer.h>
#include "handler.hpp"

class EvilPortal
{
private:
    void initialize_server();
    CaptiveRequestHandler handler;
    DNSServer dnsServer;
    String mdns = "";
public:
    EvilPortal(const char *mdns_name);
    EvilPortal(const char *mdns_name, const char *static_path);
    ~EvilPortal();
    void start_portal();
    void stop_portal();
};

#endif
