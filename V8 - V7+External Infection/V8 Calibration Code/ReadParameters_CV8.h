#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <random>

using namespace std;
vector<string> Headers;
map<int,vector<double> > ParametersMap;
int NumParaSet=0;

bool ReadParameters() 
{
	string filename="Parameters.csv";
	std::ifstream comFile(filename.c_str());
	if (!comFile.is_open()) {
		cerr << "error opening file" << endl;
	}
    string headers;
	string omit;
	string ParaValue,ParameterName;
	getline(comFile,headers);
	stringstream CC(headers);
	while(getline(CC,ParameterName,','))
    {
        if (ParameterName[ParameterName.size()-1]=='\r') {ParameterName.erase(ParameterName.end()-1);}
        Headers.push_back(ParameterName);
    }
	while(comFile.good())
	{
		NumParaSet=NumParaSet+1;
		getline(comFile,headers);
		if (headers[headers.size()-1]=='\r') {headers.erase(headers.end()-1);}
		stringstream ss(headers);
		for (int i=0;i<3;i++)
		{
			getline(ss,ParaValue,',');
			ParametersMap[NumParaSet].push_back(stod(ParaValue));
		}
	}	
	return 0;
}
