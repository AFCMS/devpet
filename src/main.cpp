/*
SPDX-FileCopyrightText: 2024 AFCMS <afcm.contact@gmail.com>
SPDX-License-Identifier: GPL-3.0-or-later
*/

#include <Arduino.h>

#include "utils/comm.hpp"
#include "utils/devpet.hpp"
#include "utils/devpet_graphics.hpp"
#include "utils/input.hpp"
#include "utils/display/display.hpp"
#include "utils/display/display_progress_bar.hpp"
#include "utils/display/display_sprite_animated.hpp"
#include "utils/display/display_sprite_static.hpp"
#include "utils/display/display_text.hpp"
#include "utils/display/display_text_scrolling.hpp"
#include "utils/time.hpp"

using namespace utils;

input::Button buttonA(32);
input::Button buttonB(33);

display::DisplaySystem displaySystem(10);

time::TimeSystem timeSystem;

comm::CommSystem commSystem;

DevPet devPet;
DevPetGraphics devPetGraphics(displaySystem, devPet, commSystem);

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

  commSystem.log("Initializing DevPet graphics...");
  devPetGraphics.begin();

  delay(1000);
}

void loop()
{
  // Update time
  timeSystem.step();

  ///////////
  // INPUT //
  ///////////

  if (buttonA.isJustPressed())
  {
    commSystem.log("Button A pressed");
  }

  if (buttonB.isJustPressed())
  {
    commSystem.log("Button B pressed");
  }

  // Commands Input
  auto commands = commSystem.step();

  for (int i = 0; i < commands.size(); i++)
  {
    auto command = commands.front();
    commands.pop();

    commSystem.log(comm::MT_INFO, "Command: " + command.command_name + " Payload: " + command.payload);

    if (command.command_name == "music-play")
    {
      const int pos = command.payload.indexOf("^");

      if (pos != -1)
      {
        const String song = command.payload.substring(0, pos);
        const String artists = command.payload.substring(pos + 1);

        devPetGraphics.playMusic(song + " - " + artists);
        commSystem.log(comm::MT_INFO, "Playing: " + song + " - " + artists);
      }
      else
      {
        commSystem.log(comm::MT_ERROR, "Invalid payload for music-play command");
      }
    }
    else if (command.command_name == "new-issue")
    {
      devPetGraphics.pushIssue(command.payload);
    }
  }

  devPetGraphics.step();
  displaySystem.step();

  /*switch (state)
  {
  case WAITING_FOR_SERIAL:
    for (int i = 0; i < commands.size(); i++)
    {
      auto command = commands.front();
      commands.pop();

      if (command.command_name == "ping")
      {
        state = MAIN_LOOP;
      }
      else
      {
        commSystem.sendCommand("ping");
        delay(500);
      };
    }
    break;

  default:
    for (int i = 0; i < commands.size(); i++)
    {
      auto command = commands.front();
      commands.pop();

      commSystem.log(comm::MT_INFO, "Command: " + command.command_name + " Payload: " + command.payload);
    }

    displaySystem.step();
    break;
  }*/
}
