// Brandon Chan
// jumpPrime.cpp
// 9/26/20

// Brandon Chan
// jumpPrime.cs
// 9/26/20
// Written in C++ on CLion
// CPSC 3200 Professor Dingle, Seattle University Fall Quarter 2020

/* Purpose: To provide the resources for the jumpPrime object. This object allows number encapsulation,
 *          the ability to find nearest upper and lower prime values in respect to the encapsulated number,
 *          as well as the ability to reset or revive an object. Revive will permanently deactivate an object
 *          if called on an already active object.
 */

/* Revisions: Version 1.0 - 9/17/20
              Version 1.1 - 9/26/20: Added null argument constructor for duelingJP implementation. Converted
                                     code from c# to c++.
              Version 1.2 - 10/28/20: Changed lower bound to allow 3 digit numbers as well.
*/

/* CLASS INVARIANT
 * - When constructor is called, a new jumpPrime object is created and is set to the active state, will encapsulate
 *   the integer passed in through the parameter inside initialNum and num, and initialize jumpCount,
 *   low, upp, queryCount, and jumpVal.
 * - Following a call to getActiveState(), the object will still remain active/inactive unless it is the final query
 *   needed before it jumps. In this case, the object may become deactivated and will not allow intended functionality
 *   for up(), down(), or reset() calls.
 * - Following a call to up() or down(), the object may jump. If this jump is the final one, signaling deactivation,
 *   then the object will become inactive and further up(), down(), or even reset() calls will not provide
 *   intended functionality.
 * - If down() is called and causes a jump to a value below 1000, the object will be deactivated and up(), down()
 *   or reset() calls will not provide intended functionality.
 * - This class offers no tools to copy a jumpPrime object.
 * - Several objects can have the same encapsulated number.
 * - Calls to revive() will switch the state of an object or permanently deactivate it if it was already active,
 *   providing or limiting access to the objects resources.
 * - Using either up(), down(), or getActiveState() will add to the queryCount of the object, potentially
 *   provoking a jump and therefore may lead to object deactivation.
 * - State of objects will only be changed following ++, --, +=, and -= operations.
 *   All other operations use temporaries and do not change the state of the object.
 * - Fulfilling preconditions of operators means object will never be set to the default number.
 * - All operators can be used on both active, inactive, and permanently deactivated objects and cannot alter the
 *   active state of an object due to error handling.
 */

/* IMPLEMENTATION INVARIANT
 * - The direction of jumps was determined by if up() or down() was recently called for simplicity.
 * - Choosing to jump upwards as a result of getActiveState() was also for simplicity.
 * - Reset() was chosen to return a boolean for easier testing of it's success in resetting an object.
 * - Decided that reset() not count as a query for the client. This was because if reset() increased
 *   the query count before resetting, it would be pointless. If query count for that object was added after it had
 *   been reset, then the object was not returned to it's initial state where it had a query count of 0.
 * - Decided that revive() not count as a query for the client. Doing so would in someways violate what it means
 *   for an object to be inactive. No changes should be made to the objects values while changing the active state.
 * - The default value of 2488 was chosen because its nearby prime values were known and also had a large
 *   difference between them, allowing for more queries before the initial jump.
 * - Chose to return -1 from up() or down() calls on an inactivate jumpPrime object because the client is unable
 *   to encapsulate a negative number or even one below 1000. -1 acts as an easy indicator in testing that
 *   the functions were called on an inactive object.
 * - maxJumpCount was chosen to have a MINIMUM of 5 to provide more visible testing results. Having a value too low,
 *   especially in the case of numbers that jump quickly due to a low number of queries, would deactivate too quickly.
 *   Therefore, to ensure that the class is functioning properly with future changes, maxJumpCount should be at
 *   this value or larger. Altering jumpCount below 5 could also potentially break unit testing.
 * - Called up() and down() in constructor to initialize variables and quickly obtain the number of queries before
 *   jumping alongside the value added to or subtracted from the encapsulated number.
 * - Using the null argument constructor creates a permanently deactivated object that should be replaced with another object
 *   not created by the null argument constructor.
 * - Chose to not implement overloaded streaming operators to preserve secrecy and encapsulation of data.
 * - Chose to check active states of object in addition to its encapsulated number for == and != operators
 *   because to define two objects as identical, more than just their encapsulated numbers must be taken
 *   into account.
 * - Chose to support mixed modes for integers for all operators except for ==, !=, -- and ++
 * - If any mathematical operation takes in a valid that would lead to an invalid object, constructor error handling
 *   will set the encapsulated number to a default value.
 * - Supports comparison to integers located at both LHS and RHS.
 * - += -= and both pre and post ++ and -- will change the state of the object. All other operations return
 *   temporaries.
 * - Allowed operations to be used on an object despite its active state because data like the query and jump
 *   counts are independent to the encapsulated number, and only the encapsulated number ends up being changed.
 * - Chose to not check query and jump count because they are not good indicators if a jumpPrime object is
 *   identical to another jumpPrime object.
 * - Swapped the position of LHS and RHS values if an integer is initially on the LHS because an int does not
 *   have-a jumpPrime object but a jumpPrime object has-a integer.
 * - Did not support assignment or copying because data members besides the encapsulated number should only be
 *   changed through queries (jumpCount, queryCount).
 * - All operators can be used on both active, inactive, and permanently deactivated objects and cannot alter the
 *   active state of an object due to error handling.
 */


