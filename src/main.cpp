/*
SPDX-FileCopyrightText: 2024 AFCMS <afcm.contact@gmail.com>
SPDX-License-Identifier: GPL-3.0-or-later
*/

#include <Arduino.h>

#include "utils/comm.hpp"
#include "utils/input.hpp"
#include "utils/display/display.hpp"
#include "utils/display/display_progress_bar.hpp"
#include "utils/display/display_sprite_animated.hpp"
#include "utils/display/display_sprite_static.hpp"
#include "utils/display/display_text.hpp"
#include "utils/display/display_text_scrolling.hpp"
#include "utils/time.hpp"

#include "screens/screen_connect.hpp"

using namespace utils;

input::Button buttonA(32);
input::Button buttonB(33);

display::DisplaySystem displaySystem(10);

time::TimeSystem timeSystem;

comm::CommSystem commSystem;

display::Text testText;

void setup()
{
  Serial.begin(9600);
  Serial.println("DevPet starting...");
  commSystem.begin();

  commSystem.log("Initializing input system...");

  buttonA.begin();
  buttonB.begin();

  commSystem.log("Initializing display system...");
  displaySystem.begin();

  displaySystem.setNodes2D(screens::connect());

  delay(1000);
}

void loop()
{
  // Update time
  timeSystem.step();

  // Handle input
  auto pressedButtons = inputSystem.step();

  for (auto it = pressedButtons.begin(); it != pressedButtons.end(); ++it)
  {
    switch (*it)
    {
    case BUTTON_A:
      commSystem.log(comm::MT_INFO, "Button A pressed");
      break;
    }
  }

  testText.setText(timeSystem.getCurrentHourString());
  displaySystem.step();

  auto commands = commSystem.step();

  for (int i = 0; i < commands.size(); i++)
  {
    auto command = commands.front();
    commands.pop();

    commSystem.log(comm::MT_INFO, "Command: " + command.command_name + " Payload: " + command.playload);
  }
}
