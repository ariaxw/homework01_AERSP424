/******************************************************************************

This code is for the Question 2 in the Homework 1 of AERSP 424

Author: Xue (Aria) Wang

*******************************************************************************/

#include <iostream>
#include <map>
#include <string>
using namespace std;

// Use a single container (struct) to store flight information between airports
struct Flight_Information {
    string origin;
    string destination;
    int distance;
};

int main() {
    
    // Use a map to map airport paris and distances
    map<string, Flight_Information> flights;
    
    // Add flights from SCE to other airports
    flights["SCE-PHL"] = {"SCE", "PHL", 160};
    flights["SCE-ORD"] = {"SCE", "ORD", 640};
    flights["SCE-EWR"] = {"SCE", "EWR", 220};
    
    // Print outputs
    for (const pair<const string, Flight_Information>& flight : flights) {
        cout << "Flight from " << flight.second.origin
             << " to " << flight.second.destination 
             << " is " << flight.second.distance << " miles." << endl;
    }
    return 0;
}
