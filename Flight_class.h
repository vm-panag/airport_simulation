#ifndef FLIGHT_CLASS_H
#define FLIGHT_CLASS_H

#include "Application_class.h"
#include <string>
#include <ctime>
#include <vector>
#include <list>

using namespace std;

class Application;

class Flight {
	
	string destination;
	time_t deptTime;
	time_t duration;
	int maxCapA;
	int maxCapB;
	int seatsReservedA;
	int seatsReservedB;
	list<Application> flightApps;
	
	public:
		
		Flight(string fDest = "", time_t deptT = 0, time_t dur = 0, int maxA = 0, int maxB = 0, int seatsRA = 0, int seatsRB = 0);
		~Flight();
		
		void set_flight(string, time_t, time_t, int, int);
		void add_passenger(Application app);
		void cancel_reservations(int);
		time_t departs_at()const;
		time_t arrives_at()const;
		string get_destination()const;
		int get_maxA()const;
		int get_maxB()const;
		int get_seatsReservedA()const;
		int get_seatsReservedB()const;
		time_t get_duration()const;
		int get_available()const;
		const list<Application>& get_bookings()const;
};
#endif
