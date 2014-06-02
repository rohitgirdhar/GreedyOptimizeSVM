#include <iostream>
#include <fstream>
#include <cmath>
#include "svm.h"

using namespace std;

double euc_dist(svm_node* a, svm_node* b) {
    int ai = 0, bi = 0;
    double d = 0;
    while (a[ai].index != -1 && b[bi].index != -1) {
        if (a[ai].index == b[bi].index) {
            d += pow(a[ai].value - b[bi].value, 2);
            ai++; bi++;
        } else if (a[ai].index > b[bi].index) {
            bi++;
        } else {
            ai++;
        }
    }
    return sqrt(d);
}

void findSim(svm_model *model, char *ofpath) {
    int l = model->l;
    double **res = new double*[l];
    for (int i = 0; i < l; i++) res[i] = new double[l];

    for (int i = 0; i < l; i++) {
        for (int j = 0; j <= i; j++) {
            cout << i << " " << j << endl;
            double d = euc_dist(model->SV[i], model->SV[j]);
            res[i][j] = res[j][i] = d > 0 ? (1.0 / d) : 1.0; // use 1/d as the similarity
        }
    }

    ofstream fout(ofpath, ios::out);
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < l; j++) {
            fout << res[i][j] << " ";
        }
        fout << endl;
    }
    fout.close();

    for (int i = 0; i < l; i++) delete res[i];
    delete res;
}

void help() {
    cerr << "Usage : ./prog <model fpath> <output_fpath>" << endl;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        help(); return -1;
    }
    svm_model *model = svm_load_model(argv[1]);
    findSim(model, argv[2]);
    return 0;
}
