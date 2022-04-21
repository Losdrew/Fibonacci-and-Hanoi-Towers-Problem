#include <iostream>
#include <chrono>
#include <cmath>

using namespace std;

unsigned long long FibRecursive(int n, unsigned long long a, unsigned long long b);
unsigned long long FibIterative(int n, unsigned long long a, unsigned long long b);
unsigned long long FibFormula(int n, unsigned long long a, unsigned long long b);
void HanoiTowers(int n, char from_rod, char to_rod, char aux_rod);
double Time(int n, unsigned long long a, unsigned long long b, unsigned long long (*pf)(int, unsigned long long, unsigned long long));

int main()
{
    cout << "Enter n: ";
    int n;
    cin >> n;

    cout << "You entered n = " << n << "\n\n";

    // recursive Fibonacci
    cout << "Recursive Fibonacci algorithm:\n"
        "F(" << n << ") = " << FibRecursive(n, 0, 1) << "\n\n";

    cout << "Time elapsed: " << Time(n, 0, 1, FibRecursive) << " nanoseconds.\n\n";

    // iterative Fibonacci
    cout << "Iterative Fibonacci algorithm:\n"
        "F(" << n << ") = " << FibIterative(n, 0, 1) << "\n\n";

    cout << "Time elapsed: " << Time(n, 0, 1, FibIterative) << " nanoseconds.\n\n";

    // closed-form formula Fibonacci
    cout << "Closed form formula Fibonacci algorithm:\n"
        "F(" << n << ") = " << FibFormula(n, 0, 1) << "\n\n";

    cout << "Time elapsed: " << Time(n, 0, 1, FibFormula) << " nanoseconds.\n\n";

    system("pause");

    // Hanoi towers
    cout << "Hanoi Towers algorithm:\n";

    auto begin = chrono::high_resolution_clock::now();

    HanoiTowers(n, 'A', 'B', 'C');

    auto end = chrono::high_resolution_clock::now();
    auto elapsed = chrono::duration_cast<chrono::nanoseconds>(end - begin);

    cout << "Time elapsed: " << elapsed.count() * 1e-9 << " seconds.\n\n";
}

//
// Recursive Fibonacci
//
unsigned long long FibRecursive(int n, unsigned long long a, unsigned long long b)
{
    if (n == 0)
        return a;

    if (n == 1)
        return b;

    return FibRecursive(n - 1, b, a + b);
}

//
// Iterative Fibonacci
//
unsigned long long FibIterative(int n, unsigned long long a, unsigned long long b)
{
    if (n == 0)
        return a;

    if (n == 1 || n == 2)
        return b;

    unsigned long long c = 1;

    for (int i = n - 2; i > 0; i--)
    {
        a = b;
        b = c;
        c = a + b;
    }

    return c;
}

//
// closed-form formula Fibonacci
//
unsigned long long FibFormula(int n, unsigned long long a, unsigned long long b)
{
    return (1 / sqrt(5) * (pow(((1 + sqrt(5)) / 2), n) - (pow(((1 - sqrt(5)) / 2), n))));
}

//
// Hanoi towers
//
void HanoiTowers(int n, char from_rod, char to_rod, char aux_rod)
{
    if (n == 1)
    {
        cout << "Move disk 1 from rod " << from_rod <<
            " to rod " << to_rod << endl;
        return;
    }

    HanoiTowers(n - 1, from_rod, aux_rod, to_rod);
    cout << "Move disk " << n << " from rod " << from_rod <<
        " to rod " << to_rod << endl;
    HanoiTowers(n - 1, aux_rod, to_rod, from_rod);
}

//
// Time efficiency
//
double Time(int n, unsigned long long a, unsigned long long b, unsigned long long (*pf)(int, unsigned long long, unsigned long long))
{
    auto begin = chrono::high_resolution_clock::now();

    pf(n, a, b);

    auto end = chrono::high_resolution_clock::now();
    auto elapsed = chrono::duration_cast<chrono::nanoseconds>(end - begin);

    return elapsed.count();
}