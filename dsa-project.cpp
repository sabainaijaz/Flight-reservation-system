#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <limits>
using namespace std;

bool validationDate(int day, int month, int year) // Checking if date in flights is valid or not
{
    if (day <= 0 || day > 31 || month <= 0 || month > 12 || year <= 0)
        return false;

    if (month == 2)
    {
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
        {
            if (day > 29)
                return false;
            return true;
        }

        else
        {
            if (day > 28)
                return false;
            return true;
        }
    }

    if (month == 4 || month == 6 || month == 9 || month == 11)
    {
        if (day > 30)
            return false;
        return true;
    }

    else
    {
        if (day > 31)
            return false;
        return true;
    }
}

bool validateTime(string time) // checking if time in flights is valid or not 
{
    size_t positon = time.find(':');
    int hour = stoi(time.substr(0, positon));
    int minutes = stoi(time.substr(positon + 1));

    if (hour > 23 || minutes > 59 || hour < 0 || minutes < 0)
        return false;
    return true;
}

// Customers -> using BST 

template <typename T, typename V>
class BSTNode
{
    public:
    BSTNode<T,V>* LeftChild;
    BSTNode<T,V>* RightChild;
    T data;
    V value;
    BSTNode(T data, V value): data(data), LeftChild(nullptr), RightChild(nullptr), value(value) {}
};

template <typename T, typename V> 
class BST
{
    BSTNode<T,V>* root;
    void inorder(BSTNode<T,V>* p) const
	{
		if (p == nullptr)
			return;

		inorder(p->LeftChild);
		cout << p->data << ", " << p->value << endl;
		inorder(p->RightChild);
	}

	V search(BSTNode<T,V>* temp, T data)
	{
		if (temp == NULL)
			return V();
		if (temp->data == data)
			return temp->value;
		if (temp->data > data)
		{
			return search(temp->LeftChild, data);
		}
		else
		{
			return search(temp->RightChild, data);
		}
	}

    bool search2(BSTNode<T,V>* temp, T data)
	{
		if (temp == NULL)
			return false;
		if (temp->data == data)
			return true;
		if (temp->data > data)
		{
			return search2(temp->LeftChild, data);
		}
		else
		{
			return search2(temp->RightChild, data);
		}
	}

	BSTNode<T,V>* insert(BSTNode<T,V>* temp, T data, V value)
	{
		if (temp == nullptr)
			return new BSTNode<T,V>(data, value);
		if (temp->data < data)
			temp->RightChild = insert(temp->RightChild, data, value);
		else if (temp->data > data)
			temp->LeftChild = insert(temp->LeftChild, data, value);
		else
			cout << "Data already ecists" << endl;

		return temp;
	}

    BSTNode<T,V>* findmax(BSTNode<T,V>* t)
    {
        while(t && t->RightChild)
        {
            t = t->RightChild;
        }

        return t;
    }

    BSTNode<T,V>* remove(BSTNode<T,V>* node, T key)
    {
        if (node == nullptr)
            return nullptr;
        
        if (key < node->data)
            node->LeftChild = remove(node->LeftChild, key);
            
        else if (key > node->data)
            node->RightChild = remove(node->RightChild, key);
            
        else
        {
            if (!node->LeftChild && !node->RightChild)
            {
                delete node;
                return nullptr;
            }

            if (node->LeftChild == nullptr)
            {
                BSTNode<T,V>* temp = node->RightChild;
                delete node;
                return temp;
            }

            if (node->RightChild == nullptr)
            {
                BSTNode<T,V>* temp = node->LeftChild;
                delete node;
                return temp;
            }

            else
            {
                BSTNode<T,V>* temp = findmax(node->LeftChild);
                node->data = temp->data;
                node->value = temp->value;
                node->LeftChild = remove(node->LeftChild, temp->data);
            }
        }

        return node;
    }

public:
	BST(): root(nullptr) {}
	void Inorderdisplay() const 
	{
        if (root == nullptr)
        {
            cout << "Empty." << endl;
            return;
        }
		inorder(root);
	}
    BSTNode<T,V>* getRoot() { return root; }
	V getV(T data) { return search(root, data); }
    bool search(T data) { return search2(root, data); }
	void insert(T data, V value) { root = insert(root, data, value); }
    void remove(T key) { root = remove(root, key); }
    void updateV(T key, V n)
    {
        if (root == nullptr)
            return;
            
        BSTNode<T,V>* temp = root;

        while(true)
        {
            if (temp->data == key)
            {
                temp->value = n;
                return;
            }

            if (temp->data > key)
            {
                if (temp->LeftChild == nullptr)
                    return;
                    
                temp = temp->LeftChild;
            }

            else 
            {
                if (temp->RightChild == nullptr)
                    return;
                
                temp = temp->RightChild;
            }
        }
    }
};

class Customer
{
    string name;
    string phone;
    string dob; // date of birth 
    int numOfFlights; 
    int milesTraveled;
    public: 
    Customer(): name(), phone(), dob(), numOfFlights(), milesTraveled() {}
    Customer(string name, string phone, string dob, int numofFlights, int milesTraveled)
    {
        this->name = name;
        this->phone = phone;
        this->dob = dob;
        this->numOfFlights = numofFlights;
        this->milesTraveled = milesTraveled;
    }
    friend ostream& operator<<(ostream& out, const Customer& c);
    void setName(string name) { this->name = name; }
    void setPhone(string phone) { this->phone = phone; }
    void setDOB(string dob) { this->dob = dob; }
    string getName() const { return name; }
    string getphone() const { return phone; }
    string getDOB() const { return dob; }
    int getNumOfFlights() const { return numOfFlights; }
    int getMilesTravelled() const { return milesTraveled; }
    void updateNumFlights() { ++numOfFlights; }
    void decNumFlights() { --numOfFlights; }
    void updateMilesTravelled(int miles) { milesTraveled += miles; }
    void decMilesTravelled(int miles) { milesTraveled -= miles; }
    void setMilesTravelled(int miles) { this->milesTraveled = miles; }
};

ostream& operator<<(ostream& out, const Customer& c)
{
    out << c.name << ", " << c.phone << ", " << c.dob << ", " << c.numOfFlights << ", " << c.milesTraveled << endl;
    return out;
}

class CustomerBST
{
    BST<int, Customer> customerRecord;

    void saveHelper(BSTNode<int, Customer>* root, ofstream &file)
    {
        if (!root)
            return;

        saveHelper(root->LeftChild, file);

        const Customer& c = root->value;

        file << root->data << "," << c.getName() << "," << c.getphone() << "," << c.getDOB() << "," << c.getNumOfFlights() << "," << c.getMilesTravelled() << endl;

        saveHelper(root->RightChild, file);
    }

