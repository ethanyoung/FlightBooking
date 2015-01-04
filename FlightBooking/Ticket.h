#include "Flight.h"

class Ticket {
	list<Flight> flight_list;
	double fare;
	double duration;
	string time;
	Date *date;

public:
	Ticket (list<Flight> f, double fare, double d, string t, Date * date);
	list<Flight> getFlightList();
	string getTime();
	double getDuration();
	double getCost();
	Date *getDate();

};