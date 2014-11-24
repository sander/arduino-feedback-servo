#ifndef FeedbackServo_h
#define FeedbackServo_h

#include "Arduino.h"
#include "Servo.h"

#define SET_DELAY 100
#define SET_TIMEOUT 200
#define SET_THRESHOLD 2
#define GO_THRESHOLD 40

class FeedbackServo {
public:
    FeedbackServo();
    FeedbackServo(int pin, int feedbackPin);
    void begin(int pin, int feedbackPin);
    void setInputPin(int pin);
    void unsetInputPin();
    void loop();
    int setting();
    void set(int setting);
private:
    Servo _servo;

    int _pin;
    int _feedbackPin;
    int _inputPin;

    int _setting;
    unsigned long _setTime;

    int _lastPos;
};

#endif