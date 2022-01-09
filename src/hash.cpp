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

#include "hash.hpp"

#define HASH_HASH_SIZE 512

UnitHash Hash_UnitHash(HASH_HASH_SIZE);
MapHash Hash_MapHash(HASH_HASH_SIZE);

void SmartList_UnitInfo_FileLoad(SmartList<UnitInfo>& list, SmartFileReader& file) {
    list.Clear();

    for (unsigned short count = file.ReadObjectCount(); count; --count) {
        UnitInfo* unit = dynamic_cast<UnitInfo*>(file.ReadObject());

        list.PushBack(*unit);

        if (unit->flags & HASH_4) {
            /// \todo Integrate with color init
            //            unit->color_cycling_lut = dword_1770A0;
        } else if (unit->flags & HASH_3) {
            //            unit->color_cycling_lut = dword_1770A4;
        } else if (unit->flags & HASH_2) {
            //            unit->color_cycling_lut = dword_1770A8;
        } else if (unit->flags & HASH_1) {
            //            unit->color_cycling_lut = dword_1770AC;
        } else {
            //            unit->color_cycling_lut = dword_1770B0;
        }

        unit->sound = SFX_TYPE_INVALID;
    }
}

void SmartList_UnitInfo_FileSave(SmartList<UnitInfo>& list, SmartFileWriter& file) {
    unsigned short count = list.GetCount();

    file.Write(count);
    for (SmartList<UnitInfo>::Iterator unit = list.Begin(); unit != nullptr; ++unit) {
        file.WriteObject(&*unit);
    }
}

void SmartList_UnitInfo_Clear(SmartList<UnitInfo>& list) {
    for (SmartList<UnitInfo>::Iterator unit = list.Begin(); unit != nullptr; ++unit) {
        unit->GetObject()->SetParent(nullptr);
        unit->GetObject()->SetEnemy(nullptr);
        unit->GetObject()->ClearTask1List();
    }

    list.Clear();
}

void SmartList_UnitInfo_TextLoad(SmartList<UnitInfo>& list, TextStructure& object) {
    list.Clear();

    for (UnitInfo* unit; (unit = dynamic_cast<UnitInfo*>(&*object.ReadPointer("unit"))), unit != nullptr;) {
        list.PushBack(*unit);

        if (unit->flags & HASH_4) {
            /// \todo Integrate with color init
            //            unit->color_cycling_lut = dword_1770A0;
        } else if (unit->flags & HASH_3) {
            //            unit->color_cycling_lut = dword_1770A4;
        } else if (unit->flags & HASH_2) {
            //            unit->color_cycling_lut = dword_1770A8;
        } else if (unit->flags & HASH_1) {
            //            unit->color_cycling_lut = dword_1770AC;
        } else {
            //            unit->color_cycling_lut = dword_1770B0;
        }

        unit->sound = SFX_TYPE_INVALID;
    }
}

void SmartList_UnitInfo_TextSave(SmartList<UnitInfo>& list, SmartTextfileWriter& file) {
    for (SmartList<UnitInfo>::Iterator unit = list.Begin(); unit != nullptr; ++unit) {
        file.WritePointer("unit", &*unit);
    }
}

class MapHashObject : public SmartObject {
    SmartList<UnitInfo> list;
    unsigned short x;
    unsigned short y;

public:
    MapHashObject(unsigned short grid_x, unsigned short grid_y);
    ~MapHashObject();

    void FileLoad(SmartFileReader& file);
    void FileSave(SmartFileWriter& file);
    void TextLoad(TextStructure& object);
    void TextSave(SmartTextfileWriter& file);

    unsigned short GetX() const;
    unsigned short GetY() const;
    SmartList<UnitInfo>& GetList();
    void PushFront(UnitInfo* unit);
    void PushBack(UnitInfo* unit);
    void Remove(UnitInfo* unit);
};

MapHashObject::MapHashObject(unsigned short grid_x, unsigned short grid_y) : x(grid_x), y(grid_y) {}

MapHashObject::~MapHashObject() {}

void MapHashObject::FileLoad(SmartFileReader& file) {
    file.Read(x);
    file.Read(y);
    SmartList_UnitInfo_FileLoad(list, file);
}

void MapHashObject::FileSave(SmartFileWriter& file) {
    file.Write(x);
    file.Write(y);
    SmartList_UnitInfo_FileSave(list, file);
}

void MapHashObject::TextLoad(TextStructure& object) {
    x = object.ReadInt("x");
    y = object.ReadInt("y");
    SmartList_UnitInfo_TextLoad(list, object);
}

void MapHashObject::TextSave(SmartTextfileWriter& file) {
    file.WriteInt("x", x);
    file.WriteInt("y", y);
    SmartList_UnitInfo_TextSave(list, file);
}

