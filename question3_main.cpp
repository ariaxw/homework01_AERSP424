/******************************************************************************

This code is for the Question 3 in the Homework 1 of AERSP 424

Author: Xue (Aria) Wang

*******************************************************************************/

#include <iostream>
#include <string>
#include <map>
using namespace std;

// The container from Question 2
struct Flight_Information {
    string origin;
    string destination;
    int distance;
};

// Define the "Plane" class
class Plane {
    
// private members
private:
    double pos;           
    double vel;          
    double distance;     
    bool at_SCE;        
    string origin;       
    string destination;   
    map<string, Flight_Information> flights;

//public members
public:
    
    // A constructor
    Plane(string from, string to) {
        origin = from;
        destination = to;
        at_SCE = (from == "SCE");  
    }
    
    // A deconstructor
    ~Plane() {
    }
    
    // Operate function, return nothing
    void operate(double dt) {
    }
    
    // Get funciton, obtain "pos"
    double getPos() const {
        return pos;
    }
    
    // // Get funciton, obtain "origin"
    string getOrigin() const {
        return origin;
    }

    // Get function, obtain "destination"
    string getDestination() const {
        return destination;
    }
    
    // Get funciton, obtain "at_SCE"
    bool getAtSCE() const {
        return at_SCE;
    }
    
    // Set function, set "vel"
    void setVel(double velocity) {
        vel = velocity;
    }
};

int main() {
    // flights from Question 2
    map<string, Flight_Information> flights;
    flights["SCE-PHL"] = {"SCE", "PHL", 160};
    flights["SCE-ORD"] = {"SCE", "ORD", 640};
    flights["SCE-EWR"] = {"SCE", "EWR", 220};
    
    // An example of plane
    string origin, destination;
    cout << "Enter the origin airport code (e.g., SCE): ";
    cin >> origin;
    cout << "Enter the destination airport code (e.g., PHL): ";
    cin >> destination;
    
    Plane myPlane(origin, destination);

    // output some information using Get function
    cout << "Origin: " << myPlane.getOrigin() << endl;
    cout << "Destination: " << myPlane.getDestination() << endl;
    cout << "At SCE: " << (myPlane.getAtSCE() ? "Yes" : "No") << endl;
    
    return 0;
}
