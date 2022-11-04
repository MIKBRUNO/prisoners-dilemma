#include <iostream>
#include <getopt.h>

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
    while (true) {
        int c = getopt_long_only(argc, argv, "", long_options, NULL);
        if (c == -1)
            break;
        
        switch (c)
        {
        case MODE:
            cout << "mode: " << optarg << endl;
            break;
        case STEPS:
            cout << "steps: " << optarg << endl;
            break;
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

    return 0;
}