/*
SPDX-FileCopyrightText: 2024 AFCMS <afcm.contact@gmail.com>
SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "devpet.hpp"
#include "comm.hpp"
#include "display/display.hpp"
#include "display/display_progress_bar.hpp"
#include "display/display_rect.hpp"
#include "display/display_sprite_bar.hpp"
#include "display/display_sprite_static.hpp"
#include "display/display_text.hpp"
#include "display/display_text_scrolling.hpp"

#include "images/button_center.hpp"
#include "images/button_left.hpp"
#include "images/button_right.hpp"
#include "images/music_note.hpp"
#include "images/git_commit.hpp"
#include "images/git_pull_request.hpp"
#include "images/heart.hpp"
#include "images/issue_opened.hpp"
#include "images/dino.hpp"

#pragma once

using namespace utils;

/**
 * The different pages of the DevPet
 *
 * - Main: The main page, with the health bar, the dinosaur and the top feed
 * - Stats: The stats page, with the mood, energy and productivity bars
 * - Game: The game page, with the minigame itself
 *
 * The main page is at the middle, the stats page at the left and the game page at the right
 */
enum DevPetPage
{
    Main,
    Stats,
    Game,
};

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
    DevPet &devPet;

    /**
     * @brief Reference to the communication system
     */
    comm::CommSystem &commSystem;

    /**
     * @brief Current page
     */
    DevPetPage currentPage = DevPetPage::Main;

    bool hasFirstDisplayed = false;

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
    display::SpriteStatic feedNewCommits{0, 0, images::static_git_commit, 16, 16};

    static const unsigned char FEED_TITLE_1_Z = 11;
    display::Text feedTitle1{18, 0, "", 1, 18, true};

    static const unsigned long FEED_MUSIC_TIMEOUT = 1000 * 10;
    unsigned long lastTimeMusicUpdated = 0;

    static const unsigned char FEED_TITLE_2_Z = 12;
    display::TextScrolling feedTitle2{18, 8, "", 1, 18, 1};

    display::Rect testRect{0, 17, 128, 1};

    display::SpriteStatic mainButtonLeft{0, 24, images::static_button_left, 13, 13};
    display::SpriteStatic mainButtonRight{128 - 13, 24, images::static_button_right, 13, 13};

    // Health Bar

    display::SpriteAnimated healthBarSp1{83 + 0, 55, images::heart, images::heart_num_frames, 9, 9};
    display::SpriteAnimated healthBarSp2{83 + 9, 55, images::heart, images::heart_num_frames, 9, 9};
    display::SpriteAnimated healthBarSp3{83 + 18, 55, images::heart, images::heart_num_frames, 9, 9};
    display::SpriteAnimated healthBarSp4{83 + 27, 55, images::heart, images::heart_num_frames, 9, 9};
    display::SpriteAnimated healthBarSp5{83 + 36, 55, images::heart, images::heart_num_frames, 9, 9};

    display::SpriteAnimated *healthBarSps[5];
    display::SpriteBar healthBar{5, healthBarSps, 255};

    display::SpriteStatic testSp{9, 40, images::static_dino, 25, 25};

    // Stats Page

    display::SpriteStatic statsButtonRight{128 - 13, 24, images::static_button_right, 13, 13};

    display::Text statsMoodLabel{0, 18, "Mood"};
    display::ProgressBar statsMood{6 * 8, 17, 50, 10, 255};
    display::Text statsMoodValue{6 * 8 + 50 + 2, 18, ""};

    display::Text statsEnergyLabel{0, 29, "Energy"};
    display::ProgressBar statsEnergy{6 * 8, 28, 50, 10, 255};
    display::Text statsEnergyValue{6 * 8 + 50 + 2, 29, ""};

    display::Text statsProductivityLabel{0, 40, "Prod"};
    display::ProgressBar statsProductivity{6 * 8, 39, 50, 10, 255};
    display::Text statsProductivityValue{6 * 8 + 50 + 2, 40, ""};

    void updateDisplay();
    void updateDisplayedNodes();

    bool internalFeedIsDisplayingItem();
    bool internalFeedHasJustDisplayedItem();
    void internalFeedReset();
    void internalFeedMusic();

public:
    DevPetGraphics(display::DisplaySystem &_displaySystem, DevPet &_devPet, comm::CommSystem &_commSystem);

    void begin();

    void step();

    DevPetPage getCurrentPage();

    void setCurrentPage(DevPetPage page);

    void playMusic(String musicTitle);

    void pushIssue(String issueTitle);

    void pushPullRequest(String pullRequestTitle);

    void pushNewCommits(long nbCommits);
};