    public:
    CustomerBST(): customerRecord() {}
    void insertNew(int customerID, string name, string phone, string dob, int numofFlights, int milesTraveled)
    {
        Customer customer = {name, phone, dob, numofFlights, milesTraveled};
        customerRecord.insert(customerID, customer);
    }
    void readFile()
    {
        ifstream file("customers.txt");

        if (!file)
	    {
		    cerr << "Error. cant open file." << endl;
		    return;
	    }

        string line;

        while(getline(file, line)) // parsing line by line 
        {
            vector<string> substrings;

            size_t start = 0;
            size_t comma = line.find(',');

            while (comma != string::npos) // insert strings into vector when comma is found
            {
                substrings.push_back(line.substr(start, comma - start));
                start = comma + 1;
                comma = line.find(',', start);
            }

            substrings.push_back(line.substr(start));

            if (substrings.size() < 6) // if there's less than 6 substrings - info is not complete.
            {
                cerr << "Skipping line " << line << ": invalid data format" << endl;
                continue;
            }

            string date = substrings[3];
            size_t first = date.find('/');
            size_t second = date.find('/', first + 1);

            int day = stoi(date.substr(0, first));
            int month = stoi(date.substr(first+1, second - first - 1));
            int year = stoi(date.substr(second + 1));

            if (!validationDate(day, month, year))
            {
                cerr << "Invalid date in line " << line << endl;
                continue;
            }
            
            insertNew(stoi(substrings[0]), substrings[1], substrings[2], substrings[3], stoi(substrings[4]), stoi(substrings[5])); // insert it into BST
        }

        file.close();
    }
    void display() const 
    {
        customerRecord.Inorderdisplay();
    }
    void update(int customerID, string name, string phone, string dob)
    {
        Customer oldcustomer = customerRecord.getV(customerID);

        oldcustomer.setName(name);
        oldcustomer.setPhone(phone);
        oldcustomer.setDOB(dob); 

        customerRecord.updateV(customerID, oldcustomer); 
    }
    void FullUpdate(int customerID, Customer cus)
    {
        customerRecord.updateV(customerID, cus);
    }
    void remove(int customerID)
    {
        customerRecord.remove(customerID);
    }
    void saveData()
    {
        ofstream file("customers.txt");

        if (!file)
        {
            cerr << "Error. Can't open file." << endl;
            return;
        }

        saveHelper(getRoot(), file);

        file.close();
    }
    bool search(int customerID) { return customerRecord.search(customerID); }
    Customer getCustomer(int customerID) { return customerRecord.getV(customerID); }
    BSTNode<int, Customer>* getRoot() { return customerRecord.getRoot(); }
};

template <typename T>
class DLLNode
{
	public:
		T data;
		DLLNode* next;
		DLLNode* prev;
		DLLNode(): data(), prev(nullptr), next(nullptr) {}
		DLLNode(T data)
		{
			this->data = data;
			next = NULL;
			prev = NULL;
		}
};

template <typename T>
class DLL
{
	private:
		DLLNode<T>* head;
		DLLNode<T>* tail;
	public: 
		DLL()
		{
			head = NULL;
			tail = NULL;
		}
		void Insert(T element)
		{
			DLLNode<T>* temp = new DLLNode<T>(element);

			if (tail == NULL)
			{
				head = tail = temp;
			}
			else
			{
				tail->next = temp;
				temp->prev = tail;
				tail = temp;
			}
		}
		void display() 
		{
			DLLNode<T>* temp = head;

			while (temp != NULL)
			{
				cout << temp->data << endl ;
				temp = temp->next;
			}
			cout << endl;
		}
		void DeleteFromStart()
		{
			if (head == NULL)
			{
				cout << "List is empty." << endl;
				return;
			}

			if (head == tail)
			{
				delete head;
				head = tail = NULL;
			}

			else
			{
				DLLNode<T>* temp = head;

				head->next->prev = NULL;
				head = head->next;
				delete temp;
			}
		}
		void DeleteFromEnd()
		{
			if (head == NULL)
			{
				cout << "List is empty." << endl;
				return;
			}

			if (tail == head)
			{
				delete head;
				head = tail = NULL;
			}

			else
			{
				DLLNode<T>* temp = tail;

				tail->prev->next = NULL;
				tail = tail->prev;
				delete temp;
			}
		}
		void DeleteByValue(T value) 
		{
			if (head == NULL)
			{
				cout << "List is empty." << endl;
				return;
			}

			DLLNode<T>* temp = head;

			while (temp != NULL)
			{
				if (head->data == value)
				{
					DeleteFromStart();
				}
				else if (tail->data == value)
				{
					DeleteFromEnd();
				}
				else if (temp->data == value)
				{
					temp->next->prev = temp->prev;
					temp->prev->next = temp->next;
					delete temp;
				}
				else 
					temp = temp->next;
			}

			cout << "Value not found in list." << endl;

		}
		void search(T data)
		{
			if (head == NULL)
			{
				cout << "List is empty" << endl;
				return;
			}

			DLLNode<T>* temp = head;

			int i = 1;

			while (temp != NULL)
			{
				if (temp->data == data)
					return;
				temp = temp->next;
				i++;
			}

			return;
		}
        void update(T data, T newData)
        {
            if (head == NULL)
			{
				cout << "List is empty" << endl;
				return;
			}

            DLLNode<T>* temp = head;

			while (temp != NULL)
			{
				if (temp->data == data)
				{
                    temp->data = newData;
                    break;
                }
				temp = temp->next;
			}
        }
        DLLNode<T>* getHead() { return head; }
};

class Flight
{
    int flightNumber;
    int planeID;
    int day;
    int month;
    int year;
    int departureTime;
    string destination;
    vector<pair<string, int>> ticketType;
    CustomerBST passengers; 

    int ReservedSeats;
    public: 
    Flight(): flightNumber(), planeID(), day(), month(), year(), departureTime(), destination(), ticketType(), passengers(), ReservedSeats(0) {}
    Flight(int flightNumber, int planeID, int day, int month, int year, int departureTime, string destination, vector<pair<string, int>> ticketType)
    {
        this->flightNumber = flightNumber;
        this->planeID = planeID;
        this->day = day;
        this->month = month;
        this->year = year;
        this->departureTime = departureTime;
        this->destination = destination;
        this->ticketType = ticketType;
        this->ReservedSeats = 0;
    }
    friend ostream& operator<<(ostream& out, const Flight& f);
    vector<pair<string,int>> getTicketType()
    {
        return ticketType;
    }
    int getFlightNumber() const { return flightNumber; }
    int getPlaneID() const { return planeID; }
    int getDay() const { return day; }
    int getMonth() const { return month; }
    int getYear() const  { return year; }
    int getDepartureTime() const { return departureTime; }
    string getDestination() const { return destination; }
    vector<pair<string,int>> getTicketType() const { return ticketType; }
    int getReservedSeats() const { return ReservedSeats; }
    bool isValid() // checking if flight exists or not 
    {
        return flightNumber != 0;       
    }
    bool operator==(const Flight& other) const
    {
        return flightNumber == other.flightNumber && planeID == other.planeID && day == other.day && month == other.month && year == other.year && departureTime == other.departureTime && destination == other.destination && ticketType == other.ticketType;
    }
    int getTotalSeats() const
    {
        int totalSeats = 0;
        for (size_t i = 0; i < ticketType.size(); i++)
        {
            totalSeats += ticketType[i].second;
        }

        return totalSeats;
    }
    bool seatsAvailable() const
    {
        int totalSeats = getTotalSeats();

        return totalSeats > ReservedSeats;
    }
    void IncrementReservedSeats() { ++ReservedSeats; }
    void DecrementReservedSeats() { --ReservedSeats; }
    CustomerBST& getPassengers() { return passengers; }
    void setPLaneID(int planeID) {this->planeID = planeID;}
    void setDay(int day) { this->day = day;}
    void setMonth(int month) { this->month = month;}
    void setYear(int year) { this->year = year;}
    void setTime(int time) { this->departureTime = time;}
    void setDestination(string des) { this->destination = des; }
};

