/* Copyright (c) 2021 M.A.X. Port Team
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

#ifndef PATHS_HPP
#define PATHS_HPP

#include "point.hpp"
#include "textfileobject.hpp"
#include "unitinfo.hpp"

extern "C" {
#include "gnw.h"
}

class UnitPath : public TextFileObject {
protected:
    short x_end;
    short y_end;
    int distance_x;
    int distance_y;
    short euclidean_distance;

public:
    UnitPath();
    UnitPath(int target_x, int target_y);
    UnitPath(int distance_x, int distance_y, int euclidean_distance, int target_x, int target_y);
    virtual ~UnitPath();

    virtual unsigned short GetTypeIndex() const = 0;
    virtual void FileLoad(SmartFileReader& file) = 0;
    virtual void FileSave(SmartFileWriter& file) = 0;
    virtual void TextLoad(TextStructure& object) = 0;
    virtual void TextSave(SmartTextfileWriter& file) = 0;
    virtual Point GetPosition(UnitInfo* unit) const;
    virtual bool IsInPath(int grid_x, int grid_y) const;
    virtual void Path_vfunc8(UnitInfo* unit);
    virtual int Path_vfunc9(UnitInfo* unit) = 0;
    virtual bool Path_vfunc10(UnitInfo* unit) = 0;
    virtual void UpdateUnitAngle(UnitInfo* unit);
    virtual int Path_vfunc12(int unknown) = 0;
    virtual bool Path_vfunc13(UnitInfo* unit, WindowInfo* window) = 0;
    virtual bool IsEndStep() const;
    virtual int WritePacket(char* buffer);
    virtual void Path_vfunc16(int unknown1, int unknown2);
    virtual void Path_vfunc17(int unknown1, int unknown2);

    short GetEndX() const;
    short GetEndY() const;
    void SetEndXY(int target_x, int target_y);
};

class GroundPath : public UnitPath {};

class AirPath : public UnitPath {
    short length;
    char angle;
    short pixel_x_start;
    short pixel_y_start;
    int x_step;
    int y_step;
    int delta_x;
    int delta_y;

public:
    AirPath();
    AirPath(UnitInfo* unit, int distance_x, int distance_y, int euclidean_distance, int target_x, int target_y);
    ~AirPath();

    static TextFileObject* Allocate() { return new (std::nothrow) AirPath(); }

    unsigned short GetTypeIndex() const;
    void FileLoad(SmartFileReader& file);
    void FileSave(SmartFileWriter& file);
    void TextLoad(TextStructure& object);
    void TextSave(SmartTextfileWriter& file);
    Point GetPosition(UnitInfo* unit) const;
    void Path_vfunc8(UnitInfo* unit);
    int Path_vfunc9(UnitInfo* unit);
    bool Path_vfunc10(UnitInfo* unit);
    int Path_vfunc12(int unknown);
    bool Path_vfunc13(UnitInfo* unit, WindowInfo* window);
};

class BuilderPath : public UnitPath {};

#endif /* PATHS_HPP */