/* Graph.h
 * Graph with courses as vertices,
 * correlation coefficients as edges (bidirectional)
 */
#pragma once

#include <iostream>
#include <assert.h>
#include <vector>
#include <limits>
#include <fstream>

#include "Course.h"

// negative infinity (type float)
const float neg_inf = -numeric_limits<float>::infinity();

using namespace std;

class Graph{
public:
	Graph(int n = 0) {
		assert(n >= 0);
		num_courses = n;
		
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
	// !! different from modifying correlation
	void set_correlation(Course* i, Course* j, float correlation) {
		/* set correlation coefficient */
		int index_i = get_index(i);
		int index_j = get_index(j);
		
		// if index out of range, push_back
		vector<float> to_push(index_j + 1, neg_inf);

		// i(column to modify) greater than the size of matrix
		if (index_i >= p.size() || index_i == 0)
			p.push_back(to_push);

		// j(row to modify) greater than the size of vector
		if (index_j >= p.at(index_i).size())
			p[index_i].push_back(correlation);

		modify_correlation(i, j, correlation);
	}

	void modify_correlation(Course* i, Course* j, float correlation) {
		int index_i = get_index(i);
		int index_j = get_index(j);
		//vector<float> tmp_vec = p[index_i];

		// sanity check
		assert(index_i < p.size() || \
			index_j < p.at(index_i).size());

		p.at(index_i).at(index_j) = correlation;
		//cout << "in modify func! with corr, " << correlation << \
			", p_val: " << p.at(index_i).at(index_j) << endl;
	}
	
	int get_index(Course* c) {
		int i;
		for (i = 0; i < num_courses; i++)
			if (index[i]->get_num()== c->get_num() && \
				index[i]->get_track() == c->get_track())
				return i;

		assert(i < num_courses);
	}

	void add_index(Course* c) {
		for (int i = 0; i < index.size(); i++)
			if (index[i]->get_num() == c->get_num() && \
				index[i]->get_track() == c->get_track())
				return;
		index.push_back(c);
		num_courses++;
		//cout << index.size() << endl;
	}

	int get_size() { return num_courses; }
	void print_graph() {
		//printf("size_i: %d\nsize_j: %d\n", p.size(), p.at(0).size());
		for (int i = 0; i < p.size(); i++) {
			for (int j = 0; j < p.at(i).size(); j++)
				printf("%.3f\t", p.at(i).at(j));
			cout << endl;
		}
		cout << endl;
		int x;
		//cin >> x;
	}
	void file_print_graph(const char* path) {
		// creating output.txt
		ofstream output;
		string s = path;
		output.open(s + "graph_output.txt");

		for (int i = 0; i < p.size(); i++) {
			for (int j = 0; j < p.at(i).size(); j++)
				output << p.at(i).at(j) << "\t";
			output << endl;
		}
		output << endl;
	}

private:
	int num_courses;
	vector<Course*> index;
	vector<vector<float>> p;
};