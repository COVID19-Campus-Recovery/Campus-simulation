#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <random>


using namespace std;



bool StateTransition(vector<Student*>& StudentInfected,int NumToday) 
{
    for(Student* stu: StudentInfected)
   {
	    switch(stu->condition)
	    { 
		    case 1:  {
				if (NumToday-(stu->SE)==ED){
				    stu->condition=2;
				}
				break;
			}
			
		    case 2:  {
				if (NumToday-(stu->SE)==PD+ED){
					double RandomNumber = du(ge);
					if(RandomNumber<=PA){
						stu->condition=3;
					}
					if(RandomNumber>PA){
						stu->condition=4;
						stu->TestPriority=3;
						CumuNumSym=CumuNumSym+1;
						double RandomNumber = du(ge);
						if((RandomNumber<=PQ)&& (stu->ifQuarantine==0))
						{
							stu->ifQuarantine=1; 
							CumuQua=CumuQua+1;
							stu->SQ=NumToday;
						}
					}
				}
				break;
			}
			
			case 3:  {
				if (NumToday-(stu->SE)==PD+ED+AD){
				    stu->condition=5;
				}
				break;
			}
			
			case 4:  {
				if (NumToday-(stu->SE)==ED+PD+SD){
					double RandomNumber = du(ge);
					if(RandomNumber<=PH){
						stu->condition=6;
						CumuHospitalization=CumuHospitalization+1;
						if(stu->ifQuarantine==0) 
						{
							stu->ifQuarantine=1; 
							CumuQua=CumuQua+1;
							stu->SQ=NumToday;
						}	
					}
					else if(RandomNumber>PH){
						stu->condition=5;
					}
				}
				break;
			}
			
			case 6:  {
				if (NumToday-(stu->SE)>=ED+PD+SD+HD) 
				{
					double RandomNumber = du(ge);
					if(RandomNumber<=PDE){
						stu->condition=7;
						stu->ifQuarantine=0;
						TNS=TNS-1;
						NSOn=NSOn-1;
					}
					if(RandomNumber>PDE){
						stu->condition=5;
					}
				}
				break;
			}								
		}
   }
	return 0;
}