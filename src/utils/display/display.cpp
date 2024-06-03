/*
SPDX-FileCopyrightText: 2024 AFCMS <afcm.contact@gmail.com>
SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "display.hpp"

namespace utils
{
    namespace display
    {
        void Node2D::setPos(unsigned char _x, unsigned char _y)
        {
            x = _x;
            y = _y;
        };

        DisplaySystem::DisplaySystem(unsigned char _fps)
        {

            dp = Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
            fps = _fps;
            lastMillis = 0;
        };

        unsigned char DisplaySystem::getFps()
        {
            return fps;
        };

        Adafruit_SSD1306 *DisplaySystem::getDP()
        {
            return &dp;
        };

        void DisplaySystem::setNode2D(unsigned char zIndex, Node2D *node)
        {
            nodes[zIndex] = node;
        };

        void DisplaySystem::removeNode2D(unsigned char zIndex)
        {
            nodes.erase(zIndex);
        };

        Node2D *DisplaySystem::getNode2D(unsigned char zIndex)
        {
            return nodes[zIndex];
        };

        Node2DMap DisplaySystem::getNodes2D()
        {
            return nodes;
        };

        void DisplaySystem::setNodes2D(Node2DMap _nodes)
        {
            nodes = _nodes;
        };

        void utils::display::DisplaySystem::clearNodes2D()
        {
            nodes.clear();
        };

        void DisplaySystem::clearDisplay()
        {
            dp.clearDisplay();
        };

        void DisplaySystem::drawNode2D(Node2D *node)
        {
            node->drawFrame(this);
        };

        void DisplaySystem::begin()
        {
            dp.begin(SSD1306_SWITCHCAPVCC, 0x3C);
            dp.clearDisplay();
            dp.setTextSize(1);
            dp.setTextColor(SSD1306_WHITE);
            dp.setCursor(0, 0);
            dp.display();
        };

        void DisplaySystem::display()
        {
            dp.display();
        };

        void DisplaySystem::step()
        {
            if (millis() - lastMillis > 1000 / fps)
            {
                lastMillis = millis();
                clearDisplay();

                for (auto it = nodes.begin(); it != nodes.end(); ++it)
                {
                    it->second->drawFrame(this);
                }

                display();
            }
        };
    }
}
