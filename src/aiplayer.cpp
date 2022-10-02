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

#include "aiplayer.hpp"

AiPlayer AiPlayer_Teams[4];
TerrainMap AiPlayer_TerrainMap;
ThreatMap AiPlayer_ThreatMaps[10];

/// \todo

int AiPlayer_CalculateProjectedDamage(UnitInfo* friendly_unit, UnitInfo* enemy_unit, int caution_level) {}

int AiPlayer_GetProjectedDamage(UnitInfo* friendly_unit, UnitInfo* enemy_unit, int caution_level) {}

AiPlayer::AiPlayer() {}

AiPlayer::~AiPlayer() {}

void AiPlayer::SetInfoMapPoint(Point point) {}

void AiPlayer::UpdateMineMap(Point point) {}

void AiPlayer::MarkMineMapPoint(Point point) {}

void AiPlayer::ChangeTasksPendingFlag(bool value) {}

bool AiPlayer::SelectStrategy() {}

void AiPlayer::PlanMinefields() {}

void AiPlayer::GuessEnemyAttackDirections() {}

bool AiPlayer::CreateBuilding(ResourceID unit_type, Point position, Task* task) {}

bool AiPlayer::IsUpgradeNeeded(UnitInfo* unit) {}

bool AiPlayer::MatchPath(TaskPathRequest* request) {}

void AiPlayer::ClearZone(Zone* zone) {}

unsigned char** AiPlayer::GetInfoMap() {}

unsigned short** AiPlayer::GetDamagePotentialMap(UnitInfo* unit, int caution_level, unsigned char flags) {}

unsigned short** AiPlayer::GetDamagePotentialMap(ResourceID unit_type, int caution_level, unsigned char flags) {}

int AiPlayer::GetDamagePotential(UnitInfo* unit, Point point, int caution_level, unsigned char flags) {}

void AiPlayer::AddTransportOrder(TransportOrder* transport_order) {}

Task* AiPlayer::FindManager(Point site) {}

unsigned char** AiPlayer::GetMineMap() {}

unsigned char AiPlayer::GetMineMapEntry(Point site) {}

WeightTable AiPlayer::GetFilteredWeightTable(ResourceID unit_type, unsigned char flags) {}

int AiPlayer::GetPredictedAttack(UnitInfo* unit, int caution_level) {}

unsigned short AiPlayer::GetTargetTeam() const {}

int AiPlayer::GetStrategy() const {}
