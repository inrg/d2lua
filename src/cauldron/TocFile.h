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

#ifndef __CAULDRON_TOCFILE_H__
#define __CAULDRON_TOCFILE_H__

#include <string>
#include <vector>

namespace d2lua {
    struct TocTag {
        std::string name;
        std::string value;
    };

    class TocFile {
    public:
        std::string filename;
        std::vector<TocTag>* tags;
        std::vector<std::string>* entries;

        TocFile(std::string filename);
    };
}
#endif // __CAULDRON_TOCFILE_H__