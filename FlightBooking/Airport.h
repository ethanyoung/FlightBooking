#include <string>
#include <list>

using namespace std;

class Flight;
class Airport
{
	string code;
	string name;
	double depart_tax;
	double connection_time;
	list<Flight> flight_list;

public:
		Airport (string c, string n, double fare, double time);
		void addFlight (Flight *f);
		string getCode();
		list<Flight> getFlightSet();
		double getDepartTax();
		double getConnectionTime();
};