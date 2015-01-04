#include "Airport.h"
#include "Flight.h"

Airport::Airport (string c, string n, double fare, double time) {
	code = c;
	name = n;
	depart_tax = fare;
	connection_time = time;
}

void Airport::addFlight (Flight *f) {
	flight_list.push_back(*f);
}

string Airport::getCode() {
	return code;
}

list<Flight> Airport::getFlightSet() {
	return flight_list;
}
double Airport::getDepartTax(){
	return depart_tax;
}

double Airport::getConnectionTime(){
	return connection_time;
}