/******************************************************************************

This code is for the Question 7 in the Homework 1 of AERSP 424

Author: Xue (Aria) Wang

The AI generated/support (ChatGPT) helped me write checkAtSCE and swapRoute function in the class Plane, 
which are used in the main function to achieve the following in the main program: 
1. The correct output "The plane xxxxxx is at SCE"; 
2.Reset the plane position and swap the route.

*******************************************************************************/

#include <iostream>
#include <string>
#include <map>
#include <sstream>
using namespace std;

struct Flight_Information {
    string origin;
    string destination;
    int distance;
};

// Define the "Plane" class
class Plane {
private:
    double pos;           
    double vel;          
    double distance;     
    bool at_SCE;        
    string origin;       
    string destination;   
    map<string, Flight_Information>& flights;

public:
    // Constructor
    Plane(string from, string to, map<string, Flight_Information>& flight_map) : flights(flight_map) {
        origin = from;
        destination = to;
        pos = 0.0;
        vel = 0.0;
        distance = 0.0;
        at_SCE = (from == "SCE");
        string flightinfo = from + "-" + to;
        if (flights.find(flightinfo) != flights.end()) {
            distance = flights[flightinfo].distance;
        } else {
            cout << "Flight Not Found!" << endl;
        }
        cout << "Plane Created with a tail number " << this << endl;
    }
    
    // Destructor
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
    
    double getPos() const {
        return pos;
    }

    string getOrigin() const {
        return origin;
    }

    string getDestination() const {
        return destination;
    }

    bool getAtSCE() const {
        return at_SCE;
    }

    void setVel(double velocity) {
        vel = velocity;
    }

    bool hasArrived() const {
        return pos >= distance;
    }

    void swapRoute() {
        swap(origin, destination);
        at_SCE = (origin == "SCE");
    }
    
    void checkAtSCE() {
        if (destination == "SCE" && pos >= distance) {
            at_SCE = true;
        }
    }
};


class Pilot {
private:
    string name;

public:
    // Constructor
    Pilot(string pilotName) : name(pilotName), myPlane(nullptr) {
        cout << name << " with certificate number " << this << " is at the gate, ready to board the plane." << endl;
    }

    // Destructor
    ~Pilot() {
        cout << name << " with certificate number " << this << " is out of the plane." << endl;
    }

    // Get function for name
    string getName() const {
        return name;
    }

    // Pointer to Plane object
    Plane* myPlane;
};

int main() {
    Pilot pilot1("Pilot-in-Command");
    Pilot pilot2("Co-Pilot");
    
    map<string, Flight_Information> flights;
    flights["SCE-PHL"] = {"SCE", "PHL", 160};
    flights["SCE-ORD"] = {"SCE", "ORD", 640};
    flights["SCE-EWR"] = {"SCE", "EWR", 220};

    Plane myPlane("SCE", "PHL", flights);

    // Input for flight speed
    string input;
    double velocity;
    cout << "Enter the flight speed between 400-500 mph (Press Enter to default: 450): ";
    getline(cin, input);
    if (input.empty()) {
        velocity = 450.0; 
    } else {
        stringstream(input) >> velocity;
    }
    myPlane.setVel(velocity);

    // Input for timestep
    double dt;
    cout << "Enter the timestep between [10,100] seconds (Press Enter to default: 15): ";
    getline(cin, input);
    if (input.empty()) {
        dt = 15; 
    } else {
        stringstream(input) >> dt;
    }
    
    // Input for maximum number of iterations
    int max_iterations;
    cout << "Enter the maximum number of iterations between [1000,2000] (Press Enter to default: 1500): ";
    getline(cin, input);
    if (input.empty()) {
        max_iterations = 1500;  
    } else {
        stringstream(input) >> max_iterations;
    }

    // Assign the plane to the first pilot initially
    pilot1.myPlane = &myPlane;
    
    cout << pilot1.getName() << " with certificate number " << &pilot1 << " is in control of a plane: " << pilot1.myPlane << endl;
    cout << pilot2.getName() << " with certificate number " << &pilot2 << " is in control of a plane: " << pilot2.myPlane << endl;
    cout << " " << endl;

    for (int i = 0; i < max_iterations; i++) {

        // Simulate SCE to PHL
        while (!myPlane.hasArrived()) {
            myPlane.operate(dt); 
        }

        // Output when SCE to PHL has been completed
        cout << "Navigation from " << myPlane.getOrigin() << " to " << myPlane.getDestination() << " has been completed. On to the next leg!" << endl;

        // Reset the plane position and swap the route
        myPlane.resetPosition();
        myPlane.swapRoute();

        // Simulate PHL to SCE
        while (!myPlane.hasArrived()) {
            myPlane.operate(dt);  
        }

        // Output when PHL to SCE has been completed
        cout << "Navigation from " << myPlane.getOrigin() << " to " << myPlane.getDestination() << " has been completed. On to the next leg!" << endl;

        // Check if the plane has landed at SCE
        myPlane.checkAtSCE();
        if (myPlane.getAtSCE()) {
            cout << "The plane " << &myPlane << " is at SCE" << endl;
        }

        // Reset the plane for the next flight (starts from SCE)
        myPlane.resetPosition();
        if (!myPlane.getAtSCE()) {
            myPlane.swapRoute(); 
        }

        // Swap control between the two pilots
        swap(pilot1.myPlane, pilot2.myPlane);

        // Print after swapping
        cout << pilot1.getName() << " with certificate number " << &pilot1 << " is in control of a plane: " << pilot1.myPlane << endl;
        cout << pilot2.getName() << " with certificate number " << &pilot2 << " is in control of a plane: " << pilot2.myPlane << endl;
        cout << " " << endl;
    }

    return 0;
}
