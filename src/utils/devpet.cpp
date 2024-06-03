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

unsigned char DevPet::getHealth()
{
    return health;
}

void DevPet::updateHealth()
{
    float geometricMean = pow(mood * energy * productivity, 1.0 / 3.0);
    health = (unsigned char)geometricMean;
}

void DevPet::saveData()
{
    preferences.putUChar("mood", mood);
    preferences.putUChar("energy", energy);
    preferences.putUChar("productivity", productivity);
}

void DevPet::loadData()
{
    mood = preferences.getUChar("mood", 0);
    energy = preferences.getUChar("energy", 0);
    productivity = preferences.getUChar("productivity", 0);
    updateHealth();
}