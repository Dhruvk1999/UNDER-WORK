// Import required libraries
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <aREST.h>
// Clients
WiFiClient espClient;
PubSubClient client(espClient);
// Create aREST instance
aREST rest = aREST(client);
// Unique ID to identify the device for cloud.arest.io
char* device_id = "9cwerty";
// WiFi parameters
const char* ssid = "wifi-name";
const char* password = "wifi-password";
// Functions
void callback(char* topic, byte* payload, unsigned int length);
void setup(void)
{
 // Start Serial
 Serial.begin(115200);
 // Set callback
 client.setCallback(callback);
 // Give name and ID to device
 rest.set_id(device_id);
 rest.set_name("PD_Board_Control");
 // Connect to WiFi
 WiFi.begin(ssid, password);
 while (WiFi.status() != WL_CONNECTED) {
 delay(500);
 Serial.print(".");
 }
 Serial.println("");
 Serial.println("WiFi connected");
 // Set output topic
 char* out_topic = rest.get_topic();
}
void loop() {
 // Connect to the cloud
 rest.handle(client);
}
// Handles message arrived on subscribed topic(s)
void callback(char* topic, byte* payload, unsigned int length) {
 rest.handle_callback(client, topic, payload, length);
}

//Some more insructions
//to check if the board is online
//login to arest
//to actually test it, go to your  web browser,http://cloud.arest.io/(device id as in the code)/id
//if getting some message the board is online
//turniing pins on or off
//first step is to declare it as input or output
//enter https://cloud.arest.io/9u2co4/mode/5/o this sets pin 5 as the output
//https://cloud.arest.io/9u2co4/digital/5/1 this sets pin 5 HIGH replace 1 with 0 for low
//blah...blah....blah
