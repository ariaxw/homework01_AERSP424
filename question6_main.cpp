/******************************************************************************

This code is for the Question 6 in the Homework 1 of AERSP 424

Author: Xue (Aria) Wang

*******************************************************************************/

#include <iostream>
#include <string>
using namespace std;

class Plane; 

class Pilot {
// Private members
private:
    string name;

// public members
public:

    // A constructor
    Pilot(string pilotName) : name(pilotName) {
        cout << name << " The pilot is at the gate, ready to board the plane. Address: " << this << endl;
    }

    // Destructor
    ~Pilot() {
        cout << name << " The pilot is out of the plane." << endl;
    }

    // Getter function for name
    string getName() {
        return name;
    }
    
    // Pointer to Plane object
    Plane* myPlane;  
};

int main() {
    return 0;
}
