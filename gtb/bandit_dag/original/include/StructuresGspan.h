#pragma once

#include "IncludeLib.h"
#include "Structures.h"


/*
struct EdgeTracer {
	VertexPair vpair;
	EdgeTracer* predec;
	explicit EdgeTracer() {};
	void set(ID, ID, ID, EdgeTracer*);
};

inline void EdgeTracer::set(ID a, ID b, ID id, EdgeTracer* pr) {
	vpair.a = a;
	vpair.b = b;
	vpair.id = id;
	predec = pr;
}
*/

using EdgeTracer = vector<VertexPair>;
using Tracers = vector<EdgeTracer>;
using GraphToTracers = map<ID, Tracers>;
using PairSorter = map<Pair, GraphToTracers>;

struct DFSCode {
	Triplet labels;
	Pair time;
};

inline bool operator == (const DFSCode& l, const DFSCode& r) {
	if (l.time.a != r.time.a) return false;
	if (l.time.b != r.time.b) return false;
	if (l.labels.x != r.labels.x) return false;
	if (l.labels.y != r.labels.y) return false;
	return (l.labels.z == r.labels.z);
}

inline bool operator != (const DFSCode& l, const DFSCode& r) {
	return !(l == r);
}

inline bool operator < (const DFSCode& l, const DFSCode& r) { // original gspan order
	if(l.time.a != r.time.a) return l.time.a > r.time.a;
	if(l.time.b != r.time.b) return l.time.b < r.time.b;
	if(l.labels.x != r.labels.x) return l.labels.x < r.labels.x;
	if(l.labels.y != r.labels.y) return l.labels.y < r.labels.y;
	return (l.labels.z < r.labels.z);
}

inline std::ostream& operator << (std::ostream& os, const DFSCode dcode) {
	os << "(" << dcode.time.a << " " << dcode.time.b << " " << dcode.labels.x << " "  << dcode.labels.y << " "  << dcode.labels.z << ")";
	return os;
}

using Pattern = vector<DFSCode>;

inline bool operator < (const Pattern& l, const Pattern& r) {
	for (size_t i = 0; i < l.size() and i < r.size(); i++) {
		if (l[i] == r[i]) {
			continue;
		}
		if (l[i] < r[i]) return true;
		if (r[i] < l[i]) return false;
	}
	if (l.size() < r.size()) return true;
	if (r.size() < l.size()) return false;
	return false;
}

inline bool operator != (const Pattern& l, const Pattern& r) {
	return !(l == r);
}

inline bool operator == (const Pattern& l, const Pattern& r) {
	if (l.size() != r.size()) return false;
	for (size_t i = 0; i < l.size(); i++) {
		if (l[i] == r[i]) {
			continue;
		} else {
			return false;
		}
	}
	return true;
}

inline std::ostream& operator << (std::ostream& os, const Pattern pattern) {
	if (pattern.empty()) return os;
	os << "(" << pattern[0].labels.x << ") " << pattern[0].labels.y << " (0f" << pattern[0].labels.z << ")";
	for (size_t i = 1; i < pattern.size(); i++) {
		if (pattern[i].time.a < pattern[i].time.b) {
			os << " " << pattern[i].labels.y << " (" << pattern[i].time.a << "f" << pattern[i].labels.z << ")";
		} else {
			//os << " " << pattern[i].labels.y << " (b" << pattern[i].time.b << ")";
			os << " " << pattern[i].labels.y << " (" << pattern[i].time.a << "b" << pattern[i].time.b << ")";
		}
	}
	return os;
}

/*
inline Graph toGraph(const Pattern& codes) {
	Graph g;
	ID eid = 0;
	for (auto p : codes) {
		g.resize(std::max(p.time.a, p.time.b) + 1);
		if (p.labels.x != -1) g.label[p.time.a] = p.labels.x;
		if (p.labels.z != -1) g.label[p.time.b] = p.labels.z;
		Triplet labels(g.label[p.time.a], p.labels.y, g.label[p.time.b]);
		g[p.time.a].push_back(Edge(eid++, p.time.b, labels));
		g[p.time.b].push_back(Edge(eid++, p.time.a, labels.reverse()));
	}
	g.num_of_edges = eid;
	return g;
}
*/

inline Graph toGraph(const EdgeTracer& tracer, const Graph& original_g) {
	Graph g;
	g.resize(original_g.size());
	g.label = original_g.label;
	for (auto vpair : tracer) {
		Triplet labels(g.label[vpair.a], vpair.label, g.label[vpair.b]);
		if (vpair.id % 2 == 0) {
			g[vpair.a].push_back(Edge(vpair.id, vpair.b, labels));
			g[vpair.b].push_back(Edge(vpair.id+1, vpair.a, labels.reverse()));
		} else {
			g[vpair.a].push_back(Edge(vpair.id, vpair.b, labels));
			g[vpair.b].push_back(Edge(vpair.id-1, vpair.a, labels.reverse()));
		}
	}
	g.num_of_edges = original_g.num_of_edges;
	return g;
}

inline void scan_rm(const Pattern& pat, vector<size_t>& idx) {
	ID prev = -1;
	for (int i = pat.size() - 1; i >= 0; i--) {
		if (pat[i].time.a < pat[i].time.b) { // forward edge
			if (prev == pat[i].time.b or prev == (ID) -1) {
				idx.push_back(i);
				prev = pat[i].time.a;
			}
		}
	}
}
