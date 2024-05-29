/*
SPDX-FileCopyrightText: 2024 AFCMS <afcm.contact@gmail.com>
SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "devpet.hpp"
#include "comm.hpp"
#include "display/display.hpp"
#include "display/display_sprite_static.hpp"
#include "display/display_text.hpp"
#include "display/display_text_scrolling.hpp"

#include "images/music_note.hpp"
#include "images/git_pull_request.hpp"
#include "images/issue_opened.hpp"

#pragma once

using namespace utils;

class DevPetGraphics
{
private:
    // Pointers to core classes

    /**
     * @brief Reference to the display system
     */
    display::DisplaySystem &displaySystem;

    /**
     * @brief Reference to the DevPet instance, to get data to display
     */
    const DevPet &devPet;

    /**
     * @brief Reference to the communication system
     */
    comm::CommSystem &commSystem;

    // Top Feed
    //
    // This takes place on the 16px top yellow bar of the screen and display:
    //
    // - Push events (typically from GitHub)
    // - Overwise the currently playing music
    //
    // With the following elements:
    //
    // - The icon of the event at left (music note, relevant Octicons icon)
    // - A static string at top for the type of event
    // - A scrolling text for the title of the event or the music name

    unsigned long feedMusicLastUpdate = 0;
    String feedMusicName = "";

    unsigned long feedItemLastUpdate = 0;
    bool lastStepWasDisplayingItem = false;

    static const unsigned int FEED_ITEM_TIMEOUT = 1000 * 5;

    static const unsigned char FEED_ICON_Z = 10;
    display::SpriteStatic feedMusicIcon{0, 0, images::static_music_note, 16, 16};
    display::SpriteStatic feedGitPullRequest{0, 0, images::static_git_pull_request, 16, 16};
    display::SpriteStatic feedIssueOpened{0, 0, images::static_issue_opened, 16, 16};

    static const unsigned char FEED_TITLE_1_Z = 11;
    display::Text feedTitle1{18, 0, "", 1, 18, true};

    static const unsigned long FEED_MUSIC_TIMEOUT = 1000 * 10;
    unsigned long lastTimeMusicUpdated = 0;

    static const unsigned char FEED_TITLE_2_Z = 12;
    display::TextScrolling feedTitle2{18, 8, "", 1, 18, 1};

    bool internalFeedIsDisplayingItem();
    bool internalFeedHasJustDisplayedItem();
    void internalFeedReset();
    void internalFeedMusic();

public:
    DevPetGraphics(display::DisplaySystem &_displaySystem, DevPet &_devPet, comm::CommSystem &_commSystem);

    void begin();

    void step();

    void playMusic(String musicTitle);

    void pushIssue(String issueTitle);

    void pushPullRequest(String pullRequestTitle);
};
