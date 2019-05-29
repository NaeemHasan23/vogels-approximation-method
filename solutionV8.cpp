#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int **inputMatrix;

struct Difference
{
	int difference;
	int row, column;
};

int numberOfOrigin, numberOfDestination;
int **workMatrix, **allocation, **cost;
int *demand, *supply;
Difference *rowDifference,  *columnDifference;

bool sortFunctionAscending(Difference i, Difference j)
{
	return (i.difference < j.difference);
}

void printAllMinRowDifference(void)
{
	for(int i=0; i<numberOfOrigin;i++)
	{
		cout << "MinDifference" << rowDifference[i].difference << "\t"
			<< "Row" << rowDifference[i].row << "\t"
			<< "Column" << rowDifference[i].column << endl;
	}
}

void findAllMinRowDifference(void) //handle 420 case if the whole row in -420
{
	for(int i=0; i<numberOfOrigin; i++)
	{
		vector <Difference> temp;
		
		for(int j=0; j<numberOfDestination; j++)
		{
			if(workMatrix[i][j] != -420)
			{
				Difference d;
				d.difference = workMatrix[i][j];
				d.row = i;
				d.column = j;
				
				temp.push_back(d);
			}
		}
		
		if(!temp.empty())
		{
			sort(temp.begin(), temp.end(), sortFunctionAscending);
		
			int min = temp[0].difference;
		
			for(int k=0; k<temp.size(); k++)
			{
				temp[k].difference = temp[k].difference - min;
			}
		
			rowDifference[i].row = temp[0].row;
			rowDifference[i].column = temp[0].column;
			rowDifference[i].difference = temp[1].difference;
		}
		else
		{
			rowDifference[i].row = -1;
			rowDifference[i].column = -1;
			rowDifference[i].difference = -840;
		}
	}
}


void printAllMinColumnDifference(void)
{
	for(int j=0; j<numberOfDestination; j++)
	{
		cout << "MinDifference" << columnDifference[j].difference << "\t"
			<< "Row" << columnDifference[j].row << "\t"
			<< "Column" << columnDifference[j].column << endl;
	}
}

void findAllMinColDifference(void)
{
	for(int j=0; j<numberOfDestination; j++)
	{
		vector <Difference> temp;
		
		for(int i=0; i<numberOfOrigin; i++)
		{
			if(workMatrix[i][j] != -420)
			{
				Difference d;
				d.difference = workMatrix[i][j];
				d.row = i;
				d.column = j;
				
				temp.push_back(d);
			}
		}
		
		if(!temp.empty())
		{
			sort(temp.begin(), temp.end(), sortFunctionAscending);
		
			int min = temp[0].difference;
		
			for(int k=0; k<temp.size(); k++)
			{
				temp[k].difference = temp[k].difference - min;
			}
		
			columnDifference[j].row = temp[0].row;
			columnDifference[j].column = temp[0].column;
			columnDifference[j].difference = temp[1].difference;
		}
		else
		{
			columnDifference[j].row = -1;
			columnDifference[j].column = -1;
			columnDifference[j].difference = -840;
		}
	}
}

void printMaxOfRowColumnDifference(Difference d)
{
	cout << "MaxRowColDifference" << d.difference << "\t"
			<< "Row" << d.row << "\t"
			<< "Column" << d.column << endl;
}


bool sortFunction(Difference i, Difference j)
{
	return (i.difference >j.difference);
}

Difference findMaxOfRowColumnDifference(void)
{
	vector <Difference> differenceVec;
		
	
	for(int i=0; i<numberOfOrigin; i++)
	{
		differenceVec.push_back(rowDifference[i]);
	}
	
	for(int j=0; j<numberOfDestination; j++)
	{
		differenceVec.push_back(columnDifference[j]);
	}
	
	sort(differenceVec.begin(), differenceVec.end(), sortFunction);
	
	return differenceVec[0];
}

void printNecessaryMatrices(void)
{
	cout << "Working Matrix" << endl;
	for(int i=0; i<numberOfOrigin; i++)
	{
		for(int j=0; j<numberOfDestination; j++)
		{
				cout << workMatrix[i][j] << " ";
		}
		cout << endl;
	}
	
	cout << "Allocation Matrix" << endl;
	for(int i=0; i<numberOfOrigin; i++)
	{
		for(int j=0; j<numberOfDestination; j++)
		{
			cout << allocation[i][j] << " ";
		}
		cout << endl;
	}
	
	cout << "Demand" << endl;
	for(int i=0; i<numberOfOrigin; i++)
	{
		cout << demand[i] << " ";
	}
	cout << endl;
	
	cout << "Supply" << endl;
	for(int j=0; j<numberOfDestination; j++)
	{
		cout << supply[j] << " ";
	}
	cout << endl;
}

void printBeforeAllocateFromSourceTODestination(void)
{
	cout << "Cost Matrix" << endl;
	for(int i=0; i<numberOfOrigin; i++)
	{
		for(int j=0; j<numberOfDestination; j++)
		{
				cout << cost[i][j] << " ";
		}
		cout << endl;
	}
	
	printNecessaryMatrices();
}

void allocateFromSourceTODestination(Difference point)
{
	if(demand[point.row] > supply[point.column])
	{
		allocation[point.row][point.column] = supply[point.column];
		demand[point.row] = demand[point.row] - supply[point.column];
		supply[point.column] = supply[point.column] - supply[point.column];
		
		for(int i=0; i<numberOfOrigin; i++)
		{
			workMatrix[i][point.column] = -420;
		}
	}
	else
	{
		allocation[point.row][point.column] = demand[point.row];
		supply[point.column] = supply[point.column] - demand[point.row];
		demand[point.row] = demand[point.row] - demand[point.row];
		
		for(int j=0; j<numberOfDestination; j++)
		{
			workMatrix[point.row][j] = -420;
		}
	}
}

