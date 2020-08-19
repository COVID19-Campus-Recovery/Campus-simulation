#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <random>
#include "ContactsTracing_V8.h"


using namespace std;



bool TestingProcess(Student* stu ,int DayNum) 
{	
	stu->ST=DayNum;
	double RandomNumber = du(ge);
	switch(stu->condition)
	{
		case 0:  
		{
            stu->ifWaitResult=1;
			if(RandomNumber>TNR) //false positive 
			{
				stu->ifPositive=1;
			}
			break;
		}
		case 1:  
		{
			stu->ifWaitResult=1;
			if(RandomNumber<=TPR) //true positive 
			{
				stu->ifPositive=1;
			}
			break;
		}
		case 2:  
		{
			stu->ifWaitResult=1;
			if(RandomNumber<=TPR) //true positive 
			{
				stu->ifPositive=1;
			}
			break;
		}
		case 3:  
		{
			stu->ifWaitResult=1;
			if(RandomNumber<=TPR) //true positive 
			{
				stu->ifPositive=1;
			}
			break;
		}
		case 4:  
		{
			stu->ifWaitResult=1;
			if(RandomNumber<=TPR) //true positive 
			{
				stu->ifPositive=1;
			}
			break;
		}
		case 5:  {break;}
		case 6:  {break;}
		case 7:  {break;}
		case 10:  
		{
			stu->ifWaitResult=1;
			if(RandomNumber>TNR) //false positive 
			{
				stu->ifPositive=1;
			}
			break;
		}
	}
	return 0;
}

bool TestingResult(Student* stu ,int DayNum) 
{					
	if (DayNum-(stu->ST)==TD)
	{
		stu->ifWaitResult=0;
		if (stu->ifQuarantine==1)
		{
			if (stu->ifPositive==1)
			{
				stu->ifTested=1; 
				ContactsTracing(stu,stu->SQ);
				CountTraced=CountTraced+1;
			}
			if (stu->ifPositive==0)
			{
				stu->ifQuarantine=0;
				stu->SQ=0; 
			}
		}
		else if (stu->ifQuarantine==0)
		{
			if (stu->ifPositive==1)
			{
				stu->ifTested=1; 
				ContactsTracing(stu,DayNum);
				CountTraced=CountTraced+1;
				double RandomNumber = du(ge);
				if(RandomNumber<=PQ) 
				{
					if(stu->ifQuarantine==0)
					{
						stu->ifQuarantine=1; 
						CumuQua=CumuQua+1;
						stu->SQ=DayNum;
					}
				}
			}
		}
	}
	return 0;
}

bool Quarantine(Student* stu ,int DayNum) 
{					
	if(    (DayNum-(stu->SQ)>=QD)&&(stu->condition!=1) &&(stu->condition!=2) &&(stu->condition!=3) &&(stu->condition!=4) &&(stu->condition!=6)    )
	{
		stu->ifQuarantine=0;
	}
	return 0;
}