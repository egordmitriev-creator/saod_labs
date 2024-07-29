#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <math.h>
#include <vector>

using namespace std;
int s;
double C[50][10], L[50];

float chas[50] = {0};
char ch[50];

int C2[50][10] = {{0}};
int Length[50], i;
float SL, SR;

float chas2[50] = {0};
char ch2[50];

void Hen(int n)
{
    int i, j;
    double Q[n];
    Q[0] = 0.0;
    L[0] = (int)(-log2(chas[0])) + 1;
    for (i = 1; i < n; i++) {
        Q[i] = Q[i - 1] + chas[i - 1];
        L[i] = (int)(-log2(chas[i])) + 1;
    }
    cout << endl;
    for (i = 0; i < n; i++) {
        for (j = 0; j < L[i]; j++) {
            Q[i] = Q[i] * 2;
            C[i][j] = int(Q[i]);
            if (Q[i] > 1)
                Q[i] = Q[i] - 1;
        }
    }
}

int Med(int L, int R)
{
    int k, m1;
    SL = 0;
    for (k = L; k <= R - 1; k++)
        SL = SL + chas2[k];
    if (SL == 0)
        return 0;
    SR = chas2[R];
    m1 = R;
    while (SL >= SR) {
        m1 = m1 - 1;
        SL = SL - chas2[m1];
        SR = SR + chas2[m1];
    }
    return m1;
}

void Fano(int L, int R, int k)
{
    int m;
    if (L < R) {
        k++;
        m = Med(L, R);
        for (i = L; i <= m; i++) {
            C[i][k] = 0;
            Length[i] = Length[i] + 1;
        }
        for (i = m + 1; i <= R; i++) {
            C[i][k] = 1;
            Length[i] = Length[i] + 1;
        }
        Fano(L, m, k);
        Fano(m + 1, R, k);
    }
}

void BubbleSort2(float* A, int n)
{
    int i, j;
    float t;
    char t1;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - 1; j++)
            if (A[j + 1] > A[j]) {
                t = A[j + 1];
                A[j + 1] = A[j];
                A[j] = t;
                t1 = ch[j + 1];
                ch[j + 1] = ch[j];
                ch[j] = t1;
            }
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    int j = 0, q = 0, i, kol = 0, sum = 0;
    double H = 0, Lsr = 0.0;
    ifstream f("1.txt", ios::out | ios::binary);
    map<char, int> m;
    while (!f.eof()) {
        char c = f.get();
        if ((c == 10) || (c == 13))
            continue;
        m[c]++;
        kol++;
    }
    s = m.size();
    for (map<char, int>::iterator itr = m.begin(); itr != m.end(); j++, ++itr) {
        ch[j] = itr->first;
        chas[j] = (float)itr->second / kol;
    }
    BubbleSort2(chas, 51);
    Hen(50);
    cout << "Символ "
         << "Верояность символа  "
         << "Код символа" << endl;
    for (i = 0; i < s; i++) {
        cout << "    " << ch[i] << "     ";
        printf("%.8f", chas[i]);
        cout << "       ";
        for (j = 0; j < L[i]; j++)
            cout << C[i][j];
            cout << "\t" << j;
        cout << endl;
    }
    for (i = 0; i < s; i++)
        H = H - chas[i] * (log(chas[i]) / log(2.0));
    for (i = 0; i < s; i++)
        Lsr = Lsr + chas[i] * L[i];
    cout << "Kol-vo = " << kol << endl;
    cout << "Size = " << s << endl;
    cout << "Энтропия исходного файла ровна " << H << endl;
    cout << "Средняя длина кодового слова ровна " << Lsr << endl;
    cout << "Соотношение " << Lsr << "<" << H << " + 1"
         << " выполнено" << endl;
//////////////////////////////////////////////////////
    Fano(0, 49, -1);
    cout << "Символ "
         << "Верояность символа  "
         << "Код символа" << endl;
    for (i = 0; i < 50; i++) {
        cout << "    " << ch2[i] << "     ";
        printf("%.8f", chas[i]);
        cout << "       ";
        for (j = 0; j < Length[i]; j++) {
            if ((i > 10) && (j == 0))
                cout << "1";
            else
                cout << C2[i][j];
        }
        cout << endl;
    }
    for (i = 0; i < m.size(); i++)
        H = H - chas2[i] * (log(chas2[i]) / log(2.0));
    for (i = 0; i < m.size(); i++)
        Lsr = Lsr + chas2[i] * Length[i];
    cout << "Kol-vo = " << kol << endl;
    cout << "Size = " << m.size() << endl;
    cout << "Энтропия исходного файла ровна " << H << endl;
    cout << "Средняя длина кодового слова ровна " << Lsr << endl;
    cout << "Соотношение " << Lsr << "<" << H << "+ 1"
         << " выполнено" << endl;

    return 0;
}