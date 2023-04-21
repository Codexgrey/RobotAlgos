#include <QTRSensors.h>
#include <Servo.h>


QTRSensors qtr;
Servo myservo;
int pos = 20; 
const uint8_t SensorCount = 6;
uint16_t sensorValues[SensorCount];
int S1=9; // rs
int S2=3; // ls

// rs motor
int motorPinA1 = 7; // P
int motorPinA2 = 6; // n

// ls motor
int motorPinB1 = 5; // P
int motorPinB2 = 4; // n


// threshold values for black color detection on Sensor Array
int threshLow = 1500;
int threshHigh = 2500;


void setup(){
  // configure the sensors
  qtr.setTypeRC();
  qtr.setSensorPins((const uint8_t[]){A0,A1,A2,A3,A4,A5}, SensorCount);
  pinMode(S1,INPUT); 
  pinMode(S2,INPUT);
  pinMode(motorPinA1,OUTPUT);
  pinMode(motorPinA2,OUTPUT);
  pinMode(motorPinB1,OUTPUT);
  pinMode(motorPinB2,OUTPUT);
  Serial.begin(9600);
  myservo.attach(11);
}


void loop() {
  // read raw sensor values
  qtr.read(sensorValues);
  int O1=digitalRead(S1); // rs
  int O2=digitalRead(S2); // ls


  // check if the sensors detect black color within the threshold range
  int isBlack = 0;
  for (uint8_t i = 0; i < SensorCount; i++) {
    if (sensorValues[i] >= threshLow && sensorValues[i] <= threshHigh) {
      isBlack = 1;
      Serial.print(sensorValues[i]);
      Serial.print('\n');
      break;
    }
  }

  // Serial.println(isBlack);
  Serial.println(O1); // rs
  Serial.println(O2); // ls
 

  // if ls and rs are both on white 
  if ( isBlack && O2 == 0 && O1 == 0 ){
    // move forward
    digitalWrite(motorPinA1, HIGH);
    digitalWrite(motorPinA2, LOW);
    digitalWrite(motorPinB1, HIGH);
    digitalWrite(motorPinB2, LOW);
  }

  // if ls and rs are on black, white
  else if ( O2 == isBlack && O1 == 0) { // O2 == 1
    // ls is black, turn left
    digitalWrite(motorPinA1, HIGH);
    digitalWrite(motorPinA2, LOW);
    digitalWrite(motorPinB1, LOW);
    digitalWrite(motorPinB2, LOW);
  }

  // if ls and rs are on white, black
  else if ( O2 == 0 && O1 == isBlack) { // O1 == 1
    // rs is black, turn right
    digitalWrite(motorPinA1, LOW);
    digitalWrite(motorPinA2, LOW);
    digitalWrite(motorPinB1, HIGH);
    digitalWrite(motorPinB2, LOW);
  }

  // if ls and rs are both on black/white and equal to isBlack
  else if (O2 == isBlack && isBlack == O1) {
    // Stop
    digitalWrite(motorPinA1, LOW);
    digitalWrite(motorPinA2, LOW);
    digitalWrite(motorPinB1, LOW);
    digitalWrite(motorPinB2, LOW);
  }

  // delay(1000);

  for (pos = 20; pos <= 160; pos += 1) { 
    // in steps of 1 degree
    // myservo.write(pos);              
    // delay(15);                      
  }
  
  for (pos = 160; pos >= 20; pos -= 1) { 
    // myservo.write(pos);              
    // delay(15);                       
  }
}

  /** // if ls and rs are black, white
  else if ( O2 == 1 && O1 == 1) { //isBlack &&
    // Move backward
    digitalWrite(motorPinA1, LOW);
    digitalWrite(motorPinA2, HIGH);
    digitalWrite(motorPinB1, LOW);
    digitalWrite(motorPinB2, HIGH);
    Serial.println();
  } **/ 