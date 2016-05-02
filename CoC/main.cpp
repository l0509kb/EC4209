#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bitset>

#include <math.h>
#include <glut.h>
#include <gl.h>
#include <glu.h>

#include "Student.h"
#include "Course.h"
#include "Graph.h"

#define PI 3.1415926

using namespace std;

// graphical interface
void display();
void reshape(int w, int h);
void keyboard(unsigned char key, int x, int y);
float rotate_angle = 0.0f;
float threshold = 0.0f;

// variables
bool is_parsed = false;
vector<Student*> student_list;
vector<Course*> course_list;
Graph* multi_graph;
Graph* simple_graph;

// function prototypes
bool in_conversion(const char* path);
int check_track(char x, char y);
Graph* build_multi_graph(void);
void compute_correlation(Graph* G, int index_i, int index_j, Course* cour_i, Course* cour_j);
Graph* build_simple_graph(void);

int main(int argc, char** argv)
{
	/*
	// (i) 매번 실행할 때마다 파일 경로를 넣고 싶으면 이걸 쓰셈
	char* path = new char[100];
	cout << "Enter the directory path to the Git Project: " << endl;
	cout << "(Example) C:\\\\Users\\\\USER\\\\Documents\\\\GitHub\\\\EC4209\\\\CoC\\\\" << endl;
	cin.getline(path, 100);
	is_parsed = in_conversion(path);
	*/

	// Add your own home directory
	int user_id;
	char* home_dir = " ";
	cout << "Giyeon[1] Sunwoo_lab[2] Kyubin[3] Seoyoung_room[4] Seoyoung_lab[5]" << endl << "Enter user number:";
	cin >> user_id;

	switch (user_id)
	{
	case 1:
		home_dir = "C:\\Users\\user\\Documents\\GitHub\\EC4209\\CoC\\";
		break;
	case 2:
		home_dir = "C:\\Users\\cvlab2243\\Source\\Repos\\EC4209\\CoC\\";
		break;
	case 3:
		home_dir = "C:\\Users\\규빈\\Documents\\EC4209-ClashOfClass\\EC4209-ClashOfClass\\CoC\\";
		break;
	case 4:
		home_dir = "C:\\Users\\USER\\Documents\\GitHub\\EC4209\\CoC\\";
		break;
	case 5:
		home_dir = "C:\\Users\\June\\Documents\\GitHub\\EC4209\\CoC\\";
		break;
	}

	is_parsed = in_conversion(home_dir);

	// result print out on console
	if (is_parsed)
	{
		for (int i = 0; i < student_list.size(); i++)
			student_list[i]->print_student_info();
		for (int j = 0; j < course_list.size(); j++)
			course_list[j]->print_student_list();
	}

	/* simple course list test */
	/*for (int i = 0; i < 3; i++)
		student_list[i]->print_student_info();*/
	/*for (int j = 0; j < 3; j++)
		course_list[j]->print_student_list();*/

	/* Build Multi Graph
	 *  builds a directed graph
	 *  with bidirectional correlation coefficients
	 */
	vector<Course*> course_list_test = \
		{course_list[0], course_list[1], course_list[2]};
	//G = build_graph(course_list);
	multi_graph = build_multi_graph();
	/* graph print test */
	multi_graph->file_print_graph(home_dir, "directed_graph.txt");

	/* Build Simple Graph
	 *  conversion from the bidirectional graph to a simple weighted graph
	 *  need specific models to merge the correlation coefficients
	 */
	simple_graph = build_simple_graph();
	simple_graph->file_print_graph(home_dir, "simple_graph.txt");

	// graphical interface
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1000, 1000);
	glutCreateWindow("Graph");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();

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
			
			if (first)
			{
				Course* C = new Course(track, num);
				course_list.push_back(C);
				C->enroll_student(S);
				S->register_course(track, num);
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
						course_list[j]->enroll_student(S);
						S->register_course(track, num);
						exist = true;
						break;
					}
				}

				if (!exist)
				{
					Course* C = new Course(track, num);
					course_list.push_back(C);
					C->enroll_student(S);
					S->register_course(track, num);
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

Graph* build_multi_graph(void)
{
	Graph* G = new Graph();
	for (int i = 0; i < course_list.size(); i++)
	{
		// add index (node)
		G->add_index(course_list[i]);

		// add 
		for (int j = i; j < course_list.size(); j++)
		{
			// add index if j is not found in index
			if (i == 0 || i != j)
				G->add_index(course_list[j]);
			
			compute_correlation(G, i, j, course_list[i], course_list[j]);
			//G->set_correlation(course_list[i], course_list[j], \
				compute_correlation(i, j, course_list[i], course_list[j]));
			
		}
	}

	return G;
}

