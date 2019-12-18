#pragma once

#include "IncludeLib.h"

struct Setting {
	//size_t minsup = 1; // same as min_node_size
	double minsup = 1; // same as min_node_size
	size_t maxpat = -1;
	size_t num_of_trees = 1;
	double shrinkage = 1.0;
	double needed_impurity_decrease = 0.0;
	size_t max_depth = -1;
	int search_threshold = 1000;

	void print() {
		cout
			<< " minsup (min_node_size) " << minsup
			<< " maxpat " << maxpat
			<< " num_of_trees " << num_of_trees
			<< " shrinkage " << shrinkage
			<< " needed_impurity_decrease " << needed_impurity_decrease
			<< " max_depth " << max_depth
			<< " search_threshold " << search_threshold
			<< endl;
	}

};
