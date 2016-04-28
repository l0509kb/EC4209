#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Student.h"

using namespace std;

// variables
bool isParsed = false;
vector<Student> student_list;

// function prototypes
bool inputConversion(const char* path);



int main()
{
	// Parsing
	isParsed = inputConversion("C:\\Users\\USER\\Desktop\\2016_1\\AI\\project\\");
	for (int i = 0; i < student_list.size(); i++)
		printf("ID: %02i Year: %04i\n", student_list[i].id, student_list[i].year);
	
	return 0;
}

bool inputConversion(const char* path)
{
	int id, year, unit;
	char* major; char* minor;
	char* prefix; int num;

	// creating output.txt
	ofstream output;
	string s = path;
	output.open(s + "output.txt");

	// read in test.txt
	string p = s + "test2.txt";
	FILE* file = fopen(p.c_str(), "r");
	int c;

	while ((c = fgetc(file)) != EOF) 
	{
		// characters that are neither delims nor separators
		if (((char)c != ',') && ((char)c != '\t') && ((char)c != '\"') && ((char)c != ' '))
		{
			// unit
			if ((char)c == '(')
			{
				c = fgetc(file); c = fgetc(file); c = fgetc(file);
			}
			else
				output << (char)c;
		}
	}
	output.close();
	fclose(file);

	string s2 = s + "output.txt";
	FILE* file2 = fopen(s2.c_str(), "r");
	char* code;
	size_t n = 0;
	int c2;

	// end if file is empty
	if (file2 == NULL)
		return false;

	// find and allocate file size
	fseek(file2, 0, SEEK_END);
	long f_size = ftell(file2);
	fseek(file2, 0, SEEK_SET);
	code = (char*)malloc(f_size);

	while ((c2 = fgetc(file2)) != EOF) 
		code[n++] = (char)c2;

	code[n] = '\0';
	fclose(file2);

	int s_id = 1;

	for (int i = 0; code[i] != '\0'; i++)
	{
		while (code[i] != '\n')
		{
			int year = 2000 + (code[i] - '0') * 10 + (code[i + 1] - '0');
			i += 2;
			while (code[i] != '\n')
				i++;
			Student S(s_id, year);
			student_list.push_back(S);
			s_id++;
		}

	}

	return true;
}