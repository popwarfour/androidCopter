#include <AFMotor.h>

boolean leftOn;
boolean rightOn;

void initMotorControl(AF_DCMotor motor)
{  
  Serial.println("Setting up motor");
  motor.setSpeed(minSpeed);
  
  leftOn = false;
  rightOn = false;
}

void runMotorToMaxWithDelay(int delayTime, int holdTime, AF_DCMotor motor)
{
  for(int i=0; i<255; i++)
  {
    int newSpeed = map(i, 0, 255, minSpeed, maxSpeed);
    //Serial.print("Speed: ");
    Serial.println(newSpeed);
    motor.setSpeed(newSpeed);  
    delay(delayTime);
  }
  delay(holdTime);
  motor.setSpeed(minSpeed);
}

void updateMotorOutput()
{
   if(motor1Speed < 0)
   {
     motor1Speed = 0;//abs(motor1ValueTemp); 
   }
   if(motor2Speed < 0)
   {
     motor2Speed = 0;// = abs(motor2ValueTemp);
   }
   if(motor3Speed < 0)
   {
     motor3Speed = 0;// = abs(motor3ValueTemp);
   }
   if(motor4Speed < 0)
   {
     motor4Speed = 0;// = abs(motor4ValueTemp);
   }
   int motor1SpeedMapped = map(motor1Speed, 0, 255, minSpeed, maxSpeed);
   int motor2SpeedMapped = map(motor2Speed, 0, 255, minSpeed, maxSpeed);
   int motor3SpeedMapped = map(motor3Speed, 0, 255, minSpeed, maxSpeed);
   int motor4SpeedMapped = map(motor4Speed, 0, 255, minSpeed, maxSpeed);
   
   /*
   Serial.println("------ MOTOR OUTPUT VALUES ------");
   Serial.print("F-L: ");
   Serial.print(motor1Speed);
   Serial.print(" ");
   Serial.print("F-R: ");
   Serial.print(motor2Speed);
   Serial.print(" ");
   Serial.print("B-L: ");
   Serial.print(motor3Speed);
   Serial.print(" ");
   Serial.print("B-R: ");
   Serial.print(motor4Speed);
   Serial.println(" ");
   Serial.println("***************************************");
   */
   
   frontLeft.setSpeed(motor1SpeedMapped);
   frontRight.setSpeed(motor2SpeedMapped);
   backLeft.setSpeed(motor3SpeedMapped);
   backRight.setSpeed(motor4SpeedMapped);
}

void turnLeft()
{
  if(leftOn == false)
  {
    frontLeft.setSpeed(map(255, 0, 255, minSpeed, maxSpeed));
    backLeft.setSpeed(map(255, 0, 255, minSpeed, maxSpeed));
    
    leftOn = true;
  }
  else
  {
    frontLeft.run(BRAKE);
    frontLeft.setSpeed(0);
    backLeft.run(BRAKE);
    backLeft.setSpeed(0);
    
    leftOn = false;
  }
}

void turnRight()
{
  if(rightOn == false)
  {
    frontRight.setSpeed(map(255, 0, 255, minSpeed, maxSpeed));
    backRight.setSpeed(map(255, 0, 255, minSpeed, maxSpeed));
    
    rightOn = true;
  }
  else
  {
    frontRight.run(BRAKE);
    frontRight.setSpeed(0);
    backRight.run(BRAKE);
    backRight.setSpeed(0);
    
    rightOn = false;
  }
}

