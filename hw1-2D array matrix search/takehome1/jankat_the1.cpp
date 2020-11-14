#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <cstring>

using namespace std;

// TAKEHOME EXAM 1    JANKAT YASAR  26635

void printmatrix(const vector<vector<char> > & matrix,int rows, int cols) // function to print the matrix as puzzle
{
	for (int j=0; j < rows; j++)
	{   
		for (int k=0; k < cols; k++)
		{   			
			if (k==0)	// condition to not start with space at the start of the line.
			{
				cout << matrix[j][k];
			}
			else  // putting spaces between characters in puzzle.
			{
				cout << setw(2) << matrix[j][k];
			}						
		}
		cout << endl;
	}
}

int LeftToRight(vector<vector<char> > & matrix,string s, int rows, int cols) // function for regular horizontal scan
{
	string line;	//string variable that we re gonna assign characters in rows.
	bool wordfound = false;
	int num;	//int variable to save which index the word is found.
	int charnum = 0; // number of characters variable in case the word is found.
	for (int j = 0; j < rows; j++)
	{
		for (int k = 0; k < cols; k++)
		{
			line += matrix[j][k]; // bringing together the characters of the matrix of that line.
			num = j;
		}		
		if (strstr(line.c_str(),s.c_str()))
		{
			wordfound = true;
			cout << "Word " << s << " is found." << endl;			
			break;
		}
		else
		{
			line.clear();
		}
	}
	if (wordfound == true)
	{
		if (num == rows-1)	//Checking if the word is in the last row, then we wont need to swap rows.
		{
			matrix.pop_back();	
		}
		else
		{
			for (int i = num; i < rows-1; i++)	
			{
				swap(matrix[i],matrix[i+1]);	// loop for pushing the row the last row so that we can delete with popback				
			}
			matrix.pop_back();
		}
		charnum = s.length();		// word has found so number of chars needed to calculation
	}
	return charnum; // returning number of chars to calculation later in the main func. if word not found, its 0.
}

int RightToLeft(vector<vector<char> > & matrix,string s, int rows, int cols)
{
	string line;	//string variable that we re gonna assign characters in rows.
	bool wordfound = false;
	int num;	//int variable to save which index the word is found.
	int charnum = 0; // number of characters variable in case the word is found.
	for (int j = 0; j < rows; j++)
	{
		for (int k = cols-1; k >= 0; k--)
		{
			line += matrix[j][k]; // bringing together the characters of the matrix of that line.
			num = j;
		}		
		if (strstr(line.c_str(),s.c_str()))
		{
			wordfound = true;
			cout << "Word " << s << " is found." << endl;				
			break;
		}
		else
		{
			line.clear(); // clear the string to read the next row.
		}
	}
	if (wordfound == true)
	{
		if (num == rows)	//Checking if the word is in the last row, then we wont need to swap rows.
		{
			matrix.pop_back();	
		}
		else
		{
			for (int i = num; i < rows-1; i++)	
			{
				swap(matrix[i],matrix[i+1]);	// loop for pushing the row the last row so that we can delete with popback				
			}
			matrix.pop_back();
		}
		charnum = s.length();		// word has found so number of chars needed to calculation
	}
	return charnum; // returning number of chars to calculation later in the main func. if word not found, its 0.
}

int TopToDown(vector<vector<char> > & matrix,string s, int rows, int cols)
{
	string line;	//string variable that we re gonna assign characters in rows.
	bool wordfound = false;
	int num;	//int variable to save which index the word is found.
	int charnum = 0; // number of characters variable in case the word is found.
	int tempk;	//temporary variables to check word priority in case matrix has the same word twice.
	int tempj;	//temporary variables to check word priority in case matrix has the same word twice.
	int num2 = -1;
	for (int j = 0; j < cols; j++)
	{
		for (int k = 0; k < rows; k++)
		{
			line += matrix[k][j]; // bringing together the characters of the matrix of that line.			
			
			if (strstr(line.c_str(),s.c_str()))		//Condition if word is in the string.
			{
				
				tempk = k;
				tempj = j;
				if (num2 == -1 || num2 > tempk) // -1 if is the if the word found first time, num2 > tempk is to prioritize.
				{
					num2 = tempk;
					num = j; //num selection is basically choosing word priority, because columns get deleted depending on num.
				}
				else if (num2 == tempk) // if same words are in the same row numbers
				{
					if (tempj < num) // then column numbers are the priority.
					{
						num = j;//num selection is basically choosing word priority, because columns get deleted depending on num.
					}
				}
				wordfound = true;						
				break;
			}
		}
		line.clear();	// clear the string to read the next column.		
	}
	if (wordfound == true)
	{
		cout << "Word " << s << " is found." << endl;	
		if (num == cols-1)//if the word is in the last column, no need to swap, just delete last element of all rows
		{
			for (int i = 0; i < rows; i++)
			{
				matrix[i].pop_back();
			}
		}
		else   // if the element is in the middle, swap that column to the last line so that we can delete last element
		{
			for (int i = 0; i < rows; i++) 
			{
				for (int x = num; x < cols-1; x++)
				{
					swap(matrix[i][x],matrix[i][x+1]);
				}
			}
			for (int i = 0; i < rows; i++)
			{
				matrix[i].pop_back();
			}
		}
		charnum = s.length();	// word has found so number of chars needed to calculation
	}
	return charnum; // returning number of chars to calculation later in the main func. if word not found, its 0.
}

