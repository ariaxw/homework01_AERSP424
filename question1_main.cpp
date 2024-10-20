/******************************************************************************

This code is for the Question 1 in the Homework 1 of AERSP 424

Author: Xue (Aria) Wang

*******************************************************************************/

#include <iostream>
#include <iomanip> // for setting decimal precision
using namespace std;

#define ENABLE_USER_INPUT 0 // a preprocessor directive, set to 0 for hard-coded values, set to 1 for user inputting values


int main() {
    
    //The first part: define all the variables. 
    
    // I chose the double because I would like to ensure the accuracy of algorithm (keeping the decimals).
    double Weight_empty_airplane, Moment_empty_airplane;
    double Weight_each_front1,Weight_each_front2, Distance_front_seat;
    double Weight_each_rear1, Weight_each_rear2, Distance_rear_seat;
    double Weight_per_gallon_fuel, Distance_fuel_tank, Weight_baggage, Distance_baggage;
    int Number_front_seat, Number_rear_seat, Number_gallons_fuel;
    
#if ENABLE_USER_INPUT
    //Receive information below from the user
    cout << "Enter the airplane empty weight (lbs): ";
    cin >> Weight_empty_airplane;
    cout << "Enter the airplane empty-weight moment (lbs-in): ";
    cin >> Moment_empty_airplane;
    cout << "Enter the number of front seat occupants: ";
    cin >> Number_front_seat;
    cout << "Enter the weight of the first front seat occupant (lbs): ";
    cin >> Weight_each_front1;
    cout << "Enter the weight of the second front seat occupant (lbs): ";
    cin >> Weight_each_front2;
    cout << "Enter the front seat moment arm (inches): ";
    cin >> Distance_front_seat;
    cout << "Enter the number of rear seat occupants: ";
    cin >> Number_rear_seat;
    cout << "Enter the weight of the first rear seat occupant (lbs): ";
    cin >> Weight_each_rear1;
    cout << "Enter the weight of the second rear seat occupant (lbs): ";
    cin >> Weight_each_rear2;
    cout << "Enter the rear seat moment arm (inches): ";
    cin >> Distance_rear_seat;
    cout << "Enter the number of gallons of usable fuel: ";
    cin >> Number_gallons_fuel;
    cout << "Enter the usable fuel weight per gallon (lbs): ";
    cin >> Weight_per_gallon_fuel;
    cout << "Enter the fuel tank moment arm (inches): ";
    cin >> Distance_fuel_tank;
    cout << "Enter the baggage weight (lbs): ";
    cin >> Weight_baggage;
    cout << "Enter the baggage moment arm (inches): ";
    cin >> Distance_baggage;
#else
    //input hard-coded values
    Weight_empty_airplane = 2050;
    Moment_empty_airplane = 155400;
    Number_front_seat = 2;
    Weight_each_front1 = 180;
    Weight_each_front2 = 150;
    Distance_front_seat = 85;
    Number_rear_seat = 2;
    Weight_each_rear1 = 160;
    Weight_each_rear2 = 170;
    Distance_rear_seat = 121;
    Number_gallons_fuel = 44;
    Weight_per_gallon_fuel = 6;
    Distance_fuel_tank = 75;
    Weight_baggage = 10;
    Distance_baggage = 140;
#endif
    
    //The Second part: calculation of all parameters
    
    //calculate the weights and amounts for fron/rear seat, fuel, baggage
    double Weight_front_seat = Weight_each_front1 + Weight_each_front2;
    double Weight_rear_seat = Weight_each_rear1 + Weight_each_rear2;
    double Weight_fuel = Number_gallons_fuel * Weight_per_gallon_fuel;
    double Moment_front_seat = Weight_front_seat * Distance_front_seat;
    double Moment_rear_seat = Weight_rear_seat * Distance_rear_seat;
    double Moment_fuel = Weight_fuel * Distance_fuel_tank;
    double Moment_baggage = Weight_baggage * Distance_baggage;
    
    // Calculate total gross weight and total moment
    double Gross_weight = Weight_empty_airplane + Weight_front_seat + Weight_rear_seat + Weight_fuel + Weight_baggage;
    double Total_moment = Moment_empty_airplane + Moment_front_seat + Moment_rear_seat + Moment_fuel + Moment_baggage;
    
    // Calculate the center of gravity (CG) location and then output
    double CG_location = Total_moment / Gross_weight;
    cout << "THE INITIAL PARAMETERS: " << endl;
    cout << " " << endl;
    cout << "[ Total moment (lbs-inches): " << Total_moment << " ]" << endl;
    cout << "[ Gross weight (lbs): " << Gross_weight << " ]" << endl;
    cout << "[ CG location (inches): " << CG_location << " ]" << endl;
    cout << "----------------------------------------------" << endl;
    
    //The third part: check if the gross weight and the CG location are within the airplane design limits 
    
    //define the variables of design limits
    double Max_gross_weight, Forward_CG_limit, Aft_CG_limit;
    Max_gross_weight = 2950;
    Forward_CG_limit = 82.1;
    Aft_CG_limit = 84.7;
    
    //conduct if operation: the case when gross weight exceed the maximum
    if (Gross_weight >= Max_gross_weight) {
        cout << "WARNING: THE GROSS WEIGHT IS TOO HEAVRY! EXCEEDS THE MAXIMUM LIMIT OF 2960LBS! --- PLEASE ADJUST!" << endl;
        cout << "----------------------------------------------" << endl;
    
    //In this case, check the CG location
    if ( CG_location < Forward_CG_limit ) {
        cout << "WARNING: THE CENTER OF GRAVITY LOCATION IS FORWARD OF THE LIMIT OF 82.1 INCHES! --- PLEASE ADJUST!" << endl;
        cout << "----------------------------------------------" << endl;
        
        //calculate the drained amount of fuel 
        double Drained_weight_fuel;
        for ( double Drained_weight_fuel = 0; Drained_weight_fuel += 0.05;) {
            
            // Calculate total weight and moment with the new fuel weight
            Gross_weight -= Drained_weight_fuel;
            Total_moment -= Drained_weight_fuel * Distance_fuel_tank;
            CG_location = Total_moment / Gross_weight;
            
            //check the CG location if within the limits
            if (CG_location >= Forward_CG_limit && CG_location <= Aft_CG_limit && Gross_weight <= Max_gross_weight ){
                break; //get out of this loop when satisfying the limits
            }
        }
        //output these values
        cout << "THE PARAMETWES AFTER ADJUSTING: " << endl;
        cout << " " << endl;
        cout << "[ The amount of fuel that need to be drained (lbs): " << Drained_weight_fuel << " ]" << endl;
        cout << "[ The new value of the gross weight (lbs): " << Gross_weight << " ]" << endl;
        cout << "[ The new value of the CG location (inches): " << CG_location << " ]" << endl;
        cout << "----------------------------------------------" << endl;
    }
    
    else if (CG_location > Aft_CG_limit) {
        cout << "WARNING: THE CENTER OF GRAVITY LOCATION IS AFT OF THE LIMIT OF 84.7 INCHES! --- PLEASE ADJUST!" << endl;
        cout << "----------------------------------------------" << endl;
        
        //calculate the drained amount of fuel 
       double Drained_weight_fuel;
        for (Drained_weight_fuel = 0; Drained_weight_fuel += 0.05;) {
            
            // Calculate total weight and moment with the new fuel weight
            Gross_weight -= Drained_weight_fuel;
            Total_moment -= Drained_weight_fuel * Distance_fuel_tank;
            CG_location = Total_moment / Gross_weight;
            
            //check the CG location if within the limits
            if (CG_location > Forward_CG_limit && CG_location < Aft_CG_limit && Gross_weight <= Max_gross_weight){
                break; //get out of this loop when satisfying the limits
            }        
        }
        //output these values
        cout << "THE PARAMETWES AFTER ADJUSTING: " << endl;
        cout << " " << endl;
        cout << "[ The amount of fuel that need to be drained (lbs): " << Drained_weight_fuel << " ]" << endl;
        cout << "[ The new value of the gross weight (lbs): " << Gross_weight << " ]" << endl;
        cout << "[ The new value of the CG location (inches): " << CG_location << " ]" << endl;
        cout << "----------------------------------------------" << endl;
    }
    
    else if (CG_location > Forward_CG_limit && CG_location < Aft_CG_limit) {
        cout << "THE CENTER OF GRAVITY LOCATION IS WITHIN THE LIMITS." << endl;
        cout << "----------------------------------------------" << endl;
        
        //calculate the drained amount of fuel 
       double Drained_weight_fuel;
        for (Drained_weight_fuel = 0; Drained_weight_fuel += 0.05;) {
            
            // Calculate total weight and moment with the new fuel weight
            Gross_weight -= Drained_weight_fuel;
            Total_moment -= Drained_weight_fuel * Distance_fuel_tank;
            CG_location = Total_moment / Gross_weight;
            
            //check the CG location if within the limits
            if (CG_location > Forward_CG_limit && CG_location < Aft_CG_limit && Gross_weight <= Max_gross_weight){
                break; //get out of this loop when satisfying the limits
            }        
        }
        //output these values
        cout << "THE PARAMETWES AFTER ADJUSTING: " << endl;
        cout << " " << endl;
        cout << "[ The amount of fuel that need to be drained (lbs): " << Drained_weight_fuel << " ]" << endl;
        cout << "[ The new value of the gross weight (lbs): " << Gross_weight << " ]" << endl;
        cout << "[ The new value of the CG location (inches): " << CG_location << " ]" << endl;
        cout << "----------------------------------------------" << endl;
    }
    }
    
    //conduct if operation: the case when gross weight less than the maximum
    else if ((Gross_weight < Max_gross_weight)) {
        cout << "THE GROSS WEIGHT IS WIHIN THE DESIGN LIMITS." << endl;
        cout << "----------------------------------------------" << endl;
    
    //In this case, check the CG location
    if ( CG_location < Forward_CG_limit ) {
        cout << "WARNING: THE CENTER OF GRAVITY LOCATION IS FORWARD OF THE LIMIT OF 82.1 INCHES! --- PLEASE ADJUST!" << endl;
        cout << "----------------------------------------------" << endl;
        
        //calculate the added amount of fuel 
        double Added_weight_fuel;
        for (Added_weight_fuel = 0; Added_weight_fuel <= Max_gross_weight - Gross_weight; Added_weight_fuel += 0.05) {
            
            // Calculate total weight and moment with the new fuel weight
            Gross_weight += Added_weight_fuel;
            Total_moment += Added_weight_fuel * Distance_fuel_tank;
            CG_location = Total_moment / Gross_weight;
            
            //check the CG location if within the limits
            if (CG_location >= Forward_CG_limit && CG_location <= Aft_CG_limit && Gross_weight <= Max_gross_weight ){
                break; //get out of this loop when satisfying the limits
            }
        }
        //output these values
        cout << "THE PARAMETWES AFTER ADJUSTING: " << endl;
        cout << " " << endl;
        cout << "[ The amount of fuel that need to be added (lbs): " << Added_weight_fuel << " ]" << endl;
        cout << "[ The new value of the gross weight (lbs): " << Gross_weight << " ]" << endl;
        cout << "[ The new value of the CG location (inches): " << CG_location << " ]" << endl;
        cout << "----------------------------------------------" << endl;
    }
    
   else if (CG_location > Aft_CG_limit) {
        cout << "WARNING: THE CENTER OF GRAVITY LOCATION IS AFT OF THE LIMIT OF 84.7 INCHES! --- PLEASE ADJUST!" << endl;
        cout << "----------------------------------------------" << endl;
        
        //calculate the added amount of fuel 
        double Added_weight_fuel;
        for (Added_weight_fuel = 0; Added_weight_fuel <= Max_gross_weight - Gross_weight; Added_weight_fuel += 0.05) {
            
            // Calculate total weight and moment with the new fuel weight
            Gross_weight += Added_weight_fuel;
            Total_moment += Added_weight_fuel * Distance_fuel_tank;
            CG_location = Total_moment / Gross_weight;
            
            //check the CG location if within the limits
            if (CG_location >= Forward_CG_limit && CG_location <= Aft_CG_limit && Gross_weight <= Max_gross_weight ){
                break;//get out of this loop when satisfying the limits
            }
        }
    
    //output these values
    cout << "THE PARAMETWES AFTER ADJUSTING: " << endl;
    cout << " " << endl;
    cout << "[ The amount of fuel that need to be added (lbs): " << Added_weight_fuel << " ]" << endl;
    cout << "[ The new value of the gross weight (lbs): " << Gross_weight << " ]" << endl;
    cout << "[ The new value of the CG location (inches): " << CG_location << " ]" << endl;
    cout << "----------------------------------------------" << endl;
    
    }
    
   else if (CG_location > Forward_CG_limit && CG_location < Aft_CG_limit) {
        cout << "THE CENTER OF GRAVITY LOCATION IS WITHIN THE LIMITS." << endl;
        cout << "----------------------------------------------" << endl;
        }
    }    
    
    //The forth part: check the adjusted parameter if satisfying the limits

    if (CG_location < Forward_CG_limit || CG_location > Aft_CG_limit || Gross_weight < 0 || Gross_weight >= Max_gross_weight) {
        cout << "CANNOT SATISFY THE LIMITS OF ALL PARAMETERS BASED ON THE INPUT VALUE." << endl;
        cout << "[ Maximum allowable gross weigh (lbs): " << Max_gross_weight << " ]" << endl;
        cout << "[ Forward C.G. limit (inches): " << Forward_CG_limit << " ]" << endl;
        cout << "[ Aft C.G. limit (inches): " << Aft_CG_limit << " ]" <<  endl;
        cout << " " << endl;
        cout << "PLEASE CHANG THE INPUTS!!" << endl;
        cout << "----------------------------------------------" << endl;
    }
    
    if (CG_location >= Forward_CG_limit && CG_location <= Aft_CG_limit && Gross_weight >0 && Gross_weight <= Max_gross_weight){
        cout << "NOW ALL THE PARAMETERS OF THE AIRPLANE ARE WIHIN THE DESIGN LIMITS" << endl;
        cout << "[ Maximum allowable gross weigh (lbs): " << Max_gross_weight << " ]" << endl;
        cout << "[ Forward C.G. limit (inches): " << Forward_CG_limit << " ]" << endl;
        cout << "[ Aft C.G. limit (inches): " << Aft_CG_limit << " ]" <<  endl;
        cout << " " << endl;
        cout << "AWOSOME!!" << endl;
        cout << "----------------------------------------------" << endl;
    }
}