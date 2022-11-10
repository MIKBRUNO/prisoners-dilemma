#include <iostream>
#include <fstream>
#include <getopt.h>
#include "Simulation.h"

namespace {

    enum OPTIONS {
        MODE, STEPS, CONF, MAT
    };

    static struct option long_options[] =
    {
        {"mode", 1, NULL, MODE},
        {"steps", 1, NULL, STEPS},
        {"configs", 1, NULL, CONF},
        {"matrix", 1, NULL, MAT}
    };

    const std::array<unsigned int, 24>* DEFAULT_MATRIX = new std::array<unsigned int, 24>
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

using namespace std;

int main(int argc, char* argv[]) {
    std::string mode = "detailed"s;
    unsigned int stepCount = 0;
    std::string matFile = "";
    while (true) {
        int c = getopt_long_only(argc, argv, "", long_options, NULL);
        if (c == -1)
            break;
        switch (c)
        {
        case MODE:
            mode = optarg;
            break;
        case STEPS: {
            int i = 0;
            try {
                i = stoi(optarg);
            }
            catch (const std::exception& e) {
                cerr << argv[0] << ": cannot get valid number of steps from " <<
                    optarg << endl;
                return 1;
            }
            if (i < 0)
                stepCount = 0;
            else
                stepCount = i;
            break; }
        case CONF:
            cout << "conf: " << optarg << endl;
            break;
        case MAT:
            matFile = optarg;
            break;
        default:
            break;
        }
    }
    if (argc - optind < 3) {
        cerr << argv[0] << ": three or more strategies are required!" << endl;
        return 1;
    }

    const array<unsigned int, 24>* matrix = DEFAULT_MATRIX;
    if (matFile != "") {
        array<unsigned int, 24>* mat = new array<unsigned int, 24>;
        try {
            PrisonersDilemma::readMatrixFromFile(mat, matFile);
        }
        catch (const ifstream::failure&) {
            cerr << argv[0] << ": Exception while opening/reading matrix from file " <<
                matFile << endl;
            return 1;
        }
        matrix = mat;
    }

    try {
        if (mode == "detailed") {
            PrisonersDilemma::DetailedSimulation sim = {
                string(argv[optind]),
                string(argv[optind + 1]),
                string(argv[optind + 2]),
                *matrix
            };
            sim.run(stepCount);
        }
        else if (true) {
            ;
        }
        else {
            cerr << argv[0] << ": invalid mode name" << mode << endl;
            return 1;
        }
    }
    catch (const std::invalid_argument& e) {
        cerr << argv[0] << ": " << e.what() << endl;
    }

    return 0;
}