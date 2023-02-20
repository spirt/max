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

#include "menu.hpp"

#include <ctime>

#include "button.hpp"
#include "chooseplayermenu.hpp"
#include "clanselectmenu.hpp"
#include "cursor.hpp"
#include "desyncmenu.hpp"
#include "dialogmenu.hpp"
#include "game_manager.hpp"
#include "gameconfigmenu.hpp"
#include "gamesetupmenu.hpp"
#include "inifile.hpp"
#include "localization.hpp"
#include "movie.hpp"
#include "okcancelmenu.hpp"
#include "optionsmenu.hpp"
#include "planetselectmenu.hpp"
#include "remote.hpp"
#include "saveloadmenu.hpp"
#include "smartstring.hpp"
#include "sound_manager.hpp"
#include "text.hpp"
#include "units_manager.hpp"
#include "version.hpp"
#include "window_manager.hpp"
#include "winloss.hpp"

struct MenuButton {
    Button* button;
    char big_size;
    short ulx;
    short uly;
    const char* label;
    int r_value;
    ResourceID sfx;
};

#define MENU_BUTTON_DEF(is_big, ulx, uly, label, r_value, sfx) \
    { nullptr, (is_big), (ulx), (uly), (label), (r_value), (sfx) }

struct CreditsLine {
    unsigned short color;
    const char* text;
};

#define CREDITS_SEPARATOR \
    { (0x00), ("") }

#define CREDITS_TITLE(text) \
    { (0xFF), (text) }

#define CREDITS_TEXT(text) \
    { (0x04), (text) }

static void menu_draw_game_over_screen(WindowInfo* window, unsigned short* teams, int global_turn, bool mode);
static void menu_wrap_up_game(unsigned short* teams, int teams_in_play, int global_turn, bool mode);

static ResourceID menu_portrait_id;

static struct MenuButton* menu_button_items;
static int menu_button_items_count;
unsigned int menu_turn_timer_value;

static struct MenuButton main_menu_buttons[] = {
    MENU_BUTTON_DEF(true, 385, 175, _(28f9), GNW_KB_KEY_SHIFT_N, MBUTT0),
    MENU_BUTTON_DEF(true, 385, 210, _(dc41), GNW_KB_KEY_SHIFT_L, MBUTT0),
    MENU_BUTTON_DEF(true, 385, 245, _(8339), GNW_KB_KEY_SHIFT_M, MBUTT0),
    MENU_BUTTON_DEF(true, 385, 280, _(7013), GNW_KB_KEY_SHIFT_S, MBUTT0),
    MENU_BUTTON_DEF(true, 385, 315, _(b605), GNW_KB_KEY_SHIFT_I, MBUTT0),
    MENU_BUTTON_DEF(true, 385, 350, _(2a6b), GNW_KB_KEY_SHIFT_C, MBUTT0),
    MENU_BUTTON_DEF(false, 435, 420, _(d17d), GNW_KB_KEY_SHIFT_E, NDONE0),
    MENU_BUTTON_DEF(false, 16, 182, nullptr, GNW_KB_KEY_UP, KCARG0),
};

static struct MenuButton new_game_menu_buttons[] = {
    MENU_BUTTON_DEF(true, 385, 175, _(9b46), GNW_KB_KEY_SHIFT_T, MBUTT0),
    MENU_BUTTON_DEF(true, 385, 210, _(5d49), GNW_KB_KEY_SHIFT_S, MBUTT0),
    MENU_BUTTON_DEF(true, 385, 245, _(3d29), GNW_KB_KEY_SHIFT_U, MBUTT0),
    MENU_BUTTON_DEF(true, 385, 280, _(884f), GNW_KB_KEY_SHIFT_M, MBUTT0),
    MENU_BUTTON_DEF(true, 385, 315, _(385b), GNW_KB_KEY_SHIFT_A, MBUTT0),
    MENU_BUTTON_DEF(true, 385, 350, _(3838), GNW_KB_KEY_SHIFT_I, MBUTT0),
    MENU_BUTTON_DEF(false, 435, 420, _(1976), GNW_KB_KEY_SHIFT_C, NCANC0),
    MENU_BUTTON_DEF(false, 16, 182, nullptr, GNW_KB_KEY_UP, KCARG0),
};

static struct MenuButton network_game_menu_buttons[] = {
    MENU_BUTTON_DEF(true, 385, 175, _(c7a9), GNW_KB_KEY_SHIFT_H, MBUTT0),
    MENU_BUTTON_DEF(true, 385, 210, _(7064), GNW_KB_KEY_SHIFT_J, MBUTT0),
    MENU_BUTTON_DEF(true, 385, 280, _(f731), GNW_KB_KEY_SHIFT_O, MBUTT0),
    MENU_BUTTON_DEF(true, 385, 315, _(bf00), GNW_KB_KEY_SHIFT_T, MBUTT0),
    MENU_BUTTON_DEF(true, 385, 350, _(847e), GNW_KB_KEY_SHIFT_L, MBUTT0),
    MENU_BUTTON_DEF(false, 435, 420, _(0de3), GNW_KB_KEY_SHIFT_C, NCANC0),
    MENU_BUTTON_DEF(false, 16, 182, nullptr, GNW_KB_KEY_UP, KCARG0),
};

static const char* menu_tips_data;
static SmartString* menu_tips_strings;
static Button* menu_tips_button_up;
static Button* menu_tips_button_down;
static int menu_tips_max_row_count_per_page;
static int menu_tips_row_count;
static int menu_tips_current_row_index;

static const struct CreditsLine menu_credits_lines[] = {
    CREDITS_TITLE(_(aabe)),
    CREDITS_TEXT("Ali Atabek"),
    CREDITS_SEPARATOR,
    CREDITS_TITLE(_(84ee)),
    CREDITS_TEXT("Ali Atabek"),
    CREDITS_TEXT("Paul Kellner"),
    CREDITS_SEPARATOR,
    CREDITS_TITLE(_(8984)),
    CREDITS_TEXT("Ali Atabek"),
    CREDITS_TEXT("Paul Kellner"),
    CREDITS_TEXT("Gus Smedstad"),
    CREDITS_SEPARATOR,
    CREDITS_TITLE(_(aa55)),
    CREDITS_TEXT("Dave Boulanger"),
    CREDITS_SEPARATOR,
    CREDITS_TITLE(_(3c7e)),
    CREDITS_TITLE(_(24ef)),
    CREDITS_TEXT("Gus Smedstad"),
    CREDITS_SEPARATOR,
    CREDITS_TITLE(_(5fe6)),
    CREDITS_TEXT("Dave Boulanger"),
    CREDITS_TEXT("Bernie Weir"),
    CREDITS_SEPARATOR,
    CREDITS_TITLE(_(3215)),
    CREDITS_TEXT("Darren Monahan"),
    CREDITS_SEPARATOR,
    CREDITS_TITLE(_(38c1)),
    CREDITS_TEXT("Tony Postma"),
    CREDITS_TEXT("Arlene C. Somers"),
    CREDITS_SEPARATOR,
    CREDITS_TITLE(_(363f)),
    CREDITS_TEXT("Chris Regalado"),
    CREDITS_TEXT("Mark Bergo"),
    CREDITS_TEXT("Arlene C. Somers"),
    CREDITS_TEXT("Mike Dean"),
    CREDITS_SEPARATOR,
    CREDITS_TITLE(_(477a)),
    CREDITS_TEXT("Tony Postma"),
    CREDITS_SEPARATOR,
    CREDITS_TITLE(_(fff7)),
    CREDITS_TEXT("Cheryl Austin"),
    CREDITS_SEPARATOR,
    CREDITS_TITLE(_(47c6)),
    CREDITS_TEXT("Arlene C. Somers"),
    CREDITS_SEPARATOR,
    CREDITS_TITLE(_(9a25)),
    CREDITS_TEXT("Ali Atabek"),
    CREDITS_TEXT("Paul Kellner"),
    CREDITS_TEXT("Steve Perrin"),
    CREDITS_TEXT("Gus Smedstad"),
    CREDITS_SEPARATOR,
    CREDITS_TITLE(_(7ed6)),
    CREDITS_TEXT("Charles Deenen"),
    CREDITS_SEPARATOR,
    CREDITS_TITLE(_(0822)),
    CREDITS_TEXT("Steve Perrin"),
    CREDITS_SEPARATOR,
    CREDITS_TITLE(_(c0bb)),
    CREDITS_TEXT("Paul Kellner"),
    CREDITS_TEXT("Tony Postma"),
    CREDITS_TEXT("Amy Mitchell"),
    CREDITS_TEXT("Laura Mitchell"),
    CREDITS_SEPARATOR,
    CREDITS_TITLE(_(4a00)),
    CREDITS_TEXT("Kelly Newcomb"),
    CREDITS_SEPARATOR,
    CREDITS_TITLE(_(d200)),
    CREDITS_TEXT("Tony Postma"),
    CREDITS_SEPARATOR,
    CREDITS_TITLE(_(88c0)),
    CREDITS_TEXT("Chad Allison"),
    CREDITS_SEPARATOR,
    CREDITS_TITLE(_(f823)),
    CREDITS_TEXT("Colin Totman"),
    CREDITS_SEPARATOR,
    CREDITS_TITLE(_(796e)),
    CREDITS_TEXT("Cory Nelson"),
    CREDITS_SEPARATOR,
    CREDITS_TITLE(_(bf4a)),
    CREDITS_TEXT("Amy Mitchell"),
    CREDITS_TEXT("Chris Peak"),
    CREDITS_TEXT("Quinn Summers"),
    CREDITS_TEXT("Doug Avery"),
    CREDITS_TEXT("Steve McLafferty"),
    CREDITS_TEXT("Erick Lujan"),
    CREDITS_TEXT("Steve Victory"),
    CREDITS_TEXT("James Dunn"),
    CREDITS_TEXT("Henry Kahng"),
    CREDITS_TEXT("Bill Field"),
    CREDITS_TEXT("Steve Reed"),
    CREDITS_TEXT("John Stavros"),
    CREDITS_TEXT("Steve Baldoni"),
    CREDITS_TEXT("Richard Barker"),
    CREDITS_TEXT("Tony Bland"),
    CREDITS_TEXT("Larry Smith"),
    CREDITS_TEXT("Daniel Huffman"),
    CREDITS_TEXT("Arlen Nydam"),
    CREDITS_TEXT("Charles Crail"),
    CREDITS_TEXT("Rene Hakiki"),
    CREDITS_TEXT("Jon Atabek"),
    CREDITS_TEXT("Robert Wood"),
    CREDITS_SEPARATOR,
    CREDITS_TITLE(_(79e5)),
    CREDITS_TEXT("Bill Delk"),
    CREDITS_TEXT("Aaron J. Meyers"),
    CREDITS_SEPARATOR,
    CREDITS_TITLE(_(e3e3)),
    CREDITS_TEXT("John Werner"),
    CREDITS_SEPARATOR,
    CREDITS_TITLE(_(8433)),
    CREDITS_TEXT("Dan Forsyth"),
    CREDITS_TEXT("John Parker"),
    CREDITS_TEXT("Aaron Olaiz"),
    CREDITS_TEXT("Derek Gibbs"),
    CREDITS_TEXT("Phuong Nguyen"),
    CREDITS_TEXT("Marc Duran"),
    CREDITS_SEPARATOR,
    CREDITS_TITLE(_(d5e4)),
    CREDITS_TEXT("Paul Edelstein"),
    CREDITS_SEPARATOR,
    CREDITS_TITLE(_(25b0)),
    CREDITS_TEXT("Bill Stoudt"),
    CREDITS_SEPARATOR,
    CREDITS_TITLE(_(1d8d)),
    CREDITS_TEXT("Jim Veevaert"),
    CREDITS_SEPARATOR,
    CREDITS_TITLE(_(11dd)),
    CREDITS_TEXT("Dean Schulte"),
    CREDITS_SEPARATOR,
    CREDITS_TITLE(_(3a89)),
    CREDITS_TEXT("Julie Roether"),
    CREDITS_SEPARATOR,
    CREDITS_TITLE(_(e13c)),
    CREDITS_TEXT("Nicole Pelerine"),
    CREDITS_TEXT("Brian Cummings"),
    CREDITS_SEPARATOR,
    CREDITS_TITLE(_(f7fe)),
    CREDITS_TEXT("Charles Deenen"),
    CREDITS_SEPARATOR,
    CREDITS_TITLE(_(b3c3)),
    CREDITS_TEXT("Chris Borders"),
    CREDITS_SEPARATOR,
    CREDITS_TITLE(_(65d0)),
    CREDITS_TEXT("Craig Duman"),
    CREDITS_SEPARATOR,
    CREDITS_TITLE(_(85e2)),
    CREDITS_TEXT("Sergio Bustamante"),
    CREDITS_TEXT("Chris Borders"),
    CREDITS_TEXT("Craig Duman"),
    CREDITS_TEXT("Doug Rappaport"),
    CREDITS_SEPARATOR,
    CREDITS_TITLE(_(3c03)),
    CREDITS_TEXT("Brian Luzietti"),
    CREDITS_SEPARATOR,
    CREDITS_TITLE(_(afad)),
    CREDITS_TEXT("Rick Jackson"),
    CREDITS_SEPARATOR,
    CREDITS_TITLE(_(181c)),
    CREDITS_TEXT("Digital Brothers"),
    CREDITS_SEPARATOR,
    CREDITS_TITLE(_(02ff)),
    CREDITS_TEXT("Gregory G. Allen"),
    CREDITS_TEXT("Larry Peacock"),
    CREDITS_SEPARATOR,
    CREDITS_TITLE(_(5dab)),
    CREDITS_TEXT("Craig Duman"),
    CREDITS_SEPARATOR,
    CREDITS_TITLE(_(bec3)),
    CREDITS_TEXT("James Doyle"),
    CREDITS_TEXT("Apple's Animation"),
    CREDITS_SEPARATOR,
    CREDITS_TITLE(_(e725)),
    CREDITS_TEXT("Albert LIoyd Olson for Four Bars Entertainment"),
    CREDITS_SEPARATOR,
    CREDITS_TITLE(_(5c49)),
    CREDITS_TEXT("David Farmer"),
    CREDITS_TEXT("Harry Cohen"),
    CREDITS_TEXT("Jeffrey R. Whitcher"),
    CREDITS_TEXT("Elisabeth Flaum"),
    CREDITS_SEPARATOR,
    CREDITS_TITLE(_(6a6b)),
    CREDITS_TEXT("Ken Teaney"),
    CREDITS_TEXT("Mashall Garlington"),
    CREDITS_SEPARATOR,
    CREDITS_TITLE(_(9b23)),
    CREDITS_TEXT("Charles Deenen"),
    CREDITS_SEPARATOR,
    CREDITS_TITLE(_(f7ea)),
    CREDITS_TEXT("Doug Rappaport"),
    CREDITS_SEPARATOR,
    CREDITS_TITLE(_(3a41)),
    CREDITS_TEXT("Doug Rappaport"),
    CREDITS_TEXT("Sergio Bustamante"),
    CREDITS_SEPARATOR,
    CREDITS_TITLE(_(f813)),
    CREDITS_TITLE(_(11ae)),
    CREDITS_TITLE(_(06d1)),
    CREDITS_TITLE(_(b2a8)),
    CREDITS_SEPARATOR,
    CREDITS_SEPARATOR,
    CREDITS_SEPARATOR,
    CREDITS_SEPARATOR,
    CREDITS_TITLE(_(7a22)),
    CREDITS_TITLE(_(efb3)),
    CREDITS_TITLE(_(fda7)),
    CREDITS_TITLE(_(ab0a)),
    CREDITS_TITLE(_(163c)),
    CREDITS_TITLE(_(3ce2)),
    CREDITS_TITLE(_(d126)),
    CREDITS_TITLE(_(00a5)),
    CREDITS_TITLE(_(7bd6)),
    CREDITS_SEPARATOR,
    CREDITS_SEPARATOR,
    CREDITS_SEPARATOR,
};