void compute_correlation(Graph* G, int index_i, int index_j, Course* cour_i, Course* cour_j)
{
	float correlation = 0;

	if (index_i == index_j)
	{
		G->set_correlation(cour_i, cour_j, correlation);
		return;
	}

	vector<Student*>* stud_i;
	vector<Student*>* stud_j;

	stud_i = cour_i->get_ptr_student_list();
	stud_j = cour_j->get_ptr_student_list();

	int intersection = 0;

	for (int s1 = 0; s1 < stud_i->size(); s1++)
		for (int s2 = 0; s2 < stud_j->size(); s2++)
			if (stud_i->at(s1)->get_id() \
				== stud_j->at(s2)->get_id())
				intersection++;

	if (!intersection)
	{
		G->set_correlation(cour_i, cour_j, -neg_inf);
		G->set_correlation(cour_j, cour_i, -neg_inf);
		return;
	}

	float i_to_j = (float)intersection / stud_i->size();
	float j_to_i = (float)intersection / stud_j->size();

	G->set_correlation(cour_i, cour_j, i_to_j);
	G->set_correlation(cour_j, cour_i, j_to_i);
}

Graph* build_simple_graph(void)
{
	Graph* simple_graph = new Graph(multi_graph);
	for (int i = 0; i < course_list.size(); i++)
	{
		for (int j = i + 1; j < course_list.size(); j++)
		{
			Course* cour_i = course_list[i];
			Course* cour_j = course_list[j];

			float corr_ij = simple_graph->get_correlation(cour_i, cour_j);
			float corr_ji = simple_graph->get_correlation(cour_j, cour_i);
			
			/* simplest model that adds up two weights */
			float new_corr = corr_ij + corr_ji;

			simple_graph->modify_correlation(cour_i, cour_j, new_corr);
			simple_graph->modify_correlation(cour_j, cour_i, new_corr);
		}
	}


	return simple_graph;
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	GLfloat size[2];
	GLfloat angle;
	glGetFloatv(GL_POINT_SIZE_RANGE, size);
	glPointSize(size[0] * 6);

	glRotatef(rotate_angle, 0.0, 0.0, 1.0);

	int node_num = multi_graph->get_size();
	char* c = new char[node_num];

	int j = 0;
	for (float angle = 0.0; angle <= 2.0 * PI; angle += 2 * PI / node_num)
	{

		if (j < course_list.size())
		{
			char* name = new char[4];
			name = course_list[j]->get_course_name();
			switch (course_list[j]->get_track())
			{
			case 1:
				glColor3f(1.0, 0.498039, 0.0);
				break;
			case 2:
				glColor3f(0.137255, 0.556863, 0.137255);
				break;
			case 3:
				glColor3f(0.52, 0.39, 0.39);
				break;
			case 4:
				glColor3f(0.196078, 0.8, 0.196078);
				break;
			case 5:
				glColor3f(0.85, 0.85, 0.10);
				break;
			case 6:
				glColor3f(0.498039, 0.53, 1.0);
				break;
			case 7:
				glColor3f(1.00, 0.11, 0.68);
				break;
			case 8:
				glColor3f(0.196078, 0.6, 0.8);
				break;
			}
			j++;

			glBegin(GL_POINTS);
			glVertex3f(80 * cos(angle), 80 * sin(angle), 0.0);
			glEnd();

			glPushMatrix();
			glTranslatef(81 * cos(angle), 81 * sin(angle), 0.0);
			glRotatef(angle * 180 / PI, 0.0, 0.0, 1.0);
			glScalef(0.02f, 0.02f, 1.f);
			for (int i = 0; i < 4; i++)
				glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, name[i]);
			glPopMatrix();
		}
	}

	for (int x = 0; x < course_list.size(); x++)
	{
		for (int y = 0; y < course_list.size(); y++)
		{
			if ((multi_graph->get_correlation_addition(course_list[x], course_list[y]) >= threshold) && multi_graph->get_correlation_addition(course_list[x], course_list[y]) < 10)
			{
				glColor3f(0, 1, 0);
				glBegin(GL_LINE_STRIP);
				glVertex3f(80 * cos(2 * PI / node_num * x), 80 * sin(2 * PI / node_num * x), 0);
				glVertex3f(80 * cos(2 * PI / node_num * y), 80 * sin(2 * PI / node_num * y), 0);
				glEnd();
			}
			//else
			//{
			//	glColor3f(1, 0, 0);
			//	glBegin(GL_LINE_STRIP);
			//	glVertex3f(80 * cos(2 * PI / node_num * x), 80 * sin(2 * PI / node_num * x), 0);
			//	glVertex3f(80 * cos(2 * PI / node_num * y), 80 * sin(2 * PI / node_num * y), 0);
			//	glEnd();
			//}

		}
	}

	glutSwapBuffers(); // this is only used for double buffers
}

void reshape(int w, int h)
{
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluOrtho2D(-100.0, 100.0, -100.0, 100.0);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'r':
		rotate_angle += 1.0f;
		break;
	case 't':
		if (threshold <= 10)
		{ 
			threshold += 0.05f;
			cout << "Current Threshold = " << threshold << endl;
		}
		break;
	}

	glutPostRedisplay();
}