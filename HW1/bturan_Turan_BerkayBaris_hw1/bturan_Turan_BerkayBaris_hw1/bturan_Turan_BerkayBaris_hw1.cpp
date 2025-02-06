/***************************
	Author: Berkay Baris Turan
	Date: 07.03.2021
***************************/
#include <iostream>
#include <string>
#include <fstream>
#include <sstream> //for istringstream
#include <vector>
using namespace std;

bool input_check(int row_index, int column_index, string direction, string orientation, vector<vector<char>> & matrix)
// function that checks every component of the line
// if there is a wrong component, returns false and prints an appropriate massage.
{
	if((row_index < 0) || (row_index >=matrix.size()) || (column_index < 0) || (column_index >=matrix[0].size()))
	{
		cout << "Starting point is out of range! Point: " << row_index << "," << column_index << endl;
		cout << endl;
		return false;
	}
	else if ((direction != "l") && (direction != "r") && (direction != "u") && (direction != "d"))
	{
		cout << "Invalid input for direction! Direction: " << direction << endl;
		cout << endl;
		return false;
	}
	else if ((orientation != "CW") && (orientation != "CCW"))
	{
		cout << "Invalid input for orientation! Orientation: " << orientation << endl;
		cout << endl;
		return false;
	}
	else
	{
		return true;
	}
}

void clockwise(string & direc)
//function that changes direction in terms of CW order.
{
	if(direc == "r")
		direc = "d";

	else if(direc == "d")
		direc = "l";

	else if(direc == "l")
		direc = "u";

	else if(direc == "u")
		direc = "r";
}

void counter_clockwise(string & direc)
//function that changes direction in terms of CCW order.
{
	if(direc == "r")
		direc = "u";

	else if(direc == "u")
		direc = "l";

	else if(direc == "l")
		direc = "d";

	else if(direc == "d")
		direc = "r";
}

bool right(int row, int column, vector<vector<char>> & matrix)
//checks whether location on the right of the current location is suitable or not.
//returns true if suitable.
{
	int col = column + 1;
	if((col < 0) || (col > matrix[0].size()-1))
		return false;

	else if(matrix[row][col] != '-')
		return false;

	else
		return true;
}

bool left(int row, int column, vector<vector<char>> & matrix)
//checks whether location on the left of the current location is suitable or not.
//returns true if suitable.
{
	int col = column -1;
	if((col < 0) || (col > matrix[0].size()-1))
		return false;

	else if(matrix[row][col] != '-')
		return false;

	else
		return true;
}

bool up(int row, int column, vector<vector<char>> & matrix)
//checks whether location on the upper side of the current location is suitable or not.
//returns true if suitable.
{
	int rw = row -1;
	if((rw < 0) || (rw > matrix.size()-1))
		return false;

	else if(matrix[rw][column] != '-')
		return false;

	else
		return true;
}

bool down(int row, int column, vector<vector<char>> & matrix)
//checks whether location on the down side of the current location is suitable or not.
//returns true if suitable.
{
	int rw = row +1;
	if((rw < 0) || (rw > matrix.size()-1))
		return false;

	else if(matrix[rw][column] != '-')
		return false;

	else
		return true;
}

void right_place(char chr, int & row, int & column, vector<vector<char>> & matrix)
//places correresponding letter to the right side of the current location.
{
	int coll = column++;
	matrix[row][column] = chr;
}

void left_place(char chr, int & row, int & column, vector<vector<char>> & matrix)
//places correresponding letter to the left side of the current location.
{
	column--;
	matrix[row][column] = chr;
}

void up_place(char chr, int & row, int & column, vector<vector<char>> & matrix)
//places correresponding letter to the upper side of the current location.
{
	row--;
	matrix[row][column] = chr;
}

void down_place(char chr, int & row, int & column, vector<vector<char>> & matrix)
//places correresponding letter to the down side of the current location.
{
	row++;
	matrix[row][column] = chr;
}

void placement(string word, int row_index, int column_index, string direction, string orientation, vector<vector<char>> & matrix)
//this fucntion places all letters of the word into the matrix according to the indexes, direction, orientation.
{
	int length_of_word = word.length();
	int constant_column = column_index;
	int constant_row = row_index;


	for(int d = 0; d < length_of_word;)
	{
		if(d == 0)
		{
			if(matrix[row_index][column_index] == '-')
			{
				matrix[row_index][column_index] = word[d];
				d++;
			}
			else
			{
				cout << "\"" << word << "\" could not be put into the matrix with given starting point: " << row_index << "," << column_index
					<< "   direction: " << direction << "   orientation: " << orientation << endl;
				break;
			}
		}
		else
		{
			int loop_num = 1;
			string direc = direction;
			while(loop_num<= 4)
			//there are max 4 different directions, if non of them is suitable, loop ends. 
			{
				if(direc =="r")
				{
					if(right(row_index,column_index,matrix))
					{
						right_place(word[d],row_index,column_index,matrix);
						d++;
						break;
					}
					else
					{
						if(orientation == "CW")
							clockwise(direc);
						else
							counter_clockwise(direc);
						loop_num++;
					}
				}
				else if (direc == "l")
				{
					if(left(row_index,column_index,matrix))
					{
						left_place(word[d],row_index,column_index,matrix);
						d++;
						break;
					}
					else
					{
						if(orientation == "CW")
							clockwise(direc);
						else
							counter_clockwise(direc);
						loop_num++;
					}
				}
				else if (direc == "u")
				{
					if(up(row_index,column_index,matrix))
					{
						up_place(word[d],row_index,column_index,matrix);
						d++;
						break;
					}
					else
					{
						if(orientation == "CW")
							clockwise(direc);
						else
							counter_clockwise(direc);
						loop_num++;
					}
				}
				else if (direc == "d")
				{
					if(down(row_index,column_index,matrix))
					{
						down_place(word[d],row_index,column_index,matrix);
						d++;
						break;
					}
					else
					{
						if(orientation == "CW")
							clockwise(direc);
						else
							counter_clockwise(direc);
						loop_num++;
					}
				}
			}
		}
	}
	cout << "\"" << word << "\" was put into the matrix with given starting point: " << constant_row << "," << constant_column <<
		"   direction: " << direction << "   orientation: " << orientation << endl;
}