const char* menu_planet_descriptions[] = {
    "This world is named for the shape of its only landmass. If participants on this world are placed too close "
    "together, a production strategy is unlikely to work.\nNumber of Participants: Two to three participants is "
    "preferable.\nGame Time: Games on this land mass can be very short unless the combatants are well separated.",

    "This area is likely to need a full deployment of land, sea, and air forces. A force starting on the same land "
    "mass as another might abandon their base camp and striking out for another land mass to start over.\nNumber of "
    "Participants: two to four can be easily accommodated.\nGame Time: Games in this area are likely to be long.",

    "These chunks of ice poking up out of the frozen sea are widely enough separated that participants should have "
    "plenty of time to build up naval and air forces to pursue their goals.\nNumber of Participants: two to four can "
    "be easily accommodated.\nGame Time: Games in this area are likely to be long.",

    "This single land mass with surrounding islands is so small that two participants starting on the mass makes "
    "immediate contact with the enemy very likely. Start on one of the outlying islands to gain plenty of time for "
    "force increase.\nNumber of Participants: Two to three participants is preferable.\nGame Time: Games in this area "
    "can be very short.",

    "Participants who land on one of the smaller land masses should have plenty of time to build production before "
    "encountering an opponent. Landing two on the same land mass will cause instant combat.\nNumber of Participants: "
    "two to four can be easily accommodated.\nGame Time: Games in this area are likely to be long.",

    "The nature of this land mass makes construction of water platforms mandatory for a successful colonization. The "
    "chance of a preemptive strike by an opponent is high, though not as high as from other single-land areas.\nNumber "
    "of Participants: Two to three participants is preferable.\nGame Time: Games in this area should be of medium to "
    "long length.",

    "A starting position on one of the outlying islands almost ensures a long time for buildup before contact is made "
    "with an enemy.\nNumber of Participants: two to four can be easily accommodated.\nGame Time: A long game unless "
    "the participants are all started in close proximity on the main continent.",

    "This archipelago of closely placed islands could be the scene of an entirely land and bridge based campaign, "
    "though sea and air assets would be useful.\nNumber of Participants: two to four can be easily accommodated.\nGame "
    "Time: Likely to be long unless there are only two participants and they both land on the same island.",

    "Only these few islands peak up from the omnipresent muddy seas of this world. The islands are sufficiently "
    "scattered that sea and air elements are necessary for any successful endeavor.\nNumber of Participants: two to "
    "four can be easily accommodated.\nGame Time: This is likely to be a long campaign.",

    "Named for the heart-shaped great lake in the center of the land mass, this world can be won by land and air "
    "forces alone, but the use of sea forces in the central lake could be crucial.\nNumber of Participants: Two to "
    "four can be easily accommodated.\nGame Time: This is likely to be a long campaign.",

    "The name of this world refers to the three lakes encompassed by the otherwise solid land mass of the world. There "
    "is a chance that a production-first strategy can run afoul of a preemptory strike by another participant.\nNumber "
    "of Participants: Two to three participants is preferable.\nGame Time: Probably short.",

    "This world has a lot of space and virtually every land mass has plenty of room for large armies. Depending on "
    "initial placements, the islands might see no activity at all. If every place is populated, expect intense "
    "seaborne combats.\nNumber of Participants: two to four can be easily accommodated.\nGame Time: Most games in this "
    "location will be long.",

    "This archipelago is tightly grouped in the middle of the planetary sea. There are opportunities for extensive air "
    "and sea resources, though an entirely land-and-air-based campaign could be successful.\nNumber of Participants: "
    "Two to three participants is preferable.\nGame Time: varies greatly depending on the landing points of the "
    "participants.",

    "The useful parts of this world are split apart by a central sea. Control of the central sea with seaborne assets "
    "will be essential unless the participants all land on the same continent.\nNumber of Participants: two to four "
    "can be easily accommodated.\nGame Time: will be long unless two participants land close together.",

    "This world is generally resourceless except for the region around the impact crater from a major asteroid strike. "
    "A combatant can win using just land and air forces. However, control of the inner sea could be important.\nNumber "
    "of Participants: two to four can be easily accommodated.\nGame Time: the game can be very long.",

    "This archipelago with a slice of mainland is suited to a balanced combined arm force with extensive resource "
    "building. Taking sanctuary from the incessant naval action on the slice of mainland is a legitimate tactic, of "
    "course.\nNumber of Participants: Two to three participants is preferable.\nGame Time: The game will probably be "
    "long.",

    "This archipelago is best suited to a concentration on sea borne forces. Extensive engineering will be necessary "
    "to create areas for proper exploitation of the planetary resources.\nNumber of Participants: two to four can be "
    "easily accommodated.\nGame Time: The necessary construction makes this a long game.",

    "The extensive land area on this planet makes it ideal for extensive land-based warfare. Sea borne assets may play "
    "a necessary but secondary role, depending on initial placement.\nNumber of Participants: two to four can be "
    "easily accommodated.\nGame Time: this is likely to be a long game.",

    "This planet gets its name from its appearance when seen from space. The mountains jutting out of the desert give "
    "it a decidedly freckled appearance. There might be extensive use of naval assets, or none.\nNumber of "
    "Participants: two to four can be easily accommodated.\nGame Time: Most games in this location will be long games.",

    "Very few lumps of sand poke out of the ocean on this planet. Its situation demands heavy use of water platforms "
    "and naval assets. Two participants are very unlikely to end up on the same land mass.\nNumber of Participants: "
    "Two to three participants is preferable.\nGame Time: Most games in this location will be long games.",

    "Like any other world where all the land is connected, this can be very risky for a high-production strategy. "
    "However, its size does give some protection against a preemptive strike by another participant.\nNumber of "
    "Participants: two to four can be easily accommodated.\nGame Time: medium to long unless participants' landing "
    "points are close.",

    "The sea passage that separates the two main land masses makes naval action likely here. Those who wish to follow "
    "a production strategy might land on the island to the north east.\nNumber of Participants: two to four can be "
    "easily accommodated.\nGame Time: this is likely to be a long game.",

    "The central island of this planet makes a natural battleground for all participants, whether they start there or "
    "not. Start on one of the corner lands t gain a reasonable amount of time for a strategic buildup.\nNumber of "
    "Participants: two to four can be easily accommodated.\nGame Time: Games on this world are likely to be very long.",

    "This world gets its name from the land bottleneck controllable by sea forces and the sea bottleneck controllable "
    "by land forces. Both are in the center of the map. Extensive use of all forces is likely in this "
    "location.\nNumber of Participants: two to four can be easily accommodated.\nGame Time: Most games on this world "
    "are likely to be very long."};

const char* menu_planet_names[] = {"Snowcrab",     "Frigia",       "Ice Berg",      "The Cooler", "Ultima Thule",
                                   "Long Floes",   "Iron Cross",   "Splatterscape", "Peak-a-boo", "Valentine's Planet",
                                   "Three Rings",  "Great divide", "New Luzon",     "Middle Sea", "High Impact",
                                   "Sanctuary",    "Islandia",     "Hammerhead",    "Freckles",   "Sandspit",
                                   "Great Circle", "Long Passage", "Flash Point",   "Bottleneck"};

static const char* save_file_extensions[] = {"dmo", "dbg", "txt", "sce", "mps"};

const char* menu_team_names[] = {"Red Team", "Green Team", "Blue Team", "Gray Team"};

static const ResourceID menu_briefing_backgrounds[] = {ENDGAME1, ENDGAME2, ENDGAME3, ENDGAME4, ENDGAME5,
                                                       ENDGAME6, ENDGAME7, ENDGAME8, ENDGAME9};

static const char* menu_game_over_screen_places[] = {"Eliminated", "1st place", "2nd place", "3rd place", "4th place"};

void draw_menu_title(WindowInfo* window, const char* caption) {
    text_font(GNW_TEXT_FONT_5);

    Text_TextBox(window->buffer, window->width, caption, WindowManager_ScaleUlx(window, 236),
                 WindowManager_ScaleUly(window, 145), 172, 15, COLOR_GREEN, true, true);
}

void menu_draw_menu_portrait_frame(WindowInfo* window) {
    WindowManager_LoadSimpleImage(BGRSCRNL, WindowManager_ScaleUlx(window, 6), WindowManager_ScaleUly(window, 173),
                                  false, window);
    WindowManager_LoadSimpleImage(BGRSCRNR, WindowManager_ScaleUlx(window, 166), WindowManager_ScaleUly(window, 173),
                                  false, window);
}

