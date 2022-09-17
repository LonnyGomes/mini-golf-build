//Includes the Arduino Stepper Library
#include <Stepper.h>
#include <Adafruit_NeoPixel.h>

#define LED_PIN 6
#define LED_COUNT 96
#define LED_TRAIL_LEN 10

// NeoPixel brightness, 0 (min) to 255 (max)
#define BRIGHTNESS 215 // Set BRIGHTNESS to about 1/5 (max = 255)

// Defines the number of steps per rotation
const int stepsPerRevolution = 2038;
const int stepperSpeed = 15;
const int rotations = 4;

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRBW + NEO_KHZ800);

// Creates an instance of stepper class
// Pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence
Stepper myStepper = Stepper(stepsPerRevolution, 8, 10, 9, 11);

void setup() {
  // Nothing to do (Stepper Library sets pins as outputs)
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(BRIGHTNESS);
}

void loop() {
  colorWipe(strip.Color(0, 255,   0), 20); // Green
  
//  // Rotate CW slowly at 5 RPM
//  myStepper.setSpeed(stepperSpeed);
//  myStepper.step(stepsPerRevolution * rotations);
//  delay(1000);
//  
//  // Rotate CCW quickly at 10 RPM
//  myStepper.setSpeed(stepperSpeed);
//  myStepper.step(-stepsPerRevolution * rotations);
//  delay(1000);
}

void colorWipe(uint32_t color, int wait) {
  
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)  
 
    if ((i - LED_TRAIL_LEN) >= 0) {
       strip.setPixelColor(i - LED_TRAIL_LEN, 0); 
    }
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }

  for(int idx = strip.numPixels() - LED_TRAIL_LEN; idx < strip.numPixels() + LED_TRAIL_LEN; idx +=1) {
    strip.setPixelColor(idx, 0); 
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}
