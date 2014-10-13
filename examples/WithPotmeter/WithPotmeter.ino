#include <FeedbackServo.h>
#include <Servo.h>

FeedbackServo servo1(10, A2);
FeedbackServo servo2(9, A3);

void setup() {
  Serial.begin(9600);
  
  servo1.setInputPin(A1);
  servo2.setInputPin(A0);
}

void loop() {
  servo1.loop();
  servo2.loop();
}
