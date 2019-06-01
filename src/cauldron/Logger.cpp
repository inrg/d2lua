/*
 * Copyright (C) 2019 HE Yaowen <he.yaowen@hotmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Logger.h"
#include <time.h>

using namespace cauldron;

Logger::Logger(std::string filename, LogLevel level)
{
    _filename = filename;
    _fs = std::ofstream();

    _level = level;
}

void Logger::error(std::string msg)
{
    _writeLog("[ERROR] " + msg, llError);
}

void Logger::warning(std::string msg)
{
    _writeLog("[WARNING] " + msg, llWarning);
}

void Logger::info(std::string msg)
{
    _writeLog("[INFO] " + msg, llInfo);
}

void Logger::debug(std::string msg)
{
    _writeLog("[DEBUG] " + msg, llDebug);
}

void Logger::_writeLog(std::string msg, LogLevel level)
{
    const time_t t = time(NULL);
    struct tm lt;
    char buff[256];

    if (level > _level) {
        return;
    }

    localtime_s(&lt, &t);

    sprintf_s(buff, 256, "[%d-%d-%d %d:%d:%d] ", lt.tm_year + 1900, lt.tm_mon + 1, lt.tm_mday, lt.tm_hour, lt.tm_min, lt.tm_sec);

    _fs.open(_filename, std::ios_base::app);
    _fs << buff << msg.c_str() << std::endl;
    _fs.close();
}
