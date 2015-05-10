//STL Example
#include "windows.h"
#include <iostream>
#include <map>
#include <list>
#include <vector>
#include <queue>
#include <deque>
#include <string>
#include "main.h"

//Declare all of our externed containers and adaptors again
map<int, stlSTRUCT> testMap;
list<stlSTRUCT> myList;
vector<stlSTRUCT> myVector;
queue<string> myQueue;
deque<string> myDeque;

//Load from our INI
void LoadIni()
{
	char CurDir[_MAX_PATH];
	GetCurrentDirectoryA(sizeof(CurDir), CurDir);
	string ini_file = string(CurDir) + "\\STLExample.ini";

	testMap.clear();
	myList.clear();
	myVector.clear();
	if (myQueue.empty() != true)
	{
		queue<string> empty;
		std::swap(myQueue, empty); //This literally swaps all of the values in myQueue out with empty, which is an empty queue at all times, this is one of the only ways to properly clear memory from a queue.
	}
	myDeque.clear();

	INI_Reader ini;
	if (ini.open(ini_file.c_str(), false))
	{
		while (ini.read_header())
		{
			if (ini.is_header("MAP_EXAMPLE"))
			{
				stlSTRUCT mapExample;
				while (ini.read_value())
				{
					if (ini.is_value("id"))
					{
						mapExample.id = ini.get_value_int(0);
					}
					else if (ini.is_value("name"))
					{
						mapExample.name = ini.get_value_string();
					}
				}
				testMap[mapExample.id] = mapExample;
			}
			else if (ini.is_header("LIST_EXAMPLE"))
			{
				stlSTRUCT listStruct;
				while (ini.read_value())
				{
					if (ini.is_value("id"))
					{
						listStruct.id = ini.get_value_int(0);
					}
					else if (ini.is_value("name"))
					{
						listStruct.name = ini.get_value_string();
					}
				}
				myList.push_back(listStruct);
			}
		}
		ini.close();
	}
}

int PrintVal()
{

}