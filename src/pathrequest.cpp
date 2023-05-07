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

#include "pathrequest.hpp"

#include "access.hpp"
#include "ailog.hpp"
#include "remote.hpp"
#include "sound_manager.hpp"
#include "units_manager.hpp"

const char* PathRequest_CautionLevels[] = {"none", "avoid reaction fire", "avoid next turn's fire", "avoid all damage"};

PathRequest::PathRequest(UnitInfo* unit, int mode, Point point) : unit1(unit), point(point), flags(mode) {
    AiLog log("Path request for %s at [%i,%i].", UnitsManager_BaseUnits[unit1->unit_type].singular_name,
              unit1->grid_x + 1, unit1->grid_y + 1);

    max_cost = INT16_MAX;
    minimum_distance = 0;
    caution_level = 0;
    board_transport = 0;
    optimize = 1;
}

PathRequest::~PathRequest() {}

UnitInfo* PathRequest::GetClient() const { return &*unit1; }

UnitInfo* PathRequest::GetTransporter() const { return &*unit2; }

Point PathRequest::GetDestination() const { return point; }

unsigned char PathRequest::GetCautionLevel() const { return caution_level; }

bool PathRequest::PathRequest_Vfunc1() { return false; }

void PathRequest::Cancel() {
    if (unit1->hits &&
        (unit1->orders == ORDER_MOVE || unit1->orders == ORDER_MOVE_TO_UNIT || unit1->orders == ORDER_MOVE_TO_ATTACK) &&
        unit1->state == ORDER_STATE_NEW_ORDER) {
        UnitsManager_SetNewOrder(&*unit1, unit1->orders, ORDER_STATE_12);
    }

    Access_ProcessNewGroupOrder(&*unit1);
}

void PathRequest::SetMaxCost(int value) {
    AiLog log("Max cost: %i.", value);

    max_cost = value;
}

void PathRequest::SetMinimumDistance(int value) {
    AiLog log("Minimum distance: %i.", value);

    minimum_distance = value;
}

void PathRequest::SetCautionLevel(int value) {
    AiLog log("Caution level: %s.", PathRequest_CautionLevels[value]);

    caution_level = value;
}

void PathRequest::SetBoardTransport(bool value) {
    AiLog log("Board transport: %s.", value ? "True" : "False");

    board_transport = value;
}

void PathRequest::SetOptimizeFlag(bool value) {
    AiLog log("Optimize: %s", value ? "True" : "False");

    optimize = value;
}

void PathRequest::CreateTransport(ResourceID unit_type) {
    if (unit_type != INVALID_ID) {
        AiLog log("Use %s.", UnitsManager_BaseUnits[unit_type].singular_name);

        unit2 = new (std::nothrow) UnitInfo(unit_type, unit1->team, 0xFFFF);

    } else {
        unit2 = nullptr;
    }
}

unsigned char PathRequest::GetFlags() const { return flags; }

unsigned short PathRequest::GetMaxCost() const { return max_cost; }

unsigned char PathRequest::GetBoardTransport() const { return board_transport; }

unsigned short PathRequest::GetMinimumDistance() const { return minimum_distance; }

void PathRequest::AssignGroundPath(UnitInfo* unit, GroundPath* path) {
    Point destination(unit->target_grid_x, unit->target_grid_y);
    SmartObjectArray<PathStep> steps = path->GetSteps();
    SmartPointer<GroundPath> ground_path(new (std::nothrow) GroundPath(destination.x, destination.y));
    int range = unit->GetBaseValues()->GetAttribute(ATTRIB_RANGE);
    Point position(unit->grid_x, unit->grid_y);
    int index;

    range = range * range;

    for (index = 0; index < steps.GetCount() && Access_GetDistance(position, destination) > range; ++index) {
        position.x += steps[index]->x;
        position.y += steps[index]->y;

        ground_path->AddStep(steps[index]->x, steps[index]->y);
    }

    if (index > 0) {
        unit->path = &*ground_path;

        if (unit->flags & MOBILE_AIR_UNIT) {
            unit->path->SetEndXY(position.x, position.y);
            unit->path = Paths_GetAirPath(unit);
        }

    } else {
        unit->path = nullptr;
    }
}

void PathRequest::Finish(GroundPath* path) {
    if (unit1->hits > 0 &&
        (unit1->orders == ORDER_MOVE || unit1->orders == ORDER_MOVE_TO_UNIT || unit1->orders == ORDER_BUILD ||
         unit1->orders == ORDER_MOVE_TO_ATTACK) &&
        (unit1->state == ORDER_STATE_NEW_ORDER || unit1->state == ORDER_STATE_29)) {
        unsigned char unit1_order_state = unit1->state;

        unit1->path = path;

        if (unit1->orders == ORDER_MOVE_TO_ATTACK && path != nullptr) {
            AssignGroundPath(&*unit1, path);
        }

        if (unit1->path == nullptr) {
            if (unit1->orders == ORDER_MOVE_TO_ATTACK) {
                int range = unit1->GetBaseValues()->GetAttribute(ATTRIB_RANGE);

                range = range * range;

                if (Access_GetDistance(&*unit1, Point(unit1->target_grid_x, unit1->target_grid_y)) <= range) {
                    UnitsManager_SetNewOrder(&*unit1, ORDER_MOVE_TO_ATTACK, ORDER_STATE_1);
                    unit1->RefreshScreen();
                    Access_ProcessNewGroupOrder(&*unit1);

                    return;
                }
            }

            unit1->BlockedOnPathRequest(false);

            if (Remote_IsNetworkGame) {
                Remote_SendNetPacket_41(&*unit1);
            }

            if (unit1->GetUnitList() && unit1_order_state == ORDER_STATE_NEW_ORDER) {
                unit1->ClearUnitList();
            }

            if (GameManager_SelectedUnit == unit1) {
                SoundManager.PlayVoice(V_M094, V_F095);
            }

        } else {
            if (unit1->orders == ORDER_BUILD) {
                if (Remote_IsNetworkGame) {
                    Remote_SendNetPacket_38(&*unit1);
                }

                UnitsManager_StartBuild(&*unit1);

            } else if (unit1->state == ORDER_STATE_29) {
                if (unit1->orders == ORDER_MOVE_TO_ATTACK) {
                    unit1->state = ORDER_STATE_1;

                } else {
                    unit1->RestoreOrders();
                }

                if (Remote_IsNetworkGame) {
                    Remote_SendNetPacket_38(&*unit1);
                }

                GameManager_UpdateDrawBounds();

            } else if (unit1->GetUnitList()) {
                if (Remote_IsNetworkGame) {
                    Remote_SendNetPacket_38(&*unit1);
                }

                Access_ProcessNewGroupOrder(&*unit1);

            } else {
                unit1->Redraw();
                unit1->state = ORDER_STATE_5;

                if (Remote_IsNetworkGame) {
                    Remote_SendNetPacket_38(&*unit1);
                }
            }
        }
    }
}
