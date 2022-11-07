#pragma once
#include <iostream>

namespace PrisonersDilemma {

	enum class Decision {
		COOPERATE,
		DEFECT
	};
	std::ostream& operator<<(std::ostream& o, Decision d);

	class Strategy {
	public:
		virtual Decision decide() = 0;
	};

	class CooperateStartegy : public Strategy {
	public:
		Decision decide();
	};

}