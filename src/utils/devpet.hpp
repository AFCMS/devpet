/*
SPDX-FileCopyrightText: 2024 AFCMS <afcm.contact@gmail.com>
SPDX-License-Identifier: GPL-3.0-or-later
*/

#include <Preferences.h>
#include "comm.hpp"

#pragma once

enum DevPetDifficulty
{
    Easy = 1,
    Medium = 2,
    Hard = 4,
    Insane = 5,
};

class DevPet
{
private:
    static const unsigned char DEFAULT_MOOD = 255;
    static const unsigned char DEFAULT_ENERGY = 255;
    static const unsigned char DEFAULT_PRODUCTIVITY = 255;

    unsigned char mood = 0;
    unsigned char energy = 0;
    unsigned char productivity = 0;

    /**
     * @brief The health of the DevPet, which is calculated as the geometric mean of the mood, energy and productivity.
     */
    unsigned char health = 0;
    bool dead = false;
    bool justDied = false;

    unsigned long lastUpdate = 0;

    /**
     * @brief The speed at which the stats of the pet will decrease when no actions are taken.
     *
     * The reduce step will happen at this interval.
     */
    static const unsigned long UPDATE_SPEED = 1000 * 10;

    /**
     * @brief The preferences object to store the data of the DevPet in non-volatile memory
     */
    Preferences preferences;

public:
    DevPet();

    /**
     * @brief Log the current state of the DevPet
     *
     * @param comm The communication system to be used
     */
    void log(utils::comm::CommSystem &comm);

    /**
     * @brief Get the mood of the DevPet
     */
    unsigned char getMood();

    /**
     * @brief Set the mood of the DevPet
     */
    void setMood(unsigned char mood);

    /**
     * @brief Increate the mood of the pet
     */
    void boostMood();

    /**
     * @brief Get the energy of the DevPet
     */
    unsigned char getEnergy();

    /**
     * @brief Set the energy of the DevPet
     */
    void setEnergy(unsigned char energy);

    /**
     * @brief Increate the energy of the pet
     */
    void boostEnergy();

    /**
     * @brief Get the productivity of the DevPet
     */
    unsigned char getProductivity();

    /**
     * @brief Set the productivity of the DevPet
     */
    void setProductivity(unsigned char productivity);

    /**
     * @brief Increate the productivity of the pet
     */
    void boostProductivity();

    /**
     * @brief Get the health of the DevPet
     */
    unsigned char getHealth();

    /**
     * @brief Update the health of the DevPet
     *
     * The health is calculated as the geometric mean of the mood, energy and productivity.
     */
    void updateHealth();

    /**
     * @brief If the pet died, revive it (reset it's stats)
     */
    void revive();

    bool isDead();
    bool isJustDead();

    void saveData();
    void loadData();

    void step();
};