void menu_draw_menu_portrait(WindowInfo* window, ResourceID portrait, bool draw_to_screen) {
    menu_draw_menu_portrait_frame(window);

    if (portrait != menu_portrait_id || portrait == INVALID_ID) {
        while (portrait == INVALID_ID || portrait == menu_portrait_id || portrait == P_SHIELD || portrait == P_LIFESP ||
               portrait == P_RECCTR || portrait == P_MASTER || portrait == P_JUGGER || portrait == P_ALNTAN ||
               portrait == P_ALNASG || portrait == P_ALNPLA) {
            portrait = static_cast<ResourceID>(P_TRANSP + ((67 * dos_rand()) >> 15));
        }

        menu_portrait_id = portrait;
    }

    WindowInfo wininfo;

    wininfo.buffer = &window->buffer[WindowManager_ScaleOffset(window, 16, 182)];
    wininfo.width = window->width;
    wininfo.id = window->id;
    wininfo.window.ulx = WindowManager_ScaleUlx(window, 16);
    wininfo.window.uly = WindowManager_ScaleUly(window, 182);
    wininfo.window.lrx = wininfo.window.ulx + 300;
    wininfo.window.lry = wininfo.window.uly + 240;

    WindowManager_LoadBigImage(menu_portrait_id, &wininfo, wininfo.width, false, false);

    if (draw_to_screen) {
        win_draw_rect(wininfo.id, &wininfo.window);
    }
}

void menu_draw_game_over_screen(WindowInfo* window, unsigned short* teams, int global_turn, bool mode) {
    int ulx;
    int lrx;
    unsigned short visible_team;
    FontColor team_fonts[PLAYER_TEAM_MAX - 1] = {{165, 230, 199}, {165, 238, 199}, {165, 245, 199}, {165, 214, 199}};
    int victory_status;

    if (Remote_IsNetworkGame || mode) {
        Text_TextLine(window, "Game Over", 100, 10, 440, true, Fonts_BrightSilverColor);
    }

    ulx = 80;
    visible_team = PLAYER_TEAM_RED;

    for (int team = PLAYER_TEAM_RED; team < PLAYER_TEAM_MAX - 1; ++team) {
        if (UnitsManager_TeamInfo[team].team_type != TEAM_TYPE_NONE) {
            char team_name[40];
            ulx += 110;
            ++visible_team;
            lrx = ulx + 90;

            Text_TextLine(window, SmartString().Sprintf(3, "%i", visible_team).GetCStr(), ulx, 44, 90, true,
                          team_fonts[team]);

            ini_config.GetStringValue(static_cast<IniParameter>(INI_RED_TEAM_NAME + team), team_name,
                                      sizeof(team_name));

            Text_TextBox(window, team_name, ulx, 61, lrx - ulx, 55, true, true, Fonts_BrightSilverColor);
        }
    }

    win_draw(window->id);

    Text_TypeWriter_TextBox(window, "Points", 0, 116, 172, 1);

    ulx = 80;
    visible_team = PLAYER_TEAM_RED;

    victory_status = WinLoss_CheckWinConditions(PLAYER_TEAM_RED, global_turn);

    for (int team = PLAYER_TEAM_RED; team < PLAYER_TEAM_MAX - 1; ++team) {
        if (UnitsManager_TeamInfo[team].team_type != TEAM_TYPE_NONE) {
            ulx += 110;
            ++visible_team;
            lrx = ulx + 90;

            if (victory_status == VICTORY_STATE_GENERIC) {
                Text_TypeWriter_TextBox(
                    window, SmartString().Sprintf(12, "%i", UnitsManager_TeamInfo[team].team_points).GetCStr(), ulx,
                    116, lrx - ulx, 2);

                if (mode || teams[team] == 0) {
                    Text_TypeWriter_TextBox(window, menu_game_over_screen_places[teams[team]], ulx, 132, lrx - ulx, 2);
                }

            } else if (team == PLAYER_TEAM_RED) {
                Text_TypeWriter_TextBoxMultiLineWrapText(
                    window, (victory_status == VICTORY_STATE_WON) ? "Mission Success" : "Mission Failed", ulx, 116,
                    lrx - ulx, 34, 2);
            }
        }
    }

    Text_TypeWriter_TextBox(window, "Factories Built", 0, 166, 172, 1);

    ulx = 80;
    visible_team = PLAYER_TEAM_RED;

    for (int team = PLAYER_TEAM_RED; team < PLAYER_TEAM_MAX - 1; ++team) {
        if (UnitsManager_TeamInfo[team].team_type != TEAM_TYPE_NONE) {
            ulx += 110;
            ++visible_team;
            lrx = ulx + 90;

            Text_TypeWriter_TextBox(
                window, SmartString().Sprintf(12, "%i", UnitsManager_TeamInfo[team].stats_factories_built).GetCStr(),
                ulx, 166, lrx - ulx, 2);
        }
    }

    Text_TypeWriter_TextBox(window, "Mines Built", 0, 198, 172, 1);

    ulx = 80;
    visible_team = PLAYER_TEAM_RED;

    for (int team = PLAYER_TEAM_RED; team < PLAYER_TEAM_MAX - 1; ++team) {
        if (UnitsManager_TeamInfo[team].team_type != TEAM_TYPE_NONE) {
            ulx += 110;
            ++visible_team;
            lrx = ulx + 90;

            Text_TypeWriter_TextBox(
                window, SmartString().Sprintf(12, "%i", UnitsManager_TeamInfo[team].stats_mines_built).GetCStr(), ulx,
                198, lrx - ulx, 2);
        }
    }

    Text_TypeWriter_TextBox(window, "Buildings Built", 0, 230, 172, 1);

    ulx = 80;
    visible_team = PLAYER_TEAM_RED;

    for (int team = PLAYER_TEAM_RED; team < PLAYER_TEAM_MAX - 1; ++team) {
        if (UnitsManager_TeamInfo[team].team_type != TEAM_TYPE_NONE) {
            ulx += 110;
            ++visible_team;
            lrx = ulx + 90;

            Text_TypeWriter_TextBox(
                window, SmartString().Sprintf(12, "%i", UnitsManager_TeamInfo[team].stats_buildings_built).GetCStr(),
                ulx, 230, lrx - ulx, 2);
        }
    }

    Text_TypeWriter_TextBox(window, "Lost", 0, 246, 172, 1);

    ulx = 80;
    visible_team = PLAYER_TEAM_RED;

    for (int team = PLAYER_TEAM_RED; team < PLAYER_TEAM_MAX - 1; ++team) {
        if (UnitsManager_TeamInfo[team].team_type != TEAM_TYPE_NONE) {
            CTInfo* team_info;
            int casualties;

            ulx += 110;
            ++visible_team;
            lrx = ulx + 90;

            team_info = &UnitsManager_TeamInfo[team];
            casualties = 0;

            for (int j = 0; j < UNIT_END; ++j) {
                if (UnitsManager_BaseUnits[j].flags & BUILDING) {
                    casualties += team_info->casualties[j];
                }
            }

            Text_TypeWriter_TextBox(window, SmartString().Sprintf(12, "%i", casualties).GetCStr(), ulx, 246, lrx - ulx,
                                    2);
        }
    }

    Text_TypeWriter_TextBox(window, "Units Built", 0, 278, 172, 1);

    ulx = 80;
    visible_team = PLAYER_TEAM_RED;

    for (int team = PLAYER_TEAM_RED; team < PLAYER_TEAM_MAX - 1; ++team) {
        if (UnitsManager_TeamInfo[team].team_type != TEAM_TYPE_NONE) {
            ulx += 110;
            ++visible_team;
            lrx = ulx + 90;

            Text_TypeWriter_TextBox(
                window, SmartString().Sprintf(12, "%i", UnitsManager_TeamInfo[team].stats_units_built).GetCStr(), ulx,
                278, lrx - ulx, 2);
        }
    }

    Text_TypeWriter_TextBox(window, "Lost", 0, 294, 172, 1);

    ulx = 80;
    visible_team = PLAYER_TEAM_RED;

    for (int team = PLAYER_TEAM_RED; team < PLAYER_TEAM_MAX - 1; ++team) {
        if (UnitsManager_TeamInfo[team].team_type != TEAM_TYPE_NONE) {
            CTInfo* team_info;
            int casualties;

            ulx += 110;
            ++visible_team;
            lrx = ulx + 90;

            team_info = &UnitsManager_TeamInfo[team];
            casualties = 0;

            for (int j = 0; j < UNIT_END; ++j) {
                if (UnitsManager_BaseUnits[j].flags & SELECTABLE) {
                    casualties += team_info->casualties[j];
                }
            }

            Text_TypeWriter_TextBox(window, SmartString().Sprintf(12, "%i", casualties).GetCStr(), ulx, 294, lrx - ulx,
                                    2);
        }
    }

    Text_TypeWriter_TextBox(window, "Upgrades", 0, 326, 172, 1);

    ulx = 80;
    visible_team = PLAYER_TEAM_RED;

    for (int team = PLAYER_TEAM_RED; team < PLAYER_TEAM_MAX - 1; ++team) {
        if (UnitsManager_TeamInfo[team].team_type != TEAM_TYPE_NONE) {
            ulx += 110;
            ++visible_team;
            lrx = ulx + 90;

            Text_TypeWriter_TextBox(
                window,
                SmartString()
                    .Sprintf(12, "%i %s", UnitsManager_TeamInfo[team].stats_gold_spent_on_upgrades, "Gold")
                    .GetCStr(),
                ulx, 326, lrx - ulx, 2);
        }
    }

    {
        struct ImageSimpleHeader* image;

        image = reinterpret_cast<struct ImageSimpleHeader*>(ResourceManager_ReadResource(ENDARM));

        WindowManager_DecodeSimpleImage(image, 273, 480 - image->height, true, window);

        delete[] image;
    }
}