#include "jumpPrime.h"
#include <math.h>

jumpPrime::jumpPrime() {
    activated = false;
    permDeactivated = true;
}

jumpPrime::jumpPrime(int userGivenVal)
{
    if (userGivenVal < lowerBounds) { num = defaultNum; }
    else { num = userGivenVal; }

    initialNum = num;
    activated = true;
    permDeactivated = false;
    jumpCount = 0;
    low = down();
    upp = up();
    queryCount = 0;
    jumpVal = upp - low;
}

jumpPrime jumpPrime::operator+(const jumpPrime& rhs) {
    jumpPrime jp1(num + rhs.num);
    return jp1;
}

jumpPrime jumpPrime::operator-(const jumpPrime& rhs) {
    jumpPrime jp1(num - rhs.num);
    return jp1;
}

jumpPrime& jumpPrime::operator+=(const jumpPrime& rhs) {
    num += rhs.num;
    return *this;
}

jumpPrime& jumpPrime::operator-=(const jumpPrime& rhs) {
    if ((num - rhs.num) < lowerBounds) {
        num = defaultNum;
        return *this;
    }
    num -= rhs.num;
    return *this;
}

jumpPrime jumpPrime::operator%(const jumpPrime& rhs) {
    jumpPrime jp1(num % rhs.num);
    return jp1;
}

jumpPrime jumpPrime::operator/(const jumpPrime& rhs) {
    jumpPrime jp1(num / rhs.num);
    return jp1;
}

jumpPrime jumpPrime::operator*(const jumpPrime& rhs) {
    jumpPrime jp1(num * rhs.num);
    return jp1;
}

jumpPrime jumpPrime::operator+(const int& rhs) {
    jumpPrime jp1(num + rhs);
    return jp1;
}

jumpPrime jumpPrime::operator-(const int& rhs) {
    jumpPrime jp1(num - rhs);
    return jp1;
}

jumpPrime& jumpPrime::operator+=(const int& rhs) {
    int temp = rhs;
    if (temp < 0) { temp = temp *-1; }
    num += temp;
    return *this;
}

jumpPrime& jumpPrime::operator-=(const int& rhs) {
    if ((num - rhs) < lowerBounds) {
        num = defaultNum;
        return *this;
    }
    num -= rhs;
    return *this;
}

jumpPrime jumpPrime::operator%(const int& rhs) {
    jumpPrime jp1(num % rhs);
    return jp1;
}

jumpPrime jumpPrime::operator/(const int& rhs) {
    jumpPrime jp1(num / rhs);
    return jp1;
}

jumpPrime jumpPrime::operator*(const int& rhs) {
    jumpPrime jp1(num * rhs);
    return jp1;
}

jumpPrime& jumpPrime::operator++() {
    num++;
    return *this;
}

jumpPrime& jumpPrime::operator--() {
    num--;
    if (num < lowerBounds) {num = defaultNum;}
    return *this;
}

jumpPrime jumpPrime::operator++(int dummy) {
    jumpPrime temp = *this;
    num++;
    return temp;
}

jumpPrime jumpPrime::operator--(int dummy) {
    jumpPrime temp = *this;
    num--;
    if (num < lowerBounds) {num = defaultNum;}
    return temp;
}

