#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include"Parameters_CV8.h"
#include <random>

using namespace std;

class Class {
public:
	string CourseCode;
	int DayoftheWeek[DaysoftheWeek]; // For example: MWF [1,0,1,0,1,0,0]  DaysoftheWeek=7
	int NI; // number of Infected (but not quarantine)
	int NT; // number of Total Students in the class
	double TranRate;
	double TranProb;
	//float CD;  class density 	
};



class Student {
public:
    int studentID;
	int condition;   //0 susceptible, 1 infected....
	vector<Class*> InClass;  //include all the courses the students have registered
	int SE;  //the day that the student started being infected
	bool ifQuarantine; //if the student start quarantine during Symtomatic Phase
	bool ifGreeklife;
	int NumClasses; 
	double TransCoe;
	//map<int, vector<Student> > InConnection;
	//housing data
	
};
map<string,Class*> allClass; //Map the corresponding Class and its information via string(CourseCode)
map<int,Student*> allStudent; //Map the corresponding Student and his/her information via int(StudentID)
map<int, vector<Class*> > classesInday; //Map all the classes in each day (M:0; T:1; W:2, ...)
map<Class*, vector<Student*> > classStudentMap; //Map all the students in a class
vector<string> ClassVector;
vector<int> StudentVector;


int NC; //Number of courses in the semester
int NS; //Total number of studentes registered in the semester
int CumuCase=0;
int CumuNumSym=0; //Total number of students have ever been symtomatically infected
vector<string> filenameAM;
int IfStopR; 
double TotalRNaugut=0;
double TotalDays=0;
int CountRNaught=0;

double GammaSet[5];
map<int, vector<double> > ParameterMap;

/*string outputfilename1="DayStudentMatrix.txt"; //outputfile1: Day*Student Matrix, record condition of each students on each day
std::ofstream DayStudent;*/


string outputfilename3="AverageRNaught.csv";  //outputfile2: Day*Summary Matrix. record # of students in different health conditions on each day
std::ofstream RNaughtSummary;
string outputfilename2="RNaught.csv";  //outputfile2: Day*Summary Matrix. record # of students in different health conditions on each day
std::ofstream RNaught;



std::random_device rd;
std::default_random_engine ge(rd());
std::uniform_real_distribution<double> du(0.0,1.0);

bool Openclassfile(const string& filename,int d) {
	std::ifstream comFile(filename.c_str());
	if (!comFile.is_open()) {
		cerr << "error opening file" << endl;
	}
	if(d==filenameAM.size()-1)
	{   
	    string headers;
		string omit;
		string ID,assignment,classname;
		getline(comFile,omit,',');
		getline(comFile,headers);
		stringstream CC(headers);
		while(getline(CC,classname,','))
        {
	        Class* c=new Class();
	        if (classname[classname.size()-1]=='\r') {classname.erase(classname.end()-1);}
	        ClassVector.push_back(classname);
	        c->CourseCode=classname;
	        allClass[classname]=c;
	        classesInday[d].push_back(c);	
        }
		while(comFile.good())
		{
			getline(comFile,headers);
			stringstream ss(headers);
			getline(ss,ID,',');
			Student* s=new Student();
			s->studentID=stoi(ID);
			s->condition=0;
			int count=0;
			while(getline(ss,assignment,','))
			{
				if (assignment[assignment.size()-1]=='\r') {assignment.erase(assignment.end()-1);}
				count=count+1;
				if( (bool)stoi(assignment) ) 
				{
					s->InClass.push_back(classesInday[d][count-1]);
				}
			}
			for (int i = 0; i < s->InClass.size(); i++) 
			{
				classStudentMap [ s->InClass[i] ].push_back(s);
			}
			StudentVector.push_back(stoi(ID));
			allStudent[stoi(ID)]=s;
		}
		NC=allClass.size();
		NS=allStudent.size();
		cout<<"Total Number of Students"<<' ';
		cout<<StudentVector.size()<<endl;
		cout<<"Total Number of Courses"<<' ';
		cout<<allClass.size()<<endl;
		int count=0;
	    for (auto it = classStudentMap.begin(); it != classStudentMap.end(); it++)
		{
			it->first->NT=it->second.size();
			it->first->NI=0;
		}
		
	}
	if(d!=filenameAM.size()-1)
	{
	    string headers;
		string omit;
		string ID,classname;
		getline(comFile,omit,',');
		getline(comFile,headers);
		stringstream CC(headers);
		while(getline(CC,classname,','))
	    {
		    if (classname[classname.size()-1]=='\r') {classname.erase(classname.end()-1);}
		    allClass[classname]->DayoftheWeek[d]=1;
	        classesInday[d].push_back(allClass[classname]);	
	    }

	}
	return 0;
}


bool ClearAll() {
	CumuCase=0;
	CumuNumSym=0; 
    for (auto it = allStudent.begin(); it != allStudent.end(); it++) 
    {		
	    it->second->condition=0;
	    double RandomNumber = du(ge);
	    if (RandomNumber<=PGreekLife) {it->second->ifGreeklife=1;}
	    if (RandomNumber>PGreekLife) {it->second->ifGreeklife=0;}	
    }
	for (auto it = allClass.begin(); it != allClass.end(); it++) 
	{
		it->second->NI=0;
		it->second->NT=classStudentMap[it->second].size();
	}
	return 0;
}