ostream& operator<<(ostream& out, const Flight& f)
{
    out << f.flightNumber << ", " << f.planeID << ", " << f.day << ", " << f.month << ", " << f.year << ", " << f.departureTime << ", " << f.destination << ", ";
    for (size_t i = 0; i <f.ticketType.size(); i++)
    {
        out << f.ticketType[i].first << ": " << f.ticketType[i].second << ", ";
    }

    cout << endl << "Passengers in the flights: " << endl;
    f.passengers.display();
    return out;
}

class FlightDLL
{
    DLL<Flight> flightRecord;

    public:
    FlightDLL(): flightRecord() {}
    void insertNew(int flightNumber, int planeID, int day, int month, int year, int departureTime, string destination, vector<pair<string, int>> ticketType)
    {
        Flight newFlight = {flightNumber, planeID, day, month, year, departureTime, destination, ticketType};
        flightRecord.Insert(newFlight);
    }
    void readFile()
    {
        ifstream file("flights.txt");

        if (!file)
	    {
		    cerr << "Error. cant open file." << endl;
		    return;
	    }

        string line;

        while(getline(file, line)) // parse file line by line 
        {
            vector<string> substrings;

            size_t start = 0;
            size_t comma = line.find(',');

            while (comma != string::npos) // add strings to vector as a comma is found
            {
                substrings.push_back(line.substr(start, comma - start));
                start = comma + 1;
                comma = line.find(',', start);
            }

            substrings.push_back(line.substr(start));

            if (substrings.size() < 7) // if substrings are less than 7 - information is not complete 
            {
                cerr << "Skipping line " << line << ": invalid data format" << endl;
                continue;
            }

            vector<pair<string, int>> ticketType; 
            if (validationDate(stoi(substrings[2]), stoi(substrings[3]), stoi(substrings[4])) && validateTime(substrings[5])) // check if time and date is valid - if not don't insert the flight
            {
                for (size_t i = 7; i < substrings.size(); i++) // inserting ticket types 
                {
                    if (substrings[i].empty())
                        continue;
                    
                    size_t positon = substrings[i].find(':');
                    string type = substrings[i].substr(0, positon);
                    int price = stoi(substrings[i].substr(positon + 1));
                    ticketType.push_back({type,price});
                        
                }

                insertNew(stoi(substrings[0]), stoi(substrings[1]), stoi(substrings[2]), stoi(substrings[3]), stoi(substrings[4]), stoi(substrings[5]), substrings[6], ticketType);
            }  
        }

        file.close();
    }
    void display()
    {
        flightRecord.display();
    }
    Flight* searchFlight(int flightNumber)
    {
        DLLNode<Flight>* temp = flightRecord.getHead();

        while(temp != nullptr)
        {
            if (temp->data.getFlightNumber() == flightNumber)
                return &temp->data;

            temp = temp->next;
        }

        return nullptr;
    }
    void searchFlightByDestination(string des)
    {
        DLLNode<Flight>* temp = flightRecord.getHead();

        while(temp != nullptr)
        {
            if (temp->data.getDestination() == des)
            {
                cout << temp->data; 
            }

            temp = temp->next;
        }
    }
    bool CheckSeatAvailability(int flightNumber)
    {
        DLLNode<Flight>* temp = flightRecord.getHead();

        while(temp != nullptr)
        {
            if (temp->data.getFlightNumber() == flightNumber)
            {
                const Flight& f = temp->data;
                return f.seatsAvailable();
            }

            temp = temp->next;
        }
    }
    void AddPassenger(int customerID, int flightNumber, string name, string phone, string dob, int numFlights, int miles)
    {
        Flight* f = searchFlight(flightNumber);

        if (f == nullptr)
        {
            cout << "Flight does not exist." << endl;
            return;
        }

        f->getPassengers().insertNew(customerID, name, phone, dob, numFlights, miles);
        f->IncrementReservedSeats();
    }
    void update(int oldFlightNumber, int planeID, int day, int month, int year, int departureTime, string destination, vector<pair<string, int>> ticketType)
    {
        if (!validationDate(day, month, year) || !validateTime(to_string(departureTime))) // if new flight info is valid 
        {
            cout << "invalid new flight credentials." << endl;
            return;
        }

        Flight* f = searchFlight(oldFlightNumber);

        if (f == nullptr)
        {
            cout << "Flight not found. " << endl;
            return;
        }

        f->setPLaneID(planeID);
        f->setDay(day);
        f->setMonth(month);
        f->setYear(year);
        f->setTime(departureTime);
        f->setDestination(destination);
    }
    DLLNode<Flight>* getHead() { return flightRecord.getHead(); }
    void remove(int flightNumber)
    {
        DLLNode<Flight>* temp = flightRecord.getHead();

        while (temp != nullptr)
        {
            if (temp->data.getFlightNumber() == flightNumber)
            {
            
                if (temp->prev == nullptr)
                {
                    flightRecord.DeleteFromStart();
                    cout << "Flight removed successfully." << endl;
                    return;
                }

            
                if (temp->next == nullptr)
                {
                    flightRecord.DeleteFromEnd();
                    cout << "Flight removed successfully." << endl;
                    return;
                }

           
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;

                delete temp;

                cout << "Flight removed successfully." << endl;
                return;
            }

            temp = temp->next;
        }
    }
    void saveData()
    {
        ofstream file("flights.txt");

        if (!file)
        {
            cerr << "Error. Can't open file." << endl;
            return;
        }

        DLLNode<Flight>* temp = flightRecord.getHead();

        while (temp != nullptr)
        {
            const Flight& f = temp->data;
            file << f.getFlightNumber() << "," << f.getPlaneID() << "," << f.getDay() << "," << f.getMonth() << "," << f.getYear() << "," << f.getDepartureTime() << "," << f.getDestination();
            const auto& ticketType = f.getTicketType();
            for (size_t i = 0; i < ticketType.size(); i++)
            {
                file << "," << ticketType[i].first << ":" << ticketType[i].second;
            }

            file << "\n";
            temp = temp->next;
        }

        file.close();
    }
};

class Airport
{
    string airportName;
    string country;
    string UsualWeatherCondition;
    int timeFromBeirut;
    int milesFromBeirut;
    public:
    Airport(): airportName(), country(), UsualWeatherCondition(), timeFromBeirut(), milesFromBeirut() {}
    Airport(string airportName, string country, string UsualWeatherCondition, int timeFromBeirut, int milesFromBeirut)
    {
        this->airportName = airportName;
        this->country = country;
        this->UsualWeatherCondition = UsualWeatherCondition;
        this->timeFromBeirut = timeFromBeirut;
        this->milesFromBeirut = milesFromBeirut;
    }
    friend ostream& operator<<(ostream& out, const Airport& a);
    string getAirportName() const { return airportName; }
    string getCountry() const { return country; }
    string getWeatherConditions() const { return UsualWeatherCondition; }
    int getTimeFromBeirut() const { return timeFromBeirut; }
    int getMilesFromBeirut() const { return milesFromBeirut; }
};

