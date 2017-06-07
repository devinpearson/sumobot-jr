#include <Servo.h>

Servo servoLeft;          // Define left servo
Servo servoRight;         // Define right servo

#define trigPin 13
#define echoPin 12
#define leftLinePin A0
#define rightLinePin A1
#define proxInterval 750

const int servoLeftInt = 10;
const int servoRightInt = 9;


// defines variables
int distance;
long duration;
int distanceCm, distanceInch;

int leftLineValue=0;
int rightLineValue=0;

boolean targetFound = false;
boolean lineFound = false;

int maxSpeed = 220; // max speed of motors (min 120 -> max 255 ) 
int rotation300mm = 5000; //5000ms sleep to sigify 300 mm
int rotation150mm = 2500; //2500ms sleep to sigify 150 mm
int rotation75mm = 1250; //1250ms sleep to sigify 75 mm
int rotation30mm = 500; //500ms sleep to sigify 30 mm

unsigned long timestampvar = millis();

int buttonPin = 3;
int buttonState = 0; 

boolean started = false;

void setup() {
  delay(2000);
  Serial.begin(9600);
  // motors
  servoLeft.attach(servoLeftInt);  // Set left servo to digital pin 10
  servoRight.attach(servoRightInt);  // Set right servo to digital pin 9
  // sensors
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  //pinMode(SensorPin,INPUT);
  pinMode(buttonPin, INPUT);

}


void resetSensor(){
   Serial.println("resetSensor");
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  //targetFound = false;
}

void virtualDelayStare(int total){
  Serial.println("virtualDelayStare");
  timestampvar = millis();
    while((long(millis())-long(timestampvar)) < long(total)){
        SeekLine();
        seekSensor();
        if(lineFound == true)
            break;
        if(targetFound == false)
            break;
    }
    timestampvar = millis();
}

void virtualDelayFind(int total){
  Serial.println("virtualDelayFind");
  timestampvar = millis();
    while((long(millis())-long(timestampvar)) < long(total)){
        SeekLine();
        seekSensor();
        if(lineFound == true)
            break;
        if(targetFound == true)
            break;
    }
    timestampvar = millis();
}

void goForward(int amount) //backwards
{ 
  Serial.println("GoForward");
  servoLeft.write(0);
  servoRight.write(180);
  virtualDelayStare(amount);
  stopRobot();
} 

void goBackward(int amount) //forwards
{ 
  Serial.println("GoBack");
  servoLeft.write(180);
  servoRight.write(0);
  virtualDelayFind(amount);
  stopRobot();
} 


void seekRight (int turnAmount) //forwards
{ 
  Serial.println("SeekRight");
  servoLeft.write(180);
  servoRight.write(180);
  virtualDelayFind(turnAmount);
  stopRobot();
} 

void seekLeft (int turnAmount) //forwards
{ 
  Serial.println("SeekLeft");
  servoLeft.write(0);
  servoRight.write(0);
  virtualDelayFind(turnAmount);
  stopRobot();
}

void stopRobot() { //stop
  servoLeft.write(90);
  servoRight.write(90);
}

void seekSensor(){
  resetSensor();
  targetFound = false;
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  //Serial.print("Dur1=");
  //Serial.println(duration);
  distance= duration*0.034/2;
  Serial.print("Distance=");
  Serial.println(distance);
  if(distance > 0 && distance < 30)
    targetFound = true;
}

void SeekLine(){
  lineFound = false;
  leftLineValue = analogRead(leftLinePin);
  rightLineValue = analogRead(rightLinePin);
  
  Serial.print("leftLineValue=");
  Serial.println(leftLineValue);
  Serial.print("rightLineValue=");
  Serial.println(rightLineValue);
  if(leftLineValue > 1000 || rightLineValue > 1000){
    lineFound = true;
    Serial.println("Found");
  } 
  else{
    Serial.println("Not Found");
    lineFound = false;
  }
}

void loop() {
  //Serial.println("--------------------------------------------");

    seekSensor();
    SeekLine();
    if(targetFound == true && lineFound == false){
        goForward(rotation300mm);
    }
    else if(lineFound){
        goBackward(rotation30mm);
    }
    else{
      switch(random(1, 2)) {
          case 1: 
              seekRight(rotation75mm);
              break;
          case 2:
              seekLeft(rotation75mm);
              break;          
      } 
      
    }
}
