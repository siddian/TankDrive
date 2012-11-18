#include <AFMotor.h>

#define channumber 6
 
#define SignalPin 9

int value[channumber];
double ValueNormalized[channumber];

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);

void setup() {
  Serial.begin(115200);           // set up Serial library at 115200 bps
  Serial.println("Driving!!");

  // turn on motor
  motor1.setSpeed(80);
  motor2.setSpeed(80);
 
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  
  pinMode(SignalPin, INPUT); //Pin 3 as input
}

int val;

void loop() {
  if(pulseIn(SignalPin, HIGH) > 2000) {
    for(int x=0; x < channumber; x++) {
      //Loop to store all the channel position
      value[x]=pulseIn(SignalPin, HIGH);
      ValueNormalized[x] = value[x] - 500;
      ValueNormalized[x] /= 1000;
    }
 
//    Serial.print(ValueNormalized[2]); //gas
//    Serial.print(" ");
//    Serial.print(ValueNormalized[3]); //yaw
//    Serial.print(" ");
//    Serial.print(ValueNormalized[0]); //pitch
//    Serial.print(" ");
//    Serial.print(ValueNormalized[1]); //roll
//    Serial.print(" ");
//    Serial.print(ValueNormalized[4]); //switch
//    Serial.print(" ");
//    Serial.print(ValueNormalized[5]); //not used
//    Serial.println(""); //Start a new line
  }
//  Serial.println(val);
  
  int motor1speed = map(value[0] - 500, 90, 900, -200, 200);
  int motor2speed = map(value[2] - 500, 90, 900, -200, 200);
  
//  Serial.println(motor1speed);
  if (motor1speed < 0) {
    motor1.setSpeed(-motor1speed);
    motor1.run(BACKWARD);
  } else {
    motor1.setSpeed(motor1speed);
    motor1.run(FORWARD);
  }

//  Serial.println(motor2speed);
  if (motor2speed < 0) {
    motor2.setSpeed(-motor2speed);
    motor2.run(BACKWARD);
  } else {
    motor2.setSpeed(motor2speed);
    motor2.run(FORWARD);
  }
  
//  Serial.println("RELEASE");
//  motor1.run(RELEASE);
//  motor2.run(RELEASE);
//  delay(1000);
}