void menu_wrap_up_game(unsigned short* teams, int teams_in_play, int global_turn, bool mode) {
    int victory_status;
    bool is_winner;
    int bg_image_id;
    Color* palette;
    SmartString mission_briefing;

    victory_status = WinLoss_CheckWinConditions(PLAYER_TEAM_RED, global_turn);

    if (victory_status == VICTORY_STATE_GENERIC) {
        is_winner = teams[GameManager_PlayerTeam] == 1;

    } else {
        is_winner = victory_status == VICTORY_STATE_WON;
    }

    if (Remote_IsNetworkGame) {
        Remote_WaitBeginTurnAcknowledge();
        Remote_LeaveGame(GameManager_PlayerTeam, !mode);
    }

    bg_image_id = (dos_rand() * 9) >> 15;

    Text_TypeWriter_CharacterTimeMs = 50;

    palette = GameManager_MenuFadeOut();

    if (is_winner && ini_get_setting(INI_GAME_FILE_TYPE) == GAME_TYPE_CAMPAIGN) {
        FILE* fp;
        SmartString path(ResourceManager_FilePathText);
        path += SmartString().Sprintf(30, "win%i.cam", GameManager_GameFileNumber);

        fp = fopen(path.GetCStr(), "rt");

        if (fp) {
            int character;

            for (;;) {
                character = fgetc(fp);
                if (character == EOF) {
                    break;
                }

                mission_briefing += static_cast<char>(character);
            }

            fclose(fp);

            Text_TypeWriter_CharacterTimeMs = 10;
        }
    }

    {
        Window window(menu_briefing_backgrounds[bg_image_id]);
        WindowInfo window_info;
        unsigned short team_places[PLAYER_TEAM_MAX - 1];
        Button* button_end;
        bool exit_loop;
        int key;

        GameManager_WrapUpGame = true;
        GameManager_RequestMenuExit = false;

        Remote_UpdatePauseTimer = false;

        SoundManager.FreeAllSamples();

        GameManager_DeinitPopupButtons(false);

        window.SetFlags(0x10);

        text_font(GNW_TEXT_FONT_1);

        Cursor_SetCursor(CURSOR_HAND);

        window.SetPaletteMode(true);
        window.Add();
        window.FillWindowInfo(&window_info);

        for (int team = PLAYER_TEAM_RED; team < PLAYER_TEAM_MAX - 1; ++team) {
            team_places[team] = 0;
        }

        for (int i = 0; i < teams_in_play - 1; ++i) {
            for (int j = i + 1; j < teams_in_play; ++j) {
                if (WinLoss_DetermineWinner(teams[i], teams[j]) < 0) {
                    std::swap(teams[i], teams[j]);
                }
            }
        }

        for (int i = 0; i < teams_in_play; ++i) {
            team_places[teams[i]] = i + 1;
        }

        if (is_winner) {
            SoundManager.PlayVoice(V_M283, V_F283);
            SoundManager.PlayMusic(WINR_MSC, false);

        } else {
            SoundManager.PlayMusic(LOSE_MSC, false);
        }

        if (mission_briefing.GetLength() > 0) {
            win_draw(window_info.id);
            Text_TypeWriter_TextBoxMultiLineWrapText(&window_info, mission_briefing.GetCStr(), 20, 20, 600, 400, 0);

        } else {
            menu_draw_game_over_screen(&window_info, team_places, global_turn, mode);
        }

        text_font(GNW_TEXT_FONT_5);

        button_end = new (std::nothrow) Button(ENDOK_U, ENDOK_D, 293, 458);
        button_end->SetCaption("OK");

        text_font(GNW_TEXT_FONT_1);

        button_end->SetRValue(GNW_KB_KEY_ESCAPE);
        button_end->RegisterButton(window_info.id);

        win_draw(window_info.id);

        exit_loop = false;

        do {
            key = get_input();

            switch (key) {
                case GNW_KB_KEY_ESCAPE:
                case GNW_KB_KEY_RETURN: {
                    exit_loop = true;
                } break;

                case GNW_KB_KEY_SPACE: {
                    bg_image_id = (bg_image_id + 1) % 9;

                    WindowManager_LoadBigImage(menu_briefing_backgrounds[bg_image_id], &window_info, window_info.width,
                                               true, false, -1, -1, true);

                    if (mission_briefing.GetLength() > 0) {
                        win_draw(window_info.id);
                        Text_TypeWriter_TextBoxMultiLineWrapText(&window_info, mission_briefing.GetCStr(), 20, 20, 600,
                                                                 400, 0);

                    } else {
                        menu_draw_game_over_screen(&window_info, team_places, global_turn, mode);
                    }
                } break;
            }

            win_draw(window_info.id);

        } while (!exit_loop);

        delete button_end;
    }

    GameManager_LoadGame(0, palette, false);

    GameManager_GameState = GAME_STATE_3_MAIN_MENU;

    if (is_winner && ini_get_setting(INI_GAME_FILE_TYPE) == GAME_TYPE_CAMPAIGN) {
        ini_set_setting(INI_GAME_FILE_NUMBER, GameManager_GameFileNumber + 1);

        if (ini_get_setting(INI_LAST_CAMPAIGN) < GameManager_GameFileNumber + 1) {
            ini_set_setting(INI_LAST_CAMPAIGN, GameManager_GameFileNumber + 1);
        }

        ini_config.Save();
    }
}

bool menu_check_end_game_conditions(int global_turn, int local_turn, bool is_demo_mode) {
    int ini_victory_limit;
    int team_count;
    int teams_in_play;
    int human_teams_in_play;
    int non_computer_teams_count;
    unsigned short team_places[PLAYER_TEAM_MAX - 1];
    int victory_status;
    bool result;
    char game_state;
    bool is_network_game;

    ini_victory_limit = ini_setting_victory_limit;
    team_count = 0;
    teams_in_play = 0;
    human_teams_in_play = 0;
    non_computer_teams_count = 0;

    if (is_demo_mode && (global_turn - local_turn >= 5)) {
        GameManager_GameState = GAME_STATE_3_MAIN_MENU;
        result = true;

    } else {
        for (int team = PLAYER_TEAM_RED; team < PLAYER_TEAM_MAX - 1; ++team) {
            if (UnitsManager_TeamInfo[team].team_type != TEAM_TYPE_NONE) {
                ++team_count;

                if (UnitsManager_TeamInfo[team].team_type == TEAM_TYPE_COMPUTER) {
                    ++non_computer_teams_count;
                }

                if (WinLoss_CheckLossConditions(team) &&
                    UnitsManager_TeamInfo[team].team_type != TEAM_TYPE_ELIMINATED) {
                    if (UnitsManager_TeamInfo[team].team_type != TEAM_TYPE_COMPUTER) {
                        ++human_teams_in_play;
                    }

                    team_places[teams_in_play] = team;
                    ++teams_in_play;
                }
            }
        }

        victory_status = WinLoss_CheckWinConditions(PLAYER_TEAM_RED, global_turn);

        if (victory_status == VICTORY_STATE_WON || victory_status == VICTORY_STATE_LOST ||
            (victory_status != VICTORY_STATE_PENDING && teams_in_play == 1 && team_count > 1) || teams_in_play == 0 ||
            (human_teams_in_play == 0 && non_computer_teams_count > 0)) {
            menu_wrap_up_game(team_places, teams_in_play, global_turn, true);
            return true;

        } else if (ini_setting_victory_type == VICTORY_TYPE_DURATION) {
            if (global_turn == (ini_victory_limit - 10) && non_computer_teams_count > 0) {
                DialogMenu_Menu("Notice: Game will end in 10 turns!");

            } else if (ini_victory_limit <= global_turn) {
                menu_wrap_up_game(team_places, teams_in_play, global_turn, true);
                return true;
            }

        } else {
            for (int team = PLAYER_TEAM_RED; team < PLAYER_TEAM_MAX - 1; ++team) {
                if (UnitsManager_TeamInfo[team].team_type != TEAM_TYPE_NONE &&
                    UnitsManager_TeamInfo[team].team_points >= ini_victory_limit) {
                    menu_wrap_up_game(team_places, teams_in_play, global_turn, true);
                    return true;
                }
            }
        }

        if (victory_status == VICTORY_STATE_GENERIC) {
            for (int team = PLAYER_TEAM_RED; team < PLAYER_TEAM_MAX - 1; ++team) {
                if (UnitsManager_TeamInfo[team].team_type == TEAM_TYPE_PLAYER && !WinLoss_CheckLossConditions(team)) {
                    game_state = GameManager_GameState;
                    is_network_game = Remote_IsNetworkGame;

                    menu_wrap_up_game(team_places, teams_in_play, global_turn, false);

                    if (is_network_game) {
                        return true;

                    } else {
                        GameManager_GameState = game_state;
                        UnitsManager_TeamInfo[team].team_type = TEAM_TYPE_ELIMINATED;
                    }
                }
            }
        }

        result = false;
    }

    return result;
}

void menu_draw_menu_title(WindowInfo* window, MenuTitleItem* menu_item, int color, bool horizontal_align,
                          bool vertical_align) {
    if (menu_item->title && strlen(menu_item->title)) {
        Text_TextBox(
            window->buffer, window->width, menu_item->title, WindowManager_ScaleUlx(window, menu_item->bounds.ulx),
            WindowManager_ScaleUly(window, menu_item->bounds.uly), menu_item->bounds.lrx - menu_item->bounds.ulx,
            menu_item->bounds.lry - menu_item->bounds.uly, color, horizontal_align, vertical_align);
    }
}

void menu_draw_logo(ResourceID resource_id, int time_limit) {
    WindowInfo* window = WindowManager_GetWindow(WINDOW_MAIN_WINDOW);
    unsigned int time_stamp;

    if (WindowManager_LoadBigImage(resource_id, window, window->width, true, false, -1, -1, true, true)) {
        Cursor_SetCursor(CURSOR_HIDDEN);
        mouse_show();
        setSystemPalette(WindowManager_SystemPalette);
        win_draw(window->id);
        WindowManager_FadeIn(500);

        time_stamp = timer_get_stamp32();
        while (timer_elapsed_time_ms(time_stamp) < time_limit && get_input() == -1) {
        }

        WindowManager_ClearWindow();
    }
}

template <typename T>
void ReadFile(FILE* fp, T& buffer) {
    if (fread(&buffer, sizeof(char), sizeof(T), fp) != (sizeof(T))) {
        ResourceManager_ExitGame(EXIT_CODE_CANNOT_READ_RES_FILE);
    }
}

template <typename T>
void ReadFile(FILE* fp, T* buffer, int size) {
    if (fread(buffer, sizeof(char), size, fp) != size) {
        ResourceManager_ExitGame(EXIT_CODE_CANNOT_READ_RES_FILE);
    }
}

int Menu_LoadPlanetMinimap(int planet_index, unsigned char* buffer, int width) {
    char* filename;
    int result;

    filename = reinterpret_cast<char*>(ResourceManager_ReadResource(static_cast<ResourceID>(SNOW_1 + planet_index)));

    ResourceManager_ToUpperCase(filename);

    if (filename) {
        FILE* fp;

        fp = fopen(filename, "rb");
        delete[] filename;

        if (fp) {
            char map_type[5];
            Point map_dimensions;
            short map_tile_count;
            Color palette[3 * PALETTE_SIZE];

            ReadFile(fp, map_type);
            ReadFile(fp, map_dimensions);

            for (int i = 0; i < map_dimensions.x; ++i) {
                ReadFile(fp, &buffer[width * i], map_dimensions.y);
            }

            fseek(fp, map_dimensions.x * map_dimensions.y * 2, SEEK_CUR);

            ReadFile(fp, map_tile_count);
            fseek(fp, map_tile_count * 64 * 64, SEEK_CUR);

            ReadFile(fp, palette);

            for (int i = 0; i < sizeof(palette); ++i) {
                palette[i] /= 4;
            }

            WindowManager_ColorPalette = getColorPalette();

            for (int i = 0; i < sizeof(palette); i += 3) {
                palette[i / 3] =
                    ResourceManager_FindClosestPaletteColor(palette[i], palette[i + 1], palette[i + 2], true);
            }

            for (int i = 0; i < map_dimensions.x; ++i) {
                for (int j = 0; j < map_dimensions.y; ++j) {
                    buffer[i * width + j] = palette[buffer[i * width + j]];
                }
            }

            fclose(fp);
            result = true;

        } else {
            result = false;
        }
    } else {
        result = false;
    }

    return result;
}

void menu_draw_campaign_mission_briefing_screen() {
    int image_index;
    FILE* fp;
    SmartString filepath(ResourceManager_FilePathText);
    SmartString filename;
    SmartString text;
    WindowInfo window;

    image_index = (dos_rand() * 9) >> 15;

    Text_TypeWriter_CharacterTimeMs = 10;

    filename.Sprintf(30, "intro%i.cam", GameManager_GameFileNumber);

    filename.Toupper();

    filepath += filename;

    fp = fopen(filepath.GetCStr(), "rt");

    if (fp) {
        for (;;) {
            int character = fgetc(fp);

            if (character == EOF) {
                break;
            }

            text += character;
        }

        fclose(fp);

        Window briefing_window(menu_briefing_backgrounds[image_index]);
        Button* button_end_ok;
        bool exit_loop;

        briefing_window.SetFlags(0x10);
        Cursor_SetCursor(CURSOR_HAND);
        briefing_window.SetPaletteMode(true);
        briefing_window.Add();
        briefing_window.FillWindowInfo(&window);

        win_draw(window.id);
        text_font(GNW_TEXT_FONT_1);

        Text_TypeWriter_TextBoxMultiLineWrapText(&window, text.GetCStr(), 20, 20, 600, 400, 0);
        Text_TypeWriter_CharacterTimeMs = 0;

        text_font(GNW_TEXT_FONT_5);
        button_end_ok = new (std::nothrow) Button(ENDOK_U, ENDOK_D, 293, 458);
        button_end_ok->SetCaption("OK");

        text_font(GNW_TEXT_FONT_1);
        button_end_ok->SetRValue(GNW_KB_KEY_ESCAPE);
        button_end_ok->RegisterButton(window.id);

        win_draw(window.id);

        exit_loop = false;

        do {
            int key;

            key = get_input();

            switch (key) {
                case GNW_KB_KEY_RETURN:
                case GNW_KB_KEY_ESCAPE: {
                    exit_loop = true;
                } break;

                case GNW_KB_KEY_SPACE: {
                    image_index = (image_index + 1) % 9;

                    WindowManager_LoadBigImage(menu_briefing_backgrounds[image_index], &window, window.width, true,
                                               false, -1, -1, true);

                    text_font(GNW_TEXT_FONT_1);

                    Text_TypeWriter_TextBoxMultiLineWrapText(&window, text.GetCStr(), 20, 20, 600, 400, 0);
                    win_draw(window.id);
                } break;
            }

        } while (!exit_loop);

        delete button_end_ok;
    }
}

