// Brandon Chan
// duelingJP.h - Header file for the duelingJP object.
// 9/21/20
// Written in C++ on CLion
// CPSC 3200 Professor Dingle, Seattle University Fall Quarter 2020

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
 * - Comparison operators ==, !=, <=, >= will compare the contents of two duelingJP objects encapsulated arrays
 *   in addition to the size of their arrays.
 */

/* INTERFACE INVARIANT
 * - Calls to collide() and inversion() will only offer valid values if called on a duelingJP object with an array of
 *   jumpPrime objects that aren't all deactivated.
 * - Use of the null argument constructor.
 * - In order to guarantee expected use of the duelingJP constructor, the user must specify a non-negative, non-zero
 *   value as a parameter or else the contract is broken and the size of the array will be set to the default value.
 * - Calling collide() or inversion() on an array of inactive objects will not yield expected results and will return a
 *   negative value.
 * - Mathematical operators do not support negative values.
 * - Supports < and > between duelingJP objects and integers.
 * - Supports all comparison operators.
 * - Supports + which returns a temporary with the RHS objects array concatenated to the LHS objects array.
 * - Supports - which returns a shortened temporary of the LHS array by the RHS array size. LHS must be greater than
 *   the RHS or else a temporary with a null array will be returned.
 * - Supports += which concatenates the RHS objects array to the LHS objects array and adds the RHS array size
 *   to the LHS array size.
 * - Supports -= which shortens the LHS objects array by the array size of the RHS object while also decreasing the
 *   array size of LHS. LHS must be greater than the RHS or else an invalid array (size 0) will be encapsulated in
 *   the LHS.
 * - Comparison operators ==, !=, <= and >= check the array size of the object in addition to if the encapsulated
 *   arrays are also identical.
 */

#ifndef P4_DUELINGJP_H
#define P4_DUELINGJP_H

#include "jumpPrime.h"

class duelingJP {

public:
    // POST: Creates a duelingJP object with the default array size.
    duelingJP();

    // PRE: Must give a valid array size (non negative, non zero).
    // POST: Will create a duelingJP object with an array the size specified by the user.
    duelingJP(int numObj);

    // POST: Creates a deep copy of the object.
    duelingJP(const duelingJP& djp);

    // POST: Heap memory transferred between objects and the caller loses access to that heap memory.
    duelingJP(duelingJP&& djp);

    // POST: The left hand side object will replace all of its members with those of the right hand side object.
    duelingJP& operator=(const duelingJP& rhs);

    // POST: An object with the RHS array concatenated onto the LHS array will be returned.
    duelingJP operator+(const duelingJP& rhs);

    // POST: The LHS object will have its array changed by concatenating the array of the RHS to its own array.
    duelingJP& operator+=(const duelingJP& rhs);

    // PRE: RHS value must be greater than the LHS
    // POST: May return an object with an invalid array length of 0
    duelingJP operator-(const duelingJP& rhs);

    // PRE: RHS value must be greater than the LHS
    // POST: May set object to have an invalid array (length 0) if pre conditions not satisfied
    duelingJP& operator-=(const duelingJP& rhs);

    // POST: Will return whether or not the LHS has a lesser array length than the RHS.
    bool operator<(const duelingJP& rhs);

    // POST: Will return whether or not the LHS has a lesser array length than the RHS.
    bool operator<(const int& rhs);

    // POST: Will return whether or not the LHS has a greater array length than the RHS.
    bool operator>(const duelingJP& rhs);

    // POST: Will return whether or not the LHS has a greater array length than the RHS.
    bool operator>(const int& rhs);

    // POST: Will return whether or not the LHS and RHS objects have identical arrays.
    bool operator==(const duelingJP& rhs);

    // POST: Will return whether or not the LHS and RHS objects do not have identical arrays.
    bool operator!=(const duelingJP& rhs);

    // POST: Will return whether or not the LHS array size is less than or equal to
    //       the lhs array size or has identical arrays.
    bool operator<=(const duelingJP& rhs);

    // POST: Will return whether or not the LHS array size is greater than or equal to
    //       the lhs array size or has identical arrays.
    bool operator>=(const duelingJP& rhs);

    // POST: The ownership between the left hand side and right hand side objects will swap.
    duelingJP& operator=(duelingJP&& rhs);

    // POST: The duelingJP array will be deleted and all memory for the object will be released.
    ~duelingJP();

    // PRE: Calling this on an array of inactive objects will not yield expected results and will return a negative value.
    // POST: Will return and locally increment the number of collisions on all jumpPrime objects within the array.
    //       Objects may be deactivated.
    int collide();

    // PRE: Calling this on an array of inactive objects will not yield expected results and will return a negative value.
    // POST: Will return and locally increment the number of inversions on all jumpPrime objects within the array. Objects may be deactivated.
    int inversion();

private:
    jumpPrime* objArr;
    int collisionCount;
    int inversionCount;
    int arrSize;
    int numDeactivated;
    static const int defaultSize = 5;
    static const int startingJpNum = 5000;
    static const int geometricNum = 50;
};

// POST: Will return whether or not the integer is less than the duelingJP object
bool operator<(int num, duelingJP lhs);

// POST: Will return whether or not the integer is greater than the duelingJP object
bool operator>(int num, duelingJP lhs);

#endif //P4_DUELINGJP_H
