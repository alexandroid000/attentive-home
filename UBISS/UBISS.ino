#include <Servo.h>

static const int servoPin = 26;

Servo servo1;

void setup() {
    Serial.begin(115200);

    // attach servo motor, delay so we don't start sending power too soon
    servo1.attach(servoPin);
    delay(10);
    spin_motor(0);

}

void spin_motor(int dir) {
  // CLOCKWISE SPIN
  if (dir == 1) {
    for(int posDegrees = 0; posDegrees <= 90; posDegrees++) {
        servo1.write(posDegrees);
        Serial.println(posDegrees);
        delay(7);
    }
  }
  // COUNTERCLOCKWISE
  else{
    for(int posDegrees = 180; posDegrees >= 90; posDegrees--) {
        servo1.write(posDegrees);
        Serial.println(posDegrees);
        delay(7);
    }
  }
  
}

void loop() {

}
