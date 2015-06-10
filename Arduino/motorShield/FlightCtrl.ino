void FlightControl(){

  throttle=map(speedSteer,minSpeed,maxSpeed,0,100);
  
  float mappedYaw = map(yawSensor,-10,10,-10,10);
  float mappedRoll = map(rollSensor,-10,10,-10,10);
  float mappedPitch = map(pitchSensor,-10,10,-10,10);

  PIDroll_val = (int)PIDroll.Compute((float)rollSteer-mappedRoll);
  if(mappedRoll == 0)
  {
    PIDroll_val = 0;
  }
  PIDpitch_val = (int)PIDpitch.Compute((float)pitchSteer-mappedPitch);
  if(mappedPitch == 0)
  {
    PIDpitch_val = 0;
  }
  
  String turnDirection = "";
  int change = 0;
  if(abs(yawSteer - yawSensor) < 10)
  {
    //We are close enough to our angle
    PIDyaw_val = 0;
  }
  else
  {
    //We Need To Make Adjustments
    //Find Shortest Direction To New Angle
    //Rights are positive
    //Lefts are negative
    if((yawSensor + 180) > 360)
    {
      //Serial.println("***********************PIVOT ON RIGHT");
      //Pivot on Right
      int top = (yawSensor + 180) - 360;
      if(yawSteer > yawSensor & yawSteer <= 360)
      {
        //Serial.println("***********************TURN RIGHT 1");      
        turnDirection = "right";
        //Steer RIGHT
        change = yawSteer - yawSensor;
      }
      else if(yawSteer > 0 & yawSteer <= top)
      {
        //Serial.println("***********************TURN RIGHT 2");   
        turnDirection = "right";
        change = (360 - yawSensor) + yawSteer;
      }
      else
      {
        //Serial.println("***********************TURN LEFT 1");
        turnDirection = "left";
        //Steer LEFT
        change = abs(yawSensor - yawSteer);
        change *= -1;
      }
    }
    else if((yawSensor - 180) < 0)
    {
      Serial.println("***********************PIVOT ON LEFT");
      //Pivot on Left
      int top = 360 + (yawSensor - 180);
      if(yawSteer > top & yawSteer <= 360)
      {
        //Serial.println("***********************TURN LEFT 2");
        turnDirection = "left";
        change = yawSensor + (360 - yawSteer);
        change *= -1;
      }
      else if(yawSteer > 0 & yawSteer <= yawSensor)
      {
        //Serial.println("***********************TURN LEFT 3");
        turnDirection = "left";
        change = abs(yawSensor - yawSteer);
        change *= -1;
      }
      else
      {
        //Serial.println("***********************TURN RIGHT 3");
        turnDirection = "right";
        change = yawSteer - yawSensor;
      }
    }
    else
    {
      turnDirection = "unknown - on pivot";
      //Serial.println("********************* ON PIVOT ");
      if((yawSensor == 0 || yawSensor == 360) & yawSteer <= 180)
      {
         change = yawSteer - yawSensor;
      }
      else if((yawSensor == 0 || yawSensor == 360) & yawSteer > 180)
      {
        change = abs(360 - yawSteer);
        change *= -1;
      }
      else if((yawSensor == 180) & yawSteer >= 180 & yawSteer < 360)
      {
        change = yawSteer - yawSensor;
      }
      else if((yawSensor == 180) & yawSteer <= 180 & yawSteer > 0)
      {
        change = abs(yawSensor - yawSteer);
        change *= -1;
      }
    }  
    
    Serial.print("Sensor: ");
    Serial.print(yawSensor);
    Serial.print(" - Steer: ");
    Serial.print(yawSteer);
    Serial.print(" - Change: ");
    Serial.print(change);
    Serial.print(" - Direction: ");
    Serial.println(turnDirection);
    
    PIDyaw_val = (int)PIDyaw.Compute(change);  
  }
  
  
  /*
  Serial.println("***************************************");
  Serial.println("***************************************");
  Serial.println("***************************************");
  Serial.println("----- SENSOR VALUES -------");
  Serial.print("ROLL: ");
  Serial.print(rollSensor);
  Serial.print(" PITCH: ");
  Serial.print(pitchSensor);
  Serial.print(" YAW: ");
  Serial.println(yawSensor);
  Serial.println("***************************************");
  Serial.println("------ PID VALUES ------");
  Serial.print("PID PITCH: ");
  Serial.print(PIDpitch_val);
  Serial.print(" PID ROLL: ");
  Serial.print(PIDroll_val);
  Serial.print(" PID YAW: ");
  Serial.println(PIDyaw_val); 
  Serial.println("***************************************");
  Serial.println("------ STEERING VALUES -------");
  Serial.print("Throttle: ");
  Serial.print(speedSteer);
  Serial.print(" ROLL STEER: ");
  Serial.print(rollSteer);
  Serial.print(" PITCH STEER: ");
  Serial.print(pitchSteer);
  Serial.print(" YAW STEER: ");
  Serial.print(yawSteer);
  Serial.print(" (change): ");
  Serial.println(change);
  Serial.println("***************************************");
  */
  
  //LEFTS
  motor1Speed = throttle+PIDroll_val+PIDpitch_val+PIDyaw_val;
  motor3Speed = throttle+PIDroll_val-PIDpitch_val-PIDyaw_val;
  
  //RIGHTS
  motor2Speed = throttle-PIDroll_val+PIDpitch_val-PIDyaw_val;
  motor4Speed = throttle-PIDroll_val-PIDpitch_val+PIDyaw_val; 
}

