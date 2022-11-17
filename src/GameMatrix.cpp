#include "GameMatrix.h"

using namespace std;

namespace {

    const array<unsigned int, 24>& DEFAULT_MATRIX = array<unsigned int, 24>
	{
		7, 7, 7,
		3, 3, 9,
		3, 9, 3,
		9, 3, 3,
		0, 5, 5,
		5, 0, 5,
		5, 5, 0,
		1, 1, 1
	};

}

namespace PrisonersDilemma::gameutils {

    GameMatrix::GameMatrix() {
        mat = new array<unsigned int, 24> (DEFAULT_MATRIX);
    }
    GameMatrix::GameMatrix(const string& file) {
        ifstream f;
        f.exceptions( ifstream::failbit | ifstream::badbit | ifstream::eofbit );
		f.open(file);
        mat = new array<unsigned int, 24>;
		for (size_t i = 0; i < 24; ++i)
			f >> mat->at(i);
		f.close();
    }
    GameMatrix::~GameMatrix() {
        delete mat;
    }
    unsigned int GameMatrix::at(const Decision d1,
                    const Decision d2,
                    const Decision d3, unsigned int idx) const
    {
        size_t id = 0;
		id += (d1 == Decision::COOPERATE ? 0u : 1u);
		id += (d2 == Decision::COOPERATE ? 0u : 1u) << 1;
		id += (d3 == Decision::COOPERATE ? 0u : 1u) << 2;
        if (idx > 2)
            throw std::invalid_argument("bad row index for 7x3 matrix");
        return mat->at(id*3 + idx);
    }
    GameMatrix::GameMatrix (const GameMatrix& o) {
        mat = new array<unsigned int, 24> (*o.mat);
    }
    GameMatrix::GameMatrix (GameMatrix&& o) noexcept {
        delete mat;
        mat = o.mat;
        o.mat = nullptr;
    }
    GameMatrix& GameMatrix::operator= (const GameMatrix& o) {
        if (this != &o) {
            delete mat;
            mat = new array<unsigned int, 24> (*o.mat);
        }
        return *this;
    }
    GameMatrix& GameMatrix::operator= (GameMatrix&& o) {
        if (this != &o) {
            delete mat;
            mat = o.mat;
            o.mat = nullptr;
        }
        return *this;
    }

}
