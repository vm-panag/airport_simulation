#ifndef AIRPORT_CLASS_H
#define AIRPORT_CLASS_H

#include "Application_class.h"
#include "Flight_class.h"
#include <string>
#include <ctime>
#include <vector>
#include <list>

using namespace std;

class Airport{
	
	time_t currTime;
	Flight** terminals;
	time_t* timeOrder;
	time_t moveTime;
	const int numberOfTerminals;
	static unsigned terminalCounter;
	list <Application> waitingList;	
	list<Application> Passengers;
	vector<Application> failedApps;
	
	public:
		
		Airport(time_t curTT = 0, Flight** term = NULL, time_t* timeO = NULL, const int numOfTerm = 5, time_t moveT = 0);
		~Airport();
		
		void set(string, time_t, time_t, int, int);
		time_t get_time();
		void add_application(int, string, string, string, time_t, time_t, int);
		void cancel_applications(int);
		int add_flight(string, time_t, time_t, int, int);
		void cancel_flight(int);
		int failed_applications();
		void show_timetable();		
		void show_people_waiting();
		void flow_time(time_t);
};
#endif
