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

#include "message_manager.hpp"

#include <algorithm>

#include "dialogmenu.hpp"
#include "gui.hpp"

extern "C" {
#include "gnw.h"
}

/// \todo Fix gwin includes
extern "C" {
WindowInfo* gwin_get_window(unsigned char id);
}

static_assert(sizeof(Point) == 4, "It is expected that Point is exactly 2+2 bytes long.");
static_assert(sizeof(bool) == 1, "It is expected that bool is exactly 1 byte long.");

#define MESSAGE_MANAGER_TEAM_COUNT 4
#define MESSAGE_MANAGER_MAX_COUNT 50
#define MESSAGE_MANAGER_MESSAGE_BUFFER_SIZE 800
#define MESSAGE_MANAGER_TEXT_BUFFER_SIZE 300

char MessageManager_MessageBuffer[MESSAGE_MANAGER_MESSAGE_BUFFER_SIZE];
char MessageManager_TextBuffer[MESSAGE_MANAGER_TEXT_BUFFER_SIZE];

short MessageManager_Buffer1_Length;
short MessageManager_MessageBox_Width;
short MessageManager_MessageBox_Height;
char* MessageManager_MessageBox_BgColor;
bool MessageManager_MessageBox_IsActive;

/// \todo Implement correct LUT
char** MessageManager_MessageBox_BgColorArray[] = {0, 0, 0};

SmartList<MessageLogEntry> MessageManager_TeamMessageLog[MESSAGE_MANAGER_TEAM_COUNT];

void MessageManager_WrapText(char* text, short width) {
    int position = 0;
    short row_width = 0;
    char* buffer = MessageManager_MessageBuffer;

    do {
        if (text[position] == '\n') {
            MessageManager_MessageBox_Width = std::max(row_width, MessageManager_MessageBox_Width);
            MessageManager_MessageBox_Height += 10;

            MessageManager_MessageBuffer[MessageManager_Buffer1_Length] = ' ';
            ++MessageManager_Buffer1_Length;

            MessageManager_MessageBuffer[MessageManager_Buffer1_Length] = '\0';
            ++MessageManager_Buffer1_Length;

            row_width = 0;
            buffer = &MessageManager_MessageBuffer[MessageManager_Buffer1_Length];

        } else {
            short char_width = text_char_width(text[position]);

            if ((row_width + char_width) > width) {
                char* line_buffer = &MessageManager_MessageBuffer[MessageManager_Buffer1_Length];

                *line_buffer = '\0';
                --line_buffer;

                while (*line_buffer != ' ') {
                    --line_buffer;
                }

                *line_buffer = '\0';
                row_width = text_width(buffer);
                MessageManager_MessageBox_Width = std::max(row_width, MessageManager_MessageBox_Width);
                buffer = line_buffer + 1;
                row_width = text_width(buffer);
                MessageManager_MessageBox_Height += 10;
            }

            row_width += char_width;

            SDL_assert(MessageManager_Buffer1_Length < sizeof(MessageManager_MessageBuffer));

            MessageManager_MessageBuffer[MessageManager_Buffer1_Length] = text[position];
            ++MessageManager_Buffer1_Length;
        }
    } while (text[position++] != '\0');

    MessageManager_MessageBox_Width = std::max(row_width, MessageManager_MessageBox_Width);
    MessageManager_MessageBox_Height += 10;
}

void MessageManager_DrawMessageBoxText(unsigned char* buffer, int width, int left_margin, int top_margin, char* text,
                                       int color, bool monospace) {
    int flags;
    int offset;

    offset = 0;
    text_font(5);

    top_margin *= width;

    if (monospace) {
        flags = 0x40000;
    } else {
        flags = 0;
    }

    color += flags + 0x10000;
    do {
        text_to_buf(&buffer[left_margin + top_margin], &text[offset], width, width, color);
        top_margin += 10 * width;
        offset += strlen(&text[offset]) + 1;
    } while (text[offset] != '\0');
}

