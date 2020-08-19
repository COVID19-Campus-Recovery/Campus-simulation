#include <iostream>
#define DaysoftheWeek 7
#define NumberofWeeks 14

double P_WearingMasks=0.5;
double lambda_s=0.005*P_WearingMasks;
double beta=0.46;
double lambda_a=beta*lambda_s;
double lambda_p=beta*lambda_s;
double alpha=0.001;
double ExternalRate=0.0001;

double ProbCoeff=0.05;
double Pa=0.7672*ProbCoeff*P_WearingMasks; //Infection probability for a susceptible student given he/she sit next to one asymptomatically infectious student
double Ps=0.95*ProbCoeff*P_WearingMasks;  //Infection probability for a susceptible student given he/she sit next to one symptomatically infectious student
double Pp=0.7672*ProbCoeff*P_WearingMasks; //Infection probability for a susceptible student given he/she sit next to one student in pre-infectious phase

int NW_L=25; //Number of students to contact with effective infectious distance on weekends
int NW_H=100;
int NW_S=30;
double PGreekLife=0.25;
double PR=0.062; // % of residents with antibody 
double PIn=0.024; // % of residents infected 18-29 
int RunTimes=50;

//Parameters used for SEIR model
int ED=5;  //Exposed duration: the time (days) it takes for an exposed individual to move from E to Ip
int PD=1;  //Pre-symptomatic duration: The time (days) before an infected patient enters either asymptomatic and symptomatic phases	
int SD=3;  //Symptomatic duration
int AD=2;  //Asymptomatic duration
int HD=10;  //Hospitalized duration
double PS=0.66;  //Probability of Symptomatic
double PA=0.34;  //Probability of Asymptomatic
double PH=0.143;   //Probability of Hospitalization
double PDE=0.024;  //Probability a person who is hospitalized dies
 
double PQ=0.95; //Probability of qurantine if a student start showing symptom/testing positive
int NumTest=10000; //Number of test per day
double TPR=0.97; 
double TNR=0.999;
int TD=2; //time duration form the onset of testing to obtain results
int QD=14; //duration of quarantine 
int NumTracing=2;
//float STA=1.5;   //Symptomatic-to-Asymptomatic duration ratio
//float RTD=9.9;   //Recover-to-Death ratio
//quarantine for state S and H 
//float p=0.005; //Probability of getting infected by a student j given they share a class together and social distance

