```cpp
#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

// ==========================================
// ESP32 16-CHANNEL PLC CONTROLLER
// ==========================================

// Wi-Fi
const char* WIFI_SSID = "YOUR_WIFI_NAME";
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";

// Number of relay outputs
const uint8_t OUTPUT_COUNT = 16;

// Most relay modules are Active LOW.
// Change to false if your relay is Active HIGH.
const bool RELAY_ACTIVE_LOW = true;

// ==========================================
// GPIO CONFIGURATION
// ==========================================

const uint8_t OUTPUT_PINS[OUTPUT_COUNT] = {
  4, 5, 13, 14,
  16, 17, 18, 19,
  21, 22, 23, 25,
  26, 27, 32, 33
};

// Output status
bool outputState[OUTPUT_COUNT] = {false};

// Web server
WebServer server(80);


// ==========================================
// RELAY CONTROL
// ==========================================

void writeRelay(uint8_t channel, bool state)
{
    if (channel >= OUTPUT_COUNT)
        return;

    outputState[channel] = state;

    bool pinState;

    if (RELAY_ACTIVE_LOW)
    {
        pinState = !state;
    }
    else
    {
        pinState = state;
    }

    digitalWrite(
        OUTPUT_PINS[channel],
        pinState ? HIGH : LOW
    );
}


// ==========================================
// ALL OUTPUT OFF
// ==========================================

void allOutputsOff()
{
    for (uint8_t i = 0; i < OUTPUT_COUNT; i++)
    {
        writeRelay(i, false);
    }
}


// ==========================================
// WEB PAGE
// ==========================================

String createWebPage()
{
    String html;

    html += "<!DOCTYPE html>";
    html += "<html>";
    html += "<head>";

    html += "<meta name='viewport' content='width=device-width,initial-scale=1'>";

    html += "<title>ESP32 PLC Controller</title>";

    html += "<style>";

    html += "body{";
    html += "font-family:Arial;";
    html += "background:#111;";
    html += "color:white;";
    html += "padding:20px;";
    html += "}";

    html += ".grid{";
    html += "display:grid;";
    html += "grid-template-columns:repeat(auto-fit,minmax(130px,1fr));";
    html += "gap:15px;";
    html += "}";

    html += ".card{";
    html += "background:#222;";
    html += "padding:15px;";
    html += "border-radius:12px;";
    html += "text-align:center;";
    html += "}";

    html += "button{";
    html += "width:100%;";
    html += "padding:12px;";
    html += "margin-top:8px;";
    html += "border:none;";
    html += "border-radius:8px;";
    html += "font-weight:bold;";
    html += "}";

    html += ".on{background:#159447;color:white;}";
    html += ".off{background:#444;color:white;}";
    html += ".danger{background:#c62828;color:white;}";
    
    html += "</style>";

    html += "</head>";
    html += "<body>";

    html += "<h1>ESP32 16-Channel PLC</h1>";

    html += "<p>Industrial Automation Controller</p>";

    html += "<button class='danger' onclick='allOff()'>";
    html += "ALL OUTPUTS OFF";
    html += "</button>";

    html += "<div class='grid'>";

    for (uint8_t i = 0; i < OUTPUT_COUNT; i++)
    {
        html += "<div class='card'>";

        html += "<h2>Q";
        html += String(i);
        html += "</h2>";

        html += "<p id='status";
        html += String(i);
        html += "'>OFF</p>";

        html += "<button class='on' onclick='setOutput(";
        html += String(i);
        html += ",1)'>ON</button>";

        html += "<button class='off' onclick='setOutput(";
        html += String(i);
        html += ",0)'>OFF</button>";

        html += "</div>";
    }

    html += "</div>";

    html += "<script>";

    html += "function setOutput(ch,state){";
    html += "fetch('/api/set?ch='+ch+'&state='+state);";
    html += "}";

    html += "function allOff(){";
    html += "fetch('/api/alloff');";
    html += "}";

    html += "</script>";

    html += "</body>";
    html += "</html>";

    return html;
}


// ==========================================
// ROOT PAGE
// ==========================================

void handleRoot()
{
    server.send(
        200,
        "text/html",
        createWebPage()
    );
}


// ==========================================
// STATUS API
// ==========================================

void handleStatus()
{
    String json = "{";

    for (uint8_t i = 0; i < OUTPUT_COUNT; i++)
    {
        json += "\"q";
        json += String(i);
        json += "\":";
        json += outputState[i] ? "1" : "0";

        if (i < OUTPUT_COUNT - 1)
        {
            json += ",";
        }
    }

    json += "}";

    server.send(
        200,
        "application/json",
        json
    );
}


// ==========================================
// SET OUTPUT API
// ==========================================

void handleSet()
{
    if (!server.hasArg("ch") ||
        !server.hasArg("state"))
    {
        server.send(
            400,
            "text/plain",
            "Missing parameters"
        );

        return;
    }

    int channel = server.arg("ch").toInt();
    int state = server.arg("state").toInt();

    if (channel < 0 ||
        channel >= OUTPUT_COUNT)
    {
        server.send(
            400,
            "text/plain",
            "Invalid channel"
        );

        return;
    }

    writeRelay(
        channel,
        state != 0
    );

    server.send(
        200,
        "text/plain",
        "OK"
    );
}


// ==========================================
// ALL OFF API
// ==========================================

void handleAllOff()
{
    allOutputsOff();

    server.send(
        200,
        "text/plain",
        "ALL OUTPUTS OFF"
    );
}


// ==========================================
// SETUP
// ==========================================

void setup()
{
    Serial.begin(115200);

    delay(500);

    Serial.println();
    Serial.println("==============================");
    Serial.println(" ESP32 PLC CONTROLLER");
    Serial.println("==============================");


    // --------------------------------------
    // Initialize relay outputs
    // --------------------------------------

    for (uint8_t i = 0; i < OUTPUT_COUNT; i++)
    {
        pinMode(
            OUTPUT_PINS[i],
            OUTPUT
        );

        // Safe startup state
        if (RELAY_ACTIVE_LOW)
        {
            digitalWrite(
                OUTPUT_PINS[i],
                HIGH
            );
        }
        else
        {
            digitalWrite(
                OUTPUT_PINS[i],
                LOW
            );
        }

        outputState[i] = false;
    }


    Serial.println("All outputs OFF.");


    // --------------------------------------
    // Wi-Fi
    // --------------------------------------

    WiFi.mode(WIFI_STA);

    WiFi.begin(
        WIFI_SSID,
        WIFI_PASSWORD
    );

    Serial.print("Connecting to WiFi");

    unsigned long startTime = millis();

    while (
        WiFi.status() != WL_CONNECTED &&
        millis() - startTime < 20000
    )
    {
        delay(500);

        Serial.print(".");
    }

    Serial.println();


    if (WiFi.status() == WL_CONNECTED)
    {
        Serial.println("WiFi Connected!");

        Serial.print("IP Address: ");

        Serial.println(
            WiFi.localIP()
        );
    }
    else
    {
        Serial.println(
            "WiFi connection failed!"
        );
    }


    // --------------------------------------
    // Web Server
    // --------------------------------------

    server.on(
        "/",
        HTTP_GET,
        handleRoot
    );

    server.on(
        "/api/status",
        HTTP_GET,
        handleStatus
    );

    server.on(
        "/api/set",
        HTTP_GET,
        handleSet
    );

    server.on(
        "/api/alloff",
        HTTP_GET,
        handleAllOff
    );


    server.begin();

    Serial.println(
        "Web server started."
    );
}


// ==========================================
// MAIN LOOP
// ==========================================

void loop()
{
    server.handleClient();
}
```
