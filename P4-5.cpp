// Brandon Chan
// p4.cpp - Driver for the duelingJP and jumpPrime objects and their overloaded operators.
// 10/26/20
// Written in C++ on CLion
// CPSC 3200 Professor Dingle, Seattle University Fall Quarter 2020

// Purpose: This driver acts to test all mathematical and comparison overloaded operators
//          of both the duelingJP and jumpPrime objects. It first tests the duelingJP object
//          and then the jumpPrime object.
//          * Comparison operators are used as a way to test mathematical operators.
//          * All arrays are populated with randomly instantiated objects.
//          * An integer array holds a copy of the random value used in construction in each
//            object and is used to track what number is encapsulated in each object.
//          * No testing functions alter the state of the original object arrays in main().

// Revisions:
//   Version 1.0 - 9/27/20 - Initial driver for use of the duelingJP object.
//   Version 2.0 - 10/26/20 - Added testing of overloaded operators for the duelingJP
//                 and jumpPrime objects.

#include "duelingJP.h"
#include <iostream>
#include <memory>
#include <ctime>
#include <vector>

using namespace std;

const int DEFAULTSIZE = 5;
const int DEFAULTSIZE2 = 15;

const int MIXEDMODEINT = 10;
const int DEFAULTJPNUM = 2503;

const int RANDLOWERDJP = 5;
const int RANDUPPERDJP = 15;
const int RANDLOWERJP = 10000;
const int RANDUPPERJP = 50000;

const int ARRAYSIZE = 3;
const int SMARTARRAYSIZE = 5;

// Provides testing for the duelingJP overloaded operators
void printComparisons(duelingJP djp1, duelingJP djp2);
void testAddition(duelingJP objArr[], int arr[]);
void testSubtraction(duelingJP objArr[], int arr[]);
void testAdditionEquals(duelingJP objArr[], int arr[]);
void testSubtractionEquals(duelingJP objArr[], int arr[]);
void testComparisonInt(duelingJP objArr[]);

// Provides testing for the jumpPrime overloaded operators
void printComparisonsJP(jumpPrime jp1, jumpPrime jp2);
void testAdditionJP(jumpPrime objArr[], int arr[]);
void testSubtractionJP(jumpPrime objArr[], int arr[]);
void testMultiplicationJP(jumpPrime objArr[], int arr[]);
void testDivisionJP(jumpPrime objArr[], int arr[]);
void testModulusJP(jumpPrime objArr[], int arr[]);
void testAdditionEqualsJP(jumpPrime objArr[], int arr[]);
void testSubtractionEqualsJP(jumpPrime objArr[], int arr[]);
void increment(jumpPrime objArr[], int arr[]);
void decrement(jumpPrime objArr[], int arr[]);

// Provides testing for the duelingJP and move semantics functionality
void testCollisionInversion();
void testMoveCopy(vector<unique_ptr<duelingJP>> &v1);
void testMoveAssignment(vector<shared_ptr<duelingJP>> &v1);

int main() {

    srand(time(NULL));
    int random;
    duelingJP djpArr[ARRAYSIZE];
    jumpPrime jpArr[ARRAYSIZE];

    int randArr[ARRAYSIZE];
    for (int i = 0; i < ARRAYSIZE; i++) {
        random = (rand() % RANDUPPERDJP) + RANDLOWERDJP;
        duelingJP obj(random);
        randArr[i] = random;
        djpArr[i] = obj;
    }

    cout << endl;
    cout << "=== NOW TESTING DUELINGJP === " << endl;
    testAddition(djpArr, randArr);
    testSubtraction(djpArr, randArr);
    testAdditionEquals(djpArr, randArr);
    testSubtractionEquals(djpArr, randArr);
    testComparisonInt(djpArr);
    cout << endl;

    for (int i = 0; i < ARRAYSIZE; i++) {
        random = (rand() % RANDUPPERJP) + RANDLOWERJP;
        jumpPrime obj(random);
        randArr[i] = random;
        jpArr[i] = obj;
    }

    cout << "=== NOW TESTING JUMPPRIME === " << endl;
    cout << "Note: Mixed mode comparisons are used to determine success of" << endl
         << "      state changing or destructive operators." << endl;
    testAdditionJP(jpArr, randArr);
    testSubtractionJP(jpArr, randArr);
    testMultiplicationJP(jpArr, randArr);
    testDivisionJP(jpArr, randArr);
    testModulusJP(jpArr, randArr);
    testAdditionEqualsJP(jpArr, randArr);
    testSubtractionEqualsJP(jpArr, randArr);
    increment(jpArr, randArr);
    decrement(jpArr, randArr);

    // *** FOR P2 REGRADING ***

    vector<unique_ptr<duelingJP>> djpVector;
    vector<shared_ptr<duelingJP>> sharedVector;
    for (int i = 0; i < SMARTARRAYSIZE; i++) {
        random = (rand() % RANDUPPERDJP) + RANDLOWERDJP;
        unique_ptr<duelingJP> tempUniquePtr = make_unique<duelingJP>(random);
        shared_ptr<duelingJP> tempUniquePtr2 = make_shared<duelingJP>(random);
        djpVector.push_back(move(tempUniquePtr));
        sharedVector.push_back(move(tempUniquePtr2));
    }
    testCollisionInversion();
    testMoveCopy(djpVector);
    testMoveAssignment(sharedVector);

    return 0;
}

