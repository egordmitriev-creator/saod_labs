#include <iostream>
#include <cmath>
#include <random>
#include <algorithm>
#include <stdlib.h>
#include <unordered_map>
#include <fstream>
#include <functional>

using namespace std;

void shannon(const int n, double p[], int Length[], char c[][20]) {
    double *q = new double[n];
    q[0] = 0;
    Length[0] = -floor(log2(p[0]));
    for (int i = 1; i < n; ++i) {
        q[i] = q[i - 1] + p[i - 1];
        Length[i] = -floor(log2(p[i]));
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < Length[i - 1]; ++j) {
            q[i - 1] *= 2;
            c[i - 1][j] = floor(q[i - 1]) + '0';
            if (q[i - 1] >= 1) {
                q[i - 1] -= 1;
            }
        }

    }
}

int Med(int L, int R, double *p) {
    double SL = 0;
    for (int i = L; i <= R; i++) {
        SL = SL + p[i];
    }
    double SR = p[R];
    int m = R;
    while (SL >= SR) {
        m--;
        SL = SL - p[m];
        SR = SR + p[m];
    }
    return m;
}

void Fano(int L, int R, int k, double *p, int Length[], char c[][20]) {
    int m;
    if (L < R) {
        k++;
        m = Med(L, R, p);
        for (int i = L; i <= R; i++) {
            if (i <= m) {
                c[i][k] = '0';
                Length[i] = Length[i] + 1;
            } else {
                c[i][k] = '1';
                Length[i] = Length[i] + 1;
            }
        }
        Fano(L, m, k, p, Length, c);
        Fano(m + 1, R, k, p, Length, c);
    }
}

unordered_map<char, int> get_char_counts_from_file(const string &file_name, int &file_size) {
    ifstream file(file_name);
    if (!file.is_open()) {
        throw runtime_error("Could not open file");
    }
    unordered_map<char, int> counter_map;
    file_size = 0;
    for (char c = (char) file.get(); c != EOF; c = (char) file.get()) {
        if (c != '\n' && c != '\r') {
            counter_map[c]++;
            file_size++;
        }
    }
    file.close();
    return counter_map;
}

vector<pair<double, char> > calc_probabilities(const unordered_map<char, int> &counter_map, int count) {
    vector<pair<double, char> > probabilities;
    probabilities.reserve(counter_map.size());
    for (auto i : counter_map) {
        probabilities.emplace_back(make_pair((double) i.second / count, i.first));
    }
    return probabilities;
}

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    int file_size;
    unordered_map<char, int> counter_map;
    try {
        counter_map = get_char_counts_from_file("1.txt", file_size);
    } catch (runtime_error &exc) {
        cout << exc.what();
        return 1;
    }
    auto probabilities = calc_probabilities(counter_map, file_size);
    counter_map.clear();

    sort(probabilities.begin(), probabilities.end(), greater<pair<double, char> >());
    for (auto i : probabilities) {
        cout << fixed << i.first << " | " << i.second << '\n';
    }

    double ent = 0;

    for (auto i : probabilities) {
        ent += i.first*log2(i.first);
    }

    ent *= -1;

    const int n = (int) probabilities.size();

    auto c = new char[n][20];
    auto Length = new int[n];
    auto p = new double[n];
    for (int i = 0; i < n; ++i) {
        p[i] = probabilities[i].first;
    }

    double shen = 0;
    shannon(n, p, Length, c);
    cout << "\nShannon Code:\n";
    cout << "\n  Length Code\n";
    double temp = 0;
    for (int i = 0; i < n; i++) {
        printf("%c | %4.6lf %d ", probabilities[i].second, shen, Length[i]);
        for (int j = 0; j < Length[i]; ++j) {
            printf("%c", c[i][j]);
        }
        cout << '\n';
        shen += p[i];
        temp += p[i] * Length[i];
    }

    double shanAver = temp;
    temp = 0;
    cout << "\nFano Code:\n";
    for (int i = 0; i < n; ++i) {
        Length[i] = 0;
    }
    Fano(0, n - 1, -1, p, Length, c);

    cout << "\n  Length Code\n";
    for (int i = 0; i < n; i++) {
        printf("%c | %4.6lf %d ", probabilities[i].second, p[i], Length[i]);
        for (int j = 0; j < Length[i]; ++j) {
            printf("%c", c[i][j]);
        }
        cout << '\n';
        temp += p[i] * Length[i];
    }

    double fanoAver = temp;

    cout << " entropy     average length        redundancy    "<<endl;
    cout << "           shannon     fano    shannon     fano   "<<endl;
    cout << ent << "  " <<  shanAver << "  " << fanoAver << "  " << shanAver - ent << "  " << fanoAver - ent  << endl;
    delete[] p;
    return 0;
}