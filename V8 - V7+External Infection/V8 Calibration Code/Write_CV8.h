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

bool WriteRNaught(int DayNum,int NumSuc, int NumExp) {

	double numerator=NS-NumSuc-1.00;
	double denominator=NS-NumSuc-NumExp-0.00;
	double RNaughtValue=numerator/denominator;
	TotalRNaugut=TotalRNaugut+RNaughtValue;
	TotalDays=TotalDays+DayNum;
	CountRNaught=CountRNaught+1;    
	RNaught.open(outputfilename2,std::ios::app);
	RNaught<<RNaughtValue<<',';
	RNaught.close();
	return 0;
}

bool WriteDaySummary(int CumuCase, int CumuNumSym,int DayNum,int NewExp) {
	int NumExp=0; //# Exposed
	int NumSuc=0; //# Susceptible
	for (auto it = allStudent.begin(); it != allStudent.end(); it++)
	{
	    switch(it->second->condition){
		    case 0:  {NumSuc=NumSuc+1;break;}
		    case 1:  {NumExp=NumExp+1;break;}
		    case 2:  {break;}
		    case 3:  {break;}
		    case 4:  {break;}
		    case 5:  {break;}
		    case 6:  {break;}
		    case 7:  {break;}
	    }
	}
	if ( NumSuc < NS*(1-PTC) )
	 {
		IfStopR=1;
		WriteRNaught(DayNum,NumSuc,NumExp);
	 }
	return 0;
}



/*bool WriteDaySummaryIndividualHeader(int RunNum) {
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
	DaySummaryInv<<"# Dead"<<'\r';
	DaySummaryInv.close();
	return 0;
}


bool WriteDaySummaryFile() {
	DaySummary.open(outputfilename2,std::ios::app);
	for (int i=0;i<=NumberofWeeks*DaysoftheWeek;i++)
	{
		DaySummary<<"Day"<<' ';DaySummary<<i<<',';
		for (int j=0;j<10;j++)
		{
			DaySummary<<DaySummaryMap[i][j]/RunTimes<<',';
		}
		DaySummary<<DaySummaryMap[i][10]/RunTimes<<'\r';
	}
	DaySummary.close();
	return 0;
}*/