ostream& operator<<(ostream& out, const Airport& a)
{
    out << a.airportName << ", " << a.country << ", " << a.UsualWeatherCondition << ", " << a.timeFromBeirut << ", " << a.milesFromBeirut << endl;
    return out;
}

class AirportDLL
{
    DLL<Airport> airportRecord;

    public:
    AirportDLL(): airportRecord() {}

    DLLNode<Airport>* getHead() { return airportRecord.getHead(); }

    void InsertNew(string airportName, string country, string UsualWeatherCondition, int timeFromBeirut, int milesFromBeirut)
    {
        Airport airport = {airportName, country, UsualWeatherCondition, timeFromBeirut, milesFromBeirut};
        airportRecord.Insert(airport);
    }
    void readFile()
    {
        ifstream file("airports.txt");

        if (!file)
	    {
		    cerr << "Error. cant open file." << endl;
		    return;
	    }

        string line;

        while(getline(file, line)) // parsing line by line 
        {
            vector<string> substrings;

            size_t start = 0;
            size_t comma = line.find(',');

            while (comma != string::npos) // insert strings into vector when comma is found
            {
                substrings.push_back(line.substr(start, comma - start));
                start = comma + 1;
                comma = line.find(',', start);
            }

            substrings.push_back(line.substr(start));

            if (substrings.size() < 5) // if there's less than 5 substrings - info is not complete.
            {
                cerr << "Skipping line " << line << ": invalid data format" << endl;
                continue;
            }

            InsertNew(substrings[0], substrings[1], substrings[2], stoi(substrings[3]), stoi(substrings[4])); // insert it into DLL
        }

        file.close();
    }
    void display()
    {
        airportRecord.display();
    }
    void saveData()
    {
        ofstream file("airports.txt");

        if (!file)
        {
            cerr << "Error. Can't open file." << endl;
            return;
        }

        DLLNode<Airport>* temp = airportRecord.getHead();

        while(temp != nullptr)
        {
            const Airport& a = temp->data;
            file << a.getAirportName() << "," << a.getCountry() << "," << a.getWeatherConditions() << "," << a.getTimeFromBeirut() << "," << a.getMilesFromBeirut() << endl;

            temp = temp->next;
        }

        file.close();

    }
};

class Plane
{
    int planeID;
    string description;
    int numberOfMilesTravelled;
    vector<int> numberOfSeatsPerClass;
    public:
    Plane(): planeID(), description(), numberOfMilesTravelled(), numberOfSeatsPerClass() {}
    Plane(int planeID, string description, int numberOfMilesTravelled, vector<int> numberOfSeatsPerClass)
    {
        this->planeID = planeID;
        this->description = description;
        this->numberOfMilesTravelled = numberOfMilesTravelled;
        this->numberOfSeatsPerClass = numberOfSeatsPerClass;
    }
    friend ostream& operator<<(ostream& out, const Plane& p);
    int getPlaneID() const { return planeID; }
    string getDescription() const { return description; }
    int getMilesTravelled() const { return numberOfMilesTravelled; }
    vector<int> getSeatsPerClass() const { return numberOfSeatsPerClass; }
};

ostream& operator<<(ostream& out, const Plane& p)
{
    out << p.planeID << ", " << p.description << ", " << p.numberOfMilesTravelled << ",";
    for (size_t i = 0; i <p.numberOfSeatsPerClass.size(); i++)
    {
        out << p.numberOfSeatsPerClass[i] << " ";
    }

    return out;
}

class PlaneDLL
{
    DLL<Plane> planeRecord;
    public:
    PlaneDLL(): planeRecord() {}
    void InsertNew(int planeID, string description, int numberOfMilesTravelled, vector<int> numberOfSeatsPerClass)
    {
        Plane plane = {planeID, description, numberOfMilesTravelled, numberOfSeatsPerClass};
        planeRecord.Insert(plane);
    }
    void readFile()
    {
        ifstream file("planes.txt");

        if (!file)
	    {
		    cerr << "Error. cant open file." << endl;
		    return;
	    }

        string line;

        while(getline(file, line)) // parse file line by line 
        {
            vector<string> substrings;

            size_t start = 0;
            size_t comma = line.find(',');

            while (comma != string::npos) // add strings to vector as a comma is found
            {
                substrings.push_back(line.substr(start, comma - start));
                start = comma + 1;
                comma = line.find(',', start);
            }

            substrings.push_back(line.substr(start));

            if (substrings.size() < 4) // if substrings are less than 4 - information is not complete 
            {
                cerr << "Skipping line " << line << ": invalid data format" << endl;
                continue;
            }

            vector<int> numberOfSeatsPerClass;
            for (size_t i = 3; i < substrings.size(); i++) // inserting ticket types 
            {
                if (substrings[i].empty())
                    continue;
                    
                numberOfSeatsPerClass.push_back(stoi(substrings[i]));     
            }

            InsertNew(stoi(substrings[0]), substrings[1], stoi(substrings[2]), numberOfSeatsPerClass);
        }

        file.close();
    }
    void display()
    {
        planeRecord.display();
    }
    Plane* search(int planeID)
    {
        DLLNode<Plane>* temp = planeRecord.getHead();
        while( temp != nullptr)
        {
            if (temp->data.getPlaneID() == planeID)
                return &temp->data;
            temp = temp->next;
        }

        return nullptr;
    }
    void saveData()
    {
        ofstream file("planes.txt");

        if (!file)
        {
            cerr << "Error. Can't open file." << endl; 
            return;
        }

        DLLNode<Plane>* temp = planeRecord.getHead();

        while(temp != nullptr)
        {
            const Plane& p = temp->data;

            file << p.getPlaneID() << "," << p.getDescription() << "," << p.getMilesTravelled();
            const auto& seatsPerClass = p.getSeatsPerClass();
            for (size_t i = 0; i < seatsPerClass.size(); i++)
            {
                file << "," << seatsPerClass[i];
            }

            file << endl;
            temp = temp->next;
        }

        file.close();
    }
};

class Ticket
{
    string customerId;
    string name;
    int flightNum;
    int ticketNum;
    string ticketType;
    int costOfFlight;
    bool discount;
    string reasonForDiscount;
    string dateTime;
    int seatNumber;
    public:
    Ticket(): customerId(), name(), flightNum(), ticketNum(), costOfFlight(), discount(false), reasonForDiscount(), dateTime(), seatNumber() {}
    Ticket(string customerId, string name, int flightNum, int ticketNum, string ticketType, int costOfFlight, bool discount, string reasonForDiscount, string dateTime, int seatNumber)
    {
        this->customerId = customerId;
        this->name = name;
        this->flightNum = flightNum;
        this->ticketNum = ticketNum;
        this->ticketType = ticketType;
        this->costOfFlight = costOfFlight;
        this->discount = discount;
        this->reasonForDiscount = reasonForDiscount;
        this->dateTime = dateTime;
        this->seatNumber = seatNumber;
    }
    friend ostream& operator<<(ostream& out, const Ticket& t);
    string getCustomerID() const { return customerId; }
    string getName() const { return name; }
    int getFlightNum() const { return flightNum; }
    int getTicketNum() const { return ticketNum; }
    string getTicketType() const { return ticketType; }
    int getCostofFlight() const { return costOfFlight; }
    bool getDiscount() const { return discount; }
    string getreasonForDiscount() const { return reasonForDiscount; }
    string getDateTime() const { return dateTime; }
    int getSeatNumber() const { return seatNumber; }
};

