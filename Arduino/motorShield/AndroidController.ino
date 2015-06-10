// ADK CONFIG
AndroidAccessory acc("X3R", "Rover", "Remote control rover", "0.1", "http://www.bovbel.com", "0000000012345678");

//FREQUENCY
#define ARDUINO_FREQ 200
#define USB_FREQ 200

void initAndriodConnection()
{
  Serial.println("Powering On ADK Accessory");
  //Power Up ADK
  acc.powerOn();
}

void checkUpdates()
{
  byte msg[64];
 
  if(acc.isConnected())
  {
    setGreenOn();
  }
  else
  {
    Serial.println("FIRST CONDICTIONAL NOT CONNECTION");
    setGreenOff();
    frontLeft.setSpeed(0);
    frontRight.setSpeed(0);
    backLeft.setSpeed(0);
    backRight.setSpeed(0);
  }

  if(acc.isConnected() && millis()-usbTimer >= 1000/USB_FREQ)
  {    
    Serial.print("MADE IT TO TIMER PART!!");
    usbTimer = millis();
		
    int len = acc.read(msg, sizeof(msg), 1); // read data into msg variable
    if(len > 0)
    {
      Serial.println("Received message"); 
      //Sensor Values From Android
      int rollTemp = 0;
      int pitchTemp = 0;
      int yawTemp = 0;
      
      //Steering & Throttle Values From Android
      unsigned int speedTemp = 0;
      unsigned int tempSteerYawLeft = 0;
      unsigned int tempSteerYawRight = 0;
      unsigned int tempSteerRollLeft = 0;
      unsigned int tempSteerRollRight = 0;
      unsigned int tempSteerPitchForward = 0;
      unsigned int tempSteerPitchBackwards = 0;


      speedTemp = msg[0];
      tempSteerRollLeft = msg[1] & 00000011;
      tempSteerRollRight = msg[1] & 00001100;
      tempSteerYawLeft = msg[1] & 00110000;
      tempSteerYawRight = msg[1] & 11000000;
      tempSteerPitchForward = msg[2] & 00000011;
      tempSteerPitchBackwards = msg[2] & 00001100;
      
      rollTemp = msg[3];
      pitchTemp = msg[4];
      yawTemp = msg[5];
      
//      for(int i = 0; i < 4; i++)
//      {
//        rollTemp = (rollTemp << 8) | msg[i];
//      }
//      for(int i = 4; i < 8; i++)
//      {
//        pitchTemp = (pitchTemp << 8) | msg[i];
//      }
//      for(int i = 8; i < 12; i++)
//      {
//        speedTemp = (speedTemp << 8) | msg[i];
//      }
//      for(int i = 12; i < 16; i++)
//      {
//        yawTemp = (yawTemp << 8) | msg[i];
//      }
//      for(int i = 16; i < 20; i++)
//      {
//        tempSteerYaw = (tempSteerYaw << 8) | msg[i];
//      }
//      for(int i = 20; i < 24; i++)
//      {
//        tempSteerPitch = (tempSteerPitch << 8) | msg[i];
//      }
//      for(int i = 24; i < 28; i++)
//      {
//        tempSteerRoll = (tempSteerRoll << 8) | msg[i];
//      }
      
      //Throttle And Sensor Values
      rollSensor = rollTemp / 10;
      pitchSensor = pitchTemp / 10;
      speedSteer = speedTemp; 
      yawSensor = yawTemp;
      
      Serial.print("Throttle: " + speedSteer);
      Serial.print(" Yaw Left: " + tempSteerYawLeft);
      Serial.print(" Yaw Right: " + tempSteerYawRight);
      Serial.print(" Roll Left: " + tempSteerRollLeft);
      Serial.print(" Roll Right: " + tempSteerRollRight);
      Serial.print(" Pitch Forward: " + tempSteerPitchForward);
      Serial.print(" Pitch Backwards: " + tempSteerPitchBackwards);  
      Serial.print(" RollSensor: " + rollTemp / 10);
      Serial.print(" PitchSensor: " + pitchTemp / 10);
      Serial.println(" YawSesnor: " + yawTemp);

      //Steering Values
//      if(tempSteerYaw != 0)
//      {
//
//        //Normalize New Yaw Steering Value to degrees if we are receiving a steering value from the remote
//        if((yawSteer + tempSteerYaw) < 0)
//        {
//          //If we go to the left past 0
//          yawSteer = 360 + yawSteer + tempSteerYaw;
//        }
//        else if((yawSteer + tempSteerYaw) > 360)
//        {
//          //If we go to the right past 360
//          yawSteer = (yawSteer + tempSteerYaw) - 360;
//        }
//        else
//        {
//          //No adjustmentes needed!
//          yawSteer = yawSteer + tempSteerYaw;
//        }
//      }
//      
//      if(pitchSteer != 0)
//      {
//        pitchSteer = tempSteerPitch;
//      }
//      if(rollSteer != 0)
//      {
//        rollSteer = tempSteerRoll;
//      }
//      
//      if(yawSensor != 0 && firstTimeConnecting == true)
//      {        
//        firstTimeConnecting = false;
//        
//        //Set initial Steering Yaw To Be Current Sensor Value...
//        yawSteer = yawSensor;
//      }
    } 
  }
  else
  {
    Serial.println("Second conditional, NOT CONNECTED!");
  }
}
