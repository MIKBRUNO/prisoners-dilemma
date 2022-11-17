#include <stdexcept>
#include <iostream>
#include <fstream>
#include <cstring>
#include "Simulation.h"
#include "StrategyFactory.h"

using namespace std;

namespace PrisonersDilemma {

	ThreePrisonerSimulation::ThreePrisonerSimulation(
		const string& s1,
		const string& s2,
		const string& s3)
		: ThreePrisonerSimulation(s1, s2, s3, gameutils::GameMatrix())
	{  }
	ThreePrisonerSimulation::ThreePrisonerSimulation(
		const std::string& s1,
		const std::string& s2,
		const std::string& s3,
		const gameutils::GameMatrix& matrix)
	{
		score = { 0, 0, 0 };
		competitors[0] = StrategyFactory::createStrategyByString(s1);
		competitors[1] = StrategyFactory::createStrategyByString(s2);
		competitors[2] = StrategyFactory::createStrategyByString(s3);
		history = {  };
		mat = matrix;
	}
	ThreePrisonerSimulation::~ThreePrisonerSimulation() {
		for (Strategy* s : competitors)
			delete s;
	}

	void DetailedSimulation::run(unsigned int steps) {
		for (unsigned int i = 0; i < steps; ++i) {
			history.push_back({});
			for (unsigned int j = 0; j < 3; ++j) {
				history[i][j] = competitors[j]->decide(history, competitors);
				std::cout << history[i][j] << ' ';
			}
			std::cout << std::endl;

			score[0] += mat.at(history[i].data(), 0);
			score[1] += mat.at(history[i].data(), 1);
			score[2] += mat.at(history[i].data(), 2);
			std::cout << score[0] << ' '
			<< score[1] << ' '
			<< score[2] << ' '
			<< std::endl;
			cin.get();
		}
	}

	void FastSimulation::run(unsigned int steps) {
		for (unsigned int i = 0; i < steps; ++i) {
			history.push_back({});
			for (unsigned int j = 0; j < 3; ++j)
				history[i][j] = competitors[j]->decide(history, competitors);

			score[0] += mat.at(history[i].data(), 0);
			score[1] += mat.at(history[i].data(), 1);
			score[2] += mat.at(history[i].data(), 2);
		}
		std::cout << score[0] << ' ';
		std::cout << score[1] << ' ';
		std::cout << score[2] << ' ';
		std::cout << std::endl;
	}

}