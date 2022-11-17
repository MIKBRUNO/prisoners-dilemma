#include <stdexcept>
#include "StrategyFactory.h"

namespace PrisonersDilemma {

	Strategy* StrategyFactory::createStrategyByString(const std::string& strat) {
		if (strat == "cooperate") {
			return new CooperateStrategy();
		}
		else if (strat == "dingdong") {
			return new DingDongStrategy();
		}
		else if (strat == "majority") {
			return new GoByMajorityStrategy();
		}
		else {
			throw std::invalid_argument("bad strategy name");
		}
	}

}
