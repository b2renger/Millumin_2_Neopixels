
/*
   based on : https://fredrikolofsson.com/f0blog/f0dmx/
   install OSC from https://github.com/CNMAT/OSC
   install WiFiManager from https://github.com/tzapu/WiFiManager
   install neopixel lib from adafruit
*/

// change the name to a unique one
char *espname = "esp8266_01";
// messaging variables
const unsigned int outPort = 12000;          // remote port (not needed for receive)
const unsigned int inPort = 10000;        // local port to listen for UDP packets (here's where we send the packets)

// wifi stuff
// uncomment the 3 lines below if you are working with an esp8266
#//include <ESP8266WiFi.h>
#//include <ESP8266WebServer.h>
#//include <ESP8266mDNS.h>
#include <DNSServer.h>
#include <WiFiManager.h>
#include <Ticker.h>
// for OSC messaging
#include <WiFiUdp.h>
#include <OSCMessage.h>
#include <OSCBundle.h>
#include <OSCData.h>
IPAddress outIp;
IPAddress broadIp;
WiFiUDP Udp;

// led stuff
#include <Adafruit_NeoPixel.h>
// neopixel variables
#define PIN        14
#define NUMPIXELS 16
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// wifi connection feedback
Ticker ticker;
int LED = LED_BUILTIN;
#define LED_BUILTIN 13 // ESP32 DOES NOT DEFINE LED_BUILTIN

void tick() {
  digitalWrite(LED, !digitalRead(LED));
}



void setup() {

  Serial.begin(115200);

  // init the lights at startup
  pixels.begin();
  for (int i = 0; i < NUMPIXELS; i++) { // For each pixel...
    pixels.setPixelColor(i, pixels.Color(10, 10, 10));
  }
  pixels.show();


  // wifi stuff
  pinMode(LED, OUTPUT);
  ticker.attach(0.6, tick);// start ticker with 0.5 because we start in AP mode and try to connect

  init_wifi();
  broadcast_identity();

  ticker.detach();
  digitalWrite(LED, LOW);


}

float r = 0 ;
float g = 0;
float b = 0;

// callback from osc messages received with "/color1" adress pattern
// as specified below
void red(OSCMessage &msg) {
   r = msg.getFloat(0);
   println("message ok");
}

void green(OSCMessage &msg) {
   g = msg.getFloat(0);
}

void blue(OSCMessage &msg) {
   b = msg.getFloat(0);
}

void loop() {

  OSCBundle bundle;
  int size = Udp.parsePacket();
  if (size > 0) {
    while (size--) {
      //yield();
      bundle.fill(Udp.read());
    }
    // you can add lines here to add custom callback functions for each
    // address pattern you send data to with your osc controller
    bundle.dispatch("/r", red);
    bundle.dispatch("/g", green);
    bundle.dispatch("/b", blue);
    // don't remove the line below though (it's needed for auto-discovery)
    bundle.dispatch("/id", broadcast_id);
  }

  for (int i = 0; i < NUMPIXELS; i++) { // For each pixel...
    pixels.setPixelColor(i, pixels.Color(r, g, b));
  }
  pixels.show();   // Send the updated pixel colors to the hardware.

}


// you don't need to change stuff below this line
void broadcast_id(OSCMessage &msg1) {
  // sending a message broadcasted to all the network to give name ip and port
  // construct a message telling ready / name of the device / ip
  OSCMessage msg("/ready");  //announcement
  msg.add(espname);
  msg.add(int(outIp[0]));
  msg.add(int(outIp[1]));
  msg.add(int(outIp[2]));
  msg.add(int(outIp[3]));
  msg.add(outPort);
  //send the message
  Udp.beginPacket(broadIp, outPort);
  msg.send(Udp);
  Udp.endPacket();
  yield();
  msg.empty();

  Serial.print("id message received, broadcasting myIp : " );
  Serial.print(outIp + ":" );
  Serial.println(inPort );
}

void broadcast_identity() {
  // sending a message broadcasted to all the network to give name ip and port
  // construct a message telling ready / name of the device / ip
  OSCMessage msg("/ready");  //announcement
  msg.add(espname);
  msg.add(int(outIp[0]));
  msg.add(int(outIp[1]));
  msg.add(int(outIp[2]));
  msg.add(int(outIp[3]));
  msg.add(outPort);
  //send the message
  Udp.beginPacket(broadIp, outPort);
  msg.send(Udp);
  Udp.endPacket();
  yield();
  msg.empty();
}

void init_wifi() {
  WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP
  //  WiFi.hostname(espname);
  //  wifi_station_set_hostname(espname);
  //WiFiManager
  WiFiManager wm;
  // wm.resetSettings();//reset settings - for testing
  //set callback that gets called when connecting to previous WiFi fails, and enters Access Point mode
  wm.setAPCallback(configModeCallback);
  //fetches ssid and pass and tries to connect
  //if it does not connect it starts an access point with the specified name
  //here  "AutoConnectAP" and goes into a blocking loop awaiting configuration
  if (!wm.autoConnect(espname)) {
    Serial.println("failed to connect and hit timeout");
    //reset and try again, or maybe put it to deep sleep
    ESP.restart();
    delay(1000);
  }
  //if you get here you have connected to the WiFi
  Serial.println("connected...yeah ! :)");
  //MDNS.begin(espname);  //make .local work
  outIp = WiFi.localIP();
  broadIp = WiFi.localIP();
  broadIp[3] = 255;// broadcast it to every device on the netwok IP x.x.x.255
  Udp.begin(inPort);

}

//gets called when WiFiManager enters configuration mode
void configModeCallback (WiFiManager *myWiFiManager) {
  Serial.println("Entered config mode");
  Serial.println(WiFi.softAPIP());
  //if you used auto generated SSID, print it
  Serial.println(myWiFiManager->getConfigPortalSSID());
  //entered config mode, make led toggle faster
  ticker.attach(0.2, tick);
}
