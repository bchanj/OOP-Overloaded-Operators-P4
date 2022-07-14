// Brandon Chan
// duelingJP.cpp - Implementation for the duelingJP header file.
// 10/28/20
// Written in C++ on CLion
// CPSC 3200 Professor Dingle, Seattle University Fall Quarter 2020

/* Purpose: To create an object containing an array of jumpPrime objects and allow the users to find the collisions
            and inversions of the objects in the array. Each object is compared against all other objects in the array
            when using these functions. Deep Copying and Move Semantics have also been implemented.
*/

/* Revisions: Version 1.0 - 9/27/20
 *            Version 2.0 - 10/28/20 - Added operator overloading for +, -, +=, -= as well as comparison operator
 *                                     overloading. Implemented mixed mode for < and >.
 */


/* CLASS INVARIANT
 * - Following construction of duelingJP object, an array of jumpPrime objects will be created and all
 *   member variables will be set to 0 except for arrSize which is user defined through the constructor or
 *   automatically assigned a default value if using the null argument constructor.
 * - Deep copying is supported through the copy constructor and overloaded assignment operator. To save resources,
 *   move semantics have also been implemented through a move copy constructor and a move overloaded assignment operator.
 * - After a call to collide() or inversion() the jumpPrime objects in the array will be altered, in either a jump or deactivation.
 * - Each duelingJP object owns it's own array of jumpPrime objects.
 * - Through initialization of array jumpPrime objects, all objects should have a unique encapsulated number.
 * - Following += or -= the state of the LHS object will be altered by changing the array size variable and the array
 *   itself. Therefore, encapsulated data may become invalid due to these operators destructive nature.
 * - Mathematical operators + and - and all comparison operators do not alter the state of the LHS or RHS objects.
 * - Mathematical operators + and - return temporaries.
 * - Following use of -= the LHS object may have an invalid (size 0) encapsulated array.
 * - Comparison operators <, >, will only compare the size of the array to an integer or another duelingJP
 *   object.
 * - Comparison operators ==, !=, <=, >= will compare the contents of two duelingJP objects's encapsulated arrays
 *   in addition to the size of their arrays.
 */

/* IMPLEMENTATION INVARIANT
 * - Chose to create array of jumpPrime objects using the default size when using null argument constructor. To use own objects, client
 *   must replace objects within the array.
 * - Chose to start at 5000 for the default value for the base in the geometric sequence alongside a linear increase of 50. This was to ensure that
 *   collision and inversion results and functionality would be quickly visible even with duelingJP objects that used a smaller array size.
 * - Chose to revive objects ONLY when they have become deactivated before both checks (up to up or down to down for collide(), up to down, down to up for
 *   inversion()) to ensure checks worked as intended.
 * - Chose to return -1 if all objects within array were deactivated as an easy indicator to the client.
 * - Chose to periodically check active state of object to ensure that each object was active during each check, therefore
 *   ensuring correct functionality and correct collision/inversion counts.
 * - When two jumpPrime objects collide or invert, if they match both or only one condition, the max that the collision
 *   or inversion count can increase is by 1.
 * - Chose to only support mathematical operators: +, -, +=, -= of duelingJP objects because they allow
 *   concatenation and resizing of the duelingJP array and fit the container nature of the object.
 * - Only allowed mixed mode for < and > comparison operators because when checking <=, >=, ==, or != you also
 *   have to check commonalities between array values.
 * - Made <=, >=, ==, and != check the array indices in addition to the array size because subtraction
 *   can create two arrays of the same sizes but different elements.
 * - Does not support *, /, % because they do not fit the nature of a container object like duelingJP.
 *   For example: You cannot multiply two arrays like you can add two arrays together.
 * - Does not support ++ or -- because it does not make sense to increment an array and does not fit the
 *   nature of a container object.
 */

#include "duelingJP.h"
#include <iostream>

using namespace std;

duelingJP::duelingJP() {
    arrSize = defaultSize;
    objArr = new jumpPrime[arrSize];
    for (int i = 0; i < arrSize; i++) {
        objArr[i] = jumpPrime(startingJpNum + (i*geometricNum));
    }
    numDeactivated = 0;
    collisionCount = 0;
    inversionCount = 0;
    arrSize = 0;
}

