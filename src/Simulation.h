#pragma once
#include <string>
#include <vector>
#include <map>
#include <array>
#include "Strategy.h"

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
		~ThreePrisonerSimulation();
	protected:
		std::array<Strategy*, 3> competitors;
		unsigned int* matrix;
		std::array<unsigned int, 3> score;
		std::vector<std::array<Decision, 3>> history;
		size_t matId(const Decision[3]) const;
	};

	class DetailedSimulation : public ThreePrisonerSimulation {
	public:
		DetailedSimulation(
			const std::string& s1,
			const std::string& s2,
			const std::string& s3) : ThreePrisonerSimulation(s1, s2, s3) {}
		void run(unsigned int);
	};

}