int DownToTop(vector<vector<char> > & matrix,string s, int rows, int cols)
{
	string line;	//string variable that we re gonna assign characters in rows.
	bool wordfound = false;
	int num;	//int variable to save which index the word is found.
	int charnum = 0; // number of characters variable in case the word is found.
	int tempk;	//temporary variables to check word priority in case matrix has the same word twice.
	int tempj;	//temporary variables to check word priority in case matrix has the same word twice.
	int num2 = -1;	// -1 is to make sure it has a default value. index starts with 0 its out of range.
	for (int j = 0; j < cols; j++)
	{
		for (int k = rows-1; k >= 0; k--)
		{
			line += matrix[k][j]; // bringing together the characters of the matrix of that line.						
			if (strstr(line.c_str(),s.c_str()))		//Condition if word is in the string.
			{
				wordfound = true;
				tempk = k;
				tempj = j;
				if (num2 == -1 || num2 > tempk) // -1 if is the if the word found first time, num2 > tempk is to prioritize.
				{
					num2 = tempk;
					num = j; //num selection is basically choosing word priority, because columns get deleted depending on num.
				}
				else if (num2 == tempk) // if same words are in the same row numbers
				{
					if (tempj < num) // then column numbers are the priority.
					{
						num = j;//num selection is basically choosing word priority,because columns get deleted depending on num.
					}
				}
			}
		}
		line.clear();
				
	}
	if (wordfound == true)
	{
		cout << "Word " << s << " is found." << endl;
		if (num == cols-1)//if the word is in the last column, no need to swap, just delete last element of all rows
		{
			for (int i = 0; i < rows; i++)
			{
				matrix[i].pop_back();
			}
		}
		else   // if the element is in the middle, swap that column to the last line so that we can delete last element
		{
			for (int i = 0; i < rows; i++) 
			{
				for (int x = num; x < cols-1; x++)
				{
					swap(matrix[i][x],matrix[i][x+1]);
				}
			}
			for (int i = 0; i < rows; i++)
			{
				matrix[i].pop_back();
			}
		}
		charnum = s.length();
	}
	return charnum; // returning number of chars to calculation later in the main func. if word not found, its 0.
}

int main()
{
	string sfile;
	ifstream inputfile;
	cout << "Welcome to Word Seek.\nPlease enter a filename for the puzzle: ";
	cin >> sfile;
	inputfile.open(sfile.c_str()); 
	while (!(inputfile.is_open())) // loop to make user write the right text file.
	{
		cout << "Failed..\nPlease enter another filename for the puzzle: ";
		cin >> sfile;
		inputfile.open(sfile.c_str());
	}
	cout << "Success!\nPuzzle:" << endl;	
	vector<vector<char> > matrix;
	string line;	
	while(!inputfile.eof())		// reading the file and filling the matrix
	{
		getline(inputfile,line);
		stringstream ss(line);
		char character;
		vector<char> temp;	// temp vector to pushback each line to matrix
		if (!(isdigit(line[0]))) // condition to not add the row and column numbers to matrix to make matrix words only.
		{
			while (ss >> character)
			{			
				temp.push_back(character);						
			}
			matrix.push_back(temp);
		}		
	}
	inputfile.close();
	int rows = matrix.size(); //defining row number
	int cols = matrix[0].size(); //defining column number
	bool gameOn = true;		// to keep the game loop going.
	int totalPoint = 0;
	printmatrix(matrix,rows,cols);
	while (gameOn)
	{
		int point1 = 0;
		int point2 = 0;
		int point3 = 0;
		int point4 = 0;		
		cout << "Please enter a word: ";
		string word;
		cin >> word;		
		if (word.length() < 3)
		{
			cout << "Game has ended.\nTotal points: " << totalPoint << "." << endl;
			break;
		}
		point1 = LeftToRight(matrix,word,rows,cols);
		if (point1 != 0)
		{			
			totalPoint += point1;
			cout << point1 << " points are earned." << endl;
			rows --;
			cout << "Total points: " << totalPoint << "." << endl;			
		}
		else
		{
			point2 = RightToLeft(matrix,word,rows,cols);
			if (point2 != 0)
			{			
				point2 = point2 *2 ;
				totalPoint += point2;				
				cout << point2 << " points are earned." << endl;
				rows --;
				cout << "Total points: " << totalPoint << "." << endl;				
			}
			else
			{
				point3 = TopToDown(matrix,word,rows,cols);
				if (point3 != 0)
				{
					point3 = point3 + 2;
					totalPoint += point3;					
					cout << point3 << " points are earned." << endl;
					cols --;
					cout << "Total points: " << totalPoint << "." << endl;					
				}
				else
				{
					point4 = DownToTop(matrix,word,rows,cols);
					if (point4 != 0)
					{						
						point4 = (point4*2) + 2;
						totalPoint += point4;
						cout << point4 << " points are earned." << endl;
						cols --;
						cout << "Total points: " << totalPoint << "." << endl;						
					}
					else
					{
						totalPoint -= 5;
						cout << "The word cannot be found in the puzzle.\n5 points are deducted." << endl;
						cout << "Total points: " << totalPoint << "." << endl;
						continue;
					}
				}
			}			
		}
		if (rows == 0 || cols == 0)
		{
			totalPoint += 20;
			cout << "Puzzle is cleared. 20 extra points are earned.\nTotal points: " << totalPoint << "." << endl;
			cout << "Game has ended.\nTotal points: " << totalPoint << "."<< endl;
			break;
		}
		cout << "Puzzle:" << endl;
		printmatrix(matrix,rows,cols);		
	}
	return 0;
}