duelingJP::duelingJP(int numObj) {
    if (numObj <= 1) { numObj = defaultSize; }
    objArr = new jumpPrime[numObj];
    for (int i = 0; i < numObj; i++) {
       objArr[i] = jumpPrime(startingJpNum + (i*geometricNum));
    }
    numDeactivated = 0;
    collisionCount = 0;
    inversionCount = 0;
    arrSize = numObj;
}

duelingJP::duelingJP(const duelingJP& djp) {
    arrSize = djp.arrSize;
    collisionCount = djp.collisionCount;
    inversionCount = djp.inversionCount;
    numDeactivated = djp.numDeactivated;
    objArr = new jumpPrime[arrSize];
    for (int i = 0; i < arrSize; i++) {
        objArr[i] = djp.objArr[i];
    }
}

duelingJP::duelingJP(duelingJP&& djp) {
    arrSize = djp.arrSize;
    collisionCount = djp.collisionCount;
    inversionCount = djp.inversionCount;
    numDeactivated = djp.numDeactivated;
    objArr = djp.objArr;
    djp.numDeactivated = 0;
    djp.collisionCount = 0;
    djp.inversionCount = 0;
    djp.arrSize = 0;
    djp.objArr = nullptr;
}

duelingJP& duelingJP::operator=(const duelingJP& rhs) {
    if (this == &rhs) { return *this; }
    delete [] objArr;
    collisionCount = rhs.collisionCount;
    inversionCount = rhs.inversionCount;
    arrSize = rhs.arrSize;
    numDeactivated = rhs.numDeactivated;
    objArr = new jumpPrime[arrSize];
    for (int i = 0; i < arrSize; i++) {
        objArr[i] = rhs.objArr[i];
    }
    return *this;
}

duelingJP duelingJP::operator+(const duelingJP& rhs) {
    int count = 0;
    int totalSize = arrSize + rhs.arrSize;

    duelingJP djp(totalSize);

    for (int i = 0; i < arrSize; i++) {
        djp.objArr[i] = objArr[i];
    }
    for (int i = arrSize-1; i < totalSize; i++) {
        djp.objArr[i] = rhs.objArr[count];
        count++;
    }
    return djp;
}

duelingJP& duelingJP::operator+=(const duelingJP& rhs) {
    int count = 0;
    int totalSize = arrSize + rhs.arrSize;

    jumpPrime* newArray = new jumpPrime[totalSize];
    for (int i = 0; i < arrSize; i++) {
        newArray[i] = objArr[i];
    }
    for (int i = arrSize-1; i < totalSize; i++) {
        newArray[i] = rhs.objArr[count];
        count++;
    }
    delete [] objArr;
    objArr = newArray;
    newArray = nullptr;
    delete [] newArray;
    arrSize = totalSize;

    return *this;
}

duelingJP duelingJP::operator-(const duelingJP& rhs) {
    if (rhs.arrSize >= arrSize) {
        duelingJP emptyDJP(0);
        delete [] emptyDJP.objArr;
        emptyDJP.objArr = new jumpPrime[0];
        emptyDJP.arrSize = 0;
        return emptyDJP;
    }
    int totalSize = arrSize - rhs.arrSize;
    duelingJP djp(totalSize);
    for (int i = 0; i < totalSize; i++) {
        djp.objArr[i] = objArr[i];
    }
    return djp;
}

duelingJP& duelingJP::operator-=(const duelingJP& rhs) {
    if (rhs.arrSize >= arrSize) {
        duelingJP emptyDJP(0);
        delete [] emptyDJP.objArr;
        emptyDJP.objArr = new jumpPrime[0];
        emptyDJP.arrSize = 0;
        *this = emptyDJP;
        return *this;
    }
    int totalSize = arrSize - rhs.arrSize;

    jumpPrime* newArray = new jumpPrime[totalSize];
    for (int i = 0; i < totalSize; i++) {
        newArray[i] = objArr[i];
    }
    delete [] objArr;
    objArr = newArray;
    newArray = nullptr;
    delete [] newArray;
    arrSize = totalSize;

    return *this;
}

bool duelingJP::operator<(const duelingJP& rhs) {
    return arrSize < rhs.arrSize;
}

