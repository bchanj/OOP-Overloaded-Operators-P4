// Brandon Chan
// jumpPrime.h
// 9/20/20

#ifndef P4_JUMPPRIME_H
#define P4_JUMPPRIME_H

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

/* INTERFACE INVARIANT
 * - Calling up(), down(), or reset() on a deactivated object will yield a negative value and will not
 *   return any data on the object itself. Calls to reset() or revive() will not count as queries.
 * - Calling revive() on an already active object will permanently deactivate it.
 * - Encapsulating a number lower than 1000 will cause the object to default to the value 2488.
 * - If the object jumps to a value below 1000 the object will become deactivated.
 * - Calling revive() on an a non permanently deactivated or active object will switch the active state,
 *   reset the number of jumps counted on that object, and potentially reset() the object if
 *   the encapsulated number was below the bounds of 1000.
 * - Using either up(), down(), or getActiveState() will add to the queryCount of the object, potentially
 *   provoking a jump and therefore may lead to object deactivation.
 * - up() or down() calls on an object with an encapsulated prime number will find the next nearest upper
 *   and lower prime numbers.
 * - Calling reset() will reset an object to its initial state if it is currently active.
 * - Passing in negative values into mathematical operators not supported.
 * - Streaming operators not supported.
 * - == and != check the active state of objects in addition to encapsulated number.
 * - Subtracting below the lower bounds of a jumpPrime object will set the value to the default number.
 * - += -= and post and pre ++ and -- will change the state of the object.
 * - Mixed mode with integers is supported is supported for all operations besides ==, !=, -- and ++.
 * - All operators can be used on both active, inactive, and permanently deactivated objects and cannot alter the
 *   active state of an object due to error handling.
 * - Using integers in the format of 'int (operator) jumpPrime' will swap the positions of the int and jumpPrime
 *   objects when using mathematical operators and may not yield expected results.
 * - Assignment nor copying supported.
 */

class jumpPrime {

public:

    /* POST: Creates an permanently inactive jumpPrime object */
    jumpPrime();

    /* PRE:  A positive integer of at least 4 digits must be passed in.
       POST: 'num' will be assigned the value passed in and object will be created and member variables will
             be initialized. */
    jumpPrime(int userGivenVal);

    // POST: Will return a temporary with an encapsulated number of the LHS and RHS encapsulated numbers added.
    jumpPrime operator+(const jumpPrime& rhs);

    // PRE: The LHS and RHS values, once subtracted, must be within bounds
    // POST: A jumpPrime object with a new encapsulated number resulting from
    //       the LHS encapsulated number subtracted by the RHS encapsulated number.
    //       Returned object may have the default encapsulated number if pre-conditions
    //       not satisfied.
    jumpPrime operator-(const jumpPrime& rhs);

    // POST: Will add the RHS objects encapsulated number onto the LHS encapsulated number
    jumpPrime& operator+=(const jumpPrime& rhs);

    // PRE: The LHS and RHS values, once subtracted, must be within bounds
    // POST: The LHS object will be directly altered by changing it's encapsulated number
    //       by subtracting the RHS encapsulated num from it.
    //       LHS object may have the default encapsulated number if pre-conditions
    //       not satisfied.
    jumpPrime& operator-=(const jumpPrime& rhs);

    // POST: Will return a temporary with an encapsulated number of LHS % RHS.
    jumpPrime operator%(const jumpPrime& rhs);

    // POST: Will return a temporary with an encapsulated number of LHS / RHS.
    jumpPrime operator/(const jumpPrime& rhs);

    // POST: Will return a temporary with an encapsulated number of LHS * RHS.
    jumpPrime operator*(const jumpPrime& rhs);

    // PRE: Client must not pass in a negative value
    // POST: Will return a temporary with an encapsulated number of LHS + RHS.
    jumpPrime operator+(const int& rhs);

    // POST: Will return a temporary with an encapsulated number of LHS - RHS.
    jumpPrime operator-(const int& rhs);

    // PRE: Client must not pass in a negative value
    // POST: Will add the RHS objects encapsulated number onto the LHS encapsulated number.
    jumpPrime& operator+=(const int& rhs);

    // PRE: The LHS and RHS values, once subtracted, must be within bounds
    // POST: The LHS object will be directly altered by changing it's encapsulated number
    //       by subtracting the RHS integer from it.
    //       LHS object may have the default encapsulated number if pre-conditions
    //       not satisfied.
    jumpPrime& operator-=(const int& rhs);

    // PRE: Client must not pass in a negative value
    // POST: Will return a temporary with an encapsulated number of LHS % RHS.
    jumpPrime operator%(const int& rhs);

    // PRE: Client must not pass in a negative value
    // POST: Will return a temporary with an encapsulated number of LHS / RHS.
    jumpPrime operator/(const int& rhs);

    // PRE: Client must not pass in a negative value
    // POST: Will return a temporary with an encapsulated number of LHS * RHS.
    jumpPrime operator*(const int& rhs);

    // POST: Will increment encapsulated number and return the object.
    jumpPrime& operator++();

    // POST: Will decrement the encapsulated number and return the object
    jumpPrime& operator--();

    // POST: Will increment the encapsulated number but return the object pre-increment
    jumpPrime operator++(int dummy);

