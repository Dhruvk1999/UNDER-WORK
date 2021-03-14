#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
/* Set these to your desired credentials. */
const char *ssid = "*****"; //Enter your WIFI ssid
const char *password = "*****"; //Enter your WIFI password
ESP8266WebServer server(80);
int RelayInput1=2
void handleRoot() {
 server.send(200, "text/html", "<form action=\"/RelayInput1_on\" method=\"get\" id=\"form1\"></form><button type=\"submit\" form=\"form1\" value=\"On\">On</button><form action=\"/RelayInput1_off\" method=\"get\" id=\"form2\"></form><button type=\"submit\" form=\"form2\" value=\"Off\">Off</button>");
}
void handleSave() {
 if (server.arg("pass") != "") {
   Serial.println(server.arg("pass"));
 }
}
void setup() {
 pinMode(RelayInput1, OUTPUT);
 delay(3000);
 Serial.begin(115200);
 Serial.println();
 Serial.print("Configuring access point...");
 WiFi.begin(ssid, password);
 while (WiFi.status() != WL_CONNECTED) {
   delay(500);
   Serial.print("Relay Module 1 is switched ON");
 }
 Serial.println("");
 Serial.println("WiFi connected");
 Serial.println("IP address: ");
 Serial.println(WiFi.localIP());
 server.on ( "/", handleRoot );
 server.on ("/save", handleSave);
 server.begin();
 Serial.println ( "HTTP server started" );
 server.on("/Relay1_on", []() {
   digitalWrite(RelayInput1, 1);
   Serial.println("on");
   handleRoot();
 });
 server.on("/Relay1_off", []() {
   digitalWrite(RelayInput1, 0);
   Serial.println("off");
   handleRoot();
 });
}
void loop() {
 server.handleClient();
} 
