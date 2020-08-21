#include <iostream>
#include"Sample_V8.h"

using namespace std;

bool SamplingInfectionsWeekends(Student* stu,vector<Student*>& StudentSampledFrom,int DayNum)
{   
            bool IfExp=0;
            int NW;
	        bool ifSkip=0;  //to decide whether a student have been infected so need to skip the for loop
	        vector<int>* p;
	        int NumofThisStu=FindIndex_1(StudentSampledFrom,stu);  //find the index of stu 
            if(stu->ifGreeklife==1)  
            {
                if(StudentSampledFrom.size()>NW_H) {NW=NW_H;}
                if(StudentSampledFrom.size()<=NW_H) {NW=StudentSampledFrom.size()-1;}
            }
            else if(stu->ifGreeklife==0)  
            {
                if(StudentSampledFrom.size()>NW_L) {NW=NW_L;}
                if(StudentSampledFrom.size()<=NW_L) {NW=StudentSampledFrom.size()-1;}
            }
	        p=Sample(NW,0,StudentSampledFrom.size(),NumofThisStu);  // generate NW different students during weekends (can not be this stu)
	        for (int i=0;i<NW;i++)     
	        {
		        switch ( StudentSampledFrom[p->at(i)] ->condition)       
		        {
			        case 0:  {break;}
			        case 1:  {break;}
			        case 5:  {break;}
			        case 6:  {break;}
			        case 7:  {break;}
                    case 10: {break;}
			        case 2:  {
                        if(StudentSampledFrom[p->at(i)]->ifQuarantine==1) {break;}
    				    if(StudentSampledFrom[p->at(i)]->ifQuarantine==0)
                        {
    				         double RandomNumber = du(ge);
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
    				         double RandomNumber = du(ge);
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
					         double RandomNumber = du(ge);
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