#pragma once
#include <string>
#include <vector>
#include <map>
#include <array>
#include "Strategy.h"
#include "GameMatrix.h"

namespace PrisonersDilemma {

	class Simulation {
	public:
		virtual void run(unsigned int stepCount) = 0;
	};

	class ThreePrisonerSimulation : public Simulation {
	public:
		ThreePrisonerSimulation(
			const std::string& s1,
			const std::string& s2,
			const std::string& s3);
		ThreePrisonerSimulation(
			const std::string& s1,
			const std::string& s2,
			const std::string& s3,
			const gameutils::GameMatrix& mat);
		~ThreePrisonerSimulation();
	protected:
		std::array<Strategy*, 3> competitors;
		gameutils::GameMatrix mat;
		std::array<unsigned int, 3> score;
		std::vector<std::array<Decision, 3>> history;
	};


	class DetailedSimulation : public ThreePrisonerSimulation {
	public:
		using ThreePrisonerSimulation::ThreePrisonerSimulation;
		
		void run(unsigned int);
	};


	class FastSimulation : public ThreePrisonerSimulation {
	public:
		using ThreePrisonerSimulation::ThreePrisonerSimulation;

		void run(unsigned int);
	};

}
