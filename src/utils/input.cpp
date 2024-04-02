#include <Arduino.h>
#include "input.hpp"

namespace utils
{
    namespace input
    {
        void IRAM_ATTR InputSystem::ISR(void *isrData)
        {
            volatile ButtonDataISR *data = (volatile ButtonDataISR *)isrData;
            uint8_t btn = data->button;
            InputSystem *inputSystem = data->inputSystem;

            if (millis() - inputSystem->getButtonLastMillis(btn) > BUTTON_DEBOUNCE)
            { // Software debouncing button
                inputSystem->buttonPressedQueue.insert(btn);
            }
            inputSystem->setButtonLastMillis(btn, millis());
        };

        InputSystem::InputSystem()
        {
            buttons = std::vector<uint8_t>();
            buttonsLastMillis = std::map<uint8_t, unsigned long>();
            buttonPressedQueue = std::set<uint8_t>();
        };

        InputSystem::InputSystem(std::vector<uint8_t> _buttons)
        {
            buttons = _buttons;
            buttonsLastMillis = std::map<uint8_t, unsigned long>();
            buttonPressedQueue = std::set<uint8_t>();
        };

        void InputSystem::begin()
        {
            for (int i = 0; i < buttons.size(); i++)
            {
                pinMode(buttons[i], INPUT_PULLUP);
                buttonsLastMillis[buttons[i]] = 0;

                static volatile ButtonDataISR data = {buttons[i], this};
                attachInterruptArg(buttons[i], &InputSystem::ISR, (void *)(&data), RISING);
            }
        };

        std::set<uint8_t> InputSystem::step()
        {
            std::set<uint8_t> pressedButtons = buttonPressedQueue;
            buttonPressedQueue.clear();
            return pressedButtons;
        };

        std::vector<uint8_t> InputSystem::getButtons()
        {
            return buttons;
        };

        unsigned long InputSystem::getButtonLastMillis(uint8_t button)
        {
            return buttonsLastMillis[button];
        };

        void InputSystem::setButtonLastMillis(uint8_t button, unsigned long millis)
        {
            buttonsLastMillis[button] = millis;
        };
    }
};