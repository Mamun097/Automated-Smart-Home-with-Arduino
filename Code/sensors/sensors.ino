#include <Wire.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>

#include <SoftwareSerial.h>

#define DHTPIN 6
#define DHTTYPE DHT11
#define in 8 //IR Sensor 1
#define out 7 //IR sensor 2


int light=0;
int count=0, pos=0;

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

char sms;

LiquidCrystal_I2C lcd(0x27, 20, 4);
DHT dht(DHTPIN,DHTTYPE);

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

}

void loop()
{

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

    if(bulb1status==1){
      if(light<60){
        digitalWrite(bulb1,HIGH);
      }
      else{
        digitalWrite(bulb1,LOW);
      }
    }
    if(bulb1status==0){
      digitalWrite(bulb1,LOW);
    }
    
    if(bulb2status==1){
      if(light<60){
        digitalWrite(bulb2,HIGH);
      }
      else{
        digitalWrite(bulb2,LOW);
      }
    }
    if(bulb2status==0){
      digitalWrite(bulb2,LOW);
    }


    if(fanstatus==1){
      if(temperature>28){
        digitalWrite(relay,LOW);
      }
      else{
        digitalWrite(relay,HIGH);
      }
    }
    if(fanstatus==0){
      digitalWrite(relay,HIGH);
    }

    gas=analogRead(A1);
    fireValue=digitalRead(firePin);
    if(gas>=200 || fireValue==0)
      digitalWrite(buzzer,HIGH);
    else
      digitalWrite(buzzer,LOW);
    
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

  /* if((digitalRead(in))==0){
   delay(20);
   while((digitalRead(in))==0)
     if(pos==0)
        pos=1;
     else if(pos==3)
       pos=4;
   }
   if(pos==4){
   count=count-5;
   pos=0;
}

if((digitalRead(out))==0){
delay(20);
while((digitalRead(out))==0)
if(pos==1)
pos=2;
else if(pos==0)
pos=3;
}

if(pos==2){
count=count+1;
lcd.setCursor(0,0);
lcd.print(count);
pos=0;
}
else if(pos==4){
count=count-10;
lcd.setCursor(0,0);
lcd.print(count);
pos=0;
}

else
  pos=0;*/

 delay(400);
 lcd.clear();
}
