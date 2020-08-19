#include <iostream>
#include<cmath>

using namespace std;


vector<int> *Sample(int N, int sub, int sup,int ThisOne)
{
	vector<int> *RandNum=new vector<int>;
	unsigned int seed=rand();
	srand(seed);
	for(int i=0;i<N;i++)
	{
	    int t = (rand() % (sup-sub))+ sub; 
	    bool ifExsit=(bool) 0;
		if( t==ThisOne )  {i=i-1; ifExsit=1; continue;}
	    for( int j=0; j < i; j++ )
	    {
		    //cout<<(*RandNum)[j]<<endl;
		    if( t==(*RandNum)[j]  )  {i=i-1; ifExsit=1; break;}
	    }
	    if( !ifExsit )  {RandNum->push_back(t);}
	}
	return RandNum;
}

int FindIndex_1(vector<Student*>& vec, Student* stu)
{
	int index;
	int ifFind=0;
	for (int i=0;i<vec.size();i++)
	{
	   if(vec[i]==stu)
	   {
		index=i;
		ifFind=1;
		break;
	   }
   }
   if((bool) !ifFind) {cout<<"didn't found"<<endl;}
   return index;
}

int FindIndex_2(vector<int>& vec, int studentID)
{
	int index;
	int ifFind=0;
	for (int i=0;i<vec.size();i++)
	{
	   if(vec[i]==studentID)
	   {
		index=i;
		ifFind=1;
		break;
	   }
   }
   if((bool) !ifFind) {cout<<"didn't found"<<endl;}
   return index;
}





