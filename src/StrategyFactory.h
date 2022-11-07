#pragma once
#include <string>
#include "Strategy.h"

namespace PrisonersDilemma {

	class StrategyFactory {
	public:
		static Strategy* createStrategyByString(const std::string&);
	private:
		StrategyFactory() {};
	};

}