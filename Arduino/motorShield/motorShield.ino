// Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009
// this code is public domain, enjoy!


#include <Max3421e.h>
#include <Usb.h>
#include <AndroidAccessory.h>
#include <AFMotor.h>
#include "PIDCont.h"

#include "Constants.h"

//Timers
long arduinoTimer = millis();
long usbTimer = millis();

//VALUES
boolean led8 = false;
boolean flash = false;
boolean blinkValue = false;
boolean showedConnected = false;
boolean showedNotConnected = false;

AF_DCMotor frontLeft(1);
AF_DCMotor frontRight(2);
AF_DCMotor backLeft(3);
AF_DCMotor backRight(4);

int throttle = minSpeed;

int tempCount = 0;

PIDCont PIDroll,PIDpitch,PIDyaw,PIDangleX,PIDangleY;

void setup()
{
  Serial.begin(9600);           // set up Serial library at 9600 bps
  
  //Initilize Motors
  Serial.println("Init All 4 Motors");
  initMotorControl(frontLeft);
  frontLeft.run(BACKWARD);
  initMotorControl(frontRight);
  frontRight.run(FORWARD);
  initMotorControl(backLeft);
  backLeft.run(FORWARD);
  initMotorControl(backRight);
  backRight.run(BACKWARD);
  
  initLeds();
  
  initAndriodConnection();
  
  firstTimeConnecting = true;
 
  PID_init();
}

void loop()
{
  //Get Android Updates For Sensors
  checkUpdates();
  FlightControl();
  updateMotorOutput();
  
  
  if(tempCount == 1000)
  {
    //yawSteer += 10;
    //tempCount = 0; 
  }
  /*
  for(int i = 5; i < 255; i++)
  {
    Serial.print("VALUE: ");
    Serial.println(map(i, 0, 255, minSpeed, maxSpeed));
    frontLeft.setSpeed(map(i, 0, 255, minSpeed, maxSpeed));
    frontRight.setSpeed(map(i, 0, 255, minSpeed, maxSpeed));
    backLeft.setSpeed(map(i, 0, 255, minSpeed, maxSpeed));
    backRight.setSpeed(map(i, 0, 255, minSpeed, maxSpeed));
    delay(500);
  }*/
  
   /*
  Serial.print("VALUE: ");
  Serial.println(map(speedValue, 0, 100, minSpeed, maxSpeed));
  frontLeft.setSpeed(map(speedValue, 0, 100, minSpeed, maxSpeed));
  frontRight.setSpeed(map(speedValue, 0, 100, minSpeed, maxSpeed));
  backLeft.setSpeed(map(speedValue, 0, 100, minSpeed, maxSpeed));
  backRight.setSpeed(map(speedValue, 0, 100, minSpeed, maxSpeed));
  
  delay(10);
  */
  
  /*
  Serial.println("Front Left Test\n");
  runMotorToMaxWithDelay(100, 1000, frontLeft);
  Serial.println("Front Right Test\n");
  runMotorToMaxWithDelay(100, 1000, frontRight);
  Serial.println("Back Left Test\n");
  runMotorToMaxWithDelay(100, 1000, backLeft);
  Serial.println("Back Right Test\n");
  runMotorToMaxWithDelay(100, 1000, backRight);
  */
}

