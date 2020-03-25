#include <Arduino.h>

// Motor steps per revolution. Most steppers are 200 steps or 1.8 degrees/step
#define MOTOR_STEPS 200
#define RPM 4

#define DIR 8
#define STEP 9
#define SLEEP 13 // optional (just delete SLEEP from everywhere if not used)


#include "A4988.h"
#define MS1 10
#define MS2 11
#define MS3 15
#define microStepMode 8
#define MOTOR_ACCEL 2000
#define MOTOR_DECEL 1000
A4988 stepper(MOTOR_STEPS, DIR, STEP, SLEEP, MS1, MS2, MS3);
/*
   For Servo
  #define StringHeadPin 20
  #define StringHeadInitialPos 4
  #define StringHeadLastPos 75
  Servo StringHead;
*/
//Software parameters
int incomingByte = 0;
int flagRaised = 0;
int row = 0;

// Canvas Parameter
int nailNumber = 95;
int microStepPerNail = (MOTOR_STEPS*microStepMode) / nailNumber;
int numberOfSequence = 5;
int curNailID = 1;

// Weaving Sequence Data
int sequence[5][2] = {{1, 1},
  {5, 0},
  {11, 1},
  {25, 0},
  {31, 1}
};


void setup() {
  Serial.begin(115200);
  delay(500);
  stepper.begin(RPM);
  stepper.enable();
  stepper.setMicrostep(microStepMode);   // Set microstep mode to 1:8
  stepper.setSpeedProfile(stepper.LINEAR_SPEED, MOTOR_ACCEL, MOTOR_DECEL);

  curNailID = sequence[0][0];
  Serial.print("The sequence is starting from nail ID:\t");
  Serial.println(curNailID);
}

void loop() {
  //Checking for Serial input
  if (Serial.available() > 0) {
    incomingByte = Serial.read();

    if (incomingByte == 'n') {
      if (row < numberOfSequence) {
        row = row + 1;
      } else {
        Serial.println("Sequence Exhausted");
      }
    }
    else if (incomingByte == 'p') {
      row = row - 1;
    }
    else {
      //Serial.print("I received: nothing yet!");
    }
    if (curNailID != sequence[row][0]) {
      flagRaised = 0;
      int desiredNailID = sequence[row][0];
      int nails = stepsToMove(curNailID, desiredNailID, nailNumber);
      Serial.print("\tSteps to move are \t");
      Serial.println(nails);
      curNailID = desiredNailID;
      stepNode(nails);
    }
  }
  //End of Checking for Serial input

  //Have the user been notified
  if (flagRaised == 0) {
    flagRaised = 1;
    Serial.print("Current Row : ");
    Serial.print(row);
    Serial.print("\tString Direction : \t");
    if (sequence[row][1] == 1)
    {
      Serial.print("Face [Up]");
    }
    else {
      Serial.print("Face [Down]");
    }
    Serial.println("\tPress 'n' for next or 'p' for previous");

  }
}

void stepNode(int nails) {
  int numberOfSteps = nails * (MOTOR_STEPS * microStepMode) / nailNumber;
  stepper.move(numberOfSteps);
}

int stepsToMove( int startingNail, int  endingNail, int NailNumber) {
  int distance = 0;
  //distance = NailNumber * (distance / NailNumber) - (distance % NailNumber)
  if (endingNail < startingNail) {
    distance = startingNail - endingNail;
    if (abs(distance) < NailNumber / 2) {
      distance = -1 * distance;
    } else {
      distance = NailNumber - startingNail + endingNail;
    }
  }
  else {
    distance = endingNail - startingNail;
    if (abs(distance) < NailNumber / 2) {
      distance = distance;
    } else {
      distance = NailNumber - endingNail + startingNail;
    }
  }

  return distance;
}