ostream& operator<<(ostream& out, const Ticket& t)
{
    out << t.customerId << ", " << t.name << ", " << t.flightNum << ", " << t.ticketNum << ", " << t.ticketType << ", " << t.costOfFlight << ", " << t.discount << ", " << t.reasonForDiscount << ", " << t.dateTime << ", " << t.seatNumber << endl;
    return out; 
}

class TicketArray
{
    vector<Ticket> ticketRecord;
    public:
    TicketArray(): ticketRecord() {}
    void InsertNew(string customerId, string name, int flightNum, int ticketNum, string ticketType, int costOfFlight, bool discount, string reasonForDiscount, string dateTime, int seatNumber)
    {
        Ticket ticket = {customerId, name, flightNum, ticketNum, ticketType, costOfFlight, discount, reasonForDiscount, dateTime, seatNumber};
        ticketRecord.push_back(ticket);
    }
    void readFile()
    {
        ifstream file("tickets.txt");

        if (!file)
	    {
		    cerr << "Error. cant open file." << endl;
		    return;
	    }

        string line;

        while(getline(file, line)) // parsing line by line 
        {
            vector<string> substrings;

            size_t start = 0;
            size_t comma = line.find(',');

            while (comma != string::npos) // insert strings into vector when comma is found
            {
                substrings.push_back(line.substr(start, comma - start));
                start = comma + 1;
                comma = line.find(',', start);
            }

            substrings.push_back(line.substr(start));

            if (substrings.size() < 10) // if there's less than 10 substrings - info is not complete.
            {
                cerr << "Skipping line " << line << ": invalid data format" << endl;
                continue;
            }

            bool b = (substrings[6] == "1");

            InsertNew(substrings[0], substrings[1], stoi(substrings[2]), stoi(substrings[3]), substrings[4], stoi(substrings[5]), b, substrings[7], substrings[8], stoi(substrings[9]));
        }

        file.close();
    }
    void display()
    {
        for (const auto& t: ticketRecord)
        {
            cout << t;
        }
    }
    vector<Ticket>& getTicketRecord()
    {
        return ticketRecord;
    }
    void saveData()
    {
        ofstream file("tickets.txt");

        if (!file)
        {
            cerr << "Error. Can't open file." << endl;
            return;
        }

        for (auto& t: ticketRecord)
        {
            file << t.getCustomerID() << "," << t.getName() << "," << t.getFlightNum() << "," << t.getTicketNum() << "," << t.getTicketType() << "," << t.getCostofFlight() << "," << t.getDiscount() << "," << t.getreasonForDiscount() << "," << t.getDateTime() << "," << t.getSeatNumber() << endl;
        }

        file.close();
    
    }
    int getTicketRecordSize() { return ticketRecord.size(); }
};

class Offers
{
    int offerID;
    int flightNumber;
    string offerType;
    int discountAmount;
    public:
    Offers(): offerID(), flightNumber(), offerType(), discountAmount() {}
    Offers(int offerID, int flightNumber, string offerType, int discountAmount)
    {
        this->offerID = offerID;
        this->flightNumber = flightNumber;
        this->offerType = offerType;
        this->discountAmount = discountAmount;
    }
    friend ostream& operator<<(ostream& out, const Offers& o);
    int getOfferID() const { return offerID; }
    int getFlightNum() const { return flightNumber; }
    string getOfferType() const { return offerType; }
    int getDiscountAmount() const { return discountAmount; }
};

ostream& operator<<(ostream& out, const Offers& o)
{
    out << o.offerID << ", " <<  o.flightNumber << ", " << o.offerType << ", " << o.discountAmount << endl;
    return out; 
}

class OffersArray
{
    vector<Offers> offersRecord;
    public:
    OffersArray(): offersRecord() {}
    void InsertNew(int offerID, int flightNumber, string offerType, int discountAmount)
    {
        Offers offer = {offerID, flightNumber, offerType, discountAmount};
        offersRecord.push_back(offer);
    }
    void readFile()
    {
        ifstream file("offers.txt");

        if (!file)
	    {
		    cerr << "Error. cant open file." << endl;
		    return;
	    }

        string line;

        while(getline(file, line)) // parsing line by line 
        {
            vector<string> substrings;

            size_t start = 0;
            size_t comma = line.find(',');

            while (comma != string::npos) // insert strings into vector when comma is found
            {
                substrings.push_back(line.substr(start, comma - start));
                start = comma + 1;
                comma = line.find(',', start);
            }

            substrings.push_back(line.substr(start));

            if (substrings.size() < 4) // if there's less than 4 substrings - info is not complete.
            {
                cerr << "Skipping line " << line << ": invalid data format" << endl;
                continue;
            }

            InsertNew(stoi(substrings[0]), stoi(substrings[1]), substrings[2], stoi(substrings[3]));
        }

        file.close();
    }
    void display()
    {
        for (const auto& o: offersRecord)
        {
            cout << o;
        }
    }
    vector<Offers> getOfferRecord() { return offersRecord; }
    void saveData()
    {
        ofstream file("offers.txt");

        if (!file)
        {
            cerr << "Error. Can't open file." << endl;
            return;
        }

        for (auto& o: offersRecord)
        {
            file << o.getOfferID() << "," << o.getFlightNum() << "," << o.getOfferType() << "," << o.getDiscountAmount() << endl;
        }

        file.close();
    
    }
};

class FlightReservationSystem
{
    AirportDLL airports;
    PlaneDLL planes;
    FlightDLL flights;
    CustomerBST customers;
    OffersArray offers;
    TicketArray tickets;
    vector<pair<int, queue<int>>> waitingList; // flight number and queue of customer ids

    // HELPER FUNCTIONS //

    // delelting passengers from bst 
    void RemovePassengersFromFlight(BSTNode<int, Customer>* root, int miles)
    {
        if (root == nullptr)
            return;

        RemovePassengersFromFlight(root->LeftChild, miles);
        RemovePassengersFromFlight(root->RightChild, miles);

        int customerID = root->data;

        if (customers.search(customerID))
        {
            Customer cus = customers.getCustomer(customerID);

            if (cus.getNumOfFlights() > 0)
                cus.decNumFlights();

            cus.decMilesTravelled(miles);
            if (cus.getMilesTravelled() < 0)
                cus.setMilesTravelled(0);

            customers.FullUpdate(customerID, cus);
        }
    } 
    
    // get flight miles
    int getMilesForFlight(string des)
    {
        DLLNode<Airport>* temp = airports.getHead();

        while (temp != nullptr)
        {
            if (temp->data.getAirportName() == des)
                return temp->data.getMilesFromBeirut();
            temp = temp->next;
        }

        return 0;
    }

