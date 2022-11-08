#include <stdexcept>
#include "Simulation.h"
#include "StrategyFactory.h"
#include <iostream>
#include <cstring>

using namespace std;

namespace {

	const unsigned int* DEFAULT_MATRIX = new unsigned int[24]
	{
		7, 7, 7,
		3, 3, 9,
		3, 9, 3,
		9, 3, 3,
		0, 5, 5,
		5, 0, 5,
		5, 5, 0,
		1, 1, 1
	};

}

namespace PrisonersDilemma {

	ThreePrisonerSimulation::ThreePrisonerSimulation(
		const string& s1,
		const string& s2,
		const string& s3)
	{
		score = { 0, 0, 0 };
		competitors[0] = StrategyFactory::createStrategyByString(s1);
		competitors[1] = StrategyFactory::createStrategyByString(s2);
		competitors[2] = StrategyFactory::createStrategyByString(s3);
		history = {  };
		matrix = new unsigned int[24];
		memcpy(matrix, DEFAULT_MATRIX, 24*sizeof(unsigned int));
	}
	ThreePrisonerSimulation::~ThreePrisonerSimulation() {
		for (Strategy* s : competitors)
			delete s;
		delete[] matrix;
	}
	size_t ThreePrisonerSimulation::matId(const Decision decs[3]) const {
		size_t id = 0;
		for (size_t i = 0; i < 3; ++i) {
			id += (decs[i] == Decision::COOPERATE ? 0u : 1u) << i;
		}
		return id;
	}

	void DetailedSimulation::run(unsigned int steps) {
		for (unsigned int i = 0; i < steps; ++i) {
			history.push_back({});
			for (unsigned int j = 0; j < 3; ++j) {
				history[i][j] = competitors[j]->decide();
				std::cout << history[i][j] << ' ';
			}
			std::cout << std::endl;
			
			size_t mid = matId(history[i].data());

			score[0] += matrix[mid*3 + 0];
			std::cout << score[0] << ' ';
			score[1] += matrix[mid*3 + 1];
			std::cout << score[1] << ' ';
			score[2] += matrix[mid * 3 + 2];
			std::cout << score[2] << ' ';
			std::cout << std::endl;

			cin.get();
		}
	}

}