# Campus-simulation

-----
July-26
-----

### Symbols' Description

`0`- `S`:   Susceptible: Healthy and susceptible to the coronavirus

`1`- `E`:   Exposed: Have already exposed to the coronavirus but haven't become infectious for others

`2`- `Ip`:  Pre-symptomatically infected: During infectious period before showing symptoms

`3`- `Ia`:  Asymptomatically infected: Being infectious but showing no symptoms

`4`- `Is`:  Symptomatically infected: Being infectious and have started showing symptoms

`5`- `R`:   Recovered: Have already recovered from COVID-19, thus have an antibody for now

`6`- `Ih`:  Hospitalization: Be in hospitalized after being symtomatically infected 

`7`- `D`:   Dead

`10`- `RP`: Have recovered from COVID-19 thus have an antibody before the beginning of the semester


### Input Files

`AffiliationMatrix.csv` / `AffiliationMatrixAll.csv` includes the assignment of all courses for all students, which is generated from the 2019 Fall registration data

`AffiliationMatrixOnCampus.csv` includes the assignment of all courses for all students living on campus, which is depended on the course scheduling strategy and housing scenario

`AffiliationMatrix_M/T/W/R/F/S.csv` includes the assignment of courses for students each weekday from Monday to Saturday respectively

### Output Files

`Average.csv` shows the average simulation results of total runs, which have # Cumulative Cases, # New Cases, # Quarantine, etc. 

`1.csv`....`100.csv`shows the simulation results of each individual run respectively.


### Different versions of simulation model

**1\.Version 1:** 

Calculate infections in class through assumed Closed-Form Formula


**2\. Version 2:**

Calculate infections in class through sampling students sitting close to each student

Calculate infections on weekends through sampling students get contacted with each student


**3\. Version 3:**

Calculate infections in class based on transmission rate & total number of infected students in a class

Calculate infections on weekends through sampling students get contacted with each student


**4\. Version 4:**

Calculate infections in class based on in-class transmission rate & total number of infected students in a class

Calculate infections outside of the class but on campus based on outside-of-class transmission rate & total number of infected students in school

Calculate infections off campus based on off-campus transmission rate & total number of infections in Fulton county

Calculate infections on weekends through sampling students get contacted with each student per day


**5\. Version 5:**

Modify based on version 4 to adapt to the new hybrid strategies.


**6\. Version 6:**

Modify based on version 5 to add interventions including wearing masks, testing (3% of all students per day), and quarantine.


**7\. Version 7:**

Modify based on version 6 to add interventions including wearing masks, testing (300 students per day), quarantine, and contact tracing.

**8\. Version 8:**

`8.1` Simulation code for hybrid strategies

`8.2` Simulation code for no hybrid strategies

`8.3` Calibration code

**Infection models included:**

Calculate new infections in each class based on transmission rate and total number of infected students in the class

Calculate new infections outside of class based on transmission rate and total number of infected students in school

Calculate new infections introduced from the external source based on a constant rate of external infection

Calculate new infections through social activities on Thursday, Friday, and Saturday via Sampling 30 students contacted with each student during 3 hours

Calculate new infections on Sunday via Sampling NW students contacted with each student each day

**Interventions included:**

Wearing masks;  Testing;  Contact tracing;  Quarantine


