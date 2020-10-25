bool active = false;
char inactiveFlag = 'a';
char activeFlag = 'b';

int hoseMotor = 4;
int sensorPin = A0;

int motorSpinTime = 1000;
int threshold = 600;

void setup() {
  pinMode(hoseMotor, OUTPUT);
  pinMode(sensorPin, INPUT);

  // Begins serial communications with computer
  Serial.begin(9600);
  // Waits until communications are established to enter main loop
  while (!Serial) {}
}

void loop() {
  int onFire = analogRead(sensorPin);

  if (onFire > 600 && !active)
  {
    active = true;
    activate();
  }
  else
  {
    int availableBytes = Serial.availableForWrite();
    if (availableBytes >= 1)
    {
      Serial.write("a");
    }
  }

  if (Serial.read() != -1)
  {
    servo.write(30);
    delay(motorSpinTime);
    servo.write(0);
  }
 
  delay(1000);
}

void activate()
{
  int availableBytes = Serial.availableForWrite();
  if (availableBytes >= 1)
  {
    Serial.write("b");
    digitalWrite(hoseMotor, HIGH);
    delay(motorSpinTime);
    digitalWrite(hoseMotor, LOW);
  }
  else
  {
    active = false;
  }
}
