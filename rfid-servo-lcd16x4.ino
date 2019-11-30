#include <Servo.h>
#include <Wire.h> 
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>

SoftwareSerial rfidSerial(5, 6); // RX, TX
LiquidCrystal_I2C lcd(0x27,20,4);
Servo Barrier;
int incomingByte = 0;   // dùng để lưu giá trị được gửi



#define open 0
#define close 90
String data;
void setup()
{
  rfidSerial.begin(9600); // Setting the baud rate of Software Serial Library  
  Serial.begin(9600);  //Setting the baud rate of Serial Monitor
  Barrier.attach(9);
  Barrier.write(close);
  
  lcd.init();
  lcd.backlight();
  lcd.setCursor(5,0);
  lcd.print("Automatic");
  lcd.setCursor(4,1);
  lcd.print("BOT station");
 }
void loop()
{
  if (Serial.available() > 0) {
                incomingByte = Serial.read();
                
                if (incomingByte != -1){
                    data = char(incomingByte);
                    if (data =="o"){
                      Barrier.write(open);
                    }
                    if (data =="c"){
                      Barrier.write(close);
                    }
        }
  }
        
 if(rfidSerial.available()>0) //check all data coming from RFID reader module via SoftwareSerial 9 pin
  {
   data = rfidSerial.readString();
   data = data.substring(data.indexOf(0x02)+1, data.indexOf(0x03)-1); //separate id
   
   lcd.setCursor(1,3);
   lcd.print("ID: ");
   lcd.setCursor(6,3);
   lcd.print(data);
   Serial.println(data);
  }
 }
