#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <random>

using namespace std;

bool ContactsTracing(Student* stu ,int DayNum) 
{
	for (int i=1;i<=NumTracing;i++)
	{
		int DayCal;
		DayCal=DayNum-i;
		int NumWeek=DayCal/7;
		int NumDayOf=DayCal%7;
		vector<Class*> ClassesTraced;
		if((DayCal%7!=0)&&(DayCal>=1))
		{
			int Sequence=(NumWeek%4)*6+NumDayOf;
			for (Class* cla: stu->InClassToday[Sequence])
			{
                 ClassesTraced.push_back(cla);
			}
			for (Student* s: AllStudents)
			{
				for (Class* cla: s->InClassToday[Sequence])
				{
					if (std::find(ClassesTraced.begin(), ClassesTraced.end(), cla) != ClassesTraced.end())
					{
						s->TestPriority=2;
						break;
					}
				}
			}
		}	
	}
}