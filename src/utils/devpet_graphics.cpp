/*
SPDX-FileCopyrightText: 2024 AFCMS <afcm.contact@gmail.com>
SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "devpet_graphics.hpp"

String getNumberAsHEX(unsigned char number)
{
    auto end = String(number, HEX);
    end.toUpperCase();
    end.length() == 1 ? end = "0" + end : end;
    return String("0x") + end;
}

DevPetGraphics::DevPetGraphics(display::DisplaySystem &_displaySystem, DevPet &_devPet, comm::CommSystem &_commSystem) : devPet(_devPet), displaySystem(_displaySystem), commSystem(_commSystem) {}

void DevPetGraphics::begin()
{
    healthBarSps[0] = &healthBarSp1;
    healthBarSps[1] = &healthBarSp2;
    healthBarSps[2] = &healthBarSp3;
    healthBarSps[3] = &healthBarSp4;
    healthBarSps[4] = &healthBarSp5;

    healthBar.setVal(255);

    mainDinoSprite.setAnim(DINO_BIG_WAKE);
    mainDinoSprite.setAnimAfter(DINO_BIG_IDLE);
    mainDinoSprite.setSpeed(2);

    for (unsigned char i = 0; i < 5; i++)
    {
        healthBarSps[i]->setSpeed(4);
    }

    updateDisplay();
    updateDisplayedNodes();
}

void DevPetGraphics::step()
{
    if (!hasFirstDisplayed)
    {
        hasFirstDisplayed = true;
        updateDisplayedNodes();
    }

    // Update health bar
    healthBar.setVal(devPet.getHealth());

    if (devPet.isJustDead())
    {
        mainDinoSprite.setAnimAfter(DINO_BIG_DEAD);
        mainDinoSprite.doStopLoopAfter();
        feedMusicName = "";
        feedMusicLastUpdate = 0;
        internalFeedReset();
        updateDisplayedNodes();
    }

    if (!devPet.isDead())
    {
        // Reset music name if no update in a while
        if (millis() - lastTimeMusicUpdated > FEED_MUSIC_TIMEOUT)
        {
            feedMusicName = "";
        }

        if (getCurrentPage() == DevPetPage::Stats)
        {
            statsMood.setVal(devPet.getMood());
            statsMoodValue.setText(getNumberAsHEX(devPet.getMood()));

            statsEnergy.setVal(devPet.getEnergy());
            statsEnergyValue.setText(getNumberAsHEX(devPet.getEnergy()));

            statsProductivity.setVal(devPet.getProductivity());
            statsProductivityValue.setText(getNumberAsHEX(devPet.getProductivity()));
        }

        updateDisplay();
    }
}

void DevPetGraphics::updateDisplay()
{
    // Update Music feed item
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

void DevPetGraphics::updateDisplayedNodes()
{
    displaySystem.clearNodes2D();

    switch (getCurrentPage())
    {
    case DevPetPage::Main:
        displaySystem.setNode2D(FEED_TITLE_1_Z, &feedTitle1);
        displaySystem.setNode2D(FEED_TITLE_2_Z, &feedTitle2);

        if (devPet.isDead())
        {
            displaySystem.setNode2D(200, &mainDeathLabel);
            displaySystem.setNode2D(201, &mainButtonNewPet);
        }
        else
        {
            displaySystem.setNode2D(200, &mainButtonLeft);
            displaySystem.setNode2D(201, &mainButtonRight);
        }

        displaySystem.setNode2D(221, &testRect);
        displaySystem.setNode2D(222, &healthBarSp1);
        displaySystem.setNode2D(223, &healthBarSp2);
        displaySystem.setNode2D(224, &healthBarSp3);
        displaySystem.setNode2D(225, &healthBarSp4);
        displaySystem.setNode2D(226, &healthBarSp5);

        displaySystem.setNode2D(227, &mainDinoSprite);
        break;
    case DevPetPage::Stats:
        displaySystem.setNode2D(200, &statsMainLabel);
        displaySystem.setNode2D(201, &statsButtonRight);
        displaySystem.setNode2D(230, &statsMoodLabel);
        displaySystem.setNode2D(231, &statsMood);
        displaySystem.setNode2D(232, &statsMoodValue);

        displaySystem.setNode2D(233, &statsEnergyLabel);
        displaySystem.setNode2D(234, &statsEnergy);
        displaySystem.setNode2D(235, &statsEnergyValue);

        displaySystem.setNode2D(236, &statsProductivityLabel);
        displaySystem.setNode2D(237, &statsProductivity);
        displaySystem.setNode2D(238, &statsProductivityValue);
        break;
    case DevPetPage::Game:

    default:
        break;
    }
}

DevPetPage DevPetGraphics::getCurrentPage()
{
    return currentPage;
}

void DevPetGraphics::setCurrentPage(DevPetPage page)
{
    currentPage = page;

    updateDisplayedNodes();
}

void DevPetGraphics::playMusic(String musicTitle)
{
    feedMusicName = musicTitle;
    lastTimeMusicUpdated = millis();
}

void DevPetGraphics::pushIssue(String issueTitle)
{
    if (currentPage == DevPetPage::Main)
    {
        displaySystem.setNode2D(FEED_ICON_Z, &feedIssueOpened);
        feedTitle1.setText("Issue");
        feedTitle2.setText(issueTitle);
        feedItemLastUpdate = millis();
    }
    internalDinoParty();
}

void DevPetGraphics::pushPullRequest(String pullRequestTitle)
{
    if (currentPage == DevPetPage::Main)
    {
        displaySystem.setNode2D(FEED_ICON_Z, &feedGitPullRequest);
        feedTitle1.setText("Pull Request");
        feedTitle2.setText(pullRequestTitle);
        feedItemLastUpdate = millis();
    }
    internalDinoParty();
}

void DevPetGraphics::pushNewCommits(long nbCommits)
{
    if (currentPage == DevPetPage::Main)
    {
        displaySystem.setNode2D(FEED_ICON_Z, &feedNewCommits);
        feedTitle1.setText("Commits");
        feedTitle2.setText(String(nbCommits) + " new commits");
        feedItemLastUpdate = millis();
    }
    internalDinoParty();
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
    expectedDinoIDLE = DINO_BIG_IDLE;
    if (!devPet.isDead())
    {
        mainDinoSprite.setAnimAfter(expectedDinoIDLE);
    }
}

void DevPetGraphics::internalFeedMusic()
{
    if (currentPage == DevPetPage::Main)
    {
        displaySystem.setNode2D(FEED_ICON_Z, &feedMusicIcon);
    }
    feedTitle1.setText("Listening");
    feedTitle2.setText(feedMusicName);
    expectedDinoIDLE = DINO_BIG_MUSIC;
    mainDinoSprite.setAnimAfter(expectedDinoIDLE);
}

void DevPetGraphics::internalDinoParty()
{
    mainDinoSprite.setAnim(DINO_BIG_PARTY);
    mainDinoSprite.setNbLoopBeforeNext(3);
    mainDinoSprite.setAnimAfter(expectedDinoIDLE);
}

void DevPetGraphics::internalSetDinoAnim(unsigned char anim)
{
    if (mainDinoCurrentAnim != DINO_BIG_DEAD)
    {
        mainDinoSprite.setAnim(anim);
        mainDinoCurrentAnim = anim;
    }
}

void DevPetGraphics::drinkCoffee()
{
    mainDinoSprite.setAnim(DINO_BIG_COFFEE);
    mainDinoSprite.setAnimAfter(expectedDinoIDLE);
}

void DevPetGraphics::revive()
{
    mainDinoSprite.setAnim(DINO_BIG_WAKE);
    mainDinoSprite.setAnimAfter(DINO_BIG_IDLE);
    updateDisplayedNodes();
}