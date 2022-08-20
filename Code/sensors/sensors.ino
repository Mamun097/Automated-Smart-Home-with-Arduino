#include <Wire.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <SoftwareSerial.h>
#include <GPRS_Shield_Arduino.h>

#define PIN_TX    2
#define PIN_RX    3
#define BAUDRATE  9600
#define PHONE_NUMBER  "01724458983"
#define MESSAGE1  "Dear Sir,\nIt's rainning. Please bring an umbrella if you go outside.\nThank you."

GPRS gprs(PIN_TX, PIN_RX, BAUDRATE);

#define DHTPIN 6
#define DHTTYPE DHT11
#define in 7 //IR Sensor 1
#define out 8 //IR sensor 2


int light=0;
int count=0, pos=0;
int rain=1024;
int rainMsgCount=0;

int bulb1=12;
int bulb2=11;

int bulb1status=0;
int bulb2status=0;
int fanstatus=0;

int gas=0;
int firePin=10;
int fireValue=1;
int buzzer=5;
int relay=4;

int in_ir=0, out_ir=0;

char sms;

bool isFire=false;
bool isGas=false;
bool isRain=false;
int win=0;

LiquidCrystal_I2C lcd(0x27, 20, 4);
DHT dht(DHTPIN,DHTTYPE);
Servo servo;

void setup()
{
  lcd.init();
  lcd.backlight();

  dht.begin();

  Serial.begin(9600);
  pinMode(bulb1,OUTPUT);
  pinMode(bulb2, OUTPUT);
  pinMode(in, INPUT);
  pinMode(out, INPUT);
  pinMode (buzzer, OUTPUT);
  pinMode (firePin, INPUT);
  pinMode(relay, OUTPUT);
  servo.attach(9);
  servo.write(180);
  
  gprs.checkPowerUp();
  Serial.begin(9600);
    while (!gprs.init()) {
        Serial.println("Initialization failed!");
    }

    while (!gprs.isNetworkRegistered()) {
        Serial.println("Network has not registered yet!");
    }
    Serial.println("gprs initialize done");
}

void loop()
{
    int person=PersonCount();
    float humidity= dht.readHumidity();
    float temperature= dht.readTemperature();
    
    light=analogRead(A0);
    
    if(Serial.available()!=0){
      sms=Serial.read();
    }

    if(sms=='1'){
      bulb1status=1;
    }

    if(sms=='2'){
      bulb1status=0;
    }

    if(sms=='3'){
      bulb2status=1;
    }

    if(sms=='4'){
      bulb2status=0;
    }

    if(sms=='5'){
      fanstatus=1;
    }
    if(sms=='6'){
      fanstatus=0;
    }

    if(sms=='7'){
      servo.write(0);
      win=1;
    }
    if(sms=='8'){
      servo.write(180);
      win=0;
    }

    if(bulb1status==1 && person>0){
      if(light<60){
        digitalWrite(bulb1,HIGH);
      }
      else{
        digitalWrite(bulb1,LOW);
      }
    }
    if(bulb1status==0 || person<=0){
      digitalWrite(bulb1,LOW);
    }
    
    if(bulb2status==1 && person>0){
      if(light<60){
        digitalWrite(bulb2,HIGH);
      }
      else{
        digitalWrite(bulb2,LOW);
      }
    }
    if(bulb2status==0 || person<=0){
      digitalWrite(bulb2,LOW);
    }


    if(fanstatus==1 && person>0){
      if(temperature>28){
        digitalWrite(relay,LOW);
      }
      else{
        digitalWrite(relay,HIGH);
      }
    }
    if(fanstatus==0 || person<=0){
      digitalWrite(relay,HIGH);
    }

    gas=analogRead(A1);
    fireValue=digitalRead(firePin);
    
    if(fireValue==0)isFire=true;
    else isFire=false;

    if(gas>250)isGas=true;
    else isGas=false;

    //gas bairatase
    if(gas>=100){
      digitalWrite(buzzer,HIGH);
      servo.write(0);
      
      lcd.clear();
      lcd.setCursor(0,1);
      lcd.print("   Gas Detected!");
      lcd.setCursor(0,2);
      lcd.print(" Making phone call.");
      
      gprs.callUp(PHONE_NUMBER);
    }
    else
      digitalWrite(buzzer,LOW);

    //Agun lagse
    if(fireValue==0){
      digitalWrite(buzzer,HIGH);
      
      lcd.clear();
      lcd.setCursor(0,1);
      lcd.print("   Fire Detected!");
      lcd.setCursor(0,2);
      lcd.print(" Making phone call.");
      
      gprs.callUp(PHONE_NUMBER);
    }
    else
      digitalWrite(buzzer,LOW);

    rain=analogRead(A2);

    if(rain<700){
      if(win==1)
        servo.write(180);
    isRain=true;

    if(rainMsgCount==0){
      lcd.clear();
      lcd.setCursor(0,1);
      lcd.print("Oofs! It's rainning!");
      lcd.setCursor(0,2);
      lcd.print("   Window Closed");
      gprs.sendSMS(PHONE_NUMBER, MESSAGE1);
      rainMsgCount=rainMsgCount+1;
    }
  }
  else{
    rainMsgCount=0;
    isRain=false;
  }

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("T:");
    lcd.print(temperature);
    lcd.print((char)223);
    lcd.print("C");
    lcd.setCursor(11,0);
    lcd.print("H:");
    lcd.print(humidity);
    lcd.print("%");
    
    lcd.setCursor(0,1);
    lcd.print("L:");
    lcd.print(light);

    lcd.setCursor(11,1);
    lcd.print("G:");
    lcd.print(gas);

    lcd.setCursor(0,2);
    lcd.print("P:");
    lcd.print(person);
  
    delay(250);
    lcd.clear();
}


int PersonCount(){
  if((digitalRead(out))==0 && (digitalRead(in))==0){
  }
else if((digitalRead(out))==0){
  Serial.println("out tr");
  if(out_ir==0){
  out_ir=1;
    if(in_ir==1){
    count=count+1;
    in_ir=0;
    out_ir=0;
      delay(250);

    }
  }
}
else if((digitalRead(in))==0){
  Serial.println("in tr");
  if(in_ir==0){
  in_ir=1;
  if(out_ir==1){
  if(count>0)  count=count-1;

    in_ir=0;
    out_ir=0;
         delay(250);

    }
  }
}
  return count;
}
