# include <iostream>
# include <string>
# include <fstream>
# include <set>
# include <list>
# include <queue>
# include <sstream>
# include <stdlib.h>

#include "Ticket.h"
#include "Airport.h"

struct Airport_Flight
{
	list<Airport> airport_list;
	list<Flight> flight_list;

public:
	Airport *getAirport(string code) {

		for (auto p = this->airport_list.begin(); p!=this->airport_list.end();++p) {
			if((code.compare(p->getCode())) ==0) {
				return &(*p);
			}
		}

		return NULL;
	}
};

/**
* The major function of the prgramme. Find flights among the given data.
* Up to three connection flights, i.e. two stops.
*/
vector<Ticket> findFlight(Airport_Flight * data, string departure, string arrival, Date * date);

string convertMonth(int m);

bool readAirportFile (string filename, Airport_Flight *data) ;

bool readFlightFile (string filename, Airport_Flight *data) ;

void printReceipt(Ticket *ticket);

bool writeFile (string filename, Ticket *ticket) ;

void print (vector<Ticket> result);

void searchForFlight(Airport_Flight *data);