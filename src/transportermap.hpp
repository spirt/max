/* Copyright (c) 2022 M.A.X. Port Team
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef TRANSPORTERMAP_HPP
#define TRANSPORTERMAP_HPP

#include "accessmap.hpp"
#include "enums.hpp"
#include "point.hpp"

class UnitInfo;

class TransporterMap {
    AccessMap map;
    bool is_initialized;
    SmartPointer<UnitInfo> unit;
    unsigned char flags;
    unsigned char caution_level;
    ResourceID unit_type;

public:
    TransporterMap(UnitInfo* unit, unsigned char flags, unsigned char caution_level, ResourceID unit_type = INVALID_ID);
    ~TransporterMap();

    bool Search(Point site);
    void UpdateSite(Point site, bool mode);
};

#endif /* TRANSPORTERMAP_HPP */