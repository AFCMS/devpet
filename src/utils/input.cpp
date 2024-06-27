/*
SPDX-FileCopyrightText: 2024 AFCMS <afcm.contact@gmail.com>
SPDX-License-Identifier: GPL-3.0-or-later
*/

// Many thanks to AKArien0 for the inspiration
// https://github.com/AKArien0/arduino-input-handler

#include <Arduino.h>
#include "input.hpp"

namespace utils
{
    namespace input
    {

        void Button::begin(int _debounceTime)
        {
            pinMode(pin, INPUT_PULLUP);
            debounceTime = _debounceTime;
            attachInterruptArg(digitalPinToInterrupt(pin), ISR, this, CHANGE);
        };

        void Button::interruptChange()
        {
            if (millis() - debounceLastMeasure > debounceTime)
            {
                lastState = currentState;
                currentState = !digitalRead(pin);
            }
            debounceLastMeasure = millis();
        }

        bool Button::isPressed()
        {
            return currentState;
        }

        bool Button::isJustPressed()
        {
            if (lastState == false)
            {
                lastState = currentState;
                return isPressed();
            }
            return false;
        }

        bool Button::isJustReleased()
        {
            if (lastState == true)
            {
                lastState = currentState;
                return !isPressed();
            }
            return false;
        }

        Button::~Button()
        {
            detachInterrupt(pin);
        }

        void IRAM_ATTR ISR(void *btn)
        {
            Button *bt = (Button *)btn;
            bt->interruptChange();
        };
    }
};