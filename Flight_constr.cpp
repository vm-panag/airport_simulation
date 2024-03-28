#include <iostream>
#include "Application_class.h"
#include "Flight_class.h"
#include <string>
#include <ctime>
#include <vector>
#include <list>

using namespace std;	
//Constructor of the class
Flight::Flight(string fDest, time_t deptT, time_t dur, int maxA, int maxB, int seatsRA, int seatsRB):
destination(fDest), deptTime(deptT), duration(dur), maxCapA(maxA), maxCapB(maxB), seatsReservedA(seatsRA), seatsReservedB(seatsRB) {
	
		//cout << "A flight was created" << endl;
}	
//Function that sets flight's information
void Flight::set_flight(string dest, time_t deptT, time_t dur, int maxA, int maxB) {	
	
	destination = dest;
	deptTime = deptT;
	duration = dur;
	maxCapA = maxA;
	maxCapB = maxB;	
}
//Function that adds a passenger to a flight	
void Flight::add_passenger(Application app) {	
	
	if(app.matches(this) == 1) {	//If passenger's application matches to a flight and he preferes an A class seat
		
		if(app.is_luxury_class() == 1) {
		
			if(seatsReservedA < maxCapA) {	//If there are available seats in class A
				flightApps.push_back(app);	//Add passenger to flight	
				seatsReservedA++;	//Raise the counter for seats reserved in class A								
			}
		}

		else if(app.is_luxury_class() == 0) {	//If passenger's application matches to a flight and he preferes an A class seat
		
			if(seatsReservedB < maxCapB) {	//If there are available seats in class A
				flightApps.push_back(app);	//Add passenger to flight
				seatsReservedB++;			//Raise the counter for seats reserved in class B
			}
		}
	}
}
//Function that returns flight's departure time
time_t Flight::departs_at()const {				
	
	return deptTime;
}
//Function that returns flight's arrival time
time_t Flight::arrives_at()const {				
	
	return deptTime+duration;
}
//Function that returns flight's destination
string Flight::get_destination()const {			
	
	return destination;
}
//Function that returns flight's duration
time_t Flight::get_duration()const {				
	
	return duration;
}
//Function that returns flight's max capacity for class A
int Flight::get_maxA()const {					
	
	return maxCapA;
}
//Function that returns flight's max capacity for class B
int Flight::get_maxB()const {					
	
	return maxCapB;
}
//Function that returns flight's seats reserved for class A
int Flight::get_seatsReservedA()const {			
	
	return seatsReservedA;
}
//Function that returns flight's seats reserved for class B
int Flight::get_seatsReservedB()const {			
	
	return seatsReservedB;
}
//Function that returns flight's total seats available
int Flight::get_available()const {				
	
	int maxA = this->get_maxA();
	int maxB = this->get_maxB();
	int seatsA = this->get_seatsReservedA();
	int seatsB = this->get_seatsReservedB();
	
	int freeSeats = (maxA - seatsA) + (maxB - seatsB);
	
	return freeSeats;	
}  
//Function that erases a passenger from a flight given an id
void Flight::cancel_reservations(int cancelR) { 
	
	for(list<Application>::iterator it = flightApps.begin(); it != flightApps.end(); ++it) {
			
		if(it->get_id() == cancelR) {	//If passenger's id matches the given id
			
			if((it->is_luxury_class()) == 1 && this->get_seatsReservedA() > 0)	//If passenger owns an A class seat and class A isn't empty 
				seatsReservedA--;												//Reduce class' A seats counter
			else if((it->is_luxury_class()) == 0 && this->get_seatsReservedB() > 0)	//If passenger owns an B class seat and class B isn't empty
				seatsReservedB--;													//Reduce class' B seats counter
					
			it=flightApps.erase(it);	//Remove passenger from the flight
		}
	}
}
//Function that returns all flight's applications in a vector
const list<Application>& Flight::get_bookings()const {		
		
	return flightApps;		 
}
//Destructor of the class
Flight::~Flight() {		
	
	//cout << "A flight was terminated" << endl;	
}