void menu_update_resource_levels() {
    int resource_min;
    int resource_max;
    int resource_raw;
    int resource_fuel;
    int resource_gold;
    int resource_derelicts;

    resource_raw = ini_get_setting(INI_RAW_RESOURCE);
    resource_fuel = ini_get_setting(INI_FUEL_RESOURCE);
    resource_gold = ini_get_setting(INI_GOLD_RESOURCE);
    resource_derelicts = ini_get_setting(INI_ALIEN_DERELICTS);

    resource_min = 1;
    resource_max = 15;

    switch (resource_raw) {
        case 0: {
            ini_set_setting(INI_RAW_NORMAL_LOW, 0);
            ini_set_setting(INI_RAW_NORMAL_HIGH, 3);
            ini_set_setting(INI_RAW_CONCENTRATE_LOW, 8);
            ini_set_setting(INI_RAW_CONCENTRATE_HIGH, 12);
            ini_set_setting(INI_RAW_CONCENTRATE_SEPERATION, 28);
            ini_set_setting(INI_RAW_CONCENTRATE_DIFFUSION, 6);

            resource_min = 4;
            resource_max = 16;
        } break;

        case 1: {
            ini_set_setting(INI_RAW_NORMAL_LOW, 0);
            ini_set_setting(INI_RAW_NORMAL_HIGH, 5);
            ini_set_setting(INI_RAW_CONCENTRATE_LOW, 13);
            ini_set_setting(INI_RAW_CONCENTRATE_HIGH, 16);
            ini_set_setting(INI_RAW_CONCENTRATE_SEPERATION, 23);
            ini_set_setting(INI_RAW_CONCENTRATE_DIFFUSION, 5);

            resource_min = 6;
            resource_max = 17;
        } break;

        case 2: {
            ini_set_setting(INI_RAW_NORMAL_LOW, 1);
            ini_set_setting(INI_RAW_NORMAL_HIGH, 5);
            ini_set_setting(INI_RAW_CONCENTRATE_LOW, 16);
            ini_set_setting(INI_RAW_CONCENTRATE_HIGH, 16);
            ini_set_setting(INI_RAW_CONCENTRATE_SEPERATION, 19);
            ini_set_setting(INI_RAW_CONCENTRATE_DIFFUSION, 4);

            resource_min = 7;
            resource_max = 18;
        } break;
    }

    switch (resource_fuel) {
        case 0: {
            ini_set_setting(INI_FUEL_NORMAL_LOW, 1);
            ini_set_setting(INI_FUEL_NORMAL_HIGH, 2);
            ini_set_setting(INI_FUEL_CONCENTRATE_LOW, 8);
            ini_set_setting(INI_FUEL_CONCENTRATE_HIGH, 12);
            ini_set_setting(INI_FUEL_CONCENTRATE_SEPERATION, 29);
            ini_set_setting(INI_FUEL_CONCENTRATE_DIFFUSION, 6);

            resource_min += 2;
            resource_max += 1;
        } break;

        case 1: {
            ini_set_setting(INI_FUEL_NORMAL_LOW, 2);
            ini_set_setting(INI_FUEL_NORMAL_HIGH, 3);
            ini_set_setting(INI_FUEL_CONCENTRATE_LOW, 12);
            ini_set_setting(INI_FUEL_CONCENTRATE_HIGH, 16);
            ini_set_setting(INI_FUEL_CONCENTRATE_SEPERATION, 24);
            ini_set_setting(INI_FUEL_CONCENTRATE_DIFFUSION, 5);

            resource_min += 3;
            resource_max += 2;
        } break;

        case 2: {
            ini_set_setting(INI_FUEL_NORMAL_LOW, 2);
            ini_set_setting(INI_FUEL_NORMAL_HIGH, 4);
            ini_set_setting(INI_FUEL_CONCENTRATE_LOW, 16);
            ini_set_setting(INI_FUEL_CONCENTRATE_HIGH, 16);
            ini_set_setting(INI_FUEL_CONCENTRATE_SEPERATION, 20);
            ini_set_setting(INI_FUEL_CONCENTRATE_DIFFUSION, 4);

            resource_min += 4;
            resource_max += 3;
        } break;
    }

    switch (resource_raw + resource_fuel) {
        case 0: {
            ini_set_setting(INI_MIXED_RESOURCE_SEPERATION, 49);
        } break;

        case 1: {
            ini_set_setting(INI_MIXED_RESOURCE_SEPERATION, 44);
        } break;

        case 2: {
            ini_set_setting(INI_MIXED_RESOURCE_SEPERATION, 40);
        } break;

        case 3: {
            ini_set_setting(INI_MIXED_RESOURCE_SEPERATION, 36);
        } break;

        case 4: {
            ini_set_setting(INI_MIXED_RESOURCE_SEPERATION, 33);
        } break;
    }

    switch (resource_gold) {
        case 0: {
            ini_set_setting(INI_GOLD_NORMAL_LOW, 0);
            ini_set_setting(INI_GOLD_NORMAL_HIGH, 0);
            ini_set_setting(INI_GOLD_CONCENTRATE_LOW, 5);
            ini_set_setting(INI_GOLD_CONCENTRATE_HIGH, 9);
            ini_set_setting(INI_GOLD_CONCENTRATE_SEPERATION, 39);
            ini_set_setting(INI_GOLD_CONCENTRATE_DIFFUSION, 6);

            resource_min += 0;
            resource_max += 0;
        } break;

        case 1: {
            ini_set_setting(INI_GOLD_NORMAL_LOW, 0);
            ini_set_setting(INI_GOLD_NORMAL_HIGH, 0);
            ini_set_setting(INI_GOLD_CONCENTRATE_LOW, 8);
            ini_set_setting(INI_GOLD_CONCENTRATE_HIGH, 12);
            ini_set_setting(INI_GOLD_CONCENTRATE_SEPERATION, 32);
            ini_set_setting(INI_GOLD_CONCENTRATE_DIFFUSION, 5);

            resource_min += 0;
            resource_max += 1;
        } break;

        case 2: {
            ini_set_setting(INI_GOLD_NORMAL_LOW, 0);
            ini_set_setting(INI_GOLD_NORMAL_HIGH, 1);
            ini_set_setting(INI_GOLD_CONCENTRATE_LOW, 12);
            ini_set_setting(INI_GOLD_CONCENTRATE_HIGH, 16);
            ini_set_setting(INI_GOLD_CONCENTRATE_SEPERATION, 26);
            ini_set_setting(INI_GOLD_CONCENTRATE_DIFFUSION, 4);

            resource_min += 1;
            resource_max += 2;
        } break;
    }

    ini_set_setting(INI_MIN_RESOURCES, resource_min);
    ini_set_setting(INI_MAX_RESOURCES, resource_max);

    switch (resource_derelicts) {
        case 0: {
            ini_set_setting(INI_ALIEN_SEPERATION, 0);
            ini_set_setting(INI_ALIEN_UNIT_VALUE, 0);
        } break;

        case 1: {
            ini_set_setting(INI_ALIEN_SEPERATION, 65);
            ini_set_setting(INI_ALIEN_UNIT_VALUE, 20);
        } break;

        case 2: {
            ini_set_setting(INI_ALIEN_SEPERATION, 50);
            ini_set_setting(INI_ALIEN_UNIT_VALUE, 30);
        } break;
    }
}

void draw_copyright_label(WindowInfo* window) {
    Rect bounds;

    bounds.ulx = WindowManager_ScaleUlx(window, 10);
    bounds.uly = WindowManager_ScaleUly(window, 469);
    bounds.lrx = bounds.ulx + 620;
    bounds.lry = bounds.uly + 10;

    text_font(GNW_TEXT_FONT_5);

    Text_TextBox(window->buffer, window->width,
                 "Copyright 1996 Interplay Productions. v1.04"
                 "  (M.A.X. Port " GAME_VERSION ")",
                 bounds.ulx, bounds.uly, bounds.lrx - bounds.ulx, bounds.lry - bounds.uly, COLOR_BLACK, true, false);
}

void menu_draw_main_menu_buttons(MenuButton* button_items, int button_count, int special_button_id = 0) {
    WindowInfo* window = WindowManager_GetWindow(WINDOW_MAIN_WINDOW);

    menu_button_items = button_items;
    menu_button_items_count = button_count;

    text_font(GNW_TEXT_FONT_1);

    for (int i = 0; i < button_count; ++i) {
        ResourceID up;
        ResourceID down;

        if (button_items[i].big_size) {
            up = BLANK_UP;
            down = BLANK_DN;

        } else {
            up = SBLNK_UP;
            down = SBLNK_DN;
        }

        if (button_items[i].label) {
            button_items[i].button =
                new (std::nothrow) Button(up, down, WindowManager_ScaleUlx(window, button_items[i].ulx),
                                          WindowManager_ScaleUly(window, button_items[i].uly));
            button_items[i].button->SetCaption(button_items[i].label);

        } else {
            button_items[i].button =
                new (std::nothrow) Button(WindowManager_ScaleUlx(window, button_items[i].ulx),
                                          WindowManager_ScaleUly(window, button_items[i].uly), 300, 240);
        }

        button_items[i].button->SetRValue(button_items[i].r_value);
        button_items[i].button->SetPValue(GNW_INPUT_PRESS + i);
        button_items[i].button->SetSfx(button_items[i].sfx);

        if (special_button_id) {
            if (special_button_id == i) {
                button_items[i].button->SetFlags(1);
                button_items[i].button->SetPValue(button_items[i].r_value);
            }
        }

        button_items[i].button->RegisterButton(window->id);
        button_items[i].button->Enable();
    }

    win_draw(window->id);
    mouse_show();
}

void menu_draw_tips_frame(WindowInfo* window) {
    if (menu_tips_strings) {
        Rect bounds;
        unsigned char* buffer_position;
        int row_index_limit;

        menu_draw_menu_portrait_frame(window);

        bounds.ulx = 19;
        bounds.uly = 185;
        bounds.lrx = 315;
        bounds.lry = 421;

        buffer_position = &window->buffer[window->width * bounds.uly + bounds.ulx];
        row_index_limit = menu_tips_current_row_index + menu_tips_max_row_count_per_page;

        if (row_index_limit > menu_tips_row_count) {
            row_index_limit = menu_tips_row_count;
        }

        text_font(GNW_TEXT_FONT_5);

        for (int i = menu_tips_current_row_index; i < row_index_limit; ++i) {
            text_to_buf(&buffer_position[(i - menu_tips_current_row_index) * text_height() * window->width],
                        menu_tips_strings[i].GetCStr(), 296, window->width, 0xA2);
        }

        win_draw_rect(window->id, &bounds);
    }
}

void menu_draw_tips(WindowInfo* window) {
    text_font(GNW_TEXT_FONT_5);
    menu_tips_data = reinterpret_cast<char*>(ResourceManager_ReadResource(TIPS));

    menu_tips_max_row_count_per_page = 236 / text_height();

    menu_tips_strings =
        Text_SplitText(menu_tips_data, menu_tips_max_row_count_per_page * 100, 296, &menu_tips_row_count);

    menu_tips_current_row_index = 0;

    menu_tips_button_up = new (std::nothrow) Button(MNUUAROU, MNUUAROD, 16, 438);
    menu_tips_button_up->SetRValue(1000);
    menu_tips_button_up->SetPValue(GNW_INPUT_PRESS + 1000);
    menu_tips_button_up->SetSfx(KCARG0);
    menu_tips_button_up->RegisterButton(window->id);

    menu_tips_button_down = new (std::nothrow) Button(MNUDAROU, MNUDAROD, 48, 438);
    menu_tips_button_down->SetRValue(1001);
    menu_tips_button_down->SetPValue(GNW_INPUT_PRESS + 1001);
    menu_tips_button_down->RegisterButton(window->id);

    menu_draw_tips_frame(window);
    win_draw(window->id);
}

void menu_delete_tips() {
    delete menu_tips_data;
    menu_tips_data = nullptr;

    delete[] menu_tips_strings;
    menu_tips_strings = nullptr;

    delete menu_tips_button_up;
    menu_tips_button_up = nullptr;

    delete menu_tips_button_down;
    menu_tips_button_down = nullptr;
}

