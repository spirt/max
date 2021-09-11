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

#include "window.hpp"

#include "enums.hpp"
#include "resource_manager.hpp"

/// \todo Fix gwin includes
extern "C" {
extern WindowInfo* gwin_get_window(unsigned char id);
extern int gwin_load_image(unsigned short id, WindowInfo* wid, short offx, short palette_from_image, int draw_to_screen,
                           int width_from_image = -1, int height_from_image = -1);
}

Window::Window(short ulx, short uly, short width, short height)
    : window_id(0),
      ulx(ulx),
      uly(uly),
      width(width),
      height(height),
      flags(0),
      resource_id(INVALID_ID),
      palette_from_image(false) {}

Window::Window(unsigned short resource_id)
    : window_id(0), flags(0), resource_id(resource_id), palette_from_image(false) {
    struct SpriteMeta image_header;
    int result;

    result = ResourceManager_ReadImageHeader(resource_id, &image_header);
    SDL_assert(result == 1);

    ulx = (640 - image_header.width) / 2;
    uly = (480 - image_header.height) / 2;
    width = image_header.width;
    height = image_header.height;
}

Window::Window(unsigned short resource_id, unsigned char win_id)
    : window_id(0), flags(0), resource_id(resource_id), palette_from_image(false) {
    struct SpriteMeta image_header;
    WindowInfo* window;
    int result;

    window = gwin_get_window(win_id);
    result = ResourceManager_ReadImageHeader(resource_id, &image_header);
    SDL_assert(result == 1);

    width = image_header.width;
    height = image_header.height;

    ulx = ((window->window.lrx - window->window.ulx - width) / 2) + window->window.ulx;
    uly = ((window->window.lry - window->window.uly - height) / 2) + window->window.uly;
}
Window::~Window() {
    if (window_id) {
        win_delete(window_id);
    }
}

void Window::FillWindowInfo(WindowInfo* window) {
    window->id = window_id;
    window->buffer = win_get_buf(window_id);
    window->window.ulx = 0;
    window->window.uly = 0;
    window->window.lrx = width;
    window->window.lry = height;
    window->unknown = width;
}

void Window::Add(bool draw_to_screen) {
    SDL_assert(window_id == 0);

    window_id = win_add(ulx, uly, width, height, 0, flags);

    if (resource_id != INVALID_ID) {
        WindowInfo window;

        FillWindowInfo(&window);
        gwin_load_image(resource_id, &window, width, palette_from_image, draw_to_screen);
    }
}

void Window::GetCursorPosition(int& x, int& y) const {
    int position_x;
    int position_y;

    mouse_get_position(&position_x, &position_y);
    x = position_x - ulx;
    y = position_y - uly;
}

bool Window::EventHandler() { return false; }
