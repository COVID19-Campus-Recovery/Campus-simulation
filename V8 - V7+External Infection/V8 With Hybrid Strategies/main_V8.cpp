#include <iostream>
#include<cmath>
#include"AllSchedule_V8.h"
#include"EverydaySchedule_V8.h"
#include"Write_V8.h"
#include"StateTransition_V8.h"
#include"SamplingInfectionsWeekends_V8.h"
#include"SampleInfectionsWeekdays_V8.h"
#include"TransmissionInfections_V8.h"
#include"Clear_V8.h"
#include"TestingProcess_V8.h"


int main() {
    filenameAM.push_back("AffiliationMatrix_M.csv");     // add the name of input files to a vector 
    filenameAM.push_back("AffiliationMatrix_T.csv");
    filenameAM.push_back("AffiliationMatrix_W.csv");
    filenameAM.push_back("AffiliationMatrix_R.csv");
    filenameAM.push_back("AffiliationMatrix_F.csv");
    filenameAM.push_back("AffiliationMatrix_S.csv");

    OpenFiles() ;  //Read "AffiliationMatrixOnCampus.csv" &  "AffiliationMatrixAll.csv" and record the information of all students & courses.

	outputfilename="Average";     //Generate the output file of average results, named as "AverageXX.csv", XX is corresponding testing number 
	string NumTestFilename;  
    stringstream ssNumTest;
    ssNumTest<<NumTest;
    ssNumTest>>NumTestFilename;
	outputfilename.append(NumTestFilename);
	outputfilename.append(".csv");
    cout<<outputfilename<<endl;

    int NumberData=0;      //Read “AffiliationMatrix_M/T/W/R/F/S.csv” in turn to record the student-course assignments on different days and in different weeks 
	for(int i=0; i<4;i++)    // With hybrid strategies, the class schedule are the same for week 1 and week 5 and so on, thus only record 4 weeks' schedule 
	{
		for(int j=0;j<DaysoftheWeek-1;j++)     //4 week * 6 days/week=24, thus there are totally 24 different types of student-course assignments 
		{
			OpenEverydayFile(filenameAM[j],i,NumberData);  //The function to read “AffiliationMatrix_M/T/W/R/F/S.csv” and record the student-course assignments 
			NumberData=NumberData+1;
		}
	}
    WriteAverageHeader();  //Write the header line of average results's output file

for(int k=0;k<RunTimes;k++)	
{
	cout<<"Run"<<" "; cout<<k<<endl;  //Output the number of current run
	
	ClearEachRun();  // Before each run, renew the state/condition of each student and reset those variables of recording cumulative data
	
	EntryTest();   
	
	WriteDaySummaryIndividualHeader(k);   // Write the header line of each individual run's output file
	
	WriteDaySummaryInv(0,0,CumuQua,CumuCase,CumuNumSym,0,CumuCase,k); 
	
	for(int i=0; i<NumberofWeeks;i++)    //NumberofWeeks: 14 weeks in a semester
	{
		for(int j=0;j<DaysoftheWeek;j++)    //DaysoftheWeek: 7 days in a week
		{
			CountTraced=0;        // define CountTraced to record the required number of contact tracing every day 
			int CountTest=0;      // define CountTest to record the actual number of tests every day 
			
			//define SeqNum to represent the serial number of today's student-course assignment
			int SeqNum=100;      //There are total 4*6=24 types of student-course assignment, 100 is used for avoiding assign courses for students on Sunday 
			
			int DayNum=7*i+j+1;   //define DayNum to record the number of today (day 1 - day 98) 
			
			ClearEachDay();       // Before each day, clear the record of last day's assignments and transmission rate within each class
			
			cout<<"day:"<<" "; cout<<DayNum<<endl;   //Output the number of current day
			
			if(j!=DaysoftheWeek-1)        // set today's student-course assignment based on the SeqNum and previous data read from EverydaySchedule
			{ 
				SeqNum=(i%4)*6+j;
				for (Student* stu: AllStudents)
				{
					for (Class* cla: stu->InClassToday[SeqNum])
					{
						ClassStudentsTodayMap[cla].push_back(stu);
					}
				}
			}
			int NewExp=0;  // # New Exposed today
			int NumIP=0;   // # Pre-symptomatically infected today
			int NumIS=0;   // # Symptomatically infected today
			int NumIA=0;   // # Asymptomatically infected today
			
			vector<Student*> StudentInfected;  //define vectors to record students those have been exposed/infected and haven't recovered/Dead:  E,Ip,Ia,Is,Ih 
			
			//define vectors to record students with different testing priority 
			vector<Student*> StudentHighTestPriority;     //The first class: start showing symptoms & student->TestPriority=3
			vector<Student*> StudentMedTestPriority;      //The second class: was traced having contacted with confirmed individuals & student->TestPriority=2
			vector<Student*> StudentLowTestPriority;      // Others will be tested randomly & student->TestPriority=1
			
			 
			for (Student* stu: AllStudents)
			{
				if ( (stu->ifOncampus==1) || (stu->NumClasses[SeqNum]!=0) )
				{
					if ( (stu->ifTested==0)&&(stu->ifWaitResult==0))
					{
						switch(stu->TestPriority)
						{
							    case 1:  { StudentLowTestPriority.push_back(stu);  break; }
							    case 2:  { StudentMedTestPriority.push_back(stu);  break; }
							    case 3:  { StudentHighTestPriority.push_back(stu); break; }
						}
					}
				}
				//Update StudentInfected to calculate the state transition at the beginning of each day
				if((stu->condition==1)||(stu->condition==2)||(stu->condition==3)||(stu->condition==4)||(stu->condition==6))
				{
					StudentInfected.push_back(stu);
				}
			}
			StateTransition(StudentInfected,DayNum);
			
			//Update the result of testing and quarantine each day
			for (Student* stu: AllStudents)
			{
				if ( stu->ifQuarantine==1 )
				{
					Quarantine(stu ,DayNum); //At the beginning of each day, update the state of students those are being quarantining
				}
				if ((stu->ifWaitResult==1) && (stu->ifTested==0))
				{
					TestingResult(stu ,DayNum); //At the beginning of each day, update the state of students those are waiting for testing results
				}
			}
			//Testing 3000 students according to the priority
			if (StudentHighTestPriority.size()>=NumTest){
				for (Student* stu: StudentHighTestPriority)
				{
					CountTest=CountTest+1;
					TestingProcess(stu ,DayNum);
					if (CountTest==NumTest) {break;}
				}

			}	
			else{
				if(StudentHighTestPriority.size()+StudentMedTestPriority.size()>=NumTest){
					for (Student* stu: StudentHighTestPriority)
					{
						CountTest=CountTest+1;
						TestingProcess(stu ,DayNum);
					}
					for (Student* stu: StudentMedTestPriority)
					{
						CountTest=CountTest+1;
						TestingProcess(stu ,DayNum);
						if (CountTest==NumTest) {break;}
					}
				}
				else{
					for (Student* stu: StudentHighTestPriority)
					{
						CountTest=CountTest+1;
						TestingProcess(stu ,DayNum);
					}
					for (Student* stu: StudentMedTestPriority)
					{
						CountTest=CountTest+1;
						TestingProcess(stu ,DayNum);
					}
					vector<int>* p;
					int SampleNum;
					if (NumTest-CountTest>=StudentLowTestPriority.size()) {SampleNum=StudentLowTestPriority.size();}
					if (NumTest-CountTest<StudentLowTestPriority.size()) {SampleNum=NumTest-CountTest;}
					p=Sample (SampleNum, 0, StudentLowTestPriority.size(),100000);
					for (int i=0;i<SampleNum;i++)     
					{
						CountTest=CountTest+1;
						TestingProcess(StudentLowTestPriority[p->at(i)] , DayNum);			
					}
				}
			}
			// cout<<CountTest<<endl;  //Print out the actual number of tests today (may not equal to NumTest, some students on campus are waiting for test results)
			
			// Calculate the # students in different compartments today, used to calculate the trasmission rate on campus
			for (Student* stu: AllStudents)
			{
				if ((stu->ifOncampus==1)||(stu->NumClasses[SeqNum]!=0))
				{
					switch(stu->condition){
						    case 0:  {break;}
						    case 1:  {break;}
						    case 5:  {break;}
						    case 6:  {break;}
						    case 7:  {break;}
						    case 2:  
							{
								if(stu->ifQuarantine==0)
								{
									NumIP=NumIP+1;
								}
								break; 
							}
						    case 3:  
							{
								if(stu->ifQuarantine==0)
								{
									NumIA=NumIA+1;
								}
								break; 
							}
						    case 4:  
							{
								if(stu->ifQuarantine==0)
								{
									NumIS=NumIS+1;
								}
								break; 
							}
					}
				}
			}
			
			//Calculate new infections during WeekDay (have classes on campus)
			
			if(j!=DaysoftheWeek-1) 
			{
				// Update TranRate & TranProb for each class
				for (Class* cla:ClassesToday[SeqNum]) 
			    {
				    int NIs=0;
					int NIp=0;
					int NIa=0;
					for (Student* s:ClassStudentsTodayMap[cla]) 
					{
					    switch(s->condition){
						    case 0:  {break;}
						    case 1:  {break;}
						    case 5:  {break;}
						    case 6:  {break;}
						    case 7:  {break;}
						    case 2:  
							{
								if(s->ifQuarantine==0)
								{
									NIp=NIp+1;
								}
								break; 
							}
						    case 3:  
							{
								if(s->ifQuarantine==0)
								{
									NIa=NIa+1;
								}
								break; 
							}
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
					cla->TranRate=lambda_s*NIs+lambda_p*NIp+lambda_a*NIa; 
					cla->TranProb=1-exp(-cla->TranRate);
			    }
			
			    //For each susceptible student, decide whether she/he will get infected today
			
			    //Calculate new In class infections: Mon. to Sat.
			    for (Student* stu:AllStudents)  
			    {
				    if ((stu->condition==0) && (stu->NumClasses[SeqNum]!=0) && (stu->ifQuarantine!=1)   )
				    {
				    	if( (bool) InclassInfections(stu,j,DayNum,SeqNum)) {NewExp+=1;CumuCase+=1;} 
				    }
			    }
			
			    //Calculate new Infections via social activities (3-hour parties) during weekdays: Thur. Frida. Sat. ,only for Greeklife students 
				if((j==DaysoftheWeek-2) ||(j==DaysoftheWeek-3)||(j==DaysoftheWeek-4))
				{
					vector<Student*> StudentSampledFrom;
					for (Student* stu:StudentsOnCampus)
					{
						if ((stu->ifQuarantine==0)&&(stu->ifGreeklife==1))
						{
							StudentSampledFrom.push_back(stu);
						}
					}
					for (Student* stu:StudentSampledFrom) 
					{
						if(stu->condition==0)
						{
							if(SamplingInfectionsWeekdays(stu,StudentSampledFrom,DayNum))
							{
								NewExp+=1;
								CumuCase+=1;
							}
						}
					}
				}
			
			    //Calculate new Infections outside of the class but on campus: Mon. to Sat.
				for (Student* stu:AllStudents)  
				{
					if  ( (stu->condition==0)  && ((stu->ifOncampus==1)||(stu->NumClasses[SeqNum]!=0)) && (stu->ifQuarantine!=1)  )
					{
						if((bool) OutclassInfections(stu,j,DayNum,NumIP,NumIS,NumIA,SeqNum))  {NewExp+=1;CumuCase+=1;}
					}
				}
				
				//Calculate new External Infecions: infections introduced from external source: Mon. to Sat.
				for (Student* stu:AllStudents) 
				{
					if  ((stu->condition==0)  && ((stu->ifOncampus==1)||(stu->NumClasses[SeqNum]!=0)) && (stu->ifQuarantine!=1) )
					{
						if((bool) OffCampusInfections(stu,j,DayNum,NumIP,NumIS,NumIA,SeqNum))  {NewExp+=1;CumuCase+=1;}
					}
				}
			}
			
			//Calculate new infections on Sunday (sample social contacts)
			if (j==DaysoftheWeek-1)  
			{
				vector<Student*> StudentSampledFrom;
				for (Student* stu:StudentsOnCampus)
				{
					if (stu->ifQuarantine==0)
					{
						StudentSampledFrom.push_back(stu);
					}
				}
				for (Student* stu:StudentSampledFrom)
				{
					if (stu->condition==0)  
					{
						if(SamplingInfectionsWeekends(stu,StudentSampledFrom,DayNum)) {NewExp+=1;CumuCase+=1;}	
					}
				}
			}
			
			//Output the summary of each individual run (cumulative and active number of cases each day)
			WriteDaySummaryInv(CumuHospitalization,CountTraced,CumuQua,CumuCase,CumuNumSym,DayNum,NewExp,k);    //Record summary each day
			
		}
		

	}
}
//Output the summary of the average results (cumulative and active number of cases each day)
WriteAverage();
}