void tips_on_click_up(WindowInfo* window) {
    if (menu_tips_current_row_index) {
        int page_offset;
        unsigned int time_stamp;

        page_offset = menu_tips_current_row_index - menu_tips_max_row_count_per_page;

        if (page_offset < 0) {
            page_offset = 0;
        }

        do {
            time_stamp = timer_get_stamp32();
            --menu_tips_current_row_index;
            menu_draw_tips_frame(window);

            while ((timer_get_stamp32() - time_stamp) < TIMER_FPS_TO_TICKS(96)) {
            }
        } while (menu_tips_current_row_index != page_offset);
    }
}

void tips_on_click_down(WindowInfo* window) {
    int page_offset;
    unsigned int time_stamp;

    page_offset = menu_tips_current_row_index + menu_tips_max_row_count_per_page;

    if (page_offset < menu_tips_row_count) {
        do {
            time_stamp = timer_get_stamp32();
            ++menu_tips_current_row_index;
            menu_draw_tips_frame(window);

            while ((timer_get_stamp32() - time_stamp) < TIMER_FPS_TO_TICKS(96)) {
            }
        } while (menu_tips_current_row_index != page_offset);
    }
}

void menu_delete_menu_buttons() {
    if (menu_button_items) {
        for (int i = 0; i < menu_button_items_count; ++i) {
            if (menu_button_items[i].button) {
                delete menu_button_items[i].button;
            }
        }

        menu_button_items_count = -1;
        menu_button_items = nullptr;
        menu_delete_tips();
    }
}

int play_attract_demo(int save_slot) {
    char filename[20];
    FILE* fp;
    int result;

    sprintf(filename, "save%i.%s", save_slot, save_file_extensions[0]);

    ResourceManager_ToUpperCase(filename);

    fp = fopen(filename, "rb");

    if (fp) {
        int backup_opponent;
        int backup_timer;
        int backup_endturn;
        int backup_play_mode;
        int backup_start_gold;
        int backup_raw_resource;
        int backup_fuel_resource;
        int backup_gold_resource;
        int backup_alien_derelicts;

        char backup_player_name[30];
        char backup_red_team_name[30];
        char backup_green_team_name[30];
        char backup_blue_team_name[30];
        char backup_gray_team_name[30];

        fclose(fp);

        backup_opponent = ini_get_setting(INI_OPPONENT);
        backup_timer = ini_get_setting(INI_TIMER);
        backup_endturn = ini_get_setting(INI_ENDTURN);
        backup_play_mode = ini_get_setting(INI_PLAY_MODE);
        backup_start_gold = ini_get_setting(INI_START_GOLD);
        backup_raw_resource = ini_get_setting(INI_RAW_RESOURCE);
        backup_fuel_resource = ini_get_setting(INI_FUEL_RESOURCE);
        backup_gold_resource = ini_get_setting(INI_GOLD_RESOURCE);
        backup_alien_derelicts = ini_get_setting(INI_ALIEN_DERELICTS);

        ini_config.GetStringValue(INI_PLAYER_NAME, backup_player_name, 30);
        ini_config.GetStringValue(INI_RED_TEAM_NAME, backup_red_team_name, 30);
        ini_config.GetStringValue(INI_GREEN_TEAM_NAME, backup_green_team_name, 30);
        ini_config.GetStringValue(INI_BLUE_TEAM_NAME, backup_blue_team_name, 30);
        ini_config.GetStringValue(INI_GRAY_TEAM_NAME, backup_gray_team_name, 30);

        ini_set_setting(INI_GAME_FILE_NUMBER, save_slot);
        ini_set_setting(INI_GAME_FILE_TYPE, GAME_TYPE_DEMO);

        GameManager_GameLoop(GAME_STATE_10);

        ini_set_setting(INI_OPPONENT, backup_opponent);
        ini_set_setting(INI_TIMER, backup_timer);
        ini_set_setting(INI_ENDTURN, backup_endturn);
        ini_set_setting(INI_PLAY_MODE, backup_play_mode);
        ini_set_setting(INI_START_GOLD, backup_start_gold);
        ini_set_setting(INI_RAW_RESOURCE, backup_raw_resource);
        ini_set_setting(INI_FUEL_RESOURCE, backup_fuel_resource);
        ini_set_setting(INI_GOLD_RESOURCE, backup_gold_resource);
        ini_set_setting(INI_ALIEN_DERELICTS, backup_alien_derelicts);

        ini_config.SetStringValue(INI_PLAYER_NAME, backup_player_name);
        ini_config.SetStringValue(INI_RED_TEAM_NAME, backup_red_team_name);
        ini_config.SetStringValue(INI_GREEN_TEAM_NAME, backup_green_team_name);
        ini_config.SetStringValue(INI_BLUE_TEAM_NAME, backup_blue_team_name);
        ini_config.SetStringValue(INI_GRAY_TEAM_NAME, backup_gray_team_name);

        result = 1;

    } else {
        result = 0;
    }

    return result;
}

void menu_disable_menu_buttons() {
    if (menu_button_items) {
        for (int i = 0; i < menu_button_items_count; ++i) {
            menu_button_items[i].button->Disable();
        }
    }
}

void menu_enable_menu_buttons() {
    if (menu_button_items) {
        for (int i = 0; i < menu_button_items_count; ++i) {
            menu_button_items[i].button->Enable();
        }
    }
}

void menu_credits_menu_loop() {
    WindowInfo* window;
    Image* image1;
    Image* image2;
    Rect bounds;
    int window_width;
    int window_height;
    bool play;
    int height_offset;
    int line_index;
    unsigned char* image_buffer_position;
    unsigned char* window_buffer_position;
    unsigned int time_stamp;

    window = WindowManager_GetWindow(WINDOW_MAIN_WINDOW);
    Cursor_SetCursor(CURSOR_HIDDEN);
    WindowManager_LoadBigImage(CREDITS, window, window->width, true, false, -1, -1, true, true);
    win_draw(window->id);

    window_width = WindowManager_ScaleUlx(window, 450);
    window_height = WindowManager_ScaleUly(window, 230);

    bounds.ulx = (WindowManager_GetWidth(window) - window_width) / 2;
    bounds.uly = (WindowManager_GetHeight(window) - window_height) / 2;
    bounds.lrx = bounds.ulx + window_width;
    bounds.lry = bounds.uly + window_height;

    image1 = new (std::nothrow) Image(bounds.ulx, bounds.uly, bounds.lrx, bounds.lry);
    image2 = new (std::nothrow) Image(bounds.ulx, bounds.uly, window_width, window_height + 18);

    image1->Copy(window);
    memset(image2->GetData(), -128, (window_height + 18) * window_width);

    text_font(GNW_TEXT_FONT_1);

    play = true;
    line_index = 0;
    height_offset = bounds.lry;

    while (play) {
        image1->Write(window);
        memmove(image2->GetData(), &image2->GetData()[window_width], (window_height + 17) * window_width);
        memset(&image2->GetData()[(window_height + 17) * window_width], 0x80, window_width);

        --height_offset;

        if (line_index < (sizeof(menu_credits_lines) / sizeof(struct CreditsLine)) && height_offset <= bounds.lry) {
            Text_TextBox(image2->GetData(), window_width, menu_credits_lines[line_index].text, 0, window_height,
                         window_width, 0x12, menu_credits_lines[line_index].color | GNW_TEXT_OUTLINE, true, true);
            ++line_index;
            height_offset = bounds.lry + 20;
        }

        image_buffer_position = image2->GetData();
        window_buffer_position = &window->buffer[window->width * bounds.uly + bounds.ulx];

        for (int i = 0; i < window_height; ++i) {
            for (int j = 0; j < window_width; ++j) {
                if (image_buffer_position[j] != 0x80) {
                    window_buffer_position[j] = image_buffer_position[j];
                }
            }

            image_buffer_position += window_width;
            window_buffer_position += window->width;
        }

        win_draw_rect(window->id, &bounds);

        time_stamp = timer_get_stamp32();
        while (timer_elapsed_time_ms(time_stamp) < 10) {
            if (get_input() != -1) {
                play = 0;
            }
        }

        if (height_offset <= bounds.uly) {
            play = 0;
        }
    }

    delete image1;
    delete image2;
}

int menu_clan_select_menu_loop(int team) {
    ClanSelectMenu clan_select_menu;
    int result;
    bool event_release;

    event_release = false;
    clan_select_menu.Init(team);

    do {
        if (Remote_GameState) {
            Remote_NetSync();
        }

        if (Remote_GameState == 2) {
            break;
        }

        clan_select_menu.key = get_input();

        if (clan_select_menu.key > 0 && clan_select_menu.key < GNW_INPUT_PRESS) {
            event_release = false;
        }

        for (int i = 0; i < CLAN_SELECT_MENU_ITEM_COUNT; ++i) {
            if (clan_select_menu.buttons[i]) {
                if (clan_select_menu.key == GNW_INPUT_PRESS + i) {
                    if (!event_release) {
                        clan_select_menu.buttons[i]->PlaySound();
                    }

                    event_release = true;
                    break;
                }

                if (clan_select_menu.key == clan_select_menu.menu_item[i].event_code) {
                    clan_select_menu.key = clan_select_menu.menu_item[i].r_value;
                }

                if (clan_select_menu.key == clan_select_menu.menu_item[i].r_value) {
                    if (i < 8) {
                        clan_select_menu.buttons[i]->PlaySound();
                    }

                    clan_select_menu.key -= 1000;
                    (clan_select_menu.*clan_select_menu.menu_item[i].event_handler)();
                    break;
                }
            }
        }

    } while (!clan_select_menu.event_click_done_cancel_random);

    clan_select_menu.Deinit();

    ini_set_setting(clan_select_menu.team_clan_ini_id, clan_select_menu.team_clan);

    UnitsManager_TeamInfo[team].team_clan = clan_select_menu.team_clan;
    result = clan_select_menu.team_clan;

    return result;
}

void DialogMenu_Menu(const char* label) {
    menu_turn_timer_value -= (timer_get_stamp32() - Remote_PauseTimeStamp) / 1193180;

    {
        DialogMenu dialog_menu(label, true);

        dialog_menu.RunMenu();

        if (Remote_IsNetworkGame) {
            Remote_SendNetPacket_Signal(40, GameManager_PlayerTeam, 0);
        }

        Remote_PauseTimeStamp = timer_get_stamp32();
    }
}

void PauseMenu_Menu() {
    if (Remote_IsNetworkGame) {
        Remote_SendNetPacket_Signal(39, GameManager_PlayerTeam, 0);
    }

    DialogMenu_Menu("Game Paused.\nClick OK to continue.");
}

int menu_planet_select_menu_loop() {
    PlanetSelectMenu planet_select_menu;
    int result;
    bool event_release;

    event_release = false;
    planet_select_menu.Init();

    do {
        if (Remote_GameState == 1) {
            Remote_NetSync();
        }

        planet_select_menu.key = get_input();

        if (planet_select_menu.key > 0 && planet_select_menu.key < GNW_INPUT_PRESS) {
            event_release = false;
        }

        for (int i = 0; i < PLANET_SELECT_MENU_ITEM_COUNT; ++i) {
            if (planet_select_menu.buttons[i]) {
                if (planet_select_menu.key == GNW_INPUT_PRESS + i) {
                    if (!event_release) {
                        planet_select_menu.buttons[i]->PlaySound();
                    }

                    event_release = true;
                    break;
                }

                if (planet_select_menu.key == planet_select_menu.menu_item[i].event_code) {
                    planet_select_menu.key = planet_select_menu.menu_item[i].r_value;
                }

                if (planet_select_menu.key == planet_select_menu.menu_item[i].r_value) {
                    planet_select_menu.key -= 1000;
                    (planet_select_menu.*planet_select_menu.menu_item[i].event_handler)();
                    break;
                }
            }
        }
    } while (!planet_select_menu.event_click_done && !planet_select_menu.event_click_cancel);

    planet_select_menu.Deinit();
    if (!planet_select_menu.event_click_cancel) {
        ini_set_setting(INI_WORLD, planet_select_menu.world);

        result = 1;
    } else {
        result = 0;
    }

    return result;
}

