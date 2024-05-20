/*
SPDX-FileCopyrightText: 2024 AFCMS <afcm.contact@gmail.com>
SPDX-License-Identifier: GPL-3.0-or-later
*/

#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <vector>
#include <map>

#pragma once

#define OLED_RESET 0x3C

namespace utils
{
    namespace display
    {
        class DisplaySystem;

        /**
         * @brief The width of the screen
         */
        static const unsigned char SCREEN_WIDTH = 128;

        /**
         * @brief The height of the screen
         */
        static const unsigned char SCREEN_HEIGHT = 64;

        /**
         * @brief The height of the yellow upper band of the screen
         */
        static const unsigned char SCREEN_UB_HEIGHT = 16;

        /**
         * @brief The height of the blue lower band of the screen
         */
        static const unsigned char SCREEN_LB_HEIGHT = SCREEN_HEIGHT - SCREEN_UB_HEIGHT;

        /**
         * @brief The number of characters that can be displayed on a line
         */
        static const unsigned char SCREEN_NB_CHARS = SCREEN_WIDTH / 6;

        /**
         * @brief A 2D node that can be drawn on the DisplaySystem
         */
        class Node2D
        {
        protected:
            /**
             * @brief The position of the node on the screen
             */
            uint8_t x, y;

        public:
            /**
             * @brief Set the position of the node on the screen
             */
            void setPos(uint8_t _x, uint8_t _y);

            /**
             * @brief Draw a frame
             */
            virtual void drawFrame(DisplaySystem *displaySystem) = 0;
        };

        /**
         * @brief A map of 2D nodes
         */
        typedef std::map<unsigned char, Node2D *> Node2DMap;

        class DisplaySystem
        {
        private:
            /**
             * @brief The rate at which the display is refreshed
             */
            unsigned char fps;

            /**
             * @brief The display to draw on
             */
            Adafruit_SSD1306 dp;

            unsigned long lastMillis;

            /**
             * All nodes to render on the screen
             *
             * `std::map` is a sorted container, so the nodes will be drawn in the order of their key
             */
            Node2DMap nodes;

        public:
            /**
             * @brief Create a DisplaySystem with a given refresh rate
             */
            DisplaySystem(unsigned char _fps);

            /**
             * @brief Get the refresh rate of the display system
             */
            unsigned char getFps();

            /**
             * @brief Get a pointer to the display
             */
            Adafruit_SSD1306 *getDP();

            /**
             * @brief Add a 2D node to the display system at the given zIndex, or replace the node at zIndex if it already exists
             */
            void setNode2D(Node2D *node, unsigned char zIndex);

            /**
             * @brief Remove the 2D node from the display system at the given zIndex
             */
            void removeNode2D(unsigned char zIndex);

            /**
             * @brief Get the 2D node from the display system at the given zIndex
             */
            Node2D *getNode2D(unsigned char zIndex);

            /**
             * @brief Get all 2D nodes in the display system
             */
            Node2DMap getNodes2D();

            /**
             * @brief Set all 2D nodes in the display system
             */
            void setNodes2D(Node2DMap _nodes);

            /**
             * @brief Clear the display
             */
            void clearDisplay();

            /**
             * @brief Draw a 2D node on the display
             */
            void drawNode2D(Node2D *node);

            /**
             * @brief Initialize the display system
             */
            void begin();

            /**
             * @brief Update the display. Calls `display()` on the display.
             *
             * @internal
             */
            void display();

            /**
             * @brief Called in the main loop to update the display at the given refresh rate
             */
            void step();
        };
    }
}