    // check waiting size list limit (5:100 ratio)
    queue<int>* getWaitingQueueForFlight(int flightNum)
    {
        for (auto &w : waitingList)
        {
            if (w.first == flightNum)
                return &w.second;
        }

        waitingList.push_back({flightNum, queue<int>()}); // if no queue for flight exists -> create one
        return &waitingList.back().second;
    }
  
    // get flight ticket price
    int getTicketPrice(Flight* f, string TicketType)
    {
        for (auto& ticket: f->getTicketType())
        {
            if (ticket.first == TicketType)
                return ticket.second;
        }

        return -1;
    }

    // check offers 
    int checkOffer(int customerID, int flightNum, int price, bool& discount, string& reason)
    {
        discount = false;
        reason = " ";

        for (auto& off : offers.getOfferRecord())
        {
            if (off.getFlightNum() == flightNum)
            {
                discount = true;
                reason = off.getOfferType();
                return price - off.getDiscountAmount();
            }
        }

        return price;
    }
  
    public:
    FlightReservationSystem(): airports(), planes(), flights(), customers(), offers(), tickets(), waitingList() {}
    
    // SYSTEM LOADING //

    // loading all files to data structures
    void loadData()
    {
        cout << "Loading airports..." << endl;
        airports.readFile();
        cout << "Loading planes..." << endl;
        planes.readFile();
        cout << "Loading flights..." << endl;
        flights.readFile();
        cout << "Loading cutoemrs..." << endl;
        customers.readFile();
        cout << "Loading offers..." << endl;
        offers.readFile();
        cout << "Loading tickets..." << endl;
        tickets.readFile();
    }

    // save data back to files
    void saveData()
    {
        cout << "Saving airports..." << endl;
        airports.saveData();
        cout << "Saving planes..." << endl;
        planes.saveData();
        cout << "Saving flights..." << endl;
        flights.saveData();
        cout << "Saving custoemrs..." << endl;
        customers.saveData();
        cout << "Saving offers..." << endl;
        offers.saveData();
        cout << "Saving tickets..." << endl;
        tickets.saveData();
    } 


    // FLIGHTS FUNCTIONS // 

    // add new flight
    void AddNewFlight()
    {
        int flightnumber; int planeID; int day; int month; int year; int departureTime; string destination; vector<pair<string,int>> ticketType;
        int count;

        cout << "Enter new flight Numebr: ";
        cin >> flightnumber;
        cout << "Enter plane ID: ";
        cin >> planeID;
        cout << "Enter date of departure: ";
        cin >> day;
        cout << "Enter month of departure: ";
        cin >> month;
        cout << "Enter year of departure: ";
        cin >> year;

        if (!validationDate(day, month, year))
        {
            cout << "Invalid date. please try again." << endl;

            cin.clear(); 
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

            return;
        }

        cout << "Enter depature time: ";
        cin >> departureTime;

        if (departureTime < 0 || departureTime > 23)
        {
            cout << "Invalid time. please try again." << endl;
            return;
        }

        cout << "Enter destination: ";
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
        getline(cin, destination);
        cout << "How many ticket types are there? ";
        cin>> count;
        cout << "Enter the ticket type and its price: ";
        for (int i = 0; i < count; i++)
        {
            string type; int price;
            cout << i+1 << ": ";
            cout << "Type: ";
            cin >> type;
            cout << "Price: ";
            cin >> price;
            ticketType.push_back({type,price});
        }

        flights.insertNew(flightnumber, planeID, day, month, year, departureTime, destination, ticketType);
        cout << "New flight inserted successfully." << endl;

        // updating plane miles
        int miles = getMilesForFlight(destination);
        Plane* p = planes.search(planeID);

        if (p)
        {
            int newMiles = p->getMilesTravelled() + miles;
            *p = Plane(p->getPlaneID(), p->getDescription(), newMiles, p->getSeatsPerClass());
        }
    }

    // update flights
    void UpdateFlight(int oldFlightNumber)
    {
        int planeID, day, month, year, departureTime, count;
        string destination;
        vector<pair<string, int>> ticketType;

        cout << "Enter new plane ID: ";
        cin >> planeID;

        cout << "Enter new flight date and time: " << endl;
        cout << "date: ";
        cin >> day;
        cout << "month: ";
        cin >> month;
        cout << "year: ";
        cin >> year;

        if (!validationDate(day, month, year))
        {
            cout << "Invalid date. please try again." << endl;
            return;
        }

        cout << "time: ";
        cin >> departureTime;

        if (departureTime < 0 || departureTime > 23)
        {
            cout << "Invalid time. please try again." << endl;
            return;
        }

        cout << "Enter destination: ";
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        getline(cin, destination);

        cout << "How many ticket types are there? ";
        cin>> count;
        cout << "Enter the ticket type and its price: ";
        for (int i = 0; i < count; i++)
        {
            string type; int price;
            cout << i+1 << ": ";
            cout << "Type: ";
            cin >> type;
            cout << "Price: ";
            cin >> price;
            ticketType.push_back({type,price});
        }

        flights.update(oldFlightNumber, planeID, day, month, year, departureTime, destination, ticketType);

        // updating plane miles:
        
        Plane* p = planes.search(planeID);

        if (p)
        {
            int currMiles = getMilesForFlight(destination);
            int newMiles = p->getMilesTravelled() + currMiles;
            *p = Plane(p->getPlaneID(), p->getDescription(), newMiles, p->getSeatsPerClass());
        }
    }
    // delete flight and handle waiting list + passengers etc

    void DeleteFlight(int flightNum)
    {
        Flight* f = flights.searchFlight(flightNum);

        if (!f)
        {
            cout << "Flight doesn't exist." << endl;
            return;
        }

        // updating plane miles:
        int planeID = f->getPlaneID();
        string des = f->getDestination();
        int miles = getMilesForFlight(des);

        Plane* p = planes.search(planeID);
        if (p)
        {
            int newMiles = p->getMilesTravelled() - miles;
            if (newMiles < 0)
                newMiles = 0;

            *p = Plane(p->getPlaneID(), p->getDescription(), newMiles, p->getSeatsPerClass());
        }

        // removing passengers 
        RemovePassengersFromFlight(f->getPassengers().getRoot(), miles);

        // removing tickets
        vector<Ticket> newTickets;
        for (auto &t: tickets.getTicketRecord())
        {
            if (t.getFlightNum() != flightNum)
                newTickets.push_back(t);
        }
        tickets.getTicketRecord() = newTickets;

        // removing waiting lists
        for (int i = 0; i < waitingList.size(); i++)
        {
            if (waitingList[i].first == flightNum)
            {
                waitingList.erase(waitingList.begin() + i);
                break;
            }
        }

        // removing flight
        flights.remove(flightNum);
        cout << "Deletion of flight successful." << endl;

    }
    
    // display all flights
    void DisplayAllFlights()
    {
        flights.display();
    }

    // CUSTOMER FUNCTIONS //