int menu_options_menu_loop(int game_mode) {
    GameConfigMenu game_config_menu;
    int result;
    bool event_release;

    event_release = false;
    game_config_menu.game_mode = game_mode;
    game_config_menu.Init();

    do {
        if (Remote_GameState == 1) {
            Remote_NetSync();
        }

        game_config_menu.key = get_input();

        if (game_config_menu.key > 0 && game_config_menu.key < GNW_INPUT_PRESS) {
            event_release = false;
        }

        if (game_config_menu.text_edit) {
            if (game_config_menu.text_edit->ProcessKeyPress(game_config_menu.key)) {
                if (game_config_menu.key == GNW_KB_KEY_ESCAPE || game_config_menu.key == GNW_KB_KEY_RETURN) {
                    game_config_menu.UpdateTextEdit(game_config_menu.key == GNW_KB_KEY_RETURN);
                }

                game_config_menu.key = 0;
                continue;
            }

            if (game_config_menu.key > 0) {
                game_config_menu.text_edit->ProcessKeyPress(GNW_KB_KEY_RETURN);
                game_config_menu.UpdateTextEdit(1);
            }
        }

        for (int i = 0; i < GAME_CONFIG_MENU_ITEM_COUNT; ++i) {
            if (game_config_menu.buttons[i]) {
                if (game_config_menu.key == game_config_menu.menu_item[i].event_code) {
                    game_config_menu.key = game_config_menu.menu_item[i].r_value;
                }

                if (game_config_menu.key == game_config_menu.menu_item[i].r_value) {
                    if (!event_release) {
                        game_config_menu.buttons[i]->PlaySound();
                    }

                    event_release = true;
                    game_config_menu.key -= 1000;
                    (game_config_menu.*game_config_menu.menu_item[i].event_handler)();
                    break;
                }
            }
        }

    } while (!game_config_menu.event_click_cancel && !game_config_menu.event_click_done);

    game_config_menu.Deinit();
    result = game_config_menu.event_click_done;

    return result;
}

int menu_choose_player_menu_loop(bool game_type) {
    ChoosePlayerMenu choose_player_menu;
    bool event_release;

    if (game_type) {
        ini_set_setting(INI_RED_TEAM_PLAYER, TEAM_TYPE_PLAYER);
        ini_set_setting(INI_GREEN_TEAM_PLAYER, TEAM_TYPE_COMPUTER);
    } else {
        ini_set_setting(INI_RED_TEAM_PLAYER, TEAM_TYPE_PLAYER);
        ini_set_setting(INI_GREEN_TEAM_PLAYER, TEAM_TYPE_PLAYER);
    }

    ini_set_setting(INI_BLUE_TEAM_PLAYER, TEAM_TYPE_NONE);
    ini_set_setting(INI_GRAY_TEAM_PLAYER, TEAM_TYPE_NONE);

    event_release = false;

    choose_player_menu.game_type = game_type;
    choose_player_menu.Init();
    choose_player_menu.event_click_done = false;

    do {
        choose_player_menu.key_press = get_input();

        if (choose_player_menu.key_press > 0 && choose_player_menu.key_press < GNW_INPUT_PRESS) {
            event_release = false;
        }

        for (int i = 0; i < CHOOSE_PLAYER_MENU_ITEM_COUNT; ++i) {
            if (choose_player_menu.buttons[i]) {
                if (choose_player_menu.key_press == i + GNW_INPUT_PRESS) {
                    if (!event_release) {
                        choose_player_menu.buttons[i]->PlaySound();
                    }

                    event_release = true;
                    break;
                }

                if (choose_player_menu.key_press == choose_player_menu.menu_item[i].event_code) {
                    choose_player_menu.key_press = choose_player_menu.menu_item[i].r_value;
                }

                if (choose_player_menu.key_press == choose_player_menu.menu_item[i].r_value) {
                    if (i < 12) {
                        choose_player_menu.buttons[i]->PlaySound();
                    }

                    choose_player_menu.key_press -= 1000;
                    (choose_player_menu.*choose_player_menu.menu_item[i].event_handler)();
                    break;
                }
            }
        }

        if (choose_player_menu.event_click_cancel) {
            choose_player_menu.Deinit();

            return false;
        }

    } while (!choose_player_menu.event_click_done);

    choose_player_menu.Deinit();

    for (int i = 0; i < PLAYER_TEAM_MAX - 1; ++i) {
        int team_type;
        char buffer[30];

        team_type = ini_get_setting(static_cast<IniParameter>(INI_RED_TEAM_PLAYER + i));

        if (game_type && team_type == TEAM_TYPE_PLAYER) {
            ini_config.GetStringValue(INI_PLAYER_NAME, buffer, sizeof(buffer));
            ini_config.SetStringValue(static_cast<IniParameter>(INI_RED_TEAM_NAME + i), buffer);
            game_type = 0;
        } else {
            ini_config.SetStringValue(static_cast<IniParameter>(INI_RED_TEAM_NAME + i), menu_team_names[i]);
        }
    }

    return true;
}

int GameSetupMenu_Menu(int game_file_type, bool flag1, bool flag2) {
    GameSetupMenu game_setup_menu;
    SaveFormatHeader save_file_header;
    bool palette_from_image;
    bool event_release;
    int result;

    palette_from_image = false;
    game_setup_menu.game_file_type = game_file_type;

    if (game_file_type == GAME_TYPE_CAMPAIGN) {
        ini_set_setting(INI_GAME_FILE_NUMBER, ini_get_setting(INI_LAST_CAMPAIGN));
    } else {
        ini_set_setting(INI_GAME_FILE_NUMBER, 1);
    }

    for (;;) {
        event_release = false;
        game_setup_menu.Init(palette_from_image);

        do {
            if (Remote_GameState == 1) {
                Remote_NetSync();
            }

            game_setup_menu.key = get_input();

            if (game_setup_menu.key > 0 && game_setup_menu.key < GNW_INPUT_PRESS) {
                event_release = false;
            }

            switch (game_setup_menu.key) {
                case GNW_KB_KEY_PAGEUP: {
                    game_setup_menu.key = 12;
                    game_setup_menu.EventScrollButton();
                } break;

                case GNW_KB_KEY_PAGEDOWN: {
                    game_setup_menu.key = 13;
                    game_setup_menu.EventScrollButton();
                } break;

                case GNW_KB_KEY_UP:
                case GNW_KB_KEY_DOWN: {
                    game_setup_menu.EventStepButton();
                } break;

                default: {
                    for (int i = 0; i < GAME_SETUP_MENU_ITEM_COUNT; ++i) {
                        if (game_setup_menu.buttons[i]) {
                            if (game_setup_menu.key == GNW_INPUT_PRESS + i) {
                                if (!event_release) {
                                    game_setup_menu.buttons[i]->PlaySound();
                                }

                                event_release = true;
                                break;
                            }

                            if (game_setup_menu.key == game_setup_menu.menu_item[i].event_code) {
                                game_setup_menu.key = game_setup_menu.menu_item[i].r_value;
                            }

                            if (game_setup_menu.key == game_setup_menu.menu_item[i].r_value) {
                                game_setup_menu.key -= 1000;
                                (game_setup_menu.*game_setup_menu.menu_item[i].event_handler)();
                                break;
                            }
                        }
                    }

                } break;
            }

        } while (!game_setup_menu.event_click_done && !game_setup_menu.event_click_cancel);

        game_setup_menu.Deinit();

        if (game_setup_menu.event_click_cancel) {
            result = false;
            break;
        }

        GameManager_GameFileNumber = game_setup_menu.game_file_number;

        ini_set_setting(INI_GAME_FILE_NUMBER, GameManager_GameFileNumber);
        ini_set_setting(INI_GAME_FILE_TYPE, game_setup_menu.game_file_type);

        if (game_setup_menu.game_file_type != GAME_TYPE_MULTI_PLAYER_SCENARIO || flag1) {
            if (menu_options_menu_loop(2)) {
                if (game_setup_menu.game_file_type == GAME_TYPE_CAMPAIGN) {
                    menu_draw_campaign_mission_briefing_screen();
                }

                if (GameManager_GameFileNumber == 1 && game_setup_menu.game_file_type == GAME_TYPE_CAMPAIGN) {
                    Movie_Play(DEMO2FLC);
                }

                if (game_setup_menu.game_file_type == GAME_TYPE_MULTI_PLAYER_SCENARIO) {
                    SaveLoadMenu_GetSavedGameInfo(GameManager_GameFileNumber, ini_get_setting(INI_GAME_FILE_TYPE),
                                                  save_file_header, false);

                    ini_set_setting(INI_RED_TEAM_CLAN, save_file_header.team_clan[PLAYER_TEAM_RED]);
                    ini_set_setting(INI_GREEN_TEAM_CLAN, save_file_header.team_clan[PLAYER_TEAM_GREEN]);
                    ini_set_setting(INI_BLUE_TEAM_CLAN, save_file_header.team_clan[PLAYER_TEAM_BLUE]);
                    ini_set_setting(INI_GRAY_TEAM_CLAN, save_file_header.team_clan[PLAYER_TEAM_GRAY]);

                    if (menu_choose_player_menu_loop(flag2)) {
                        GameManager_GameLoop(GAME_STATE_10);
                        palette_from_image = true;
                    } else {
                        palette_from_image = false;
                    }

                } else {
                    GameManager_GameLoop(GAME_STATE_10);
                    palette_from_image = true;
                }

            } else {
                palette_from_image = false;
            }

            continue;
        }

        result = true;
        break;
    };

    return result;
}

int menu_custom_game_menu(bool game_type) {
    int result;
    bool enter_options_menu;
    bool enter_planet_select_menu;
    bool player_menu_passed;

    enter_options_menu = true;
    enter_planet_select_menu = true;
    player_menu_passed = false;

    do {
        if (enter_options_menu) {
            if (!menu_options_menu_loop(1)) {
                return 0;
            }

            enter_options_menu = false;
        }

        if (enter_planet_select_menu) {
            if (!menu_planet_select_menu_loop()) {
                enter_options_menu = 1;
                continue;
            }

            enter_planet_select_menu = false;
        }

        for (int i = PLAYER_TEAM_RED; i < PLAYER_TEAM_MAX - 1; ++i) {
            ini_set_setting(static_cast<IniParameter>(INI_RED_TEAM_CLAN + i), ini_get_setting(INI_PLAYER_CLAN));
        }

        player_menu_passed = menu_choose_player_menu_loop(game_type);

        if (!player_menu_passed) {
            enter_planet_select_menu = true;
        }

    } while (!player_menu_passed);

    mouse_hide();
    WindowManager_ClearWindow();
    mouse_show();

    GameManager_GameLoop(GAME_STATE_6);

    return 1;
}

