#include <iostream>
#include "Application_class.h"
#include "Flight_class.h"
#include "Airport_class.h"
#include <string>
#include <ctime>
#include <vector>
#include <list>

using namespace std;
//Constructor of the class
Airport::Airport(time_t currT, Flight** term, time_t* timeO, const int numOfTerm, time_t moveT):
currTime(currT), terminals(term), timeOrder(timeO), numberOfTerminals(numOfTerm), moveTime(moveT) {
		
	terminals = new Flight*[numberOfTerminals]();	//Initialize NULL aray
	timeOrder = new time_t[numberOfTerminals]();	//Initialize NULL aray
	
	cout << "An airport was created" << endl;
}

unsigned Airport::terminalCounter = 0;	//Static variable set to 0 in order to count the terminals

void Airport::set(string dest, time_t deptT, time_t dur, int maxA, int maxB) {	//Function that sets a flight in a terminal

	if(terminalCounter < numberOfTerminals) {	
	
		if(terminals[terminalCounter] == NULL) {	//If terminal is empty add a new flight
			
			terminals[terminalCounter++] = new Flight(dest,deptT,dur,maxA,maxB);
		}
	}
}
//Function tha returns the current time
time_t Airport::get_time() {						
	
		return currTime;
}
//Function that takes an application's information and adds the application on the waiting list of the airport
//If there is a flight in the airport that matches to the application, then a passengers is directly added to the right flight
void Airport::add_application(int iD, string fname, string lname, string dest, time_t airT, time_t wantedA, int classT) {
	int i,j = 0;																
	int flag = 0;																
																			
	Application app(iD,fname,lname,dest,airT,wantedA,classT);
	
	for(i = 0; i < numberOfTerminals; i++) {	//Traverse through the terminals
		
		if((app.matches(terminals[i]) == 1)) {	//If an application matches to a flight
			//If there are available seats in the flight
			if((terminals[i]->get_seatsReservedA() < terminals[i]->get_maxA()) && (terminals[i]->get_seatsReservedB() < terminals[i]->get_maxB())){
					
				terminals[i]->add_passenger(app);	//Add passenger to the flight
				flag++;
				break;
			}
		}
	}
		
	if(flag < 1) {	//If the application doesn't match to any flight, add it in airport's waiting list								
		
		waitingList.push_back(app);
	}
}
//Function that cancels reserved seats in any flight of the airport 
//and removes applications from airport's waiting list, given a passenger's id
void Airport::cancel_applications(int cancelA) { 	
	
	for(list<Application>::iterator it = waitingList.begin(); it != waitingList.end(); ++it){	//Traverse through airport's waiting list
			
		if((it->get_id())==cancelA)		//If there is an application's id that matches to the given id
			it=waitingList.erase(it);	//remove the application from the waiting list
    }
	
	for(int i = 0; i < numberOfTerminals; i++) {	//Traverse through airport's terminals
			
		if(terminals[i] != NULL)						//If a flight departs through the current terminal
			terminals[i]->cancel_reservations(cancelA);	//and there are reserved seats by the given id, then cancel the seats' reservations
	}
}
//Function that takes the information of a flight and returns  the number that represents the flight's termimal
int Airport::add_flight(string dest, time_t deptT, time_t dur, int maxA, int maxB){	
	Flight f(dest,deptT,dur,maxA,maxB);
	
	int i,terminal,tMaxA,fMaxA,tMaxB,fMaxB;
	time_t tDeptT,fDeptT,tDur,fDur;
	string tDest,fDest;
	
	for(i = 0; i < numberOfTerminals; i++) {	//Traverse through the terminals
		
		tDest = terminals[i]->get_destination();	//Get actual flight's destination
		fDest = f.get_destination();	//Get wanted flight's destination
		
		tDeptT = terminals[i]->departs_at();	//Get actual flight's departure time
		fDeptT = f.departs_at();	//Get wanted flight's departure time
		
		tDur = terminals[i]->get_duration();	//Get actual flight's duration
		fDur = f.get_duration();	//Get wanted flight's duration
		
		tMaxA = terminals[i]->get_maxA();	//Get actual flight's class' A capacity
		fMaxA = f.get_maxA();		//Get wanted flight's class' A capacity
		
		tMaxB = terminals[i]->get_maxB();	//Get actual flight's class' B capacity
		fMaxB = f.get_maxB();	//Get wanted flight's class' B capacity
	
		
		if((tDest == fDest) && (tDeptT == fDeptT) && (tDur == fDur) && (tMaxA == fMaxA) && (tMaxB == fMaxB)) {
			//If the above match
			//Return flight's terminal ( Consider terminal No 1 , as the first terminal)
		 	terminal = i + 1;							
			break;
		}
		
		else 

			terminal = 0;	//Else return 0, meaning that the flight wasn't found												
	}
	
	return terminal;
}

