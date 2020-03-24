#include <Arduino.h>
#include <Servo.h>
// Motor steps per revolution. Most steppers are 200 steps or 1.8 degrees/step
#define MOTOR_STEPS 200
#define RPM 4

#define DIR 8
#define STEP 9
#define SLEEP 13 // optional (just delete SLEEP from everywhere if not used)

/*
   Choose one of the sections below that match your board
*/

//#include "DRV8834.h"
//#define M0 10
//#define M1 11
//DRV8834 stepper(MOTOR_STEPS, DIR, STEP, SLEEP, M0, M1);

#include "A4988.h"
#define MS1 10
#define MS2 11
#define MS3 15
#define microStepMode 8
#define MOTOR_ACCEL 2000
#define MOTOR_DECEL 1000
A4988 stepper(MOTOR_STEPS, DIR, STEP, SLEEP, MS1, MS2, MS3);

#define StringHeadPin 20
#define StringHeadInitialPos 4
#define StringHeadLastPos 75
Servo StringHead;

//Setup parameters
int incomingByte = 0;
int flagRaised = 0;
int row = 0;
int nailNumber = 95;
int microStepPerNail = (MOTOR_STEPS*microStepMode) / nailNumber;
int sequence[5][2] = {{1, 1},
  {5, 0},
  {11, 1},
  {25, 0},
  {31, 1}
};
void setup() {
  /*
     Set target motor RPM.
  */
  Serial.begin(115200);
  delay(500);
  stepper.begin(RPM);
  // if using enable/disable on ENABLE pin (active LOW) instead of SLEEP uncomment next line
  // stepper.setEnableActiveState(LOW);
  stepper.enable();
  stepper.setMicrostep(microStepMode);   // Set microstep mode to 1:8
  stepper.setSpeedProfile(stepper.LINEAR_SPEED, MOTOR_ACCEL, MOTOR_DECEL);

  StringHead.attach(StringHeadPin);
  // set current level (for DRV8880 only).
  // Valid percent values are 25, 50, 75 or 100.
  // stepper.setCurrent(100);
}

void loop() {
  //Checking for Serial input
  if (Serial.available() > 0) {
    incomingByte = Serial.read();

    if (incomingByte == 'n') {
      row = row + 1;
      flagRaised = 0;
    }
    else if (incomingByte == 'p') {
      row = row - 1;
      flagRaised = 0;
    }
    else {
      //Serial.print("I received: nothing yet!");
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
      Serial.print("Face [Up]");
    }
    Serial.println("\tPress 'n' for next or 'p' for previous");

  }
}


void stepNodeCwise(int nails , int microStepPerNail) {
  int numberOfSteps = nails * (MOTOR_STEPS * microStepMode) / nailNumber;
  stepper.move(numberOfSteps);
}

void stepNodeCCwise(int nails , int microStepPerNail) {
  int numberOfSteps = nails * (MOTOR_STEPS * microStepMode) / nailNumber;
  stepper.move(-1 * numberOfSteps);
}