bool placement_bool(string word, int row_index, int column_index, string direction, string orientation, vector<vector<char>> & matrix)
//before placing word to the matrix, this fucntion checks whether all of the letters of the word suits to the matrix.
//returns true if the word can be placed.
{
	int length_of_word = word.length();
	int true_counter = 0;

	int const_row = row_index;
	int const_column = column_index;

	vector<vector<char>> trial(matrix.size(),vector<char>(matrix[0].size(),'-')); 

	for (int l = 0; l<matrix.size(); l++)
		for(int a=0; a<matrix[0].size(); a++)
			trial[l][a] = matrix[l][a];

	for(int d = 0; d < length_of_word;)
	{
		if(d == 0)
		{
			if(trial[row_index][column_index] == '-')
			{
				trial[row_index][column_index] = word[d];
				true_counter++;
				d++;
			}
			else
			{
				cout << "\"" << word << "\" could not be put into the matrix with given starting point: " << const_row << "," << const_column
					<< "   direction: " << direction << "   orientation: " << orientation << endl;
				return false;
			}
		}
		else
		{
			int loop_num = 1;
			string direc = direction;
			while(loop_num<= 4)
			{
				if(direc =="r")
				{
					if(right(row_index,column_index,trial))
					{
						right_place(word[d],row_index,column_index,trial);
						true_counter++;
						d++;
						break;
					}
					else
					{
						if(orientation == "CW")
							clockwise(direc);
						else
							counter_clockwise(direc);
						loop_num++;
					}
				}
				else if (direc == "l")
				{
					if(left(row_index,column_index,trial))
					{
						left_place(word[d],row_index,column_index,trial);
						true_counter++;
						d++;
						break;
					}
					else
					{
						if(orientation == "CW")
							clockwise(direc);
						else
							counter_clockwise(direc);
						loop_num++;
					}
				}
				else if (direc == "u")
				{
					if(up(row_index,column_index,trial))
					{
						up_place(word[d],row_index,column_index,trial);
						true_counter++;
						d++;
						break;
					}
					else
					{
						if(orientation == "CW")
							clockwise(direc);
						else
							counter_clockwise(direc);
						loop_num++;
					}
				}
				else if (direc == "d")
				{
					if(down(row_index,column_index,trial))
					{
						down_place(word[d],row_index,column_index,trial);
						true_counter++;
						d++;
						break;
					}
					else
					{
						if(orientation == "CW")
							clockwise(direc);
						else
							counter_clockwise(direc);
						loop_num++;
					}
				}
			}
			if(loop_num > 4)
			{
				cout << "\"" << word << "\" could not be put into the matrix with given starting point: " << const_row << "," << const_column
					<< "   direction: " << direction << "   orientation: " << orientation << endl;
				return false;
			}
			else if(true_counter == length_of_word)
			{
				return true;
			}
		}
	}

}

void print(vector<vector<char>> & matrix)
//function for printing the matrix
{
	for(int i=0; i<matrix.size();i++){
		for(int j=0; j<matrix[0].size();j++){
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}

int main()
{
	string file_name;
	ifstream input; 
	
	cout << "Please enter the name of the file: ";
	cin >> file_name;
	cout << endl;
	input.open(file_name.c_str());

	while(input.fail())
	// Checks whether the input file is opened or not.
	{
		cout << "File name is incorrect, please enter again: ";
		cin >> file_name;
		input.open(file_name.c_str());
		cout << endl;
	}

	string line;
	int row_num, column_num;
	
	getline(input,line);
	istringstream inp1(line);
	inp1 >> row_num >> column_num;



	if ((row_num <= 0) || (column_num <= 0))
	{
		cout << "Invalid number for row and/or column!" << endl;
		cout << endl;
	}

	else
	{
		vector<vector<char>> matrix(row_num,vector<char> (column_num,'-'));

		while(getline(input,line))
		{

			int row_index, column_index, num_component = 0;
			string word, direction, orientation;
			string check_word; //for chekcing number of components.
			istringstream check(line);

			while(check >> check_word)
			//counting number of components.
			{
				num_component++;
			}

			if(num_component!= 5)
			{
				cout << "Invalid line! Number of values is different than 5." << endl;
				cout << endl;
			}

			else
			{
				istringstream inp2(line);
				inp2 >> word >> row_index >> column_index >> direction >> orientation;

				if (input_check(row_index, column_index, direction, orientation, matrix))
				// if there are no incorrect inputs, it passes to placement process.
				// if there are some incorrect inputs, it displays appropriate error masseges, don't continue with placement process.
				{
					if(placement_bool(word,row_index,column_index,direction,orientation,matrix))
					{
						placement(word,row_index,column_index,direction,orientation,matrix);
					}
					print(matrix);
					cout << endl;
				}
			}
		}
	}
	return 0;
}