#include <SoftwareSerial.h> 
#include <RTClib.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

RTC_DS1307 rtc;

const int ledPinUpdateSignal =  9;

String updateValue;

void setup()
{
    Serial.begin(9600);
    lcd.begin();

    pinMode(ledPinUpdateSignal, OUTPUT);
    
    lcd.setBacklight((uint8_t)1);
    
    if (! rtc.begin()) {
      Serial.flush();
      while (1);
    }
    
    DateTime now = rtc.now();
    rtc.adjust(DateTime(now.hour(), now.minute(), now.second(), 0, 0, 0));       
}
    
void loop()
{  
  DateTime now = rtc.now();
  
    if (Serial.available() > 0) {
        updateValue = Serial.readStringUntil('\n'); 
        
        int index = updateValue.indexOf(':');
        String hourSet = updateValue.substring(0, index);
        int hourSetInt = hourSet.toInt();
      
        String hourRemove = removeWord(updateValue, hourSet);
        String removeColon = hourRemove.substring(1);
        int minuteIndex = removeColon.indexOf(',');
        String minuteString = removeColon.substring(0, minuteIndex);
        int minuteInt = minuteString.toInt();
        
        digitalWrite(ledPinUpdateSignal, HIGH);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Updating time");
        delay(2000);
        lcd.clear();
        digitalWrite(ledPinUpdateSignal, LOW);

        if(hourSetInt != 0 && minuteInt != 0){
          rtc.adjust(DateTime(now.hour(), now.minute(), now.second(), hourSetInt, minuteInt, 2));
          DateTime now = rtc.now();
        }
    }
    
    int hourNow = now.hour();
    int minutesNow = now.minute();
    int secondsNow = now.second();
     
    lcd.setCursor(0,0);
    lcd.print("Time now");
    lcd.setCursor(0,1);
    lcd.print(String(hourNow) + ":" + String(minutesNow) + ":" + String(secondsNow)); 

    int hourIncrement = 6;
    
    for(int loopTime = 0; loopTime < 26; loopTime++){

        if(loopTime >= 0 && loopTime <= 12){
            if(hourNow >= hourIncrement && minutesNow <= 0){
                Serial.println("Open%");
                break;
            }

            else{
                hourIncrement++;
            }
        }

        if(loopTime >= 13 && loopTime <= 26){
            if(loopTime >= 19){
                hourNow = 0;

                if(hourNow >= hourIncrement && minutesNow <= 0){
                    Serial.println("Close%");
                    break;
                }
    
                else{
                    hourIncrement++;
                }
            }

            else{
                if(hourNow >= hourIncrement && minutesNow <= 0){
                    Serial.println("Close%");
                    break;
                }
    
                else{
                    hourIncrement++;
                }
            } 
        }
    }
}


String removeWord(String str, String word) {
  int index = str.indexOf(word);
  if (index == -1) return str;
  int len = word.length();
  return str.substring(0, index) + str.substring(index+len);
}
