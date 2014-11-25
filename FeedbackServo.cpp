#include "FeedbackServo.h"

FeedbackServo::FeedbackServo() {
    _reversed = false;
}

FeedbackServo::FeedbackServo(int pin, int feedbackPin) {
    begin(pin, feedbackPin);
}

void FeedbackServo::begin(int pin, int feedbackPin) {
    _pin = pin;
    _feedbackPin = feedbackPin;
    _setting = 0;
    _inputPin = -1;
}

void FeedbackServo::setInputPin(int pin) {
    _inputPin = pin;
}

void FeedbackServo::unsetInputPin() {
    _inputPin = -1;
}

void FeedbackServo::loop() {
    unsigned long t = millis();
    int feedback = analogRead(_feedbackPin);
    int diff = abs(_lastPos - feedback);

    if (_inputPin != -1) {
        int input = analogRead(_inputPin);
        int mapped = map(input, 0, 1023, 0, 180);

        if (abs(mapped - _setting) > SET_THRESHOLD) {
            set(mapped);
        }
    }

    if (_servo.attached()) {
        _servo.write(_reversed ? 180 - _setting : _setting);
    }

    //Serial.println(diff);

    if (t - _setTime > SET_DELAY && diff == 0 && _servo.attached()) {
        _servo.detach();
    } else if (t - _setTime > SET_DELAY && _servo.attached()) {
        //Serial.println(diff);
    }

    _lastPos = feedback;
}

int FeedbackServo::setting() {
    return _setting;
}

void FeedbackServo::set(int setting) {
    if (_setting != setting) {
        _setting = setting;
        _setTime = millis();
        _servo.attach(_pin);
    }
}

void FeedbackServo::setReversed(bool reversed) {
    _reversed = reversed;
}
