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
    for(Student* it1: StudentInfected)
   {
	    switch(it1->condition)
	    { 
		    case 1:  {
				if (NumToday-(it1->SE)==ED){
				    it1->condition=2;
				    for (Class* it2:it1->InClass) {it2->NI=it2->NI+1;} 
				}
				break;
			}
			
		    case 2:  {
				if (NumToday-(it1->SE)==PD+ED){
					double RandomNumber = du(ge);
					if(RandomNumber<=PA){
						it1->condition=3;
					}
					if(RandomNumber>PA){
						it1->condition=4;
						CumuNumSym=CumuNumSym+1;
						double RandomNumber = du(ge);
						if(RandomNumber<=PQ) {
							it1->ifQuarantine=(bool) 1; 
							for (Class* it2:it1->InClass) {it2->NI=it2->NI-1;it2->NT=it2->NT-1;} 
						}
						if(RandomNumber>PQ) { it1->ifQuarantine=(bool) 0;  }
					}
				}
				break;
			}
			
			case 3:  {
				if (NumToday-(it1->SE)==PD+ED+AD){
				    it1->condition=5;
				    for (Class* it2:it1->InClass) {it2->NI=it2->NI-1;} 
				}
				break;
			}
			
			case 4:  {
				if (NumToday-(it1->SE)==ED+PD+SD){
					double RandomNumber = du(ge);
					if(RandomNumber<=PH){
						it1->condition=6;
						if(!it1->ifQuarantine) {
							for (Class* it2:it1->InClass) {it2->NI=it2->NI-1;it2->NT=it2->NT-1;} 
						}
					}
					if(RandomNumber>PH){
						it1->condition=5;
						if(it1->ifQuarantine){
							for (Class* it2:it1->InClass) {it2->NT=it2->NT+1;} 
						}
						if(!it1->ifQuarantine){
							for (Class* it2:it1->InClass) {it2->NI=it2->NI-1;} 
						}
					}
				}
				break;
			}
			
			case 6:  {
				if (NumToday-(it1->SE)==ED+PD+SD+HD){
					double RandomNumber = du(ge);
					if(RandomNumber<=PDE){
						it1->condition=7;
						NS=NS-1;
					}
					if(RandomNumber>PDE){
						it1->condition=5;
						for (Class* it2:it1->InClass) {it2->NT=it2->NT+1;} 
					}
				}
				break;
			}								
		}
   }
	return 0;
}