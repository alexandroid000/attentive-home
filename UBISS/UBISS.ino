#include <Servo.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>


char *myStrings[] = {"Your home is fine.",
                     "A bird is perched on the maple tree outside your window.",
                     "Your neighbors also feel overwhelmed sometimes."};


int currentString = 0;
static const int servoPin = 26; // A0
long num;


// LED constants
//static const int ledPin = 4; // A5
//int brightness = 0;    // how bright the LED is
//int fadeAmount = 5;    // how many points to fade the LED by
//#define LED_PIN            4
//
//// use first channel of 16 channels (started from zero)
//#define LEDC_CHANNEL_0     0
//// use 13 bit precission for LEDC timer
//#define LEDC_TIMER_13_BIT  13
//// use 5000 Hz as a LEDC base frequency
//#define LEDC_BASE_FREQ     5000

// screen pins
#ifdef ESP32
   #define STMPE_CS 32
   #define TFT_CS   15
   #define TFT_DC   33
   #define SD_CS    14
#endif

Servo servo1;

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

void setup() {
    Serial.begin(115200);

    delay(10);

    // start screen
    tft.begin();
    tft.setRotation(1);

    // attach servo motor, delay so we don't start sending power too soon
    servo1.attach(servoPin);

    servo1.write(0);


    // Setup timer and attach timer to a led pin
    //ledcSetup(LEDC_CHANNEL_0, LEDC_BASE_FREQ, LEDC_TIMER_13_BIT);
    //ledcAttachPin(LED_PIN, LEDC_CHANNEL_0);

}



// text on screen
void writeText(char str[]) {

  
  tft.fillScreen(ILI9341_WHITE);
  tft.setCursor(0, 0);
  tft.setTextColor(ILI9341_BLACK);  tft.setTextSize(4);
  tft.println(str);
  delay(5000);
  tft.fillScreen(ILI9341_BLACK);

}

// Arduino like analogWrite
// value has to be between 0 and valueMax
void ledcAnalogWrite(uint8_t channel, uint32_t value, uint32_t valueMax = 255) {
  // calculate duty, 8191 from 2 ^ 13 - 1
  uint32_t duty = (8191 / valueMax) * min(value, valueMax);
  // write duty to LEDC
  ledcWrite(channel, duty);
}

void spinMotor(int dir) {

  // CLOCKWISE SPIN
  if (dir == 1) {
    for(int posDegrees = 0; posDegrees <= 180; posDegrees++) {
        servo1.write(posDegrees);
        Serial.println(posDegrees);
        delay(25);
    }
  }
  // COUNTERCLOCKWISE
  else{
    for(int posDegrees = 180; posDegrees >= 0; posDegrees--) {
        servo1.write(posDegrees);
        Serial.println(posDegrees);
        delay(25);
    }
  }
  
}

//long read_distance() {
//
//  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
//  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
//  digitalWrite(trigPin, LOW);
//  delayMicroseconds(5);
//  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(10);
//  digitalWrite(trigPin, LOW);
//
//  // Read the signal from the sensor: a HIGH pulse whose
//  // duration is the time (in microseconds) from the sending
//  // of the ping to the reception of its echo off of an object.
//  pinMode(echoPin, INPUT);
//  duration = pulseIn(echoPin, HIGH);
//
//   // Convert the time into a distance
//  cm = (duration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
//  Serial.print(cm);
//  Serial.print("cm");
//  Serial.println();
//  return cm;
//}


void loop() {

//  // set the brightness on LEDC channel 0
//  ledcAnalogWrite(LEDC_CHANNEL_0, brightness);
//
//  // change the brightness for next time through the loop:
//  brightness = brightness + fadeAmount;
//
//  // reverse the direction of the fading at the ends of the fade:
//  if (brightness <= 0 || brightness >= 255) {
//    fadeAmount = -fadeAmount;
//  }


  num = random(0,10);

  if (num == 6) {
    spinMotor(1);
    writeText(myStrings[currentString]);
    delay(5000);
    currentString = (currentString + 1) % 3;
    spinMotor(-1);
  }
  
  delay(2000);

}
