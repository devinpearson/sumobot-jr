#include <Servo.h>

Servo servoLeft;          // Define left servo
Servo servoRight;         // Define right servo

#define trigPin 13
#define echoPin 12
#define leftLinePin A0
#define rightLinePin A1
#define proxInterval 750

unsigned long previousMillis = 0;        // will store last time LED was updated
unsigned long proxPreviousMillis = 0;

// constants won't change :
long interval = 500;           // interval at which to blink (milliseconds)

int leftLineValue = 0;        // value read from the pot
int rightLineValue = 0;
int moveArray[5];
boolean sensorsTriggered = false;

void setup() { 
  servoLeft.attach(10);  // Set left servo to digital pin 10
  servoRight.attach(9);  // Set right servo to digital pin 9
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  //demo();
  makeMove();
} 

void loop() {            // Loop through motion tests
  checkLineSensors();
  readProximity();
  moveTimer();
  delay(2);
}
// set previousMillis to millis();
// set interval to how long we want the move
// start movement
void moveTimer() {
  
  //if (inMotion) {
  if (moveArray[0] != -1) {
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval) {
      // save the last time you blinked the LED
      previousMillis = currentMillis;
     
      //Serial.print("  timer  ");
    
      makeMove();
    }
  }
}

void readProximity() {
  unsigned long currentMillis = millis();

    if (currentMillis - proxPreviousMillis >= proxInterval) {
      // save the last time you blinked the LED
      proxPreviousMillis = currentMillis;
     
      long duration, distance;
      digitalWrite(trigPin, LOW);  // Added this line
      delayMicroseconds(2); // Added this line
      digitalWrite(trigPin, HIGH);
    //  delayMicroseconds(1000); - Removed this line
      delayMicroseconds(10); // Added this line
      //digitalWrite(trigPin, LOW);
      duration = pulseIn(echoPin, HIGH);
      distance = (duration/2) / 29.1;
      if (distance < 4) {  // This is where the LED On/Off happens
      //  digitalWrite(led,HIGH); // When the Red condition is met, the Green LED should turn off
      //digitalWrite(led2,LOW);
      }
      else {
        //digitalWrite(led,LOW);
        //digitalWrite(led2,HIGH);
      }
      if (distance >= 70 || distance <= 0){
        Serial.println("Out of range");
      }
      else {
        foundObject();
        Serial.print(distance);
        Serial.println(" cm");
      }
    }
  
}

void checkLineSensors() {
  leftLineValue = analogRead(leftLinePin);
  rightLineValue = analogRead(rightLinePin);
  if (leftLineValue > 900 || rightLineValue > 900) {
      //Serial.print(leftLineValue);
      if (!sensorsTriggered) {
        int direct = 3;
        if (leftLineValue > 900)
        {
          direct = 4;
        }
        avoidLine(direct);
        makeMove();
        Serial.print("\n triggered");
        //stopAll();
        sensorsTriggered = true;
      }
    } else {
      sensorsTriggered = false;
    }
}

void makeMove() {

    switch(moveArray[0]) {
      case 1:
        forward();
        //Serial.print("\n forward");
        break;
      case 2:
        reverse();
        //Serial.print("\n reverse");
        break;
      case 3:
        turnRight();
        break;
      case 4:
        turnLeft();
        break;
      default:
        interval = 0;
        stopRobot();
        break;
    }
    previousMillis = millis();
    pop();
  
}

void pop() {
  moveArray[0] = moveArray[1];
  moveArray[1] = moveArray[2];
  moveArray[2] = moveArray[3];
  moveArray[3] = moveArray[4];
  moveArray[4] = 0;
}

// Motion routines for forward, reverse, turns, and stop
void forward() {
  interval = 1000;
  servoLeft.write(0);
  servoRight.write(180);
}

void reverse() {
  interval = 1000;
  servoLeft.write(180);
  servoRight.write(0);
}

void turnRight() {
  interval = 600;
  servoLeft.write(180);
  servoRight.write(180);
}
void turnLeft() {
  interval = 600;
  servoLeft.write(0);
  servoRight.write(0);
}

void stopRobot() {
  servoLeft.write(90);
  servoRight.write(90);
}

void demo() {
  moveArray[0] = 1;
  moveArray[1] = 2;
  moveArray[2] = 3;
  moveArray[3] = 4;
  moveArray[4] = 0;
}

void avoidLine(int direct) {
  moveArray[0] = 0;
  moveArray[1] = direct;
  moveArray[2] = 3;
  moveArray[3] = 4;
  moveArray[4] = 0;
}

void foundObject() {
  moveArray[0] = 0;
  moveArray[1] = 1;
  moveArray[2] = 1;
  moveArray[3] = 1;
  moveArray[4] = 1;
}

void stopAll() {
  moveArray[0] = 0;
  moveArray[1] = 0;
  moveArray[2] = 0;
  moveArray[3] = 0;
  moveArray[4] = 0;
  stopRobot();
}

