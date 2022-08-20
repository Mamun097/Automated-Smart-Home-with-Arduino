#include <GPRS_Shield_Arduino.h>  
 #include <SoftwareSerial.h>  
 #include <Wire.h>  
  int led = 13;     
 #define MESSAGE1 "Load is on"  
 #define MESSAGE2 "Load is off"  
 String data;  
 char b[100];  
 int temp=0;  
 #define PIN_TX  7  
 #define PIN_RX  8  
 #define BAUDRATE 9600  
 #define PHONE_NUMBER1 "0174175953"  
 //#define MESSAGE"data"   
 #define MESSAGE_LENGTH 160  
 char message[MESSAGE_LENGTH];  
 int messageIndex = 0;  
 char phone[16];  
 char datetime[24];  
 String rmsg;  
 String asish = String("load on");  
 String asish1 = String("load off");  
 GPRS gprs(PIN_TX,PIN_RX,BAUDRATE);//RX,TX,PWR,BaudRate  
  void read_sms();  
 void setup() {  
  // digitalWrite(13, HIGH);  
   pinMode( 13, OUTPUT);  
   gprs.checkPowerUp();  
  Serial.begin(9600);  
  while(!gprs.init()) {  
    Serial.print("init error\r\n");  
    delay(1000);  
  }  
  delay(3000);   
  Serial.println("Init Success, please send SMS message to me!");  
 }  
 void loop() {  
  read_sms();  
 }  
  void read_sms(){  
  messageIndex = gprs.isSMSunread();  
   if (messageIndex > 0) { //At least, there is one UNREAD SMS  
    gprs.readSMS(messageIndex, message, MESSAGE_LENGTH, phone, datetime);  
    delay(200);  
      rmsg=String(message);  
       if(asish == message)  
      {  
        digitalWrite(13, HIGH);  
        (gprs.sendSMS(PHONE_NUMBER1,MESSAGE1));  
         delay(20);  
         gprs.deleteSMS(messageIndex);   
      }   
     if(asish1 == message)  
      {  
        digitalWrite(13, LOW);  //For 5 sec motor stsr  
        (gprs.sendSMS(PHONE_NUMBER1,MESSAGE2));  
         delay(20);  
         gprs.deleteSMS(messageIndex);   
      }   
      gprs.deleteSMS(messageIndex);  
    Serial.print("From number: ");  
    Serial.println(phone);   
    Serial.print("Datetime: ");  
    Serial.println(datetime);      
    Serial.print("Recieved Message: ");  
    Serial.println(message);    
   }  
  }
