#include <filesystem>
#include <fstream>
#include <random>
#include <ctime>
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

    Decision DefectStrategy::decide(
			const std::vector<Decision>& myhist,
			const std::vector<Decision>& hist1,
			const std::vector<Decision>& hist2) {
		return Decision::DEFECT;
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

    TitForTatStrategy::TitForTatStrategy(const string& confdir) {
        filesystem::path pth = confdir;
        pth /= "tit-for-tat.cfg";
        ifstream f;
        f.exceptions( ifstream::failbit | ifstream::badbit );
		f.open(pth.string());
        string mode;
        f >> mode;
        if (mode == "either")
            either = true;
        else if (mode == "both")
            either = false;
        else
            throw invalid_argument("invalid mode for tit-for-tat strategy");
        f.close();
    }

    Decision TitForTatStrategy::decide(
			const std::vector<Decision>& myhist,
			const std::vector<Decision>& hist1,
			const std::vector<Decision>& hist2)
    {
        if (0 == myhist.size())
            return Decision::COOPERATE;
        else if (either) {
            if (hist1.back() == Decision::DEFECT || hist2.back() == Decision::DEFECT)
                return Decision::DEFECT;
        }
        else {
            if (hist1.back() == Decision::DEFECT && hist2.back() == Decision::DEFECT)
                return Decision::DEFECT;
        }
        return Decision::COOPERATE;
    }

    ReactiveStrategy::ReactiveStrategy(const string& confdir) {
        filesystem::path pth = confdir;
        pth /= "reactive.cfg";
        ifstream f;
        f.exceptions( ifstream::failbit | ifstream::badbit );
		f.open(pth.string());
        f >> FirstpP;
        f >> CCp;
        f >> CDp;
        f >> DDp;
        f.close();
        srand(time(nullptr));
    }

    Decision ReactiveStrategy::decide(
			const std::vector<Decision>& myhist,
			const std::vector<Decision>& hist1,
			const std::vector<Decision>& hist2)
    {
        if (0 == myhist.size())
            return decideByProbability(FirstpP);
        if (hist1.back() != hist2.back())
            return decideByProbability(CDp);
        if (hist1.back() == Decision::COOPERATE)
            return decideByProbability(CCp);
        if (hist1.back() == Decision::DEFECT)
            return decideByProbability(DDp);
        return Decision::COOPERATE;
    }

    Decision ReactiveStrategy::decideByProbability(double p) {
        double shot = static_cast<double>(rand());
        shot /= static_cast<double>(RAND_MAX);
        if (shot < p)
            return Decision::COOPERATE;
        else
            return Decision::DEFECT;
    }

}