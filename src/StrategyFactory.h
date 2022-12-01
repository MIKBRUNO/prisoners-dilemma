#pragma once
#include <string>
#include "Strategy.h"

namespace PrisonersDilemma {

	class StrategyFactory {
	public:
		static Strategy* createStrategyByString(const std::string&, const std::string& confs = "");
	private:
		StrategyFactory() {};
	};

}