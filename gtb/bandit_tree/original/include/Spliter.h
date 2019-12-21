#pragma once

#include "MyInclude.h"
#include "StructuresGspan.h"

class Spliter {
	public:
		void prepare(const vector<ID>& _targets);
		vector<ID> run(const vector<ID>& _targets, const size_t tree_count, size_t depth);
		void update(const Pattern& pattern, double score);
		bool isBounded(double min_bound);
		inline bool valid() {
			return valid_flg;
		}
		inline const Pattern& getBestPattern() {
			assert(valid_flg);
			return best_pattern;
		}
		inline double getImportance() {
			assert(valid_flg);
			return parent_score - min_score;
		}
		void SearchStart(const size_t _tree_count, size_t _depth) {
			search_node = 0;
			search_idx++;
			if (tree_count != _tree_count) {
				tree_count = _tree_count;
				search_idx = 0;
			}
			if (depth != _depth) {
				depth = _depth;
				search_idx = 0;
			}
			std::ostringstream oss;
			oss << "./search/tree" << tree_count << "depth" << depth << "_" << search_idx << ".dat";
			string filename = oss.str();
			std::ofstream file;
			file.open(filename, std::ios::out);
		}
		void Log(double min_score, Pattern pattern) {
			std::ostringstream oss;
			oss << "./search/tree" << tree_count << "depth" << depth << "_" << search_idx << ".dat";
			string filename = oss.str();
			std::ofstream file;
			file.open(filename, std::ios::app);
			file << search_node << "," << min_score << "," << pattern << std::endl;
		}

	private:
		bool valid_flg;
		vector<ID> targets;
		double parent_score;
		double min_score;
		Pattern best_pattern;
		size_t tree_count;
		size_t depth;
		size_t search_idx = 0;
		int search_node;

		void initMinScore();
};

