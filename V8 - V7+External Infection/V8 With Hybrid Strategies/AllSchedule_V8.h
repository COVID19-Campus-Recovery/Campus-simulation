#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include"Parameters_V8.h"
#include <random>

using namespace std;

class Class {
public:
	string CourseCode;
	double TranRate;   // Corresponding rate of transmission in this class
	double TranProb;   // Corresponding probability of transmission in this class based on trasnmission rate 
	int IfTraced;      // 1: there was infectious students in this class thus need to conduct contact tracing for every students in this class  0: on the contrart 
};

class Student {
public:
    int studentID;
	int condition;   //0 susceptible, 1 infected....
	int SE;  //the day that this student started being infected
	int ST;  //the day that this student was tested 
	int SQ;  //the day that this student started being quarantined
	int TestPriority;    //The priority of test for this student
	bool ifQuarantine;   //1: this student will quarantine him/herself as required  0: On the contrary 
	bool ifOncampus;     //if this student live on campus
	bool ifTested;       // if this student have ever been tested positive (thus don't need to be tested again during the remaining semester)
	bool ifWaitResult;   // if this student is waiting for testing results (thus don't need to repeat test during the waiting process)
	bool ifPositive;     // if this student is tested positive
	bool ifGreeklife;    // is this student is super social (25% students are super social)
	map<int,int> NumClasses;  // for each student int : SeqNum  -> int: Number of classes this student will attend at that day
	double TransCoe;     //The relative coefficient of transmission rate out of class for this student (depend on this student's out of class time today)
	map<int,vector<Class*> > InClassToday;  //include all the courses the students will attend today
};

map<Class*,vector<Student*> > ClassStudentsTodayMap; //Map the corresponding students today for each class
map<string,Class*> ClassMap; //Map the corresponding Class and its information via string(CourseCode)
map<int,Student*> StudentMap; //Map the corresponding Student and his/her information via int(StudentID)
vector<Student*> AllStudents; //All students vector
vector<Student*> StudentsOnCampus; //All students on campus vector
vector<Class*> AllClasses; //All Classes this semester
map<int,vector<Class*> > ClassesToday; //All classes today

int NSOn; //Total number of studentes live on campus in the semester
int TNS; //Total number of studentes in the semester
int TNC; //Total number of course in the semester
int CumuCase;  //cumulative number of students have ever been exposed
int CumuQua;  //cumulative number of students have ever been quarantine
int CumuHospitalization; //cumulative number of students have ever been hospitalized
int CountTraced;  //Number of students were traced today (have contacted with those infectious students)
int CumuNumSym; //cumulative number of students have ever been symtomatically infected
 
vector<string> filenameAM;   //record name of input files


string outputfilename;
std::ofstream DaySummary;

std::random_device rd;                  //define the random number with uniform distribution between 0-1
std::default_random_engine ge(rd());
std::uniform_real_distribution<double> du(0.0,1.0);

string filenameAll="AffiliationMatrixAll.csv";
string filenameOnCampus="AffiliationMatrixOnCampus.csv";
bool OpenFiles() {
	std::ifstream comFileAll(filenameAll.c_str());
	if (!comFileAll.is_open()) {
		cerr << "error opening file" << endl;
	}
    string headers;
	string omit;
	string ID,classname;
	getline(comFileAll,omit,',');
	getline(comFileAll,headers);
	stringstream CC(headers);
	while(getline(CC,classname,','))
    {
        Class* c=new Class();
        if (classname[classname.size()-1]=='\r') {classname.erase(classname.end()-1);}
        AllClasses.push_back(c);
        c->CourseCode=classname;
        ClassMap[classname]=c;	
    }

	while(getline(comFileAll,headers))
	{
		stringstream ss(headers);
		getline(ss,ID,',');
		if (ID[ID.size()-1]=='\r') {ID.erase(ID.end()-1);}
		Student* s=new Student();
		s->studentID=stoi(ID);
		s->ifOncampus=0;
	    AllStudents.push_back(s);
	    StudentMap[stoi(ID)]=s;		
	}
	comFileAll.close();
	
	std::ifstream comFile(filenameOnCampus.c_str());
	if (!comFile.is_open()) {
		cerr << "error opening file" << endl;
	}
	getline(comFile,headers);
	while(getline(comFile,headers))
	{
		stringstream ss(headers);
		getline(ss,ID,',');
		Student* stu=StudentMap[stoi(ID)];
		stu->ifOncampus=1;
		StudentsOnCampus.push_back(stu);	
	}
	comFile.close();
	
	TNS=AllStudents.size();
	TNC=AllClasses.size();
	NSOn=StudentsOnCampus.size();
	cout<<"Total Number of Students"<<' ';  cout<<TNS<<endl;
	cout<<"Total Number of Students Oncampus"<<' ';  cout<<NSOn<<endl;
	cout<<"Total Number of Courses"<<' ';  cout<<TNC<<endl;
	
	return 0;
}





