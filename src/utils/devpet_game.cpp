/*
SPDX-FileCopyrightText: 2024 AFCMS <afcm.contact@gmail.com>
SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "devpet_game.hpp"

DevPetGame::DevPetGame(comm::CommSystem &_commSystem, display::DisplaySystem &_displaySystem) : commSystem(_commSystem), displaySystem(_displaySystem)
{
}

DevPetGameState DevPetGame::getState()
{
    return state;
}

void DevPetGame::step()
{
    if (millis() - lastMillis > 1000 / sps)
    {
        switch (state)
        {
        case DevPetGameState::Menu:
            // Waiting for button press to start the game
            break;
        case DevPetGameState::InGame:
            // player.setPos(50, 50);
            updatePlayerPosition();
            updateEnemyPosition();
            checkGameConditions();
            break;
        case DevPetGameState::End:
            // Display score and wait for button press to restart
            break;
        }
        lastMillis = millis();
    }
}

void DevPetGame::start()
{
    commSystem.log("Starting DevPet game");
    state = DevPetGameState::InGame;
    score = 0;
    isJumping = false;
    jumpUp = true;
    player.setPos(0, screenHeight - groundLevel);
    updateNodes();
    spawnEnemy();
}

void DevPetGame::updateNodes()
{
    displaySystem.clearNodes2D();
    switch (state)
    {
    case DevPetGameState::Menu:
        displaySystem.setNode2D(61, &buttonLeft);
        displaySystem.setNode2D(62, &buttonCenter);
        break;
    case DevPetGameState::InGame:
        displaySystem.setNode2D(50, &player);
        displaySystem.setNode2D(51, &enemyType1);
        displaySystem.setNode2D(60, &scoreLabel);
        break;
    case DevPetGameState::End:
        displaySystem.setNode2D(60, &scoreLabel);
        displaySystem.setNode2D(61, &buttonLeft);
        displaySystem.setNode2D(62, &buttonCenter);
        displaySystem.setNode2D(63, &gameOver);
        break;
    };
}

void DevPetGame::updatePlayerPosition()
{
    unsigned char px, py;
    player.getPos(px, py);

    if (isJumping)
    {
        if (jumpUp)
        {
            if (py > jumpHeight)
            {
                py -= jumpSpeed;
            }

            if (py <= jumpHeight)
            {
                jumpUp = false; // Start moving down
            }
        }
        else
        {
            py += jumpSpeed; // Move down
            if (py >= screenHeight - groundLevel)
            {
                py = screenHeight - groundLevel; // Reset to ground level
                isJumping = false;
                jumpUp = true; // Ready for next jump
            }
        }
    }
    else
    {
        py = screenHeight - groundLevel; // Ensure player is on ground if not jumping
    }

    player.setPos(px, py);
}

void DevPetGame::updateEnemyPosition()
{
    unsigned char ex, ey;
    enemyType1.getPos(ex, ey);

    // Check if the enemy has reached the left side of the screen or beyond
    if (ex > 0 && ex <= enemySpeed)
    {
        // Increment score and spawn a new enemy
        score++;
        scoreLabel.setText("Score: " + String(score));
        spawnEnemy();
    }
    else if (ex > 0)
    {
        // Move the enemy towards the left
        ex -= enemySpeed;
        enemyType1.setPos(ex, ey);
    }
    else
    {
        // This condition handles the case where ex is already 0
        // It ensures a new enemy is spawned without incrementing the score
        // This is a safeguard and might not be necessary if enemies are always spawned
        // with an x-coordinate greater than 0.
        spawnEnemy();
    }
}

void DevPetGame::checkGameConditions()
{
    unsigned char px, py, ex, ey;
    player.getPos(px, py);
    enemyType1.getPos(ex, ey);

    if (checkCollision(player, enemyType1))
    {
        commSystem.log("Game over! Score: " + String(score));
        state = DevPetGameState::End;
        updateNodes();
    }
}

void DevPetGame::pressButton()
{
    switch (state)
    {
    case DevPetGameState::Menu:
        start();
        break;
    case DevPetGameState::InGame:
        commSystem.log("Button pushed");
        if (!isJumping)
        {
            isJumping = true;
            commSystem.log("Player jump");
        }
        break;
    case DevPetGameState::End:
        state = DevPetGameState::Menu;
        break;
    }
}

void DevPetGame::spawnEnemy()
{
    // Randomly select an enemy type
    /*int enemyType = rand() % 3;
    switch (enemyType)
    {
    case 0:
        currentEnemy = &enemyType1;
        currentEnemy->setPos(128 - 13, 64 - 13);
        break;
    case 1:
        currentEnemy = &enemyType2;
        currentEnemy->setPos(128 - 13, 64 - 13);
        break;
    case 2:
        currentEnemy = &enemyType3;
        currentEnemy->setPos(128 - 13, 64 - 13);
        break;
    }*/

    enemyType1.setPos(128 - 13, 64 - 13);
}

bool DevPetGame::checkCollision(display::SpriteStatic &rectA, display::SpriteStatic &rectB)
{
    unsigned char ax, ay, bx, by;
    rectA.getPos(ax, ay);
    rectB.getPos(bx, by);

    // Check if one rectangle is to the left of the other
    if (ax + rectA.w < bx || bx + rectB.w < ax)
    {
        return false;
    }
    // Check if one rectangle is above the other
    if (ay + rectA.h < by || by + rectB.h < ay)
    {
        return false;
    }
    return true; // Overlapping
}