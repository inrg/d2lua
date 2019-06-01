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

#ifndef __CAULDRON_LOGGER_H__
#define __CAULDRON_LOGGER_H__

#include <ios>
#include <fstream>

namespace cauldron {
    enum LogLevel {
        llNone = 0,
        llError, llWarning, llInfo, llDebug
    };

    class Logger {
    public:
        Logger(std::string msg, LogLevel level);
        void error(std::string msg);
        void warning(std::string msg);
        void info(std::string msg);
        void debug(std::string msg);
    private:
        std::string _filename;
        std::ofstream _fs;
        LogLevel _level;

        void _writeLog(std::string msg, LogLevel level);
    };
}

#endif // __CAULDRON_LOGGER_H__
