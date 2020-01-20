#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "DynIntStack.h"

using namespace std;
// murat nuhoðlu 24014
unsigned int spacecounter(string & line)//this function counts the number of space at the beginning of each line
{
	unsigned int j=0;
	while (line[j]==' ')
		j++;
	return j;
}

void deletestack(DynIntStack stack)//this function deletes the stack
{
	cout << endl << "Stack emptied and program ending." << endl;
	int k;
	while(!stack.isEmpty())
		stack.pop(k);
}
int main()
{
	string filename, s;											
	ifstream i;
	cout << "Please enter the file name that is going to be analyzed." << endl;				//file name taken as input
	cin >> filename;
	i.open(filename.c_str());

	while (i.fail()) //checks if the file opened correctly
	{
		cout << "Unable to open file please enter a different file name."<< endl;
		cin >> filename;
		i.open(filename.c_str());
	}cout << "Starting file analysis... " << endl << "Initial indentation level is pushed to the stack as 0. " << endl << endl;
	DynIntStack stack;stack.push(0);
	int k = 1;
	int currlevel=0;
	bool check=false;
	while(getline(i,s))//this loop keeps turning as long as program gets line from the file
	{
		cout << "Line number: " << k << endl;
		cout << "Line: " << s << endl;
		unsigned int space = spacecounter(s);
		cout << space << " number of spaces observed before the start of the line." << endl;		
	//if there were a keyword in the previous line this if statement executes
		if(check){cout << "This line proceeds a keyword containing line." << endl <<  "Current level = " << currlevel << " This line = " << space << endl;
		if(currlevel >= space){	
			cout << "Incorrect file structure." << endl << "Current line must be greater than the Current indentation level."<< endl << "Stopping file analysis..." <<endl;deletestack(stack);return 0;}
		else if(space > currlevel)
		{
			cout << "Line correct. Depth " << space << " added to stack." << endl;
			stack.push(space);
		}}
		else{//this else statement is written for the lines who does not have keyword in previous line.
		if(currlevel == space)
			cout <<  "Current level = " << currlevel << " This line = " << space << endl << "Line belongs to current block." << endl;
		else if(space > currlevel){	cout <<  "Current level = " << currlevel << " This line = " << space << endl ;
			cout << "Incorrect file structure." << endl << "Current line must be greater than the Current indentation level."<< endl << "Stopping file analysis..." <<endl;deletestack(stack); return 0;}
		else if(space < currlevel){//this statement checks the outer blocks to check if current line belongs to other block
			stack.pop(currlevel);
			
			while(space < currlevel){
			cout << "Current Level = " << currlevel << " This line = " << space << endl;
				cout << "Current line is smaller than Current indentation level; checking if line belongs to outer indentation." << endl;
				stack.pop(currlevel);}stack.push(currlevel);
				cout << "Current Level = " << currlevel << " This line = " << space << endl;
				if(space < currlevel){
				cout << "Incorrect file structure." << endl << "An indentation level same as the Current line is not found in outer blocks." << endl;
				cout <<"Stopping file analysis..."<< endl;
				deletestack(stack);return 0;}cout << "Line belongs to outer block." << endl;
		}
		}
			
		istringstream iss(s);
		string keyword;//i take the line string by string to check if there are key word
		iss >> keyword;
		check = false;
		if(keyword=="while" || keyword=="if" || keyword=="else" || keyword=="elif" || keyword=="for")//i checked if there are a keyword in this line.
		{
			cout << "Keyword " << keyword << " found on this line." << endl;
			check = true;
		}k++;cout << endl;currlevel=space;
	}cout << "Finished file analysis. File structure is correct!";//if this line of code is executed it means there were no errors. 
	deletestack(stack);
	return 0;
}