void testAddition(duelingJP objArr[], int arr[]) {
    duelingJP temp(DEFAULTSIZE);
    for (int i = 0; i < ARRAYSIZE-1; i++) {
        cout << "Testing + between " << arr[i] << " and " << arr[i+1] << endl;
        cout << "BEFORE:                 ";
        printComparisons(objArr[i], objArr[i+1]);
        cout << "RESULT COMPARED TO RHS: ";
        temp = objArr[i] + objArr[i+1];
        printComparisons(temp, arr[i+1]);
        cout << endl;
    }
}

void testSubtraction(duelingJP objArr[], int arr[]) {
    duelingJP temp(DEFAULTSIZE);
    for (int i = 0; i < ARRAYSIZE-1; i++) {
        cout << "Testing - between " << arr[i] << " and " << arr[i+1] << endl;
        cout << "BEFORE:                 ";
        printComparisons(objArr[i], objArr[i+1]);
        cout << "RESULT COMPARED TO RHS: ";
        temp = objArr[i] - objArr[i+1];
        printComparisons(temp, arr[i+1]);
        cout << endl;
    }
}

void testAdditionEquals(duelingJP objArr[], int arr[]) {
    duelingJP newArr[ARRAYSIZE];
    int temp;
    for (int i = 0; i < ARRAYSIZE; i++) { newArr[i] = objArr[i]; }

    for (int i = 0; i < ARRAYSIZE-1; i++) {
        cout << "Testing += between " << arr[i] << " and " << arr[i+1] << endl;
        cout << "BEFORE:                 ";
        printComparisons(newArr[i], newArr[i+1]);
        cout << "RESULT COMPARED TO RHS: ";
        newArr[i] += newArr[i+1];
        temp = arr[i] + arr[i+1];
        printComparisons(newArr[i], newArr[i+1]);

        if (newArr[i] > temp || (newArr[i] < temp)) { cout << "Failed!" << endl; }
        else {cout << "Success!" << endl;}
        cout << endl;
    }
}

void testSubtractionEquals(duelingJP objArr[], int arr[]) {
    duelingJP newArr[ARRAYSIZE];
    int temp;
    for (int i = 0; i < ARRAYSIZE; i++) { newArr[i] = objArr[i]; }

    for (int i = 0; i < ARRAYSIZE-1; i++) {
        cout << "Testing -= between " << arr[i] << " and " << arr[i+1] << endl;
        cout << "BEFORE:                 ";
        printComparisons(newArr[i], newArr[i+1]);
        cout << "RESULT COMPARED TO RHS: ";
        newArr[i] -= newArr[i+1];
        temp = arr[i] - arr[i+1];
        printComparisons(newArr[i], newArr[i+1]);

        if ((newArr[i] > temp || newArr[i] < temp)
            && (newArr[i] > 0 || newArr[i] < 0)) { cout << "Failed!" << endl; }
        else {cout << "Success!" << endl;}
        cout << endl;
    }
}

void testComparisonInt(duelingJP objArr[]) {
    cout << "Testing mixed mode with integers for > and <" << endl;
    cout << "Object < than " << MIXEDMODEINT << ": " << (objArr[0] < MIXEDMODEINT) << endl;
    cout << MIXEDMODEINT << " is < Object: " << (MIXEDMODEINT < objArr[0]) << endl;
    cout << "Object > than " << MIXEDMODEINT << ": " << (objArr[0] > MIXEDMODEINT) << endl;
    cout << MIXEDMODEINT << " is > Object: " << (MIXEDMODEINT > objArr[0]) << endl;
}


