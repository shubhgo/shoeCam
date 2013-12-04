const int activateButton = 2;
const int cameraButton = 3;
const int flashPin = 13;
const int motorPin = 9;

int activateButtonState = 0;
int activateFirstTap = 0;
unsigned long activateFirstTapTime = 0;

boolean activeNow = false;
unsigned long activatedAt = 0;
float doubleTapTime = 2000;
float autoDeactivateTime = 3000;

float motorOnTime = 1000;
unsigned long motorTurnedOnAt = 0;


void setup()
{
  pinMode(flashPin, OUTPUT);
  pinMode(activateButton, INPUT);
  Serial.begin(9600);
  Serial.println("setup");
}


void loop()
{
  if (shouldActivate())
  {
    Serial.println("turn On");
    shouldTurnOnFlashLight(true);
    activatedAt = millis();
    activeNow = true;
  }
  
  if (shouldDeactivate())
  {
    Serial.println("auto Off");
    shouldTurnOnFlashLight(false);
    activatedAt = 0;
    activeNow = false;
  }
  
  if (motorTurnedOnAt > 0)
  {
    // Oh no! the motor is on!
    if (shouldTurnMotorOff)
    {
      motorTurnedOnAt = 0;
      turnMotorOn(false);
    }
  }
  
  if (activeNow)
  {
    int clickButtonPressed = digitalRead(cameraButton);
    if (clickButtonPressed)
    {
      Serial.println("Click!");
      activatedAt = 0;
      activeNow = false;
       tower
      // 1 Flashlight off
      shouldTurnOnFlashLight(false);
      
      // 2 Take a picture
      takePicture();
      
      // 3 Motor on for some time
      motorTurnedOnAt = millis();;
      turnMotorOn(true);
      
      // 4 get location
      // 5 upload to net
    }
  }
}


void shouldTurnOnFlashLight(boolean state)
{
  if(state == true)
  {
    digitalWrite(flashPin, HIGH);
  }
  else
  {
    digitalWrite(flashPin, LOW);
  }
}


boolean shouldDeactivate()
{
  if (activatedAt == 0)
  {
    return false;
  }
  
  int currentTime = millis();
  if ((currentTime - activatedAt) > autoDeactivateTime)
  {
    return true;
  }else
  {
    return false;
  }
}


boolean shouldActivate()
{
  activateButtonState = digitalRead(activateButton);
  if (activateButtonState == HIGH)
  {
    delay(250);
    // first press
    if (activateFirstTap == 0)
    {
//      Serial.println("first tap");
      activateFirstTap = 1;
      activateFirstTapTime = millis();
      return false;
    }else
    {
      // second tap
      int currentTime = millis();
      if ((currentTime-activateFirstTapTime)<doubleTapTime)
      {
//        Serial.println("second tap");
        // activate
        activateFirstTap = 0;
        activateFirstTapTime = 0;
        return true;
      }
      else
      {
//        Serial.println("late first tap");
        // deactivate and register first tap
        activateFirstTap = 1;
        activateFirstTapTime = millis();
        return false;
      }
    }
  }
}


void takePicture()
{
  Serial.println("takePicture: __incomplete__");
}


boolean shouldTurnMotorOff()
{
  int currentTime = millis();
  if ((currentTime-motorTurnedOnAt)>motorOnTime)
  {
    return true;
  }
  else
  {
    return false;
  }
}


void turnMotorOn(boolean state)
{
  if (state)
  {
    analogWrite(motorPin, 254);
  }
  else
  {
    analogWrite(motorPin, 0);
  }
}

