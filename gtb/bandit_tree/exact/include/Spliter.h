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
		void TimeStart(const size_t _tree_count, size_t _depth) {
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
			search_start = clock();
		}
		void Log(int gain_count, double min_score, Pattern pattern) {
			clock_t time = clock() - search_start;
			std::ostringstream oss;
			oss << "./search/tree" << tree_count << "depth" << depth << "_" << search_idx << ".dat";
			string filename = oss.str();
			std::ofstream file;
			file.open(filename, std::ios::app);
			file << double(time) / CLOCKS_PER_SEC << "," << gain_count << "," << min_score / targets.size() << "," << pattern << std::endl;
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
		clock_t search_start;

		void initMinScore();
};

