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
// ��������� ����������
Polynomial CreatePoly(double* a, int n);
// ���������� � ����� polynomial.txt
Polynomial ReadPoly(std::istream& is);
// �������� �� ���������
bool AreEqual(Polynomial a, Polynomial b);
// ���� ����������
std::ostream& operator<<(std::ostream& os, Polynomial p);
// ��������� ����������
Polynomial Add(Polynomial a, Polynomial b);
// �������� ����������
Polynomial Multiply(Polynomial a, Polynomial b);
// ���������� ����������
void Simplify(Polynomial& a);
// ��������� ��������� �� ������
void MultiplyByScalar(Polynomial& a, const double scalar);
// ������ ����������
Polynomial Minus(Polynomial a, Polynomial b);
// �������� ���������� � �����
double CalcValue(Polynomial p, double x);
// ���������� ������� (��� ������ �������� ������� � ����� ����� ������������ CalcValue, ��������� ������� � �����)
Polynomial Derivative(Polynomial a);
// ���������� �������� 
double DefiniteIntegral(Polynomial p, double a, double b);
// ��������� �������
void RemovePoly(Polynomial& p);
// ���������� ������ ���������� �� ������
void DrawFunctions(std::ofstream& os, const Polynomial& p, double start, double end, int steps);
// ������ ������, � ������� ����� ���� �������� (������������� �� ���������)
double* PolyToArray(Polynomial a);