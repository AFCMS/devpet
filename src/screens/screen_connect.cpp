/*
SPDX-FileCopyrightText: 2024 AFCMS <afcm.contact@gmail.com>
SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "screen_connect.hpp"

namespace screens
{
    display::Text connectTitle(0, 0, "Waiting for Serial");

    display::SpriteStatic connectBluetoothSprite(0, 32, images::static_bluetooth, 24, 24);

    display::Node2DMap connectNodes = {
        {0, &connectTitle},
        {1, &connectBluetoothSprite}};

    display::Node2DMap connect()
    {
        // Title in the upper bar
        connectTitle.setCharsMax(21);
        connectTitle.setFontSize(1);
        connectTitle.setCentered(true);

        return connectNodes;
    }
}