    // add new customer
    void NewCustomer()
    {
        int customerID; 
        string name, phone, dob;

        cout << "Enter your ID: ";
        cin >> customerID;

        if (customers.search(customerID))
        {
            cout << "Customer already exists." << endl;
            return;
        }

        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        cout << "Enter your name: ";
        getline(cin, name);
        cout << "Enter a phone number: ";
        getline(cin, phone);
        cout << "Enter your date of birth in DD/MM/YY format: ";
        getline(cin, dob); 

        size_t first = dob.find('/');
        size_t second = dob.find('/', first + 1);

        int day = stoi(dob.substr(0, first));
        int month = stoi(dob.substr(first+1, second - first - 1));
        int year = stoi(dob.substr(second + 1));

        if (!validationDate(day, month, year))
        {
            cerr << "Invalid date. Please try again. " << endl;
            return;
        }

        customers.insertNew(customerID, name, phone, dob, 0, 0);

        cout << "New customer added succeddully." << endl;
    }

    // update customer
    void UpdateCustomer()
    {
        int customerID; 
        string name, phone, dob;

        cout << "Enter your ID: ";
        cin >> customerID;

        if (!customers.search(customerID))
        {
            cout << "Customer doesnt exists." << endl;
            return;
        }

        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        cout << "Enter your name: ";
        getline(cin, name);
        cout << "Enter a phone number: ";
        getline(cin, phone);
        cout << "Enter your date of birth in DD/MM/YY format: ";
        getline(cin, dob);

        size_t first = dob.find('/');
        size_t second = dob.find('/', first + 1);

        int day = stoi(dob.substr(0, first));
        int month = stoi(dob.substr(first+1, second - first - 1));
        int year = stoi(dob.substr(second + 1));

        if (!validationDate(day, month, year))
        {
            cerr << "Invalid date. Please try again. " << endl;
            return;
        }

        customers.update(customerID, name, phone, dob);

        // updating tickets:
        for (auto& t: tickets.getTicketRecord())
        {
            if (stoi(t.getCustomerID()) == customerID)
            {
                t = Ticket(to_string(customerID), name, t.getFlightNum(), t.getTicketNum(), t.getTicketType(), t.getCostofFlight(), t.getDiscount(), t.getreasonForDiscount(), t.getDateTime(), t.getSeatNumber());
            }
        }

        cout << "Custoemr updated successfully." << endl;
    }

    // delete 
    void DeleteCustomer(int customerID)
    {
        if (!customers.search(customerID))
        {
            cout << "Customer doesn't exist." << endl;
            return;
        }

        // removing from flights
        DLLNode<Flight>* temp = flights.getHead();

        while (temp != nullptr)
        {
            Flight &f = temp->data;

            if (f.getPassengers().search(customerID))
            {
                f.getPassengers().remove(customerID);

                if (f.getReservedSeats() > 0)
                    f.DecrementReservedSeats();
            }

            temp = temp->next;
        }

        // remove from waiitng lsits
        for (auto& w: waitingList)
        {
            queue<int> queue;
            while(!w.second.empty())
            {
                int cusID = w.second.front();
                w.second.pop();
                if (cusID != customerID)
                {
                    queue.push(cusID);                
                }
            }
            w.second = queue;
        }

        // dleeting tickets:
        vector<Ticket> newTickets;
        for (auto& t: tickets.getTicketRecord())
        {
            if (stoi(t.getCustomerID()) != customerID)
                newTickets.push_back(t);
        }
        tickets.getTicketRecord() = newTickets;

        customers.remove(customerID);
        cout << "Customer removed succesfully" << endl;
    }

    // view customer profile && flight history
    void ViewCustomerProfile(int customerID)
    {
        if (!customers.search(customerID))
        {
            cout << "Customer does not exist." << endl;
            return;
        }

        Customer customer = customers.getCustomer(customerID);
        cout << "Displaying customer profile: " << endl;
        cout << "Name: " << customer.getName() << "\n Phone: " << customer.getphone() << "\n DOB: " << customer.getDOB() << "\n Number of Flights taken: " << customer.getNumOfFlights() << "\n Number of Miles travelled: " << customer.getMilesTravelled() << endl;
        cout << "Customer's tickets: " << endl;
        for (auto &t: tickets.getTicketRecord())
        {
            if (stoi(t.getCustomerID()) == customerID)
            {
                cout << t;
            }
        }
    }
   
    // RESERVATION FUNCTIONS // 

    // search flights by destination - print its flight details
    void SearchFlightsByDestination(string destination)
    {
        cout << "Displaying flights to " << destination << ": " << endl;
        flights.searchFlightByDestination(destination); // display available seats 
    }

    // reserve seat - create customer + check seat available + allocate seat + update flight passengers + update customer + update plane + generate ticket + save to ticket
    void ReserveSeat(int customerID, int flightNumber, string TicketType)
    {
        Flight* f = flights.searchFlight(flightNumber);

        if (!f) // check if flight exists
        {
            cout << "Flight does not exist." << endl;
            return;
        }

        if (!customers.search(customerID)) // check if customer exists
        {
            cout << "Customer doesn't exist. Adding now: " << endl;
            NewCustomer();
        }

        if (!f->seatsAvailable()) // if no seats available -> add customer to waiting lsit
        {
            cout << "Flight is full. Adding you to the waiting list." << endl;

            queue<int>* queue = getWaitingQueueForFlight(flightNumber);
            int limit = (f->getTotalSeats() / 100) * 5; // 5:100 ratio of queue to total seats

            if (queue->size() >= limit)
            {
                cout << "Waiting list for flight is full." << endl;
                return;
            }

            queue->push(customerID);
            cout << "You're added to the waiting list." << endl;
            return; 
        }

        // if there are seats available:
        int seatNumber = f->getReservedSeats() + 1;
        int price = getTicketPrice(f, TicketType);

        bool discount = false;
        string reason;
        int CostAfterOffer = checkOffer(customerID, flightNumber, price, discount, reason);

        // updating cuztomer info:
        Customer customer = customers.getCustomer(customerID);
        customer.updateNumFlights();
        customer.updateMilesTravelled(getMilesForFlight(f->getDestination()));
        customers.FullUpdate(customerID, customer);

        // up[dating] number of flights
        f->IncrementReservedSeats();

        // generating ticket:
        int ticket = tickets.getTicketRecordSize() + 1;

        string date = to_string(f->getDay()) + "/" + to_string(f->getMonth()) + "/" + to_string(f->getYear());
        string time = to_string(f->getDepartureTime());

        tickets.InsertNew(to_string(customerID), customer.getName(), flightNumber, ticket, TicketType, CostAfterOffer, discount, reason, date + " " + time, seatNumber);

        // adding customers to the flights passengers lsit:
        f->getPassengers().insertNew(customerID, customer.getName(), customer.getphone(), customer.getDOB(), customer.getNumOfFlights(), customer.getMilesTravelled());

        cout << "Seat reserved successfully." << endl;
        
    }
    
