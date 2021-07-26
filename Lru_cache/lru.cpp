#include<iostream>
#include<list>
#include<unordered_map>
using namespace std;

//Node to store thr data (linked list)
class Node{
public:
	string key;
	int value;
	Node(string key, int value)
	{
		this->key = key;
		this->value = value;
	}
};

//LRU Cache Data structure
cass LRUCache{
public:
	int maxSize;
	list<Node> l;
	unordered_map<string, list<Node>:: iterator> m;
	LRUCache(int maxSize)
	{
		this->maxSize = maxSize > 1 ? maxSize : 1;
	}
	void insertKeyValue(string key, int value)
	{
		//2nd Case
		if(m.count(key)!=0)
		{
			//replace old value and update
			auto it = m[key];
			it->value = value;
		}
		else
		{
			//check if cache is full or not
			//remove the least recently used item from cache
			if(l.size() == maxSize)
			{
				Node last = l.back();
				m.erase(last.key); //remove from hashmap
				l.pop_back(); //remove from Linked list
			}
			Node n(key,value);
			l.push_front(n);
			m[key] = l.begin();
		}
	}

	int* getValue(string key)
	{
		if(m.count(key)!=0)
		{
			auto it = m[key];
			int value = it->value;
			l.push_front(*it);
			l.erase(it);
			m[key] = l.begin();
			return &l.begin()->value;  //Now here we need to return address of this value but this is a local variable that is being destroyed
					// now think that we have the l.begin()->value
		}
		return NULL; //if the key is not present then return NULL for this return type of function should be a pointer.
	}

	string mostRecentKey()
	{
		return l.front().key;
	}

};

int main()
{
	LRUCache lru(3);
	lru.insertKeyValue("mango",10);
	lru.insertKeyValue("apple",20);
	lru.insertKeyValue("mango",30);
	cout<< lru.mostRecentKey() <<endl;
	lru.insertKeyValue("mango",40);
	cout<< lru.mostRecentKey() <<endl;
	lru.insertKeyValue("banana",20);

	if(lru.getValue("apple")==NULL)
		cout<< "apple doesn't exist";

	if(lru.getValue("guava")==NULL)
		cout<< "guava doesn't exist";

	if(lru.getValue("banana")==NULL)
		cout<< "banana doesn't exist";
	
	if(lru.getValue("mango")==NULL)
		cout<< "mango doesn't exist";

}
