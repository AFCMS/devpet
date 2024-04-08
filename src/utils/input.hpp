/*
SPDX-FileCopyrightText: 2024 AFCMS <afcm.contact@gmail.com>
SPDX-License-Identifier: GPL-3.0-or-later
*/

#include <Arduino.h>
#include <vector>
#include <queue>
#include <map>
#include <set>

namespace utils
{
    namespace input
    {
        class InputSystem; // Forward declaration

        struct ButtonDataISR
        {
            uint8_t button;
            InputSystem *inputSystem;
        };

        /**
         * A class to handle button presses and debouncing
         */
        class InputSystem
        {
        private:
            std::vector<uint8_t> buttons;
            std::map<uint8_t, unsigned long> buttonsLastMillis;
            std::set<uint8_t> buttonPressedQueue;

            static void ISR(void *buttonPin);

            unsigned long getButtonLastMillis(uint8_t button);
            void setButtonLastMillis(uint8_t button, unsigned long millis);

        public:
            InputSystem();
            /**
             * Construct a new Input System object
             *
             * @param _buttons A vector of button pins
             */
            InputSystem(std::vector<uint8_t> _buttons);
            /**
             * Initialize the input system
             *
             * This method should be called in the setup() function
             *
             * It initializes the pins and the interrupts
             */
            void begin();
            /**
             * Update the input system
             *
             * This method should be called in the loop() function
             *
             * Iteturns a set of the buttons that have been pressed
             *
             * @return A set of the buttons that have been pressed
             */
            std::set<uint8_t> step();
            /**
             * Get the registered buttons
             *
             * @return A vector of the button pins
             */
            std::vector<uint8_t> getButtons();
            /**
             * The debounce time for the buttons
             */
            static const unsigned long BUTTON_DEBOUNCE = 10;
        };
    }
};