    // cancel reservation - remove pass from flight + u[date customer info + free seat + delete ticket + handle waiting lsit
    void CancelReservation(int customerID, int flightNum)
    {
        Flight* f = flights.searchFlight(flightNum);

        if (!f) // check if flight exists 
        {
            cout << "Flight foesn't exist." << endl;
            return;
        }

        if (!f->getPassengers().search(customerID)) // if cus is not part of the flight
        {
            cout << "No resevration found." << endl;
            return;
        }

        f->getPassengers().remove(customerID);

        f->DecrementReservedSeats();

        // updating cutomer info:
        Customer customer = customers.getCustomer(customerID);
        customer.decNumFlights();
        customer.decMilesTravelled(getMilesForFlight(f->getDestination()));
        customers.FullUpdate(customerID, customer);

        // removing ticket:
        vector<Ticket> newTickets;
        for (auto& t: tickets.getTicketRecord())
        {
            if (!(stoi(t.getCustomerID()) == customerID && t.getFlightNum() == flightNum))
            {
                newTickets.push_back(t);
            }
        }
        tickets.getTicketRecord() = newTickets;

        cout << "Reservation Cancelled." << endl;
 

        // handingling waiiting list:
        queue<int>* queue = getWaitingQueueForFlight(flightNum);
        if (!queue->empty())
        {
            int passenger = queue->front();
            queue->pop();

            cout << "Paasenger " << passenger << " from waiting lsit's reservation done successfully." << endl;

            ReserveSeat(passenger, flightNum, "economy");
        }
        
    }

    // change reservation - check availability + cancel old + create new + update customer + update waiting lsit
    void ChangeReservation(int customerID, int oldFlightNum, int newFlightNum, string ticketType)
    {
        Flight* oldFlight = flights.searchFlight(oldFlightNum);

        if (!oldFlight)
        {
            cout << "Old flight does not exist. " << endl;
            return;
        }

        Flight* newFlight = flights.searchFlight(newFlightNum);

        if (!newFlight)
        {
            cout << "New flight does not exist. " << endl;
            cout << "Change of reservation failed" << endl;
            return;
        }

        if (!oldFlight->getPassengers().search(customerID)) // does customer have a reservation?
        {
            cout << "No reservation for old flight found." << endl;
            cout << "Change of reservation failed" << endl;
            return;
        }

        if (!newFlight->seatsAvailable()) // are there seats available for new flight?
        {
            cout << "No seats available in new flight." << endl;
            cout << "Change of reservation failed" << endl;
            return;
        }

        CancelReservation(customerID, oldFlightNum);
        ReserveSeat(customerID, newFlightNum, ticketType);

        cout << "Change of reservation was successfull." << endl;

    } 


    // MENUE // 

    void handleFlightReservation()
    {
        int choice;
    
        do
        {
            cout << "\n==== Flight Reservation ====\n"
                 << "1. Search for flights" << endl
                << "2. Reserve a flight" << endl
                << "3. Cancel Reservation" << endl
                << "4. Change Reservation" << endl
                << "5. Back to main menue" << endl
                << "=============================" << endl;

            cout << "Enter your choice: ";

            cin >> choice;

            switch (choice)
            {
                case 1:
                {   string des;
                    cout << "Enter destination: ";
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    getline(cin, des);
                    SearchFlightsByDestination(des);
                    break;
                }

                case 2:
                {
                    int customerID, flightNum;
                    string ticketType;
                    cout << "Enter customer ID: ";
                    cin >> customerID;
                    cout << "Enter flight Number: ";
                    cin >> flightNum;
                    cout << "Enter ticket Type: (Economy/Business)";
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    getline(cin, ticketType);
                    ReserveSeat(customerID, flightNum, ticketType);
                    break;
                }

                case 3:
                {
                    int customerID, flightNum;
                    cout << "Enter customer ID: ";
                    cin >> customerID;
                    cout << "Enter flight Number: ";
                    cin >> flightNum;
                    CancelReservation(customerID, flightNum);
                    break;
                }

                case 4: 
                {
                    int customerID, flightNum, newFlight;
                    string ticketType;
                    cout << "Enter customer ID: ";
                    cin >> customerID;
                    cout << "Enter current flight Number: ";
                    cin >> flightNum;
                    cout << "Enter new flight Number: ";
                    cin >> newFlight;
                    cout << "Enter ticket Type: (Economy/Business)";
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                    getline(cin, ticketType);
                    ChangeReservation(customerID, flightNum, newFlight, ticketType);
                    break;
                }

                case 5:
                    break;

                default:
                    cout << "Invalid chocie. Please try again. \n";

            }
        } while (choice != 5);
    }

    void handleCustomerManagement()
    {
        int choice;
    
        do
        {
            cout << "\n==== Customer Management ====\n"
                 << "1. Add customer" << endl
                 << "2. Update customer" << endl
                 << "3. Delete customer" << endl
                 << "4. View customer profile" << endl
                 << "5. Back to main menue" << endl
                 << "=============================" << endl;

            cout << "Enter your choice: ";

            cin >> choice;

            switch (choice)
            {
                case 1:
                {
                    NewCustomer();
                    break;
                }

                case 2:
                {
                    UpdateCustomer();
                    break;
                }

                case 3:
                {
                    int customerID;
                    cout << "Enter customer ID: ";
                    cin >> customerID;
                    DeleteCustomer(customerID);
                    break;
                }

                case 4:
                {
                    int customerID;
                    cout << "Enter customer ID: ";
                    cin >> customerID;
                    ViewCustomerProfile(customerID);
                    break;
                }

                case 5: break;
                default: cout << "Invalid choice. Please try again. \n";
            }
        } while (choice != 5);
    }

    void handleFlightManagement()
    {
        int choice;
    
        do
        {
            cout << "\n==== Flight Managemtn ====\n"
                 << "1. Add flight" << endl
                 << "2. Update flight" << endl
                 << "3. Delete flight" << endl
                 << "4. View flights" << endl
                 << "5. Back to main menue" << endl
                 << "=============================" << endl;

            cout << "Enter your choice: ";

            cin >> choice;

            switch (choice)
            {
                case 1: 
                {
                    AddNewFlight();
                    break;
                }

                case 2:
                {
                    int flightNum;
                    cout << "Enter flight number: ";
                    cin >> flightNum;
                    UpdateFlight(flightNum);
                    break;
                }

                case 3:
                {
                    int flightNum;
                    cout << "Enter flight number: ";
                    cin >> flightNum;
                    DeleteFlight(flightNum);
                    break;
                }

                case 4:
                {
                    DisplayAllFlights();
                    break;
                }

                case 5: break;
                default: cout << "Invalid chocie. Please try again. \n";


            }
        } while (choice != 5);
    }

    void systemRun()
    {
        int choice;

        do
        {
            cout << "\n==== Flight Reservation System ===\n"
                 << "1. Flight Rervation \n"
                 << "2. Customer Management \n"
                 << "3. Flight Management \n"
                 << "4. Setup System Data \n"
                 << "5. Save Data \n"
                 << "6. Exit \n"
                 << "=====================================" << endl
                 << "Enter your choice: ";

            cin >> choice; 

            switch (choice)
            {
                case 1:
                    handleFlightReservation();
                    break;

                case 2:
                    handleCustomerManagement();
                    break;

                case 3:
                    handleFlightManagement();
                    break;
                
                case 4: 
                    loadData();
                    cout << "System data laoded successfully." << endl;
                    break;
            
                case 5:
                    saveData();
                    cout << "Data saved successfully" << endl;
                    break;

                case 6:
                    cout << "Exiting system..." << endl;
                    break;

                default:
                    cout << "Invalid choice. Please try again. \n";
            }
        } while (choice != 6);
    }

};

int main()
{
   cout << "Welcome to flight reservation system... Starting..." << endl;
   FlightReservationSystem system;
   system.systemRun();
   cout << "System shutdown." << endl;

   return 0;

}