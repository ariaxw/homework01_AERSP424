/******************************************************************************

This code is for the Question 5 in the Homework 1 of AERSP 424

Author: Xue (Aria) Wang

*******************************************************************************/

#include <iostream>
#include <string>
#include <map>
#include <sstream>
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
            pos += vel * dt / 3600;
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
    
    void resetPosition() {
        pos = 0.0; 
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

    string origin = "SCE", destination = "PHL";
    Plane myPlane(origin, destination, flights);
    
    // Input for flight speed
    string input;
    double velocity;
    cout << "Enter the flight speed between 400-500 mph (Press Enter to default: 450): ";
    getline(cin, input);
    if (input.empty()) {
        velocity = 450.0;  // Default value
    } else {
        stringstream(input) >> velocity;
    }
    myPlane.setVel(velocity);

    // Input for timestep
    double dt;
    cout << "Enter the timestep between [10,100] seconds (Press Enter to default: 15): ";
    getline(cin, input);
    if (input.empty()) {
        dt = 15;  // Default value
    } else {
        stringstream(input) >> dt;
    }

    // Input for maximum number of iterations
    int max_iterations;
    cout << "Enter the maximum number of iterations between [1000,2000] (Press Enter to default: 1500): ";
    getline(cin, input);
    if (input.empty()) {
        max_iterations = 1500;  // Default value
    } else {
        stringstream(input) >> max_iterations;
    }
    
    cout << "Time: 0 seconds, Position: 0 miles." << endl;

    // Run the simulation
    for (int i = 0; i < max_iterations; i++) {
        myPlane.operate(dt);
        
        cout << "Time: " << (i + 1) * dt << " seconds, Position: " << myPlane.getPos() << " miles." << endl;
        
        if (myPlane.getPos() >= flights[origin + "-" + destination].distance) {
            cout << "Navigation from " << myPlane.getOrigin() << " to " << myPlane.getDestination() << " has been completed. On to the next leg!" << endl;
            myPlane.resetPosition(); 
        }
    }
    
    cout << "Plane should get destroyed ... now!" << endl;

    return 0;
}
