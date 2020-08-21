#include <iostream>
#define DaysoftheWeek 7
#define NumberofWeeks 14

double P_WearingMasks=0.5;   //if wearing masks, the transmission probabilities/rate are reduced to half of the values without masks
double lambda_s=0.005*P_WearingMasks;  //Transmission rate in class per symptomatically infected student per class period (1.5 hours)
double beta=0.46; //Relative coefficient of lambda_a to lambda_s
double lambda_a=beta*lambda_s;  //Transmission rate in class per asymptomatically infected student per class period (1.5 hours)
double lambda_p=beta*lambda_s;  //Transmission rate in class per pre-symptomatically infected student per class period (1.5 hours)
double alpha=0.001;     //Relative coefficient of transmission rate outside of class to the in-class rate
double ExternalRate=0.0001;   //constant rate of external infection for each student

double ProbCoeff=0.05;  //Coefficient of infection probabilities (calibrated)
double Pa=0.7672*ProbCoeff*P_WearingMasks; //Infection probability for a susceptible student given he/she contacts with one asymptomatically infectious student
double Ps=0.95*ProbCoeff*P_WearingMasks;  //Infection probability for a susceptible student given he/she contacts with one symptomatically infectious student
double Pp=0.7672*ProbCoeff*P_WearingMasks; //Infection probability for a susceptible student given he/she contacts with one student in pre-infectious phase

int NW_L=25;   //Number of students contacted with on Sunday for each non-super social student 
int NW_H=100;  //Number of students contacted with on Sunday for each super social student
int NW_S=30;   //Number of students contacted with on Thu. Fri. Sat. during 3-hour party time for each super social student
double PGreekLife=0.25;   //Percentage of students who are super social ("Greek Life" students)
double PR=0.062; // % of students with antibody before the semester
double PIn=0.024; // % of students infected before the semester (assume all of them are exposed at day 0)
int RunTimes=50;   //# of running times for each scenario


//Parameters used for SEIR model
int ED=5;  //Exposed duration: the time (days) it takes for an exposed individual to move from E to Ip
int PD=1;  //Pre-symptomatic duration: The time (days) before an infected patient enters either asymptomatic and symptomatic phases	
int SD=3;  //Symptomatic duration
int AD=2;  //Asymptomatic duration
int HD=10;  //Hospitalized duration
double PS=0.66;  //Probability of Symptomatic infected if exposed
double PA=0.34;  //Probability of Asymptomatic infected if exposed
double PH=0.143;   //Probability of Hospitalization if symptomatically infected
double PDE=0.024;  //death to hospitalization probability 
 

//Parameters used for interventions
double PQ=0.95; //Probability of qurantine if a student start showing symptom/testing positive
int NumTest=10000; //Number of test per day
double TPR=0.97;   //True positive rate 
double TNR=0.999;  //True negative rate
int TD=2; //time duration form the onset of testing to obtain results
int QD=14; //duration of quarantine 
int NumTracing=2; //Anyone with positive test result are flagged to have their in-class contacts during the past NumTracing days traced

