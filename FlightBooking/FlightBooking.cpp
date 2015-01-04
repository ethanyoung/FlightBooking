#include "FlightBooking.h"

vector<Ticket> findFlight(Airport_Flight * data, string departure, string arrival, Date * date)
{
	vector<Ticket> tickets;

	Airport *depart = data->getAirport(departure);
	Airport *arr = data->getAirport(arrival);

	//Chech for null pointer
	if (depart == NULL) {
		cout<<"The Departure Airport \""+departure+"\" not found in the data."<<endl;
		return tickets;
	}
	if (arr == NULL) {
		cout<<"The Arrival Airport \""+arrival+"\" not found in the data."<<endl;
		return tickets;
	}

	list<Flight> flights = depart->getFlightSet();
	
	bool flag0= false;

	// Search for direct connection.
	for (auto p = flights.begin(); p!=flights.end();++p){

		if (*(p->getDate()) != *date ) {
			continue;
		}
		
		string time = p->getTime();
		Date * date = p->getDate();

		double fare = p->getPrice()+depart->getDepartTax();
		double duration = p->getDuration();


		Airport * first_stop = p->getArr();

		if(p->getDate() == date && (first_stop->getCode().compare(arrival))==0 ) {

			list<Flight> result;
			
			result.clear();
			result.push_back(*p);

			Ticket *ticket = new Ticket(result, fare, duration,time, date);
			
			tickets.push_back(*ticket);

			flag0 = true;
		}
		
		// Attempt the first level.
		else {

			// Do not go to next level if there is result in this level.
			if (flag0 == true) {
				continue;
			}

			
			// Search for one-stop connection.
			list<Flight> first_stop_flights = first_stop->getFlightSet();

			bool flag1 = false;


			for (auto p1 = first_stop_flights.begin(); p1!=first_stop_flights.end();++p1){
				Airport * second_stop = p1->getArr();
				if ((second_stop->getCode().compare(departure))==0) {
					continue;
				}

				double fare1 = fare+p1->getPrice()+first_stop->getDepartTax();
				double duration1 = duration+p1->getDuration()+first_stop->getConnectionTime();

				if((second_stop->getCode().compare(arrival))==0) {
					list<Flight> result;
					result.clear();
					result.push_back(*p);
					result.push_back(*p1);

					Ticket *ticket = new Ticket(result, fare1, duration1,time, date);
					
					tickets.push_back(*ticket);

					flag1 = true;
				}
				
				// Attempt the second level.
				else {

					// Do not go to next level if there is result in this level.
					if (flag1 == true) {
						continue;
					}

					// Search for two-stop connection. 
					list<Flight> second_stop_flights = second_stop->getFlightSet();

					for (auto p2 = second_stop_flights.begin(); p2!=second_stop_flights.end();++p2){
						Airport * last_stop = p2->getArr();
						
						double fare2 = fare1+second_stop->getDepartTax()+p2->getPrice();
						double duration2 = duration1+second_stop->getConnectionTime()+p2->getDuration();

						if((last_stop->getCode().compare(arrival))==0) {
							list<Flight> result;
							result.clear();
							result.push_back(*p);
							result.push_back(*p1);
							result.push_back(*p2);

							Ticket *ticket = new Ticket(result, fare2, duration2,time, date);
							tickets.push_back(*ticket);

						}
					}
				}
			}
		}

	}

	return tickets;
}

string convertMonth(int m){
	switch(m) {
	case 1:
		return "Jan";
	case 2:
		return "Feb";
	case 3:
		return "Mar";
	case 4:
		return "Apr";
	case 5:
		return "May";
	case 6:
		return "Jun";
	case 7:
		return "Jul";
	case 8:
		return "Aug";
	case 9:
		return "Sep";
	case 10:
		return "Oct";
	case 11:
		return "Nov";
	case 12:
		return "Dec";
	default:
		return NULL;
	}
}

