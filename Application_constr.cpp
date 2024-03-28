#include <iostream>
#include "Application_class.h"
#include "Flight_class.h"
#include <string>
#include <ctime>

using namespace std;
//Constructor of the class
Application::Application(int iD, string fname, string lname, string dest, time_t airTime, time_t wantedArr, bool classT):
id(iD), fName(fname), lName(lname), destination(dest), airportTime(airTime), wantedArrival(wantedArr), classType(classT) {
	
	//cout << "I just created an application" << endl;	
}
//Function to check if an application matches to any available flights
bool Application::matches(Flight* f) {	
	
	string des = f->get_destination();	//Flight's destination
	
	time_t airT = this->airport_arrival();	//Passenger will be at the airport at this time
	time_t depT = f->departs_at();	//Flight will depart at this time
	
	time_t wantedA = this->arrived_by();	//Passenger wants to arrive to his destination by this time
	time_t arrT = f->arrives_at();	//Flight arrives to it's destination at this time
	
	if(des == destination && airT <= depT && arrT <= wantedA) {	
		
		return 1;	//Function returns 1 if application matches to a flight
	}

	else
		
		return 0;	//Otherwise it returns 0
}
//Function that returns passenger's id
int Application::get_id()const {	
	
	return id;
}
//Function that returns passenger's full name
string Application::get_name()const {	
	
	string blank=" ";
	
	return fName+blank+lName;
}
//Function that returns passenger's arrival time at the airport
time_t Application::airport_arrival()const {	
		
	return airportTime;
}
//Function that returns passenger's wanted arrival to his destination
time_t Application::arrived_by()const {	
	
	return wantedArrival;
}
//Function that returns passenger's class preference
bool Application::is_luxury_class() {	
	
	return classType;	//Returns 1 for class A , 0 for class B	
}
//Function that returns passenger's destination
string Application::get_destination()const {	

	return destination;
}
//Destructor of the class
Application::~Application() {	
	
	//cout << "An application was destroyed" << endl;
}
