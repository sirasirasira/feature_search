#include "Spliter.h"
#define CLASS Spliter

extern Setting setting;
#include "Database.h"
extern Database db;

#include "Calculator.h" 
#include "StructuresGspan.h"

void CLASS::initMinScore() {
	parent_score = Calculator::imp(db.ys, targets);
	min_score = parent_score - setting.needed_impurity_decrease - std::numeric_limits<double>::epsilon();
}

void CLASS::prepare(const vector<ID>& _targets) {
	// std::cout << "debug Spliter prepare" << std::endl; // debug
	targets = _targets;
	initMinScore();
	// Debug::IDs(targets); // debug
	db.gspan.setSpliterPtr(this);
	db.gspan.minsup = setting.minsup;
	db.gspan.maxpat = setting.maxpat;
	db.gspan.run();
	std::cout << "prepare cache size: " << cache.size() << std::endl;
}

vector<ID> CLASS::run(const vector<ID>& _targets, const size_t tree_count, size_t depth) {
	// std::cout << "debug spliter run" << std::endl; // debug
	SearchStart(tree_count, depth);

	targets = _targets;
	best_pattern = {};
	initMinScore();
	if (min_score < 0) {
		goto G_INVALID;
	}
	search();
	// std::cout << "debug best_pattern " << best_pattern << std::endl; // debug
	if (best_pattern.size() == 0) {
G_INVALID:
		valid_flg = false;
		return {};
	}
	// std::cout << "debug parent_score " << parent_score << " min_score " << min_score << std::endl; // debug
	valid_flg = true;
	vector<ID> posi = db.gspan.getPosiIds(cache.at(best_pattern).g2tracers);
	return Calculator::setIntersec(targets, posi);
}

void CLASS::search() {
	// std::cout << "serch Cache" << std::endl;
	// e1patterns to pq_bound
	for (auto& pattern : e1patterns) {
		if (SearchStop())	break;

		const auto& g2tracers = cache[pattern].g2tracers;
		vector<ID> posi = db.gspan.getPosiIds(g2tracers);
		update(pattern, posi);
		double min_bound = Calculator::bound(db.ys, targets, posi);
		pq_bound.push(std::make_pair(min_bound, pattern));
	}

	// pq_bound search
	while (!pq_bound.empty()) {
		if (SearchStop())	break;

		double min_bound = pq_bound.top().first;
		if (min_score <= min_bound) {
			break;
		}

		Pattern pattern = pq_bound.top().second;
		pq_bound.pop();
		CacheRecord& record = cache[pattern];
		if (!record.scan) {
			db.gspan.run(pattern);
		}
		for (auto& c : record.childs) {
			if (SearchStop())	break;

			pattern.push_back(c);
			auto posi = db.gspan.getPosiIds(cache[pattern].g2tracers);
			update(pattern, posi);
			double bound = Calculator::bound(db.ys, targets, posi);
			pq_bound.push(std::make_pair(bound, pattern));
			pattern.pop_back();
		}
	}
}

void CLASS::update(Pattern pattern, vector<ID> posi) {
	double score = Calculator::score(db.ys, targets, posi);
	if (score < min_score ) { // old pattern may be used
		min_score = score;
		best_pattern = pattern;
		int gain_count = db.gradient_boosting.getGainCount();
		Log(gain_count, min_score, best_pattern);
	}
	search_node++;
}

