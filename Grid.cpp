/* Implements the grid class for a word search which holds and accesses a character matrix
*/

#include <grid.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <locale>
#include <sstream>
#include <string>
#include <d_except.h>

class Grid
{
	public:
		Grid();
		Grid(string filename);
		void setGrid(string filename);
		const char getChar(const int m, const int n);
		const int getSize();
		
	protected:
		vector<vector<char>> lttrs;
		int size;
}

const int Grid::getSize() {return size;}

const char Grid::getChar(const int m, const int n)
{	return lttrs[m][n]; }

Grid::Grid() {size = 0;}

Grid::Grid(string filename) { setGrid(filename); }
// sets the grid to the values of the given file
void Grid::setGrid(string filename)
{
	// open file
	ifstream gridfile(filename);
	// attempt to read line with size of file
	string line;
	if(gridfile.is_open())
	{
		getline(myfile,line); // read first line
		char * pch =strtok(line," "); // split string by space character token
		istringstream convert(pch); // stringstream used for the conversion constructed with the contents of 'pch' 
                             		// ie: the stream will start containing the characters of 'Text'
		if ( !(convert >> size) ) //give the value to 'size' using the characters in the stream
    	{ throw BaseException("Unable to read grid size!"); }    //if that fails throw error
	}
	else { throw BaseException("Unable to open grid file!"); }
	
	// create/size the data vectors
	lttrs.resize(size); // size number of rows
	lttrs.assign(size,vector<char>(size,'\0')); // assign copies of rows
	
	// read the characters from the rest of the file
	// temporary free character
	char *ch;
	for(int i=0;i<size,i++)
	{
		for(int j=0;j<size;j++)
		{
			gridfile.read(ch,1); // read a character
			if(*ch = '\s') // ignore spaces
			{ j--; } // move index back for spaces
			else if((*ch = '\n') || (*ch = '\r')) // skip to next row if encountering new line or return 
			{ break; } // move to next row
			else
			{ lttrs[i][j] = *ch; } // store character
			// validate character
			if((((int)(*ch)) < 97) || (((int)(*ch)) > 122)) { throw BaseException("Warning: illegal character!"); }
		}
	}
	if(!gridfile.eof()) { throw BaseException("Warning: Not at end of file!"); }
	// close file
	gridfile.close();
}
