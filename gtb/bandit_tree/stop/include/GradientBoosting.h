#pragma once

#include "MyInclude.h"

class GradientBoosting {
	public:
		void run();
		void incPosi(int num) {
			posi_size += num;
		}
		void incBoundTime(double time) {
			bound_time += time;
		}
		void incGainCount() {
			gain_count++;
		}
		int getGainCount() {
			return gain_count;
		}
		void incBoundCount() {
			bound_count++;
		}

	private:
		vector<ID> train_targets;
		vector<ID> test_targets;
		size_t tree_count; // (gradient boosting) from 0, (random forest) from 1
		int posi_size = 0;
		int gain_count = 0;
		int bound_count = 0;
		double bound_time = 0;

		void makeTargets();
		void plantFirst();
		void calcResidualErrors();
		inline void report();
		inline void reportFeatureImportance();
};
