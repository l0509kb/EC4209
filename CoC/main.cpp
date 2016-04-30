#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bitset>

#include "Student.h"
#include "Course.h"

using namespace std;

// variables
bool isParsed = false;
vector<Student*> student_list;
vector<Course*> course_list;

// function prototypes
bool in_conversion(const char* path);
int check_track(char x, char y);

int main()
{
	// (i) 매번 실행할 때마다 파일 경로를 넣고 싶으면 이걸 쓰셈
	char* path = new char[100];
	cout << "Enter the directory path to the Git Project: " << endl;
	cout << "(Example) C:\\\\Users\\\\USER\\\\Documents\\\\GitHub\\\\EC4209\\\\CoC\\\\" << endl;
	cin.getline(path, 100);
	isParsed = in_conversion(path);

	// (ii) 귀찮으면 이 부분을 수정하도록. 각자 자신의 파일경로를 추가하셈. 
	// 뭔가 자신의 컴퓨터와 상관없이 이 프로젝트가 있는 폴더 안에서 실행하는 방법이 있긴 한데 그게 Resource Files를 쓰는 방법인데 난 복잡해서 못 하겟음
	//isParsed = in_conversion("C:\\Users\\USER\\Documents\\GitHub\\EC4209\\CoC\\");// 서영이의 경로다
	//isParsed = in_conversion("어쩌고\\저쩌고\\");// 홍길동의 경로다

	
	if (isParsed)
	{
		for (int i = 0; i < student_list.size(); i++)
			student_list[i]->print_student();
		for (int j = 0; j < course_list.size(); j++)
			course_list[j]->print_reg_students();
	}
	
	return 0;
}

bool in_conversion(const char* path)
{
	int id, year, unit;
	char* major; char* minor;
	char* prefix; int num;

	// creating output.txt
	ofstream output;
	string s = path;
	output.open(s + "output.txt");

	// read in test.txt
	string p = s + "test3.txt";
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
	bool first = true;

	for (int i = 0; code[i] != '\0'; i++)
	{

		// year
		int year = 2000 + (code[i] - '0') * 10 + (code[i + 1] - '0');
		i += 2;
		
		// Major, minor
		int major = 0; int minor = 0;
		char x = code[i]; char y = code[i + 1];
		major = check_track(x, y);
		i += 2;			
		x = code[i]; y = code[i + 1];
		minor = check_track(x, y);
		i += 2;

		Student* S = new Student(s_id, year, major, minor);

		// add courses with track and number
		while (code[i] != '\n')
		{
			int track, num;
			x = code[i]; y = code[i + 1];
			track = check_track(x, y);
			i += 2;
			x = code[i]; y = code[i + 1];
			num = (x - '0') * 10 + (y - '0');
			i += 2;
			//S->push_course(track, num);
			
			if (first)
			{
				Course* C = new Course(track, num);
				course_list.push_back(C);
				C->push_student(S);
				S->push_course(track, num);
				first = false;
			}
			else
			{
				// find if the course is already in course_list
				bool exist = false;
				for (int j = 0; j < course_list.size(); j++)
				{
					if ((course_list[j]->get_num() == num) && (course_list[j]->get_track() == track))
					{
						course_list[j]->push_student(S);
						S->push_course(track, num);
						exist = true;
						break;
					}
				}

				if (!exist)
				{
					Course* C = new Course(track, num);
					course_list.push_back(C);
					C->push_student(S);
					S->push_course(track, num);
				}
			}
		}
		student_list.push_back(S);
		s_id++;
	}

	return true;
}

int check_track(char x, char y)
{
	if ((x == 'N') || (x == 'g'))
		return 1;
	else if (x == 'b')
		return 2;
	else if (x == 'c')
	{
		if (y == 'h')
			return 3;
		else
			return 4;
	}
	else if (x == 'e')
		return 5;
	else if (x == 'm')
	{
		if (y == 'a')
			return 6;
		else
			return 7;
	}
	else
		return 8;
}