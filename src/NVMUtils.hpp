#include <fstream>
#include <iostream>
#include <set>
#include <map>
#include <string>
#include <algorithm>
#include <cmath>
#include <sstream>

using namespace std;

map<int, set<int> >
readImgVecsFromNVM(string fpath) {
    map<int, set<int> > res;
    ifstream fin(fpath.c_str());
    string line;
    getline(fin, line); getline(fin, line); // ignore
    getline(fin, line);
    int nimgs = stoi(line);
    while(nimgs--) getline(fin, line);
    getline(fin, line);
    
    getline(fin, line);
    int npts = stoi(line);
    cerr << npts << " total feature points" << endl;
    float temp;
    for (int ftrID = 0; ftrID < npts; ftrID++) {
        fin >> temp >> temp >> temp;
        fin >> temp >> temp >> temp;
        int num_imgs;
        fin >> num_imgs;
        while (num_imgs--) {
            int img_idx;
            fin >> img_idx >> temp >> temp >> temp;
            if (res.count(img_idx) <= 0) {
                res[img_idx] = set<int>();
            }
            res[img_idx].insert(ftrID);
        }
    }
    fin.close();
    return res;
}

void printVecs(map<int, set<int> > vecs) {
    for (auto iter = vecs.begin(); iter != vecs.end(); ++iter) {
        cout << "Image ID: " << iter->first << endl;
        set<int> ftr_pts = iter->second;
        for (auto iter2 = ftr_pts.begin(); iter2 != ftr_pts.end(); ++iter2) {
            cout << " " << *iter2 << endl;
        }
    }
}

float computeSimilarity(map<int, set<int> > &vecs, int i, int j) {
    if (vecs.count(i) <= 0 || vecs.count(j) <= 0) {
        return 0.0f;
    }

    auto iter1 = vecs[i].begin(), iter2 = vecs[j].begin();
    int count_int = 0;
    while (iter1 != vecs[i].end() && iter2 != vecs[j].end()) {
        if (*iter1 == *iter2) {
            count_int++;
            iter1++; iter2++;
        } else if (*iter1 > *iter2) {
            iter2++;
        } else {
            iter1++;
        }
    }

    double denom = vecs[i].size() * 1.0f * vecs[j].size();
    return (count_int * 1.0f / sqrt(denom));
}

vector<vector<float> >
readSimFile(string fname) {
    vector<vector<float> > res;
    ifstream fin(fname.c_str());
    string line;
    float val;
    while (getline(fin, line)) {
        istringstream iss(line);
        vector<float> row;
        while (iss >> val) {
            row.push_back(val);
        }
        res.push_back(row);
    }
    fin.close();
    // set i,j = j,i
    for (int i = 0; i < res.size(); i++) {
        for (int j = 0; j < res[i].size(); j++) {
            if (i == j) res[i][j] = 0;
            else res[i][j] = max(res[i][j], res[j][i]);
        }
    }
    return res;
}

/**
 * Assumes res is already set to all false
 */
void readIgnoreList(string fname, bool res[]) {
    ifstream fin(fname.c_str());
    if (!fin.is_open()) {
        return;
    }
    string line;
    while (getline(fin, line)) {
        res[stoi(line)] = true;
    }
    fin.close();
}

