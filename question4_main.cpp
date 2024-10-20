/******************************************************************************

This code is for the Question 4 in the Homework 1 of AERSP 424

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
    map<string, Flight_Information>& flights;

//public members
public:
    
    // A constructor
    Plane(string from, string to, map<string, Flight_Information>& flight_map) : flights(flight_map) {
        origin = from;
        destination = to;
        pos = 0.0;
        vel = 0.0;
        distance = 0.0;
        at_SCE = (from == "SCE");
        
        //Set the value of “distance” using the container from question 2
        string flightinfo = from + "-" + to;
        if (flights.find(flightinfo) != flights.end()) {
            distance = flights[flightinfo].distance;
        } else {
            cout << "Flight Not Found!" << endl;
        }
        
        //Print out a string “Plane Created at ” followed by the memory address where this plane object is stored
        cout << "Plane Created at " << this << endl;
        
    }
    
    // A deconstructor
    ~Plane() {
        cout << "Plane Destroyed" << endl;
    }
    
    // Operate function
    void operate(double dt) {
        if (pos < distance) {
            pos += vel * dt;
             if (pos > distance) {
            pos = distance;
            }
            return;
        }
            
        if (destination == "SCE") {
            if (at_SCE == 1) {
                at_SCE = 0;  
                pos = 0.0;  
            }
        } else {
              swap(origin, destination);
            pos = 0.0;  
            at_SCE = 1; 
        }
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
    // Flight information from Question 2
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
    
    Plane myPlane(origin, destination, flights);
    
    double velocity;
    cout << "Enter the velocity (m/s): ";
    cin >> velocity;
    myPlane.setVel(velocity);
    
    double dt;
    cout << "Enter the dt (s): ";
    cin >> dt;
    myPlane.operate(dt);
    
    // output some information using Get function
    cout << "Origin: " << myPlane.getOrigin() << endl;
    cout << "Destination: " << myPlane.getDestination() << endl;
    cout << "Position: " << myPlane.getPos() << endl;
    cout << "At SCE: " << (myPlane.getAtSCE() ? "Yes" : "No") << endl;
    
    return 0;
}
