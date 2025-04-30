#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here

// recursive backtrack func - assign worker to current day and slot
bool backtrack(const AvailabilityMatrix& avail, size_t dailyNeed, size_t maxShifts, DailySchedule& sched, vector<size_t>& shiftsUsed, size_t day, size_t slot);


// Add your implementation of schedule() and other helper functions here

bool backtrack(const AvailabilityMatrix& avail, size_t dailyNeed, size_t maxShifts, DailySchedule& sched, vector<size_t>& shiftsUsed, size_t day, size_t slot)
{
    // base case: all days filled
    if(day == avail.size()) return true;

    // try assigning each worker
    for(size_t w = 0; w < avail[0].size(); ++w) {
        // skip if worker not available on this day
        if(!avail[day][w]) continue;

        // skip if worker already scheduled on this day
        if(find(sched[day].begin(), sched[day].end(), w) != sched[day].end()) continue;

        // skip if worker exceeded max shifts
        if(shiftsUsed[w] >= maxShifts) continue;

        // assign worker
        sched[day][slot] = w;
        shiftsUsed[w]++;

        // recurse to next slot or next day
        bool success;
        if(slot + 1 == dailyNeed)
        {
            success = backtrack(avail, dailyNeed, maxShifts, sched, shiftsUsed, day + 1, 0);
        }
        else
        {
            success = backtrack(avail, dailyNeed, maxShifts, sched, shiftsUsed, day, slot + 1);
        }

        if(success) return true;

        // unassign worker (backtrack)
        sched[day][slot] = INVALID_ID;
        shiftsUsed[w]--;
    }

    // no valid assignment found for this position
    return false;
}

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below

    size_t days = avail.size();
    size_t workers = avail[0].size();

    // initialize sched matrix to days x dailyNeed with all invalid ids
    sched.assign(days, vector<Worker_T>(dailyNeed, INVALID_ID));

    // track how many shifts each worker has been assigned
    vector<size_t> shiftsUsed(workers, 0);

    // start backtracking search at first slot of day 0
    return backtrack(avail, dailyNeed, maxShifts, sched, shiftsUsed, 0, 0);

}

