//Includes the Arduino Stepper Library
#include <Stepper.h>
#include <Adafruit_NeoPixel.h>
#include <AccelStepper.h>

#define LED_PIN 6
#define LED_COUNT 96
#define LED_TRAIL_LEN 10
#define LED_DELAY 30

#define STEPS_PER_REV 32
#define GEAR_REDUCTION 64

#define MOTOR_PIN_1 8
#define MOTOR_PIN_2 9
#define MOTOR_PIN_3 10
#define MOTOR_PIN_4 11

// NeoPixel brightness, 0 (min) to 255 (max)
#define BRIGHTNESS 215 // Set BRIGHTNESS to about 1/5 (max = 255)

// Defines the number of steps per rotation
const int stepsPerRevolution =  STEPS_PER_REV * GEAR_REDUCTION; // 2038
const int stepperSpeed = 15;
const int rotations = 4;

// Pixel variables
int curPixelIdx = 0;
unsigned long lastPixelDelayTime = 0;

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRBW + NEO_KHZ800);

// Creates an instance of stepper class
// Pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence
Stepper myStepper = Stepper(stepsPerRevolution, 8, 10, 9, 11);

AccelStepper stepper(AccelStepper::FULL4WIRE, MOTOR_PIN_1, MOTOR_PIN_3, MOTOR_PIN_2, MOTOR_PIN_4);

void setup() {
  Serial.begin(9600);
  // Nothing to do (Stepper Library sets pins as outputs)
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(BRIGHTNESS);

  stepper.setMaxSpeed(1000.0);
  //stepper.setAcceleration(20);
  stepper.moveTo(stepsPerRevolution * 2);
  stepper.setSpeed(700);
}

void loop() {


//  // Rotate CW slowly at 5 RPM
//  myStepper.setSpeed(stepperSpeed);
//  myStepper.step(stepsPerRevolution * rotations);
//  delay(1000);
//  
//  // Rotate CCW quickly at 10 RPM
//  myStepper.setSpeed(stepperSpeed);
//  myStepper.step(-stepsPerRevolution * rotations);
//  delay(1000);

  if (stepper.distanceToGo() == 0) {
    stepper.stop();
    stepper.moveTo(-stepper.currentPosition());
    stepper.setSpeed(500);
    Serial.println(stepper.currentPosition());
  }
  stepper.runSpeedToPosition();


  //colorWipe(strip.Color(0, 255,   0), 20); // Green
  if (millis() - lastPixelDelayTime >= LED_DELAY) {
    lastPixelDelayTime = millis();
    updatePixelStrip();
  }
}

void updatePixelStrip() {
  strip.setPixelColor(curPixelIdx, strip.Color(0, 255, 0));
  if ((curPixelIdx - LED_TRAIL_LEN) >= 0) {
      strip.setPixelColor(curPixelIdx - LED_TRAIL_LEN, 0);
  } else {
    strip.setPixelColor((strip.numPixels() - LED_TRAIL_LEN) + curPixelIdx, 0);
  }
  strip.show();                          //  Update strip to match
  curPixelIdx = (curPixelIdx + 1 == strip.numPixels()) ? 0 : curPixelIdx + 1;
}

void colorWipe(uint32_t color, int wait) {
  
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)  
 
    if ((i - LED_TRAIL_LEN) >= 0) {
       strip.setPixelColor(i - LED_TRAIL_LEN, 0); 
    }
    strip.show();                          //  Update strip to match
    //delay(wait);                           //  Pause for a moment
  }

  for(int idx = strip.numPixels() - LED_TRAIL_LEN; idx < strip.numPixels() + LED_TRAIL_LEN; idx +=1) {
    strip.setPixelColor(idx, 0); 
    strip.show();                          //  Update strip to match
    //delay(wait);                           //  Pause for a moment
  }
}
