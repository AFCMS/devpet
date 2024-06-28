/*
SPDX-FileCopyrightText: 2024 AFCMS <afcm.contact@gmail.com>
SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "devpet.hpp"

DevPet::DevPet()
{
    preferences.begin("devpet");
    loadData();
};

void DevPet::log(utils::comm::CommSystem &comm)
{
    comm.log("DevPet: Mood:" + String(mood) + ", Energy:" + String(energy) + ", Productivity:" + String(productivity) + ", Health:" + String(health));
}

unsigned char DevPet::getMood()
{
    return mood;
}

void DevPet::setMood(unsigned char mood)
{
    this->mood = mood;
    updateHealth();
    saveData();
}

void DevPet::boostMood()
{
    setMood(constrain(getMood() + 20, 0, 255));
}

unsigned char DevPet::getEnergy()
{
    return energy;
}

void DevPet::setEnergy(unsigned char energy)
{
    this->energy = energy;
    updateHealth();
    saveData();
}

void DevPet::boostEnergy()
{
    setEnergy(constrain(getEnergy() + 20, 0, 255));
}

unsigned char DevPet::getProductivity()
{
    return productivity;
}

void DevPet::setProductivity(unsigned char productivity)
{
    this->productivity = productivity;
    updateHealth();
    saveData();
}

void DevPet::boostProductivity()
{
    setProductivity(constrain(getProductivity() + 20, 0, 255));
}

unsigned char DevPet::getHealth()
{
    return health;
}

void DevPet::updateHealth()
{
    float geometricMean = pow(mood * energy * productivity, 1.0 / 3.0);
    health = (unsigned char)geometricMean;
    if (health == 0)
    {
        dead = true;
        justDied = true;
    }
}

void DevPet::revive()
{
    mood = DEFAULT_MOOD;
    energy = DEFAULT_ENERGY;
    productivity = DEFAULT_PRODUCTIVITY;
    updateHealth();
    dead = false;
    saveData();
}

bool DevPet::isDead()
{
    return dead;
}

bool DevPet::isJustDead()
{
    return justDied;
}

void DevPet::saveData()
{
    preferences.putUChar("mood", mood);
    preferences.putUChar("energy", energy);
    preferences.putUChar("productivity", productivity);
}

void DevPet::loadData()
{
    mood = preferences.getUChar("mood", DEFAULT_MOOD);
    energy = preferences.getUChar("energy", DEFAULT_ENERGY);
    productivity = preferences.getUChar("productivity", DEFAULT_PRODUCTIVITY);
    updateHealth();
}

void DevPet::step()
{
    if (isDead())
    {
        if (justDied)
        {
            justDied = false;
        }
    }
    else if (millis() - lastUpdate > UPDATE_SPEED)
    {
        lastUpdate = millis();

        setMood(constrain(getMood() - 20, 0, 255));
        setEnergy(constrain(getEnergy() - 20, 0, 255));
        setProductivity(constrain(getProductivity() - 20, 0, 255));
    }
}