bool jumpPrime::operator==(const jumpPrime& rhs) {
    return (num == rhs.num && activated == rhs.activated
        && permDeactivated == rhs.permDeactivated);
}

bool jumpPrime::operator!=(const jumpPrime& rhs) {
    return (num != rhs.num || activated != rhs.activated
            || permDeactivated != rhs.permDeactivated);
}

bool jumpPrime::operator<(const jumpPrime& rhs) {
    return num < rhs.num;
}

bool jumpPrime::operator<(const int& rhs) {
    return num < rhs;
}

bool jumpPrime::operator>(const jumpPrime& rhs) {
    return num > rhs.num;
}

bool jumpPrime::operator>(const int& rhs) {
    return num > rhs;
}

bool jumpPrime::operator<=(const jumpPrime& rhs) {
    return num <= rhs.num;
}

bool jumpPrime::operator<=(const int& rhs) {
    return num <= rhs;
}

bool jumpPrime::operator>=(const jumpPrime& rhs) {
    return num >= rhs.num;
}

bool jumpPrime::operator>=(const int& rhs) {
    return num >= rhs;
}


jumpPrime operator+(int lhs, jumpPrime& rhs) {
    return rhs + lhs;
}
jumpPrime operator-(int lhs, jumpPrime& rhs) {
    return rhs - lhs;
}
jumpPrime& operator+=(int lhs, jumpPrime& rhs) {
    return rhs += lhs;
}
jumpPrime& operator-=(int lhs, jumpPrime& rhs) {
    return rhs -= lhs;
}
jumpPrime operator%(int lhs, jumpPrime& rhs) {
    return rhs % lhs;
}
jumpPrime operator/(int lhs, jumpPrime& rhs) {
    return rhs / lhs;
}
jumpPrime operator*(int lhs, jumpPrime& rhs) {
    return rhs * lhs;
}

bool operator<(int num, jumpPrime lhs) {
    return lhs > num;
}

bool operator>(int num, jumpPrime lhs) {
    return lhs < num;
}

bool operator<=(int num, jumpPrime lhs) {
    return lhs >= num;
}

bool operator>=(int num, jumpPrime lhs) {
    return lhs <= num;
}

bool jumpPrime::getActiveState()
{
    if (permDeactivated || !activated)
    {
        return false;
    }
    queryCount++;
    if (queryCount == jumpVal)
    {
        num += jumpVal;
        jump();
        if (jumpCount == maxJumpCount
            || num < lowerBounds) { activated = false; }
    }
    return activated;
}

bool jumpPrime::reset()
{
    if (activated)
    {
        jumpCount = 0;
        num = initialNum;
        low = down();
        upp = up();
        queryCount = 0;
        jumpVal = upp - low;
        return true;
    }
    return false;
}

void jumpPrime::revive()
{
    if (!activated && !permDeactivated)
    {
        activated = !activated;
        if (jumpCount == maxJumpCount) { jumpCount = 0; }
        if (num < lowerBounds) { reset(); }
    }
    else
    {
        permDeactivated = true;
        activated = false;
    }
}

int jumpPrime::up()
{
    if (activated)
    {
        int upper = num;
        upper++;
        while (!isAPrimeNum(upper))
        {
            upper++;
        }
        queryCount++;
        upp = upper;
        if (queryCount == jumpVal)
        {
            num += jumpVal;
            jump();
            if (jumpCount == maxJumpCount) { activated = false; }
        }
        return upper;
    }
    return -1;
}

int jumpPrime::down()
{
    if (activated)
    {
        int lower = num;
        lower--;
        while (!isAPrimeNum(lower))
        {
            lower--;
        }
        queryCount++;
        low = lower;
        if (queryCount == jumpVal)
        {
            num -= jumpVal;
            jump();
            if (jumpCount == maxJumpCount
                || num < lowerBounds) { activated = false; }
        }
        return lower;
    }
    return -1;
}

bool jumpPrime::isAPrimeNum(int val)
{
    int count = 2;
    bool prime = true;
    int squareRoot = sqrt(val);
    while (count < squareRoot && prime)
    {
        if (val % count == 0) { prime = false; }
        else { count++; }
    }
    return prime;
}

void jumpPrime::jump()
{
    jumpCount++;
    upp = up();
    low = down();
    queryCount = 0;
    jumpVal = upp - low;
}