unsigned short MapHashObject::GetX() const { return x; }

unsigned short MapHashObject::GetY() const { return y; }

SmartList<UnitInfo>& MapHashObject::GetList() { return list; }

void MapHashObject::PushFront(UnitInfo* unit) { list.PushFront(*unit); }

void MapHashObject::PushBack(UnitInfo* unit) { list.PushBack(*unit); }

void MapHashObject::Remove(UnitInfo* unit) { list.Remove(*unit); }

MapHash::MapHash(unsigned short hash_size)
    : hash_size(hash_size), x_shift(0), entry(new (std::nothrow) SmartList<MapHashObject>[hash_size]) {
    while (hash_size > 128) {
        ++x_shift;
        hash_size >>= 1;
    }
}

MapHash::~MapHash() { delete[] entry; }

void MapHash::AddEx(UnitInfo* unit, unsigned short grid_x, unsigned short grid_y, bool mode) {
    SmartList<MapHashObject>* list = &entry[(grid_y ^ (grid_x << x_shift)) % hash_size];
    SmartList<MapHashObject>::Iterator object = list->Begin();

    while (object != nullptr) {
        if (grid_x == (*object).GetX() && grid_y == (*object).GetY()) {
            break;
        }

        ++object;
    }

    if (object == nullptr) {
        list->PushFront(*new (std::nothrow) MapHashObject(grid_x, grid_y));
        object = list->Begin();
    }

    if (!mode || unit->unit_type == LRGTAPE || unit->unit_type == SMLTAPE) {
        (*object).PushFront(unit);
    } else {
        (*object).PushBack(unit);
    }
}

void MapHash::Add(UnitInfo* unit, bool mode) {
    unsigned short grid_x;
    unsigned short grid_y;

    SDL_assert(unit != nullptr);

    grid_x = unit->grid_x;
    grid_y = unit->grid_y;

    AddEx(unit, grid_x, grid_y, mode);

    if (unit->flags & BUILDING) {
        AddEx(unit, grid_x + 1, grid_y, mode);
        AddEx(unit, grid_x, grid_y + 1, mode);
        AddEx(unit, grid_x + 1, grid_y + 1, mode);
    }
}

void MapHash::RemoveEx(UnitInfo* unit, unsigned short grid_x, unsigned short grid_y) {
    SmartList<MapHashObject>* list = &entry[(grid_y ^ (grid_x << x_shift)) % hash_size];
    SmartList<MapHashObject>::Iterator object = list->Begin();

    while (object != nullptr) {
        if (grid_x == (*object).GetX() && grid_y == (*object).GetY()) {
            break;
        }

        ++object;
    }

    if (object != nullptr) {
        (*object).Remove(unit);

        if (!(*object).GetList().GetCount()) {
            list->Remove(object);
        }
    }
}

void MapHash::Remove(UnitInfo* unit) {
    unsigned short grid_x;
    unsigned short grid_y;

    SDL_assert(unit != nullptr);

    grid_x = unit->grid_x;
    grid_y = unit->grid_y;

    RemoveEx(unit, grid_x, grid_y);

    if (unit->flags & BUILDING) {
        RemoveEx(unit, grid_x + 1, grid_y);
        RemoveEx(unit, grid_x, grid_y + 1);
        RemoveEx(unit, grid_x + 1, grid_y + 1);
    }
}

void MapHash::Clear() {
    for (int index = 0; index < hash_size; ++index) {
        entry[index].Clear();
    }
}

void MapHash::FileLoad(SmartFileReader& file) {
    Clear();
    delete[] entry;

    file.Read(hash_size);
    file.Read(x_shift);

    entry = new (std::nothrow) SmartList<MapHashObject>[hash_size];

    for (int index = 0; index < hash_size; ++index) {
        for (unsigned short count = file.ReadObjectCount(); count; --count) {
            MapHashObject* object = new (std::nothrow) MapHashObject(0, 0);

            object->FileLoad(file);
            entry[index].PushBack(*object);
        }
    }
}

void MapHash::FileSave(SmartFileWriter& file) {
    file.Write(hash_size);
    file.Write(x_shift);

    for (int index = 0; index < hash_size; ++index) {
        unsigned short count = entry[index].GetCount();
        file.Write(count);

        for (SmartList<MapHashObject>::Iterator object = entry[index].Begin(); object != nullptr; ++object) {
            (*object).FileSave(file);
        }
    }
}