bool duelingJP::operator<(const int &rhs) {
    return arrSize < rhs;
}

bool duelingJP::operator>(const duelingJP& rhs) {
    return arrSize > rhs.arrSize;
}

bool duelingJP::operator>(const int &rhs) {
    return arrSize > rhs;
}

bool duelingJP::operator==(const duelingJP& rhs) {
    if (arrSize != rhs.arrSize) {return false;}
    bool equal = true;

    int count = 0;
    while (count < arrSize && equal) {
        if (objArr[count] != rhs.objArr[count]) {equal = !equal;}
        count++;
    }
    return equal;
}

bool duelingJP::operator!=(const duelingJP& rhs) {
    if (arrSize != rhs.arrSize) {return true;}
    int count = 0;
    int inCommon = 0;
    for (int i = 0; i < arrSize; i++) {
        if (objArr[count] == rhs.objArr[count]) {inCommon++;}
    }
    return inCommon != arrSize;
}

bool duelingJP::operator<=(const duelingJP& rhs) {
    if (arrSize < rhs.arrSize) {return true;}
    else if (arrSize > rhs.arrSize) {return false;}
    int count = 0;
    int inCommon = 0;
    for (int i = 0; i < arrSize; i++) {
        if (objArr[count] == rhs.objArr[count]) {inCommon++;}
    }
    return (inCommon == arrSize);
}

bool duelingJP::operator>=(const duelingJP& rhs) {
    return arrSize >= rhs.arrSize;
}

bool operator<(int num, duelingJP lhs) {
    return lhs > num;
}

bool operator>(int num, duelingJP lhs) {
    return lhs < num;
}

duelingJP& duelingJP::operator=(duelingJP&& rhs) {
    jumpPrime* temp;
    if (this == &rhs) { return *this; }
    swap(arrSize, rhs.arrSize);
    swap(collisionCount, rhs.collisionCount);
    swap(inversionCount, rhs.inversionCount);
    swap(numDeactivated, rhs.numDeactivated);
    temp = objArr;
    objArr = rhs.objArr;
    rhs.objArr = temp;
    temp = nullptr;
    return *this;
}

duelingJP::~duelingJP() {
    delete [] objArr;
}

int duelingJP::collide() {
    if (numDeactivated >= arrSize) { return -1; }
    int currUp, currDown, targetUp, targetDown;
    for (int i = 0; i < arrSize; i++) {
        if (objArr[i].getActiveState()) {
            currUp = objArr[i].up();
            if (!objArr[i].getActiveState()) {objArr[i].revive();}
            currDown = objArr[i].down();
            if (!objArr[i].getActiveState()) {objArr[i].revive();}
            for (int j = i; j < arrSize; j++) {
                if (objArr[j].getActiveState()) {
                    targetUp = objArr[j].up();
                    if (!objArr[j].getActiveState()) {objArr[j].revive();}
                    targetDown = objArr[j].down();
                    if (!objArr[j].getActiveState()) {objArr[j].revive();}
                    if (currUp == targetUp || currDown == targetDown) { collisionCount++; }
                } else {numDeactivated++;}
            }
        } else {numDeactivated++;}
    }
    return collisionCount;
}

int duelingJP::inversion() {
    if (numDeactivated >= arrSize) { return -1; }
    int currUp, currDown, targetUp, targetDown;
    for (int i = 0; i < arrSize; i++) {
        currUp = objArr[i].up();
        if (!objArr[i].getActiveState()) {objArr[i].revive();}
        currDown = objArr[i].down();
        if (!objArr[i].getActiveState()) {objArr[i].revive();}
        if (objArr[i].getActiveState()) {
            for (int j = i; j < arrSize; j++) {
                if (objArr[j].getActiveState()) {
                    targetUp = objArr[j].up();
                    if (!objArr[j].getActiveState()) {objArr[j].revive();}
                    targetDown = objArr[j].down();
                    if (!objArr[j].getActiveState()) {objArr[j].revive();}
                    if (currUp == targetDown || currDown == targetUp) { inversionCount++; }
                } else {numDeactivated++;}
            }
        } else {numDeactivated++;}
    }
    return inversionCount;
}

