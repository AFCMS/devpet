/*
SPDX-FileCopyrightText: 2024 AFCMS <afcm.contact@gmail.com>
SPDX-License-Identifier: GPL-3.0-or-later
*/

// Many thanks to AKArien0 for the inspiration
// https://github.com/AKArien0/arduino-input-handler

#include <Arduino.h>

namespace utils
{
    namespace input
    {
        /**
         * The debounce time for the buttons
         */
        const unsigned long BUTTON_DEBOUNCE = 10;

        class Button
        {
        private:
            /**
             * @brief The pin of the button
             */
            const unsigned char pin;
            volatile bool currentState = false;
            volatile bool lastState = false;
            volatile unsigned int debounceLastMeasure;

        public:
            Button(unsigned char _pin) : pin(_pin){};

            /**
             * @brief Initialize the pin, attach the handler to the interrupt
             */
            void begin();

            /**
             * @brief The class interrupt handler for the buttons
             */
            void interruptChange();

            /**
             * @brief Check if the button is pressed
             */
            bool isPressed();

            /**
             * @brief Check if the button has just been pressed
             */
            bool isJustPressed();

            /**
             * @brief Check if the button has just been released
             */
            bool isJustReleased();

            ~Button();
        };

        /**
         * @brief The base interrupt handler for the buttons, calls the class interrupt handler
         *
         * @param btn The button that triggered the interrupt
         */
        void ISR(void *btn);
    }
};