/*
SPDX-FileCopyrightText: 2024 AFCMS <afcm.contact@gmail.com>
SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "comm.hpp"

namespace utils
{
    namespace comm
    {
        CommSystem::CommSystem(){};

        BluetoothSerial CommSystem::getSerial()
        {
            return serial_bt;
        };

        void CommSystem::begin()
        {
            serial_bt.begin(BT_NAME);
        };

        std::queue<CommandResult> CommSystem::step()
        {
            std::queue<CommandResult> commandQueue = {};
            while (readCommand(&commandQueue))
                ;
            return commandQueue;
        };
        std::queue<CommandResult> commandQueue = {};

        void CommSystem::sendString(String str)
        {
            serial_bt.println(str);
        };

        bool CommSystem::readCommand(std::queue<CommandResult> *queue)
        {
            if (serial_bt.available())
            {
                String line = serial_bt.readStringUntil('\n');

                int index = line.indexOf(' ');

                String command = line.substring(0, index);

                String payload = line.substring(index + 1);

                if (command != "")
                {
                    queue->push({command, payload});
                }
                return true;
            }
            return false;
        };

        void CommSystem::sendCommand(String command)
        {
            sendString(command);
        };

        void CommSystem::sendCommand(String command, String playload)
        {
            sendString(command + " " + playload);
        };

        void CommSystem::log(LogMessageType type, String message)
        {
            switch (type)
            {
            case MT_LOG:
                sendCommand("log", "[LOG] " + message);
                break;
            case MT_ERROR:
                sendCommand("log", "[ERROR] " + message);
                break;
            case MT_INFO:
                sendCommand("log", "[INFO] " + message);
                break;
            default:
                break;
            }
        };

        void CommSystem::log(String message)
        {
            log(MT_LOG, message);
        };
    }
}