#include "UCT.h"
#define CLASS UCT

extern Setting setting;
#include "Database.h"
#include "Calculator.h" 
extern Database db;

void CLASS::run(const vector<ID>& _targets) {
	// std::cout << "uct run" << std::endl; // debug
	targets = _targets;
	before_mse = Calculator::TSS(db.ys, targets) / targets.size();
	db.gspan.clearUCB();
	Pattern pattern;
	GraphToTracers g2tracers;
	vector<ID> posi;
	double score;
	bool sim_flg;
	iter = 0;

	while (1) {
		path = {root};
		if (!selection(root)) { // all node is searched
			break;
		}
		sim_flg = false;
		iter++;

		if (expansion()){
			if(path.size()-1 < setting.maxpat) {
				sim_flg = true;
			}
		}

		if (sim_flg) {
			auto res = simulation(path[path.size()-1], path.size()-1);
			pattern = res.pattern;
			g2tracers = res.g2tracers;
		} else {
			pattern = path[path.size()-1];
			g2tracers = cache[pattern].g2tracers;
		}

		posi = db.gspan.getPosiIds(g2tracers);
		score = Calculator::score(db.ys, targets, posi) / before_mse; // range [0, 1]
		backpropagation(score);
	}
}

bool CLASS::selection(const Pattern& pattern) {
	// std::cout << "selection: " << pattern << std::endl; // debug
	auto& precord = cache[pattern];
	if (precord.terminal) return true;

	Pattern best_child;
	double max_ucb = -DBL_MAX;
	double ucb = 0;
	for (auto& c : precord.childs) {
		auto& crecord = cache[c];
		if (crecord.prune) {
			continue;
		}

		if (crecord.count == 0) {
			if (update(c)) { // prune
				continue;
			} else { // not prune
				best_child = c;
				break;
			}
		} else {
			ucb = (crecord.sum_score / crecord.count)
				+ setting.exploration_strength * sqrt(log(precord.count) / (2 * crecord.count));
			if (ucb > max_ucb) {
				best_child = c;
				max_ucb = ucb;
			}
		}
	}

	if (best_child.size() != 0) {
		path.push_back(best_child);
		return selection(best_child);
	} else {
		if (path.size() == 1) { // all node is pruned
			return false;
		} else {
			precord.prune = true;
			path.pop_back();
			return selection(path[path.size()-1]);
		}
	}
}

bool CLASS::update(const Pattern& pattern) {
	// std::cout << "update: " << pattern << endl; // debug
	auto& precord = cache[pattern];
	vector<ID> posi = db.gspan.getPosiIds(precord.g2tracers);
	double score = Calculator::score(db.ys, targets, posi);
	db.spliter.update(pattern, score);
	double bound = Calculator::bound(db.ys, targets, posi);
	if (db.spliter.isBounded(bound) or pattern.size() >= setting.maxpat){
		precord.prune = true;
		return true;
	}
	return false;
}

bool CLASS::expansion() {
	const Pattern pattern = path[path.size()-1];
	// std::cout << "expansion: " << pattern << endl; // debug
	auto& precord = cache[pattern];
	if (pattern.size() >= setting.maxpat) {
		precord.prune = true;
		return false;
	}
	if (precord.count < setting.threshold) {
		return true;
	}

	if (!precord.scan) {
		if (db.gspan.scanGspan(pattern)) {
			precord.terminal = false;
			return expand_selection(pattern);
		} else {
			precord.prune = true;
			return false;
		}
	} else {
		if (precord.childs.size()) {
			precord.terminal = false;
			return expand_selection(pattern);
		} else {
			precord.prune = true;
			return false;
		}
	}
}

bool CLASS::expand_selection(const Pattern& pattern) {
	auto& precord = cache[pattern];
	Pattern selected_child;
	for (auto& c : precord.childs) {
		if (update(c)) { // prune
			continue;
		} else { // not prune
			selected_child = c;
			break;
		}
	}

	if (selected_child.size() != 0) {
		path.push_back(selected_child);
		return true;
	} else {
		precord.prune = true;
		return false;
	}
}

PandT CLASS::simulation(const Pattern& pattern, const size_t base_pattern_size) {
	// cout << "simulation: " << pattern << endl;
	return db.gspan.EdgeSimulation(pattern, base_pattern_size);
}

void CLASS::backpropagation(double score) {
	// cout << "backpropagation: " << score << endl;
	for (int i = path.size() - 1; i > 0; i--) {
		cache[path[i]].count++;
		cache[path[i]].sum_score -= score; // score is mse (lower is better)
	}
	cache[root].count++;
}
