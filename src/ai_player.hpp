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

#ifndef AI_PLAYER_HPP
#define AI_PLAYER_HPP

#include "terrainmap.hpp"
#include "threatmap.hpp"
#include "unitinfo.hpp"

class AiPlayer {
public:
    AiPlayer();
    ~AiPlayer();

    void SetInfoMapPoint(Point point);
    void UpdateMineMap(Point point);
    void MarkMineMapPoint(Point point);
    void ChangeTasksPendingFlag(bool value);
    bool SelectStrategy();
    void PlanMinefields();
    void GuessEnemyAttackDirections();
    bool CreateBuilding(ResourceID unit_type, Point position, Task* task);
    bool IsUpgradeNeeded(UnitInfo* unit);
    void ClearZone(Zone* zone);
    unsigned char** GetInfoMap();
};

extern AiPlayer AiPlayer_Teams[4];
extern TerrainMap AiPlayer_TerrainMap;
extern ThreatMap AiPlayer_ThreatMaps[10];

#endif /* AI_PLAYER_HPP */