int menu_new_game_menu_loop() {
    WindowInfo* window;
    int key;
    bool exit_loop;
    bool event_release;
    bool is_tips_window_active;

    window = WindowManager_GetWindow(WINDOW_MAIN_WINDOW);
    key = 0;

    while (key != GNW_KB_KEY_CTRL_ESCAPE && key != 9000) {
        event_release = false;

        mouse_hide();
        WindowManager_LoadBigImage(MAINPIC, window, window->width, false, false, -1, -1, true);
        draw_menu_title(window, "New Game Menu");
        menu_draw_menu_portrait(window, menu_portrait_id, false);
        menu_draw_main_menu_buttons(new_game_menu_buttons, sizeof(new_game_menu_buttons) / sizeof(MenuButton), 5);
        mouse_show();

        exit_loop = false;
        is_tips_window_active = false;

        while (!exit_loop) {
            key = toupper(get_input());

            if (key > 0 && key < GNW_INPUT_PRESS) {
                event_release = false;
            }

            switch (key) {
                case GNW_KB_KEY_SHIFT_T: {
                    menu_delete_menu_buttons();

                    if (GameSetupMenu_Menu(GAME_TYPE_TRAINING)) {
                        key = 9000;
                    }

                    exit_loop = true;

                } break;

                case GNW_KB_KEY_SHIFT_S: {
                    menu_delete_menu_buttons();

                    if (GameSetupMenu_Menu(GAME_TYPE_SCENARIO)) {
                        key = 9000;
                    }

                    exit_loop = true;

                } break;

                case GNW_KB_KEY_SHIFT_U: {
                    menu_delete_menu_buttons();
                    ini_set_setting(INI_GAME_FILE_TYPE, GAME_TYPE_CUSTOM);
                    if (menu_custom_game_menu(true)) {
                        key = 9000;
                    }

                    exit_loop = true;

                } break;

                case GNW_KB_KEY_SHIFT_M: {
                    menu_delete_menu_buttons();
                    ini_set_setting(INI_GAME_FILE_TYPE, GAME_TYPE_CUSTOM);
                    if (GameSetupMenu_Menu(GAME_TYPE_MULTI_PLAYER_SCENARIO)) {
                        key = 9000;
                    }

                    exit_loop = true;

                } break;

                case GNW_KB_KEY_SHIFT_A: {
                    menu_delete_menu_buttons();
                    if (GameSetupMenu_Menu(GAME_TYPE_CAMPAIGN)) {
                        key = 9000;
                    }

                    exit_loop = true;

                } break;

                case GNW_KB_KEY_SHIFT_I: {
                    is_tips_window_active = !is_tips_window_active;

                    SDL_assert(menu_button_items_count >= 5);

                    menu_button_items[5].button->PlaySound();

                    if (is_tips_window_active) {
                        menu_draw_tips(window);
                    } else {
                        menu_delete_menu_buttons();
                        exit_loop = true;
                    }

                } break;

                case GNW_KB_KEY_SHIFT_C:
                case GNW_KB_KEY_ESCAPE: {
                    menu_delete_menu_buttons();
                    key = GNW_KB_KEY_ESCAPE;
                    exit_loop = true;
                } break;

                case GNW_KB_KEY_UP: {
                    if (!is_tips_window_active) {
                        menu_draw_menu_portrait(window, INVALID_ID, true);
                    }
                } break;

                case 1000: {
                    tips_on_click_up(window);
                } break;

                case 1001: {
                    tips_on_click_down(window);
                } break;

                default: {
                    if (key >= GNW_INPUT_PRESS && !event_release) {
                        key -= GNW_INPUT_PRESS;

                        if (key == 1000 || key == 1001) {
                            menu_tips_button_up->PlaySound();
                        } else if (key < menu_button_items_count) {
                            menu_button_items[key].button->PlaySound();
                        }

                        event_release = true;
                    }

                } break;
            }
        }
    }

    return key == 9000;
}

void menu_preferences_window(unsigned short team) {
    OptionsMenu options_menu = OptionsMenu(team, PREFSPIC);

    options_menu.Run();
}

void menu_setup_window() {
    OptionsMenu options_menu = OptionsMenu(PLAYER_TEAM_RED, SETUPPIC);

    options_menu.Run();
}

int menu_network_game_menu(bool is_host_mode) {
    if (Remote_Lobby(is_host_mode)) {
        if (is_host_mode) {
            menu_update_resource_levels();
            Remote_SendNetPacket_17();
        }

        GameManager_GameLoop(GameManager_GameState);
    }

    Remote_Deinit();

    return false;
}

int menu_multiplayer_menu_loop() {
    WindowInfo* window;
    short palette_from_image;
    int key;
    bool exit_loop;
    bool event_release;

    window = WindowManager_GetWindow(WINDOW_MAIN_WINDOW);
    palette_from_image = 0;
    key = 0;

    while (key != GNW_KB_KEY_CTRL_ESCAPE && key != 9000) {
        event_release = false;

        mouse_hide();
        WindowManager_LoadBigImage(MAINPIC, window, window->width, palette_from_image, false, -1, -1, true);
        draw_menu_title(window, "Multiplayer Menu");
        menu_draw_menu_portrait(window, menu_portrait_id, false);
        menu_draw_main_menu_buttons(network_game_menu_buttons,
                                    sizeof(network_game_menu_buttons) / sizeof(struct MenuButton));
        ini_set_setting(INI_GAME_FILE_TYPE, GAME_TYPE_MULTI);
        palette_from_image = 0;
        mouse_show();

        exit_loop = false;

        while (!exit_loop) {
            key = toupper(get_input());

            if (key > 0 && key < GNW_INPUT_PRESS) {
                event_release = false;
            }

            switch (key) {
                case GNW_KB_KEY_SHIFT_L: {
                    int game_file_number;
                    menu_delete_menu_buttons();
                    ini_set_setting(INI_GAME_FILE_TYPE, GAME_TYPE_HOT_SEAT);
                    game_file_number = SaveLoadMenu_MenuLoop(false, false);

                    if (game_file_number) {
                        ini_set_setting(INI_GAME_FILE_NUMBER, game_file_number);
                        GameManager_GameLoop(GAME_STATE_10);

                        key = 9000;
                    }

                    exit_loop = true;
                    palette_from_image = true;

                } break;

                case GNW_KB_KEY_SHIFT_T: {
                    menu_delete_menu_buttons();

                    if (GameSetupMenu_Menu(GAME_TYPE_MULTI_PLAYER_SCENARIO, true, false)) {
                        key = 9000;
                    }

                    exit_loop = true;

                } break;

                case GNW_KB_KEY_UP: {
                    menu_draw_menu_portrait(window, INVALID_ID, true);
                } break;

                case GNW_KB_KEY_SHIFT_O: {
                    menu_delete_menu_buttons();
                    ini_set_setting(INI_GAME_FILE_TYPE, GAME_TYPE_HOT_SEAT);

                    if (menu_custom_game_menu(false)) {
                        key = 9000;
                    }

                    exit_loop = true;

                } break;

                case GNW_KB_KEY_SHIFT_H: {
                    menu_delete_menu_buttons();

                    if (menu_network_game_menu(true)) {
                        key = 9000;
                    }

                    exit_loop = true;

                } break;

                case GNW_KB_KEY_SHIFT_J: {
                    menu_delete_menu_buttons();

                    if (menu_network_game_menu(false)) {
                        key = 9000;
                    }

                    exit_loop = true;

                } break;

                case GNW_KB_KEY_SHIFT_C:
                case GNW_KB_KEY_ESCAPE: {
                    menu_delete_menu_buttons();
                    key = GNW_KB_KEY_ESCAPE;
                    exit_loop = true;
                } break;

                default: {
                    if (key >= GNW_INPUT_PRESS) {
                        key -= GNW_INPUT_PRESS;

                        if (!event_release && key < menu_button_items_count) {
                            menu_button_items[key].button->PlaySound();
                        }

                        event_release = true;
                    }

                } break;
            }
        }

        Remote_Deinit();
    }

    return key == 9000;
}

void menu_draw_exit_logos() {
    mouse_hide();
    menu_draw_logo(OEMONE, 60000);
    menu_draw_logo(OEMTWO, 60000);
}

bool OKCancelMenu_Menu(const char* caption, bool mode) { return OKCancelMenu(caption, mode).Run(); }

bool DesyncMenu_Menu() {
    DesyncMenu desync_menu;

    Remote_WaitBeginTurnAcknowledge();

    return desync_menu.Run();
}

void main_menu() {
    WindowInfo* window;
    unsigned int time_stamp;
    short palette_from_image;
    bool exit_loop;
    bool event_release;
    int save_slot;
    int old_save_slot;
    int last_mouse_x;
    int last_mouse_y;

    window = WindowManager_GetWindow(WINDOW_MAIN_WINDOW);
    palette_from_image = 1;
    save_slot = 1;
    mouse_set_position(WindowManager_GetWidth(window) / 2, WindowManager_GetHeight(window) / 2);
    menu_portrait_id = INVALID_ID;
    dos_srand(time(nullptr));
    ini_setting_victory_type = ini_get_setting(INI_VICTORY_TYPE);
    ini_setting_victory_limit = ini_get_setting(INI_VICTORY_LIMIT);

    for (;;) {
        last_mouse_x = 0;
        last_mouse_y = 0;
        event_release = false;
        time_stamp = timer_get_stamp32();
        GameManager_GameState = GAME_STATE_3_MAIN_MENU;
        mouse_hide();
        WindowManager_LoadBigImage(MAINPIC, window, window->width, palette_from_image, false, -1, -1, true);
        draw_menu_title(window, _(35f9));
        menu_draw_menu_portrait(window, menu_portrait_id, false);
        draw_copyright_label(window);
        menu_draw_main_menu_buttons(main_menu_buttons, sizeof(main_menu_buttons) / sizeof(struct MenuButton));
        mouse_show();
        SoundManager.PlayMusic(MAIN_MSC, false);
        Cursor_SetCursor(CURSOR_HAND);
        mouse_show();
        palette_from_image = 0;
        ini_set_setting(INI_GAME_FILE_TYPE, GAME_TYPE_CUSTOM);

        exit_loop = false;

        while (!exit_loop) {
            if (timer_elapsed_time_ms(time_stamp) > 60000) {
                old_save_slot = save_slot;
                menu_delete_menu_buttons();

                do {
                    palette_from_image = play_attract_demo(save_slot);
                    ++save_slot;
                    if (save_slot == 10) {
                        save_slot = 1;
                    }
                } while (!palette_from_image && old_save_slot != save_slot);

                break;

            } else {
                int key;
                int mouse_x;
                int mouse_y;

                key = get_input();
                mouse_get_position(&mouse_x, &mouse_y);

                if (key != -1 || mouse_x != last_mouse_x || mouse_y != last_mouse_y) {
                    time_stamp = timer_get_stamp32();
                    last_mouse_x = mouse_x;
                    last_mouse_y = mouse_y;
                }

                key = toupper(key);

                if (key > 0 && key < GNW_INPUT_PRESS) {
                    event_release = false;
                }

                switch (key) {
                    case GNW_KB_KEY_SHIFT_L: {
                        int game_file_number;

                        menu_delete_menu_buttons();
                        game_file_number = SaveLoadMenu_MenuLoop(false, false);

                        if (game_file_number) {
                            ini_set_setting(INI_GAME_FILE_NUMBER, game_file_number);

                            GameManager_GameLoop(GAME_STATE_10);

                            menu_portrait_id = INVALID_ID;
                        }

                        palette_from_image = 1;
                        exit_loop = true;

                    } break;

                    case GNW_KB_KEY_CTRL_L: {
                        int game_file_number;

                        menu_delete_menu_buttons();
                        game_file_number = SaveLoadMenu_MenuLoop(false, true);

                        if (game_file_number) {
                            ini_set_setting(INI_GAME_FILE_TYPE, GAME_TYPE_TEXT);
                            ini_set_setting(INI_GAME_FILE_NUMBER, game_file_number);

                            GameManager_GameLoop(GAME_STATE_10);

                            menu_portrait_id = INVALID_ID;
                        }

                        palette_from_image = 1;
                        exit_loop = true;
                    } break;

                    case GNW_KB_KEY_SHIFT_N: {
                        menu_delete_menu_buttons();
                        palette_from_image = menu_new_game_menu_loop();

                        if (palette_from_image) {
                            menu_portrait_id = INVALID_ID;
                        }

                        exit_loop = true;

                    } break;

                    case GNW_KB_KEY_SHIFT_S: {
                        menu_disable_menu_buttons();
                        menu_setup_window();
                        menu_enable_menu_buttons();
                        time_stamp = timer_get_stamp32();
                    } break;

                    case GNW_KB_KEY_UP: {
                        menu_draw_menu_portrait(window, INVALID_ID, true);
                    } break;

                    case GNW_KB_KEY_SHIFT_M: {
                        menu_delete_menu_buttons();
                        palette_from_image = menu_multiplayer_menu_loop();

                        if (palette_from_image) {
                            menu_portrait_id = INVALID_ID;
                        }

                        exit_loop = true;

                    } break;

                    case GNW_KB_KEY_SHIFT_E: {
                        menu_delete_menu_buttons();
                        ResourceManager_ExitGame(EXIT_CODE_THANKS);

                    } break;

                    case GNW_KB_KEY_SHIFT_I: {
                        mouse_hide();
                        menu_delete_menu_buttons();

                        Movie_PlayIntro();

                        palette_from_image = 1;
                        exit_loop = true;

                    } break;

                    case GNW_KB_KEY_SHIFT_C: {
                        menu_delete_menu_buttons();

                        menu_credits_menu_loop();

                        palette_from_image = 1;
                        exit_loop = true;

                    } break;

                    default: {
                        if (key >= GNW_INPUT_PRESS) {
                            key -= GNW_INPUT_PRESS;

                            if (!event_release && key < menu_button_items_count) {
                                menu_button_items[key].button->PlaySound();
                            }

                            event_release = true;
                        }
                    } break;
                }
            }
        }
    }
}
