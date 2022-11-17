#include "Strategy.h"
#include <random>

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

	Decision CooperateStrategy::decide(vector<array<Decision, 3>>&, array<Strategy*, 3>&) {
		return Decision::COOPERATE;
	}

    Decision RandomStrategy::decide(vector<array<Decision, 3>>&, array<Strategy*, 3>&) {
        srandom(123);
        if (rand() > RAND_MAX/2)
		    return Decision::COOPERATE;
        else
		    return Decision::DEFECT;
	}

    Decision GoByMajorityStrategy::decide(
        vector<array<Decision, 3>>& history,
        array<Strategy*, 3>& comps)
    {
        if (history.empty())
            return Decision::COOPERATE;
        unsigned int Cooperations = 0;
        unsigned int Defections = 0;
        for (array<Decision, 3>& decs : history) {
            for (size_t i = 0; i < 3; ++i) {
                if (decs[i] == Decision::COOPERATE)
                    ++Cooperations;
                else
                    ++Defections;
            }
        }
        if (Defections > Cooperations)
            return Decision::DEFECT;
        else
            return Decision::COOPERATE;
    }

}