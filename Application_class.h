#ifndef APPLICATION_CLASS_H
#define APPLICATION_CLASS_H

#include "Flight_class.h"
#include <string>
#include <ctime>
#include <vector>

using namespace std;

class Application {
	
	int id;		
	string fName;
	string lName;
	string destination;
	time_t airportTime;
	time_t wantedArrival;
	bool classType;
	
	public:
		
		Application(int iD = 0, string fname = "", string lname = "", string dest = "", time_t airTime = 0, time_t wantedArr = 0, bool classT = 0);
		~Application();
		
		bool matches(Flight*);
		bool is_luxury_class();
		string get_name()const;
		int get_id()const;
		time_t airport_arrival()const;
		time_t arrived_by()const;
		string get_destination()const;	
};

#endif
