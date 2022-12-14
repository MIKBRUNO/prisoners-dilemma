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
		{"matrix", 1, NULL, MAT},
		{NULL, 0, NULL, 0}
	};

}

using namespace std;

int main(int argc, char* argv[]) {
	std::string mode;
	unsigned int stepCount = 1;
	std::string matFile = "";
	std::string confDir = ""s;
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
			confDir = optarg;
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
	if (mode.empty()) {
		if (argc - optind > 3)
			mode = "tournament";
		else
			mode = "detailed";
	}

	PrisonersDilemma::simutils::SimMatrix matrix{};
	if (matFile != "") {
		try {
			matrix = PrisonersDilemma::simutils::SimMatrix(matFile);
		}
		catch (const ifstream::failure&) {
			cerr << argv[0] << ": Exception while opening/reading matrix from file " <<
				matFile << endl;
			return 1;
		}
	}

	try {
		vector<PrisonersDilemma::Prisoner> prisoners {};
		for (size_t i = 0; i < argc - optind; ++i) {
			string name = "["s + to_string(i) + "]"s;
			prisoners.push_back(PrisonersDilemma::Prisoner(name, argv[optind + i], confDir));
		}
		if (mode == "detailed" || mode == "fast") {
			PrisonersDilemma::ThreePrisonerSimulation sim = { prisoners, matrix };
			sim.run(stepCount, (mode == "fast"));
		}
		else if (mode == "tournament") {
			PrisonersDilemma::Tournament sim = { prisoners, matrix };
			sim.run(stepCount);
		}
		else {
			cerr << argv[0] << ": invalid mode name " << mode << endl;
			return 1;
		}
	}
	catch (const invalid_argument& e) {
		cerr << argv[0] << ": " << e.what() << endl;
		return 1;
	}
	catch (const ifstream::failure& e) {
		cerr << argv[0] << ": Exception while reading configuration files." << endl;
		return 1;
	}
	catch (const exception& e) {
		cerr << argv[0] << ": " << e.what() << endl;
		return 1;
	}

	return 0;
}