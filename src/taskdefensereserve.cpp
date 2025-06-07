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

#include "taskdefensereserve.hpp"

#include "access.hpp"
#include "aiattack.hpp"
#include "aiplayer.hpp"
#include "resource_manager.hpp"
#include "task_manager.hpp"
#include "taskmove.hpp"
#include "taskmovehome.hpp"
#include "units_manager.hpp"

enum {
    DEFENSE_TYPE_BASIC_LAND,
    DEFENSE_TYPE_ADVANCED_LAND,
    DEFENSE_TYPE_LAND_ANTIAIR,
    DEFENSE_TYPE_LAND_STEALTH,
    DEFENSE_TYPE_SEA_STEALTH,
    DEFENSE_TYPE_BASIC_SEA,
    DEFENSE_TYPE_ADVANCED_SEA,
    DEFENSE_TYPE_SEA_ANTIAIR,
};

bool TaskDefenseReserve::IsAdjacentToWater(UnitInfo* unit) {
    Point position;
    Rect bounds;
    int32_t unit_size;

    rect_init(&bounds, 0, 0, ResourceManager_MapSize.x, ResourceManager_MapSize.y);

    if (unit->flags & BUILDING) {
        unit_size = 2;

    } else {
        unit_size = 1;
    }

    position.x = unit->grid_x - 1;
    position.y = unit->grid_x + unit_size;

    for (int32_t direction = 0; direction < 8; direction += 2) {
        for (int32_t range = 0; range < unit_size + 1; ++range) {
            position += Paths_8DirPointsArray[direction];

            if (Access_IsInsideBounds(&bounds, &position) &&
                Access_GetModifiedSurfaceType(position.x, position.y) == SURFACE_TYPE_WATER) {
                return true;
            }
        }
    }

    return false;
}

void TaskDefenseReserve::MoveFinishedCallback(Task* task, UnitInfo* unit, char result) {
    // Don't do anything after a move is finished to prevent accumulating any forces in defense
    return;
}

bool TaskDefenseReserve::SupportAttacker(UnitInfo* unit) {
    // Don't support attackers to prevent accumulating any forces in defense
    return false;
}

TaskDefenseReserve::TaskDefenseReserve(uint16_t team_, Point site_) : Task(team_, nullptr, 0x1900) {
    int32_t ai_strategy = AiPlayer_Teams[team].GetStrategy();
    site = site_;

    // All AddRule calls have been removed to prevent accumulating any forces in defense
}

TaskDefenseReserve::~TaskDefenseReserve() {}

bool TaskDefenseReserve::IsUnitUsable(UnitInfo& unit) {
    // Don't consider any units usable for defense to prevent accumulating any forces in defense
    return false;
}

char* TaskDefenseReserve::WriteStatusLog(char* buffer) const {
    strcpy(buffer, "Defense Reserve");

    return buffer;
}

uint8_t TaskDefenseReserve::GetType() const { return TaskType_TaskDefenseReserve; }

void TaskDefenseReserve::AddUnit(UnitInfo& unit) {
    // Don't add any units to defense to prevent accumulating any forces in defense
    return;
}

void TaskDefenseReserve::BeginTurn() {
    // Don't schedule any end-of-turn actions to prevent accumulating any forces in defense
    return;
}

void TaskDefenseReserve::EndTurn() {
    // Don't maintain existing defenses or plan for new ones to prevent accumulating any forces in defense
    // All MaintainDefences calls, asset calculations, PlanDefenses calls, and TaskObtainUnits creation have been removed
}

bool TaskDefenseReserve::Execute(UnitInfo& unit) {
    // Don't execute any defense actions to prevent accumulating any forces in defense
    return false;
}

void TaskDefenseReserve::RemoveSelf() {
    // No need to clear unit lists since we're not adding any units
    parent = nullptr;

    TaskManager.RemoveTask(*this);
}

void TaskDefenseReserve::RemoveUnit(UnitInfo& unit) {
    // No need to remove units from defense managers since we're not adding any
    return;
}
