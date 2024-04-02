#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "utils/input.hpp"
#include "utils/display.hpp"
#include "utils/time.hpp"

using namespace utils;

#define OLED_RESET 0x3C
Adafruit_SSD1306 dp(128, 64, &Wire, -1);

enum Buttons
{
  BUTTON_A = 32,
};

input::InputSystem inputSystem({BUTTON_A});

display::DisplaySystem displaySystem(&dp, 5);

time::TimeSystem timeSystem;

void setup() {
  Serial.begin(9600);
  Serial.println("Starting DevPet...");

  Serial.println("Initializing input system...");
  inputSystem.begin();

  Serial.println("Initializing OLED...");
  displaySystem.begin();
}

void loop() {
  // Update time
  timeSystem.step();

  // Handle input
  std::set<uint8_t> pressedButtons = inputSystem.step();

  for (std::set<uint8_t>::iterator it = pressedButtons.begin(); it != pressedButtons.end(); ++it)
  {
    switch (*it)
    {
    case BUTTON_A:
      Serial.println("Button A pressed");
      break;
    }
  }

  displaySystem.printUpBar(timeSystem.getCurrentHourString());
  displaySystem.step();
}
