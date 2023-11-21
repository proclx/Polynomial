#pragma once 
#include <iostream> 

struct PolyNode;
using Polynomial = PolyNode*;

struct PolyNode {
	double coef;
	int power;
	Polynomial next;
	PolyNode(double c, int p, Polynomial n = nullptr) : coef(c), power(p), next(n) {}
};
// створення многочлену
Polynomial CreatePoly(double* a, int n);
// зчитування з файлу polynomial.txt
Polynomial ReadPoly(std::istream& is);
// перевірка на тотожність
bool AreEqual(Polynomial a, Polynomial b);
// друк многочлену
std::ostream& operator<<(std::ostream& os, Polynomial p);
// додавання многочленів
Polynomial Add(Polynomial a, Polynomial b);
// множення многочленів
Polynomial Multiply(Polynomial a, Polynomial b);
// скорочення многочленів
void Simplify(Polynomial& a);
// помножити многочлен на скаляр
void MultiplyByScalar(Polynomial& a, const double scalar);
// різниця многочленів
Polynomial Minus(Polynomial a, Polynomial b);
// значення многочлену в точці
double CalcValue(Polynomial p, double x);
// побудувати похідну (щоб знайти значення похідної в точці можна скористатися CalcValue, передавши похідну і точку)
Polynomial Derivative(Polynomial a);
// визначений інтеграл 
double DefiniteIntegral(Polynomial p, double a, double b);
// видалення поліному
void RemovePoly(Polynomial& p);
// побудувати графік многочлена на відрізку
void DrawFunctions(std::ofstream& os, const Polynomial& p, double start, double end, int steps);
// приймає поліном, а повертає масив його елементів (впорядкований за степенями)
double* PolyToArray(Polynomial a);