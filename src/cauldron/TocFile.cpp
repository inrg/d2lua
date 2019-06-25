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

#include <vector>
#include <fstream>
#include <Windows.h>
#include "TocFile.h"

using namespace d2lua;

TocFile::TocFile(std::string path) {

    char buffer[MAX_PATH];
    TocTag tag;
    std::string ln;
    std::fstream fs;

    tags = new std::vector<TocTag>();
    entries = new std::vector<std::string>();

    fs.open(path);

    while (!fs.eof()) {
        fs.getline(buffer, MAX_PATH);

        if (buffer[0] == '#' && buffer[1] != '#') {
            continue;
        }

        if (buffer[0] != '#') {
            entries->push_back(std::string(buffer));
            continue;
        }

        ln = std::string(buffer);
        tag = TocTag();
        tag.name = ln.substr(3, ln.find_first_of(':') - 3);
        tag.value = ln.substr(ln.find_first_of(':') + 1);
        tags->push_back(tag);
    }

    fs.close();
}