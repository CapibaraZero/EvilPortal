# EvilPortal - A captive portal library for ESP32

This library read static files from SD and create a web server with a customizable POST method and a DNS server that redirect all requests from connected devices to captive portal page.

## Requirements

- ESP32 in AP mode
- SD card module

### How to use
Create page like example.html, load it in SD then initialize an AP in setup() and create a EvilPortal object outside loop() or setup()
You can also create a void captive_portal_callback(AsyncWebServerRequest* request) {} to handle data in POST /login. To use callback add CONFIG_USE_LOGIN_CALLBACK flag to your building system

