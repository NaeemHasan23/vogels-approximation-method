#include <iostream>
#include <fstream>
#include <cmath>
#include <list>

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
		Difference d;
		
		int min;// = (int) pow(2,31)-10;
		
		/*
		for(int i=0; i<numberOfOrigin; i++)
		{
			if(workMatrix[i][j] != -420)
				if(min > workMatrix[i][j]) min = workMatrix[i][j];
		}
		*/
		
		list <int> temp;
		for(int i=0; i<numberOfOrigin; i++)
		{
			if(workMatrix[i][j] !=-420)temp.push_back(workMatrix[i][j]);
			//cout << "Terrible :O   " << workMatrix[i][j] << endl;
		}
		//for (list<int>::iterator it3=temp.begin(); it3!=temp.end(); ++it3)
		//	cout << "XXXXXXXXXXXXXXXX" << *it3 << endl;
		
		temp.sort();
		temp.unique();
		//temp.remove(-420);
		
		if(!temp.empty())
		{
			list<int>::iterator it2= temp.begin();
			min = *it2;
		
		//	cout << "Hudai "<< *it2 << endl;
		}
		else 
		{
			//cout << "Keu na " << "-420"<<endl;
			min = -420;
		}
		
		//cout << "Min Paisi " << min << endl;
		
		list <int> differenceList, sortedDifferenceList;
		
		for(int i=0; i<numberOfOrigin; i++)
		{
			if(workMatrix[i][j] == -420) 
			{
				//differenceList.push_back(-420);
				//sortedDifferenceList.push_back((int) pow(2,31)-10);
			}
			else
			{
				int diff;
				if(min > workMatrix[i][j]) diff = min - workMatrix[i][j];
				else diff = workMatrix[i][j] - min;
				
				differenceList.push_back(diff);
				sortedDifferenceList.push_back(diff);
			}
		}
		
		if(!differenceList.empty())
		{
			sortedDifferenceList.sort();
		
			list<int>::iterator it=sortedDifferenceList.begin();
			++it;
			d.difference = *it;
		
			d.column= j;
		
			int rowNumber=0;
			for(list<int>::iterator it1 = differenceList.begin(); it1 != differenceList.end(); ++it1)
			{
				if(*it1 == 0) 
				{
					d.row = rowNumber;
					break;
				}
				rowNumber++;
			}
		}
		else
		{
			d.difference =-420;
			d.row = -1;
			d.column =-1;
		}
		
		
		columnDifference[j] = d;
	}
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

void findAllMinRowDifference(void)
{
	for(int i=0; i<numberOfOrigin; i++)
	{
		Difference d;
		
		int min = (int) pow(2,31)-10;
		
		for(int j=0; j<numberOfDestination; j++)
		{
			if(workMatrix[i][j] != -420)
			if(min > workMatrix[i][j]) min = workMatrix[i][j];
			//if(min > workMatrix[i][j] && workMatrix[i][j] != -420) min = workMatrix[i][j];
		}
		
		list <int> differenceList, sortedDifferenceList;
		
		for(int j=0; j<numberOfDestination; j++)
		{
			if(workMatrix[i][j] == -420) 
			{
				differenceList.push_back(-420);
				sortedDifferenceList.push_back((int) pow(2,31)-10);
			}
			else
			{
				int diff;
				if(min > workMatrix[i][j]) diff = min - workMatrix[i][j];
				else diff = workMatrix[i][j] - min;
				
				differenceList.push_back(diff);
				sortedDifferenceList.push_back(diff);
			}
		}
		
		sortedDifferenceList.sort();
		
		list<int>::iterator it=sortedDifferenceList.begin();
		++it;
		d.difference = *it;
		
		d.row = i;
		
		int columnNumber=0;
		for(list<int>::iterator it1 = differenceList.begin(); it1 != differenceList.end(); ++it1)
		{
			if(*it1 == 0) 
			{
				d.column = columnNumber;
				break;
			}
			columnNumber++;
		}
		
		rowDifference[i] = d;
	}
}

void printMaxOfRowColumnDifference(Difference d)
{
	cout << "MaxRowColDifference" << d.difference << "\t"
			<< "Row" << d.row << "\t"
			<< "Column" << d.column << endl;
}

void changeTheDifference(Difference &dest, Difference source)
{
	dest.difference = source.difference;
	dest.row = source.row;
	dest.column = source.column;
}

Difference findMaxOfRowColumnDifference(void)
{
	Difference d;
	d.difference = -1;
	d.row=-1;
	d.column=-1;
	
	for(int i=0; i<numberOfOrigin; i++)
	{
		if(d.difference < rowDifference[i].difference) changeTheDifference(d, rowDifference[i]);
	}
	
	for(int j=0; j<numberOfDestination; j++)
	{
		if(d.difference < columnDifference[j].difference) changeTheDifference(d, columnDifference[j]);
	}
	
	return d;
}

void printNecessaryMatrices(void)
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

void printAfterAllocateFromSourceTODestination(void)
{
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
		demand[point.row] = demand[point.row] - demand[point.row];
		supply[point.column] = supply[point.column] - demand[point.row];
		
		for(int j=0; j<numberOfDestination; j++)
		{
			workMatrix[point.row][j] = -420;
		}
	}
}

void vogelsApproximationMethod(void)
{
	int iteration = 0;
	while(1)
	{
		if (iteration == 2)break;
		iteration++;
		
		//cout << "vogel shaber iteration " << iteration << endl;
		findAllMinRowDifference();
		//cout << "Row Diff Iteration (3)" << iteration << endl;
		//printAllMinRowDifference();
		findAllMinColDifference();
		//cout << "Col Diff Iteration (4)" << iteration << endl;
		//printAllMinColumnDifference();
		
		Difference d = findMaxOfRowColumnDifference();
		//printMaxOfRowColumnDifference(d);
		
		
		cout << "Allocation " << iteration << endl;
		allocateFromSourceTODestination(d);
		printAfterAllocateFromSourceTODestination();
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



int main (int argc, char *argv[])
{
	if(!openFile(argv[1]))
	{
		return -1;
	}
	
	prepareNecessaryMatrices();
	
	vogelsApproximationMethod();
	
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
