/* Graph.h
 * Graph with courses as vertices,
 * correlation coefficients as edges (bidirectional)
 */
#pragma once

#include <iostream>
#include <assert.h>
#include <vector>

#include "Course.h"

using namespace std;

class Graph{
public:
	Graph(int n = 0) {
		assert(n >= 0);
		num_courses = n;
		/*if (n == 0)
			p = NULL;
		else {
			for (int i = 0; i < n; i++) {
				p->push_back()
			}
			p = new vector<vector<float>*>[n];
			for (int i = 0; i < n; i++){
				p[i]->push_back(vector<float>[n]);
				for (int j = 0; i < n; j++)
					p[i][j] = 0;
			}
		}*/
	}

	// return TRUE if nodes have an edge, FALSE if not
	bool is_edge(Course* i, Course* j) {
		int cor = get_correlation(i, j);
		if (cor >= 0)
			return TRUE;
		else
			return FALSE;
	}

	// get the correlation of two courses,
	// correlation of i -> j
	float get_correlation(Course* i, Course* j) {
		int index_i = get_index(i);
		int index_j = get_index(j);

		return p.at(index_i).at(index_j);
	}

	// set the correlation of two courses
	// course ordering from i to j
	void set_correlation(Course* i, Course* j, float correlation) {
		/* set correlation coefficient */
		int index_i = get_index(i);
		int index_j = get_index(j);

		vector<float> tmp_vec = p[index_i];

		tmp_vec[index_j] = correlation;
	}
	
	int get_index(Course* c) {
		int i;
		for (i = 0; i < num_courses; i++)
			if (index[i] == c)
				return i;

		assert(i < num_courses);
	}

	void add_index(Course* c) { index.push_back(c); num_courses++; }

	int get_size() { return num_courses; }
	void print_graph() {
		/* to be implemented */
	}

private:
	int num_courses;
	vector<Course*> index;
	vector<vector<float>> p;
};