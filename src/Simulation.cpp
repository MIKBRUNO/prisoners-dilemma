#include <stdexcept>
#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>
#include "Simulation.h"
#include "StrategyFactory.h"

using namespace std;

namespace PrisonersDilemma {

	Prisoner::Prisoner(const string& name, const string& strategy, const string& cfg) {
		nm = new string(name);
		strat = StrategyFactory::createStrategyByString(strategy, cfg);
	}
	Prisoner::~Prisoner() noexcept {
		delete nm;
		delete strat;
	}
	Prisoner::Prisoner (const Prisoner& o) {
		nm = new string { *o.nm };
		strat = o.strat->clone();
	}
    Prisoner::Prisoner (Prisoner&& o) noexcept {
		nm = o.nm;
		o.nm = nullptr;
		strat = o.strat;
		o.strat = nullptr;
	}
    Prisoner& Prisoner::operator= (const Prisoner& o) {
		if (&o == this)
			return *this;
		nm = new string { *o.nm };
		strat = o.strat->clone();
		return *this;
	}
    Prisoner& Prisoner::operator= (Prisoner&& o) {
		if (&o == this)
			return *this;
		nm = o.nm;
		o.nm = nullptr;
		strat = o.strat;
		o.strat = nullptr;
		return *this;
	}

	void ThreePrisonerSimulation::step() {
		array<Decision, 3> decisions{};
		decisions[0] = prisoners[0].decide(history[0], history[1], history[2]);
		decisions[1] = prisoners[1].decide(history[1], history[0], history[2]);
		decisions[2] = prisoners[2].decide(history[2], history[1], history[0]);
		for (unsigned int j = 0; j < 3; ++j) {
			history[j].push_back(decisions[j]);
			score[j] += mat.at(decisions.data(), j);
		}
	}
	void ThreePrisonerSimulation::run(unsigned int stepCount, bool fast) {
		cout << "Competitors: ";
		for (size_t j = 0; j < 3; ++j)
			cout<< prisoners[j].name() << "("
				<< prisoners[j].getStrategy().name() << ") ";
		cout << endl;
		if (fast) {
			for (size_t i = 0; i < stepCount; ++i)
				step();
			cout << "Scores:      ";
			for (size_t j = 0; j < 3; ++j)
				cout << score[j] << '\t';
		}
		else
			do {
				step();
				cout << "Decisions:   ";
				for (size_t j = 0; j < 3; ++j)
					cout << history[j].back() << '\t';
				cout << endl;
				cout << "Scores:      ";
				for (size_t j = 0; j < 3; ++j)
					cout << score[j] << '\t';
				cout << endl;
			} while ('q' != cin.get());
		cout << endl;
	}

	void Tournament::run(unsigned int stepCount) {
		unsigned int roundCounter = 0;
		for (unsigned int i = 0; i < prisoners.size() - 2; ++i)
		for (unsigned int j = i+1; j < prisoners.size() - 1; ++j)
		for (unsigned int k = j+1; k < prisoners.size();     ++k) {
			vector<Prisoner> pris { prisoners[i], prisoners[j], prisoners[k] };
			ThreePrisonerSimulation sim(pris, mat);
			cout << "Round: " << ++roundCounter << endl;
			sim.run(stepCount, true);
			score[i] += sim.getScore(0);
			score[j] += sim.getScore(1);
			score[k] += sim.getScore(2);
			cout << "Full Score:  ";
			cout << score[i] << '\t';
			cout << score[j] << '\t';
			cout << score[k] << '\t';
			cout << endl;
			cout << endl;
		}

		auto it = max_element(score.begin(), score.end());
		size_t i = distance(score.begin(), it);
		cout << "Winner:      " << prisoners[i].name() << '('
			 << prisoners[i].getStrategy().name() << ')' << endl;
		cout << "Winner's score: " << *it << endl;
	}

}