#include <iostream> 
#include "../PolynomialLib/Polynomial.h" 
#include <fstream>
using std::cout;
using std::endl;
using std::cin;

inline void beautifulPrint() {
    for (int i = 0; i < 100; ++i) cout << '-';
    cout << endl;
}

int main() {
    double a[] = { -99., 1., 2., 1. };
    const int aSize = sizeof a / sizeof a[0];
    // створення першого многочлену
    Polynomial P_a = CreatePoly(a, aSize);
    cout << "P_1: \t\t\t" << P_a << endl;
    beautifulPrint();
    cout << P_a << endl;
    // створення другого многочлену
    std::ifstream fin("polynomial.txt");
    Polynomial P_b = ReadPoly(fin);
    fin.close();
    cout << "P_2: \t\t\t" << P_b << endl;
    // третій многочлен - сума перших двох
    Polynomial sum = Add(P_a, P_b);
    beautifulPrint();
    cout << "P_1 + P_2: \t\t" << sum << endl;
    // четвертий многочлен - добуток перших двох
    Polynomial mul = Multiply(P_a, P_b);
    beautifulPrint();
    cout << "P_1 * P_2: \t\t" << mul << endl;
    beautifulPrint();
    cout << "P_1 * P_2(simplified): \t";
    Simplify(mul);
    cout << mul << endl;
    // множення  многочлену на скаляр
    {
        double scalar;
        cout << "   Enter scalar and I'll multiply first polynomial on it: ";
        cin >> scalar;
        MultiplyByScalar(P_a, scalar);
        beautifulPrint();
        cout << "P_1 * scalar: \t\t" << P_a << endl;
        MultiplyByScalar(P_a, 1 / scalar);
        beautifulPrint();
        cout << "P_1 / scalar: \t\t" << P_a << endl;
    }
    // п'ятий многочлен - різниця першого та другого
    Polynomial min = Minus(P_a, P_b);
    beautifulPrint();
    cout << "P_1 - P_2: \t\t" << min << endl;
    // значення першого многочлену в точці
    {
        double point;
        cout << "   Enter point and I'll find value of polynomial on it: ";
        cin >> point;
        beautifulPrint();
        cout << "P_1(" << point << "): \t\t" << CalcValue(P_a, point) << endl;
    }
    // похідна від першого поліному
    Polynomial der = Derivative(P_a);
    beautifulPrint();
    cout << "P_1' = \t\t\t" << der << endl;
    // визначений інтеграл, С = 0 (можна змінити)
    {
        beautifulPrint();
        cout << "P_1 Definite Integral: " << DefiniteIntegral(P_a, 0, 2) << endl;
    }
    std::ofstream fout("points.txt");
    // зберегти у файл значення многочлену на відрізку [1, 6] з кроком 1
    DrawFunctions(fout, P_a, 1, 6, 5);
    fout.close();
    system("pause");
    return 0;
}