bool readAirportFile (string filename, Airport_Flight *data) 
{
	ifstream reader;
	reader.open(filename);
	string line;

	if (reader.is_open()) {
		while (reader.good()) {
			getline (reader, line);
			
			stringstream ss(line);
			string token;
			getline (ss, token, '\t');
			string code = token;
			getline (ss, token, '\t');
			string name = token;
			getline (ss, token, '\t');
			double tax = atof(token.c_str());
			getline (ss, token, '\t');
			double time = atof(token.c_str());

			//cout << code << name << tax << time<< endl;

			Airport *airport = new Airport(code, name, tax, time);

			data->airport_list.push_back(*airport);
			
		}
		reader.close();
		cout<<"read airport file successful! airport size: "<<data->airport_list.size()<<endl;
		return true;
	}
	
	else {
		cout << "Cannot open file \"filename\"" << endl;
		return false;
	}
}

bool readFlightFile (string filename, Airport_Flight *data) 
{
	ifstream reader;
	reader.open(filename);
	string line;

	if (reader.is_open()) {
		while (reader.good()) {
			getline (reader, line);
			
			stringstream ss(line);
			string token;
			getline (ss, token, '\t');
			string No = token;
			getline (ss, token, '\t');
			string airline = token;
			getline (ss, token, '\t');
			double price = atof(token.c_str());
			getline (ss, token, '\t');
			double duration = atof(token.c_str());
			getline (ss, token, '\t');
			Airport* departure = data->getAirport(token);
			getline (ss, token, '\t');
			Airport* arrival = data->getAirport(token);
			getline (ss, token, '\t');
			int day = atoi(token.c_str());
			getline (ss, token, '\t');
			int month = atoi(token.c_str());
			getline (ss, token, '\t');
			int year = atoi(token.c_str());
			getline (ss, token, '\t');
			string time = token;

			//cout << No << airline << price << duration<<departure->getCode()<<arrival->getCode()<< endl;

			Flight *flight = new Flight(No, airline, price, duration, departure, arrival, new Date(day, month, year), time);

			data->flight_list.push_back(*flight);

			departure->addFlight(flight);
			
		}
		reader.close();
		cout<<"read flight file successful! flight size: "<<data->flight_list.size()<<endl;
		return true;
	}
	
	else {
		cout << "Cannot open file \"filename\"" << endl;
		return false;
	}
}

void printReceipt(Ticket *ticket) {
	list<Flight> flights = ticket->getFlightList();
	cout<<"Booking successful! Your receipt is below:"<<endl;
	cout<<"--------------------------------------------"<<endl;
	cout<<"FROM: "<<flights.front().getDep()->getCode()<<"\tTO: "<<flights.back().getArr()->getCode()<<endl;
	cout<<"Departure Time:"<<ticket->getTime()<<"\tDate:"<<ticket->getDate()->day<<" "<<convertMonth(ticket->getDate()->month)<<" "<<ticket->getDate()->year<<endl;
	cout<<"Total Cost(include departure tax):"<<ticket->getCost()<<endl;
	cout<<"--------------------------------------------"<<endl;
	cout<<"NO.\tAIRLINE\tTIME\tPRICE\tFROM\tTO"<<endl;
	cout<<"--------------------------------------------"<<endl;
	for (auto j = flights.begin(); j!= flights.end(); ++j) {
		cout<<j->getID()+'\t'+j->getAirline()+"\t"<<j->getTime()<<'\t'<<j->getPrice()<<'\t'<<j->getDep()->getCode()<<'\t'<<j->getArr()->getCode()<<endl;
	}
	cout<<"--------------------------------------------"<<endl;
		
}

