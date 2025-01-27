#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <string>
#include <windows.h>

using namespace std;

mutex mutex1;

void greenLight();
void yellowLight();
void redLight();
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE); //Just for the purposes of coloring the console text :)

void greenLight(const string& direction){
            lock_guard<mutex> lock(mutex1);
            SetConsoleTextAttribute(h,10);
            if (direction == "East-West"){
            	cout<<"                              ";
			}
            cout << "	GREEN light\n";
        }
        
void yellowLight(const string& direction){
            lock_guard<mutex> lock(mutex1);
            SetConsoleTextAttribute(h,6);
            if (direction == "East-West"){
            	cout<<"                              ";
			}
            cout << "	YELLOW light\n";
        }
        
void redLight(const string& direction){
            lock_guard<mutex> lock(mutex1);
            SetConsoleTextAttribute(h,12);
            if (direction == "East-West"){
            	cout<<"                              ";
			}
            cout << "	RED light\n";
        }

void simulateTrafficLight(const string& direction, int green, int yellow, int red) {
    while (true) {
        
        if (direction == "North-South"){
            //GREEN
            greenLight(direction);
            this_thread::sleep_for(chrono::seconds(green));
            
            //YELLOW
            yellowLight(direction);
            this_thread::sleep_for(chrono::seconds(yellow));
            
            //RED
            redLight(direction);
            this_thread::sleep_for(chrono::seconds(red));
        }
        
        else{
            //RED
            redLight(direction);
            this_thread::sleep_for(chrono::seconds(red)); 
            
            //GREEN
            greenLight(direction);
            this_thread::sleep_for(chrono::seconds(green));
            
            //YELLOW
            yellowLight(direction);
            this_thread::sleep_for(chrono::seconds(yellow));
        }
    }
}

int main() {
	int green = 0, yellow = 0, red;
	
	while(green <= 0){
		cout << "Green Light duration: ";
		cin >> green;
	}
	
	while(yellow <= 0){
		cout << "Yellow Light duration: ";
		cin >> yellow;
	}
	
	system("cls");
	
	cout << "Green Light duration: " << green << endl;
	cout << "Yellow Light duration: " << yellow << endl;
	red = green + yellow;
	cout << "Red Light duration: " << red << endl << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "	NORTH-SOUTH		EAST-WEST			" << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	
	
    thread northSouth(simulateTrafficLight, "North-South", green, yellow, red);
    thread eastWest(simulateTrafficLight, "East-West", green, yellow, red);

	northSouth.detach();
    eastWest.detach();

	this_thread::sleep_for(chrono::seconds(30)); // Let the simulation run for 30 seconds
    return 0;
}
