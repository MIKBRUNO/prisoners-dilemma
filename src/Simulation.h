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
		ThreePrisonerSimulation(
			const std::string& s1,
			const std::string& s2,
			const std::string& s3,
			const std::array<unsigned int, 24>& mat);
		~ThreePrisonerSimulation();
	protected:
		std::array<Strategy*, 3> competitors;
		unsigned int* matrix;
		std::array<unsigned int, 3> score;
		std::vector<std::array<Decision, 3>> history;
		size_t matId(const Decision[3]) const;
	};
	void readMatrixFromFile(std::array<unsigned int, 24>* mat, const std::string& file);

	class DetailedSimulation : public ThreePrisonerSimulation {
	public:
		using ThreePrisonerSimulation::ThreePrisonerSimulation;
		
		void run(unsigned int);
	};

}