void MessageManager_AddMessage(char* text, ResourceID id) {
    MessageManager_TeamMessageLog[GUI_PlayerTeamIndex].PushBack(
        *dynamic_cast<MessageLogEntry*>(new (std::nothrow) MessageLogEntry(text, id)));

    if (MessageManager_TeamMessageLog[GUI_PlayerTeamIndex].GetCount() > MESSAGE_MANAGER_MAX_COUNT) {
        MessageManager_TeamMessageLog[GUI_PlayerTeamIndex].Remove(
            *MessageManager_TeamMessageLog[GUI_PlayerTeamIndex].Begin());
    }
}

void MessageManager_DrawMessage(char* text, char type, UnitInfo* unit, Point point) {
    if (text[0] != '\0') {
        MessageManager_TeamMessageLog[GUI_PlayerTeamIndex].PushBack(
            *dynamic_cast<MessageLogEntry*>(new (std::nothrow) MessageLogEntry(text, unit, point)));

        if (MessageManager_TeamMessageLog[GUI_PlayerTeamIndex].GetCount() > MESSAGE_MANAGER_MAX_COUNT) {
            MessageManager_TeamMessageLog[GUI_PlayerTeamIndex].Remove(
                *MessageManager_TeamMessageLog[GUI_PlayerTeamIndex].Begin());
        }

        MessageManager_DrawMessage(text, type, 0);
    }
}

void MessageManager_DrawMessage(char* text, char type, int mode, bool flag1, bool save_to_log) {
    if (*text != '\0') {
        if (mode) {
            DialogMenu dialog(text, flag1);
            dialog.Run();
        } else {
            WindowInfo* window_2;
            WindowInfo* window_38;
            int width;
            int offset_x;
            int offset_y;
            Rect bounds;

            if (MessageManager_MessageBox_IsActive) {
                MessageManager_ClearMessageBox();
            }

            if (save_to_log) {
                MessageManager_TeamMessageLog[GUI_PlayerTeamIndex].PushBack(
                    *dynamic_cast<MessageLogEntry*>(new (std::nothrow) MessageLogEntry(text, I_CMPLX)));

                if (MessageManager_TeamMessageLog[GUI_PlayerTeamIndex].GetCount() > MESSAGE_MANAGER_MAX_COUNT) {
                    MessageManager_TeamMessageLog[GUI_PlayerTeamIndex].Remove(
                        *MessageManager_TeamMessageLog[GUI_PlayerTeamIndex].Begin());
                }
            }

            text_font(5);
            window_38 = gwin_get_window(38);
            width = window_38->window.lrx - window_38->window.ulx;

            MessageManager_MessageBox_Width = 0;
            MessageManager_Buffer1_Length = 0;
            MessageManager_MessageBox_Height = 20;

            MessageManager_WrapText(text, width - 20);

            MessageManager_MessageBuffer[MessageManager_Buffer1_Length] = '\0';
            MessageManager_MessageBox_Width += 20;

            offset_x = 0;
            offset_y = 10;

            window_2 = gwin_get_window(2);

            window_2->window.ulx = window_38->window.ulx + offset_x;
            window_2->window.uly = window_38->window.uly + offset_y;
            window_2->window.lrx = window_2->window.ulx + MessageManager_MessageBox_Width;
            window_2->window.lry = window_2->window.uly + MessageManager_MessageBox_Height;

            window_2->buffer = &window_38->buffer[offset_x + 640 * offset_y];

            MessageManager_MessageBox_BgColor = *MessageManager_MessageBox_BgColorArray[type];
            MessageManager_MessageBox_IsActive = true;

            /// \todo Implement functions
            //            sub_9A9FD(&bounds);
            //            drawmap_add_dirty_zone(&bounds);
        }
    }
}

void MessageManager_DrawMessageBox() {
    WindowInfo* window;
    int height;
    int fullw;
    int row;

    window = gwin_get_window(2);

    for (height = MessageManager_MessageBox_Height, fullw = 0; height > 0; --height, fullw += 640) {
        for (row = 0; row < MessageManager_MessageBox_Width; ++row) {
            window->buffer[row + fullw] = MessageManager_MessageBox_BgColor[window->buffer[row + fullw]];
        }
    }

    MessageManager_DrawMessageBoxText(window->buffer, 640, 10, 10, MessageManager_MessageBuffer, 0xFF, false);
}

