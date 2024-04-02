#include <Arduino.h>

namespace utils
{
    namespace time
    {
        class TimeSystem
        {
        private:
            unsigned long timeInfoInit;
            struct tm initTime;
            struct tm currentTime;
            unsigned long previousMillis;

        public:
            TimeSystem();
            bool begin();
            void step();
            struct tm getInitTime();
            struct tm getTime();
            static String getTimeString(tm *timeinfo, const char *_fmt = "%A, %B %d %Y %H:%M:%S");
            String getCurrentTimeString(const char *_fmt = "%A, %B %d %Y %H:%M:%S");
            String getCurrentHourString();
            String getInitTimeString(const char *_fmt = "%A, %B %d %Y %H:%M:%S");
            String getInitHourString();
            /**
             * Europe/Paris timezone
             */
            const long GMT_OFFSET_SEC = 3600 * 1;
            const int DAYLIGHT_OFFSET_SEC = 3600 * 0;
            const char *NTP_SERVER = "pool.ntp.org";
        };
    }
}
