#pragma once
#include <iostream>
#include <vector>
#include <array>

namespace PrisonersDilemma {

	enum class Decision {
		COOPERATE,
		DEFECT
	};
	std::ostream& operator<<(std::ostream& o, Decision d);

	class Strategy {
	public:
		virtual Decision decide(std::vector<std::array<Decision, 3>>&, std::array<Strategy*, 3>&) = 0;
	};

	class CooperateStrategy : public Strategy {
	public:
		Decision decide(std::vector<std::array<Decision, 3>>&, std::array<Strategy*, 3>&);
	};

	class DingDongStrategy : public Strategy {
	public:
		Decision decide(std::vector<std::array<Decision, 3>>&, std::array<Strategy*, 3>&);
	private:
		Decision d = Decision::COOPERATE;
	};

	class GoByMajorityStrategy : public Strategy {
	public:
		Decision decide(std::vector<std::array<Decision, 3>>&, std::array<Strategy*, 3>&);
	};

}