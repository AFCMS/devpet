/*
SPDX-FileCopyrightText: 2024 AFCMS <afcm.contact@gmail.com>
SPDX-License-Identifier: GPL-3.0-or-later
*/

#include <Preferences.h>
#include "comm.hpp"

#pragma once

class DevPet
{
private:
    unsigned char mood = 0;
    unsigned char energy = 0;
    unsigned char productivity = 0;

    /**
     * @brief The health of the DevPet, which is calculated as the geometric mean of the mood, energy and productivity.
     */
    unsigned char health = 0;

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
     * @brief Update the health of the DevPet
     *
     * The health is calculated as the geometric mean of the mood, energy and productivity.
     */
    void updateHealth();

    void saveData();
    void loadData();
};