const int activateButton = 2;
const int cameraButton = 3;
const int location1Button = 4;
//const int location2Button = 5;
const int flashPin = 10;
const int motorPin = 9;
const int debugPin = 13;

int activateButtonState = 0;
int activateFirstTap = 0;
int deAtivateFirstTap = 0;
unsigned long activateFirstTapTime = 0;

boolean activeNow = false;
unsigned long activatedAt = 0;
float doubleTapTime = 2000;
float autoDeactivateTime = 10000;

boolean activeOOINow = false;
unsigned long activatedOOIAt= 0;

float motorOnTime = 1000;
unsigned long motorTurnedOnAt = 0;


void setup()
{
  pinMode(flashPin, OUTPUT);
  pinMode(debugPin, OUTPUT);
  pinMode(activateButton, INPUT);
  Serial.begin(9600);
  Serial.println("setup");
}


void loop()
{
  if (shouldActivate())
  {
    Serial.println("activated");
    shouldTurnOnFlashLight(true);
    activatedAt = millis();
    activeNow = true;
  }

  if (shouldDeactivate())
  {
    Serial.println("deactivated");
    shouldTurnOnFlashLight(false);
    activatedAt = 0;
    activeNow = false;
  }

  if (shouldTurnMotorOff())
  {
    // Serial.println("shouldTurnMotorOff");
    // Oh no! the motor is on!
    motorTurnedOnAt = 0;
    turnMotorOn(false);
  }

  if (nearOOI())
  {
    digitalWrite(debugPin, HIGH);
    // near obeject of Interest 
    Serial.println("near OOI");
    activatedOOIAt = millis();
    activeOOINow = true;

    // Turn on the motor
    motorTurnedOnAt = millis();
    ;
    turnMotorOn(true);
  }

  if (awayFromOOI())
  {
    digitalWrite(debugPin, LOW);
    Serial.println("awayFromOOI");
    activatedOOIAt = 0;
    activeOOINow = false;
  }


  if (activeOOINow)
  {
    //    digitalWrite(debugPin, HIGH);
    int likeButtonPressed = digitalRead(cameraButton);
    if (likeButtonPressed)
    {
      digitalWrite(debugPin, LOW);
      Serial.println("Liked");
      activatedOOIAt = 0;
      activeOOINow = false;

      // Turn on the motor
      motorTurnedOnAt = millis();
      ;
      turnMotorOn(true);
      //TODO: Like function
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

      // 1 Flashlight off
      shouldTurnOnFlashLight(false);

      // 2 Take a picture
      takePicture();

      // 3 Motor on for some time
      motorTurnedOnAt = millis();
      ;
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
    // shoe is deactive
    return false;
  }

  long currentTime = millis();
  if ((currentTime - activatedAt) > autoDeactivateTime)
  {
    // auto deactivate
    deAtivateFirstTap = 0;
    return true;
  }
  else
  {
    // currently active
    int deActivateButtonState = digitalRead(activateButton);
    if (deActivateButtonState == HIGH)
    {
      delay(250);
      if (deAtivateFirstTap == 0)
      {
        //Serial.println("deactivate first tap");
        deAtivateFirstTap = 1;
        return false;
      }
      else
      {
        //Serial.println("deactivate second tap");
        deAtivateFirstTap = 0;
        return true;
      }
    }
    return false;
  }

  activateButtonState = digitalRead(activateButton);
  if (activateButtonState == HIGH)
  {
    delay(50);
    // first press
    if (activateFirstTap == 0)
    {
      //      Serial.println("first tap");
      activateFirstTap = 1;
      activateFirstTapTime = millis();
      return false;
    }
    else
    {
      // second tap
      long currentTime = millis();
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


boolean shouldActivate()
{
  if (activeNow)
  {
    return false;
  }
  else
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
      }
      else
      {
        // second tap
        long currentTime = millis();
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
}


void takePicture()
{
  Serial.println("takePicture: __incomplete__");
}


boolean shouldTurnMotorOff()
{
  if (motorTurnedOnAt > 0)
  {
    long currentTime = millis();
    if ((currentTime-motorTurnedOnAt)>motorOnTime)
    {
      return true;
    }
    else
    {
      return false;
    }
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


boolean nearOOI()
{
  //Serial.println("nearOOI: checking function");
  if(activeOOINow)
  {
    return false;
  }
  else
  {
    int location1Status = digitalRead(location1Button);
    if (location1Status == HIGH)
    {
      Serial.println("location1Status: HIGH");
      delay(250);
      return true;
    }
    else
    {
      return false;
    }
  }
  //TODO: add more locations
  //TODO: make it location specific
}

boolean awayFromOOI()
{
  if (activatedOOIAt > 0)
  {
    long awayFromOOIcurrentTime = millis();
    if ((awayFromOOIcurrentTime - activatedOOIAt) > autoDeactivateTime)
    {
      Serial.println(activatedOOIAt);
      Serial.println(awayFromOOIcurrentTime - activatedOOIAt);
      return true;
    }
    else
    {
      //Serial.println("____: in time");
      return false;
    }
  }
  else
  {
    //Serial.println("____: idle");
    return false;
  }
}