bool writeFile (string filename, Ticket *ticket) 
{
	ofstream writer (filename);

	if (writer.is_open()) {
		list<Flight> flights = ticket->getFlightList();

		writer<<"--------------------------------------------"<<endl;
		writer<<"FROM: "<<flights.front().getDep()->getCode()<<"\tTO: "<<flights.back().getArr()->getCode()<<endl;
		writer<<"Departure Time:"<<ticket->getTime()<<"\tDate:"<<ticket->getDate()->day<<" "<<convertMonth(ticket->getDate()->month)<<" "<<ticket->getDate()->year<<endl;
		writer<<"Total Cost(include departure tax):"<<ticket->getCost()<<endl;
		
		writer<<"--------------------------------------------"<<endl;
		writer<<"NO.\tAIRLINE\tTIME\tPRICE\tFROM\tTO"<<endl;
		writer<<"--------------------------------------------"<<endl;
		for (auto j = flights.begin(); j!= flights.end(); ++j) {
			writer<<j->getID()+'\t'+j->getAirline()+"\t"<<j->getTime()<<'\t'<<j->getPrice()<<'\t'<<j->getDep()->getCode()<<'\t'<<j->getArr()->getCode()<<endl;
		}
		writer<<"--------------------------------------------"<<endl;
		
		writer.close();

		cout<<"Your receipt has been saved in the file \""+filename+"\"."<<endl;
		return true;
	}
	
	else {
		return false;
		cout << "Cannot open file \""+filename+"\"" << endl;
	}
}

void print (vector<Ticket> result) {
	cout<< result.size()<<" tickets available."<<endl;
	int index=1;
	for (auto i = result.begin(); i!= result.end(); ++i) {
		list<Flight> flights = i->getFlightList();
		cout<<"--------------------------------------------"<<endl;
		cout<<"#"<<index<<"\tStart Time:"<<i->getTime()<<"\tTotal Cost(include departure tax):"<<i->getCost()<<endl;
		cout<<"--------------------------------------------"<<endl;
		for (auto j = flights.begin(); j!= flights.end(); ++j) {
			cout<<j->getID()+'\t'+j->getAirline()+"\t"<<j->getTime()<<'\t'<<j->getPrice()<<'\t'<<j->getDep()->getCode()<<'\t'<<j->getArr()->getCode()<<endl;
		}
		cout<<"--------------------------------------------"<<endl;
	index++;
	}
}

void searchForFlight(Airport_Flight *data){

	cout << "Please input the two airports (format \"CAN MEL\"):"<< endl;
	string line;
	string airport_a;
	string airport_b;
	getline (cin, line);

	stringstream ss(line);
	getline (ss, airport_a, ' ');
	getline (ss, airport_b, ' ');
	
	cout << "Please input the date (format \"15/05/2013\"):"<< endl;
	int day;
	int month;
	int year;
	string token;
	getline (cin, line);

	stringstream ss1(line);
	getline (ss1, token, '/');
	day = atoi(token.c_str());
	getline (ss1, token, '/');
	month = atoi(token.c_str());
	getline (ss1, token, '/');
	year = atoi(token.c_str());
	
	if (day<0||day>30||
		month<0||month>12||
		year<0) {
		cout<<"Invalid date!"<<endl;
		return;
	}


	Date *date = new Date(day, month, year);

	vector<Ticket> info = findFlight(data, airport_a,airport_b, date);

	if (info.size()==0) {
		 cout<<"No result match the query."<<endl;
		return;
	}
	print(info);

	cout<<"1. Book one ticket."<<endl;
	cout<<"2. Go back to main menu."<<endl;
	cout<<"Please select:";

	getline (cin, line);
		
	int choice = stoi(line);

	switch(choice){
	case 1:
		cout<<"Which ticket would you like to book?"<<endl;
		cout<<"Please select:";
		getline (cin, line);
		
		choice = stoi(line);
		
		writeFile("receipt.txt", &info.at(choice-1));
		printReceipt(&info.at(choice-1));
		break;
	case 2:
		return;
		break;
	default:
		cout<<"Please select an option!"<<endl;
		break;
	}
}

int main()
{
	cout<<"initializing, please wait..."<<endl;
	Airport_Flight *data = new Airport_Flight();
	readAirportFile("data\\airport_data.txt", data);
	readFlightFile("data\\flight_data.txt", data);
	while (true) {
		cout << "Welcome to the Flight Booking system!"<<endl;
		cout << "1. Search for flights"<<endl;
		cout << "0. Exit"<<endl;
		cout<<"Please select:";
		
		string line;
		getline(cin, line);
		int choice = stoi(line);
		switch(choice) {
		case 1:
			searchForFlight(data);
			break;
		case 0:
			exit(EXIT_FAILURE);
			break;
		default:
			cout<<"Please select an option!"<<endl;
		}
	}
	system("PAUSE");

	return 0;
}