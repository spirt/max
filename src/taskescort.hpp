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

#ifndef TASKESCORT_HPP
#define TASKESCORT_HPP

#include "task.hpp"

class TaskEscort : public Task {
    SmartPointer<UnitInfo> target;
    SmartPointer<UnitInfo> escort;
    ResourceID unit_type;
    bool is_escort_requested;

    bool IssueOrders(UnitInfo* unit);

    static void MoveFinishedCallback(Task* task, UnitInfo* unit, char result);

public:
    TaskEscort(UnitInfo* unit, ResourceID unit_type);
    ~TaskEscort();

    bool Task_vfunc1(UnitInfo& unit);
    char* WriteStatusLog(char* buffer) const;
    uint8_t GetType() const;
    void AddUnit(UnitInfo& unit);
    void Begin();
    void EndTurn();
    bool Execute(UnitInfo& unit);
    void RemoveSelf();
    void RemoveUnit(UnitInfo& unit);
};

#endif /* TASKESCORT_HPP */
