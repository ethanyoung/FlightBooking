#include "Ticket.h"

Ticket::Ticket (list<Flight> f, double fare, double d, string t, Date * date) {
	flight_list = f;
	this->fare = fare;
	duration = d;
	time = t;
	this->date = date;

}
	
list<Flight> Ticket::getFlightList(){return flight_list;}
string Ticket::getTime(){return time;}
double Ticket::getDuration(){return duration;}
double Ticket::getCost(){return fare;}
Date* Ticket::getDate(){return date;}
