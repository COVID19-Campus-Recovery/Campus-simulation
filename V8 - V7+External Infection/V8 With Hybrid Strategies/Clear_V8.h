#include <iostream>
using namespace std;

bool ClearEachRun() {
	CumuCase=0;
	CumuNumSym=0; 
	CumuQua=0;
	CumuHospitalization=0;
    for (Student* s:AllStudents) 
    {
	    s->ifQuarantine=0;
	    s->ifTested=0;
	    s->ifWaitResult=0;
	    s->ifPositive=0;
	    s->TestPriority=1;
	
	    double RandomNumber = du(ge);
	    if (RandomNumber<=PGreekLife) {s->ifGreeklife=1;}
	    if (RandomNumber>PGreekLife) {s->ifGreeklife=0;}
	    if(RandomNumber<=PR) {s->condition=10;}
	    else if((RandomNumber>PR)&&(RandomNumber<=PR+PIn))
		{
		    s->condition=1;
		    s->SE=0;
		    CumuCase=CumuCase+1;
		}
	    else if(RandomNumber>PR+PIn) {s->condition=0;}
    }
	return 0;
}

bool EntryTest() {
    for (Student* stu:AllStudents) 
    {
	    double RandomNumber = du(ge);
	    switch(stu->condition)
		{
			case 0:  
			{
				if(RandomNumber>TNR) //false positive 
				{
					stu->ifPositive=1;
					stu->ifTested=1;
					double RandomNumber = du(ge);
					if(RandomNumber<=PQ) 
					{
						stu->ifQuarantine=1; 
						CumuQua=CumuQua+1;
						stu->SQ=0;
					}
				}
				break;
			}
			case 1:  
			{
				if(RandomNumber<=TPR) //true positive 
				{
					stu->ifPositive=1;
					stu->ifTested=1;
					double RandomNumber = du(ge);
					if(RandomNumber<=PQ) 
					{
						stu->ifQuarantine=1; 
						CumuQua=CumuQua+1;
						stu->SQ=0;
					}
				}
				break;
			}
			case 2:  {break;}
			case 3:  {break;}
			case 4:  {break;}
			case 5:  {break;}
			case 6:  {break;}
			case 7:  {break;}
			case 10:  
			{
				if(RandomNumber>TNR) //false positive 
				{
					stu->ifPositive=1;
					stu->ifTested=1;
					double RandomNumber = du(ge);
					if(RandomNumber<=PQ) 
					{
						stu->ifQuarantine=1; 
						CumuQua=CumuQua+1;
						stu->SQ=0;
					}
				}
				break;
			}
		}
    }
	return 0;
}

bool ClearEachDay() {
	for (Class* c:AllClasses) 
	{
	    c->TranRate=0;
	    c->TranProb=0;
	}
	ClassStudentsTodayMap.clear();
	return 0;
}