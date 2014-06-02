#include <iostream>
#include <fstream>
#include <cmath>
#include "svm.h"

using namespace std;

void modifyModel(svm_model *model, char *sel_fpath) {
    ifstream fin(sel_fpath);
    string line;
    while (getline(fin, line)) {
        int id = stoi(line);
        // simply set the coef to 0s
        for (int i = 0; i < model->nr_class - 1; i++) {
            model->sv_coef[i][id] = 0.0;
        }
    }
    fin.close();
}

void help() {
    cerr << "Usage : ./prog <model fpath> <output model fpath> <sel list fpath: 0 indexed>" << endl;
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        help(); return -1;
    }
    svm_model *model = svm_load_model(argv[1]);
    modifyModel(model, argv[3]);
    svm_save_model(argv[2], model);
    return 0;
}
