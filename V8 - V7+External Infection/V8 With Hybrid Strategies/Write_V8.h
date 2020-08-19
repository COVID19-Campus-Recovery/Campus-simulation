#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <random>

using namespace std;

map<int,vector<double> > DaySummaryMap;

bool WriteDaySummaryInv(int CumuHospitalization,int CountTraced,int CumuQua, int CumuCase, int CumuNumSym,int DayNum,int NewExp,int k) {
	int NumExp=0; //# Exposed
	int NumRec=0; //# Recovered
	int NumAsym=0; //# Asympotomatically Infected
	int NumSym=0; //# Sympotomatically Infected
	int NumHos=0; //# Hospitalization
	int NumDead=0; //# Dead
	int NumSuc=0;
	int NumPre=0;
	int NumQua=0;
	double summary[15];
	string filename;   string suffix=".csv";  stringstream ss;       ss << k;      ss >> filename;    filename.append(suffix);
	std::ofstream DaySummaryInv;
	for (Student* stu:AllStudents)
	{
		if(stu->ifQuarantine==1) {NumQua=NumQua+1;}
	    switch(stu->condition){
		    case 0:  {NumSuc=NumSuc+1;break;}
		    case 1:  {NumExp=NumExp+1;break;}
		    case 2:  {NumPre=NumPre+1;break;}
		    case 3:  {NumAsym=NumAsym+1;break;}
		    case 4:  {NumSym=NumSym+1;break;}
		    case 5:  {NumRec=NumRec+1;break;}
		    case 6:  {NumHos=NumHos+1;break;}
		    case 7:  {NumDead=NumDead+1;break;}
		    case 10: {NumRec=NumRec+1;break;}
	    }
	}
	summary[0]=CumuCase;
	summary[1]=CumuNumSym;
	summary[2]=NewExp;
	summary[3]=NumSuc;
	summary[4]=NumExp;
	summary[5]=NumPre;
	summary[6]=NumRec;
	summary[7]=NumAsym;
	summary[8]=NumSym;
	summary[9]=NumHos;
	summary[10]=NumDead;
	summary[11]=NumQua;
	summary[12]=CumuQua;
	summary[13]=CumuHospitalization;
	summary[14]=CountTraced;
	DaySummaryInv.open(filename,std::ios::app);
	DaySummaryInv<<"Day"<<' '; DaySummaryInv<<DayNum<<',';
	for (int i=0;i<14;i++)
    {
	    DaySummaryInv<<summary[i]<<',';	
    }
    DaySummaryInv<<summary[14]<<'\r';	
    DaySummaryInv.close();
	if(k==0){
	    for (int i=0;i<=14;i++)
		   {
		       DaySummaryMap[DayNum].push_back(summary[i]);	
		   }
	}
	if(k!=0){
	    for (int i=0;i<=14;i++)
		   {
			   double temp=DaySummaryMap[DayNum][i];
		       DaySummaryMap[DayNum][i]=temp+summary[i];	
		   }
	}
	return 0;
}

bool WriteDaySummaryIndividualHeader(int RunNum) {
	string filename;  
	string suffix=".csv";
	stringstream ss;         
	ss << RunNum;                      
	ss >> filename;
    filename.append(suffix);
	std::ofstream DaySummaryInv;
	DaySummaryInv.open(filename,std::ios::app);
	DaySummaryInv<<"Day of the Semester"<<',';
	DaySummaryInv<<"# Cumulative Cases(Exposed)"<<',';
	DaySummaryInv<<"# Cumulative Symptomatically Infected"<<',';
	DaySummaryInv<<"# New Exposed"<<',';
	DaySummaryInv<<"# Susceptible"<<',';
	DaySummaryInv<<"# Exposed"<<',';
	DaySummaryInv<<"# Pre-Symptimatic"<<',';
	DaySummaryInv<<"# Recovered"<<',';
	DaySummaryInv<<"# Asymptomatically Infected"<<',';
	DaySummaryInv<<"# Symptomatically Infected"<<',';
	DaySummaryInv<<"# Hospitalization"<<',';
	DaySummaryInv<<"# Dead"<<',';
	DaySummaryInv<<"# Quarantine"<<',';
	DaySummaryInv<<"# Cumulative Quarantine"<<',';
	DaySummaryInv<<"# Cumulative Hospitalization"<<',';
	DaySummaryInv<<"# Contact Traced"<<'\r';
	DaySummaryInv.close();
	return 0;
}

bool WriteAverageHeader() {
	DaySummary.open(outputfilename,std::ios::app);
	DaySummary<<"Day of the Semester"<<',';
	DaySummary<<"# Cumulative Cases(Exposed)"<<',';
	DaySummary<<"# Cumulative Symptomatically Infected"<<',';
	DaySummary<<"# New Exposed"<<',';
	DaySummary<<"# Susceptible"<<',';
	DaySummary<<"# Exposed"<<',';
	DaySummary<<"# Pre-Symptimatic"<<',';
	DaySummary<<"# Recovered"<<',';
	DaySummary<<"# Asymptomatically Infected"<<',';
	DaySummary<<"# Symptomatically Infected"<<',';
	DaySummary<<"# Hospitalization"<<',';
	DaySummary<<"# Dead"<<',';
	DaySummary<<"# Quarantine"<<',';
	DaySummary<<"# Cumulative Quarantine"<<',';
	DaySummary<<"# Cumulative Hospitalization"<<',';
	DaySummary<<"# Contact Traced"<<'\r';
	DaySummary.close();
	return 0;
}


bool WriteAverage() {
	DaySummary.open(outputfilename,std::ios::app);
	for (int i=0;i<=NumberofWeeks*DaysoftheWeek;i++)
	{
		DaySummary<<"Day"<<' ';DaySummary<<i<<',';
		for (int j=0;j<14;j++)
		{
			DaySummary<<DaySummaryMap[i][j]/RunTimes<<',';
		}
		DaySummary<<DaySummaryMap[i][14]/RunTimes<<'\r';
	}
	DaySummary.close();
	return 0;
}





