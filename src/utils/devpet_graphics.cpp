/*
SPDX-FileCopyrightText: 2024 AFCMS <afcm.contact@gmail.com>
SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "devpet_graphics.hpp"

DevPetGraphics::DevPetGraphics(display::DisplaySystem &_displaySystem, DevPet &_devPet, comm::CommSystem &_commSystem) : devPet(_devPet), displaySystem(_displaySystem), commSystem(_commSystem) {}

void DevPetGraphics::begin()
{
    displaySystem.setNode2D(FEED_TITLE_1_Z, &feedTitle1);
    displaySystem.setNode2D(FEED_TITLE_2_Z, &feedTitle2);
}

void DevPetGraphics::step()
{
    // Reset music name if no update in a while
    if (millis() - lastTimeMusicUpdated > FEED_MUSIC_TIMEOUT)
    {
        feedMusicName = "";
    }

    if (millis() - feedItemLastUpdate > FEED_ITEM_TIMEOUT)
    {
        if (feedMusicName != "")
        {
            internalFeedMusic();
        }
        else
        {
            internalFeedReset();
        }
    }
}

void DevPetGraphics::playMusic(String musicTitle)
{
    feedMusicName = musicTitle;
    lastTimeMusicUpdated = millis();
}

void DevPetGraphics::pushIssue(String issueTitle)
{
    displaySystem.setNode2D(FEED_ICON_Z, &feedIssueOpened);
    feedTitle1.setText("Issue");
    feedTitle2.setText(issueTitle);
    feedItemLastUpdate = millis();
}

void DevPetGraphics::pushPullRequest(String pullRequestTitle)
{
    displaySystem.setNode2D(FEED_ICON_Z, &feedGitPullRequest);
    feedTitle1.setText("Pull Request");
    feedTitle2.setText(pullRequestTitle);
    feedItemLastUpdate = millis();
}

void DevPetGraphics::pushNewCommits(long nbCommits)
{
    displaySystem.setNode2D(FEED_ICON_Z, &feedNewCommits);
    feedTitle1.setText("Commits");
    feedTitle2.setText(String(nbCommits) + " new commits");
    feedItemLastUpdate = millis();
}

bool DevPetGraphics::internalFeedIsDisplayingItem()
{
    return millis() - feedItemLastUpdate < FEED_ITEM_TIMEOUT;
}

bool DevPetGraphics::internalFeedHasJustDisplayedItem()
{
    return lastStepWasDisplayingItem && !internalFeedIsDisplayingItem();
}

void DevPetGraphics::internalFeedReset()
{
    displaySystem.removeNode2D(FEED_ICON_Z);
    feedTitle1.setText("");
    feedTitle2.setText("");

    feedMusicName = "";
    feedMusicLastUpdate = 0;
    feedItemLastUpdate = 0;
}

void DevPetGraphics::internalFeedMusic()
{
    displaySystem.setNode2D(FEED_ICON_Z, &feedMusicIcon);
    feedTitle1.setText("Listening");
    feedTitle2.setText(feedMusicName);
}