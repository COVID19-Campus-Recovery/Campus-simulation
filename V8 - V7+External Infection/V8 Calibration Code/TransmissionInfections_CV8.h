#include <iostream>

using namespace std;
bool InclassInfections(Student* stu,int j,int DayNum)
{ 
	bool IfExp=0;
	bool ifSkip=0;  //to decide whether a student have been infected so need to skip the for loop
	for (Class* c:stu->InClass)
	{
	    if((c->NI!=0)&&(c->DayoftheWeek[j]==1)) 
	    {
	         double RandomNumber = du(ge);
             if(RandomNumber<=c->TranProb)  
             {
	            stu->condition=1;
	            stu->SE=DayNum+1;
				IfExp=1;
	            ifSkip=1;		
             }
	    }
	    if(ifSkip) {break;}
	}
	return IfExp;
}

bool OutclassInfections(Student* stu,int j,int DayNum,int NumIP, int NumIS, int NumIA)
{ 
	bool IfExp=0;
	stu->NumClasses=0;
	stu->TransCoe=0;
	for (Class* c:stu->InClass)
	{
		if(c->DayoftheWeek[j]==1)
		{
			int temp=stu->NumClasses;
			stu->NumClasses=temp+1;
		}
	}
	if ((stu->ifGreeklife==1)&&((j==DaysoftheWeek-2) ||(j==DaysoftheWeek-3)||(j==DaysoftheWeek-4)))
	{
		stu->TransCoe= alpha*(24-3-1.5*stu->NumClasses)/(1.5);
	}
	else 
	{
		stu->TransCoe= alpha*(24-1.5*stu->NumClasses)/(1.5);
	}
	double InfRateOut=stu->TransCoe*lambda_s*NumIS+stu->TransCoe*lambda_p*NumIP+stu->TransCoe*lambda_a*NumIA;
	double InfProbOut=1-exp(-InfRateOut);
	double RandomNumber = du(ge);
    if(RandomNumber<=InfProbOut)  
    {
        stu->condition=1;
        stu->SE=DayNum+1;
		IfExp=1;		
    }
	return IfExp;
}

bool OffCampusInfections(Student* stu,int j,int DayNum,int NumIP, int NumIS, int NumIA)
{ 
	bool IfExp;
	IfExp=0;
	/*
	stu->TransCoe=0;
	if (stu->ifGreeklife==1) {stu->TransCoe= alpha*(24--3-1.5*stu->NumClasses)/(1.5);}
	if (stu->ifGreeklife==0) {stu->TransCoe= alpha*(24-1.5*stu->NumClasses)/(1.5);}
	stu->TransCoe= 0*(24-1.5*stu->NumClasses)/(1.5);
	double InfRateOut=stu->TransCoe*lambda_s*NumIS+stu->TransCoe*lambda_p*NumIP+stu->TransCoe*lambda_a*NumIA;
	double InfProbOut=1-exp(-InfRateOut);
	*/
	double RandomNumber = du(ge);
    if(RandomNumber<1-exp(-ExternalRate))  
    {
        stu->condition=1;
        stu->SE=DayNum+1;
		IfExp=1;		
    }
	return IfExp;
}

