#include <iostream>

using namespace std;

bool SamplingInfectionsWeekdays(Student* stu,vector<Student*>& StudentSampledFrom,int DayNum)
{   
		int IfExp=0;
		int NW;
        bool ifSkip=0;  //to decide whether a student have been infected so need to skip the for loop
        vector<int>* p;
        int NumofThisStu=FindIndex_1(StudentSampledFrom, stu);  //find the index of stu in the vector<Student*> for class c
		if(StudentSampledFrom.size()>NW_S) {NW=NW_S;}
		else if (StudentSampledFrom.size()<=NW_S) {NW=StudentSampledFrom.size()-1;}
        p=Sample(NW,0,StudentSampledFrom.size(),NumofThisStu);  // generate NW different students during weekends (can not be this stu)
		double RandomNumber = du(ge);
        for (int i=0;i<NW;i++)     
        {
	        switch (StudentSampledFrom[p->at(i)]->condition)       
	        {
		        case 0:  {break;}
		        case 1:  {break;}
		        case 5:  {break;}
		        case 6:  {break;}
		        case 7:  {break;}
		        case 10:  {break;}
		        case 2:  {
					if(StudentSampledFrom[p->at(i)]->ifQuarantine==1) {break;}
					if(StudentSampledFrom[p->at(i)]->ifQuarantine==0)
					{
			             if(RandomNumber<=Pp)  
			             {
				            stu->SE=DayNum+1;
							stu->condition=1;
							IfExp=1;
				            ifSkip=1;
			             }
				         break;
					}
			    }
		        case 3:  {
					if(StudentSampledFrom[p->at(i)]->ifQuarantine==1) {break;}
				    if(StudentSampledFrom[p->at(i)]->ifQuarantine==0)
					{
			             if(RandomNumber<=Pa)  
			             {
				            stu->SE=DayNum+1;
							stu->condition=1;
							IfExp=1;
				            ifSkip=1;
			             }
				         break;
					}
			    }
		        case 4:  {
			         if(StudentSampledFrom[p->at(i)]->ifQuarantine==1) {break;}
			         if(StudentSampledFrom[p->at(i)]->ifQuarantine==0)
					 {
			             if(RandomNumber<=Ps) 
			             {
				            stu->SE=DayNum+1;
							stu->condition=1;
							IfExp=1;
				            ifSkip=1;
			             }
				         break;
			         }
			    }
		    } 
		    if(ifSkip) {break;}  
        }
	delete p;
	return IfExp;
}