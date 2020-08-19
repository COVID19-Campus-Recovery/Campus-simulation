#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <random>

using namespace std;

bool OpenEverydayFile(const string& filename,int NoWeek,int NumberData) {
	int ifToday=10+(NoWeek%4)+1;
	std::ifstream comFile(filename.c_str());
	if (!comFile.is_open()) {
		cerr << "error opening file" << endl;
	}
    string headers;
	string omit;
	string ID,classname;
	int NumClass;
	getline(comFile,omit,',');
	getline(comFile,omit,',');
	getline(comFile,omit,',');
	getline(comFile,omit,',');
	getline(comFile,omit,',');
	getline(comFile,headers);
	stringstream CC(headers);
	while(getline(CC,classname,','))
    {
	    if (classname[classname.size()-1]=='\r') {classname.erase(classname.end()-1);}
	    ClassesToday[NumberData].push_back(ClassMap[classname]);
    }
    while(getline(comFile,headers))
    { 
	    stringstream ss(headers);
	    for(int j=0;j<5;j++) 
	    {
		    getline(ss,omit,',');
		    if(j==(NoWeek%4)) {NumClass=stoi(omit);}
		    if(j==4)  {ID=omit;}
		}
		Student* stu=StudentMap[stoi(ID)];
		stu->NumClasses[NumberData]=NumClass;
		for(int j=0;j<ClassesToday[NumberData].size();j++) 
		{
		    getline(ss,omit,',');
		    if (omit[omit.size()-1]=='\r') {omit.erase(omit.end()-1);}
		    if((stoi(omit)==ifToday)||(stoi(omit)==4)) 
		    {
			    Class* cla=ClassesToday[NumberData][j];
			    stu->InClassToday[NumberData].push_back(cla);
			}
		}
    }  
    comFile.close();
	return 0;
}




