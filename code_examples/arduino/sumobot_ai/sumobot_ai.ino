// Sumobot Sample Code
// Used to get your sumobot in the ring
// Covers most of the basic features and should hold its own in the ring
// Author: Devin Pearson
// License: MIT License (https://opensource.org/licenses/MIT)

#include <Servo.h>

Servo servoLeft;                  // Define left servo
Servo servoRight;                 // Define right servo

#define trigPin 13                // Define trigger pin for proximity to digital pin 12
#define echoPin 12                // Define trigger pin for proximity to digital pin 12

#define servoLeftPin 10           // Define left servo to digital pin 10
#define servoRightPin 9           // Define right servo to digital pin 9

#define leftLinePin A0            // Define left line to analog pin A0
#define rightLinePin A1           // Define right line to analog pin A1

unsigned long previousMillis = 0; // will store last time LED was updated

long interval = 500;              // interval used for move lengths (milliseconds)

int moveArray[5];                 // the move buffer. sets the size of the buffer

boolean sensorsTriggered = false; // flag for keeping tabs on whether the line sensors have been triggered

/**
 * Setup Pins and initialise the bot
 */
void setup() { 
  servoLeft.attach(servoLeftPin);  
  servoRight.attach(servoRightPin);  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  // open Serial for debugging
  Serial.begin(9600);
  
  moveArray[0] = 0;
  makeMove();
  delay(2000);
  moveArray[0] = 5;
} 
/**
 * Main loop
 * keep this as clean as possible to give an overview of what steps are run
 */
void loop() {
  // checks the line sensors
  checkLineSensors();
  // check for an opponent
  readProximity();
  // handles movements
  moveTimer();
  delay(2);
}
/**
 * moveTimer checks if the interval times have passed.
 * if it has it actions the next move
 */
void moveTimer() {
  // gets the current time
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time you made a move
    previousMillis = currentMillis;
    // action the next move
    makeMove();
  }

}
/**
 * Checks the proximity sensor for any opponents ahead of it
 */
void readProximity() {
    long duration, distance;
    // the proximity sensor is triggered by a HIGH pulse of 2 or more microseconds.
    // give a short LOW pulse beforehand to ensure a clean HIGH pulse:
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(5);
    digitalWrite(trigPin, LOW);
    // get distance in microseconds
    duration = pulseIn(echoPin, HIGH);
    // The speed of sound is 340 m/s or 29 microseconds per centimeter.
    // The ping travels out and back, so to find the distance of the
    // object we take half of the distance travelled.
    distance = duration / 29 / 2;
    
    if (distance >= 70 || distance <= 0){
      Serial.println("Out of range");
    }
    else {
      foundObject();
      Serial.print(distance);
      Serial.println(" cm");
    }
}
/**
 * Checks the line sensors for the edge.
 * If one is triggered the bot will turn the opposite way
 */
void checkLineSensors() {
  // read the pins for the line sensors
  int leftLineValue = analogRead(leftLinePin);
  int rightLineValue = analogRead(rightLinePin);
  // check if either of the seonsors have a value high enough to beconsidered a white line
  if (leftLineValue > 900 || rightLineValue > 900) {
      if (!sensorsTriggered) {
        // turn right
        int direct = 3;
        if (leftLineValue > 900)
        {
          // turn left
          int direct = 4;
        }
        // gives the avoidance commands with direction
        avoidLine(direct);
        // actions the move right away
        makeMove();
        Serial.print("\n line sensor triggered");
        // flag for debounce, needs to wait to be off the line before it can be triggered again
        sensorsTriggered = true;
      }
    } else {
      // turns the flag off again
      sensorsTriggered = false;
    }
}

/**
 * make more thats the command by id from the buffer and matches it to a movement
 */
void makeMove() {
  // we reset the interval timer so actions happen immediately in the moveTimer()
  interval = 0;
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
    case 5:
      shortForward();
      //Serial.print("\n forward");
      break;
    case 6:
      turnLeftSlow();
      //Serial.print("\n forward");
      break;
    case 7:
      turnRightSlow();
      //Serial.print("\n forward");
      break;
    default:
      stopRobot();
      break;
  }
  previousMillis = millis();
  // call pop to remove the move we just did
  pop();
}

/**
 * Pop shifts all the movements forward by 1 and added a default command on the end
 */
void pop() {
  moveArray[0] = moveArray[1];
  moveArray[1] = moveArray[2];
  moveArray[2] = moveArray[3];
  moveArray[3] = moveArray[4];
  moveArray[4] = 7;
}

/**
 * Moves forward for 1 second at full pace. 
 * As one servo is backwards we have to send opposite values for the continuous revolution servos
 * 90 is stopped
 * 180 is forward 
 * 0 is backward
 */
void forward() {
  interval = 1000;
  servoLeft.write(0);
  servoRight.write(180);
}

void shortForward() {
  interval = 2000;
  servoLeft.write(0);
  servoRight.write(180);
}

void reverse() {
  interval = 1000;
  servoLeft.write(180);
  servoRight.write(0);
}

void turnRight() {
  interval = 300;
  servoLeft.write(180);
  servoRight.write(180);
}
void turnLeft() {
  interval = 300;
  servoLeft.write(0);
  servoRight.write(0);
}
/**
 * This slow command is achieved by having the servo value close to 90.
 * The closer it is the slower the servo will turn
 */
void turnRightSlow() {
  interval = 300;
  servoLeft.write(95);
  servoRight.write(95);
}
void turnLeftSlow() {
  interval = 300;
  servoLeft.write(85);
  servoRight.write(85);
}

void stopRobot() {
  servoLeft.write(90);
  servoRight.write(90);
}
/**
 * runs through some of the basic movements
 */
void demo() {
  moveArray[0] = 1;
  moveArray[1] = 2;
  moveArray[2] = 3;
  moveArray[3] = 4;
  moveArray[4] = 0;
}
/**
 * a left to right motion to search for a target
 */
void sweep() {
  moveArray[0] = 3;
  moveArray[1] = 4;
  moveArray[2] = 3;
  moveArray[3] = 4;
  moveArray[4] = 1;
}
/**
 * used when a line is triggered to move away and face the inside of the arena again
 */
void avoidLine(int direct) {
  moveArray[0] = 0;
  moveArray[1] = direct;
  moveArray[2] = direct;
  moveArray[3] = 5;
  moveArray[4] = 0;
}
/**
 * When a object if found we tell the bot to just keep charging forward
 */
void foundObject() {
  moveArray[0] = 0;
  moveArray[1] = 1;
  moveArray[2] = 1;
  moveArray[3] = 1;
  moveArray[4] = 1;
}
/**
 * use if you want the bot to stop all actions
 */
void stopAll() {
  moveArray[0] = 0;
  moveArray[1] = 0;
  moveArray[2] = 0;
  moveArray[3] = 0;
  moveArray[4] = 0;
  stopRobot();
}

