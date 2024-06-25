/*
SPDX-FileCopyrightText: 2024 AFCMS <afcm.contact@gmail.com>
SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "display/display.hpp"
#include "display/display_progress_bar.hpp"
#include "display/display_rect.hpp"
#include "display/display_sprite_bar.hpp"
#include "display/display_sprite_static.hpp"
#include "display/display_text.hpp"
#include "display/display_text_scrolling.hpp"

#include "images/music_note.hpp"
#include "images/git_commit.hpp"
#include "images/git_pull_request.hpp"
#include "images/heart.hpp"
#include "images/issue_opened.hpp"
#include "images/dino.hpp"

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
    display::Text playTitle{0, 0, "Play"};
    display::SpriteStatic player{0, 64 - 16, images::static_issue_opened, 16, 16};

    DevPetGameState state = DevPetGameState::Menu;

public:
    DevPetGame();
    void step();
    void updateNodes();
    void start();
};
