## Version 8

### `Folder 8.1` Simulation code for hybrid strategies 

Input Files:

Eight affiliation matrixes for strategies with hybrid mode

AffiliationMatrixAll.csv & AffiliationMatrix_M/T/W/R/F/S.csv & AffiliationMatrixOnCampus.csv


### `Folder 8.2` Simulation code for no hybrid strategies 

Input Files:

Seven affiliation matrixes for strategies without hybrid mode

AffiliationMatrix.csv & AffiliationMatrix_M/T/W/R/F/S.csv


### `Folder 8.3` Calibration code 

Input Files: 

Seven affiliation matrixes for Fall 2019 strategy (all courses are residential)

AffiliationMatrix.csv & AffiliationMatrix_M/T/W/R/F/S.csv


### `Model Features` Interventions included:

Intervention 1: Wearing masks

Intervention 2: Testing

Intervention 3: Contact tracing

Intervention 4: Quarantine


### `Model Features` Infection models included:

Calculate new infections in each class based on transmission rate and total number of infected students in the class

Calculate new infections outside of class based on transmission rate and total number of infected students in school

Calculate new infections introduced from the external source based on a constant rate of external infection

Calculate new infections on Thursday, Friday, and Saturday via Sampling 30 students contacted with each student during 3 hours

Calculate new infections on Sunday via Sampling NW students contacted with each student each day


### `Code Introduction` Descriptions of each function file

**1\. Main_V8.cpp:**

The execution file of the whole project, including main() function.

**2\. Parameters_V8.h:**

Including the defination and value of all parameters used in the model, need adjustment for different scenarios.

**3\. AllSchedule_V8.h:**

Read "AffiliationMatrixOnCampus.csv" &  "AffiliationMatrixAll.csv" and record the information of all students & courses.

**4\. EverydaySchedule_V8.h:**

Read “AffiliationMatrix_M/T/W/R/F/S.csv” in turn to record the student-course assignments on different days and in different weeks

**5\. Write_V8.h:**

Output the summary of each individual run and the average results (cumulative and active number of cases each day)

**6\. StateTransition_V8.h:**

Update and calculate the state transitions for those infected students at the beginning of each day

**7\. TransmissionInfections_V8.h:**

Calculate new infections in class and outside of classes, which both use transmission model

Calculate new infections introduced from external sourse through a constant rate of external infection

**8\. SamplingInfectionsWeekends_V8.h:**

Calculate new infections on Sunday using sampling model

**9\. SampleInfectionsWeekdays_V8.h:**

Calculate new infections on Thu. Fri. and Sat. using sampling model

**10\. Sample_V8.h:**

Defind a function which is used to sample x integers from total N integers (used for sampling students in the sampling model)

**11\. TestingProcess_V8.h:**

Functions: TestingProcess(), TestingResult(), Quarantine()

TestingProcess(): for those students to be tested, calculate the testing results according to the student's actual condition

TestingResult(): for those students have been tested, calculate if they will get their testing results today and update the corresponding information like ifQuarantine and so on

Quarantine(): for those students have been quarantined, calculate if they are qualified for stopping quarantining

**12\. ContactsTracing_V8.h:**

Simulate the process of contact tracing, update the test priority of those students who have been flaged

**13\. Clear_V8.h:**

Clear, reset and update information or parameters at the beginning of each day/run.

