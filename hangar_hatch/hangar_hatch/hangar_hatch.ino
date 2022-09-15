#include <Servo.h>

#define PIN_SERVO 5
#define PIN_LED_OPEN 2
#define PIN_LED_CLOSE 1

#define ANGLE_OPEN 180
#define ANGLE_CLOSE 90

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position
int openDelay = 3000;
int closeDelay;

int getTimeDelay() {
  return random(2000, 7000);
}

void setup() {
  pinMode(PIN_LED_OPEN, OUTPUT);
  pinMode(PIN_LED_CLOSE, OUTPUT);
  
  openDelay = getTimeDelay();
  myservo.attach(PIN_SERVO);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  digitalWrite(PIN_LED_CLOSE, LOW);
  digitalWrite(PIN_LED_OPEN, HIGH);
  
  myservo.write(ANGLE_OPEN); // open hatch
  delay(openDelay);

  digitalWrite(PIN_LED_CLOSE, HIGH);
  digitalWrite(PIN_LED_OPEN, LOW);
  
  myservo.write(ANGLE_CLOSE); // close hatch
  delay(closeDelay);

  closeDelay = getTimeDelay();
}
