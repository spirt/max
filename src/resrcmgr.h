/* Copyright (c) 2020 M.A.X. Port Team
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

#ifndef RESRCMGR_H
#define RESRCMGR_H

#include <SDL.h>

#define RESOURCE_LIST_INIT                                                                                             \
    "COMMTWR" /* 0x0 */, "POWERSTN" /* 0x1 */, "POWGEN" /* 0x2 */, "BARRACKS" /* 0x3 */, "SHIELDGN" /* 0x4 */,         \
        "RADAR" /* 0x5 */, "ADUMP" /* 0x6 */, "FDUMP" /* 0x7 */, "GOLDSM" /* 0x8 */, "DEPOT" /* 0x9 */,                \
        "HANGAR" /* 0xA */, "DOCK" /* 0xB */, "CNCT_4W" /* 0xC */, "LRGRUBLE" /* 0xD */, "SMLRUBLE" /* 0xE */,         \
        "LRGTAPE" /* 0xF */, "SMLTAPE" /* 0x10 */, "LRGSLAB" /* 0x11 */, "SMLSLAB" /* 0x12 */, "LRGCONES" /* 0x13 */,  \
        "SMLCONES" /* 0x14 */, "ROAD" /* 0x15 */, "LANDPAD" /* 0x16 */, "SHIPYARD" /* 0x17 */, "LIGHTPLT" /* 0x18 */,  \
        "LANDPLT" /* 0x19 */, "SUPRTPLT" /* 0x1A */, "AIRPLT" /* 0x1B */, "HABITAT" /* 0x1C */, "RESEARCH" /* 0x1D */, \
        "GREENHSE" /* 0x1E */, "RECCENTR" /* 0x1F */, "TRAINHAL" /* 0x20 */, "WTRPLTFM" /* 0x21 */,                    \
        "GUNTURRT" /* 0x22 */, "ANTIAIR" /* 0x23 */, "ARTYTRRT" /* 0x24 */, "ANTIMSSL" /* 0x25 */, "BLOCK" /* 0x26 */, \
        "BRIDGE" /* 0x27 */, "MININGST" /* 0x28 */, "LANDMINE" /* 0x29 */, "SEAMINE" /* 0x2A */,                       \
        "LNDEXPLD" /* 0x2B */, "AIREXPLD" /* 0x2C */, "SEAEXPLD" /* 0x2D */, "BLDEXPLD" /* 0x2E */,                    \
        "HITEXPLD" /* 0x2F */, "MASTER" /* 0x30 */, "CONSTRCT" /* 0x31 */, "SCOUT" /* 0x32 */, "TANK" /* 0x33 */,      \
        "ARTILLRY" /* 0x34 */, "ROCKTLCH" /* 0x35 */, "MISSLLCH" /* 0x36 */, "SP_FLAK" /* 0x37 */,                     \
        "MINELAYR" /* 0x38 */, "SURVEYOR" /* 0x39 */, "SCANNER" /* 0x3A */, "SPLYTRCK" /* 0x3B */,                     \
        "GOLDTRCK" /* 0x3C */, "ENGINEER" /* 0x3D */, "BULLDOZR" /* 0x3E */, "REPAIR" /* 0x3F */,                      \
        "FUELTRCK" /* 0x40 */, "CLNTRANS" /* 0x41 */, "COMMANDO" /* 0x42 */, "INFANTRY" /* 0x43 */,                    \
        "FASTBOAT" /* 0x44 */, "CORVETTE" /* 0x45 */, "BATTLSHP" /* 0x46 */, "SUBMARNE" /* 0x47 */,                    \
        "SEATRANS" /* 0x48 */, "MSSLBOAT" /* 0x49 */, "SEAMNLYR" /* 0x4A */, "CARGOSHP" /* 0x4B */,                    \
        "FIGHTER" /* 0x4C */, "BOMBER" /* 0x4D */, "AIRTRANS" /* 0x4E */, "AWAC" /* 0x4F */, "JUGGRNT" /* 0x50 */,     \
        "ALNTANK" /* 0x51 */, "ALNASGUN" /* 0x52 */, "ALNPLANE" /* 0x53 */, "ROCKET" /* 0x54 */, "TORPEDO" /* 0x55 */, \
        "ALNMISSL" /* 0x56 */, "ALNTBALL" /* 0x57 */, "ALNABALL" /* 0x58 */, "RKTSMOKE" /* 0x59 */,                    \
        "TRPBUBLE" /* 0x5A */, "HARVSTER" /* 0x5B */, "WALDO" /* 0x5C */, "UNIT_END" /* 0x5D */,                       \
        "S_COMMTW" /* 0x5E */, "S_POWERS" /* 0x5F */, "S_POWGEN" /* 0x60 */, "S_BARRAC" /* 0x61 */,                    \
        "S_SHIELD" /* 0x62 */, "S_RADAR" /* 0x63 */, "S_ADUMP" /* 0x64 */, "S_FDUMP" /* 0x65 */,                       \
        "S_GOLDSM" /* 0x66 */, "S_DEPOT" /* 0x67 */, "S_HANGAR" /* 0x68 */, "S_DOCK" /* 0x69 */,                       \
        "S_CNCT4W" /* 0x6A */, "S_LRGRBL" /* 0x6B */, "S_SMLRBL" /* 0x6C */, "S_LRGSLA" /* 0x6D */,                    \
        "S_LRGCON" /* 0x6E */, "S_SMLSLA" /* 0x6F */, "S_SMLCON" /* 0x70 */, "S_ROAD" /* 0x71 */,                      \
        "S_LANDPA" /* 0x72 */, "S_SHIPYA" /* 0x73 */, "S_LIGHTP" /* 0x74 */, "S_LANDPL" /* 0x75 */,                    \
        "S_SUPRTP" /* 0x76 */, "S_AIRPLT" /* 0x77 */, "S_HABITA" /* 0x78 */, "S_RESEAR" /* 0x79 */,                    \
        "S_GREENH" /* 0x7A */, "S_RECCEN" /* 0x7B */, "S_TRAINH" /* 0x7C */, "S_WTRPLT" /* 0x7D */,                    \
        "S_GUNTUR" /* 0x7E */, "S_ANTIAI" /* 0x7F */, "S_ARTYTR" /* 0x80 */, "S_ANTIMS" /* 0x81 */,                    \
        "S_BLOCK" /* 0x82 */, "S_BRIDGE" /* 0x83 */, "S_MINING" /* 0x84 */, "S_LANDMI" /* 0x85 */,                     \
        "S_SEAMIN" /* 0x86 */, "S_MASTER" /* 0x87 */, "S_CONSTR" /* 0x88 */, "S_SCOUT" /* 0x89 */,                     \
        "S_TANK" /* 0x8A */, "S_ARTILL" /* 0x8B */, "S_ROCKTL" /* 0x8C */, "S_MISSLL" /* 0x8D */, "S_FLAK" /* 0x8E */, \
        "S_MINELA" /* 0x8F */, "S_SURVEY" /* 0x90 */, "S_SCANNE" /* 0x91 */, "S_SPLYTR" /* 0x92 */,                    \
        "S_GOLDTR" /* 0x93 */, "S_ENGINE" /* 0x94 */, "S_BULLDO" /* 0x95 */, "S_REPAIR" /* 0x96 */,                    \
        "S_FUELTR" /* 0x97 */, "S_CLNTRA" /* 0x98 */, "S_COMMAN" /* 0x99 */, "S_INFANT" /* 0x9A */,                    \
        "S_FASTBO" /* 0x9B */, "S_CORVET" /* 0x9C */, "S_BATTLS" /* 0x9D */, "S_SUBMAR" /* 0x9E */,                    \
        "S_SEATRA" /* 0x9F */, "S_MSSLBO" /* 0xA0 */, "S_SEAMNL" /* 0xA1 */, "S_CARGOS" /* 0xA2 */,                    \
        "S_FIGHTE" /* 0xA3 */, "S_BOMBER" /* 0xA4 */, "S_AIRTRA" /* 0xA5 */, "S_AWAC" /* 0xA6 */,                      \
        "S_JUGGRN" /* 0xA7 */, "S_ALNTAN" /* 0xA8 */, "S_ALNASG" /* 0xA9 */, "S_ALNPLA" /* 0xAA */,                    \
        "S_HARVST" /* 0xAB */, "MOVEPT" /* 0xAC */, "NOMOVEPT" /* 0xAD */, "FIREPT" /* 0xAE */, "NOFIREPT" /* 0xAF */, \
        "NOCARGO" /* 0xB0 */, "UNTBTN_U" /* 0xB1 */, "UNTBTN_D" /* 0xB2 */, "DONE_OF" /* 0xB3 */,                      \
        "DONE_ON" /* 0xB4 */, "NEXT_OF" /* 0xB5 */, "NEXT_ON" /* 0xB6 */, "PREV_OF" /* 0xB7 */, "PREV_ON" /* 0xB8 */,  \
        "XFORM_OF" /* 0xB9 */, "XFORM_ON" /* 0xBA */, "BUILD_OF" /* 0xBB */, "BUILD_ON" /* 0xBC */,                    \
        "ALLOC_OF" /* 0xBD */, "ALLOC_ON" /* 0xBE */, "ATTK_OF" /* 0xBF */, "ATTK_ON" /* 0xC0 */,                      \
        "SNTRY_OF" /* 0xC1 */, "SNTRY_ON" /* 0xC2 */, "WAIT_OF" /* 0xC3 */, "WAIT_ON" /* 0xC4 */,                      \
        "XFER_OF" /* 0xC5 */, "XFER_ON" /* 0xC6 */, "LOAD_OF" /* 0xC7 */, "LOAD_ON" /* 0xC8 */, "ACTVT_OF" /* 0xC9 */, \
        "ACTVT_ON" /* 0xCA */, "STOP_OF" /* 0xCB */, "STOP_ON" /* 0xCC */, "REPAR_OF" /* 0xCD */,                      \
        "REPAR_ON" /* 0xCE */, "FLLOW_OF" /* 0xCF */, "FLLOW_ON" /* 0xD0 */, "CLEAR_OF" /* 0xD1 */,                    \
        "CLEAR_ON" /* 0xD2 */, "RECHG_OF" /* 0xD3 */, "RECHG_ON" /* 0xD4 */, "START_OF" /* 0xD5 */,                    \
        "START_ON" /* 0xD6 */, "UPGRD_OF" /* 0xD7 */, "UPGRD_ON" /* 0xD8 */, "BYUPG_OF" /* 0xD9 */,                    \
        "BYUPG_ON" /* 0xDA */, "RLOAD_OF" /* 0xDB */, "RLOAD_ON" /* 0xDC */, "RSRCH_OF" /* 0xDD */,                    \
        "RSRCH_ON" /* 0xDE */, "PLACE_OF" /* 0xDF */, "PLACE_ON" /* 0xE0 */, "REMVE_OF" /* 0xE1 */,                    \
        "REMVE_ON" /* 0xE2 */, "ENTER_OF" /* 0xE3 */, "ENTER_ON" /* 0xE4 */, "TOPIC_OF" /* 0xE5 */,                    \
        "TOPIC_ON" /* 0xE6 */, "TIMER" /* 0xE7 */, "XYPOS" /* 0xE8 */, "UNITNAME" /* 0xE9 */, "TURNS" /* 0xEA */,      \
        "SELFD_OF" /* 0xEB */, "SELFD_ON" /* 0xEC */, "STEAL_OF" /* 0xED */, "STEAL_ON" /* 0xEE */,                    \
        "DISBL_OF" /* 0xEF */, "DISBL_ON" /* 0xF0 */, "STATS_OF" /* 0xF1 */, "STATS_ON" /* 0xF2 */,                    \
        "R_RSRC_U" /* 0xF3 */, "R_RSRC_D" /* 0xF4 */, "R_FACL_U" /* 0xF5 */, "R_FACL_D" /* 0xF6 */,                    \
        "R_PERF_U" /* 0xF7 */, "R_PERF_D" /* 0xF8 */, "R_PROD_U" /* 0xF9 */, "R_PROD_D" /* 0xFA */,                    \
        "R_MINE_U" /* 0xFB */, "R_MINE_D" /* 0xFC */, "R_UNIT_U" /* 0xFD */, "R_UNIT_D" /* 0xFE */,                    \
        "R_UPGR_U" /* 0xFF */, "R_UPGR_D" /* 0x100 */, "R_CSLT_U" /* 0x101 */, "R_CSLT_D" /* 0x102 */,                 \
        "R_ETA__U" /* 0x103 */, "R_ETA__D" /* 0x104 */, "R_STAT_U" /* 0x105 */, "R_STAT_D" /* 0x106 */,                \
        "R_CPLX_U" /* 0x107 */, "R_CPLX_D" /* 0x108 */, "R_CLSE_U" /* 0x109 */, "R_CLSE_D" /* 0x10A */,                \
        "R_UPAR_U" /* 0x10B */, "R_UPAR_D" /* 0x10C */, "R_DNAR_U" /* 0x10D */, "R_DNAR_D" /* 0x10E */,                \
        "ENDTRN_U" /* 0x10F */, "R_ENDT_D" /* 0x110 */, "G_ENDT_D" /* 0x111 */, "B_ENDT_D" /* 0x112 */,                \
        "W_ENDT_D" /* 0x113 */, "QWKUP_OF" /* 0x114 */, "QWKUP_ON" /* 0x115 */, "QWKDN_OF" /* 0x116 */,                \
        "QWKDN_ON" /* 0x117 */, "QWKCN_OF" /* 0x118 */, "QWKCN_ON" /* 0x119 */, "BLDUP__U" /* 0x11A */,                \
        "BLDUP__D" /* 0x11B */, "BLDUP__X" /* 0x11C */, "BLDDWN_U" /* 0x11D */, "BLDDWN_D" /* 0x11E */,                \
        "BLDDWN_X" /* 0x11F */, "BLDBLD_U" /* 0x120 */, "BLDBLD_D" /* 0x121 */, "BLDONE_U" /* 0x122 */,                \
        "BLDONE_D" /* 0x123 */, "BLDREP_U" /* 0x124 */, "BLDREP_D" /* 0x125 */, "BLDDEL_U" /* 0x126 */,                \
        "BLDDEL_D" /* 0x127 */, "BLDDES_U" /* 0x128 */, "BLDDES_D" /* 0x129 */, "BLDCAN_U" /* 0x12A */,                \
        "BLDCAN_D" /* 0x12B */, "BLDHLP_U" /* 0x12C */, "BLDHLP_D" /* 0x12D */, "BLDPTH_U" /* 0x12E */,                \
        "BLDPTH_D" /* 0x12F */, "BLD2X_U" /* 0x130 */, "BLD2X_D" /* 0x131 */, "BLD4X_U" /* 0x132 */,                   \
        "BLD4X_D" /* 0x133 */, "AL_DNE_U" /* 0x134 */, "AL_DNE_D" /* 0x135 */, "UPGDNE_U" /* 0x136 */,                 \
        "UPGDNE_D" /* 0x137 */, "UPGCAN_U" /* 0x138 */, "UPGCAN_D" /* 0x139 */, "UPGRGT_U" /* 0x13A */,                \
        "UPGRGT_D" /* 0x13B */, "UPGRGT_X" /* 0x13C */, "UPGLFT_U" /* 0x13D */, "UPGLFT_D" /* 0x13E */,                \
        "UPGLFT_X" /* 0x13F */, "SELGRD_U" /* 0x140 */, "SELGRD_D" /* 0x141 */, "SELAIR_U" /* 0x142 */,                \
        "SELAIR_D" /* 0x143 */, "SELSEA_U" /* 0x144 */, "SELSEA_D" /* 0x145 */, "SELBLD_U" /* 0x146 */,                \
        "SELBLD_D" /* 0x147 */, "SELCBT_U" /* 0x148 */, "SELCBT_D" /* 0x149 */, "XFRDNE_U" /* 0x14A */,                \
        "XFRDNE_D" /* 0x14B */, "XFRHLP_U" /* 0x14C */, "XFRHLP_D" /* 0x14D */, "XFRCAN_U" /* 0x14E */,                \
        "XFRCAN_D" /* 0x14F */, "XFRRGT_U" /* 0x150 */, "XFRRGT_D" /* 0x151 */, "XFRLFT_U" /* 0x152 */,                \
        "XFRLFT_D" /* 0x153 */, "XFRLFARO" /* 0x154 */, "XFRRTARO" /* 0x155 */, "DLOGOK_U" /* 0x156 */,                \
        "DLOGOK_D" /* 0x157 */, "HELPOK_U" /* 0x158 */, "HELPOK_D" /* 0x159 */, "ENDOK_U" /* 0x15A */,                 \
        "ENDOK_D" /* 0x15B */, "SLFDAR_U" /* 0x15C */, "SLFDAR_D" /* 0x15D */, "SLFDCN_U" /* 0x15E */,                 \
        "SLFDCN_D" /* 0x15F */, "SLFDOK_U" /* 0x160 */, "SLFDOK_D" /* 0x161 */, "SLFDOPN1" /* 0x162 */,                \
        "SLFDOPN2" /* 0x163 */, "SLFDOPN3" /* 0x164 */, "SLFDOPN4" /* 0x165 */, "SLFDOPN5" /* 0x166 */,                \
        "SLFDOPN6" /* 0x167 */, "PNLHLP_U" /* 0x168 */, "PNLHLP_D" /* 0x169 */, "PNLCAN_U" /* 0x16A */,                \
        "PNLCAN_D" /* 0x16B */, "CHTCAN_U" /* 0x16C */, "CHTCAN_D" /* 0x16D */, "CHTHLP_U" /* 0x16E */,                \
        "CHTHLP_D" /* 0x16F */, "CHTSND_U" /* 0x170 */, "CHTSND_D" /* 0x171 */, "CHTRED_U" /* 0x172 */,                \
        "CHTRED_D" /* 0x173 */, "CHTGRN_U" /* 0x174 */, "CHTGRN_D" /* 0x175 */, "CHTBLU_U" /* 0x176 */,                \
        "CHTBLU_D" /* 0x177 */, "CHTGRY_U" /* 0x178 */, "CHTGRY_D" /* 0x179 */, "PRFCAN_U" /* 0x17A */,                \
        "PRFCAN_D" /* 0x17B */, "PRFHLP_U" /* 0x17C */, "PRFHLP_D" /* 0x17D */, "PRFDNE_U" /* 0x17E */,                \
        "PRFDNE_D" /* 0x17F */, "PREFEDIT" /* 0x180 */, "PREFNAME" /* 0x181 */, "PRFSLIDE" /* 0x182 */,                \
        "PRFSLIT" /* 0x183 */, "CRGTOG_U" /* 0x184 */, "CRGTOG_D" /* 0x185 */, "CRGDEL_U" /* 0x186 */,                 \
        "CRGDEL_D" /* 0x187 */, "CRGDEL_X" /* 0x188 */, "CRGBUY_U" /* 0x189 */, "CRGBUY_D" /* 0x18A */,                \
        "CRGBUY_X" /* 0x18B */, "CRGSELUX" /* 0x18C */, "CRGSELDX" /* 0x18D */, "DPTBAYUP" /* 0x18E */,                \
        "DPTBAYDN" /* 0x18F */, "DPTMNUUP" /* 0x190 */, "DPTMNUDN" /* 0x191 */, "DPTUP_UP" /* 0x192 */,                \
        "DPTUP_DN" /* 0x193 */, "DPTUP_X" /* 0x194 */, "DPTDN_UP" /* 0x195 */, "DPTDN_DN" /* 0x196 */,                 \
        "DPTDN_X" /* 0x197 */, "DPTHP_UP" /* 0x198 */, "DPTHP_DN" /* 0x199 */, "RAWMSK0" /* 0x19A */,                  \
        "RAWMSK1" /* 0x19B */, "RAWMSK2" /* 0x19C */, "RAWMSK3" /* 0x19D */, "RAWMSK4" /* 0x19E */,                    \
        "RAWMSK5" /* 0x19F */, "RAWMSK6" /* 0x1A0 */, "RAWMSK7" /* 0x1A1 */, "RAWMSK8" /* 0x1A2 */,                    \
        "RAWMSK9" /* 0x1A3 */, "RAWMSK10" /* 0x1A4 */, "RAWMSK11" /* 0x1A5 */, "RAWMSK12" /* 0x1A6 */,                 \
        "RAWMSK13" /* 0x1A7 */, "RAWMSK14" /* 0x1A8 */, "RAWMSK15" /* 0x1A9 */, "RAWMSK16" /* 0x1AA */,                \
        "FUELMK0" /* 0x1AB */, "FUELMK1" /* 0x1AC */, "FUELMK2" /* 0x1AD */, "FUELMK3" /* 0x1AE */,                    \
        "FUELMK4" /* 0x1AF */, "FUELMK5" /* 0x1B0 */, "FUELMK6" /* 0x1B1 */, "FUELMK7" /* 0x1B2 */,                    \
        "FUELMK8" /* 0x1B3 */, "FUELMK9" /* 0x1B4 */, "FUELMK10" /* 0x1B5 */, "FUELMK11" /* 0x1B6 */,                  \
        "FUELMK12" /* 0x1B7 */, "FUELMK13" /* 0x1B8 */, "FUELMK14" /* 0x1B9 */, "FUELMK15" /* 0x1BA */,                \
        "FUELMK16" /* 0x1BB */, "GOLDMK0" /* 0x1BC */, "GOLDMK1" /* 0x1BD */, "GOLDMK2" /* 0x1BE */,                   \
        "GOLDMK3" /* 0x1BF */, "GOLDMK4" /* 0x1C0 */, "GOLDMK5" /* 0x1C1 */, "GOLDMK6" /* 0x1C2 */,                    \
        "GOLDMK7" /* 0x1C3 */, "GOLDMK8" /* 0x1C4 */, "GOLDMK9" /* 0x1C5 */, "GOLDMK10" /* 0x1C6 */,                   \
        "GOLDMK11" /* 0x1C7 */, "GOLDMK12" /* 0x1C8 */, "GOLDMK13" /* 0x1C9 */, "GOLDMK14" /* 0x1CA */,                \
        "GOLDMK15" /* 0x1CB */, "GOLDMK16" /* 0x1CC */, "SMRWMK1" /* 0x1CD */, "SMRWMK2" /* 0x1CE */,                  \
        "SMRWMK3" /* 0x1CF */, "SMRWMK4" /* 0x1D0 */, "SMRWMK5" /* 0x1D1 */, "SMRWMK6" /* 0x1D2 */,                    \
        "SMRWMK7" /* 0x1D3 */, "SMRWMK8" /* 0x1D4 */, "SMRWMK9" /* 0x1D5 */, "SMRWMK10" /* 0x1D6 */,                   \
        "SMRWMK11" /* 0x1D7 */, "SMRWMK12" /* 0x1D8 */, "SMRWMK13" /* 0x1D9 */, "SMRWMK14" /* 0x1DA */,                \
        "SMRWMK15" /* 0x1DB */, "SMRWMK16" /* 0x1DC */, "SMFLMK1" /* 0x1DD */, "SMFLMK2" /* 0x1DE */,                  \
        "SMFLMK3" /* 0x1DF */, "SMFLMK4" /* 0x1E0 */, "SMFLMK5" /* 0x1E1 */, "SMFLMK6" /* 0x1E2 */,                    \
        "SMFLMK7" /* 0x1E3 */, "SMFLMK8" /* 0x1E4 */, "SMFLMK9" /* 0x1E5 */, "SMFLMK10" /* 0x1E6 */,                   \
        "SMFLMK11" /* 0x1E7 */, "SMFLMK12" /* 0x1E8 */, "SMFLMK13" /* 0x1E9 */, "SMFLMK14" /* 0x1EA */,                \
        "SMFLMK15" /* 0x1EB */, "SMFLMK16" /* 0x1EC */, "SMGDMK1" /* 0x1ED */, "SMGDMK2" /* 0x1EE */,                  \
        "SMGDMK3" /* 0x1EF */, "SMGDMK4" /* 0x1F0 */, "SMGDMK5" /* 0x1F1 */, "SMGDMK6" /* 0x1F2 */,                    \
        "SMGDMK7" /* 0x1F3 */, "SMGDMK8" /* 0x1F4 */, "SMGDMK9" /* 0x1F5 */, "SMGDMK10" /* 0x1F6 */,                   \
        "SMGDMK11" /* 0x1F7 */, "SMGDMK12" /* 0x1F8 */, "SMGDMK13" /* 0x1F9 */, "SMGDMK14" /* 0x1FA */,                \
        "SMGDMK15" /* 0x1FB */, "SMGDMK16" /* 0x1FC */, "BULB" /* 0x1FD */, "MARKER0" /* 0x1FE */,                     \
        "MARKER1" /* 0x1FF */, "MARKER2" /* 0x200 */, "MARKER3" /* 0x201 */, "MARKER4" /* 0x202 */,                    \
        "STATNUM0" /* 0x203 */, "STATNUM1" /* 0x204 */, "STATNUM2" /* 0x205 */, "STATNUM3" /* 0x206 */,                \
        "STATNUM4" /* 0x207 */, "STATNUM5" /* 0x208 */, "STATNUM6" /* 0x209 */, "STATNUM7" /* 0x20A */,                \
        "STATNUM8" /* 0x20B */, "STATNUM9" /* 0x20C */, "FUELDOT" /* 0x20D */, "GOLDDOT" /* 0x20E */,                  \
        "LFARO_OF" /* 0x20F */, "LFARO_ON" /* 0x210 */, "PRODDOT" /* 0x211 */, "PRODSLOT" /* 0x212 */,                 \
        "RAWDOT" /* 0x213 */, "RTARO_OF" /* 0x214 */, "RTARO_ON" /* 0x215 */, "BARRAW" /* 0x216 */,                    \
        "BARFUEL" /* 0x217 */, "BARGOLD" /* 0x218 */, "BARUNUS" /* 0x219 */, "BARTAPE" /* 0x21A */,                    \
        "BARTAPE2" /* 0x21B */, "BARTAPE3" /* 0x21C */, "BARTAPEX" /* 0x21D */, "SMBRRAW" /* 0x21E */,                 \
        "SMBRFUEL" /* 0x21F */, "SMBRGOLD" /* 0x220 */, "VERTRAW" /* 0x221 */, "VERTFUEL" /* 0x222 */,                 \
        "VERTGOLD" /* 0x223 */, "LOADBAR" /* 0x224 */, "CLOSE_OF" /* 0x225 */, "CLOSE_ON" /* 0x226 */,                 \
        "PURCHOFF" /* 0x227 */, "PURCHON" /* 0x228 */, "RETURNOF" /* 0x229 */, "RETURNON" /* 0x22A */,                 \
        "EDITWNDO" /* 0x22B */, "BIGSCRNL" /* 0x22C */, "BIGSCRNR" /* 0x22D */, "SUBTITLE" /* 0x22E */,                \
        "BGRSCRNL" /* 0x22F */, "BGRSCRNR" /* 0x230 */, "BLDMRK1" /* 0x231 */, "BLDMRK2" /* 0x232 */,                  \
        "BLDMRK3" /* 0x233 */, "BLDMRK4" /* 0x234 */, "BLDMRK5" /* 0x235 */, "HIDDNPTR" /* 0x236 */,                   \
        "HANDPTR" /* 0x237 */, "CONDLITE" /* 0x238 */, "FUELLITE" /* 0x239 */, "AMMOLITE" /* 0x23A */,                 \
        "CARGOLIT" /* 0x23B */, "CLOSED" /* 0x23C */, "ARROW_N" /* 0x23D */, "ARROW_NE" /* 0x23E */,                   \
        "ARROW_E" /* 0x23F */, "ARROW_SE" /* 0x240 */, "ARROW_S" /* 0x241 */, "ARROW_SW" /* 0x242 */,                  \
        "ARROW_W" /* 0x243 */, "ARROW_NW" /* 0x244 */, "MAP_PTR" /* 0x245 */, "MINI_PTR" /* 0x246 */,                  \
        "MINI_X" /* 0x247 */, "MINI_X2" /* 0x248 */, "FRND_FIX" /* 0x249 */, "FRND_XFR" /* 0x24A */,                   \
        "FRND_LOD" /* 0x24B */, "FRND_FUE" /* 0x24C */, "FRND_PTR" /* 0x24D */, "ENMY_PTR" /* 0x24E */,                \
        "PTR_FTRG" /* 0x24F */, "WAY_PTR" /* 0x250 */, "GROUPPTR" /* 0x251 */, "ACTVTPTR" /* 0x252 */,                 \
        "PTR_RLD" /* 0x253 */, "STEALPTR" /* 0x254 */, "DISBLPTR" /* 0x255 */, "PTR_PATH" /* 0x256 */,                 \
        "PTR_HELP" /* 0x257 */, "ZOOMPNL1" /* 0x258 */, "ZOOMPNL2" /* 0x259 */, "ZOOMPNL3" /* 0x25A */,                \
        "ZOOMPNL4" /* 0x25B */, "ZOOMPNL5" /* 0x25C */, "ZOOMPNL6" /* 0x25D */, "ZOOMPNL7" /* 0x25E */,                \
        "ZOOMPTR" /* 0x25F */, "UNIT_GO" /* 0x260 */, "UNIT_NGO" /* 0x261 */, "LIGHTOFF" /* 0x262 */,                  \
        "LIGHTON" /* 0x263 */, "I_HRDATK" /* 0x264 */, "I_ATTACK" /* 0x265 */, "I_SHOTS" /* 0x266 */,                  \
        "I_RANGE" /* 0x267 */, "I_AMMO" /* 0x268 */, "I_ARMOR" /* 0x269 */, "I_SFTARM" /* 0x26A */,                    \
        "I_CHARGE" /* 0x26B */, "I_HITS" /* 0x26C */, "I_SCAN" /* 0x26D */, "I_SPEED" /* 0x26E */,                     \
        "I_FUEL" /* 0x26F */, "I_RAW" /* 0x270 */, "I_RAWE" /* 0x271 */, "I_GOLD" /* 0x272 */, "I_GOLDE" /* 0x273 */,  \
        "I_POWER" /* 0x274 */, "I_LIFE" /* 0x275 */, "SI_HITSB" /* 0x276 */, "EI_HITSB" /* 0x277 */,                   \
        "SI_HITSY" /* 0x278 */, "EI_HITSY" /* 0x279 */, "SI_HITSR" /* 0x27A */, "EI_HITSR" /* 0x27B */,                \
        "SI_AMMO" /* 0x27C */, "EI_AMMO" /* 0x27D */, "SI_RAW" /* 0x27E */, "EI_RAW" /* 0x27F */,                      \
        "SI_FUEL" /* 0x280 */, "EI_FUEL" /* 0x281 */, "SI_GOLD" /* 0x282 */, "EI_GOLD" /* 0x283 */,                    \
        "SI_LAND" /* 0x284 */, "EI_LAND" /* 0x285 */, "SI_SEA" /* 0x286 */, "EI_SEA" /* 0x287 */,                      \
        "SI_AIR" /* 0x288 */, "EI_AIR" /* 0x289 */, "SI_WORK" /* 0x28A */, "EI_WORK" /* 0x28B */,                      \
        "SI_SPEED" /* 0x28C */, "EI_SPEED" /* 0x28D */, "SI_SHOTS" /* 0x28E */, "EI_SHOTS" /* 0x28F */,                \
        "SI_POWER" /* 0x290 */, "EI_POWER" /* 0x291 */, "IL_SPEED" /* 0x292 */, "IL_SHOTS" /* 0x293 */,                \
        "IL_DSBLD" /* 0x294 */, "LIPS" /* 0x295 */, "I_CMPLX" /* 0x296 */, "BUY_OFF" /* 0x297 */,                      \
        "BUY_ON" /* 0x298 */, "MENU_OFF" /* 0x299 */, "MENU_ON" /* 0x29A */, "REPT_OFF" /* 0x29B */,                   \
        "REPT_ON" /* 0x29C */, "STAT_OFF" /* 0x29D */, "STAT_ON" /* 0x29E */, "RANG_OFF" /* 0x29F */,                  \
        "RANG_ON" /* 0x2A0 */, "VISN_OFF" /* 0x2A1 */, "VISN_ON" /* 0x2A2 */, "REDY_OFF" /* 0x2A3 */,                  \
        "REDY_ON" /* 0x2A4 */, "TRGT_OFF" /* 0x2A5 */, "TRGT_ON" /* 0x2A6 */, "FIND_OFF" /* 0x2A7 */,                  \
        "FIND_ON" /* 0x2A8 */, "CHAT_OFF" /* 0x2A9 */, "CHAT_ON" /* 0x2AA */, "GOAL_OFF" /* 0x2AB */,                  \
        "GOAL_ON" /* 0x2AC */, "PREF_OFF" /* 0x2AD */, "PREF_ON" /* 0x2AE */, "SYSM_OFF" /* 0x2AF */,                  \
        "SYSM_ON" /* 0x2B0 */, "FILES_OF" /* 0x2B1 */, "FILES_ON" /* 0x2B2 */, "SURV_OFF" /* 0x2B3 */,                 \
        "SURV_ON" /* 0x2B4 */, "GRID_OFF" /* 0x2B5 */, "GRID_ON" /* 0x2B6 */, "NAMES_UP" /* 0x2B7 */,                  \
        "NAMES_DN" /* 0x2B8 */, "CHECKED" /* 0x2B9 */, "UNCHKED" /* 0x2BA */, "BLANK_UP" /* 0x2BB */,                  \
        "BLANK_DN" /* 0x2BC */, "SBLNK_UP" /* 0x2BD */, "SBLNK_DN" /* 0x2BE */, "OBAR_UP" /* 0x2BF */,                 \
        "OBAR_DN" /* 0x2C0 */, "HELP_OF" /* 0x2C1 */, "HELP_ON" /* 0x2C2 */, "UDONE_OF" /* 0x2C3 */,                   \
        "UDONE_ON" /* 0x2C4 */, "MIN2X_OF" /* 0x2C5 */, "MIN2X_ON" /* 0x2C6 */, "MINFL_OF" /* 0x2C7 */,                \
        "MINFL_ON" /* 0x2C8 */, "AMMO_OF" /* 0x2C9 */, "AMMO_ON" /* 0x2CA */, "HITS_OF" /* 0x2CB */,                   \
        "HITS_ON" /* 0x2CC */, "COLOR_OF" /* 0x2CD */, "COLOR_ON" /* 0x2CE */, "PAUSE_OF" /* 0x2CF */,                 \
        "PAUSE_ON" /* 0x2D0 */, "PLAY_OF" /* 0x2D1 */, "PLAY_ON" /* 0x2D2 */, "LOCK_OF" /* 0x2D3 */,                   \
        "LOCK_ON" /* 0x2D4 */, "CLN0LOGO" /* 0x2D5 */, "CLN1LOGO" /* 0x2D6 */, "CLN2LOGO" /* 0x2D7 */,                 \
        "CLN3LOGO" /* 0x2D8 */, "CLN4LOGO" /* 0x2D9 */, "CLN5LOGO" /* 0x2DA */, "CLN6LOGO" /* 0x2DB */,                \
        "CLN7LOGO" /* 0x2DC */, "CLN8LOGO" /* 0x2DD */, "D_DEFALT" /* 0x2DE */, "D_LRGBLD" /* 0x2DF */,                \
        "D_SMLBLD" /* 0x2E0 */, "D_MOBILE" /* 0x2E1 */, "D_FIRING" /* 0x2E2 */, "D_RADAR" /* 0x2E3 */,                 \
        "D_ANTIAI" /* 0x2E4 */, "D_FIXED" /* 0x2E5 */, "D_TANK" /* 0x2E6 */, "D_ALTANK" /* 0x2E7 */,                   \
        "D_SP_FLK" /* 0x2E8 */, "D_UEXPLD" /* 0x2E9 */, "D_SEXPLD" /* 0x2EA */, "D_BEXPLD" /* 0x2EB */,                \
        "D_SMOKE" /* 0x2EC */, "D_BUBBLE" /* 0x2ED */, "D_LRGRBL" /* 0x2EE */, "D_SMLRBL" /* 0x2EF */,                 \
        "D_LRGSLA" /* 0x2F0 */, "D_AWAC" /* 0x2F1 */, "D_AMPHIB" /* 0x2F2 */, "D_BATTLS" /* 0x2F3 */,                  \
        "D_BRIDGE" /* 0x2F4 */, "D_COMMAN" /* 0x2F5 */, "D_INFANT" /* 0x2F6 */, "D_TORPDO" /* 0x2F7 */,                \
        "D_ALNMSL" /* 0x2F8 */, "D_ALNPBL" /* 0x2F9 */, "D_ESCORT" /* 0x2FA */, "D_MINING" /* 0x2FB */,                \
        "D_SCANNR" /* 0x2FC */, "D_SUB" /* 0x2FD */, "PNLSEQ_1" /* 0x2FE */, "PNLSEQ_2" /* 0x2FF */,                   \
        "PNLSEQ_3" /* 0x300 */, "PNLSEQ_4" /* 0x301 */, "PNLSEQ_5" /* 0x302 */, "BPNLSQ_1" /* 0x303 */,                \
        "BPNLSQ_2" /* 0x304 */, "BPNLSQ_3" /* 0x305 */, "BPNLSQ_4" /* 0x306 */, "PANELTOP" /* 0x307 */,                \
        "PANELBTM" /* 0x308 */, "CH_HUM_U" /* 0x309 */, "CH_HUM_D" /* 0x30A */, "CH_CMP_U" /* 0x30B */,                \
        "CH_CMP_D" /* 0x30C */, "CH_NON_U" /* 0x30D */, "CH_NON_D" /* 0x30E */, "CH_UP_UP" /* 0x30F */,                \
        "CH_UP_DN" /* 0x310 */, "CH_DWN_U" /* 0x311 */, "CH_DWN_D" /* 0x312 */, "CH_QST_U" /* 0x313 */,                \
        "CH_QST_D" /* 0x314 */, "CH_TM1_U" /* 0x315 */, "CH_TM1_D" /* 0x316 */, "CH_TM2_U" /* 0x317 */,                \
        "CH_TM2_D" /* 0x318 */, "CH_TM3_U" /* 0x319 */, "CH_TM3_D" /* 0x31A */, "CH_TM4_U" /* 0x31B */,                \
        "CH_TM4_D" /* 0x31C */, "M_CLAN_U" /* 0x31D */, "M_CLAN_D" /* 0x31E */, "CH_CN1_U" /* 0x31F */,                \
        "CH_CN1_D" /* 0x320 */, "CH_CN2_U" /* 0x321 */, "CH_CN2_D" /* 0x322 */, "CH_CN3_U" /* 0x323 */,                \
        "CH_CN3_D" /* 0x324 */, "CH_CN4_U" /* 0x325 */, "CH_CN4_D" /* 0x326 */, "CH_CN5_U" /* 0x327 */,                \
        "CH_CN5_D" /* 0x328 */, "CH_CN6_U" /* 0x329 */, "CH_CN6_D" /* 0x32A */, "CH_CN7_U" /* 0x32B */,                \
        "CH_CN7_D" /* 0x32C */, "CH_CN8_U" /* 0x32D */, "CH_CN8_D" /* 0x32E */, "PL_NXT_U" /* 0x32F */,                \
        "PL_NXT_D" /* 0x330 */, "PL_LST_U" /* 0x331 */, "PL_LST_D" /* 0x332 */, "MNUBTN1U" /* 0x333 */,                \
        "MNUBTN1D" /* 0x334 */, "MNUBTN2U" /* 0x335 */, "MNUBTN2D" /* 0x336 */, "MNUBTN3U" /* 0x337 */,                \
        "MNUBTN3D" /* 0x338 */, "MNUBTN4U" /* 0x339 */, "MNUBTN4D" /* 0x33A */, "MNUBTN5U" /* 0x33B */,                \
        "MNUBTN5D" /* 0x33C */, "MNUBTN6U" /* 0x33D */, "MNUBTN6D" /* 0x33E */, "MNULAROU" /* 0x33F */,                \
        "MNULAROD" /* 0x340 */, "MNURAROU" /* 0x341 */, "MNURAROD" /* 0x342 */, "MNUUAROU" /* 0x343 */,                \
        "MNUUAROD" /* 0x344 */, "MNUDAROU" /* 0x345 */, "MNUDAROD" /* 0x346 */, "I_TRANSP" /* 0x347 */,                \
        "I_POWSTN" /* 0x348 */, "I_POWGEN" /* 0x349 */, "I_BARRCK" /* 0x34A */, "I_SHIELD" /* 0x34B */,                \
        "I_RADAR" /* 0x34C */, "I_SMSTOR" /* 0x34D */, "I_SMFUEL" /* 0x34E */, "I_SMVLT" /* 0x34F */,                  \
        "I_DEPOT" /* 0x350 */, "I_HANGAR" /* 0x351 */, "I_DOCK" /* 0x352 */, "I_CONNEC" /* 0x353 */,                   \
        "I_ROAD" /* 0x354 */, "I_LANDPD" /* 0x355 */, "I_SHIPYD" /* 0x356 */, "I_LGHTPL" /* 0x357 */,                  \
        "I_HVYPLT" /* 0x358 */, "I_LIFESP" /* 0x359 */, "I_AIRPLT" /* 0x35A */, "I_HABITA" /* 0x35B */,                \
        "I_RESEAR" /* 0x35C */, "I_GREENH" /* 0x35D */, "I_RECCTR" /* 0x35E */, "I_TRNHLL" /* 0x35F */,                \
        "I_WATER" /* 0x360 */, "I_GUNTUR" /* 0x361 */, "I_FXAA" /* 0x362 */, "I_ARTYTR" /* 0x363 */,                   \
        "I_FXROCK" /* 0x364 */, "I_BLOCK" /* 0x365 */, "I_BRIDGE" /* 0x366 */, "I_MINING" /* 0x367 */,                 \
        "I_LANDMN" /* 0x368 */, "I_SEAMIN" /* 0x369 */, "I_MASTER" /* 0x36A */, "I_CONTRC" /* 0x36B */,                \
        "I_SCOUT" /* 0x36C */, "I_TANK" /* 0x36D */, "I_ARTY" /* 0x36E */, "I_ROCKET" /* 0x36F */,                     \
        "I_MISSIL" /* 0x370 */, "I_AA" /* 0x371 */, "I_MNELAY" /* 0x372 */, "I_SURVEY" /* 0x373 */,                    \
        "I_SCANNR" /* 0x374 */, "I_SPLYTR" /* 0x375 */, "I_GOLDTR" /* 0x376 */, "I_ENGINR" /* 0x377 */,                \
        "I_BULLDZ" /* 0x378 */, "I_REPAIR" /* 0x379 */, "I_FUELTR" /* 0x37A */, "I_COLNST" /* 0x37B */,                \
        "I_COMMAN" /* 0x37C */, "I_INFANT" /* 0x37D */, "I_ESCORT" /* 0x37E */, "I_CORVET" /* 0x37F */,                \
        "I_GUNBT" /* 0x380 */, "I_SUB" /* 0x381 */, "I_SEATRN" /* 0x382 */, "I_MSLCR" /* 0x383 */,                     \
        "I_SEAMNL" /* 0x384 */, "I_CARGOS" /* 0x385 */, "I_FIGHTR" /* 0x386 */, "I_BOMBER" /* 0x387 */,                \
        "I_AIRTRN" /* 0x388 */, "I_AWAC" /* 0x389 */, "I_JUGGER" /* 0x38A */, "I_ALNTAN" /* 0x38B */,                  \
        "I_ALNASG" /* 0x38C */, "I_ALNPLA" /* 0x38D */, "MEM_END" /* 0x38E */, "V_START" /* 0x38F */,                  \
        "V_M001" /* 0x390 */, "V_F001" /* 0x391 */, "V_M005" /* 0x392 */, "V_F005" /* 0x393 */, "V_M006" /* 0x394 */,  \
        "V_F006" /* 0x395 */, "V_M004" /* 0x396 */, "V_F004" /* 0x397 */, "V_M284" /* 0x398 */, "V_F284" /* 0x399 */,  \
        "V_M138" /* 0x39A */, "V_F138" /* 0x39B */, "V_M142" /* 0x39C */, "V_F142" /* 0x39D */, "V_M145" /* 0x39E */,  \
        "V_F145" /* 0x39F */, "V_M150" /* 0x3A0 */, "V_F150" /* 0x3A1 */, "V_M151" /* 0x3A2 */, "V_F151" /* 0x3A3 */,  \
        "V_M265" /* 0x3A4 */, "V_F265" /* 0x3A5 */, "V_M154" /* 0x3A6 */, "V_F154" /* 0x3A7 */, "V_M155" /* 0x3A8 */,  \
        "V_F155" /* 0x3A9 */, "V_M158" /* 0x3AA */, "V_F158" /* 0x3AB */, "V_M162" /* 0x3AC */, "V_F162" /* 0x3AD */,  \
        "V_M164" /* 0x3AE */, "V_F164" /* 0x3AF */, "V_M163" /* 0x3B0 */, "V_F163" /* 0x3B1 */, "V_M165" /* 0x3B2 */,  \
        "V_F165" /* 0x3B3 */, "V_M166" /* 0x3B4 */, "V_F166" /* 0x3B5 */, "V_M169" /* 0x3B6 */, "V_F169" /* 0x3B7 */,  \
        "V_M171" /* 0x3B8 */, "V_F171" /* 0x3B9 */, "V_M181" /* 0x3BA */, "V_F181" /* 0x3BB */, "V_M182" /* 0x3BC */,  \
        "V_F182" /* 0x3BD */, "V_M186" /* 0x3BE */, "V_F186" /* 0x3BF */, "V_M187" /* 0x3C0 */, "V_F187" /* 0x3C1 */,  \
        "V_M191" /* 0x3C2 */, "V_F191" /* 0x3C3 */, "V_M192" /* 0x3C4 */, "V_F192" /* 0x3C5 */, "V_M196" /* 0x3C6 */,  \
        "V_F196" /* 0x3C7 */, "V_M198" /* 0x3C8 */, "V_F198" /* 0x3C9 */, "V_START2" /* 0x3CA */,                      \
        "V_M007" /* 0x3CB */, "V_F007" /* 0x3CC */, "V_M010" /* 0x3CD */, "V_F010" /* 0x3CE */, "V_M012" /* 0x3CF */,  \
        "V_F012" /* 0x3D0 */, "V_M239" /* 0x3D1 */, "V_F239" /* 0x3D2 */, "V_M242" /* 0x3D3 */, "V_F242" /* 0x3D4 */,  \
        "V_M243" /* 0x3D5 */, "V_F243" /* 0x3D6 */, "V_M244" /* 0x3D7 */, "V_F244" /* 0x3D8 */, "V_M247" /* 0x3D9 */,  \
        "V_F247" /* 0x3DA */, "V_M249" /* 0x3DB */, "V_F249" /* 0x3DC */, "V_START3" /* 0x3DD */,                      \
        "V_M049" /* 0x3DE */, "V_F049" /* 0x3DF */, "V_M050" /* 0x3E0 */, "V_F050" /* 0x3E1 */, "V_M085" /* 0x3E2 */,  \
        "V_F085" /* 0x3E3 */, "V_M089" /* 0x3E4 */, "V_F089" /* 0x3E5 */, "V_M094" /* 0x3E6 */, "V_F094" /* 0x3E7 */,  \
        "V_M095" /* 0x3E8 */, "V_F095" /* 0x3E9 */, "V_M201" /* 0x3EA */, "V_F201" /* 0x3EB */, "V_M210" /* 0x3EC */,  \
        "V_F210" /* 0x3ED */, "V_M211" /* 0x3EE */, "V_F211" /* 0x3EF */, "V_M219" /* 0x3F0 */, "V_F219" /* 0x3F1 */,  \
        "V_M220" /* 0x3F2 */, "V_F220" /* 0x3F3 */, "V_M224" /* 0x3F4 */, "V_F224" /* 0x3F5 */, "V_M229" /* 0x3F6 */,  \
        "V_F229" /* 0x3F7 */, "V_M230" /* 0x3F8 */, "V_F230" /* 0x3F9 */, "V_M231" /* 0x3FA */, "V_F231" /* 0x3FB */,  \
        "V_M232" /* 0x3FC */, "V_F232" /* 0x3FD */, "V_M255" /* 0x3FE */, "V_F255" /* 0x3FF */, "V_M256" /* 0x400 */,  \
        "V_F256" /* 0x401 */, "V_M234" /* 0x402 */, "V_F234" /* 0x403 */, "V_M236" /* 0x404 */, "V_F236" /* 0x405 */,  \
        "V_M250" /* 0x406 */, "V_F250" /* 0x407 */, "V_M251" /* 0x408 */, "V_F251" /* 0x409 */, "V_M070" /* 0x40A */,  \
        "V_F070" /* 0x40B */, "V_M071" /* 0x40C */, "V_F071" /* 0x40D */, "V_START4" /* 0x40E */,                      \
        "V_M270" /* 0x40F */, "V_F270" /* 0x410 */, "V_M271" /* 0x411 */, "V_F271" /* 0x412 */, "V_M279" /* 0x413 */,  \
        "V_F279" /* 0x414 */, "V_M280" /* 0x415 */, "V_F280" /* 0x416 */, "V_M281" /* 0x417 */, "V_F281" /* 0x418 */,  \
        "V_M282" /* 0x419 */, "V_F282" /* 0x41A */, "V_M025" /* 0x41B */, "V_F025" /* 0x41C */, "V_M026" /* 0x41D */,  \
        "V_F026" /* 0x41E */, "V_M031" /* 0x41F */, "V_F031" /* 0x420 */, "V_M032" /* 0x421 */, "V_F032" /* 0x422 */,  \
        "V_M037" /* 0x423 */, "V_F037" /* 0x424 */, "V_M038" /* 0x425 */, "V_F038" /* 0x426 */, "V_M043" /* 0x427 */,  \
        "V_F043" /* 0x428 */, "V_M044" /* 0x429 */, "V_F044" /* 0x42A */, "V_M053" /* 0x42B */, "V_F053" /* 0x42C */,  \
        "V_M057" /* 0x42D */, "V_F057" /* 0x42E */, "V_M061" /* 0x42F */, "V_F061" /* 0x430 */, "V_M066" /* 0x431 */,  \
        "V_F066" /* 0x432 */, "V_M075" /* 0x433 */, "V_F075" /* 0x434 */, "V_M080" /* 0x435 */, "V_F080" /* 0x436 */,  \
        "V_M081" /* 0x437 */, "V_F081" /* 0x438 */, "V_M093" /* 0x439 */, "V_F093" /* 0x43A */, "V_M098" /* 0x43B */,  \
        "V_F098" /* 0x43C */, "V_M103" /* 0x43D */, "V_F103" /* 0x43E */, "V_M108" /* 0x43F */, "V_F108" /* 0x440 */,  \
        "V_M113" /* 0x441 */, "V_F113" /* 0x442 */, "V_M118" /* 0x443 */, "V_F118" /* 0x444 */, "V_M122" /* 0x445 */,  \
        "V_F122" /* 0x446 */, "V_M126" /* 0x447 */, "V_F126" /* 0x448 */, "V_M130" /* 0x449 */, "V_F130" /* 0x44A */,  \
        "V_M206" /* 0x44B */, "V_F206" /* 0x44C */, "V_M207" /* 0x44D */, "V_F207" /* 0x44E */, "V_M215" /* 0x44F */,  \
        "V_F215" /* 0x450 */, "V_M216" /* 0x451 */, "V_F216" /* 0x452 */, "V_M217" /* 0x453 */, "V_F217" /* 0x454 */,  \
        "V_START5" /* 0x455 */, "V_M272" /* 0x456 */, "V_F272" /* 0x457 */, "V_M273" /* 0x458 */,                      \
        "V_F273" /* 0x459 */, "V_M275" /* 0x45A */, "V_F275" /* 0x45B */, "V_M276" /* 0x45C */, "V_F276" /* 0x45D */,  \
        "V_M278" /* 0x45E */, "V_F278" /* 0x45F */, "V_M176" /* 0x460 */, "V_F176" /* 0x461 */, "V_M177" /* 0x462 */,  \
        "V_F177" /* 0x463 */, "V_M283" /* 0x464 */, "V_F283" /* 0x465 */, "V_M013" /* 0x466 */, "V_F013" /* 0x467 */,  \
        "V_END" /* 0x468 */, "F_COMMT" /* 0x469 */, "F_POWERS" /* 0x46A */, "F_BARRAC" /* 0x46B */,                    \
        "F_SHIELD" /* 0x46C */, "F_RADAR" /* 0x46D */, "F_DEPOT" /* 0x46E */, "F_HANGAR" /* 0x46F */,                  \
        "F_DOCK" /* 0x470 */, "F_ADUMP" /* 0x471 */, "F_FDUMP" /* 0x472 */, "F_GOLDSM" /* 0x473 */,                    \
        "F_POWGEN" /* 0x474 */, "F_CNCT4W" /* 0x475 */, "F_ROAD" /* 0x476 */, "F_LANDPA" /* 0x477 */,                  \
        "F_SHIPYA" /* 0x478 */, "F_LIGHTP" /* 0x479 */, "F_LANDPL" /* 0x47A */, "F_SUPRTP" /* 0x47B */,                \
        "F_AIRPLT" /* 0x47C */, "F_HABITA" /* 0x47D */, "F_RESEAR" /* 0x47E */, "F_GREENH" /* 0x47F */,                \
        "F_RECCEN" /* 0x480 */, "F_TRAINH" /* 0x481 */, "F_WTRPLT" /* 0x482 */, "F_GUNTUR" /* 0x483 */,                \
        "F_ANTIAI" /* 0x484 */, "F_ARTYTR" /* 0x485 */, "F_ANTIMS" /* 0x486 */, "F_BLOCK" /* 0x487 */,                 \
        "F_BRIDGE" /* 0x488 */, "F_MINING" /* 0x489 */, "F_LANDMI" /* 0x48A */, "F_SEAMIN" /* 0x48B */,                \
        "F_MASTER" /* 0x48C */, "F_CONSTR" /* 0x48D */, "F_SCOUT" /* 0x48E */, "F_TANK" /* 0x48F */,                   \
        "F_ARTILL" /* 0x490 */, "F_ROCKTL" /* 0x491 */, "F_MISSLL" /* 0x492 */, "F_FLAK" /* 0x493 */,                  \
        "F_MINELA" /* 0x494 */, "F_SURVEY" /* 0x495 */, "F_SCANNE" /* 0x496 */, "F_SPLYTR" /* 0x497 */,                \
        "F_GOLDTR" /* 0x498 */, "F_ENGINE" /* 0x499 */, "F_BULLDO" /* 0x49A */, "F_REPAIR" /* 0x49B */,                \
        "F_FUELTR" /* 0x49C */, "F_CLNTRA" /* 0x49D */, "F_COMMAN" /* 0x49E */, "F_INFANT" /* 0x49F */,                \
        "F_FASTBO" /* 0x4A0 */, "F_CORVET" /* 0x4A1 */, "F_BATTLS" /* 0x4A2 */, "F_SUBMAR" /* 0x4A3 */,                \
        "F_SEATRA" /* 0x4A4 */, "F_MSSLBO" /* 0x4A5 */, "F_SEAMNL" /* 0x4A6 */, "F_CARGOS" /* 0x4A7 */,                \
        "F_FIGHTE" /* 0x4A8 */, "F_BOMBER" /* 0x4A9 */, "F_AIRTRA" /* 0x4AA */, "F_AWAC" /* 0x4AB */,                  \
        "F_JUGGRN" /* 0x4AC */, "F_ALNTAN" /* 0x4AD */, "F_ALNASG" /* 0x4AE */, "F_ALNPLA" /* 0x4AF */,                \
        "TRANSFLC" /* 0x4B0 */, "FILESFLC" /* 0x4B1 */, "F_ICE" /* 0x4B2 */, "F_SAND" /* 0x4B3 */,                     \
        "F_STARS" /* 0x4B4 */, "FILE_BUP" /* 0x4B5 */, "FILE_BDN" /* 0x4B6 */, "FNAME_UP" /* 0x4B7 */,                 \
        "FNAME_DN" /* 0x4B8 */, "FTYPE_UP" /* 0x4B9 */, "FTYPE_DN" /* 0x4BA */, "FDESC_UP" /* 0x4BB */,                \
        "FDESC_DN" /* 0x4BC */, "LOAD_BUP" /* 0x4BD */, "LOAD_BDN" /* 0x4BE */, "SAVE_BUP" /* 0x4BF */,                \
        "SAVE_BDN" /* 0x4C0 */, "CNCL_BUP" /* 0x4C1 */, "CNCL_BDN" /* 0x4C2 */, "QUIT_BUP" /* 0x4C3 */,                \
        "QUIT_BDN" /* 0x4C4 */, "FILE1_UP" /* 0x4C5 */, "FILE2_UP" /* 0x4C6 */, "FILE3_UP" /* 0x4C7 */,                \
        "FILE4_UP" /* 0x4C8 */, "FILE5_UP" /* 0x4C9 */, "FILE6_UP" /* 0x4CA */, "FILE7_UP" /* 0x4CB */,                \
        "FILE8_UP" /* 0x4CC */, "FILE9_UP" /* 0x4CD */, "FILE10UP" /* 0x4CE */, "FILE1_DN" /* 0x4CF */,                \
        "FILE2_DN" /* 0x4D0 */, "FILE3_DN" /* 0x4D1 */, "FILE4_DN" /* 0x4D2 */, "FILE5_DN" /* 0x4D3 */,                \
        "FILE6_DN" /* 0x4D4 */, "FILE7_DN" /* 0x4D5 */, "FILE8_DN" /* 0x4D6 */, "FILE9_DN" /* 0x4D7 */,                \
        "FILE10DN" /* 0x4D8 */, "INTROSND" /* 0x4D9 */, "ENEMBEEP" /* 0x4DA */, "RADRPING" /* 0x4DB */,                \
        "ERRDING" /* 0x4DC */, "MBUTT0" /* 0x4DD */, "MENUOP" /* 0x4DE */, "NHUMN0" /* 0x4DF */, "NCOMP0" /* 0x4E0 */, \
        "NNONE0" /* 0x4E1 */, "NCLAN0" /* 0x4E2 */, "NOPTI0" /* 0x4E3 */, "NCANC0" /* 0x4E4 */, "NHELP0" /* 0x4E5 */,  \
        "NDONE0" /* 0x4E6 */, "CCHOS0" /* 0x4E7 */, "CCRIM0" /* 0x4E8 */, "CVONG0" /* 0x4E9 */, "CAYER0" /* 0x4EA */,  \
        "CMUSA0" /* 0x4EB */, "CSACR0" /* 0x4EC */, "CKNIG0" /* 0x4ED */, "CAXIS0" /* 0x4EE */, "CRAND0" /* 0x4EF */,  \
        "CCANC0" /* 0x4F0 */, "CHELP0" /* 0x4F1 */, "CDONE0" /* 0x4F2 */, "PWINO0" /* 0x4F3 */, "PWINC0" /* 0x4F4 */,  \
        "PSELW0" /* 0x4F5 */, "PSELM0" /* 0x4F6 */, "PRAND0" /* 0x4F7 */, "PCANC0" /* 0x4F8 */, "PHELP0" /* 0x4F9 */,  \
        "PDONE0" /* 0x4FA */, "KWINO0" /* 0x4FB */, "KWINC0" /* 0x4FC */, "KSELE0" /* 0x4FD */, "KBUY0" /* 0x4FE */,   \
        "KCARG0" /* 0x4FF */, "KHELP0" /* 0x500 */, "CBOPE0" /* 0x501 */, "CBCLO0" /* 0x502 */, "CBSEL0" /* 0x503 */,  \
        "CBBUI0" /* 0x504 */, "CBCAN0" /* 0x505 */, "CBHLP0" /* 0x506 */, "CBDON0" /* 0x507 */, "IOPEN0" /* 0x508 */,  \
        "ICLOS0" /* 0x509 */, "IZOOM0" /* 0x50A */, "ISTAT0" /* 0x50B */, "ICOLO0" /* 0x50C */, "IHITS0" /* 0x50D */,  \
        "IAMMO0" /* 0x50E */, "IRANG0" /* 0x50F */, "IVISI0" /* 0x510 */, "IGRID0" /* 0x511 */, "ISURV0" /* 0x512 */,  \
        "INAME0" /* 0x513 */, "FOPEN" /* 0x514 */, "FCLOS" /* 0x515 */, "FBUBB" /* 0x516 */, "FSAVE" /* 0x517 */,      \
        "FQUIT" /* 0x518 */, "FCANC" /* 0x519 */, "FHELP" /* 0x51A */, "FLOAD" /* 0x51B */, "FXS_STRT" /* 0x51C */,    \
        "GEN_IDLE" /* 0x51D */, "WGN_IDLE" /* 0x51E */, "GEN_DRVE" /* 0x51F */, "WGN_DRVE" /* 0x520 */,                \
        "GEN_STOP" /* 0x521 */, "WGN_STOP" /* 0x522 */, "GEN_XFRM" /* 0x523 */, "GEN_BLDG" /* 0x524 */,                \
        "GEN_SHNK" /* 0x525 */, "GEN_XPND" /* 0x526 */, "GEN_TRRT" /* 0x527 */, "GEN_FIRE" /* 0x528 */,                \
        "GEN_HIT" /* 0x529 */, "GEN_XPLD" /* 0x52A */, "GEN_PRCS" /* 0x52B */, "GEN_PRCE" /* 0x52C */,                 \
        "GEN_LAND" /* 0x52D */, "GEN_TAKE" /* 0x52E */, "MONOP10" /* 0x52F */, "MONOP15" /* 0x530 */,                  \
        "MONOP16" /* 0x531 */, "MONOP17" /* 0x532 */, "MONOP18" /* 0x533 */, "POWST10" /* 0x534 */,                    \
        "POWST15" /* 0x535 */, "POWST16" /* 0x536 */, "POWST17" /* 0x537 */, "POWST18" /* 0x538 */,                    \
        "POWGN10" /* 0x539 */, "POWGN15" /* 0x53A */, "POWGN16" /* 0x53B */, "POWGN17" /* 0x53C */,                    \
        "POWGN18" /* 0x53D */, "BARRA10" /* 0x53E */, "BARRA15" /* 0x53F */, "BARRA16" /* 0x540 */,                    \
        "BARRA17" /* 0x541 */, "BARRA18" /* 0x542 */, "GOLDR10" /* 0x543 */, "GOLDR15" /* 0x544 */,                    \
        "GOLDR16" /* 0x545 */, "GOLDR17" /* 0x546 */, "GOLDR18" /* 0x547 */, "RADAR13" /* 0x548 */,                    \
        "RADAR15" /* 0x549 */, "RADAR16" /* 0x54A */, "SSTOR15" /* 0x54B */, "SSTOR16" /* 0x54C */,                    \
        "SSTOR17" /* 0x54D */, "SFUEL15" /* 0x54E */, "SFUEL16" /* 0x54F */, "SFUEL17" /* 0x550 */,                    \
        "SGOLD15" /* 0x551 */, "SGOLD16" /* 0x552 */, "SGOLD17" /* 0x553 */, "DEPOT10" /* 0x554 */,                    \
        "DEPOT15" /* 0x555 */, "DEPOT16" /* 0x556 */, "DEPOT17" /* 0x557 */, "DEPOT18" /* 0x558 */,                    \
        "HANGR10" /* 0x559 */, "HANGR15" /* 0x55A */, "HANGR16" /* 0x55B */, "HANGR17" /* 0x55C */,                    \
        "HANGR18" /* 0x55D */, "DOCK10" /* 0x55E */, "DOCK15" /* 0x55F */, "DOCK16" /* 0x560 */, "DOCK17" /* 0x561 */, \
        "DOCK18" /* 0x562 */, "ROAD15" /* 0x563 */, "ROAD16" /* 0x564 */, "LPAD10" /* 0x565 */, "LPAD15" /* 0x566 */,  \
        "LPAD16" /* 0x567 */, "SUNIT10" /* 0x568 */, "SUNIT15" /* 0x569 */, "SUNIT16" /* 0x56A */,                     \
        "SUNIT17" /* 0x56B */, "SUNIT18" /* 0x56C */, "LVP10" /* 0x56D */, "LVP15" /* 0x56E */, "LVP16" /* 0x56F */,   \
        "LVP17" /* 0x570 */, "LVP18" /* 0x571 */, "HVP10" /* 0x572 */, "HVP15" /* 0x573 */, "HVP16" /* 0x574 */,       \
        "HVP17" /* 0x575 */, "HVP18" /* 0x576 */, "AUNIT10" /* 0x577 */, "AUNIT15" /* 0x578 */, "AUNIT16" /* 0x579 */, \
        "AUNIT17" /* 0x57A */, "AUNIT18" /* 0x57B */, "DORMI10" /* 0x57C */, "DORMI15" /* 0x57D */,                    \
        "DORMI16" /* 0x57E */, "DORMI17" /* 0x57F */, "DORMI18" /* 0x580 */, "RESEAR10" /* 0x581 */,                   \
        "RESEAR15" /* 0x582 */, "RESEAR16" /* 0x583 */, "RESEAR17" /* 0x584 */, "RESEAR18" /* 0x585 */,                \
        "ECOSP10" /* 0x586 */, "ECOSP15" /* 0x587 */, "ECOSP16" /* 0x588 */, "ECOSP17" /* 0x589 */,                    \
        "ECOSP18" /* 0x58A */, "TRAIN10" /* 0x58B */, "TRAIN15" /* 0x58C */, "TRAIN16" /* 0x58D */,                    \
        "TRAIN17" /* 0x58E */, "TRAIN18" /* 0x58F */, "WPLAT15" /* 0x590 */, "WPLAT16" /* 0x591 */,                    \
        "FGUN13" /* 0x592 */, "FGUN14" /* 0x593 */, "FGUN15" /* 0x594 */, "FGUN16" /* 0x595 */, "FANTI13" /* 0x596 */, \
        "FANTI14" /* 0x597 */, "FANTI15" /* 0x598 */, "FANTI16" /* 0x599 */, "FARTY13" /* 0x59A */,                    \
        "FARTY14" /* 0x59B */, "FARTY15" /* 0x59C */, "FARTY16" /* 0x59D */, "FROCK13" /* 0x59E */,                    \
        "FROCK14" /* 0x59F */, "FROCK15" /* 0x5A0 */, "FROCK16" /* 0x5A1 */, "BLOCK15" /* 0x5A2 */,                    \
        "BLOCK16" /* 0x5A3 */, "BRIDG15" /* 0x5A4 */, "BRIDG16" /* 0x5A5 */, "MSTAT10" /* 0x5A6 */,                    \
        "MSTAT15" /* 0x5A7 */, "MSTAT16" /* 0x5A8 */, "MSTAT17" /* 0x5A9 */, "MSTAT18" /* 0x5AA */,                    \
        "LMINE16" /* 0x5AB */, "CMINE16" /* 0x5AC */, "EMPTYLND" /* 0x5AD */, "EMPTYWTR" /* 0x5AE */,                  \
        "MASTR1" /* 0x5AF */, "MASTR5" /* 0x5B0 */, "MASTR7" /* 0x5B1 */, "MASTR9" /* 0x5B2 */, "MASTR15" /* 0x5B3 */, \
        "MASTR16" /* 0x5B4 */, "CONST1" /* 0x5B5 */, "CONST2" /* 0x5B6 */, "CONST5" /* 0x5B7 */, "CONST6" /* 0x5B8 */, \
        "CONST7" /* 0x5B9 */, "CONST8" /* 0x5BA */, "CONST10" /* 0x5BB */, "CONST15" /* 0x5BC */,                      \
        "CONST16" /* 0x5BD */, "SCOUT1" /* 0x5BE */, "SCOUT2" /* 0x5BF */, "SCOUT5" /* 0x5C0 */, "SCOUT6" /* 0x5C1 */, \
        "SCOUT7" /* 0x5C2 */, "SCOUT8" /* 0x5C3 */, "SCOUT14" /* 0x5C4 */, "SCOUT15" /* 0x5C5 */,                      \
        "SCOUT16" /* 0x5C6 */, "TANK1" /* 0x5C7 */, "TANK5" /* 0x5C8 */, "TANK7" /* 0x5C9 */, "TANK14" /* 0x5CA */,    \
        "TANK15" /* 0x5CB */, "TANK16" /* 0x5CC */, "ASGUN1" /* 0x5CD */, "ASGUN5" /* 0x5CE */, "ASGUN7" /* 0x5CF */,  \
        "ASGUN14" /* 0x5D0 */, "ASGUN15" /* 0x5D1 */, "ASGUN16" /* 0x5D2 */, "RLNCH1" /* 0x5D3 */,                     \
        "RLNCH5" /* 0x5D4 */, "RLNCH7" /* 0x5D5 */, "RLNCH14" /* 0x5D6 */, "RLNCH15" /* 0x5D7 */,                      \
        "RLNCH16" /* 0x5D8 */, "MSLNC1" /* 0x5D9 */, "MSLNC5" /* 0x5DA */, "MSLNC7" /* 0x5DB */,                       \
        "MSLNC14" /* 0x5DC */, "MSLNC15" /* 0x5DD */, "MSLNC16" /* 0x5DE */, "MANTI1" /* 0x5DF */,                     \
        "MANTI5" /* 0x5E0 */, "MANTI7" /* 0x5E1 */, "MANTI14" /* 0x5E2 */, "MANTI15" /* 0x5E3 */,                      \
        "MANTI16" /* 0x5E4 */, "MLAYER1" /* 0x5E5 */, "MLAYER5" /* 0x5E6 */, "MLAYER7" /* 0x5E7 */,                    \
        "MLAYER15" /* 0x5E8 */, "MLAYER16" /* 0x5E9 */, "MLAYER17" /* 0x5EA */, "MLAYER18" /* 0x5EB */,                \
        "SURVY1" /* 0x5EC */, "SURVY2" /* 0x5ED */, "SURVY5" /* 0x5EE */, "SURVY6" /* 0x5EF */, "SURVY7" /* 0x5F0 */,  \
        "SURVY8" /* 0x5F1 */, "SURVY15" /* 0x5F2 */, "SURVY16" /* 0x5F3 */, "SCAN1" /* 0x5F4 */, "SCAN5" /* 0x5F5 */,  \
        "SCAN7" /* 0x5F6 */, "SCAN15" /* 0x5F7 */, "SCAN16" /* 0x5F8 */, "MTRUK1" /* 0x5F9 */, "MTRUK5" /* 0x5FA */,   \
        "MTRUK7" /* 0x5FB */, "MTRUK15" /* 0x5FC */, "MTRUK16" /* 0x5FD */, "MTRUK17" /* 0x5FE */,                     \
        "GTRUK1" /* 0x5FF */, "GTRUK5" /* 0x600 */, "GTRUK7" /* 0x601 */, "GTRUK15" /* 0x602 */,                       \
        "GTRUK16" /* 0x603 */, "GTRUK17" /* 0x604 */, "ENGIN1" /* 0x605 */, "ENGIN2" /* 0x606 */,                      \
        "ENGIN5" /* 0x607 */, "ENGIN6" /* 0x608 */, "ENGIN7" /* 0x609 */, "ENGIN8" /* 0x60A */, "ENGIN10" /* 0x60B */, \
        "ENGIN15" /* 0x60C */, "ENGIN16" /* 0x60D */, "BULL1" /* 0x60E */, "BULL5" /* 0x60F */, "BULL7" /* 0x610 */,   \
        "BULL10" /* 0x611 */, "BULL15" /* 0x612 */, "BULL16" /* 0x613 */, "REPAIR1" /* 0x614 */,                       \
        "REPAIR5" /* 0x615 */, "REPAIR7" /* 0x616 */, "REPAIR15" /* 0x617 */, "REPAIR16" /* 0x618 */,                  \
        "REPAIR17" /* 0x619 */, "FTRUK1" /* 0x61A */, "FTRUK5" /* 0x61B */, "FTRUK7" /* 0x61C */,                      \
        "FTRUK15" /* 0x61D */, "FTRUK16" /* 0x61E */, "FTRUK17" /* 0x61F */, "APC1" /* 0x620 */, "APC2" /* 0x621 */,   \
        "APC5" /* 0x622 */, "APC6" /* 0x623 */, "APC7" /* 0x624 */, "APC8" /* 0x625 */, "APC15" /* 0x626 */,           \
        "APC16" /* 0x627 */, "APC17" /* 0x628 */, "APC18" /* 0x629 */, "INFIL5" /* 0x62A */, "INFIL14" /* 0x62B */,    \
        "INFIL15" /* 0x62C */, "INFIL16" /* 0x62D */, "INFIL17" /* 0x62E */, "INFAN5" /* 0x62F */,                     \
        "INFAN14" /* 0x630 */, "INFAN15" /* 0x631 */, "INFAN16" /* 0x632 */, "ESCRT2" /* 0x633 */,                     \
        "ESCRT6" /* 0x634 */, "ESCRT8" /* 0x635 */, "ESCRT14" /* 0x636 */, "ESCRT15" /* 0x637 */,                      \
        "ESCRT16" /* 0x638 */, "CORVT2" /* 0x639 */, "CORVT6" /* 0x63A */, "CORVT8" /* 0x63B */,                       \
        "CORVT14" /* 0x63C */, "CORVT15" /* 0x63D */, "CORVT16" /* 0x63E */, "GUNBT2" /* 0x63F */,                     \
        "GUNBT6" /* 0x640 */, "GUNBT8" /* 0x641 */, "GUNBT14" /* 0x642 */, "GUNBT15" /* 0x643 */,                      \
        "GUNBT16" /* 0x644 */, "SUB2" /* 0x645 */, "SUB6" /* 0x646 */, "SUB8" /* 0x647 */, "SUB14" /* 0x648 */,        \
        "SUB15" /* 0x649 */, "SUB16" /* 0x64A */, "STRANS2" /* 0x64B */, "STRANS6" /* 0x64C */, "STRANS8" /* 0x64D */, \
        "STRANS15" /* 0x64E */, "STRANS16" /* 0x64F */, "STRANS17" /* 0x650 */, "STRANS18" /* 0x651 */,                \
        "MSLCR2" /* 0x652 */, "MSLCR6" /* 0x653 */, "MSLCR8" /* 0x654 */, "MSLCR14" /* 0x655 */,                       \
        "MSLCR15" /* 0x656 */, "MSLCR16" /* 0x657 */, "SMINE2" /* 0x658 */, "SMINE6" /* 0x659 */,                      \
        "SMINE8" /* 0x65A */, "SMINE15" /* 0x65B */, "SMINE16" /* 0x65C */, "SMINE17" /* 0x65D */,                     \
        "SMINE18" /* 0x65E */, "CSHIP2" /* 0x65F */, "CSHIP6" /* 0x660 */, "CSHIP8" /* 0x661 */,                       \
        "CSHIP15" /* 0x662 */, "CSHIP16" /* 0x663 */, "CSHIP17" /* 0x664 */, "FIGHT1" /* 0x665 */,                     \
        "FIGHT5" /* 0x666 */, "FIGHT7" /* 0x667 */, "FIGHT14" /* 0x668 */, "FIGHT15" /* 0x669 */,                      \
        "FIGHT16" /* 0x66A */, "FIGHT19" /* 0x66B */, "FIGHT20" /* 0x66C */, "ATACK1" /* 0x66D */,                     \
        "ATACK5" /* 0x66E */, "ATACK7" /* 0x66F */, "ATACK14" /* 0x670 */, "ATACK15" /* 0x671 */,                      \
        "ATACK16" /* 0x672 */, "ATACK19" /* 0x673 */, "ATACK20" /* 0x674 */, "ATRANS1" /* 0x675 */,                    \
        "ATRANS5" /* 0x676 */, "ATRANS7" /* 0x677 */, "ATRANS15" /* 0x678 */, "ATRANS16" /* 0x679 */,                  \
        "ATRANS17" /* 0x67A */, "ATRANS18" /* 0x67B */, "ATRANS19" /* 0x67C */, "ATRANS20" /* 0x67D */,                \
        "AWAC1" /* 0x67E */, "AWAC5" /* 0x67F */, "AWAC7" /* 0x680 */, "AWAC14" /* 0x681 */, "AWAC15" /* 0x682 */,     \
        "AWAC16" /* 0x683 */, "AWAC19" /* 0x684 */, "AWAC20" /* 0x685 */, "JUGGR1" /* 0x686 */, "JUGGR5" /* 0x687 */,  \
        "JUGGR7" /* 0x688 */, "JUGGR14" /* 0x689 */, "JUGGR15" /* 0x68A */, "JUGGR16" /* 0x68B */,                     \
        "ALNTK1" /* 0x68C */, "ALNTK5" /* 0x68D */, "ALNTK7" /* 0x68E */, "ALNTK14" /* 0x68F */,                       \
        "ALNTK15" /* 0x690 */, "ALNTK16" /* 0x691 */, "ALNAG1" /* 0x692 */, "ALNAG5" /* 0x693 */,                      \
        "ALNAG7" /* 0x694 */, "ALNAG14" /* 0x695 */, "ALNAG15" /* 0x696 */, "ALNAG16" /* 0x697 */,                     \
        "ALNPL1" /* 0x698 */, "ALNPL5" /* 0x699 */, "ALNPL7" /* 0x69A */, "ALNPL14" /* 0x69B */,                       \
        "ALNPL15" /* 0x69C */, "ALNPL16" /* 0x69D */, "ALNPL19" /* 0x69E */, "ALNPL20" /* 0x69F */,                    \
        "FXS_END" /* 0x6A0 */, "SNOW_MSC" /* 0x6A1 */, "CRTR_MSC" /* 0x6A2 */, "GREN_MSC" /* 0x6A3 */,                 \
        "DSRT_MSC" /* 0x6A4 */, "MAIN_MSC" /* 0x6A5 */, "BKG1_MSC" /* 0x6A6 */, "BKG2_MSC" /* 0x6A7 */,                \
        "BKG3_MSC" /* 0x6A8 */, "BKG4_MSC" /* 0x6A9 */, "BKG5_MSC" /* 0x6AA */, "BKG6_MSC" /* 0x6AB */,                \
        "BKG7_MSC" /* 0x6AC */, "BKG8_MSC" /* 0x6AD */, "BKG9_MSC" /* 0x6AE */, "CRGO_MSC" /* 0x6AF */,                \
        "CRDT_MSC" /* 0x6B0 */, "WINR_MSC" /* 0x6B1 */, "LOSE_MSC" /* 0x6B2 */, "LOGOFLIC" /* 0x6B3 */,                \
        "INTROFLC" /* 0x6B4 */, "DEMO1FLC" /* 0x6B5 */, "DEMO2FLC" /* 0x6B6 */, "DEMO3FLC" /* 0x6B7 */,                \
        "DEMO4FLC" /* 0x6B8 */, "DEMO5FLC" /* 0x6B9 */, "REPORTS" /* 0x6BA */, "REP_FRME" /* 0x6BB */,                 \
        "ALLOCFRM" /* 0x6BC */, "STATS" /* 0x6BD */, "FRAMEPIC" /* 0x6BE */, "INTROPIC" /* 0x6BF */,                   \
        "MAINPIC" /* 0x6C0 */, "SETUPPIC" /* 0x6C1 */, "LOADPIC" /* 0x6C2 */, "NETPIC" /* 0x6C3 */,                    \
        "OPTPIC" /* 0x6C4 */, "LSTATPIC" /* 0x6C5 */, "EXITPIC" /* 0x6C6 */, "FACBUILD" /* 0x6C7 */,                   \
        "CONBUILD" /* 0x6C8 */, "QWKBUILD" /* 0x6C9 */, "UPGRADE" /* 0x6CA */, "CARGOPIC" /* 0x6CB */,                 \
        "XFERPIC" /* 0x6CC */, "PREFSPIC" /* 0x6CD */, "CLANSEL" /* 0x6CE */, "PLANETSE" /* 0x6CF */,                  \
        "MULTGAME" /* 0x6D0 */, "CHATWNDO" /* 0x6D1 */, "DEPOTFRM" /* 0x6D2 */, "HANGRFRM" /* 0x6D3 */,                \
        "DOCKFRM" /* 0x6D4 */, "RSRCHPIC" /* 0x6D5 */, "ENDGAME1" /* 0x6D6 */, "ENDGAME2" /* 0x6D7 */,                 \
        "ENDGAME3" /* 0x6D8 */, "ENDGAME4" /* 0x6D9 */, "ENDGAME5" /* 0x6DA */, "ENDGAME6" /* 0x6DB */,                \
        "ENDGAME7" /* 0x6DC */, "ENDGAME8" /* 0x6DD */, "ENDGAME9" /* 0x6DE */, "ENDGAM10" /* 0x6DF */,                \
        "ENDGAM11" /* 0x6E0 */, "ENDGAM12" /* 0x6E1 */, "ENDGAM13" /* 0x6E2 */, "ENDGAM14" /* 0x6E3 */,                \
        "ENDARM" /* 0x6E4 */, "DIALGPIC" /* 0x6E5 */, "HELPFRAM" /* 0x6E6 */, "ILOGO" /* 0x6E7 */,                     \
        "MLOGO" /* 0x6E8 */, "SELFDSTR" /* 0x6E9 */, "CREDITS" /* 0x6EA */, "STARTNET" /* 0x6EB */,                    \
        "JOINNET" /* 0x6EC */, "STARTMOD" /* 0x6ED */, "CHOSPLYR" /* 0x6EE */, "BLACKOUT" /* 0x6EF */,                 \
        "OEMONE" /* 0x6F0 */, "OEMTWO" /* 0x6F1 */, "OPTNFRM" /* 0x6F2 */, "P_TRANSP" /* 0x6F3 */,                     \
        "P_POWSTN" /* 0x6F4 */, "P_POWGEN" /* 0x6F5 */, "P_BARRCK" /* 0x6F6 */, "P_SHIELD" /* 0x6F7 */,                \
        "P_RADAR" /* 0x6F8 */, "P_SMSTOR" /* 0x6F9 */, "P_SMFUEL" /* 0x6FA */, "P_SMVLT" /* 0x6FB */,                  \
        "P_DEPOT" /* 0x6FC */, "P_HANGAR" /* 0x6FD */, "P_DOCK" /* 0x6FE */, "P_CONNEC" /* 0x6FF */,                   \
        "P_ROAD" /* 0x700 */, "P_LANDPD" /* 0x701 */, "P_SHIPYD" /* 0x702 */, "P_LGHTPL" /* 0x703 */,                  \
        "P_HVYPLT" /* 0x704 */, "P_LIFESP" /* 0x705 */, "P_AIRPLT" /* 0x706 */, "P_HABITA" /* 0x707 */,                \
        "P_RESEAR" /* 0x708 */, "P_GREENH" /* 0x709 */, "P_RECCTR" /* 0x70A */, "P_TRNHLL" /* 0x70B */,                \
        "P_WATER" /* 0x70C */, "P_GUNTUR" /* 0x70D */, "P_FXAA" /* 0x70E */, "P_ARTYTR" /* 0x70F */,                   \
        "P_FXROCK" /* 0x710 */, "P_BLOCK" /* 0x711 */, "P_BRIDGE" /* 0x712 */, "P_MINING" /* 0x713 */,                 \
        "P_LANDMN" /* 0x714 */, "P_SEAMIN" /* 0x715 */, "P_MASTER" /* 0x716 */, "P_CONTRC" /* 0x717 */,                \
        "P_SCOUT" /* 0x718 */, "P_TANK" /* 0x719 */, "P_ARTY" /* 0x71A */, "P_ROCKET" /* 0x71B */,                     \
        "P_MISSIL" /* 0x71C */, "P_AA" /* 0x71D */, "P_MNELAY" /* 0x71E */, "P_SURVEY" /* 0x71F */,                    \
        "P_SCANNR" /* 0x720 */, "P_SPLYTR" /* 0x721 */, "P_GOLDTR" /* 0x722 */, "P_ENGINR" /* 0x723 */,                \
        "P_BULLDZ" /* 0x724 */, "P_REPAIR" /* 0x725 */, "P_FUELTR" /* 0x726 */, "P_COLNST" /* 0x727 */,                \
        "P_COMMAN" /* 0x728 */, "P_INFANT" /* 0x729 */, "P_ESCORT" /* 0x72A */, "P_CORVET" /* 0x72B */,                \
        "P_GUNBT" /* 0x72C */, "P_SUB" /* 0x72D */, "P_SEATRN" /* 0x72E */, "P_MSLCR" /* 0x72F */,                     \
        "P_SEAMNL" /* 0x730 */, "P_CARGOS" /* 0x731 */, "P_FIGHTR" /* 0x732 */, "P_BOMBER" /* 0x733 */,                \
        "P_AIRTRN" /* 0x734 */, "P_AWAC" /* 0x735 */, "P_JUGGER" /* 0x736 */, "P_ALNTAN" /* 0x737 */,                  \
        "P_ALNASG" /* 0x738 */, "P_ALNPLA" /* 0x739 */, "A_MASTER" /* 0x73A */, "A_CONTRC" /* 0x73B */,                \
        "A_SCOUT" /* 0x73C */, "A_TANK" /* 0x73D */, "A_ARTY" /* 0x73E */, "A_ROCKET" /* 0x73F */,                     \
        "A_MISSIL" /* 0x740 */, "A_AA" /* 0x741 */, "A_MNELAY" /* 0x742 */, "A_SURVEY" /* 0x743 */,                    \
        "A_SCANNR" /* 0x744 */, "A_SPLYTR" /* 0x745 */, "A_GOLDTR" /* 0x746 */, "A_ENGINR" /* 0x747 */,                \
        "A_BULLDZ" /* 0x748 */, "A_REPAIR" /* 0x749 */, "A_FUELTR" /* 0x74A */, "A_COLNST" /* 0x74B */,                \
        "A_COMMAN" /* 0x74C */, "A_INFANT" /* 0x74D */, "A_ESCORT" /* 0x74E */, "A_CORVET" /* 0x74F */,                \
        "A_GUNBT" /* 0x750 */, "A_SUB" /* 0x751 */, "A_SEATRN" /* 0x752 */, "A_MSLCR" /* 0x753 */,                     \
        "A_SEAMNL" /* 0x754 */, "A_CARGOS" /* 0x755 */, "A_FIGHTR" /* 0x756 */, "A_BOMBER" /* 0x757 */,                \
        "A_AIRTRN" /* 0x758 */, "A_AWAC" /* 0x759 */, "A_JUGGER" /* 0x75A */, "A_ALNTAN" /* 0x75B */,                  \
        "A_ALNASG" /* 0x75C */, "A_ALNPLA" /* 0x75D */, "E_DEPOT" /* 0x75E */, "E_HANGAR" /* 0x75F */,                 \
        "E_DOCK" /* 0x760 */, "ATTRIBS" /* 0x761 */, "CLANATRB" /* 0x762 */, "SOUNDVOL" /* 0x763 */,                   \
        "TIPS" /* 0x764 */, "HELP_ENG" /* 0x765 */, "HELP_FRE" /* 0x766 */, "HELP_GRM" /* 0x767 */,                    \
        "SNOW_PIC" /* 0x768 */, "CRTR_PIC" /* 0x769 */, "GREN_PIC" /* 0x76A */, "DSRT_PIC" /* 0x76B */,                \
        "STAR_PIC" /* 0x76C */, "WORLD_S" /* 0x76D */, "SNOW_1" /* 0x76E */, "SNOW_2" /* 0x76F */,                     \
        "SNOW_3" /* 0x770 */, "SNOW_4" /* 0x771 */, "SNOW_5" /* 0x772 */, "SNOW_6" /* 0x773 */,                        \
        "CRATER_1" /* 0x774 */, "CRATER_2" /* 0x775 */, "CRATER_3" /* 0x776 */, "CRATER_4" /* 0x777 */,                \
        "CRATER_5" /* 0x778 */, "CRATER_6" /* 0x779 */, "GREEN_1" /* 0x77A */, "GREEN_2" /* 0x77B */,                  \
        "GREEN_3" /* 0x77C */, "GREEN_4" /* 0x77D */, "GREEN_5" /* 0x77E */, "GREEN_6" /* 0x77F */,                    \
        "DESERT_1" /* 0x780 */, "DESERT_2" /* 0x781 */, "DESERT_3" /* 0x782 */, "DESERT_4" /* 0x783 */,                \
        "DESERT_5" /* 0x784 */, "DESERT_6" /* 0x785 */, "WORLD_E" /* 0x786 */

