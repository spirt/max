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

#ifndef CIRCUMFERENCEWALKER_HPP
#define CIRCUMFERENCEWALKER_HPP

#include "point.hpp"

class CircumferenceWalker {
    Point start;
    int16_t direction;
    int16_t range;
    int16_t distance;
    Point offset;
    Point current;
    int16_t *grid_x;
    int16_t *grid_y;
    int16_t factor_x;
    int16_t factor_y;

    bool InitXY();
    bool InitDirection();

public:
    CircumferenceWalker(Point position, int32_t range);

    int32_t GetGridX() const;
    int32_t GetGridY() const;
    const Point *GetGridXY() const;

    bool FindNext();
};

#endif /* CIRCUMFERENCEWALKER_HPP */
