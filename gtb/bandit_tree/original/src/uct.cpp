#include "UCT.h"
#define CLASS UCT

extern Setting setting;
#include "Database.h"
#include "Calculator.h" 
extern Database db;

void CLASS::run(const vector<ID>& _targets) {
	// std::cout << "uct run" << std::endl; // debug
	targets = _targets;
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

		if (path.size()-1 < setting.maxpat) {
			if (expansion()){
				if(path.size()-1 < setting.maxpat) {
					//sim_flg = true;
				}
			}
		}
		if (sim_flg) {
			pattern = simulation(path[path.size()-1], path.size()-1);
		} else {
			pattern = path[path.size()-1];
		}

		posi = db.gspan.getPosiIds(cache[pattern].g2tracers);
		score = Calculator::score(db.ys, targets, posi);
		backpropagation(score);
	}
}

bool CLASS::selection(const Pattern& pattern) {
	// std::cout << "selection: " << pattern << std::endl; // debug
	if (cache[pattern].terminal) return true;

	Pattern best_child;
	double max_ucb = -DBL_MAX;
	double ucb = 0;
	for (auto& c : cache[pattern].childs) {
		if (cache[c].prune) {
			continue;
		}

		if (cache[c].count == 0) {
			if (update(c)) { // prune
				continue;
			} else { // not prune
				best_child = c;
				break;
			}
		} else {
			ucb = (1-setting.bound_rate) * (cache[c].sum_score / cache[c].count)
				+ setting.bound_rate * (-cache[c].bound)
				+ setting.exploration_strength * (sqrt(log(cache[pattern].count) / 2 * cache[c].count));
		}

		if (ucb > max_ucb) {
			best_child = c;
			max_ucb = ucb;
		}
	}

	if (best_child.size() != 0) {
		path.push_back(best_child);
		return selection(best_child);
	} else {
		if (path.size() == 1) { // all node is pruned
			return false;
		} else {
			cache[pattern].prune = true;
			path.pop_back();
			return selection(path[path.size()-1]);
		}
	}
}

bool CLASS::update(const Pattern& pattern) {
	// std::cout << "update: " << pattern << endl; // debug
	vector<ID> posi = db.gspan.getPosiIds(cache[pattern].g2tracers);
	double score = Calculator::score(db.ys, targets, posi);
	db.spliter.update(pattern, score);
	double bound = Calculator::bound(db.ys, targets, posi);
	cache[pattern].bound = bound;
	if (db.spliter.isBounded(bound) or pattern.size() >= setting.maxpat){
		cache[pattern].prune = true;
		return true;
	}
	return false;
}

bool CLASS::expansion() {
	const Pattern pattern = path[path.size()-1];
	// std::cout << "expansion: " << pattern << endl; // debug
	if (cache[pattern].count < setting.threshold) {
		return true;
	}

	if (!cache[pattern].scan) {
		if (db.gspan.scanGspan(pattern)) {
			cache[pattern].terminal = false;
			return expand_selection(pattern);
		} else {
			cache[pattern].prune = true;
			return false;
		}
	} else {
		if (cache[pattern].childs.size()) {
			cache[pattern].terminal = false;
			return expand_selection(pattern);
		} else {
			cache[pattern].prune = true;
			return false;
		}
	}
}

bool CLASS::expand_selection(const Pattern& pattern) {
	Pattern selected_child;
	for (auto& c : cache[pattern].childs) {
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
		cache[pattern].prune = true;
		return false;
	}
}

Pattern CLASS::simulation(const Pattern& pattern, const size_t base_pattern_size) {
	// cout << "simulation: " << pattern << endl;
	if (!cache[pattern].scan) {
		if (!db.gspan.scanGspan(pattern)) {
			return pattern;
		}
	}

	if (cache[pattern].childs.size() == 0) {
		return pattern;
	}

	auto random_child = cache[pattern].childs[Dice::id(cache[pattern].childs.size())];
	if (stop_condition(random_child, base_pattern_size)) {
		return random_child;
	} else {
		return simulation(random_child, base_pattern_size);
	}
}

bool CLASS::stop_condition(const Pattern pattern, const size_t base_pattern_size) {
	// std::cout << "stop_condition: " << pattern << std::endl; // debug
	if (pattern.size() >= setting.maxpat) {
		return true;
	}
	//if (Dice::p(1 - pow(setting.stopping_rate, pattern.size() - base_pattern_size))) {
	if (Dice::p(1 - pow(setting.stopping_rate, pattern.size()))) { // original FUSE
		return true;
	}
	return false;
}

void CLASS::backpropagation(double score) {
	// cout << "backpropagation: " << score << endl;
	for (int i = path.size() - 1; i > 0; i--) {
		cache[path[i]].count++;
		cache[path[i]].sum_score -= score; // score is mse (lower is better)
	}
	cache[root].count++;
}
