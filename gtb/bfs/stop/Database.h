#pragma once

#include "Structures.h"
#include "Setting.h"

#include "GradientBoosting.h"
#include "Planter.h"
#include "Spliter.h"
#include "Gspan.h"
#include "Finder.h"
#include "Evaluater.h"

struct Database {
	GraphData gdata;
	vector<double> raw_ys;
	vector<double> ys; // (gradient boosting) residual error, (random forest) raw ys 
	vector<double> y_predictions;

	GradientBoosting gradient_boosting;
	Planter planter;
	Spliter spliter;
	Gspan gspan = Gspan(spliter.getCache(), spliter.gete1Patterns());
	Finder finder;
	Evaluater eva;
};
