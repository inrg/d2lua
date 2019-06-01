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

#ifndef __CAULDRON_H__
#define __CAULDRON_H__

#include <Windows.h>
#include <string>
#include "Logger.h"

namespace cauldron {
    class Bootstrap {
    public:
        HMODULE module;
        std::string dllName;
        std::string basePath;

        struct {
            std::string logging_filename;
            LogLevel logging_level;
        } config;

        Logger* logger;
    public:
        void load(HMODULE);
        void unload(void);
        
        static Bootstrap* getInstance(void);
    private:
        static Bootstrap* _instance;
        Bootstrap(void);
    };
}

#endif // __CAULDRON_H__