void printComparisons(duelingJP obj1, duelingJP obj2) {
    cout << "    >: " << (obj1 > obj2)
         << "    <: " << (obj1 < obj2);
    cout << "   !=: " << (obj1 != obj2)
         << "   ==: " << (obj1 == obj2);
    cout << "   <=: " << (obj1 <= obj2)
         << "   >=: " << (obj1 >= obj2);
    cout << endl;
}

void testAdditionJP(jumpPrime objArr[], int arr[]) {
    jumpPrime temp(DEFAULTJPNUM);
    for (int i = 0; i < ARRAYSIZE-1; i++) {
        cout << "Testing + between " << arr[i] << " and " << arr[i+1] << endl;
        cout << "BEFORE:                 ";
        printComparisonsJP(objArr[i], objArr[i+1]);
        cout << "RESULT COMPARED TO RHS: ";
        temp = objArr[i] + objArr[i+1];
        printComparisonsJP(temp, arr[i+1]);

        cout << "For mixed mode, results should be the same for both scenarios..." << endl;
        cout << "Testing mixed mode: object + integer, then comparing temporary to original object" << endl;
        temp = objArr[i] + MIXEDMODEINT;
        cout << "                        ";
        printComparisonsJP(temp, arr[i]);

        cout << "Testing mixed mode: integer + object, then comparing temporary to original object" << endl;
        temp = MIXEDMODEINT + objArr[i];
        cout << "                        ";
        printComparisonsJP(temp, arr[i]);

        cout << endl;
    }
}

void testSubtractionJP(jumpPrime objArr[], int arr[]) {
    jumpPrime temp(DEFAULTJPNUM);
    for (int i = 0; i < ARRAYSIZE-1; i++) {
        cout << "Testing - between " << arr[i] << " and " << arr[i+1] << endl;
        cout << "BEFORE:                 ";
        printComparisonsJP(objArr[i], objArr[i+1]);
        cout << "RESULT COMPARED TO RHS: ";
        temp = objArr[i] - objArr[i+1];
        printComparisonsJP(temp, arr[i+1]);

        cout << "For mixed mode, results should be the same for both scenarios..." << endl;
        cout << "Testing mixed mode: object - integer, then comparing temporary to original object" << endl;
        temp = objArr[i] - MIXEDMODEINT;
        cout << "                        ";
        printComparisonsJP(temp, arr[i]);

        cout << "Testing mixed mode: integer - object, then comparing temporary to original object" << endl;
        temp = MIXEDMODEINT - objArr[i];
        cout << "                        ";
        printComparisonsJP(temp, arr[i]);

        cout << endl;
    }
}

