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

input::Button buttonLeft(32);
input::Button buttonCenter(25);
input::Button buttonRight(12);

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

  buttonLeft.begin();
  buttonCenter.begin();
  buttonRight.begin();

  commSystem.log("Initializing display system...");
  displaySystem.begin();

  commSystem.log("Initializing DevPet graphics...");
  devPetGraphics.begin();

  delay(1000);
}

unsigned long lastLoggedDevPet = 0;

void loop()
{
  // Update time
  timeSystem.step();

  ///////////
  // INPUT //
  ///////////

  if (buttonLeft.isJustPressed())
  {
    commSystem.log("Button Left pressed");
    devPetGraphics.setCurrentPage(DevPetPage::Main);
    devPet.setEnergy(constrain(devPet.getEnergy() + 10, 0, 255));
    devPet.setMood(constrain(devPet.getMood() + 10, 0, 255));
    devPet.setProductivity(constrain(devPet.getProductivity() + 10, 0, 255));
  }

  if (buttonRight.isJustPressed())
  {
    commSystem.log("Button Right pressed");
    devPetGraphics.setCurrentPage(DevPetPage::Stats);
    devPet.setEnergy(constrain(devPet.getEnergy() - 10, 0, 255));
    devPet.setMood(constrain(devPet.getMood() - 10, 0, 255));
    devPet.setProductivity(constrain(devPet.getProductivity() - 10, 0, 255));
  }

  if (buttonCenter.isJustPressed())
  {
    commSystem.log("Button Center pressed");
    devPet.setEnergy(125);
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
    else if (command.command_name == "new-pr")
    {
      devPetGraphics.pushPullRequest(command.payload);
    }
    else if (command.command_name == "new-commits")
    {
      devPetGraphics.pushNewCommits(command.payload.toInt());
    }
  }

  devPetGraphics.step();
  displaySystem.step();

  if (millis() - lastLoggedDevPet > 2000)
  {
    devPet.log(commSystem);
    lastLoggedDevPet = millis();
  }

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
