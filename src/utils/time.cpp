#include <Arduino.h>
#include "time.hpp"

namespace utils
{
    namespace time
    {
        TimeSystem::TimeSystem()
        {
            timeInfoInit = 0;
            initTime = {};
            currentTime = {};
            previousMillis = 0;
        };

        bool TimeSystem::begin()
        {
            configTime(GMT_OFFSET_SEC, DAYLIGHT_OFFSET_SEC, NTP_SERVER);

            if (!getLocalTime(&initTime))
            {
                return false;
            }
            currentTime = initTime;
            timeInfoInit = millis();
            return true;
        };

        void TimeSystem::step()
        {
            unsigned long currentMillis = millis();
            if (currentMillis - previousMillis >= 1000)
            {
                previousMillis = currentMillis;
                currentTime.tm_sec += 1;
                currentTime.tm_sec %= 60;
                if (currentTime.tm_sec == 0)
                {
                    currentTime.tm_min += 1;
                    currentTime.tm_min %= 60;
                    if (currentTime.tm_min == 0)
                    {
                        currentTime.tm_hour += 1;
                        currentTime.tm_hour %= 24;
                    }
                }
            }
        };

        struct tm TimeSystem::getInitTime()
        {
            return initTime;
        };

        struct tm TimeSystem::getTime()
        {
            return currentTime;
        };

        String TimeSystem::getTimeString(tm *timeinfo, const char *_fmt = "%A, %B %d %Y %H:%M:%S")
        {
            char buffer[80];
            strftime(buffer, 80, _fmt, timeinfo);
            return String(buffer);
        };

        String TimeSystem::getCurrentTimeString(const char *_fmt = "%A, %B %d %Y %H:%M:%S")
        {
            return getTimeString(&currentTime, _fmt);
        };

        String TimeSystem::getCurrentHourString()
        {
            return getTimeString(&currentTime, "%H:%M:%S");
        };

        String TimeSystem::getInitTimeString(const char *const _fmt = "%A, %B %d %Y %H:%M:%S")
        {
            return getTimeString(&initTime, _fmt);
        };

        String TimeSystem::getInitHourString()
        {
            return getTimeString(&initTime, "%H:%M:%S");
        };
    }
}