    // POST: Will decrement the encapsulated number but return the object pre-decrement
    jumpPrime operator--(int dummy);

    // POST: Will return whether or not objects are identical by encapsulated num and active state
    bool operator==(const jumpPrime& rhs);

    // POST: Will return whether or not objects are not identical by encapsulated num and active state
    bool operator!=(const jumpPrime& rhs);

    // POST: Will return whether or not lhs object is less than rhs object's encapsulated number.
    bool operator<(const jumpPrime& rhs);

    // POST: Will return whether or not lhs object is less than
    //       the passed in integer.
    bool operator<(const int& rhs);

    // POST: Will return whether or not lhs object is greater than rhs object's encapsulated number.
    bool operator>(const jumpPrime& rhs);

    // POST: Will return whether or not lhs object is greater than
    //       the passed in integer.
    bool operator>(const int& rhs);

    // POST: Will return whether or not lhs object is less than or equal to
    //       rhs object's encapsulated number.
    bool operator<=(const jumpPrime& rhs);

    // POST: Will return whether or not lhs object is less than or equal to
    //       the passed in integer.
    bool operator<=(const int& rhs);

    // POST: Will return whether or not lhs object is greater than or equal to
    //       rhs object's encapsulated number.
    bool operator>=(const jumpPrime& rhs);

    // POST: Will return whether or not lhs object is greater than or equal to
    //       the passed in integer.
    bool operator>=(const int& rhs);

    /* POST: queryCount will increase, if not reset. Object may become deactivated. jumpVal, num, upp, low,
              may be changed. jumpCount may increase. */
    bool getActiveState();

    /* PRE: Object must be activated.
       POST: Object will have all member values reset to their initial state. */
    bool reset();

    /* POST: Object will change "activated" state and may be reset or become permanently inactive. */
    void revive();

    /* PRE:  Object must be active.
       POST: The nearest upper prime number will be returned.
             Encapsulated number may increase and exceed bounds. Object may be deactivated, 'upp'
             and 'low' may increase. queryCount may reset. jumpVal may change in response to new 'upp'
             and 'low' values. jumpCount may increase. */
    int up();

    /* PRE:  Object must be active.
       POST: The nearest lower prime number will be returned.
             Encapsulated number may decrease and exceed bounds. Object may be deactivated, 'upp'
             and 'low' may decrease. queryCount may reset. jumpVal may change in response to new 'upp'
             and 'low' values. jumpCount may increase. */
    int down();

private:

    // POST: Will return whether or no the passed in value is a prime number.
    bool isAPrimeNum(int val);

    // PRE:  Object must be active.
    // POST: The nearest lower prime number will be returned.
    //     Encapsulated number may decrease and exceed bounds. Object may be deactivated, 'upp'
    //     and 'low' may decrease. queryCount may reset. jumpVal may change in response to new 'upp'
    //     and 'low' values. jumpCount may increase.
    void jump();

    int num;
    int initialNum;
    int low;
    int upp;
    int queryCount;
    int jumpVal;
    int jumpCount;
    bool activated;
    bool permDeactivated;

    static const int lowerBounds = 100;
    static const int defaultNum = 2503;
    static const int maxJumpCount = 10;

};

// POST: Will return boolean based on comparison and is used when LHS is an integer and RHS
//       is a jumpPrime object.
bool operator<(int num, jumpPrime lhs);

// POST: Will return boolean based on comparison and is used when LHS is an integer and RHS
//       is a jumpPrime object.
bool operator>(int num, jumpPrime lhs);

// POST: Will return boolean based on comparison and is used when LHS is an integer and RHS
//       is a jumpPrime object.
bool operator<=(int num, jumpPrime lhs);

// POST: Will return boolean based on comparison and is used when LHS is an integer and RHS
//       is a jumpPrime object.
bool operator>=(int num, jumpPrime lhs);

// POST: If an integer is the LHS, the integer will swap
//       places with the object in respect to its operation.
//       Ex. int + obj will become obj + int
jumpPrime operator+(int lhs, jumpPrime& rhs);

// POST: If an integer is the LHS, the integer will swap
//       places with the object in respect to its operation.
//       Ex. int - obj will become obj - int
jumpPrime operator-(int lhs, jumpPrime& rhs);

// POST: If an integer is the LHS, the integer will swap
//       places with the object in respect to its operation.
//       Ex. int += obj will become obj += int
jumpPrime& operator+=(int lhs, jumpPrime& rhs);

// POST: If an integer is the LHS, the integer will swap
//       places with the object in respect to its operation.
//       Ex. int -= obj will become obj -= int
jumpPrime& operator-=(int lhs, jumpPrime& rhs);

// POST: If an integer is the LHS, the integer will swap
//       places with the object in respect to its operation.
//       Ex. int % obj will become obj % int
jumpPrime operator%(int lhs, jumpPrime& rhs);

// POST: If an integer is the LHS, the integer will swap
//       places with the object in respect to its operation.
//       Ex. int / obj will become obj / int
jumpPrime operator/(int lhs, jumpPrime& rhs);

// POST: If an integer is the LHS, the integer will swap
//       places with the object in respect to its operation.
//       Ex. int * obj will become obj * int
jumpPrime operator*(int lhs, jumpPrime& rhs);

#endif //P4_JUMPPRIME_H