void MessageManager_ClearMessageBox() {
    WindowInfo* window;
    Rect bounds;

    /// \todo Implement functions
    //            sub_9A9FD(&bounds);
    //            drawmap_add_dirty_zone(&bounds);

    window = gwin_get_window(2);

    window->window.ulx = -1;
    window->window.uly = -1;
    window->window.lrx = -1;
    window->window.lry = -1;

    MessageManager_MessageBox_IsActive = false;
}

void MessageManager_DrawTextMessage(WindowInfo* window, unsigned char* buffer, int width, int left_margin,
                                    int top_margin, char* text, int color, bool screen_refresh) {
    int text_position = 0;
    int buffer_position = 0;

    do {
        if (text[text_position] == '\n') {
            MessageManager_TextBuffer[buffer_position] = ' ';
            ++buffer_position;
            MessageManager_TextBuffer[buffer_position] = '\0';
            ++buffer_position;
        } else {
            MessageManager_TextBuffer[buffer_position] = text[text_position];
            ++buffer_position;
        }
    } while (text[text_position++] != '\0');

    MessageManager_TextBuffer[buffer_position] = '\0';

    MessageManager_DrawMessageBoxText(buffer, width, left_margin, top_margin, MessageManager_TextBuffer, color, false);

    if (screen_refresh) {
        win_draw_rect(window->id, &window->window);
    }
}

void MessageManager_LoadMessageLogs(SmartFileReader& file) {
    for (int i = 0; i < MESSAGE_MANAGER_TEAM_COUNT; + i) {
        MessageManager_TeamMessageLog[i].Clear();

        for (int count = file.ReadObjectCount(); count > 0; --count) {
            MessageManager_TeamMessageLog[i].PushBack(
                *dynamic_cast<MessageLogEntry*>(new (std::nothrow) MessageLogEntry(file)));
        }
    }
}

void MessageManager_SaveMessageLogs(SmartFileWriter& file) {
    for (int i = 0; i < MESSAGE_MANAGER_TEAM_COUNT; + i) {
        file.WriteObjectCount(MessageManager_TeamMessageLog[i].GetCount());

        for (SmartList<MessageLogEntry>::Iterator it = MessageManager_TeamMessageLog[i].Begin();
             it != MessageManager_TeamMessageLog[i].End(); ++it) {
            (*it).FileSave(file);
        }
    }
}

void MessageManager_ClearMessageLogs() {
    for (int i = 0; i < MESSAGE_MANAGER_TEAM_COUNT; + i) {
        MessageManager_TeamMessageLog[i].Clear();
    }
}

MessageLogEntry::MessageLogEntry(SmartFileReader& file) {
    unsigned short length;

    file.Read(length);
    text = new (std::nothrow) char[length];
    file.Read(text, length);
    unit = dynamic_cast<UnitInfo*>(file.ReadObject());
    file.Read(point);
    file.Read(field_20);
    file.Read(id);
}

MessageLogEntry::MessageLogEntry(char* text, ResourceID id) : id(id), text(strdup(text)), field_20(false) {}

MessageLogEntry::MessageLogEntry(char* text, UnitInfo* unit, Point point)
    : text(strdup(text)), unit(unit), point(point), field_20(true), id(INVALID_ID) {}

MessageLogEntry::~MessageLogEntry() { delete text; }

void MessageLogEntry::FileSave(SmartFileWriter& file) {
    unsigned short length = strlen(text);

    file.Write(length);
    file.Write(text, length);
    file.WriteObject(&*unit);
    file.Write(point);
    file.Write(field_20);
    file.Write(id);
}

char* MessageLogEntry::GetCstr() const { return text; }

void MessageLogEntry::MessageLogEntry_sub_B780B() {
    MessageManager_DrawMessage(text, 0, 0);

    if (field_20) {
        /// \todo Implement missing stuff
        if (unit != nullptr && unit->hits && unit->IsVisibleToTeam(GUI_PlayerTeamIndex)) {
            //            sub_9F637(*unit);
        } else {
            //            sub_A1620(1, point.x, point, y);
        }
    }
}