void testMultiplicationJP(jumpPrime objArr[], int arr[]) {
    jumpPrime temp(DEFAULTJPNUM);
    for (int i = 0; i < ARRAYSIZE-1; i++) {
        cout << "Testing * between " << arr[i] << " and " << arr[i+1] << endl;
        cout << "BEFORE:                 ";
        printComparisonsJP(objArr[i], objArr[i+1]);
        cout << "RESULT COMPARED TO RHS: ";
        temp = objArr[i] * objArr[i+1];
        printComparisonsJP(temp, arr[i+1]);

        cout << "For mixed mode, results should be the same for both scenarios..." << endl;
        cout << "Testing mixed mode: object * integer, then comparing temporary to original object" << endl;
        temp = objArr[i] * MIXEDMODEINT;
        cout << "                        ";
        printComparisonsJP(temp, arr[i]);

        cout << "Testing mixed mode: integer * object, then comparing temporary to original object" << endl;
        temp = MIXEDMODEINT * objArr[i];
        cout << "                        ";
        printComparisonsJP(temp, arr[i]);

        cout << endl;
    }
}
void testDivisionJP(jumpPrime objArr[], int arr[]) {
    jumpPrime temp(DEFAULTJPNUM);
    for (int i = 0; i < ARRAYSIZE-1; i++) {
        cout << "Testing / between " << arr[i] << " and " << arr[i+1] << endl;
        cout << "BEFORE:                 ";
        printComparisonsJP(objArr[i], objArr[i+1]);
        cout << "RESULT COMPARED TO RHS: ";
        temp = objArr[i] / objArr[i+1];
        printComparisonsJP(temp, arr[i+1]);

        cout << "For mixed mode, results should be the same for both scenarios..." << endl;
        cout << "Testing mixed mode: object / integer, then comparing temporary to original object" << endl;
        temp = objArr[i] / MIXEDMODEINT;
        cout << "                        ";
        printComparisonsJP(temp, arr[i]);

        cout << "Testing mixed mode: integer / object, then comparing temporary to original object" << endl;
        temp = MIXEDMODEINT / objArr[i];
        cout << "                        ";
        printComparisonsJP(temp, arr[i]);

        cout << endl;
    }
}
void testModulusJP(jumpPrime objArr[], int arr[]) {
    jumpPrime temp(DEFAULTJPNUM);
    for (int i = 0; i < ARRAYSIZE-1; i++) {
        cout << "Testing % between " << arr[i] << " and " << arr[i + 1] << endl;
        cout << "BEFORE:                 ";
        printComparisonsJP(objArr[i], objArr[i + 1]);
        cout << "RESULT COMPARED TO RHS: ";
        temp = objArr[i] % objArr[i + 1];
        printComparisonsJP(temp, arr[i + 1]);

        cout << "For mixed mode, results should be the same for both scenarios..." << endl;
        cout << "Testing mixed mode: object % integer, then comparing temporary to original object" << endl;
        temp = objArr[i] % MIXEDMODEINT;
        cout << "                        ";
        printComparisonsJP(temp, arr[i]);

        cout << "Testing mixed mode: integer % object, then comparing temporary to original object" << endl;
        temp = MIXEDMODEINT % objArr[i];
        cout << "                        ";
        printComparisonsJP(temp, arr[i]);

        cout << endl;
    }
}

void testAdditionEqualsJP(jumpPrime objArr[], int arr[]) {
    jumpPrime newArr[ARRAYSIZE];
    int temp;
    jumpPrime tempJP(DEFAULTJPNUM);
    for (int i = 0; i < ARRAYSIZE; i++) { newArr[i] = objArr[i]; }

    for (int i = 0; i < ARRAYSIZE-1; i++) {
        cout << "Testing += between " << arr[i] << " and " << arr[i+1] << endl;
        cout << "BEFORE:                 ";
        printComparisonsJP(newArr[i], newArr[i+1]);
        cout << "RESULT COMPARED TO RHS: ";
        newArr[i] += newArr[i+1];
        temp = arr[i] + arr[i+1];
        printComparisonsJP(newArr[i], newArr[i+1]);

        if (newArr[i] > temp || (newArr[i] < temp)) { cout << "Failed!" << endl; }
        else {cout << "Success!" << endl;}
        cout << endl;

        cout << "For mixed mode, results should be the same for both scenarios..." << endl;
        cout << "Testing mixed mode: object % integer, then comparing temporary to original object" << endl;
        tempJP = objArr[i];
        tempJP += MIXEDMODEINT;
        cout << "                        ";
        printComparisonsJP(tempJP, arr[i]);

        cout << "Testing mixed mode: integer % object, then comparing temporary to original object" << endl;
        tempJP = objArr[i];
        MIXEDMODEINT += tempJP;
        cout << "                        ";
        printComparisonsJP(tempJP, arr[i]);

    }
}
void testSubtractionEqualsJP(jumpPrime objArr[], int arr[]) {
    jumpPrime newArr[ARRAYSIZE];
    int temp;
    jumpPrime tempJP(DEFAULTJPNUM);
    for (int i = 0; i < ARRAYSIZE; i++) { newArr[i] = objArr[i]; }

    for (int i = 0; i < ARRAYSIZE-1; i++) {
        cout << "Testing -= between " << arr[i] << " and " << arr[i+1] << endl;
        cout << "BEFORE:                 ";
        printComparisonsJP(newArr[i], newArr[i+1]);
        cout << "RESULT COMPARED TO RHS: ";
        newArr[i] -= newArr[i+1];
        temp = arr[i] - arr[i+1];
        printComparisonsJP(newArr[i], newArr[i+1]);

        if ((newArr[i] > temp || newArr[i] < temp)
            && (newArr[i] > DEFAULTJPNUM || newArr[i] < DEFAULTJPNUM)) { cout << "Failed!" << endl; }
        else {cout << "Success!" << endl;}
        cout << endl;

        cout << "For mixed mode, results should be the same for both scenarios..." << endl;
        cout << "Testing mixed mode: object % integer, then comparing temporary to original object" << endl;
        tempJP = objArr[i];
        tempJP -= MIXEDMODEINT;
        cout << "                        ";
        printComparisonsJP(tempJP, arr[i]);

        cout << "Testing mixed mode: integer % object, then comparing temporary to original object" << endl;
        tempJP = objArr[i];
        MIXEDMODEINT -= tempJP;
        cout << "                        ";
        printComparisonsJP(tempJP, arr[i]);

    }
}

