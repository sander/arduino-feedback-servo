#ifndef FeedbackServo_h
#define FeedbackServo_h

#include "Arduino.h"
#include "Servo.h"

#define SET_DELAY 300

// SET_THRESHOLD is used when an input pin (e.g. manual potmeter) is used.
#define SET_THRESHOLD 2

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
    void adjust(int adjustment);
    void setReversed(bool reversed);
    int adjustedSetting();
private:
    Servo _servo;

    int _pin;
    int _feedbackPin;
    int _inputPin;

    int _setting;
    int _adjustment;
    unsigned long _setTime;

    int _lastPos;

    bool _reversed;
};

#endif
