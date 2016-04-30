#pragma once

#include <vector>
#include <iostream>
#include "Student.h"

using namespace std;

class Course{
public:
	Course(int _track, int _num)
	{
		track = _track;
		num = _num;
	}

	// get course track
	int get_track(){ return track; }
	// get course num
	int get_num(){ return num; }

	// register a student
	void push_student(Student* S)
	{
		student_list.push_back(S);
	}

	// print the registered students by their ID
	void print_reg_students()
	{
		print_course_name();
		for (int i = 0; i < (int)student_list.size(); i++)
			cout << student_list[i]->get_id() << " ";
		cout << endl << endl;
	}

	// print the course name = track + numb
	void print_course_name()
	{
		switch (track)
		{
		case 1:
			printf("gs%02i ", num);
			break;
		case 2:
			printf("bi%02i ", num);
			break;
		case 3:
			printf("ch%02i ", num);
			break;
		case 4:
			printf("cs%02i ", num);
			break;
		case 5:
			printf("ev%02i ", num);
			break;
		case 6:
			printf("ma%02i ", num);
			break;
		case 7:
			printf("me%02i ", num);
			break;
		case 8:
			printf("ph%02i ", num);
			break;
		}
		printf("\n");
	}

private:
	int track;
	int num;
	vector<Student*> student_list;
};