int pinCarRed=17;
int pinCarYellow=16;
int pinCarGreen=15;
int pinWalkRed=14;
int pinWalkGreen=13;
int buttonInput=2;

// System parameters
int yellowForCarsSeconds=5;
int yellowForPedestrianSeconds=5;
int carsGreenTimeoutSeconds=5;
int pdestrianGreenTimeoutSeconds=3;
int pedButtonPressed=0;

void setup()   {                
  Serial.begin(38400);
  pinMode(buttonInput, INPUT);  
  pinMode(pinCarRed, OUTPUT);
  pinMode(pinCarYellow, OUTPUT);
  pinMode(pinCarGreen, OUTPUT);
  pinMode(pinWalkRed, OUTPUT);
  pinMode(pinWalkGreen, OUTPUT);
  //carsCanGo();
  attachInterrupt(digitalPinToInterrupt(buttonInput), interrupted, FALLING);
}

void interrupted(){
  Serial.println("Pedestrian pressed the button");
  Serial.println(pedButtonPressed);
  pedButtonPressed=1;
}

void carsCanGo() {
  Serial.println("Cars green");
  digitalWrite(pinCarRed, LOW);
  digitalWrite(pinCarYellow, LOW);
  digitalWrite(pinCarGreen, HIGH);
  digitalWrite(pinWalkGreen, LOW);  
  digitalWrite(pinWalkRed, HIGH);
  delay(carsGreenTimeoutSeconds * 1000);
  if (pedButtonPressed==1) {
    statusYellowForCars();
  }
}

void pedestrianCanGo() {
  Serial.println("Pedestrian green");  
  pedButtonPressed=0;
  digitalWrite(pinCarRed, HIGH);
  digitalWrite(pinCarYellow, LOW);
  digitalWrite(pinCarGreen, LOW);
  digitalWrite(pinWalkGreen, HIGH);  
  digitalWrite(pinWalkRed, LOW);
  delay(pdestrianGreenTimeoutSeconds * 1000);
  statusYellowForPedestrians();
}

void statusYellowForCars() {
  Serial.println("Yellow for cars");
  digitalWrite(pinCarRed, LOW);
  digitalWrite(pinCarYellow, HIGH);
  digitalWrite(pinCarGreen, LOW);
  digitalWrite(pinWalkGreen, LOW);  
  digitalWrite(pinWalkRed, HIGH);  
  delay(yellowForCarsSeconds * 1000);
  pedestrianCanGo();
}

void statusYellowForPedestrians() {
  Serial.println("Yellow for pedestrian");  
  digitalWrite(pinCarRed, HIGH);
  digitalWrite(pinCarYellow, LOW);
  digitalWrite(pinCarGreen, LOW);
  // Walk green blink
  digitalWrite(pinWalkRed, LOW);
  blinkForXMilliSeconds(pinWalkGreen, 500, 500, yellowForPedestrianSeconds * 1000);
  carsCanGo();
}

void blinkForXMilliSeconds(int led, long onTimeMS, long offTimeMS, long blinkForMS) {
  unsigned long expirationTime = millis()+blinkForMS;
  while (millis() < expirationTime) {
      digitalWrite(led, HIGH);  // turn the LED on (HIGH is the voltage level)
      delay(onTimeMS);                  // wait
      digitalWrite(led, LOW);   // turn the LED off by making the voltage LOW
      delay(offTimeMS);                 // wait
  }
}

void loop()                     
{
  carsCanGo();
  delay(50);
}
