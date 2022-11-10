#include "Strategy.h"
#include <random>

namespace PrisonersDilemma {

    std::ostream& operator<<(std::ostream& o, Decision d) {
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

	Decision CooperateStartegy::decide() {
		return Decision::COOPERATE;
	}

}