typedef enum GAME_RESOURCE_e {
    COMMTWR = 0x0,
    POWERSTN = 0x1,
    POWGEN = 0x2,
    BARRACKS = 0x3,
    SHIELDGN = 0x4,
    RADAR = 0x5,
    ADUMP = 0x6,
    FDUMP = 0x7,
    GOLDSM = 0x8,
    DEPOT = 0x9,
    HANGAR = 0xA,
    DOCK = 0xB,
    CNCT_4W = 0xC,
    LRGRUBLE = 0xD,
    SMLRUBLE = 0xE,
    LRGTAPE = 0xF,
    SMLTAPE = 0x10,
    LRGSLAB = 0x11,
    SMLSLAB = 0x12,
    LRGCONES = 0x13,
    SMLCONES = 0x14,
    ROAD = 0x15,
    LANDPAD = 0x16,
    SHIPYARD = 0x17,
    LIGHTPLT = 0x18,
    LANDPLT = 0x19,
    SUPRTPLT = 0x1A,
    AIRPLT = 0x1B,
    HABITAT = 0x1C,
    RESEARCH = 0x1D,
    GREENHSE = 0x1E,
    RECCENTR = 0x1F,
    TRAINHAL = 0x20,
    WTRPLTFM = 0x21,
    GUNTURRT = 0x22,
    ANTIAIR = 0x23,
    ARTYTRRT = 0x24,
    ANTIMSSL = 0x25,
    BLOCK = 0x26,
    BRIDGE = 0x27,
    MININGST = 0x28,
    LANDMINE = 0x29,
    SEAMINE = 0x2A,
    LNDEXPLD = 0x2B,
    AIREXPLD = 0x2C,
    SEAEXPLD = 0x2D,
    BLDEXPLD = 0x2E,
    HITEXPLD = 0x2F,
    MASTER = 0x30,
    CONSTRCT = 0x31,
    SCOUT = 0x32,
    TANK = 0x33,
    ARTILLRY = 0x34,
    ROCKTLCH = 0x35,
    MISSLLCH = 0x36,
    SP_FLAK = 0x37,
    MINELAYR = 0x38,
    SURVEYOR = 0x39,
    SCANNER = 0x3A,
    SPLYTRCK = 0x3B,
    GOLDTRCK = 0x3C,
    ENGINEER = 0x3D,
    BULLDOZR = 0x3E,
    REPAIR = 0x3F,
    FUELTRCK = 0x40,
    CLNTRANS = 0x41,
    COMMANDO = 0x42,
    INFANTRY = 0x43,
    FASTBOAT = 0x44,
    CORVETTE = 0x45,
    BATTLSHP = 0x46,
    SUBMARNE = 0x47,
    SEATRANS = 0x48,
    MSSLBOAT = 0x49,
    SEAMNLYR = 0x4A,
    CARGOSHP = 0x4B,
    FIGHTER = 0x4C,
    BOMBER = 0x4D,
    AIRTRANS = 0x4E,
    AWAC = 0x4F,
    JUGGRNT = 0x50,
    ALNTANK = 0x51,
    ALNASGUN = 0x52,
    ALNPLANE = 0x53,
    ROCKET = 0x54,
    TORPEDO = 0x55,
    ALNMISSL = 0x56,
    ALNTBALL = 0x57,
    ALNABALL = 0x58,
    RKTSMOKE = 0x59,
    TRPBUBLE = 0x5A,
    HARVSTER = 0x5B,
    WALDO = 0x5C,
    UNIT_END = 0x5D,
    S_COMMTW = 0x5E,
    S_POWERS = 0x5F,
    S_POWGEN = 0x60,
    S_BARRAC = 0x61,
    S_SHIELD = 0x62,
    S_RADAR = 0x63,
    S_ADUMP = 0x64,
    S_FDUMP = 0x65,
    S_GOLDSM = 0x66,
    S_DEPOT = 0x67,
    S_HANGAR = 0x68,
    S_DOCK = 0x69,
    S_CNCT4W = 0x6A,
    S_LRGRBL = 0x6B,
    S_SMLRBL = 0x6C,
    S_LRGSLA = 0x6D,
    S_LRGCON = 0x6E,
    S_SMLSLA = 0x6F,
    S_SMLCON = 0x70,
    S_ROAD = 0x71,
    S_LANDPA = 0x72,
    S_SHIPYA = 0x73,
    S_LIGHTP = 0x74,
    S_LANDPL = 0x75,
    S_SUPRTP = 0x76,
    S_AIRPLT = 0x77,
    S_HABITA = 0x78,
    S_RESEAR = 0x79,
    S_GREENH = 0x7A,
    S_RECCEN = 0x7B,
    S_TRAINH = 0x7C,
    S_WTRPLT = 0x7D,
    S_GUNTUR = 0x7E,
    S_ANTIAI = 0x7F,
    S_ARTYTR = 0x80,
    S_ANTIMS = 0x81,
    S_BLOCK = 0x82,
    S_BRIDGE = 0x83,
    S_MINING = 0x84,
    S_LANDMI = 0x85,
    S_SEAMIN = 0x86,
    S_MASTER = 0x87,
    S_CONSTR = 0x88,
    S_SCOUT = 0x89,
    S_TANK = 0x8A,
    S_ARTILL = 0x8B,
    S_ROCKTL = 0x8C,
    S_MISSLL = 0x8D,
    S_FLAK = 0x8E,
    S_MINELA = 0x8F,
    S_SURVEY = 0x90,
    S_SCANNE = 0x91,
    S_SPLYTR = 0x92,
    S_GOLDTR = 0x93,
    S_ENGINE = 0x94,
    S_BULLDO = 0x95,
    S_REPAIR = 0x96,
    S_FUELTR = 0x97,
    S_CLNTRA = 0x98,
    S_COMMAN = 0x99,
    S_INFANT = 0x9A,
    S_FASTBO = 0x9B,
    S_CORVET = 0x9C,
    S_BATTLS = 0x9D,
    S_SUBMAR = 0x9E,
    S_SEATRA = 0x9F,
    S_MSSLBO = 0xA0,
    S_SEAMNL = 0xA1,
    S_CARGOS = 0xA2,
    S_FIGHTE = 0xA3,
    S_BOMBER = 0xA4,
    S_AIRTRA = 0xA5,
    S_AWAC = 0xA6,
    S_JUGGRN = 0xA7,
    S_ALNTAN = 0xA8,
    S_ALNASG = 0xA9,
    S_ALNPLA = 0xAA,
    S_HARVST = 0xAB,
    MOVEPT = 0xAC,
    NOMOVEPT = 0xAD,
    FIREPT = 0xAE,
    NOFIREPT = 0xAF,
    NOCARGO = 0xB0,
    UNTBTN_U = 0xB1,
    UNTBTN_D = 0xB2,
    DONE_OF = 0xB3,
    DONE_ON = 0xB4,
    NEXT_OF = 0xB5,
    NEXT_ON = 0xB6,
    PREV_OF = 0xB7,
    PREV_ON = 0xB8,
    XFORM_OF = 0xB9,
    XFORM_ON = 0xBA,
    BUILD_OF = 0xBB,
    BUILD_ON = 0xBC,
    ALLOC_OF = 0xBD,
    ALLOC_ON = 0xBE,
    ATTK_OF = 0xBF,
    ATTK_ON = 0xC0,
    SNTRY_OF = 0xC1,
    SNTRY_ON = 0xC2,
    WAIT_OF = 0xC3,
    WAIT_ON = 0xC4,
    XFER_OF = 0xC5,
    XFER_ON = 0xC6,
    LOAD_OF = 0xC7,
    LOAD_ON = 0xC8,
    ACTVT_OF = 0xC9,
    ACTVT_ON = 0xCA,
    STOP_OF = 0xCB,
    STOP_ON = 0xCC,
    REPAR_OF = 0xCD,
    REPAR_ON = 0xCE,
    FLLOW_OF = 0xCF,
    FLLOW_ON = 0xD0,
    CLEAR_OF = 0xD1,
    CLEAR_ON = 0xD2,
    RECHG_OF = 0xD3,
    RECHG_ON = 0xD4,
    START_OF = 0xD5,
    START_ON = 0xD6,
    UPGRD_OF = 0xD7,
    UPGRD_ON = 0xD8,
    BYUPG_OF = 0xD9,
    BYUPG_ON = 0xDA,
    RLOAD_OF = 0xDB,
    RLOAD_ON = 0xDC,
    RSRCH_OF = 0xDD,
    RSRCH_ON = 0xDE,
    PLACE_OF = 0xDF,
    PLACE_ON = 0xE0,
    REMVE_OF = 0xE1,
    REMVE_ON = 0xE2,
    ENTER_OF = 0xE3,
    ENTER_ON = 0xE4,
    TOPIC_OF = 0xE5,
    TOPIC_ON = 0xE6,
    TIMER = 0xE7,
    XYPOS = 0xE8,
    UNITNAME = 0xE9,
    TURNS = 0xEA,
    SELFD_OF = 0xEB,
    SELFD_ON = 0xEC,
    STEAL_OF = 0xED,
    STEAL_ON = 0xEE,
    DISBL_OF = 0xEF,
    DISBL_ON = 0xF0,
    STATS_OF = 0xF1,
    STATS_ON = 0xF2,
    R_RSRC_U = 0xF3,
    R_RSRC_D = 0xF4,
    R_FACL_U = 0xF5,
    R_FACL_D = 0xF6,
    R_PERF_U = 0xF7,
    R_PERF_D = 0xF8,
    R_PROD_U = 0xF9,
    R_PROD_D = 0xFA,
    R_MINE_U = 0xFB,
    R_MINE_D = 0xFC,
    R_UNIT_U = 0xFD,
    R_UNIT_D = 0xFE,
    R_UPGR_U = 0xFF,
    R_UPGR_D = 0x100,
    R_CSLT_U = 0x101,
    R_CSLT_D = 0x102,
    R_ETA__U = 0x103,
    R_ETA__D = 0x104,
    R_STAT_U = 0x105,
    R_STAT_D = 0x106,
    R_CPLX_U = 0x107,
    R_CPLX_D = 0x108,
    R_CLSE_U = 0x109,
    R_CLSE_D = 0x10A,
    R_UPAR_U = 0x10B,
    R_UPAR_D = 0x10C,
    R_DNAR_U = 0x10D,
    R_DNAR_D = 0x10E,
    ENDTRN_U = 0x10F,
    R_ENDT_D = 0x110,
    G_ENDT_D = 0x111,
    B_ENDT_D = 0x112,
    W_ENDT_D = 0x113,
    QWKUP_OF = 0x114,
    QWKUP_ON = 0x115,
    QWKDN_OF = 0x116,
    QWKDN_ON = 0x117,
    QWKCN_OF = 0x118,
    QWKCN_ON = 0x119,
    BLDUP__U = 0x11A,
    BLDUP__D = 0x11B,
    BLDUP__X = 0x11C,
    BLDDWN_U = 0x11D,
    BLDDWN_D = 0x11E,
    BLDDWN_X = 0x11F,
    BLDBLD_U = 0x120,
    BLDBLD_D = 0x121,
    BLDONE_U = 0x122,
    BLDONE_D = 0x123,
    BLDREP_U = 0x124,
    BLDREP_D = 0x125,
    BLDDEL_U = 0x126,
    BLDDEL_D = 0x127,
    BLDDES_U = 0x128,
    BLDDES_D = 0x129,
    BLDCAN_U = 0x12A,
    BLDCAN_D = 0x12B,
    BLDHLP_U = 0x12C,
    BLDHLP_D = 0x12D,
    BLDPTH_U = 0x12E,
    BLDPTH_D = 0x12F,
    BLD2X_U = 0x130,
    BLD2X_D = 0x131,
    BLD4X_U = 0x132,
    BLD4X_D = 0x133,
    AL_DNE_U = 0x134,
    AL_DNE_D = 0x135,
    UPGDNE_U = 0x136,
    UPGDNE_D = 0x137,
    UPGCAN_U = 0x138,
    UPGCAN_D = 0x139,
    UPGRGT_U = 0x13A,
    UPGRGT_D = 0x13B,
    UPGRGT_X = 0x13C,
    UPGLFT_U = 0x13D,
    UPGLFT_D = 0x13E,
    UPGLFT_X = 0x13F,
    SELGRD_U = 0x140,
    SELGRD_D = 0x141,
    SELAIR_U = 0x142,
    SELAIR_D = 0x143,
    SELSEA_U = 0x144,
    SELSEA_D = 0x145,
    SELBLD_U = 0x146,
    SELBLD_D = 0x147,
    SELCBT_U = 0x148,
    SELCBT_D = 0x149,
    XFRDNE_U = 0x14A,
    XFRDNE_D = 0x14B,
    XFRHLP_U = 0x14C,
    XFRHLP_D = 0x14D,
    XFRCAN_U = 0x14E,
    XFRCAN_D = 0x14F,
    XFRRGT_U = 0x150,
    XFRRGT_D = 0x151,
    XFRLFT_U = 0x152,
    XFRLFT_D = 0x153,
    XFRLFARO = 0x154,
    XFRRTARO = 0x155,
    DLOGOK_U = 0x156,
    DLOGOK_D = 0x157,
    HELPOK_U = 0x158,
    HELPOK_D = 0x159,
    ENDOK_U = 0x15A,
    ENDOK_D = 0x15B,
    SLFDAR_U = 0x15C,
    SLFDAR_D = 0x15D,
    SLFDCN_U = 0x15E,
    SLFDCN_D = 0x15F,
    SLFDOK_U = 0x160,
    SLFDOK_D = 0x161,
    SLFDOPN1 = 0x162,
    SLFDOPN2 = 0x163,
    SLFDOPN3 = 0x164,
    SLFDOPN4 = 0x165,
    SLFDOPN5 = 0x166,
    SLFDOPN6 = 0x167,
    PNLHLP_U = 0x168,
    PNLHLP_D = 0x169,
    PNLCAN_U = 0x16A,
    PNLCAN_D = 0x16B,
    CHTCAN_U = 0x16C,
    CHTCAN_D = 0x16D,
    CHTHLP_U = 0x16E,
    CHTHLP_D = 0x16F,
    CHTSND_U = 0x170,
    CHTSND_D = 0x171,
    CHTRED_U = 0x172,
    CHTRED_D = 0x173,
    CHTGRN_U = 0x174,
    CHTGRN_D = 0x175,
    CHTBLU_U = 0x176,
    CHTBLU_D = 0x177,
    CHTGRY_U = 0x178,
    CHTGRY_D = 0x179,
    PRFCAN_U = 0x17A,
    PRFCAN_D = 0x17B,
    PRFHLP_U = 0x17C,
    PRFHLP_D = 0x17D,
    PRFDNE_U = 0x17E,
    PRFDNE_D = 0x17F,
    PREFEDIT = 0x180,
    PREFNAME = 0x181,
    PRFSLIDE = 0x182,
    PRFSLIT = 0x183,
    CRGTOG_U = 0x184,
    CRGTOG_D = 0x185,
    CRGDEL_U = 0x186,
    CRGDEL_D = 0x187,
    CRGDEL_X = 0x188,
    CRGBUY_U = 0x189,
    CRGBUY_D = 0x18A,
    CRGBUY_X = 0x18B,
    CRGSELUX = 0x18C,
    CRGSELDX = 0x18D,
    DPTBAYUP = 0x18E,
    DPTBAYDN = 0x18F,
    DPTMNUUP = 0x190,
    DPTMNUDN = 0x191,
    DPTUP_UP = 0x192,
    DPTUP_DN = 0x193,
    DPTUP_X = 0x194,
    DPTDN_UP = 0x195,
    DPTDN_DN = 0x196,
    DPTDN_X = 0x197,
    DPTHP_UP = 0x198,
    DPTHP_DN = 0x199,
    RAWMSK0 = 0x19A,
    RAWMSK1 = 0x19B,
    RAWMSK2 = 0x19C,
    RAWMSK3 = 0x19D,
    RAWMSK4 = 0x19E,
    RAWMSK5 = 0x19F,
    RAWMSK6 = 0x1A0,
    RAWMSK7 = 0x1A1,
    RAWMSK8 = 0x1A2,
    RAWMSK9 = 0x1A3,
    RAWMSK10 = 0x1A4,
    RAWMSK11 = 0x1A5,
    RAWMSK12 = 0x1A6,
    RAWMSK13 = 0x1A7,
    RAWMSK14 = 0x1A8,
    RAWMSK15 = 0x1A9,
    RAWMSK16 = 0x1AA,
    FUELMK0 = 0x1AB,
    FUELMK1 = 0x1AC,
    FUELMK2 = 0x1AD,
    FUELMK3 = 0x1AE,
    FUELMK4 = 0x1AF,
    FUELMK5 = 0x1B0,
    FUELMK6 = 0x1B1,
    FUELMK7 = 0x1B2,
    FUELMK8 = 0x1B3,
    FUELMK9 = 0x1B4,
    FUELMK10 = 0x1B5,
    FUELMK11 = 0x1B6,
    FUELMK12 = 0x1B7,
    FUELMK13 = 0x1B8,
    FUELMK14 = 0x1B9,
    FUELMK15 = 0x1BA,
    FUELMK16 = 0x1BB,
    GOLDMK0 = 0x1BC,
    GOLDMK1 = 0x1BD,
    GOLDMK2 = 0x1BE,
    GOLDMK3 = 0x1BF,
    GOLDMK4 = 0x1C0,
    GOLDMK5 = 0x1C1,
    GOLDMK6 = 0x1C2,
    GOLDMK7 = 0x1C3,
    GOLDMK8 = 0x1C4,
    GOLDMK9 = 0x1C5,
    GOLDMK10 = 0x1C6,
    GOLDMK11 = 0x1C7,
    GOLDMK12 = 0x1C8,
    GOLDMK13 = 0x1C9,
    GOLDMK14 = 0x1CA,
    GOLDMK15 = 0x1CB,
    GOLDMK16 = 0x1CC,
    SMRWMK1 = 0x1CD,
    SMRWMK2 = 0x1CE,
    SMRWMK3 = 0x1CF,
    SMRWMK4 = 0x1D0,
    SMRWMK5 = 0x1D1,
    SMRWMK6 = 0x1D2,
    SMRWMK7 = 0x1D3,
    SMRWMK8 = 0x1D4,
    SMRWMK9 = 0x1D5,
    SMRWMK10 = 0x1D6,
    SMRWMK11 = 0x1D7,
    SMRWMK12 = 0x1D8,
    SMRWMK13 = 0x1D9,
    SMRWMK14 = 0x1DA,
    SMRWMK15 = 0x1DB,
    SMRWMK16 = 0x1DC,
    SMFLMK1 = 0x1DD,
    SMFLMK2 = 0x1DE,
    SMFLMK3 = 0x1DF,
    SMFLMK4 = 0x1E0,
    SMFLMK5 = 0x1E1,
    SMFLMK6 = 0x1E2,
    SMFLMK7 = 0x1E3,
    SMFLMK8 = 0x1E4,
    SMFLMK9 = 0x1E5,
    SMFLMK10 = 0x1E6,
    SMFLMK11 = 0x1E7,
    SMFLMK12 = 0x1E8,
    SMFLMK13 = 0x1E9,
    SMFLMK14 = 0x1EA,
    SMFLMK15 = 0x1EB,
    SMFLMK16 = 0x1EC,
    SMGDMK1 = 0x1ED,
    SMGDMK2 = 0x1EE,
    SMGDMK3 = 0x1EF,
    SMGDMK4 = 0x1F0,
    SMGDMK5 = 0x1F1,
    SMGDMK6 = 0x1F2,
    SMGDMK7 = 0x1F3,
    SMGDMK8 = 0x1F4,
    SMGDMK9 = 0x1F5,
    SMGDMK10 = 0x1F6,
    SMGDMK11 = 0x1F7,
    SMGDMK12 = 0x1F8,
    SMGDMK13 = 0x1F9,
    SMGDMK14 = 0x1FA,
    SMGDMK15 = 0x1FB,
    SMGDMK16 = 0x1FC,
    BULB = 0x1FD,
    MARKER0 = 0x1FE,
    MARKER1 = 0x1FF,
    MARKER2 = 0x200,
    MARKER3 = 0x201,
    MARKER4 = 0x202,
    STATNUM0 = 0x203,
    STATNUM1 = 0x204,
    STATNUM2 = 0x205,
    STATNUM3 = 0x206,
    STATNUM4 = 0x207,
    STATNUM5 = 0x208,
    STATNUM6 = 0x209,
    STATNUM7 = 0x20A,
    STATNUM8 = 0x20B,
    STATNUM9 = 0x20C,
    FUELDOT = 0x20D,
    GOLDDOT = 0x20E,
    LFARO_OF = 0x20F,
    LFARO_ON = 0x210,
    PRODDOT = 0x211,
    PRODSLOT = 0x212,
    RAWDOT = 0x213,
    RTARO_OF = 0x214,
    RTARO_ON = 0x215,
    BARRAW = 0x216,
    BARFUEL = 0x217,
    BARGOLD = 0x218,
    BARUNUS = 0x219,
    BARTAPE = 0x21A,
    BARTAPE2 = 0x21B,
    BARTAPE3 = 0x21C,
    BARTAPEX = 0x21D,
    SMBRRAW = 0x21E,
    SMBRFUEL = 0x21F,
    SMBRGOLD = 0x220,
    VERTRAW = 0x221,
    VERTFUEL = 0x222,
    VERTGOLD = 0x223,
    LOADBAR = 0x224,
    CLOSE_OF = 0x225,
    CLOSE_ON = 0x226,
    PURCHOFF = 0x227,
    PURCHON = 0x228,
    RETURNOF = 0x229,
    RETURNON = 0x22A,
    EDITWNDO = 0x22B,
    BIGSCRNL = 0x22C,
    BIGSCRNR = 0x22D,
    SUBTITLE = 0x22E,
    BGRSCRNL = 0x22F,
    BGRSCRNR = 0x230,
    BLDMRK1 = 0x231,
    BLDMRK2 = 0x232,
    BLDMRK3 = 0x233,
    BLDMRK4 = 0x234,
    BLDMRK5 = 0x235,
    HIDDNPTR = 0x236,
    HANDPTR = 0x237,
    CONDLITE = 0x238,
    FUELLITE = 0x239,
    AMMOLITE = 0x23A,
    CARGOLIT = 0x23B,
    CLOSED = 0x23C,
    ARROW_N = 0x23D,
    ARROW_NE = 0x23E,
    ARROW_E = 0x23F,
    ARROW_SE = 0x240,
    ARROW_S = 0x241,
    ARROW_SW = 0x242,
    ARROW_W = 0x243,
    ARROW_NW = 0x244,
    MAP_PTR = 0x245,
    MINI_PTR = 0x246,
    MINI_X = 0x247,
    MINI_X2 = 0x248,
    FRND_FIX = 0x249,
    FRND_XFR = 0x24A,
    FRND_LOD = 0x24B,
    FRND_FUE = 0x24C,
    FRND_PTR = 0x24D,
    ENMY_PTR = 0x24E,
    PTR_FTRG = 0x24F,
    WAY_PTR = 0x250,
    GROUPPTR = 0x251,
    ACTVTPTR = 0x252,
    PTR_RLD = 0x253,
    STEALPTR = 0x254,
    DISBLPTR = 0x255,
    PTR_PATH = 0x256,
    PTR_HELP = 0x257,
    ZOOMPNL1 = 0x258,
    ZOOMPNL2 = 0x259,
    ZOOMPNL3 = 0x25A,
    ZOOMPNL4 = 0x25B,
    ZOOMPNL5 = 0x25C,
    ZOOMPNL6 = 0x25D,
    ZOOMPNL7 = 0x25E,
    ZOOMPTR = 0x25F,
    UNIT_GO = 0x260,
    UNIT_NGO = 0x261,
    LIGHTOFF = 0x262,
    LIGHTON = 0x263,
    I_HRDATK = 0x264,
    I_ATTACK = 0x265,
    I_SHOTS = 0x266,
    I_RANGE = 0x267,
    I_AMMO = 0x268,
    I_ARMOR = 0x269,
    I_SFTARM = 0x26A,
    I_CHARGE = 0x26B,
    I_HITS = 0x26C,
    I_SCAN = 0x26D,
    I_SPEED = 0x26E,
    I_FUEL = 0x26F,
    I_RAW = 0x270,
    I_RAWE = 0x271,
    I_GOLD = 0x272,
    I_GOLDE = 0x273,
    I_POWER = 0x274,
    I_LIFE = 0x275,
    SI_HITSB = 0x276,
    EI_HITSB = 0x277,
    SI_HITSY = 0x278,
    EI_HITSY = 0x279,
    SI_HITSR = 0x27A,
    EI_HITSR = 0x27B,
    SI_AMMO = 0x27C,
    EI_AMMO = 0x27D,
    SI_RAW = 0x27E,
    EI_RAW = 0x27F,
    SI_FUEL = 0x280,
    EI_FUEL = 0x281,
    SI_GOLD = 0x282,
    EI_GOLD = 0x283,
    SI_LAND = 0x284,
    EI_LAND = 0x285,
    SI_SEA = 0x286,
    EI_SEA = 0x287,
    SI_AIR = 0x288,
    EI_AIR = 0x289,
    SI_WORK = 0x28A,
    EI_WORK = 0x28B,
    SI_SPEED = 0x28C,
    EI_SPEED = 0x28D,
    SI_SHOTS = 0x28E,
    EI_SHOTS = 0x28F,
    SI_POWER = 0x290,
    EI_POWER = 0x291,
    IL_SPEED = 0x292,
    IL_SHOTS = 0x293,
    IL_DSBLD = 0x294,
    LIPS = 0x295,
    I_CMPLX = 0x296,
    BUY_OFF = 0x297,
    BUY_ON = 0x298,
    MENU_OFF = 0x299,
    MENU_ON = 0x29A,
    REPT_OFF = 0x29B,
    REPT_ON = 0x29C,
    STAT_OFF = 0x29D,
    STAT_ON = 0x29E,
    RANG_OFF = 0x29F,
    RANG_ON = 0x2A0,
    VISN_OFF = 0x2A1,
    VISN_ON = 0x2A2,
    REDY_OFF = 0x2A3,
    REDY_ON = 0x2A4,
    TRGT_OFF = 0x2A5,
    TRGT_ON = 0x2A6,
    FIND_OFF = 0x2A7,
    FIND_ON = 0x2A8,
    CHAT_OFF = 0x2A9,
    CHAT_ON = 0x2AA,
    GOAL_OFF = 0x2AB,
    GOAL_ON = 0x2AC,
    PREF_OFF = 0x2AD,
    PREF_ON = 0x2AE,
    SYSM_OFF = 0x2AF,
    SYSM_ON = 0x2B0,
    FILES_OF = 0x2B1,
    FILES_ON = 0x2B2,
    SURV_OFF = 0x2B3,
    SURV_ON = 0x2B4,
    GRID_OFF = 0x2B5,
    GRID_ON = 0x2B6,
    NAMES_UP = 0x2B7,
    NAMES_DN = 0x2B8,
    CHECKED = 0x2B9,
    UNCHKED = 0x2BA,
    BLANK_UP = 0x2BB,
    BLANK_DN = 0x2BC,
    SBLNK_UP = 0x2BD,
    SBLNK_DN = 0x2BE,
    OBAR_UP = 0x2BF,
    OBAR_DN = 0x2C0,
    HELP_OF = 0x2C1,
    HELP_ON = 0x2C2,
    UDONE_OF = 0x2C3,
    UDONE_ON = 0x2C4,
    MIN2X_OF = 0x2C5,
    MIN2X_ON = 0x2C6,
    MINFL_OF = 0x2C7,
    MINFL_ON = 0x2C8,
    AMMO_OF = 0x2C9,
    AMMO_ON = 0x2CA,
    HITS_OF = 0x2CB,
    HITS_ON = 0x2CC,
    COLOR_OF = 0x2CD,
    COLOR_ON = 0x2CE,
    PAUSE_OF = 0x2CF,
    PAUSE_ON = 0x2D0,
    PLAY_OF = 0x2D1,
    PLAY_ON = 0x2D2,
    LOCK_OF = 0x2D3,
    LOCK_ON = 0x2D4,
    CLN0LOGO = 0x2D5,
    CLN1LOGO = 0x2D6,
    CLN2LOGO = 0x2D7,
    CLN3LOGO = 0x2D8,
    CLN4LOGO = 0x2D9,
    CLN5LOGO = 0x2DA,
    CLN6LOGO = 0x2DB,
    CLN7LOGO = 0x2DC,
    CLN8LOGO = 0x2DD,
    D_DEFALT = 0x2DE,
    D_LRGBLD = 0x2DF,
    D_SMLBLD = 0x2E0,
    D_MOBILE = 0x2E1,
    D_FIRING = 0x2E2,
    D_RADAR = 0x2E3,
    D_ANTIAI = 0x2E4,
    D_FIXED = 0x2E5,
    D_TANK = 0x2E6,
    D_ALTANK = 0x2E7,
    D_SP_FLK = 0x2E8,
    D_UEXPLD = 0x2E9,
    D_SEXPLD = 0x2EA,
    D_BEXPLD = 0x2EB,
    D_SMOKE = 0x2EC,
    D_BUBBLE = 0x2ED,
    D_LRGRBL = 0x2EE,
    D_SMLRBL = 0x2EF,
    D_LRGSLA = 0x2F0,
    D_AWAC = 0x2F1,
    D_AMPHIB = 0x2F2,
    D_BATTLS = 0x2F3,
    D_BRIDGE = 0x2F4,
    D_COMMAN = 0x2F5,
    D_INFANT = 0x2F6,
    D_TORPDO = 0x2F7,
    D_ALNMSL = 0x2F8,
    D_ALNPBL = 0x2F9,
    D_ESCORT = 0x2FA,
    D_MINING = 0x2FB,
    D_SCANNR = 0x2FC,
    D_SUB = 0x2FD,
    PNLSEQ_1 = 0x2FE,
    PNLSEQ_2 = 0x2FF,
    PNLSEQ_3 = 0x300,
    PNLSEQ_4 = 0x301,
    PNLSEQ_5 = 0x302,
    BPNLSQ_1 = 0x303,
    BPNLSQ_2 = 0x304,
    BPNLSQ_3 = 0x305,
    BPNLSQ_4 = 0x306,
    PANELTOP = 0x307,
    PANELBTM = 0x308,
    CH_HUM_U = 0x309,
    CH_HUM_D = 0x30A,
    CH_CMP_U = 0x30B,
    CH_CMP_D = 0x30C,
    CH_NON_U = 0x30D,
    CH_NON_D = 0x30E,
    CH_UP_UP = 0x30F,
    CH_UP_DN = 0x310,
    CH_DWN_U = 0x311,
    CH_DWN_D = 0x312,
    CH_QST_U = 0x313,
    CH_QST_D = 0x314,
    CH_TM1_U = 0x315,
    CH_TM1_D = 0x316,
    CH_TM2_U = 0x317,
    CH_TM2_D = 0x318,
    CH_TM3_U = 0x319,
    CH_TM3_D = 0x31A,
    CH_TM4_U = 0x31B,
    CH_TM4_D = 0x31C,
    M_CLAN_U = 0x31D,
    M_CLAN_D = 0x31E,
    CH_CN1_U = 0x31F,
    CH_CN1_D = 0x320,
    CH_CN2_U = 0x321,
    CH_CN2_D = 0x322,
    CH_CN3_U = 0x323,
    CH_CN3_D = 0x324,
    CH_CN4_U = 0x325,
    CH_CN4_D = 0x326,
    CH_CN5_U = 0x327,
    CH_CN5_D = 0x328,
    CH_CN6_U = 0x329,
    CH_CN6_D = 0x32A,
    CH_CN7_U = 0x32B,
    CH_CN7_D = 0x32C,
    CH_CN8_U = 0x32D,
    CH_CN8_D = 0x32E,
    PL_NXT_U = 0x32F,
    PL_NXT_D = 0x330,
    PL_LST_U = 0x331,
    PL_LST_D = 0x332,
    MNUBTN1U = 0x333,
    MNUBTN1D = 0x334,
    MNUBTN2U = 0x335,
    MNUBTN2D = 0x336,
    MNUBTN3U = 0x337,
    MNUBTN3D = 0x338,
    MNUBTN4U = 0x339,
    MNUBTN4D = 0x33A,
    MNUBTN5U = 0x33B,
    MNUBTN5D = 0x33C,
    MNUBTN6U = 0x33D,
    MNUBTN6D = 0x33E,
    MNULAROU = 0x33F,
    MNULAROD = 0x340,
    MNURAROU = 0x341,
    MNURAROD = 0x342,
    MNUUAROU = 0x343,
    MNUUAROD = 0x344,
    MNUDAROU = 0x345,
    MNUDAROD = 0x346,
    I_TRANSP = 0x347,
    I_POWSTN = 0x348,
    I_POWGEN = 0x349,
    I_BARRCK = 0x34A,
    I_SHIELD = 0x34B,
    I_RADAR = 0x34C,
    I_SMSTOR = 0x34D,
    I_SMFUEL = 0x34E,
    I_SMVLT = 0x34F,
    I_DEPOT = 0x350,
    I_HANGAR = 0x351,
    I_DOCK = 0x352,
    I_CONNEC = 0x353,
    I_ROAD = 0x354,
    I_LANDPD = 0x355,
    I_SHIPYD = 0x356,
    I_LGHTPL = 0x357,
    I_HVYPLT = 0x358,
    I_LIFESP = 0x359,
    I_AIRPLT = 0x35A,
    I_HABITA = 0x35B,
    I_RESEAR = 0x35C,
    I_GREENH = 0x35D,
    I_RECCTR = 0x35E,
    I_TRNHLL = 0x35F,
    I_WATER = 0x360,
    I_GUNTUR = 0x361,
    I_FXAA = 0x362,
    I_ARTYTR = 0x363,
    I_FXROCK = 0x364,
    I_BLOCK = 0x365,
    I_BRIDGE = 0x366,
    I_MINING = 0x367,
    I_LANDMN = 0x368,
    I_SEAMIN = 0x369,
    I_MASTER = 0x36A,
    I_CONTRC = 0x36B,
    I_SCOUT = 0x36C,
    I_TANK = 0x36D,
    I_ARTY = 0x36E,
    I_ROCKET = 0x36F,
    I_MISSIL = 0x370,
    I_AA = 0x371,
    I_MNELAY = 0x372,
    I_SURVEY = 0x373,
    I_SCANNR = 0x374,
    I_SPLYTR = 0x375,
    I_GOLDTR = 0x376,
    I_ENGINR = 0x377,
    I_BULLDZ = 0x378,
    I_REPAIR = 0x379,
    I_FUELTR = 0x37A,
    I_COLNST = 0x37B,
    I_COMMAN = 0x37C,
    I_INFANT = 0x37D,
    I_ESCORT = 0x37E,
    I_CORVET = 0x37F,
    I_GUNBT = 0x380,
    I_SUB = 0x381,
    I_SEATRN = 0x382,
    I_MSLCR = 0x383,
    I_SEAMNL = 0x384,
    I_CARGOS = 0x385,
    I_FIGHTR = 0x386,
    I_BOMBER = 0x387,
    I_AIRTRN = 0x388,
    I_AWAC = 0x389,
    I_JUGGER = 0x38A,
    I_ALNTAN = 0x38B,
    I_ALNASG = 0x38C,
    I_ALNPLA = 0x38D,
    MEM_END = 0x38E,
    V_START = 0x38F,
    V_M001 = 0x390,
    V_F001 = 0x391,
    V_M005 = 0x392,
    V_F005 = 0x393,
    V_M006 = 0x394,
    V_F006 = 0x395,
    V_M004 = 0x396,
    V_F004 = 0x397,
    V_M284 = 0x398,
    V_F284 = 0x399,
    V_M138 = 0x39A,
    V_F138 = 0x39B,
    V_M142 = 0x39C,
    V_F142 = 0x39D,
    V_M145 = 0x39E,
    V_F145 = 0x39F,
    V_M150 = 0x3A0,
    V_F150 = 0x3A1,
    V_M151 = 0x3A2,
    V_F151 = 0x3A3,
    V_M265 = 0x3A4,
    V_F265 = 0x3A5,
    V_M154 = 0x3A6,
    V_F154 = 0x3A7,
    V_M155 = 0x3A8,
    V_F155 = 0x3A9,
    V_M158 = 0x3AA,
    V_F158 = 0x3AB,
    V_M162 = 0x3AC,
    V_F162 = 0x3AD,
    V_M164 = 0x3AE,
    V_F164 = 0x3AF,
    V_M163 = 0x3B0,
    V_F163 = 0x3B1,
    V_M165 = 0x3B2,
    V_F165 = 0x3B3,
    V_M166 = 0x3B4,
    V_F166 = 0x3B5,
    V_M169 = 0x3B6,
    V_F169 = 0x3B7,
    V_M171 = 0x3B8,
    V_F171 = 0x3B9,
    V_M181 = 0x3BA,
    V_F181 = 0x3BB,
    V_M182 = 0x3BC,
    V_F182 = 0x3BD,
    V_M186 = 0x3BE,
    V_F186 = 0x3BF,
    V_M187 = 0x3C0,
    V_F187 = 0x3C1,
    V_M191 = 0x3C2,
    V_F191 = 0x3C3,
    V_M192 = 0x3C4,
    V_F192 = 0x3C5,
    V_M196 = 0x3C6,
    V_F196 = 0x3C7,
    V_M198 = 0x3C8,
    V_F198 = 0x3C9,
    V_START2 = 0x3CA,
    V_M007 = 0x3CB,
    V_F007 = 0x3CC,
    V_M010 = 0x3CD,
    V_F010 = 0x3CE,
    V_M012 = 0x3CF,
    V_F012 = 0x3D0,
    V_M239 = 0x3D1,
    V_F239 = 0x3D2,
    V_M242 = 0x3D3,
    V_F242 = 0x3D4,
    V_M243 = 0x3D5,
    V_F243 = 0x3D6,
    V_M244 = 0x3D7,
    V_F244 = 0x3D8,
    V_M247 = 0x3D9,
    V_F247 = 0x3DA,
    V_M249 = 0x3DB,
    V_F249 = 0x3DC,
    V_START3 = 0x3DD,
    V_M049 = 0x3DE,
    V_F049 = 0x3DF,
    V_M050 = 0x3E0,
    V_F050 = 0x3E1,
    V_M085 = 0x3E2,
    V_F085 = 0x3E3,
    V_M089 = 0x3E4,
    V_F089 = 0x3E5,
    V_M094 = 0x3E6,
    V_F094 = 0x3E7,
    V_M095 = 0x3E8,
    V_F095 = 0x3E9,
    V_M201 = 0x3EA,
    V_F201 = 0x3EB,
    V_M210 = 0x3EC,
    V_F210 = 0x3ED,
    V_M211 = 0x3EE,
    V_F211 = 0x3EF,
    V_M219 = 0x3F0,
    V_F219 = 0x3F1,
    V_M220 = 0x3F2,
    V_F220 = 0x3F3,
    V_M224 = 0x3F4,
    V_F224 = 0x3F5,
    V_M229 = 0x3F6,
    V_F229 = 0x3F7,
    V_M230 = 0x3F8,
    V_F230 = 0x3F9,
    V_M231 = 0x3FA,
    V_F231 = 0x3FB,
    V_M232 = 0x3FC,
    V_F232 = 0x3FD,
    V_M255 = 0x3FE,
    V_F255 = 0x3FF,
    V_M256 = 0x400,
    V_F256 = 0x401,
    V_M234 = 0x402,
    V_F234 = 0x403,
    V_M236 = 0x404,
    V_F236 = 0x405,
    V_M250 = 0x406,
    V_F250 = 0x407,
    V_M251 = 0x408,
    V_F251 = 0x409,
    V_M070 = 0x40A,
    V_F070 = 0x40B,
    V_M071 = 0x40C,
    V_F071 = 0x40D,
    V_START4 = 0x40E,
    V_M270 = 0x40F,
    V_F270 = 0x410,
    V_M271 = 0x411,
    V_F271 = 0x412,
    V_M279 = 0x413,
    V_F279 = 0x414,
    V_M280 = 0x415,
    V_F280 = 0x416,
    V_M281 = 0x417,
    V_F281 = 0x418,
    V_M282 = 0x419,
    V_F282 = 0x41A,
    V_M025 = 0x41B,
    V_F025 = 0x41C,
    V_M026 = 0x41D,
    V_F026 = 0x41E,
    V_M031 = 0x41F,
    V_F031 = 0x420,
    V_M032 = 0x421,
    V_F032 = 0x422,
    V_M037 = 0x423,
    V_F037 = 0x424,
    V_M038 = 0x425,
    V_F038 = 0x426,
    V_M043 = 0x427,
    V_F043 = 0x428,
    V_M044 = 0x429,
    V_F044 = 0x42A,
    V_M053 = 0x42B,
    V_F053 = 0x42C,
    V_M057 = 0x42D,
    V_F057 = 0x42E,
    V_M061 = 0x42F,
    V_F061 = 0x430,
    V_M066 = 0x431,
    V_F066 = 0x432,
    V_M075 = 0x433,
    V_F075 = 0x434,
    V_M080 = 0x435,
    V_F080 = 0x436,
    V_M081 = 0x437,
    V_F081 = 0x438,
    V_M093 = 0x439,
    V_F093 = 0x43A,
    V_M098 = 0x43B,
    V_F098 = 0x43C,
    V_M103 = 0x43D,
    V_F103 = 0x43E,
    V_M108 = 0x43F,
    V_F108 = 0x440,
    V_M113 = 0x441,
    V_F113 = 0x442,
    V_M118 = 0x443,
    V_F118 = 0x444,
    V_M122 = 0x445,
    V_F122 = 0x446,
    V_M126 = 0x447,
    V_F126 = 0x448,
    V_M130 = 0x449,
    V_F130 = 0x44A,
    V_M206 = 0x44B,
    V_F206 = 0x44C,
    V_M207 = 0x44D,
    V_F207 = 0x44E,
    V_M215 = 0x44F,
    V_F215 = 0x450,
    V_M216 = 0x451,
    V_F216 = 0x452,
    V_M217 = 0x453,
    V_F217 = 0x454,
    V_START5 = 0x455,
    V_M272 = 0x456,
    V_F272 = 0x457,
    V_M273 = 0x458,
    V_F273 = 0x459,
    V_M275 = 0x45A,
    V_F275 = 0x45B,
    V_M276 = 0x45C,
    V_F276 = 0x45D,
    V_M278 = 0x45E,
    V_F278 = 0x45F,
    V_M176 = 0x460,
    V_F176 = 0x461,
    V_M177 = 0x462,
    V_F177 = 0x463,
    V_M283 = 0x464,
    V_F283 = 0x465,
    V_M013 = 0x466,
    V_F013 = 0x467,
    V_END = 0x468,
    F_COMMT = 0x469,
    F_POWERS = 0x46A,
    F_BARRAC = 0x46B,
    F_SHIELD = 0x46C,
    F_RADAR = 0x46D,
    F_DEPOT = 0x46E,
    F_HANGAR = 0x46F,
    F_DOCK = 0x470,
    F_ADUMP = 0x471,
    F_FDUMP = 0x472,
    F_GOLDSM = 0x473,
    F_POWGEN = 0x474,
    F_CNCT4W = 0x475,
    F_ROAD = 0x476,
    F_LANDPA = 0x477,
    F_SHIPYA = 0x478,
    F_LIGHTP = 0x479,
    F_LANDPL = 0x47A,
    F_SUPRTP = 0x47B,
    F_AIRPLT = 0x47C,
    F_HABITA = 0x47D,
    F_RESEAR = 0x47E,
    F_GREENH = 0x47F,
    F_RECCEN = 0x480,
    F_TRAINH = 0x481,
    F_WTRPLT = 0x482,
    F_GUNTUR = 0x483,
    F_ANTIAI = 0x484,
    F_ARTYTR = 0x485,
    F_ANTIMS = 0x486,
    F_BLOCK = 0x487,
    F_BRIDGE = 0x488,
    F_MINING = 0x489,
    F_LANDMI = 0x48A,
    F_SEAMIN = 0x48B,
    F_MASTER = 0x48C,
    F_CONSTR = 0x48D,
    F_SCOUT = 0x48E,
    F_TANK = 0x48F,
    F_ARTILL = 0x490,
    F_ROCKTL = 0x491,
    F_MISSLL = 0x492,
    F_FLAK = 0x493,
    F_MINELA = 0x494,
    F_SURVEY = 0x495,
    F_SCANNE = 0x496,
    F_SPLYTR = 0x497,
    F_GOLDTR = 0x498,
    F_ENGINE = 0x499,
    F_BULLDO = 0x49A,
    F_REPAIR = 0x49B,
    F_FUELTR = 0x49C,
    F_CLNTRA = 0x49D,
    F_COMMAN = 0x49E,
    F_INFANT = 0x49F,
    F_FASTBO = 0x4A0,
    F_CORVET = 0x4A1,
    F_BATTLS = 0x4A2,
    F_SUBMAR = 0x4A3,
    F_SEATRA = 0x4A4,
    F_MSSLBO = 0x4A5,
    F_SEAMNL = 0x4A6,
    F_CARGOS = 0x4A7,
    F_FIGHTE = 0x4A8,
    F_BOMBER = 0x4A9,
    F_AIRTRA = 0x4AA,
    F_AWAC = 0x4AB,
    F_JUGGRN = 0x4AC,
    F_ALNTAN = 0x4AD,
    F_ALNASG = 0x4AE,
    F_ALNPLA = 0x4AF,
    TRANSFLC = 0x4B0,
    FILESFLC = 0x4B1,
    F_ICE = 0x4B2,
    F_SAND = 0x4B3,
    F_STARS = 0x4B4,
    FILE_BUP = 0x4B5,
    FILE_BDN = 0x4B6,
    FNAME_UP = 0x4B7,
    FNAME_DN = 0x4B8,
    FTYPE_UP = 0x4B9,
    FTYPE_DN = 0x4BA,
    FDESC_UP = 0x4BB,
    FDESC_DN = 0x4BC,
    LOAD_BUP = 0x4BD,
    LOAD_BDN = 0x4BE,
    SAVE_BUP = 0x4BF,
    SAVE_BDN = 0x4C0,
    CNCL_BUP = 0x4C1,
    CNCL_BDN = 0x4C2,
    QUIT_BUP = 0x4C3,
    QUIT_BDN = 0x4C4,
    FILE1_UP = 0x4C5,
    FILE2_UP = 0x4C6,
    FILE3_UP = 0x4C7,
    FILE4_UP = 0x4C8,
    FILE5_UP = 0x4C9,
    FILE6_UP = 0x4CA,
    FILE7_UP = 0x4CB,
    FILE8_UP = 0x4CC,
    FILE9_UP = 0x4CD,
    FILE10UP = 0x4CE,
    FILE1_DN = 0x4CF,
    FILE2_DN = 0x4D0,
    FILE3_DN = 0x4D1,
    FILE4_DN = 0x4D2,
    FILE5_DN = 0x4D3,
    FILE6_DN = 0x4D4,
    FILE7_DN = 0x4D5,
    FILE8_DN = 0x4D6,
    FILE9_DN = 0x4D7,
    FILE10DN = 0x4D8,
    INTROSND = 0x4D9,
    ENEMBEEP = 0x4DA,
    RADRPING = 0x4DB,
    ERRDING = 0x4DC,
    MBUTT0 = 0x4DD,
    MENUOP = 0x4DE,
    NHUMN0 = 0x4DF,
    NCOMP0 = 0x4E0,
    NNONE0 = 0x4E1,
    NCLAN0 = 0x4E2,
    NOPTI0 = 0x4E3,
    NCANC0 = 0x4E4,
    NHELP0 = 0x4E5,
    NDONE0 = 0x4E6,
    CCHOS0 = 0x4E7,
    CCRIM0 = 0x4E8,
    CVONG0 = 0x4E9,
    CAYER0 = 0x4EA,
    CMUSA0 = 0x4EB,
    CSACR0 = 0x4EC,
    CKNIG0 = 0x4ED,
    CAXIS0 = 0x4EE,
    CRAND0 = 0x4EF,
    CCANC0 = 0x4F0,
    CHELP0 = 0x4F1,
    CDONE0 = 0x4F2,
    PWINO0 = 0x4F3,
    PWINC0 = 0x4F4,
    PSELW0 = 0x4F5,
    PSELM0 = 0x4F6,
    PRAND0 = 0x4F7,
    PCANC0 = 0x4F8,
    PHELP0 = 0x4F9,
    PDONE0 = 0x4FA,
    KWINO0 = 0x4FB,
    KWINC0 = 0x4FC,
    KSELE0 = 0x4FD,
    KBUY0 = 0x4FE,
    KCARG0 = 0x4FF,
    KHELP0 = 0x500,
    CBOPE0 = 0x501,
    CBCLO0 = 0x502,
    CBSEL0 = 0x503,
    CBBUI0 = 0x504,
    CBCAN0 = 0x505,
    CBHLP0 = 0x506,
    CBDON0 = 0x507,
    IOPEN0 = 0x508,
    ICLOS0 = 0x509,
    IZOOM0 = 0x50A,
    ISTAT0 = 0x50B,
    ICOLO0 = 0x50C,
    IHITS0 = 0x50D,
    IAMMO0 = 0x50E,
    IRANG0 = 0x50F,
    IVISI0 = 0x510,
    IGRID0 = 0x511,
    ISURV0 = 0x512,
    INAME0 = 0x513,
    FOPEN = 0x514,
    FCLOS = 0x515,
    FBUBB = 0x516,
    FSAVE = 0x517,
    FQUIT = 0x518,
    FCANC = 0x519,
    FHELP = 0x51A,
    FLOAD = 0x51B,
    FXS_STRT = 0x51C,
    GEN_IDLE = 0x51D,
    WGN_IDLE = 0x51E,
    GEN_DRVE = 0x51F,
    WGN_DRVE = 0x520,
    GEN_STOP = 0x521,
    WGN_STOP = 0x522,
    GEN_XFRM = 0x523,
    GEN_BLDG = 0x524,
    GEN_SHNK = 0x525,
    GEN_XPND = 0x526,
    GEN_TRRT = 0x527,
    GEN_FIRE = 0x528,
    GEN_HIT = 0x529,
    GEN_XPLD = 0x52A,
    GEN_PRCS = 0x52B,
    GEN_PRCE = 0x52C,
    GEN_LAND = 0x52D,
    GEN_TAKE = 0x52E,
    MONOP10 = 0x52F,
    MONOP15 = 0x530,
    MONOP16 = 0x531,
    MONOP17 = 0x532,
    MONOP18 = 0x533,
    POWST10 = 0x534,
    POWST15 = 0x535,
    POWST16 = 0x536,
    POWST17 = 0x537,
    POWST18 = 0x538,
    POWGN10 = 0x539,
    POWGN15 = 0x53A,
    POWGN16 = 0x53B,
    POWGN17 = 0x53C,
    POWGN18 = 0x53D,
    BARRA10 = 0x53E,
    BARRA15 = 0x53F,
    BARRA16 = 0x540,
    BARRA17 = 0x541,
    BARRA18 = 0x542,
    GOLDR10 = 0x543,
    GOLDR15 = 0x544,
    GOLDR16 = 0x545,
    GOLDR17 = 0x546,
    GOLDR18 = 0x547,
    RADAR13 = 0x548,
    RADAR15 = 0x549,
    RADAR16 = 0x54A,
    SSTOR15 = 0x54B,
    SSTOR16 = 0x54C,
    SSTOR17 = 0x54D,
    SFUEL15 = 0x54E,
    SFUEL16 = 0x54F,
    SFUEL17 = 0x550,
    SGOLD15 = 0x551,
    SGOLD16 = 0x552,
    SGOLD17 = 0x553,
    DEPOT10 = 0x554,
    DEPOT15 = 0x555,
    DEPOT16 = 0x556,
    DEPOT17 = 0x557,
    DEPOT18 = 0x558,
    HANGR10 = 0x559,
    HANGR15 = 0x55A,
    HANGR16 = 0x55B,
    HANGR17 = 0x55C,
    HANGR18 = 0x55D,
    DOCK10 = 0x55E,
    DOCK15 = 0x55F,
    DOCK16 = 0x560,
    DOCK17 = 0x561,
    DOCK18 = 0x562,
    ROAD15 = 0x563,
    ROAD16 = 0x564,
    LPAD10 = 0x565,
    LPAD15 = 0x566,
    LPAD16 = 0x567,
    SUNIT10 = 0x568,
    SUNIT15 = 0x569,
    SUNIT16 = 0x56A,
    SUNIT17 = 0x56B,
    SUNIT18 = 0x56C,
    LVP10 = 0x56D,
    LVP15 = 0x56E,
    LVP16 = 0x56F,
    LVP17 = 0x570,
    LVP18 = 0x571,
    HVP10 = 0x572,
    HVP15 = 0x573,
    HVP16 = 0x574,
    HVP17 = 0x575,
    HVP18 = 0x576,
    AUNIT10 = 0x577,
    AUNIT15 = 0x578,
    AUNIT16 = 0x579,
    AUNIT17 = 0x57A,
    AUNIT18 = 0x57B,
    DORMI10 = 0x57C,
    DORMI15 = 0x57D,
    DORMI16 = 0x57E,
    DORMI17 = 0x57F,
    DORMI18 = 0x580,
    RESEAR10 = 0x581,
    RESEAR15 = 0x582,
    RESEAR16 = 0x583,
    RESEAR17 = 0x584,
    RESEAR18 = 0x585,
    ECOSP10 = 0x586,
    ECOSP15 = 0x587,
    ECOSP16 = 0x588,
    ECOSP17 = 0x589,
    ECOSP18 = 0x58A,
    TRAIN10 = 0x58B,
    TRAIN15 = 0x58C,
    TRAIN16 = 0x58D,
    TRAIN17 = 0x58E,
    TRAIN18 = 0x58F,
    WPLAT15 = 0x590,
    WPLAT16 = 0x591,
    FGUN13 = 0x592,
    FGUN14 = 0x593,
    FGUN15 = 0x594,
    FGUN16 = 0x595,
    FANTI13 = 0x596,
    FANTI14 = 0x597,
    FANTI15 = 0x598,
    FANTI16 = 0x599,
    FARTY13 = 0x59A,
    FARTY14 = 0x59B,
    FARTY15 = 0x59C,
    FARTY16 = 0x59D,
    FROCK13 = 0x59E,
    FROCK14 = 0x59F,
    FROCK15 = 0x5A0,
    FROCK16 = 0x5A1,
    BLOCK15 = 0x5A2,
    BLOCK16 = 0x5A3,
    BRIDG15 = 0x5A4,
    BRIDG16 = 0x5A5,
    MSTAT10 = 0x5A6,
    MSTAT15 = 0x5A7,
    MSTAT16 = 0x5A8,
    MSTAT17 = 0x5A9,
    MSTAT18 = 0x5AA,
    LMINE16 = 0x5AB,
    CMINE16 = 0x5AC,
    EMPTYLND = 0x5AD,
    EMPTYWTR = 0x5AE,
    MASTR1 = 0x5AF,
    MASTR5 = 0x5B0,
    MASTR7 = 0x5B1,
    MASTR9 = 0x5B2,
    MASTR15 = 0x5B3,
    MASTR16 = 0x5B4,
    CONST1 = 0x5B5,
    CONST2 = 0x5B6,
    CONST5 = 0x5B7,
    CONST6 = 0x5B8,
    CONST7 = 0x5B9,
    CONST8 = 0x5BA,
    CONST10 = 0x5BB,
    CONST15 = 0x5BC,
    CONST16 = 0x5BD,
    SCOUT1 = 0x5BE,
    SCOUT2 = 0x5BF,
    SCOUT5 = 0x5C0,
    SCOUT6 = 0x5C1,
    SCOUT7 = 0x5C2,
    SCOUT8 = 0x5C3,
    SCOUT14 = 0x5C4,
    SCOUT15 = 0x5C5,
    SCOUT16 = 0x5C6,
    TANK1 = 0x5C7,
    TANK5 = 0x5C8,
    TANK7 = 0x5C9,
    TANK14 = 0x5CA,
    TANK15 = 0x5CB,
    TANK16 = 0x5CC,
    ASGUN1 = 0x5CD,
    ASGUN5 = 0x5CE,
    ASGUN7 = 0x5CF,
    ASGUN14 = 0x5D0,
    ASGUN15 = 0x5D1,
    ASGUN16 = 0x5D2,
    RLNCH1 = 0x5D3,
    RLNCH5 = 0x5D4,
    RLNCH7 = 0x5D5,
    RLNCH14 = 0x5D6,
    RLNCH15 = 0x5D7,
    RLNCH16 = 0x5D8,
    MSLNC1 = 0x5D9,
    MSLNC5 = 0x5DA,
    MSLNC7 = 0x5DB,
    MSLNC14 = 0x5DC,
    MSLNC15 = 0x5DD,
    MSLNC16 = 0x5DE,
    MANTI1 = 0x5DF,
    MANTI5 = 0x5E0,
    MANTI7 = 0x5E1,
    MANTI14 = 0x5E2,
    MANTI15 = 0x5E3,
    MANTI16 = 0x5E4,
    MLAYER1 = 0x5E5,
    MLAYER5 = 0x5E6,
    MLAYER7 = 0x5E7,
    MLAYER15 = 0x5E8,
    MLAYER16 = 0x5E9,
    MLAYER17 = 0x5EA,
    MLAYER18 = 0x5EB,
    SURVY1 = 0x5EC,
    SURVY2 = 0x5ED,
    SURVY5 = 0x5EE,
    SURVY6 = 0x5EF,
    SURVY7 = 0x5F0,
    SURVY8 = 0x5F1,
    SURVY15 = 0x5F2,
    SURVY16 = 0x5F3,
    SCAN1 = 0x5F4,
    SCAN5 = 0x5F5,
    SCAN7 = 0x5F6,
    SCAN15 = 0x5F7,
    SCAN16 = 0x5F8,
    MTRUK1 = 0x5F9,
    MTRUK5 = 0x5FA,
    MTRUK7 = 0x5FB,
    MTRUK15 = 0x5FC,
    MTRUK16 = 0x5FD,
    MTRUK17 = 0x5FE,
    GTRUK1 = 0x5FF,
    GTRUK5 = 0x600,
    GTRUK7 = 0x601,
    GTRUK15 = 0x602,
    GTRUK16 = 0x603,
    GTRUK17 = 0x604,
    ENGIN1 = 0x605,
    ENGIN2 = 0x606,
    ENGIN5 = 0x607,
    ENGIN6 = 0x608,
    ENGIN7 = 0x609,
    ENGIN8 = 0x60A,
    ENGIN10 = 0x60B,
    ENGIN15 = 0x60C,
    ENGIN16 = 0x60D,
    BULL1 = 0x60E,
    BULL5 = 0x60F,
    BULL7 = 0x610,
    BULL10 = 0x611,
    BULL15 = 0x612,
    BULL16 = 0x613,
    REPAIR1 = 0x614,
    REPAIR5 = 0x615,
    REPAIR7 = 0x616,
    REPAIR15 = 0x617,
    REPAIR16 = 0x618,
    REPAIR17 = 0x619,
    FTRUK1 = 0x61A,
    FTRUK5 = 0x61B,
    FTRUK7 = 0x61C,
    FTRUK15 = 0x61D,
    FTRUK16 = 0x61E,
    FTRUK17 = 0x61F,
    APC1 = 0x620,
    APC2 = 0x621,
    APC5 = 0x622,
    APC6 = 0x623,
    APC7 = 0x624,
    APC8 = 0x625,
    APC15 = 0x626,
    APC16 = 0x627,
    APC17 = 0x628,
    APC18 = 0x629,
    INFIL5 = 0x62A,
    INFIL14 = 0x62B,
    INFIL15 = 0x62C,
    INFIL16 = 0x62D,
    INFIL17 = 0x62E,
    INFAN5 = 0x62F,
    INFAN14 = 0x630,
    INFAN15 = 0x631,
    INFAN16 = 0x632,
    ESCRT2 = 0x633,
    ESCRT6 = 0x634,
    ESCRT8 = 0x635,
    ESCRT14 = 0x636,
    ESCRT15 = 0x637,
    ESCRT16 = 0x638,
    CORVT2 = 0x639,
    CORVT6 = 0x63A,
    CORVT8 = 0x63B,
    CORVT14 = 0x63C,
    CORVT15 = 0x63D,
    CORVT16 = 0x63E,
    GUNBT2 = 0x63F,
    GUNBT6 = 0x640,
    GUNBT8 = 0x641,
    GUNBT14 = 0x642,
    GUNBT15 = 0x643,
    GUNBT16 = 0x644,
    SUB2 = 0x645,
    SUB6 = 0x646,
    SUB8 = 0x647,
    SUB14 = 0x648,
    SUB15 = 0x649,
    SUB16 = 0x64A,
    STRANS2 = 0x64B,
    STRANS6 = 0x64C,
    STRANS8 = 0x64D,
    STRANS15 = 0x64E,
    STRANS16 = 0x64F,
    STRANS17 = 0x650,
    STRANS18 = 0x651,
    MSLCR2 = 0x652,
    MSLCR6 = 0x653,
    MSLCR8 = 0x654,
    MSLCR14 = 0x655,
    MSLCR15 = 0x656,
    MSLCR16 = 0x657,
    SMINE2 = 0x658,
    SMINE6 = 0x659,
    SMINE8 = 0x65A,
    SMINE15 = 0x65B,
    SMINE16 = 0x65C,
    SMINE17 = 0x65D,
    SMINE18 = 0x65E,
    CSHIP2 = 0x65F,
    CSHIP6 = 0x660,
    CSHIP8 = 0x661,
    CSHIP15 = 0x662,
    CSHIP16 = 0x663,
    CSHIP17 = 0x664,
    FIGHT1 = 0x665,
    FIGHT5 = 0x666,
    FIGHT7 = 0x667,
    FIGHT14 = 0x668,
    FIGHT15 = 0x669,
    FIGHT16 = 0x66A,
    FIGHT19 = 0x66B,
    FIGHT20 = 0x66C,
    ATACK1 = 0x66D,
    ATACK5 = 0x66E,
    ATACK7 = 0x66F,
    ATACK14 = 0x670,
    ATACK15 = 0x671,
    ATACK16 = 0x672,
    ATACK19 = 0x673,
    ATACK20 = 0x674,
    ATRANS1 = 0x675,
    ATRANS5 = 0x676,
    ATRANS7 = 0x677,
    ATRANS15 = 0x678,
    ATRANS16 = 0x679,
    ATRANS17 = 0x67A,
    ATRANS18 = 0x67B,
    ATRANS19 = 0x67C,
    ATRANS20 = 0x67D,
    AWAC1 = 0x67E,
    AWAC5 = 0x67F,
    AWAC7 = 0x680,
    AWAC14 = 0x681,
    AWAC15 = 0x682,
    AWAC16 = 0x683,
    AWAC19 = 0x684,
    AWAC20 = 0x685,
    JUGGR1 = 0x686,
    JUGGR5 = 0x687,
    JUGGR7 = 0x688,
    JUGGR14 = 0x689,
    JUGGR15 = 0x68A,
    JUGGR16 = 0x68B,
    ALNTK1 = 0x68C,
    ALNTK5 = 0x68D,
    ALNTK7 = 0x68E,
    ALNTK14 = 0x68F,
    ALNTK15 = 0x690,
    ALNTK16 = 0x691,
    ALNAG1 = 0x692,
    ALNAG5 = 0x693,
    ALNAG7 = 0x694,
    ALNAG14 = 0x695,
    ALNAG15 = 0x696,
    ALNAG16 = 0x697,
    ALNPL1 = 0x698,
    ALNPL5 = 0x699,
    ALNPL7 = 0x69A,
    ALNPL14 = 0x69B,
    ALNPL15 = 0x69C,
    ALNPL16 = 0x69D,
    ALNPL19 = 0x69E,
    ALNPL20 = 0x69F,
    FXS_END = 0x6A0,
    SNOW_MSC = 0x6A1,
    CRTR_MSC = 0x6A2,
    GREN_MSC = 0x6A3,
    DSRT_MSC = 0x6A4,
    MAIN_MSC = 0x6A5,
    BKG1_MSC = 0x6A6,
    BKG2_MSC = 0x6A7,
    BKG3_MSC = 0x6A8,
    BKG4_MSC = 0x6A9,
    BKG5_MSC = 0x6AA,
    BKG6_MSC = 0x6AB,
    BKG7_MSC = 0x6AC,
    BKG8_MSC = 0x6AD,
    BKG9_MSC = 0x6AE,
    CRGO_MSC = 0x6AF,
    CRDT_MSC = 0x6B0,
    WINR_MSC = 0x6B1,
    LOSE_MSC = 0x6B2,
    LOGOFLIC = 0x6B3,
    INTROFLC = 0x6B4,
    DEMO1FLC = 0x6B5,
    DEMO2FLC = 0x6B6,
    DEMO3FLC = 0x6B7,
    DEMO4FLC = 0x6B8,
    DEMO5FLC = 0x6B9,
    REPORTS = 0x6BA,
    REP_FRME = 0x6BB,
    ALLOCFRM = 0x6BC,
    STATS = 0x6BD,
    FRAMEPIC = 0x6BE,
    INTROPIC = 0x6BF,
    MAINPIC = 0x6C0,
    SETUPPIC = 0x6C1,
    LOADPIC = 0x6C2,
    NETPIC = 0x6C3,
    OPTPIC = 0x6C4,
    LSTATPIC = 0x6C5,
    EXITPIC = 0x6C6,
    FACBUILD = 0x6C7,
    CONBUILD = 0x6C8,
    QWKBUILD = 0x6C9,
    UPGRADE = 0x6CA,
    CARGOPIC = 0x6CB,
    XFERPIC = 0x6CC,
    PREFSPIC = 0x6CD,
    CLANSEL = 0x6CE,
    PLANETSE = 0x6CF,
    MULTGAME = 0x6D0,
    CHATWNDO = 0x6D1,
    DEPOTFRM = 0x6D2,
    HANGRFRM = 0x6D3,
    DOCKFRM = 0x6D4,
    RSRCHPIC = 0x6D5,
    ENDGAME1 = 0x6D6,
    ENDGAME2 = 0x6D7,
    ENDGAME3 = 0x6D8,
    ENDGAME4 = 0x6D9,
    ENDGAME5 = 0x6DA,
    ENDGAME6 = 0x6DB,
    ENDGAME7 = 0x6DC,
    ENDGAME8 = 0x6DD,
    ENDGAME9 = 0x6DE,
    ENDGAM10 = 0x6DF,
    ENDGAM11 = 0x6E0,
    ENDGAM12 = 0x6E1,
    ENDGAM13 = 0x6E2,
    ENDGAM14 = 0x6E3,
    ENDARM = 0x6E4,
    DIALGPIC = 0x6E5,
    HELPFRAM = 0x6E6,
    ILOGO = 0x6E7,
    MLOGO = 0x6E8,
    SELFDSTR = 0x6E9,
    CREDITS = 0x6EA,
    STARTNET = 0x6EB,
    JOINNET = 0x6EC,
    STARTMOD = 0x6ED,
    CHOSPLYR = 0x6EE,
    BLACKOUT = 0x6EF,
    OEMONE = 0x6F0,
    OEMTWO = 0x6F1,
    OPTNFRM = 0x6F2,
    P_TRANSP = 0x6F3,
    P_POWSTN = 0x6F4,
    P_POWGEN = 0x6F5,
    P_BARRCK = 0x6F6,
    P_SHIELD = 0x6F7,
    P_RADAR = 0x6F8,
    P_SMSTOR = 0x6F9,
    P_SMFUEL = 0x6FA,
    P_SMVLT = 0x6FB,
    P_DEPOT = 0x6FC,
    P_HANGAR = 0x6FD,
    P_DOCK = 0x6FE,
    P_CONNEC = 0x6FF,
    P_ROAD = 0x700,
    P_LANDPD = 0x701,
    P_SHIPYD = 0x702,
    P_LGHTPL = 0x703,
    P_HVYPLT = 0x704,
    P_LIFESP = 0x705,
    P_AIRPLT = 0x706,
    P_HABITA = 0x707,
    P_RESEAR = 0x708,
    P_GREENH = 0x709,
    P_RECCTR = 0x70A,
    P_TRNHLL = 0x70B,
    P_WATER = 0x70C,
    P_GUNTUR = 0x70D,
    P_FXAA = 0x70E,
    P_ARTYTR = 0x70F,
    P_FXROCK = 0x710,
    P_BLOCK = 0x711,
    P_BRIDGE = 0x712,
    P_MINING = 0x713,
    P_LANDMN = 0x714,
    P_SEAMIN = 0x715,
    P_MASTER = 0x716,
    P_CONTRC = 0x717,
    P_SCOUT = 0x718,
    P_TANK = 0x719,
    P_ARTY = 0x71A,
    P_ROCKET = 0x71B,
    P_MISSIL = 0x71C,
    P_AA = 0x71D,
    P_MNELAY = 0x71E,
    P_SURVEY = 0x71F,
    P_SCANNR = 0x720,
    P_SPLYTR = 0x721,
    P_GOLDTR = 0x722,
    P_ENGINR = 0x723,
    P_BULLDZ = 0x724,
    P_REPAIR = 0x725,
    P_FUELTR = 0x726,
    P_COLNST = 0x727,
    P_COMMAN = 0x728,
    P_INFANT = 0x729,
    P_ESCORT = 0x72A,
    P_CORVET = 0x72B,
    P_GUNBT = 0x72C,
    P_SUB = 0x72D,
    P_SEATRN = 0x72E,
    P_MSLCR = 0x72F,
    P_SEAMNL = 0x730,
    P_CARGOS = 0x731,
    P_FIGHTR = 0x732,
    P_BOMBER = 0x733,
    P_AIRTRN = 0x734,
    P_AWAC = 0x735,
    P_JUGGER = 0x736,
    P_ALNTAN = 0x737,
    P_ALNASG = 0x738,
    P_ALNPLA = 0x739,
    A_MASTER = 0x73A,
    A_CONTRC = 0x73B,
    A_SCOUT = 0x73C,
    A_TANK = 0x73D,
    A_ARTY = 0x73E,
    A_ROCKET = 0x73F,
    A_MISSIL = 0x740,
    A_AA = 0x741,
    A_MNELAY = 0x742,
    A_SURVEY = 0x743,
    A_SCANNR = 0x744,
    A_SPLYTR = 0x745,
    A_GOLDTR = 0x746,
    A_ENGINR = 0x747,
    A_BULLDZ = 0x748,
    A_REPAIR = 0x749,
    A_FUELTR = 0x74A,
    A_COLNST = 0x74B,
    A_COMMAN = 0x74C,
    A_INFANT = 0x74D,
    A_ESCORT = 0x74E,
    A_CORVET = 0x74F,
    A_GUNBT = 0x750,
    A_SUB = 0x751,
    A_SEATRN = 0x752,
    A_MSLCR = 0x753,
    A_SEAMNL = 0x754,
    A_CARGOS = 0x755,
    A_FIGHTR = 0x756,
    A_BOMBER = 0x757,
    A_AIRTRN = 0x758,
    A_AWAC = 0x759,
    A_JUGGER = 0x75A,
    A_ALNTAN = 0x75B,
    A_ALNASG = 0x75C,
    A_ALNPLA = 0x75D,
    E_DEPOT = 0x75E,
    E_HANGAR = 0x75F,
    E_DOCK = 0x760,
    ATTRIBS = 0x761,
    CLANATRB = 0x762,
    SOUNDVOL = 0x763,
    TIPS = 0x764,
    HELP_ENG = 0x765,
    HELP_FRE = 0x766,
    HELP_GRM = 0x767,
    SNOW_PIC = 0x768,
    CRTR_PIC = 0x769,
    GREN_PIC = 0x76A,
    DSRT_PIC = 0x76B,
    STAR_PIC = 0x76C,
    WORLD_S = 0x76D,
    SNOW_1 = 0x76E,
    SNOW_2 = 0x76F,
    SNOW_3 = 0x770,
    SNOW_4 = 0x771,
    SNOW_5 = 0x772,
    SNOW_6 = 0x773,
    CRATER_1 = 0x774,
    CRATER_2 = 0x775,
    CRATER_3 = 0x776,
    CRATER_4 = 0x777,
    CRATER_5 = 0x778,
    CRATER_6 = 0x779,
    GREEN_1 = 0x77A,
    GREEN_2 = 0x77B,
    GREEN_3 = 0x77C,
    GREEN_4 = 0x77D,
    GREEN_5 = 0x77E,
    GREEN_6 = 0x77F,
    DESERT_1 = 0x780,
    DESERT_2 = 0x781,
    DESERT_3 = 0x782,
    DESERT_4 = 0x783,
    DESERT_5 = 0x784,
    DESERT_6 = 0x785,
    WORLD_E = 0x786,
    RESOURCE_E = 0x787,
    INVALID_ID = -1
} GAME_RESOURCE;

typedef struct GameResourceMeta_s GameResourceMeta;

void *read_game_resource(GAME_RESOURCE id);
int read_game_resource_into_buffer(GAME_RESOURCE id, void *buffer);

#endif /* RESRCMGR_H */
