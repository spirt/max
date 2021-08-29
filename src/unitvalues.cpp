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

#include "unitvalues.hpp"

#include "registerarray.hpp"

UnitValues::UnitValues()
    : turns(0),
      hits(0),
      armor(0),
      attack(0),
      speed(0),
      range(0),
      rounds(0),
      move_and_fire(0),
      scan(0),
      storage(0),
      ammo(0),
      attack_radius(0),
      agent_adjust(0),
      version(1),
      units_built(0) {}

UnitValues::UnitValues(const UnitValues& other)
    : turns(other.turns),
      hits(other.hits),
      armor(other.armor),
      attack(other.attack),
      speed(other.speed),
      range(other.range),
      rounds(other.rounds),
      move_and_fire(other.move_and_fire),
      scan(other.scan),
      storage(other.storage),
      ammo(other.ammo),
      attack_radius(other.attack_radius),
      agent_adjust(other.agent_adjust),
      version(other.version),
      units_built(other.units_built) {}

UnitValues::~UnitValues() {}

TextFileObject* UnitValues::Allocate() { return new (std::nothrow) UnitValues(); }

static unsigned short UnitValues_TypeIndex;
static MAXRegisterClass UnitValues_ClassRegister("UnitValues", &UnitValues_TypeIndex, &UnitValues::Allocate);

unsigned short UnitValues::GetTypeIndex() const { return UnitValues_TypeIndex; }

void UnitValues::FileLoad(SmartFileReader& file) {
    file.Read(turns);
    file.Read(hits);
    file.Read(armor);
    file.Read(attack);
    file.Read(speed);
    file.Read(range);
    file.Read(rounds);
    file.Read(move_and_fire);
    file.Read(scan);
    file.Read(storage);
    file.Read(ammo);
    file.Read(attack_radius);
    file.Read(agent_adjust);
    file.Read(version);
    file.Read(units_built);
}

void UnitValues::FileSave(SmartFileWriter& file) {
    file.Write(turns);
    file.Write(hits);
    file.Write(armor);
    file.Write(attack);
    file.Write(speed);
    file.Write(range);
    file.Write(rounds);
    file.Write(move_and_fire);
    file.Write(scan);
    file.Write(storage);
    file.Write(ammo);
    file.Write(attack_radius);
    file.Write(agent_adjust);
    file.Write(version);
    file.Write(units_built);
}

void UnitValues::TextLoad(TextStructure& object) {
    turns = object.ReadInt("turns");
    hits = object.ReadInt("hits");
    armor = object.ReadInt("armor");
    attack = object.ReadInt("attack");
    speed = object.ReadInt("speed");
    range = object.ReadInt("range");
    rounds = object.ReadInt("rounds");
    move_and_fire = object.ReadBool("move_and_fire");
    scan = object.ReadInt("scan");
    storage = object.ReadInt("storage");
    ammo = object.ReadInt("ammo");
    attack_radius = object.ReadInt("attack_radius");
    agent_adjust = object.ReadInt("agent_adjust");
    version = object.ReadInt("version");
    units_built = object.ReadInt("units_built");
}

void UnitValues::TextSave(SmartTextfileWriter& file) {
    file.WriteInt("turns", turns);
    file.WriteInt("hits", hits);
    file.WriteInt("armor", armor);
    file.WriteInt("attack", attack);
    file.WriteInt("speed", speed);
    file.WriteInt("range", range);
    file.WriteInt("rounds", rounds);
    file.WriteBool("move_and_fire", move_and_fire);
    file.WriteInt("scan", scan);
    file.WriteInt("storage", storage);
    file.WriteInt("ammo", ammo);
    file.WriteInt("attack_radius", attack_radius);
    file.WriteInt("agent_adjust", agent_adjust);
    file.WriteInt("version", version);
    file.WriteInt("units_built", units_built);
}

unsigned short* UnitValues::GetAttribute(char index) {
    unsigned short* result;

    switch (index) {
        case 1:
            result = &attack;
            break;
        case 2:
            result = &rounds;
            break;
        case 3:
            result = &range;
            break;
        case 4:
            result = &ammo;
            break;
        case 5:
            result = &armor;
            break;
        case 6:
            result = &hits;
            break;
        case 7:
            result = &scan;
            break;
        case 8:
            result = &speed;
            break;
        case 9:
            result = &turns;
            break;
        default:
            SDL_assert("UnitValues::GetAttribute called with invalid index.");
            result = nullptr;
    }

    return result;
}

bool UnitValues::operator==(const UnitValues& other) const {
    return turns == other.turns && hits == other.hits && armor == other.armor && attack == other.attack &&
           speed == other.speed && range == other.range && rounds == other.rounds &&
           move_and_fire == other.move_and_fire && scan == other.scan && storage == other.storage &&
           ammo == other.ammo && attack_radius == other.attack_radius && version == other.version &&
           units_built == other.units_built && agent_adjust == other.agent_adjust;
}

bool UnitValues::operator!=(const UnitValues& other) const { return !this->operator==(other); }
