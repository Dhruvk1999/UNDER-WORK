//product design
#include<ESP8266Wifi.h>
const char* ssid = "MY_Network";    //communication
const char* password="PassWord";
#define IR 13  //sensor
#define RELAY 12 //relay subsystem 2 connected to light

void setup() 
{
  Serial.begin(115200)
  pinMode(IR,INPUT); //IR sensor
  pinMode(RELAY,OUTPUT); //Relay Output

}

void loop() 
{
 if(digtalRead(IR)==HIGH)
 {
  digitalWrite(RELAY,HIGH);
  }
}
