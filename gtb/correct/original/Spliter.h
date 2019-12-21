#pragma once

#include "MyInclude.h"
#include "StructuresGspan.h"

struct CacheRecord {
	GraphToTracers g2tracers;
	vector<DFSCode> childs;
	double feature_importance;
	bool scan;
	CacheRecord() {
		feature_importance = 0;
		scan = false;
	}
	CacheRecord(GraphToTracers g2tracers, vector<DFSCode> childs)
		: g2tracers(g2tracers), childs(childs){
			feature_importance = 0;
			scan = false;
		}
};

class Spliter {
	public:
		void prepare(const vector<ID>& _targets);
		vector<ID> run(const vector<ID>& _targets, const size_t tree_count, size_t depth);
		void update(Pattern pattern, vector<ID> posi);
		bool isBounded(vector<ID> posi);
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
		inline vector<ID> gettargets() {
			return  targets;
		}
		inline vector<Pattern>& gete1Patterns() {
			return e1patterns;
		}

		inline map<Pattern, CacheRecord>& getCache() {
			return cache;
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
		map<Pattern, CacheRecord> cache;
		vector<Pattern> e1patterns;
		size_t tree_count;
		size_t depth;
		size_t search_idx = 0;
		int search_node;

		void initMinScore();
		void search();
		void search_childs(const Pattern&);
};

