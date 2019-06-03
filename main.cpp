#include <cstdlib>
#include <string>
#include <cmath>
#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include <string.h>
#include <algorithm>
#include <chrono>
#include <queue>
#include "hashmap.h"

using namespace std;

int isSubstring(const string s1, const string s2) //function to check if a string is a substring of a string
{ 
    int M = s1.length(); 
    int N = s2.length(); 
  
    for (int i = 0; i <= N - M; i++) { //loop for each letter of the bigger string
        int j; 
  
        for (j = 0; j < M; j++) 
            if (s2[i + j] != s1[j]) //break if comparison shows not equal
                break; 
  
        if (j == M) //if equal, return the position of the first letter of the substring
            return i; 
    } 
  
    return -1; 
} 

int main(int argc, char *argv[]){

    string inputfilename ="";

    for (int i = 0; i < argc;i++){ //check input
        if (strcmp(argv[i],"-f")==0){
            i++;
            if (i >= argc){
                cout << "Error: -f should be followed by the input file!" <<endl;
                return 1;
            }
            inputfilename = argv[i];
        }
    }

    ifstream fin;
    fin.open(inputfilename); 	//open the file
    if (!fin){
        cout <<"Can not open the file..."<<endl;	 //check for file validity
        EXIT_FAILURE;
    }
    
    string line;
    getline(fin,line);
    HashMap myHashMap1(150041); 	//map that takes hotel,city as key
    HashMap myHashMap2(133013);		//map that takes city as key (for allincity function)

    while (!fin.eof()){		//input for map1
        string key1, key2, subvalue, key, value;
        getline(fin,key1,',');
        getline(fin,key2,',');
        getline(fin,subvalue);
        key = key1 + "," + key2; //concatenate to get keys
        value = key + "," + subvalue;
        cout << value << endl;
        myHashMap1.insert(key,value);
    }
    fin.close();

	fin.open(inputfilename);

	    while (!fin.eof()){		//input for map 2
        string key1, key2, subvalue, key, value;
        getline(fin,key1,',');
        getline(fin,key2,',');
        getline(fin,subvalue);
        key = key1 + "," + key2;
        value = key + "," + subvalue;
        // cout << "\t"<< key2 << endl;
        myHashMap2.insert(key2,value);
    }
    fin.close();
	
	list<string> hotels;	//we keep a linked list of all the values of the hotels (even when add or delete)
	list<string> hotelstmp; //tmp to assist in case 4
	string temp;

	fin.open(inputfilename);
		getline(fin,line);

		while(!fin.eof()){
			getline(fin,temp);
			hotels.push_back(temp); //initialize the hotel list
		}
	fin.close();

    cout << "\nmyHashmap size is: " << myHashMap1.getSize() <<endl; 		// show list size
    cout << "List of commands:\n - find k(hotel,city)\n - add s\n - delete k\n - dump f\n - allincity c\n - quit" <<endl;	//list commands


	string command; 

	//A list of accepted commands:
	string s1 = "find";
	string s2 = "add";
	string s3 = "delete";
	string s4 = "dump";
	string s5 = "allincity";

	while (true){	//input commandline
		cout << "\nPlease enter your command: ";
		getline(cin,command);
        if (command == "quit")
            break;
        int con = 0; //conditions for cases
        
		//get the value from checkin if string is in a string
        int x = isSubstring(s1,command);
        int y = isSubstring(s2,command);
        int z = isSubstring(s3,command);
        int q = isSubstring(s4,command);
        int p = isSubstring(s5,command);
        int sum = x+y+z+q+p;
		//if sum is not equal to -4, print error because only 1 command is allowed at a time.

        if (sum!=-4)
        cout<<"Error: Invalid command!!!"<<endl;
        else // set up the cases
            if (x == 0)
                con = 1;
            else if (y==0)
                con = 2;
            else if (z==0)
                con = 3;
            else if (q==0)
                con = 4;
            else if (p==0)
                con = 5;
                  
		switch (con){

			case (1):{ // Find k
				int pos0 = command.find(' ');
				string k = command.substr(pos0+1,command.length()-1); //remove Find from the key
				auto start = std::chrono::steady_clock::now();	//start the clock
				cout <<"\n"<<myHashMap1.search(k) << endl;
				auto stop = std::chrono::steady_clock::now();	//stop the clock
				double runtime = double (std::chrono::duration_cast<std::chrono::nanoseconds >(stop-start).count());	//difference of clock time	
				cout << "Time executed(s): " << runtime / 1e9 <<endl; //nanosecond = 1e^-9 second
				break;
			}

			case (2):{ // Add s
				if (count(command.begin(),command.end(),',')!=5) //check if s has enough elements by counting the commas
					cout <<"\nThe data provided is incorrect!" <<endl;
				
				else{
					int pos0 = command.find(' ');
					int pos1 = command.find(',');
					int pos2 = command.find(',',pos1+1);
					string key1 = command.substr(pos0+1,pos2-pos0-1); //Take out key1
					string key2 = command.substr(pos1+1,pos2-pos1-1);// Take out key2
					string value = command.substr(4); //Just the value without "Add"
					//cout << key1 <<endl;
					if (myHashMap1.search(key1)=="Record Not Found...!"){	//check if the value already exists
						myHashMap1.insert(key1,value); //Can't forget to add the key in both maps
						myHashMap2.insert(key2,value);
						hotels.push_back(value);	//add to the hotles list to keep track

						cout << "\nInput has been recorded."<<endl;
					}
					else
						cout << "\nWarning! Record existed!"<<endl;
				}
				break;
			}

			case (3):{ //Delete k
				int pos0 = command.find(' ');
				int pos1 = command.find(',');
				string key1 = command.substr(pos0+1);	//find key1 without delete
				string key2 = command.substr(pos1+1);	//find key2 without delete
				if (myHashMap1.search(key1)=="Record Not Found...!"){	//check if the value exists 
					cout << "\nWarning!No such ecord existed!"<<endl;
				}
				else
				{
					string value = myHashMap1.value(key1);	//just for the hotel list
					myHashMap1.remove(key1);	//always removes from both maps and hotel list
					myHashMap2.remove(key2);
					hotels.remove(value);
					cout << "\nRecord has been deleted!"<<endl;
				}
				
				break;
			}

			case (4):{ //dump f
				priority_queue <string,vector<string>,greater<string>> pqueue;	//create a min priority queue
				while (hotels.empty()!=1){	//run till hotels is empty
					string value = hotels.front();	//extract the line
					pqueue.push(value);	//add to pq
					hotelstmp.push_front(value);	//add to a tmp which will later become the original hotels list
					hotels.pop_front();
				}
				int pos0 = command.find(' ');
				string outputfile = command.substr(pos0)+".txt"; //take the input as filename
				ofstream myfile;
				myfile.open(outputfile);
				while (pqueue.empty()!=1){	//write into the newly created file
					// cout <<pqueue.top() <<endl;
					myfile << pqueue.top() +"\n"<<endl;
					pqueue.pop();
				}
				myfile.close();
				hotels = hotelstmp; //refill the original hotel list and clear the tmp list
				hotelstmp.clear();
				break;
			}

			case (5):{ //allinCity c
				int pos0 = command.find(' ');
				string key2 = command.substr(pos0+1);
				myHashMap2.searchall(key2); //print out all the hotels in the same city

			break;
			}
		}
	}

return 0;
}
