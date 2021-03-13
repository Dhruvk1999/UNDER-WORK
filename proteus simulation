#include <LiquidCrystal.h>
#include <BlynkSimpleStream.h>
#include <DS3231.h>
DS3231  rtc(A1, A2);
char auth[] = "_XItYcAYiqGGLFVsnn8dseqAmH2WRZa-"; 
const int rs = 12, en = 11, d4 = 10, d5 = 9, d6 = 8, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
LiquidCrystal lcd1(22, 23, 24, 25, 26, 27);
const int r1=28,r2=29,r3=30,r4=37,r5=38,pir=32,buzz=33,trig=31,echo=34,ldr=A0,light=6;
const int r2input=35,r3input=36,r4input=39,r5input=40;
float duration;
int distance,ldrval;
String dateandtime="",message="";
WidgetLED led1 (V3);  
WidgetLED led2 (V4);
int current,pervious=0,cur,pre=0,cur1,pre1=0,cur2,pre2=0;
//------------------------------------setup---------------------------------------------
void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, Serial);
  lcd.begin(20,4);
  lcd1.begin(20,4);
  pinMode(r1,OUTPUT);
  pinMode(r2,OUTPUT);
  pinMode(r3,OUTPUT);
  pinMode(r4,OUTPUT);
  pinMode(r5,OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(pir,INPUT);
  pinMode(buzz,OUTPUT);
  pinMode(ldr,INPUT);
  pinMode(light,OUTPUT);
  pinMode(r2input,INPUT);
  pinMode(r3input,INPUT);
  lcd.setCursor(0,0);
  lcd.print("last action was");
  lcd.setCursor(0,1);
  lcd.print("---------------");
 lcd.setCursor(0,2); 
 lcd.print("L 1 OFF     F 1 OFF");
 lcd.setCursor(0,3);
 lcd.print("L 2 OFF     F 2 OFF");
 rtc.begin();
}
//---------------------------------------loop---------------------------------------------------
void loop() {
  ldrcheck();
  doorcheck();
  Blynk.run();
  updatevalue();
  lcd1.setCursor(0,0);
  lcd1.print(rtc.getDOWStr());
  lcd1.setCursor(0,1);
  lcd1.print(rtc.getDateStr());
  lcd1.setCursor(0,2);
  lcd1.print(rtc.getTimeStr());
}
//------------------------------------------upadting the values of relays------------------------
void updatevalue() {
  current=digitalRead(r2input);
  cur=digitalRead(r3input);
  cur1=digitalRead(r4input);
  cur2=digitalRead(r5input);
  if(current!=pervious){
    pervious=current;
    if(current==1)
     {
      lcd.setCursor(1,2);
      lcd.print("L 1 ON ");
      lcd.setCursor(0,1);
      lcd.print("L 1 was turned on ");
     }
    else{
      lcd.setCursor(1,2);
      lcd.print("L 1 OFF");
      lcd.setCursor(0,1);
      lcd.print("L 1 was turned off");  
    }
   }
  if(cur!=pre){
    pre=cur;
    if(cur==1)
     {
      lcd.setCursor(12,2);
      lcd.print("F 1 ON ");
      lcd.setCursor(0,1);
      lcd.print("F 1 was turned on ");
     }
    else{
      lcd.setCursor(12,2);
      lcd.print("F 1 OFF");
      lcd.setCursor(0,1);
      lcd.print("F 1 was turned off");  
    }
  }
  if(cur1!=pre1){
    pre1=cur1;
    if(cur1==1)
     {
      lcd.setCursor(1,3);
      lcd.print("L 2 ON ");
      lcd.setCursor(0,1);
      lcd.print("L 2 was turned on ");
     }
    else{
      lcd.setCursor(1,3);
      lcd.print("L 2 OFF");
      lcd.setCursor(0,1);
      lcd.print("L 2 was turned off");  
    }
  }
  if(cur2!=pre2){
    pre2=cur2;
    if(cur2==1)
     {
      lcd.setCursor(12,3);
      lcd.print("F 2 ON ");
      lcd.setCursor(0,1);
      lcd.print("F 2 was turned on ");
     }
    else{
      lcd.setCursor(12,3);
      lcd.print("F 2 OFF");
      lcd.setCursor(0,1);
      lcd.print("F 2 was turned off");  
    }
  }
}
//------------------------------------------blynk codes--------------------------------
 BLYNK_WRITE(V1) //Button Widget is writing to pin V1
{
  int pinData = param.asInt(); 
  if(pinData==1){
    digitalWrite(r2, HIGH);
  }else{
    digitalWrite(r2, LOW);
  }
}
 BLYNK_WRITE(V5) //Button Widget is writing to pin V1
{
  dateandtime=param.asString();
  setdateandtime();
}
BLYNK_WRITE(V6) //Button Widget is writing to pin V1
{ 
  message=param.asString();
  lcd1.setCursor(0,3);
  lcd1.print("                    ");
  lcd1.setCursor(0,3);
  lcd1.print(message);
}

 BLYNK_WRITE(V2) //Button Widget is writing to pin V1
{
  int pinData = param.asInt(); 
  if(pinData==1){
    digitalWrite(r3, HIGH);
    }
    else{
    digitalWrite(r3, LOW);
    }
}
BLYNK_WRITE(D37) //Button Widget is writing to pin V1
{
  int pinData = param.asInt(); 
  if(pinData==1){
    digitalWrite(r4, HIGH);
  }else{
    digitalWrite(r4, LOW);
  }
}
BLYNK_WRITE(D38) //Button Widget is writing to pin V1
{
  int pinData = param.asInt(); 
  if(pinData==1){
    digitalWrite(r5, HIGH);
  }else{
    digitalWrite(r5, LOW);
  }
}
//-----------------------------------------set date and time----------------------------
void setdateandtime(){
lcd1.setCursor(0,0);
lcd1.print("                    ");
lcd1.setCursor(0,1);
lcd1.print("                    ");
lcd1.setCursor(0,2);
lcd1.print("                    ");
 int day1=dateandtime.substring(0,1).toInt();
 if(day1==1){
  day1=8;
 }
 rtc.setDOW(day1-1);     
 rtc.setTime(dateandtime.substring(10,12).toInt(),dateandtime.substring(12,14).toInt(),dateandtime.substring(14,16).toInt());     
 rtc.setDate(dateandtime.substring(2,4).toInt(), dateandtime.substring(4,6).toInt(), dateandtime.substring(6,10).toInt());
}
//-------------------------------------------ldr check----------------------------------
void ldrcheck(){
ldrval=analogRead(ldr);
analogWrite(light,225-(map(ldrval,0,1023,0,255)));
led2.setValue(ldrval);
if(ldrval<=300){
  digitalWrite(r1,LOW);
}
else{
  digitalWrite(r1,HIGH);
}}
//-----------------------------------------------door check--------------------------

int ultrasoniccheck(){
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  distance = 0.017 * duration;
  return(distance);
}


void doorcheck(){ 
  if(digitalRead(pir)==1){
    if(ultrasoniccheck()<=100)
       {digitalWrite(buzz,HIGH);
       led1.on();
       } 
       else{
  digitalWrite(buzz,LOW);
  led1.off();
  }}
 else{
  digitalWrite(buzz,LOW);
  led1.off();
 }}
 
