#pragma once
#include <string>
#include <fstream>
#include <array>
#include "Strategy.h"

namespace PrisonersDilemma::gameutils {
    
    class GameMatrix {
    public:
        GameMatrix();
        explicit GameMatrix(const std::string& matfile);
        unsigned int at(const Decision d1,
                        const Decision d2,
                        const Decision d3, unsigned int idx) const;
        inline unsigned int at(const Decision d[3], unsigned int idx) const {
            return at(d[0], d[1], d[2], idx);
        }
        ~GameMatrix();
        GameMatrix (const GameMatrix&);
        GameMatrix (GameMatrix&&) noexcept;
        GameMatrix& operator= (const GameMatrix&);
        GameMatrix& operator= (GameMatrix&&);
    private:
        std::array<unsigned int, 24>* mat;
    };

}