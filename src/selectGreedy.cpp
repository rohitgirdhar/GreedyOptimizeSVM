/**
 * Note: The output is 0 indexed
 */

#include <iostream>
#include <vector>
#include <set>
#include <fstream>
#include <sstream>
#include "NVMUtils.hpp"

using namespace std;

void help() {
    cerr << "Usage: ./prog <sim file> <K> <output_file> <ignore_list_fpath (img indexes to ignore in training)>" << endl;
}

void print_set(set<int> C, string output_file) {
    ofstream fout(output_file.c_str(), ios::out);
    for (auto iter = C.begin(); iter != C.end(); ++iter) {
        fout << *iter << endl;
    }
    fout.close();
}

set<int> greedySelect(vector<vector<float> > &sim, int K, bool ignore[]) {
    int N = sim.size();
    vector<float> cur(N, 0.0f);
    set<int> C;

    float max_improvement = 0.0f;
    int max_improv_i = 0;
    for (int i = 0; i < K; i++) {
        max_improvement = 0.0f;
        for (int j = 0; j < N; j++) {
            if (ignore[j]) continue;
            if (C.count(j)) continue;
            float improv = 0;
            for (int k = 0; k < N; k++) {
                if (ignore[k]) continue;
                if (sim[j][k] - cur[k] > 0) {
                    improv += sim[j][k] - cur[k];
                }
            }
            if (improv > max_improvement) {
                max_improvement = improv;
                max_improv_i = j;
            }
        }
        if (max_improvement == 0) return C;
        C.insert(max_improv_i);
        for (int k = 0; k < N; k++) {
            if (ignore[k]) continue;
            if (sim[max_improv_i][k] > cur[i]) {
                cur[k] = sim[max_improv_i][k];
            }
        }
        cerr << "i = " << i << " Improv: " << max_improvement << endl;
        cerr << "selected: " << max_improv_i << endl;
    }
    return C;
}

int main(int argc, char *argv[]) {
    if (argc < 5) {
        help();
        return -1;
    }
    string simFile = argv[1];
    int K = stoi(argv[2]);
    vector<vector<float> > sim = readSimFile(simFile);
    cout << "Read sims file " << endl;
    bool ignore[1000000] = {false};
    readIgnoreList(argv[4], ignore);
    set<int> C = greedySelect(sim, K, ignore);
    print_set(C, argv[3]);
    return 0;
}
