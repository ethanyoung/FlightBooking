#include "Flight.h"

Flight::Flight (string i, string a, double f, double d, Airport * depart, Airport * arriv, Date *date, string time) {
	id = i;
	airline = a;
	price = f;
	duration = d;
	departure = depart;
	arrival  =arriv;
	this->date = date;
	this->time = time;
}
string Flight::getID() { return id; }
double Flight::getPrice(){return price;}
double Flight::getDuration(){return duration;}
Date * Flight::getDate(){return date;}

Airport * Flight::getDep(){
	return departure;
}

Airport * Flight::getArr(){
	return arrival;
}

string Flight::getAirline(){return airline;}
string Flight::getTime(){return time;}
