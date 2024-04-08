/*
SPDX-FileCopyrightText: 2024 AFCMS <afcm.contact@gmail.com>
SPDX-License-Identifier: GPL-3.0-or-later
*/

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "utils/comm.hpp"
#include "utils/input.hpp"
#include "utils/display.hpp"
#include "utils/display_text.hpp"
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

comm::CommSystem commSystem;

display::Text testText;

void setup()
{
  Serial.begin(9600);
  Serial.println("DevPet starting...");
  commSystem.begin();

  commSystem.log("Initializing input system...");
  inputSystem.begin();

  commSystem.log("Initializing display system...");
  displaySystem.begin();
  // testText.setCharsMax(14);
  testText.setCentered(true);
  displaySystem.addNode2D(&testText, 1);
}

void loop()
{
  // Update time
  timeSystem.step();

  // Handle input
  std::set<uint8_t> pressedButtons = inputSystem.step();

  for (std::set<uint8_t>::iterator it = pressedButtons.begin(); it != pressedButtons.end(); ++it)
  {
    switch (*it)
    {
    case BUTTON_A:
      commSystem.log(comm::MT_INFO, "Button A pressed");
      break;
    }
  }

  auto ttt = (display::Text *)displaySystem.getNode2D(1);
  ttt->setText(timeSystem.getCurrentHourString());
  displaySystem.step();

  std::queue<comm::CommandResult> commands = commSystem.step();

  for (int i = 0; i < commands.size(); i++)
  {
    comm::CommandResult command = commands.front();
    commands.pop();

    commSystem.log(comm::MT_INFO, "Command: " + command.command_name + " Payload: " + command.playload);
  }
}
