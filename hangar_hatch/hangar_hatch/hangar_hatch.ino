#include <Servo.h>

#define PIN_SERVO 9

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position


void setup() {
  myservo.attach(PIN_SERVO);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  // put your main code here, to run repeatedly:
  myservo.write(90);
  delay(2000);
  myservo.write(0);
  delay(2000);
}
