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

#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "enums.hpp"
#include "events.hpp"

extern "C" {
#include "gnw.h"
}

class Window {
    WinID window_id;
    short ulx;
    short uly;
    short width;
    short height;
    unsigned int flags;
    unsigned short resource_id;
    bool palette_from_image;

public:
    Window(short ulx, short uly, short width, short height);
    Window(ResourceID id);
    Window(ResourceID id, unsigned char win_id);
    virtual ~Window();

    void FillWindowInfo(WindowInfo* window);
    void Add(bool draw_to_screen = false);
    void GetCursorPosition(int& x, int& y) const;
    void SetFlags(unsigned int flags);
    void SetPaletteMode(bool palette_from_image);
    virtual bool EventHandler(Event& event);
};

#endif /* WINDOW_HPP */