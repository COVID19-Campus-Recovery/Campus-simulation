#include <iostream>
#include<cmath>
#include"Openclassfile.h"
#include"write.h"
#include"StateTransition.h"
#include"SamplingInfections.h"
#include"InclassInfections.h"


int main() {
	
	AlphaSet[0]=0.005;AlphaSet[1]=0.01;
	LambdaSet[0]=0.015;
    filenameAM.push_back("AffiliationMatrix_M.csv");
    filenameAM.push_back("AffiliationMatrix_T.csv");
    filenameAM.push_back("AffiliationMatrix_W.csv");
    filenameAM.push_back("AffiliationMatrix_R.csv");
    filenameAM.push_back("AffiliationMatrix_F.csv");
    filenameAM.push_back("AffiliationMatrix_S.csv");
    filenameAM.push_back("AffiliationMatrix.csv");
    for(int i=filenameAM.size()-1;i>=0;i--) {Openclassfile(filenameAM[i],i);} //Read AffiliationMatrix and save the data
    for(int i=0;i<3;i++)
	{
		for(int j=0;j<2;j++)
		{
			ParameterMap[4*i+j].push_back(LambdaSet[i]);
			ParameterMap[4*i+j].push_back(AlphaSet[j]);
		}
	}
	RNaught.open(outputfilename2,std::ios::app);
	RNaught<<"lambda_s"<<',';
	RNaught<<"alpha"<<'\r';
	RNaught.close();
	
	RNaughtSummary.open(outputfilename3,std::ios::app);
	RNaughtSummary<<"Lambda_s"<<',';
	RNaughtSummary<<"Alpha"<<',';
	RNaughtSummary<<"Ave(RNaught)"<<','; 
	RNaughtSummary<<"Ave(DaysSimulated)"<<',';
	RNaughtSummary<<"Total#Runs"<<'\r';
	RNaughtSummary.close();
	
	for(int m=0;m<NumPar;m++)
	{
		TotalRNaugut=0;
		TotalDays=0;
		CountRNaught=0;
		lambda_s=ParameterMap[m][0];
		alpha=ParameterMap[m][1];
		lambda_a=beta*lambda_s;
		lambda_p=beta*lambda_s;
		cout<<"lambda_s:"<<' '; cout<<lambda_s<<endl;
		cout<<"alpha:"<<' '; cout<<alpha<<endl;
		RNaughtSummary.open(outputfilename3,std::ios::app);
		RNaughtSummary<<lambda_s<<',';
		RNaughtSummary<<alpha<<',';
		RNaughtSummary.close();
		RNaught.open(outputfilename2,std::ios::app);
		RNaught<<lambda_s<<',';
		RNaught<<alpha<<',';
		RNaught.close();
		for(int k=0;k<RunTimes;k++)	
		{
			IfStopR=0; 
			cout<<"Run"<<" "; cout<<k<<endl;
			if(k!=0) {ClearAll();}
			for (int i=0; i<Initial;i++)
			{
			    double RandomNumber = du(ge); //Randomly generate Patient Zero
			    allStudent[StudentVector[(int)(RandomNumber*NS)]]->condition=1;  
			    allStudent[StudentVector[(int)(RandomNumber*NS)]]->SE=0;
			    CumuCase=CumuCase+1;
			}
						
			for(int i=0; i<NumberofWeeks;i++)    //NumberofWeeks: 14 weeks in a semester
			{
				for(int j=0;j<DaysoftheWeek;j++)    //DaysoftheWeek: 7 days in a week
				{
					int DayNum=7*i+j+1;//the number of that day 
					int NewExp=0; //#New Exposed
					int NumIP=0;
					int NumIS=0;
					int NumIA=0;
					vector<Student*> StudentInfected; //Record students those have been exposed/infected and haven't recovered/Dead:  E,Ip,Ia,Is,Ih calculate transitions
					//Update StudentInfected at the beginning of each day 
					for (auto it = allStudent.begin(); it != allStudent.end(); it++)
					{
						switch(it->second->condition){
							    case 0:  {break;}
							    case 1:  {StudentInfected.push_back(it->second);break;}
							    case 5:  {break;}
							    case 6:  {StudentInfected.push_back(it->second);break;}
							    case 7:  {break;}
							    case 2:  {StudentInfected.push_back(it->second);NumIP=NumIP+1;break;}
							    case 3:  {StudentInfected.push_back(it->second);NumIA=NumIA+1;break;}
							    case 4:  
								{
									StudentInfected.push_back(it->second);
									if(it->second->ifQuarantine==0)
									{
										NumIS=NumIS+1;
									}
									break; 
								}
						}
					}
					//Update conditions of those StudentInfected 
					StateTransition(StudentInfected,DayNum);
					//Calculate new infections during WeekDay (have classes on campus)
					if(j!=DaysoftheWeek-1) 
					{	
						vector<Class*> ClassSuc; //Susceptible class with infected student (not quarantine) at that day
						vector<Student*> StudentSucIn; //Students those taking classes together with infected student  (not quarantine) at that day
						// Update ClassSuc (class with infectious students) & StudentSuc (susceptible students)
						for (auto it = allClass.begin(); it != allClass.end(); it++) 
					    {
						    if((it->second->NI!=0)&&(it->second->DayoftheWeek[j]==1))
						    {
							    ClassSuc.push_back(it->second);
							    int NIs=0;
								int NIp=0;
								int NIa=0;
								for (Student* s:classStudentMap[it->second]) 
								{
								    switch(s->condition){
									    case 0:  
										{
											if( std::find(StudentSucIn.begin(), StudentSucIn.end(), s) == StudentSucIn.end() )
											{StudentSucIn.push_back(s);}
											break;
									    }
									    case 1:  {break;}
									    case 5:  {break;}
									    case 6:  {break;}
									    case 7:  {break;}
									    case 2:  {NIp=NIp+1;break;}
									    case 3:  {NIa=NIa+1;break;}
									    case 4:  
										{
											if(s->ifQuarantine==0)
											{
												NIs=NIs+1;
											}
											break; 
										}
								    }
								}
								it->second->TranRate=lambda_s*NIs+lambda_p*NIp+lambda_a*NIa; 
								it->second->TranProb=1-exp(-it->second->TranRate);
						    }
					    }
					    //For each susceptible student, decide whether she/he will get infected today via sampling
					    if (StudentSucIn.size()!=0) 
					    {
						    for (Student* stu:StudentSucIn)
						    {
							    if( (bool) InclassInfections(stu,j,DayNum)) {NewExp+=1;CumuCase+=1;} 						    
							}
					    }
						for (auto it = allStudent.begin(); it != allStudent.end(); it++)  //Outside of the class but on campus
						{
							if(it->second->condition==0)  
							{
								if((bool) OutclassInfections(it->second,j,DayNum,NumIP,NumIS,NumIA))  {NewExp+=1;CumuCase+=1;}
							}
						}
						for (auto it = allStudent.begin(); it != allStudent.end(); it++) //Off Campus
						{
							if(it->second->condition==0)  
							{
								if((bool) OffCampusInfections(it->second,j,DayNum,NumIP,NumIS,NumIA))  {NewExp+=1;CumuCase+=1;}
							}
						}
					}
					
					if (j==DaysoftheWeek-1||j==DaysoftheWeek-2)  // Calculate the infection on Weekends
					{	
						for (auto it = allStudent.begin(); it != allStudent.end(); it++) 
						{
							if(it->second->condition==0)   
							{
								if(SamplingInfectionsWeekends(it->second,StudentVector,DayNum))
								{
									NewExp+=1;
									CumuCase+=1;
								}	
							}
						}
					}	
					//Record summary of at the end of each day: # of students in different condition invidual run
					WriteDaySummary(CumuCase,CumuNumSym,DayNum,NewExp);    
					if(IfStopR) {break;}
				}
				if(IfStopR) {break;}  
			}
			// at the end of each run
		}
		//at the end of each parameter set
		RNaughtSummary.open(outputfilename3,std::ios::app);
		double AverageRNaught=TotalRNaugut/CountRNaught;
		RNaughtSummary<<AverageRNaught<<',';
		double AverageDays=(TotalDays/CountRNaught)+0.00;
		RNaughtSummary<<AverageDays<<',';
		RNaughtSummary<<CountRNaught<<'\r';
		RNaughtSummary.close();
		
		RNaught.open(outputfilename2,std::ios::app);
		RNaught<<" "<<'\r';
		RNaught.close();
	}


}