void MapHash::TextLoad(TextStructure& object) {
    Clear();
    delete[] entry;

    hash_size = object.ReadInt("hash_size");
    x_shift = object.ReadInt("x_shift");

    entry = new (std::nothrow) SmartList<MapHashObject>[hash_size];

    SmartPointer<TextStructure> entry_reader = nullptr;

    for (;;) {
        entry_reader = object.ReadStructure("entry");

        if (entry_reader == nullptr) {
            break;
        }

        unsigned short index = entry_reader->ReadInt("index");

        SmartPointer<TextStructure> list_reader = nullptr;

        for (;;) {
            list_reader = entry_reader->ReadStructure("list");

            if (list_reader == nullptr) {
                break;
            } else {
                MapHashObject* maphash = new (std::nothrow) MapHashObject(0, 0);
                maphash->TextLoad(*list_reader);
                entry[index].PushBack(*maphash);
            }
        }
    }
}

void MapHash::TextSave(SmartTextfileWriter& file) {
    file.WriteInt("hash_size", hash_size);
    file.WriteInt("x_shift", x_shift);

    for (int index = 0; index < hash_size; ++index) {
        unsigned short count = entry[index].GetCount();

        if (count) {
            file.WriteIdentifier("entry");
            file.WriteInt("index", index);

            for (SmartList<MapHashObject>::Iterator object = entry[index].Begin(); object != nullptr; ++object) {
                file.WriteIdentifier("list");
                (*object).TextSave(file);
                file.WriteDelimiter();
            }

            file.WriteDelimiter();
        }
    }
}

UnitInfo* MapHash::operator[](const Point& key) {
    SmartList<MapHashObject>* list = &entry[(key.y ^ (key.x << x_shift)) % hash_size];
    SmartList<MapHashObject>::Iterator object = list->Begin();
    UnitInfo* result;

    while (object != nullptr) {
        if (key.x == (*object).GetX() && key.y == (*object).GetY()) {
            break;
        }

        ++object;
    }

    if (object != nullptr) {
        result = &*(*object).GetList().Begin();
    } else {
        result = nullptr;
    }

    return result;
}

UnitHash::UnitHash(unsigned short hash_size)
    : hash_size(hash_size), list(new (std::nothrow) SmartList<UnitInfo>[hash_size]) {}
UnitHash::~UnitHash() { delete[] list; }

void UnitHash::PushBack(UnitInfo* unit) {
    SDL_assert(unit != nullptr);

    list[unit->GetId() % hash_size].PushBack(*unit);
}
void UnitHash::Remove(UnitInfo* unit) {
    SDL_assert(unit != nullptr);

    list[unit->GetId() % hash_size].Remove(*unit);
}

void UnitHash::Clear() {
    for (int index = 0; index < hash_size; ++index) {
        for (SmartList<UnitInfo>::Iterator unit = list[index].Begin(); unit != nullptr; ++unit) {
            (*unit).ClearUnitList();
            (*unit).SetParent(nullptr);
        }

        list[index].Clear();
    }
}

void UnitHash::FileLoad(SmartFileReader& file) {
    Clear();
    delete[] list;

    file.Read(hash_size);
    list = new (std::nothrow) SmartList<UnitInfo>[hash_size];

    for (int index = 0; index < hash_size; ++index) {
        SmartList_UnitInfo_FileLoad(list[index], file);
    }
}

void UnitHash::FileSave(SmartFileWriter& file) {
    file.Write(hash_size);

    for (int index = 0; index < hash_size; ++index) {
        SmartList_UnitInfo_FileSave(list[index], file);
    }
}

void UnitHash::TextLoad(TextStructure& object) {
    Clear();
    delete[] list;

    hash_size = object.ReadInt("hash_size");
    list = new (std::nothrow) SmartList<UnitInfo>[hash_size];

    SmartPointer<TextStructure> list_reader = nullptr;

    for (;;) {
        list_reader = object.ReadStructure("list");

        if (list_reader == nullptr) {
            break;
        }

        SmartList_UnitInfo_TextLoad(list[list_reader->ReadInt("index")], *list_reader);
    }
}

void UnitHash::TextSave(SmartTextfileWriter& file) {
    file.WriteInt("hash_size", hash_size);

    for (int index = 0; index < hash_size; ++index) {
        if (list[index].GetCount()) {
            file.WriteIdentifier("list");
            file.WriteInt("index", index);
            SmartList_UnitInfo_TextSave(list[index], file);
            file.WriteDelimiter();
        }
        SmartList_UnitInfo_FileSave(list[index], file);
    }
}

UnitInfo* UnitHash::operator[](const unsigned short& key) {
    for (SmartList<UnitInfo>::Iterator unit = list[key % hash_size].Begin(); unit != nullptr; ++unit) {
        if (key == (*unit).GetId()) {
            return &(*unit);
        }
    }

    return nullptr;
}