void Airport::cancel_flight(int term) {		//Function that takes a terminal's number and cancels the flight that departs through the terminal
	list<Application> canceledApps;		//Vector that stores the applications of the canceled flight

	for(int i = 0; i < numberOfTerminals; i++) {	//Traverse through the terminals
		
		if(i == term - 1) {
			
			canceledApps=terminals[i]->get_bookings();	//Store the applications of the current flight
			delete terminals[i];						//Delete the flight
			
			terminals[i] = NULL;							//Terminal is now empty
			terminals[i] = new Flight;					//Terminal is ready to accept a new Flight
			break;
		}
	}	
														//Traverse through canceled flight's applications
	for (list<Application>::iterator it = canceledApps.begin(); it != canceledApps.end(); ++it) {
    													
    		waitingList.push_front(*it);				//Add these applications to the airport's waiting list
	}					
}

void Airport::show_timetable() {	//Function that prints an airport's timetable	
	int i,j;
	time_t temp;

	for(i = 0; i < numberOfTerminals; i++) {	//Store the departure time of each flight in a vector
 	
		timeOrder[i]=terminals[i]->departs_at();			
	}

	for(i = 0; i < numberOfTerminals; i++) {	//Sort the above vector from minimum to maximum element
	 	
		for(j = 0; j < numberOfTerminals; j++) {
		 
			 if(timeOrder[j] > timeOrder[j+1]) {
			 	
				 temp=timeOrder[j];
				 timeOrder[j] = timeOrder[j+1];
				 timeOrder[j+1] = temp;
			 }
		 }
	}
		 
	 for(i = 0; i < numberOfTerminals; i++) {	//Print flight's information starting with the flight with the smallest departure time
		
		for(j = 0; j < numberOfTerminals; j++) {

			if(timeOrder[i] == terminals[j]->departs_at() && (timeOrder[i+1] !=timeOrder[j])) {	
				
				cout << "   * Flight No: " << i+1 <<" *" << endl;
				cout << "Destination: " << terminals[j]->get_destination() << endl;
				cout << "Departure Time: " << terminals[j]->departs_at() << endl;
				cout << "Duration: " << terminals[j]->get_duration() << endl;
				cout << "Max Capacity for class A: " << terminals[j]->get_maxA() << endl;
				cout << "Max Capacity for class B: " << terminals[j]->get_maxB() << endl << endl;
				break;	
			}	
		}
	}
}
//Function that prints the names of people whose applications are still in the waiting list
void Airport::show_people_waiting() {		
	
	cout << "People's names in the waiting list are:" << endl << endl;
	
	for (list<Application>::iterator it=waitingList.begin(); it != waitingList.end(); ++it) {
		
		cout << it->get_name() << endl;
	}
	
	cout << endl;
}
//Function that return the number of applications of the waiting list that got deleted	due to flow_time function
int Airport::failed_applications() {			
	int failed = failedApps.size();
	
		return failed;	
}
//Function that takes a time period and moves the time instantly
void Airport::flow_time(time_t moveT) {		
	int i,j;
	time_t now = get_time();
	
	for(i = 0; i < numberOfTerminals; i++) {	//Traverse through the terminals
	 	
	 	if((now <= timeOrder[i]) && (timeOrder[i] <= (now + moveT))) { //If a flight's departure is programmed during the given time period
	 		
			for(j = 0; j < numberOfTerminals; j++) {
				
				if(timeOrder[i] == terminals[j]->departs_at() && (timeOrder[i+1] != timeOrder[j])) {	//Print the flight destination in time order
					
					cout<< "*** Flight to " << terminals[j]->get_destination() <<" departed at "<< terminals[j]->departs_at() <<" units of time***" <<endl << endl;
					
					Passengers=terminals[j]->get_bookings();
																				
					cout << "People who boarded in the fligh are:" << endl << endl;	//Print the passengers of the flight							
													
					for(list<Application>::iterator it = Passengers.begin(); it != Passengers.end(); ++it)
							cout << it->get_name() << endl;
						
						for(list<Application>::iterator itt = waitingList.begin(); itt != waitingList.end(); ++itt) {
							
							if((itt->matches(terminals[j])) == 1) {
								
								failedApps.push_back(*itt);	//Remove unsatisfied applications from the waiting list
								itt = waitingList.erase(itt);
							}
						}
						
					delete terminals[j];	//Terminal is now empty due to flight's departure
					terminals[j] = NULL;
					terminals[j] = new Flight;	//Terminal is ready to accept a new flight
					
					break;		
				}
			}
				cout << endl;
		}
	}
}
//Destructor of the class
Airport::~Airport() {		
	
	for(int i = 0; i < numberOfTerminals; i++)
  		delete terminals[i];
	
	delete[] terminals;	//Free dynamically allocated memories
	delete[] timeOrder;
		
	cout << "An airport was destroyed" << endl;
}
