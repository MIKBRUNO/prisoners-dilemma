#pragma once
#include <string>
#include <vector>
#include <map>
#include <array>
#include "Strategy.h"
#include "SimMatrix.h"

namespace PrisonersDilemma {

	class Prisoner {
	public:
		inline const std::string& name() const { return *nm; }
		inline const Strategy& getStrategy() const { return *strat; }
		inline Decision decide(
			const std::vector<Decision>& myhist,
			const std::vector<Decision>& hist1,
			const std::vector<Decision>& hist2)
		{ return strat->decide(myhist, hist1, hist2); }
		Prisoner(const std::string& name, const  std::string& strategy, const std::string& cfgdr = "");
		~Prisoner() noexcept;
		Prisoner (const Prisoner&);
        Prisoner (Prisoner&&) noexcept;
        Prisoner& operator= (const Prisoner&);
        Prisoner& operator= (Prisoner&&);
	private:
		Strategy* strat;
		std::string* nm;
	};

	class ThreePrisonerSimulation {
	public:
		inline ThreePrisonerSimulation(
			const std::vector<Prisoner> pris,
			const simutils::SimMatrix& matrix = simutils::SimMatrix()
		) : score({ 0, 0, 0 }), prisoners(pris), mat(matrix) {  }
		
		inline unsigned int getScore(size_t idx) const { return score[idx]; }
		inline Decision getLastResult(size_t idx) const { return history[idx].back(); }
		inline const std::vector<Prisoner>& getCompetitors() const { return prisoners; }
		void step();
		void run(unsigned int stepCount, bool fast);
	protected:
		std::vector<Prisoner> prisoners;
		simutils::SimMatrix mat;
		std::array<unsigned int, 3> score;
		std::array<std::vector<Decision>, 3> history;
	};

	class Tournament {
	public:
		inline Tournament(
			const std::vector<Prisoner>& pris,
			const simutils::SimMatrix& matrix = simutils::SimMatrix()
		) : prisoners(pris), mat(matrix) {
			for (auto p : prisoners)
				score.push_back(0);
		}
		void run(unsigned int stepCount);
		inline unsigned int getScore(size_t idx) const { return score[idx]; }
	private:
		std::vector<Prisoner> prisoners;
		simutils::SimMatrix mat;
		std::vector<unsigned int> score;
	};

}
