#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 7, 6, 5, 4);
String inputString3="";
String Logitude="";
String Latitude="";
int SMSPIN=8;
void setup() {
 lcd.begin(16, 2);
 // put your setup code here, to run once:
Serial.begin(9600);
Serial.println("GPS Ready");
inputString3.reserve(200);
Logitude.reserve(20);
Latitude.reserve(20);
pinMode(SMSPIN,INPUT);
lcd.print("System Ready");
}
void loop() {
ReadSerialData();

//delay(100);
}
void ReadSerialData() {
 char inChar;
 inputString3="";
 do{if(Serial.available()){inChar=(char)Serial.read();}}while(inChar!='$');

do{if(Serial.available()){inChar=(char)Serial.read();inputString3=inputString3+inChar;}
}while(inChar!='\n');
 if(inputString3[2]=='R' &&inputString3[3]=='M' &&
inputString3[4]=='C'){CheckForLatitude();}
 }
void CheckForLatitude()
{
 int i=0;
 char DataType;
 Logitude="";
 Latitude="";
 do{i++;}while(inputString3[i]!=',');
 do{i++;}while(inputString3[i]!=',');
 i++; DataType=inputString3[i];i++;
 do{i++;Latitude=Latitude+inputString3[i];}while(inputString3[i]!=',');
 i++; Latitude=Latitude+inputString3[i];i++;
 do{i++;Logitude=Logitude+inputString3[i];}while(inputString3[i]!=',');
 i++; Logitude=Logitude+inputString3[i];i++;
 Serial.print("Data Type:");Serial.println(DataType);
 Serial.print("Latitude:");Serial.println(Latitude);
 Serial.print("Longitude:");Serial.println(Logitude);
 lcd.setCursor(0, 0);
 lcd.print("Lat :");lcd.print(Latitude);
 lcd.setCursor(0, 1);
 lcd.print("Long:");lcd.print(Logitude);
 int GSMValue=digitalRead(SMSPIN);
 if(GSMValue==HIGH){SendSMS("7995953860");}

}
void SendSMS(String Number)
 {
 lcd.setCursor(0,1);
 lcd.print("SMS Sending");
 Serial.println("AT");
 delay(1000);
 Serial.println("AT+CSMP=17,167,0,0");
 delay(1000);
 Serial.print("AT+CMGS=");Serial.print('"');Serial.print(Number);Serial.println('"');
 delay(3000);
 Serial.println("Urgent Help:");
 Serial.print("Latitude:");Serial.println(Latitude);
 Serial.print("Longitude:");Serial.println(Logitude);
 Serial.print((char)0x1a);
 delay(10000);
 }
