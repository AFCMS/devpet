/*
SPDX-FileCopyrightText: 2024 AFCMS <afcm.contact@gmail.com>
SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "comm.hpp"
#include "display/display.hpp"
#include "display/display_progress_bar.hpp"
#include "display/display_rect.hpp"
#include "display/display_sprite_bar.hpp"
#include "display/display_sprite_static.hpp"
#include "display/display_text.hpp"
#include "display/display_text_scrolling.hpp"

#include "images/bug.hpp"
#include "images/button_center.hpp"
#include "images/button_left.hpp"
#include "images/music_note.hpp"
#include "images/git_commit.hpp"
#include "images/git_pull_request.hpp"
#include "images/heart.hpp"
#include "images/issue_opened.hpp"
#include "images/dino.hpp"
#include "images/dino_small.hpp"

#pragma once

using namespace utils;

enum DevPetGameState
{
    Menu,
    InGame,
    End,
};

class DevPetGame
{
private:
    display::DisplaySystem &displaySystem;
    comm::CommSystem &commSystem;

    unsigned char sps = 20; // Steps per second
    unsigned long lastMillis = 0;

    display::Text playTitle{0, 0, "Play"};

    display::Text gameOver{0, 20, "Game Over!", 1, 18, true};
    display::Text scoreLabel{18, 6, "Score: 0"};
    display::SpriteStatic player{0, 0, images::static_dino_small, 16, 16};

    display::SpriteStatic enemyType1{0, 0, images::static_bug, 13, 13}; // Bug
    // display::SpriteStatic enemyType2{0, 0, images::static_bug, 13, 13};
    // display::SpriteStatic enemyType3{0, 0, images::static_bug, 13, 13};

    display::SpriteStatic buttonLeft{0, 0, images::static_button_left, 13, 13};
    display::SpriteStatic buttonCenter{128 - 13, 0, images::static_button_center, 13, 13};

    /**
     * @brief The enemy that the player has currently to avoid
     */
    // display::SpriteStatic *currentEnemy = nullptr;

    DevPetGameState state = DevPetGameState::Menu;

    unsigned int score = 0;
    unsigned int enemySpeed = 2;

    bool isJumping = false;
    bool jumpUp = true; // false = down

    const unsigned char jumpHeight = 20;   // Jump height
    const unsigned char jumpSpeed = 2;     // Speed of jump
    const unsigned char groundLevel = 16;  // Distance from bottom of screen to ground
    const unsigned char screenHeight = 64; // Example screen height

    void spawnEnemy();
    bool checkCollision(display::SpriteStatic &rectA, display::SpriteStatic &rectB);

    void updatePlayerPosition();
    void updateEnemyPosition();
    void checkGameConditions();

public:
    DevPetGame(comm::CommSystem &_commSystem, display::DisplaySystem &_displaySystem);
    DevPetGameState getState();
    void step();
    void updateNodes();
    void start();
    void pressButton();
};
