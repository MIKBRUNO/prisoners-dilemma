#include <stdexcept>
#include "StrategyFactory.h"

namespace PrisonersDilemma {

	Strategy* StrategyFactory::createStrategyByString(const std::string& strat,
	const std::string& confs)
	{
		if (strat == "cooperate") {
			return new CooperateStrategy();
		}
		else if (strat == "defect") {
			return new DefectStrategy();
		}
		else if (strat == "alter") {
			return new AlternatingStrategy();
		}
		else if (strat == "majority") {
			return new GoByMajorityStrategy();
		}
		else if (strat == "voting") {
			return new VotingStrategy(confs);
		}
		else if (strat == "tit-for-tat") {
			return new TitForTatStrategy(confs);
		}
		else if (strat == "reactive") {
			return new ReactiveStrategy(confs);
		}
		else {
			throw std::invalid_argument("bad strategy name");
		}
	}

}