bool stoppingConditionForBalancedProblem(void)
{
	int sum =0;
	for(int j=0; j<numberOfDestination; j++)
	{
		sum += supply[j];
	}
	
	if(sum == 0) return true;
	else return false;
}

void vogelsApproximationMethod(void)
{
	printBeforeAllocateFromSourceTODestination();
	
	int iterationNumber =0;
	while(1)
	{
		if (stoppingConditionForBalancedProblem())break;
				
		iterationNumber++;
		
		findAllMinRowDifference();
		findAllMinColDifference();
		
		Difference d = findMaxOfRowColumnDifference();
				
		allocateFromSourceTODestination(d);
		
		cout << endl << endl <<"...Allocation " << iterationNumber << " done...." << endl << endl;
		
		printNecessaryMatrices();
	}
}

void makeInputMatrix(void)
{
	inputMatrix = new int *[numberOfOrigin+1];
	for(int i=0; i<numberOfOrigin+1; i++)
	{
		inputMatrix[i] = new int [numberOfDestination+1];
	}
}

void destroyInputMatrix(void)
{
	for(int i=0; i<numberOfOrigin+1; i++)
	{
		delete [] inputMatrix[i];
	}
	delete [] inputMatrix;
}

bool openFile(char *fileName)
{
	ifstream iFile;
	iFile.open(fileName);
	if(iFile.is_open())
	{
		iFile >> numberOfOrigin >> numberOfDestination;
		
		makeInputMatrix();
		
		for(int i=0; i<numberOfOrigin+1; i++)
		{
			for(int j=0; j<numberOfDestination+1; j++)
			{
				iFile >> inputMatrix[i][j];
			}
		}
		
		iFile.close();
		
		return true;
	}
	else
	{
		cout << "Coud not open Input File " << fileName << endl;
		return false;
	}
	
}

void createNecessaryMatrices(void)
{
	workMatrix = new int *[numberOfOrigin];
	for(int i=0; i<numberOfOrigin; i++)
	{
		workMatrix[i] = new int [numberOfDestination];
	}
	
	cost = new int *[numberOfOrigin];
	for(int i=0; i<numberOfOrigin; i++)
	{
		cost[i] = new int [numberOfDestination];
	}
	
	allocation = new int *[numberOfOrigin];
	for(int i=0; i<numberOfOrigin; i++)
	{
		allocation[i] = new int [numberOfDestination];
	}
	
	demand = new int [numberOfOrigin];
	supply = new int [numberOfDestination];
	
	rowDifference = new Difference [numberOfOrigin];
	columnDifference = new Difference [numberOfDestination];
}

void destroyNecessaryMatrices(void)
{
	for(int i=0; i<numberOfOrigin; i++)
	{
		delete [] workMatrix[i];
	}
	delete [] workMatrix;
	
	for(int i=0; i<numberOfOrigin; i++)
	{
		delete [] cost[i];
	}
	delete [] cost;
	
	for(int i=0; i<numberOfOrigin; i++)
	{
		delete [] allocation[i];
	}
	delete [] allocation;
	
	delete [] demand;
	delete [] supply;
	
	delete [] rowDifference;
	delete [] columnDifference;
}

void prepareNecessaryMatrices(void)
{
	createNecessaryMatrices();
	
	for(int i=0; i<numberOfOrigin; i++)
	{
		for(int j=0; j<numberOfDestination; j++)
		{
			workMatrix[i][j] = inputMatrix[i][j];
			cost[i][j] = inputMatrix[i][j];
		}
	}
	
	for(int i=0; i<numberOfOrigin; i++)
	{
		for(int j=0; j<numberOfDestination; j++)
		{
			allocation[i][j] = 0;
		}
	}
	
	for(int i=0; i<numberOfOrigin; i++)
	{
		demand[i] = inputMatrix[i][numberOfDestination];
		//rowDifference[i] = NULL;
	}
	
	for(int j=0; j<numberOfDestination; j++)
	{
		supply[j] = inputMatrix[numberOfOrigin][j];
		//columnDifference[j] = NULL:
	}
	
	destroyInputMatrix();
}

int calculateIBFS(void)
{
	int result =0;
	for(int i=0; i<numberOfOrigin; i++)
	{
		for(int j=0; j<numberOfDestination; j++)
		{
			result += allocation[i][j] *cost[i][j];
		}
	}
	return result;
}

void printResult(int result)
{
	
	cout << endl << "Result as follows: " << endl;
	for(int i=0; i<numberOfOrigin; i++)
	{
		for(int j=0; j<numberOfDestination; j++)
		{
			if(allocation[i][j]!=0)
				cout << "Source/Origin # " << i << " has contributed " << allocation[i][j] << " units to Destination" << j << endl;
		}
	}
	
	cout << "Total Cost " << result << endl;
}

int main (int argc, char *argv[])
{
	if(!openFile(argv[1]))
	{
		return -1;
	}
	
	prepareNecessaryMatrices();
	
	vogelsApproximationMethod();
	
	int ibfs = calculateIBFS();
	
	printResult(ibfs);
	
	destroyNecessaryMatrices();
	//destroyInputMatrix();
	return 0;
}

/*
printNecessaryMatrices();
//v2

*/

/*
testPrintInputMatrix();
//v1
void testPrintInputMatrix(void)
{
	for(int i=0; i<numberOfOrigin+1; i++)
	{
		for(int j=0; j<numberOfDestination+1; j++)
		{
				cout << inputMatrix[i][j] << " ";
		}
		cout << endl;
	}
}
*/
