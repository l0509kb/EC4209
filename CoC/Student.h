#pragma once
#include <vector>
#include "Course.h"

using namespace std;

class Student{
public:
	Student(int _id, int _year, int _maj, int _min)
	{
		id = _id;
		year = _year;
		major = _maj;
		minor = _min;
	}

	void print_course_list()
	{
		for (int i = 0; i < course_list.size(); i++)
		{
			int num = course_list[i]->get_num();
			switch (course_list[i]->get_track())
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
		}

		printf("\n\n");
	}

	void print_student()
	{
		printf("ID: %02i Year: %04i", id, year);
		
		switch (major)
		{
		case 1:
			printf(" Mj: gs");
			break;
		case 2:
			printf(" Mj: bi");
			break;
		case 3:
			printf(" Mj: ch");
			break;
		case 4:
			printf(" Mj: cs");
			break;
		case 5:
			printf(" Mj: ev");
			break;
		case 6:
			printf(" Mj: ma");
			break;
		case 7:
			printf(" Mj: me");
			break;
		case 8:
			printf(" Mj: ph");
			break;
		}

		switch (minor)
		{
		case 1:
			printf(" mn: NA\n");
			break;
		case 2:
			printf(" mn: bi\n");
			break;
		case 3:
			printf(" mn: ch\n");
			break;
		case 4:
			printf(" mn: cs\n");
			break;
		case 5:
			printf(" mn: ev\n");
			break;
		case 6:
			printf(" mn: ma\n");
			break;
		case 7:
			printf(" mn: me\n");
			break;
		case 8:
			printf(" mn: ph\n");
			break;
		}

		print_course_list();
	}

	void push_course(int track, int num)
	{
		Course* c = new Course(track, num);
		course_list.push_back(c);
	}



private:
	vector<Course*> course_list;
	// unit
	int id, year;
	int major; int minor;

};