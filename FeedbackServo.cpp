#include "FeedbackServo.h"

FeedbackServo::FeedbackServo(int pin, int feedbackPin) {
    _pin = pin;
    _feedbackPin = feedbackPin;
    _setting = 0;
    _inputPin = -1;
}

void FeedbackServo::setInputPin(int pin) {
    _inputPin = pin;
}

void FeedbackServo::loop() {
    unsigned long t = millis();
    int feedback = analogRead(_feedbackPin);
    int diff = abs(_lastPos - feedback);

    if (_inputPin != -1) {
        int input = analogRead(_inputPin);
        int mapped = map(input, 0, 1023, 0, 180);

        if (abs(mapped - _setting) > SET_THRESHOLD) {
            _setting = mapped;
            _setTime = t;
            _servo.attach(_pin);
        }

        if (_servo.attached()) {
            _servo.write(mapped);
        }
    }

    if (t - _setTime > SET_DELAY && diff == 0 && _servo.attached()) {
        _servo.detach();
    } else if (t - _setTime > SET_DELAY && _servo.attached()) {
        Serial.println(diff);
    }

    _lastPos = feedback;
}

int FeedbackServo::setting() {
    return _setting;
}