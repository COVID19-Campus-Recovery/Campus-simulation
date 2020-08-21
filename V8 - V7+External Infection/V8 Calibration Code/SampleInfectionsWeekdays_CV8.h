#include <iostream>

using namespace std;

int SamplingInfectionsWeekdays(Student* stu,vector<int>& StudentVector,int DayNum)
{   
			int IfExp=0;
			int NW;
	        bool ifSkip=0;  //to decide whether a student have been infected so need to skip the for loop
	        vector<int>* p;
	        int NumofThisStu=FindIndex_2(StudentVector, stu->studentID);  //find the index of stu in the vector<Student*> for class c
			NW=NW_S;
	        p=Sample(NW,0,StudentVector.size(),NumofThisStu);  // generate NW different students during weekends (can not be this stu)
			double RandomNumber = du(ge);
	        for (int i=0;i<NW;i++)     
	        {
		        switch (allStudent[ StudentVector[p->at(i)] ]->condition)       
		        {
			        case 0:  {break;}
			        case 1:  {break;}
			        case 5:  {break;}
			        case 6:  {break;}
			        case 7:  {break;}
			        case 2:  {
						if(allStudent[ StudentVector[p->at(i)] ]->ifQuarantine==1) {break;}
						if(allStudent[ StudentVector[p->at(i)] ]->ifQuarantine==0)
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
						if(allStudent[ StudentVector[p->at(i)] ]->ifQuarantine==1) {break;}
					    if(allStudent[ StudentVector[p->at(i)] ]->ifQuarantine==0)
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
				         if(allStudent[ StudentVector[p->at(i)] ]->ifQuarantine==1) {break;}
				         if(allStudent[ StudentVector[p->at(i)] ]->ifQuarantine==0)
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
	return IfExp;
}