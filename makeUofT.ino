#include <Wire.h>
#include <ADXL345.h>
ADXL345 adxl;

int in1 = 2; 
int in2 = 3; 
int in3 = 4; 
int in4 = 7; 
int pwr1 = 5; 
int pwr2 = 6; 
int trig = 9; 
int echo = 8; 
int rmax = 5; 
int last = -1; 
bool runLoop = true; 

int led1 = 13; 
int led2 = 12; 
int led3 = 11; 

int maxs = 130; 

void setup() {
  // put your setup code here, to run once:
  pinMode(in1, OUTPUT); 
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT); 
  pinMode(in4, OUTPUT); 
  pinMode(pwr1, OUTPUT); 
  pinMode(pwr2, OUTPUT); 
  pinMode(trig, OUTPUT); 
  pinMode(echo, INPUT); 
  acceSetup(); 

  pinMode(led1, OUTPUT); 
  pinMode(led2, OUTPUT); 
  pinMode(led3, OUTPUT); 
  
  Serial.begin(9600); 
  Serial.println("start"); 

  analogWrite(pwr1, maxs);
  analogWrite(pwr2, maxs);
  delay(5000); 
  
}

void loop() {
  colours(); 
  if (!accel()) runLoop = false; 
  if (runLoop){
    Serial.println("loop"); 
    int rdirection = random(0, 3); 
    while (rdirection == last) rdirection = random(0, 3); 
    int rtime = random(1, rmax) * 1000; 
    bool obstruction = false; 
  
    Serial.println(rtime); 
    long start = millis(); 
    while (millis() - start < rtime && ultra() == false){
    }
    //stop(); 
    
    if (ultra()){
      Serial.println("obstruction"); 
      obstruction = true; 
      rdirection = 2; 
    }
    if (obstruction && !ultra()){
      Serial.println("obstruction cleared"); 
      //stop(); 
      rdirection = 0; 
    }
  
    switch(rdirection){
      case 0: 
        forward(); 
        rmax = 5; 
        break; 
      case 1: 
        rightTurn(); 
        rmax = 1; 
        break;
      case 2: 
        leftTurn();
        rmax = 1; 
        break;    
    }
    last = rdirection; 
   //startt();
  } 
  else Serial.println("end program"); 
}

void startt(){
  for (int i = 0; i <= 255; i++){
    analogWrite(pwr1, i);
    analogWrite(pwr2, i);
    delay(20);
  }
}

void forward(){ 
  Serial.println("forward"); 
  digitalWrite(in1, HIGH); 
  digitalWrite(in2, LOW); 
  digitalWrite(in3, HIGH); 
  digitalWrite(in4, LOW); 
}

void backward(){
  Serial.println("backward"); 
  digitalWrite(in1, LOW); 
  digitalWrite(in2, HIGH); 
  digitalWrite(in3, LOW); 
  digitalWrite(in4, HIGH); 
}

void leftTurn(){
  Serial.println("leftTurn"); 
  digitalWrite(in1, LOW); 
  digitalWrite(in2, HIGH); 
  digitalWrite(in3, HIGH); 
  digitalWrite(in4, LOW); 
}

void rightTurn(){
  Serial.println("rightTurn"); 
  digitalWrite(in1, HIGH); 
  digitalWrite(in2, LOW); 
  digitalWrite(in3, LOW); 
  digitalWrite(in4, HIGH);
}

void stop(){
  Serial.println("stop"); 
  for (int i = 255; i >= 0; --i){
    analogWrite(pwr1, i);
    analogWrite(pwr2, i);
    delay(20);
  } 
}

bool ultra(){
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  long duration = pulseIn(echo, HIGH);
  if (duration*0.034/2 < 20) return true; 
  else return false; 
}

void acceSetup(){
  adxl.powerOn();

    //set activity/ inactivity thresholds (0-255)
    adxl.setActivityThreshold(75); //62.5mg per increment
    adxl.setInactivityThreshold(75); //62.5mg per increment
    adxl.setTimeInactivity(10); // how many seconds of no activity is inactive?

    //look of activity movement on this axes - 1 == on; 0 == off
    adxl.setActivityX(1);
    adxl.setActivityY(1);
    adxl.setActivityZ(1);

    //look of inactivity movement on this axes - 1 == on; 0 == off
    adxl.setInactivityX(1);
    adxl.setInactivityY(1);
    adxl.setInactivityZ(1);

    //look of tap movement on this axes - 1 == on; 0 == off
    adxl.setTapDetectionOnX(0);
    adxl.setTapDetectionOnY(0);
    adxl.setTapDetectionOnZ(1);

    //set values for what is a tap, and what is a double tap (0-255)
    adxl.setTapThreshold(50); //62.5mg per increment
    adxl.setTapDuration(15); //625us per increment
    adxl.setDoubleTapLatency(80); //1.25ms per increment
    adxl.setDoubleTapWindow(200); //1.25ms per increment

    //set values for what is considered freefall (0-255)
    adxl.setFreeFallThreshold(7); //(5 - 9) recommended - 62.5mg per increment
    adxl.setFreeFallDuration(45); //(20 - 70) recommended - 5ms per increment

    //setting all interrupts to take place on int pin 1
    //I had issues with int pin 2, was unable to reset it
    adxl.setInterruptMapping(ADXL345_INT_SINGLE_TAP_BIT,   ADXL345_INT1_PIN);
    adxl.setInterruptMapping(ADXL345_INT_DOUBLE_TAP_BIT,   ADXL345_INT1_PIN);
    adxl.setInterruptMapping(ADXL345_INT_FREE_FALL_BIT,    ADXL345_INT1_PIN);
    adxl.setInterruptMapping(ADXL345_INT_ACTIVITY_BIT,     ADXL345_INT1_PIN);
    adxl.setInterruptMapping(ADXL345_INT_INACTIVITY_BIT,   ADXL345_INT1_PIN);

    //register interrupt actions - 1 == on; 0 == off
    adxl.setInterrupt(ADXL345_INT_SINGLE_TAP_BIT, 1);
    adxl.setInterrupt(ADXL345_INT_DOUBLE_TAP_BIT, 1);
    adxl.setInterrupt(ADXL345_INT_FREE_FALL_BIT,  1);
    adxl.setInterrupt(ADXL345_INT_ACTIVITY_BIT,   1);
    adxl.setInterrupt(ADXL345_INT_INACTIVITY_BIT, 1);
}

bool accel(){
  int x, y, z;
  adxl.readXYZ(&x, &y, &z); //read the accelerometer values and store them in variables  x,y,z
  // Output x,y,z values
  Serial.print("values of X , Y , Z: ");
  Serial.print(x);
  Serial.print(" , ");
  Serial.print(y);
  Serial.print(" , ");
  Serial.println(z);
  if (x > 50 || y > 100 || y < -100 || z > 50){
    Serial.println("over limit"); 
    return false; 
  }
  return true; 
}

void colours(){
  analogWrite (led1, random(255)); 
  analogWrite (led2, random(255)); 
  analogWrite (led3, random(255)); 
}
