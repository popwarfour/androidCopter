#define greenPin 37

void initLeds()
{
  pinMode(greenPin, OUTPUT);
  digitalWrite(greenPin, LOW);
}

void setGreenOn()
{
  digitalWrite(greenPin, HIGH); 
}

void setGreenOff()
{
//  digitalWrite(greenPin, LOW); 
}

