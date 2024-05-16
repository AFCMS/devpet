/*
SPDX-FileCopyrightText: 2024 AFCMS <afcm.contact@gmail.com>
SPDX-License-Identifier: GPL-3.0-or-later
*/

#include <queue>
#include <BluetoothSerial.h>

#pragma once

#if !defined(CONFIG_BT_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

namespace utils
{
    namespace comm
    {
        /**
         * @brief Bluetooth Peripheral name
         */
        const String BT_NAME = "DevPet";

        /**
         * @brief Serial baud rate
         */
        const int SERIAL_BAUD = 9600;

        enum LogMessageType
        {
            MT_LOG,
            MT_ERROR,
            MT_INFO
        };

        struct CommandResult
        {
            String command_name;
            String payload;
        };

        /**
         * @brief Serial Communication System
         */
        class CommSystem
        {
        private:
            /**
             * @brief The underlying BluetoothSerial object
             *
             * @see BluetoothSerial
             */
            BluetoothSerial serial_bt;

            /**
             * @brief Send a string to the serial communication.
             *
             * Automatically adds a newline character at the end of the string.
             *
             * @param str The string to be sent
             */
            void sendString(String str);

            /**
             * @brief Read a command from the serial communication, push the command to a queue
             *
             * @return true if a command was read, false otherwise
             */
            bool readCommand(std::queue<CommandResult> *queue);

        public:
            CommSystem();

            /**
             * @brief Get the underlying BluetoothSerial object
             *
             * @see BluetoothSerial
             */
            BluetoothSerial getSerial();

            /**
             * @brief Begin the serial stream
             */
            void begin();

            /**
             * @brief Read commands from serial stream until nothing is availlable, return a queue of commands
             *
             * @warning If the serial connection sends too much data it could cause the loop take too much time or to never return
             */
            std::queue<CommandResult> step();

            /**
             * @brief Send a command to the serial communication without payload.
             *
             * @param command The command to be sent, should not contain spaces
             */
            void sendCommand(String command);

            /**
             * @brief Send a command to the serial communication.
             *
             * @param command The command to be sent, should not contain spaces
             * @param payload The payload to be sent
             */
            void sendCommand(String command, String payload);

            /**
             * @brief Send a `log` command to the serial communication.
             *
             * @param type The type of the log message
             * @param message The message to be sent
             */
            void log(LogMessageType type, String message);

            /**
             * @brief Send a `log` command with the default type to the serial communication.
             *
             * @param message The message to be sent
             */
            void log(String message);
        };
    }
}