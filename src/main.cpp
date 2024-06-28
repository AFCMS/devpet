/*
SPDX-FileCopyrightText: 2024 AFCMS <afcm.contact@gmail.com>
SPDX-License-Identifier: GPL-3.0-or-later
*/

#include <Arduino.h>

#include "utils/comm.hpp"
#include "utils/devpet.hpp"
#include "utils/devpet_game.hpp"
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
DevPetGame devPetGame;
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

  if (devPet.isJustDead())
  {
    commSystem.log("DevPet is dead");
    devPetGraphics.setCurrentPage(DevPetPage::Main);
  }

  ///////////
  // INPUT //
  ///////////

  if (buttonLeft.isJustPressed())
  {
    commSystem.log("Button Left pressed");

    if (!devPet.isDead())
    {
      switch (devPetGraphics.getCurrentPage())
      {
      case DevPetPage::Main:
        devPetGraphics.setCurrentPage(DevPetPage::Stats);
        break;
      case DevPetPage::Game:
        devPetGraphics.setCurrentPage(DevPetPage::Main);
        break;
      default:
        break;
      }
    }
  }

  if (buttonRight.isJustPressed())
  {
    commSystem.log("Button Right pressed");

    if (!devPet.isDead())
    {
      switch (devPetGraphics.getCurrentPage())
      {
      case DevPetPage::Stats:
        devPetGraphics.setCurrentPage(DevPetPage::Main);
        break;
      case DevPetPage::Main:
        devPetGraphics.setCurrentPage(DevPetPage::Game);
        break;
      default:
        break;
      }
    }
  }

  if (buttonCenter.isJustPressed())
  {
    commSystem.log("Button Center pressed");

    if (!devPet.isDead() && devPetGraphics.getCurrentPage() == DevPetPage::Main)
    {
      devPet.boostEnergy();
      devPetGraphics.drinkCoffee();
    }

    if (devPet.isDead())
    {
      devPet.revive();
      devPetGraphics.revive();
    }
  }

  // Commands Input
  auto commands = commSystem.step();

  for (int i = 0; i < commands.size(); i++)
  {
    auto command = commands.front();
    commands.pop();

    commSystem.log(comm::MT_INFO, "Command: " + command.command_name + " Payload: " + command.payload);

    if (command.command_name == "music-play" && !devPet.isDead())
    {
      const int pos = command.payload.indexOf("^");

      if (pos != -1)
      {
        const String song = command.payload.substring(0, pos);
        const String artists = command.payload.substring(pos + 1);

        devPetGraphics.playMusic(song + " - " + artists);

        // TODO: make sure the command can't be called too often
        devPet.boostMood();

        commSystem.log(comm::MT_INFO, "Playing: " + song + " - " + artists);
      }
      else
      {
        commSystem.log(comm::MT_ERROR, "Invalid payload for music-play command");
      }
    }
    else if (command.command_name == "new-issue" && !devPet.isDead())
    {
      devPet.boostEnergy();
      devPetGraphics.pushIssue(command.payload);
    }
    else if (command.command_name == "new-pr" && !devPet.isDead())
    {
      devPet.boostEnergy();
      devPetGraphics.pushPullRequest(command.payload);
    }
    else if (command.command_name == "new-commits" && !devPet.isDead())
    {
      devPet.boostProductivity();
      devPetGraphics.pushNewCommits(command.payload.toInt());
    }
  }

  devPet.step();
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
