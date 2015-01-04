#include <string>
#include <list>
using namespace std;

class Airport;

struct Date {
	int day;
	int month;
	int year;

public:
	Date(int d, int m, int y){
	day = d;
	month = m;
	year = y;
	}

	bool operator!= (const Date &d) const{
		return (day != d.day || month != d.month || year != d.year);
	}
};

class Flight
{
	string id;
	string airline;
	double price;
	double duration;
	string time;
	Date *date;
	Airport * departure;
	Airport * arrival;
	
public:
	Flight (string i, string a, double f, double d, Airport * depart, Airport * arriv, Date *date, string time);
	string getID();
	double getPrice();
	double getDuration();
	Date * getDate();

	Airport * getDep();

	Airport * getArr();

	string getAirline();
	string getTime();
	
};

