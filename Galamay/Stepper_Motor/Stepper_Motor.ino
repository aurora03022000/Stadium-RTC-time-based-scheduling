#include <Stepper.h>
#include <SoftwareSerial.h> 
#include <AccelStepper.h>

#define FULLSTEP 4

const int stepsPerRevolution = 200;  // change this value to match the number of steps per revolution for your motor

#define motorPin1  8     // Blue   - 28BYJ48 pin 1
#define motorPin2  9     // Pink   - 28BYJ48 pin 2
#define motorPin3  10    // Yellow - 28BYJ48 pin 3
#define motorPin4  11    // Orange - 28BYJ48 pin 4
 
AccelStepper stepper(FULLSTEP, motorPin1, motorPin3, motorPin2, motorPin4);

const int buttonPinManual = 7;
int buttonStateManual = 0;
const int buttonPinOPen = 2;
int buttonStateOpen = 0;
const int buttonPinClose = 3;
int buttonStateClose = 0;
const int buttonPinAutomatic = 4;
int buttonStateAutomatic = 0;

const int ledPinAutomaticSignal =  6;
const int ledPinManualSignal =  5;
const int ledPinOpenSignal =  13;
const int ledPinCloseSignal =  12;

bool buttonAutomatic = true;

String message;

int maxSpeedValue = 50;
int accelerationValue = 50;
int speedValue = 50;

bool automatic = true;
bool manual = false;

void setup() {
  Serial.begin(9600);
  
  stepper.setMaxSpeed(maxSpeedValue);
  stepper.setAcceleration(accelerationValue);
  stepper.setSpeed(speedValue);

  pinMode(buttonPinManual, INPUT);
  pinMode(buttonPinOPen, INPUT);
  pinMode(buttonPinClose, INPUT);
  pinMode(buttonPinAutomatic, INPUT);
  
  pinMode(ledPinAutomaticSignal, OUTPUT);
  pinMode(ledPinManualSignal, OUTPUT);
  pinMode(ledPinOpenSignal, OUTPUT);
  pinMode(ledPinCloseSignal, OUTPUT);

  digitalWrite(ledPinAutomaticSignal, HIGH);
  digitalWrite(ledPinManualSignal, LOW);
  digitalWrite(ledPinOpenSignal, LOW);
  digitalWrite(ledPinCloseSignal, LOW);
}

void loop() {
  buttonStateManual = digitalRead(buttonPinManual); // for manual
  buttonStateOpen = digitalRead(buttonPinOPen); // manual open
  buttonStateClose = digitalRead(buttonPinClose); // manual close
  buttonStateAutomatic = digitalRead(buttonPinAutomatic); // automatic
  
  if(buttonStateManual == HIGH) {
        automatic = false;
        manual = true;
        digitalWrite(ledPinAutomaticSignal, LOW);
        digitalWrite(ledPinManualSignal, HIGH);
  }

  //Open
  if (buttonStateOpen == HIGH && manual == true) {
      int steps = 100;
      digitalWrite(ledPinOpenSignal, HIGH);
      for(;;){
          buttonStateOpen = digitalRead(buttonPinOPen);
          stepper.moveTo(steps);
          stepper.run();
          steps++;
    
          if(buttonStateOpen == LOW){
             stepper.stop();
             digitalWrite(ledPinOpenSignal, LOW);
             break;
          }
      } 
  }

  //Close
  if (buttonStateClose == HIGH && manual == true) {
      int steps = -100;
      digitalWrite(ledPinCloseSignal, HIGH);
      for(;;){
          buttonStateClose = digitalRead(buttonPinClose);
          stepper.moveTo(steps);
          stepper.run();
          steps--;
    
          if(buttonStateClose == LOW){
             stepper.stop();
             digitalWrite(ledPinCloseSignal, LOW);
             break;
          }
      } 
  }

  if (buttonStateAutomatic == HIGH) {
      manual = false;
      automatic = true;
      
      digitalWrite(ledPinAutomaticSignal, HIGH);
      digitalWrite(ledPinManualSignal, LOW);
  }
  
  
  if (Serial.available()>0 && automatic == true) {
      message = Serial.readStringUntil('%'); 
      
      if(message == "Open"){
          digitalWrite(ledPinOpenSignal, HIGH);
          for(;;){
              buttonStateManual = digitalRead(buttonPinManual);
        
              if(buttonStateManual == HIGH) {
                  stepper.stop();
                  break;
              }
            
              stepper.moveTo(1000);
              stepper.run();
              
              if (!stepper.distanceToGo()) {
                digitalWrite(ledPinOpenSignal, LOW);
                break;
              } 
          }
      }

      else if(message == "Close"){
          digitalWrite(ledPinCloseSignal, HIGH);
          for(;;){
              buttonStateManual = digitalRead(buttonPinManual);
        
              if(buttonStateManual == HIGH) {
                  stepper.stop();
                  break;
              }
            
              stepper.moveTo(-1000);
              stepper.run();
              
              if (!stepper.distanceToGo()) {
                digitalWrite(ledPinCloseSignal, LOW  );
                break;
              } 
          }
      } 
  }

}
