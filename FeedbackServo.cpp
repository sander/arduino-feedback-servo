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
    _settingMicro = -1;
    _inputPin = -1;
    _maxDelay = 300;
}

void FeedbackServo::setInputPin(int pin) {
    _inputPin = pin;
}

void FeedbackServo::unsetInputPin() {
    _inputPin = -1;
}

void FeedbackServo::loop() {
    unsigned long t = millis();
    _feedback = analogRead(_feedbackPin);
    int diff = abs(_lastPos - _feedback);

    if (_inputPin != -1) {
        // NOTE this only works with 0-180 values right now.
        int input = analogRead(_inputPin);
        int mapped = map(input, 0, 1023, 0, 180);

        if (abs(mapped - adjustedSetting()) > SET_THRESHOLD) {
            set(mapped);
        }
    }

    if (attached()) {
        if (inMicro()) {
            _servo.writeMicroseconds(_reversed ? adjustedSettingMicroReverted() : adjustedSettingMicro());
        } else {
            _servo.write(_reversed ? revert(adjustedSetting()) : adjustedSetting());
        }

        if (t - _setTime > _maxDelay && diff < FEEDBACK_THRESHOLD) {
            _servo.detach();
        }
    }

    _lastPos = _feedback;
}

int FeedbackServo::feedback() {
    return _feedback;
}

int FeedbackServo::revert(int setting) {
    return (inMicro() ? 3000 : 180) - setting;
}

int FeedbackServo::adjustedSetting() {
    return constrain(_setting + _adjustment, 0, 180);
}

int FeedbackServo::adjustedSettingMicro() {
    return constrain(_settingMicro + _adjustment, _min, _max);
}

int FeedbackServo::adjustedSettingMicroReverted() {
    return constrain(3000 - (_settingMicro + _adjustment), _min, _max);
}

int FeedbackServo::setting() {
    return _setting;
}

void FeedbackServo::mconstrain(int min, int max) {
    _min = min;
    _max = max;
}

int FeedbackServo::settingMicro() {
    return _settingMicro;
}

void FeedbackServo::set(int setting) {
    if (_setting != setting) {
        _setting = setting;
        _setTime = millis();
        _servo.attach(_pin);
    }
}

void FeedbackServo::setMicro(int setting) {
    // Range 700-2300 (so 1600 step resolution)
    if (setting != _settingMicro) {
        _settingMicro = setting;
        _setTime = millis();
        _servo.attach(_pin);
    }
}

void FeedbackServo::adjust(int adjustment) {
    if (_adjustment != adjustment) {
        _adjustment = adjustment;
        _setTime = millis();
        _servo.attach(_pin);
    }
}

void FeedbackServo::setReversed(bool reversed) {
    _reversed = reversed;
}

bool FeedbackServo::inMicro() {
    return _settingMicro != -1;
}

void FeedbackServo::setMaxDelay(unsigned long delay) {
    _maxDelay = delay;
}

bool FeedbackServo::attached() {
    return _servo.attached();
}
