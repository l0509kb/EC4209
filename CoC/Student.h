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
			printf(" ( GS");
			break;
		case 2:
			printf(" ( BI");
			break;
		case 3:
			printf(" ( CH");
			break;
		case 4:
			printf(" ( CS");
			break;
		case 5:
			printf(" ( EV");
			break;
		case 6:
			printf(" ( MA");
			break;
		case 7:
			printf(" ( ME");
			break;
		case 8:
			printf(" ( PH");
			break;
		}

		switch (minor)
		{
		case 1:
			printf(" , NA )\n");
			break;
		case 2:
			printf(" , bi )\n");
			break;
		case 3:
			printf(" , ch )\n");
			break;
		case 4:
			printf(" , cs )\n");
			break;
		case 5:
			printf(" , ev )\n");
			break;
		case 6:
			printf(" , ma )\n");
			break;
		case 7:
			printf(" , me )\n");
			break;
		case 8:
			printf(" , ph )\n");
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