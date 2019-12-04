#pragma once

#include "MyInclude.h"

class GradientBoosting {
	public:
		void run();
		void incGainCount() {
			gain_count++;
		}
		void incBoundCount() {
			bound_count++;
		}
		void addIsMinTime(clock_t time) {
			is_min_time += time;
		}
		void addSimulationTime(clock_t time) {
			simulation_time += time;
		}

	private:
		vector<ID> train_targets;
		vector<ID> test_targets;
		size_t tree_count; // (gradient boosting) from 0, (random forest) from 1
		int gain_count = 0;
		int bound_count = 0;
		clock_t is_min_time = 0;
		clock_t simulation_time = 0;

		void makeTargets();
		void plantFirst();
		void calcResidualErrors();
		inline void report();
		inline void reportFeatureImportance();
};
