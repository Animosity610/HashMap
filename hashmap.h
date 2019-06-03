#ifndef HASHMAP_H
#define HASHMAP_H
#include <list>
#include <string>

using namespace std;

class HashNode
{
	public:
		string key;
		string value;
	public:
		HashNode(string key, string value)
		{
			this->key = key;
			this->value = value;
		}
		string getKey()
		{
			return this->key;
		}
		void setValue(string value)
		{
			this->value = value;
		}
		string getValue()
		{
			return this->value;
		}

};

class HashMap
{
	private:
		list<HashNode> *buckets;		// Array of Pointers to Hash Nodes
		int size;					//Current Size of HashMap
		int capacity;				// Total Capacity of HashMap
	public:
		HashMap(int capacity);
		int hashCode(const string key);
		void insert(const string key, const string value);
		string search(const string key);
		string value(const string key);
		void searchall(const string key);
		void remove(const string key);
		int getSize();
		~HashMap();

};

#endif