#include <filesystem>
#include <fstream>
#include "Strategy.h"
#include "StrategyFactory.h"

using namespace std;

namespace PrisonersDilemma {

    ostream& operator<<(ostream& o, Decision d) {
        switch (d) {
        case Decision::COOPERATE:
            o << "C";
            break;
        case Decision::DEFECT:
            o << "D";
            break;
        default:
            break;
        }
        return o;
    }

	Decision CooperateStrategy::decide(
			const std::vector<Decision>& myhist,
			const std::vector<Decision>& hist1,
			const std::vector<Decision>& hist2) {
		return Decision::COOPERATE;
	}

    Decision AlternatingStrategy::decide(
			const std::vector<Decision>& myhist,
			const std::vector<Decision>& hist1,
			const std::vector<Decision>& hist2) {
        d = (d == Decision::COOPERATE) ? Decision::DEFECT : Decision::COOPERATE;
        return d;
	}

    Decision GoByMajorityStrategy::decide(
			const std::vector<Decision>& myhist,
			const std::vector<Decision>& hist1,
			const std::vector<Decision>& hist2)
    {
        if (myhist.empty())
            return Decision::COOPERATE;
        unsigned int Cooperations = 0;
        unsigned int Defections = 0;
        for (Decision d : myhist) {
            if (d == Decision::COOPERATE)
                ++Cooperations;
            else
                ++Defections;
        }
        for (Decision d : hist1) {
            if (d == Decision::COOPERATE)
                ++Cooperations;
            else
                ++Defections;
        }
        for (Decision d : hist2) {
            if (d == Decision::COOPERATE)
                ++Cooperations;
            else
                ++Defections;
        }
        if (Defections > Cooperations)
            return Decision::DEFECT;
        else
            return Decision::COOPERATE;
    }

    VotingStrategy::VotingStrategy(const string& confdir) {
        filesystem::path pth = confdir;
        pth /= "voting.cfg";
        ifstream f;
        f.exceptions( ifstream::failbit | ifstream::badbit );
		f.open(pth.string());
        while (!f.eof()) {
            std::string adviser;
            f >> adviser;
            if ("voting" == adviser)
                throw invalid_argument("voting strategy cannot include itself.");
            advisers.push_back(StrategyFactory::createStrategyByString(adviser, confdir));
        }
        f.close();
    }

    Decision VotingStrategy::decide(
			const std::vector<Decision>& myhist,
			const std::vector<Decision>& hist1,
			const std::vector<Decision>& hist2)
    {
        unsigned int coopCount = 0;
        for (Strategy* s : advisers) {
            coopCount += (s->decide(myhist, hist1, hist2) == Decision::COOPERATE) ? 1 : 0;
        }
        return coopCount >= advisers.size() ? Decision::COOPERATE : Decision::DEFECT;
    }

    VotingStrategy::VotingStrategy(const VotingStrategy& o) {
        for (auto s : o.advisers)
            advisers.push_back(s->clone());
    }
	VotingStrategy::~VotingStrategy() {
        for (Strategy* s : advisers)
            delete s;
        advisers.clear();
    }

}