void increment(jumpPrime objArr[], int arr[]) {
    jumpPrime newArr[ARRAYSIZE];
    int temp;
    for (int i = 0; i < ARRAYSIZE; i++) { newArr[i] = objArr[i]; }
    for (int i = 0; i < ARRAYSIZE; i++) {
        cout << "Testing obj++ on " << arr[i] << ": ";
        newArr[i]++;
        temp = arr[i];
        temp++;

        if (newArr[i] > temp || newArr[i] < temp) { cout << "Failed!" << endl; }
        else { cout << "Success!" << endl; }

        newArr[i] = objArr[i];

        cout << "Testing ++obj on " << arr[i] << ": ";
        ++newArr[i];
        temp = arr[i];
        ++temp;

        if (newArr[i] > temp || newArr[i] < temp) { cout << "Failed!" << endl; }
        else { cout << "Success!" << endl; }
        cout << endl;
    }
}

void decrement(jumpPrime objArr[], int arr[]) {
    jumpPrime newArr[ARRAYSIZE];
    int temp;
    for (int i = 0; i < ARRAYSIZE; i++) { newArr[i] = objArr[i]; }
    for (int i = 0; i < ARRAYSIZE; i++) {
        cout << "Testing obj-- on " << arr[i] << ": ";
        newArr[i]--;
        temp = arr[i];
        temp--;

        if (newArr[i] > temp || newArr[i] < temp) { cout << "Failed!" << endl; }
        else { cout << "Success!" << endl; }

        newArr[i] = objArr[i];

        cout << "Testing --obj on " << arr[i] << ": ";
        --newArr[i];
        temp = arr[i];
        --temp;

        if (newArr[i] > temp || newArr[i] < temp) { cout << "Failed!" << endl; }
        else { cout << "Success!" << endl; }
        cout << endl;
    }
}

void printComparisonsJP(jumpPrime obj1, jumpPrime obj2) {
    cout << "    >: " << (obj1 > obj2)
         << "    <: " << (obj1 < obj2);
    cout << "   !=: " << (obj1 != obj2)
         << "   ==: " << (obj1 == obj2);
    cout << "   <=: " << (obj1 <= obj2)
         << "   >=: " << (obj1 >= obj2);
    cout << endl;
}

void testCollisionInversion() {
    int collisions = 0;
    int inversions = 0;
    duelingJP obj(DEFAULTSIZE);
    while (collisions >= 0 || inversions >= 0) {
        collisions = obj.collide();
        if (collisions >= 0) {
            cout << "*** CALL TO COLLIDE() ***" << endl;
            cout << "COLLISIONS: " << collisions << endl;
        }
        inversions = obj.inversion();
        if (collisions >= 0) {
            cout << "*** CALL TO INVERSION() ***" << endl;
            cout << "INVERSIONS: " << inversions << endl;
        }
    }
    cout << endl;
}

void testMoveCopy(vector<unique_ptr<duelingJP>> &v1) {
    cout << "TESTING MOVE COPYING" << endl;
    unique_ptr<duelingJP> obj;
    for (int i = 0; i < SMARTARRAYSIZE; i++) {
        v1[i].swap(obj);
    }
    cout << "Success! Compiled. Move Copy Constructor working properly." << endl;
}

void testMoveAssignment(vector<shared_ptr<duelingJP>> &v1) {
    cout << "TESTING MOVE ASSIGNMENT" << endl;
    for (int i = 0; i < SMARTARRAYSIZE; i++) {
        shared_ptr<duelingJP> obj = v1[i];
    }
    cout << "Success! Compiled. Move Assignment working properly." << endl;
}
