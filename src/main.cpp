#include <iostream>
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
}

using namespace std;

int main(int argc, char* argv[]) {
    std::string mode;
    unsigned int stepCount;
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
            int i = stoi(optarg);
            if (i < 0)
                stepCount = 0;
            else
                stepCount = i;
            break; }
        case CONF:
            cout << "conf: " << optarg << endl;
            break;
        case MAT:
            cout << "mat: " << optarg << endl;
            break;
        default:
            break;
        }
    }

    if (argc - optind < 3) {
        cerr << argv[0] << ": three or more strategies are required!" << endl;
        return 1;
    }

    try {
        if (mode == "detailed") {
            PrisonersDilemma::DetailedSimulation sim = {
                string(argv[optind]),
                string(argv[optind + 1]),
                string(argv[optind + 2]) };
            sim.run(stepCount);
        }
    }
    catch (const std::invalid_argument& e) {
        cerr << argv[0] << ": " << e.what() << endl;
    }

    return 0;
}