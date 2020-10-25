#include <Servo.h>
Servo servo;

bool active = false;
char inactiveFlag = 'a';
char activeFlag = 'b';

int hoseMotor = 4;
int doorMotor = 7;
int sensorPin = A0;

int motorSpinTime = 1000;
int threshold = 600;
int waitTime = 1000;

void setup() {
  pinMode(hoseMotor, OUTPUT);
  pinMode(sensorPin, INPUT);
  servo.attach(doorMotor);

  // Begins serial communications with computer
  Serial.begin(9600);
  // Waits until communications are established to enter main loop
  while (!Serial) {}
}

void loop() {
  int onFire = analogRead(sensorPin);

  if (onFire > threshold && !active)
  {
    // Update active to prevent system from activating twice
    active = true;
    activate();
  }
  else
  {
    int availableBytes = Serial.availableForWrite();
    if (availableBytes >= 1)
    {
      Serial.write(inactiveFlag);
    }
  }
 
/*
  Spins servo motor to close garage door when data is received from python script
  Python script was intended to send data when phone sends message
  Not implemented

  if (Serial.read() != -1)
  {
    servo.write(30);
    delay(motorSpinTime);
    servo.write(0);
  }
*/
  
  delay(waitTime);
}

void activate()
{
  int availableBytes = Serial.availableForWrite();
  
  // Checks if a byte can be written
  if (availableBytes >= 1)
  {
    Serial.write(activeFlag);
    
    // Hose motor also controls garage door
    digitalWrite(hoseMotor, HIGH);
    delay(motorSpinTime);
    digitalWrite(hoseMotor, LOW);
  }
  else
  {
    // If data isn't written, reset active and try again
    active = false;
  }
}
