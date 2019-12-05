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
	vector<ID> posi;
	double score;

	for (unsigned int i = 0; i < setting.iteration; i++) {
		path = {root};
		if (!selection(root)) { // all node is searched
			break;
		}
		if (expansion()) {
			clock_t start = clock();
			pattern = simulation(path[path.size()-1], path.size()-1);
			clock_t end = clock();
			db.gradient_boosting.addSimulationTime(end-start);
		} else {
			pattern = path[path.size()-1];
		}
		if (cache.find(pattern) == cache.end()) {
			posi = db.finder.run(pattern, targets);
		} else {
			posi = db.gspan.getPosiIds(cache[pattern].g2tracers);
		}
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
		if (cache[c].complete) {
			continue;
		}

		if (cache[c].count == 0) {
			update(c);
			best_child = c;
			break;
		} else {
			ucb = (cache[c].sum_score / cache[c].count)
				+ setting.exploration_strength
				* (sqrt(2 * log(cache[pattern].count) / cache[c].count));
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
			cache[pattern].complete = true;
			path.pop_back();
			return selection(path[path.size()-1]);
		}
	}
}

void CLASS::update(const Pattern& pattern) {
	vector<ID> posi;
	double score;
	posi = db.gspan.getPosiIds(cache[pattern].g2tracers);
	score = Calculator::score(db.ys, targets, posi);
	db.spliter.update(pattern, score);
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
			expand_selection(pattern);
			return true;
		} else {
			cache[pattern].complete = true;
			return false;
		}
	} else {
		if (cache[pattern].childs.size()) {
			cache[pattern].terminal = false;
			expand_selection(pattern);
			return true;
		} else {
			cache[pattern].complete = true;
			return false;
		}
	}
}

void CLASS::expand_selection(const Pattern& pattern) {
	Pattern selected_child;
	auto& c = cache[pattern].childs[0];
	update(c);
	path.push_back(c);
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
		// std::cout << "maxpat" << std::endl;
		return true;
	}
	//if (Dice::p(1 - pow(setting.stopping_rate, pattern.size() - base_pattern_size))) {
	if (Dice::p(1 - pow(setting.stopping_rate, pattern.size()))) { // original FUSE
		// std::cout << "probability" << std::endl;
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
