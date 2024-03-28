#include <iostream>
#include "Application_class.h"
#include "Flight_class.h"
#include "Airport_class.h"
#include <string>
#include <ctime>
#include <vector>
#include <list>
#include <fstream>
#include <cstdlib>

using namespace std;

int main(int argc, char* argv[]) {

	int i,id,classT,maxA,maxB;
	string fname,lname,dest,des;
	time_t airTime,wantedArr,moveT,dep,dur;
	
	if(argc > 1)
		moveT = atoi(argv[1]);	//Move time argument		
	
	Airport airport(20);	//create airport
	//Airport airport(26);
	
	ifstream fl("flight.txt");	//Get flights
	
	while(fl >> dest >> dep >> dur >> maxA >> maxB) {
		
		airport.set(dest,dep,dur,maxA,maxB);	//Set the flights in the terminals		
	}
	
	fl.close();
	
	ifstream ap("app.txt");		//Get applications
	
	while(ap >> id >> fname >> lname >> dest >> airTime >> wantedArr >> classT) {
	
		airport.add_application(id,fname,lname,dest,airTime,wantedArr,classT); //Add applications to the airport
	}
	
	ap.close();
	
	int ter = airport.add_flight("Paris",25,10,3,5);		//Find the terminal of flight to Paris
	cout << endl <<"Flight to Paris is in terminal " << ter << endl << endl;
	
	airport.cancel_flight(ter);			//Cancel flight to Paris
	cout << "Flight to Paris was just canceled." << endl << endl;		
	
	cout << "***Flights' timetable***" << endl << endl; 
	airport.show_timetable();	//Print airport's timetable
	
	airport.show_people_waiting();	//Print people's names in the waiting list
	
	airport.cancel_applications(105);	//Remove application with id 105
	airport.cancel_applications(107);	//Remove application with id 107
	airport.cancel_applications(110);	//Remove application with id 110
	airport.cancel_applications(112);	//Remove application with id 112

	airport.show_people_waiting();	//Print people's names in the waiting list
	
	cout << "While moving the time..." << endl << endl;
	airport.flow_time(moveT);	//Operate flow_time function
	
	cout << "***Flights' timetable***" << endl << endl;
	airport.show_timetable();	//Print airport's timetable
	
	cout << endl << "People's names still in the waiting list are:" << endl <<endl;
	airport.show_people_waiting();	//Print people's names in the waiting list
	
	cout << "The number of failed Applications is " << airport.failed_applications() << endl;	//Print the number of failed application
}