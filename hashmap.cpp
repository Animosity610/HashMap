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

using namespace std::chrono;
using namespace std;


HashMap::HashMap(int capacity) //constructor
{
	buckets = new list<HashNode>[capacity];
	this->capacity = capacity;
	this->size = 0;
}

//=====================================================

int HashMap::hashCode(const string key) //hash function
{
	long hash=57;
	for(int i=0; i<key.length(); i++){
	hash += key[i]*pow(i,5); //times the power of 5 of the position
	}

	if(hash>=0)
		return hash%this->capacity;
	else
		return hash*(-1)%this->capacity; //be careful, some of the keys are negative
}

//================================================

void HashMap::insert(const string key, const string value) //insert function
{
	int index = hashCode(key);
	
	buckets[index].push_back(HashNode(key,value)); //push back in the buckets
	this->size++;
}

//===================================================

string HashMap::value(const string key){ //just to extract only the value
	int index = hashCode(key);
	for(auto it:buckets[index]) {
		if(it.getKey()==key)
			return it.getKey();
	}
	return 0;
}

//=====================================================

string HashMap::search(const string key) //search function
{
	int index = hashCode(key);
	int counter = 0;
	string s;

	for(auto it:buckets[index]) 
	{

		if(it.getKey()==key){
			return ""+it.getValue() + "\n" +to_string(counter)+" comparisons made."; //return function if found
		}
		counter++;
	}

	return "Record Not Found...!"; //return not found
}

//=====================================================

void HashMap::searchall(const string key) //function for allincity
{
	int index = hashCode(key);
	string s;

	if (buckets[index].empty()!=1) //to keep running through the buckets
		for(auto it:buckets[index]) 
		{	
			if(it.getKey()==key) //if find the same key, cout
			cout << it.getValue() <<endl;
		}
	else
		cout<< "Record Not Found...!" <<endl;

}

//=====================================================

void HashMap::remove(const string key) //remove function
{
	int index = hashCode(key);

	for(list<HashNode>::iterator it = buckets[index].begin(); it!=buckets[index].end(); ++it) 
	{
		if(it->getKey()==key) //if found, remove
		{
			buckets[index].erase(it);
			return;
		}
	}

	cout<<"Can not delete....Record Not Found... Please check your input!"<<endl; //if not found, cout not found
}

//===================================================

int HashMap::getSize()
{
	return this->size; //to check the size 
}

//=====================================================

HashMap::~HashMap()
{
	delete[] this->buckets;
}

