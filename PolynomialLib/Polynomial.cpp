#include "pch.h"
#include "Polynomial.h" 
#include <iostream> 
#include <cmath>
#include <fstream>
#include <queue>
// створення многочлену за допомогою масиву

Polynomial CreatePoly(double* a, int n) {
    PolyNode phantom(0, 0);
    Polynomial curr = &phantom;
    for (int i = 0; i < n; ++i) {
        if (a[i] != 0) {
            curr->next = new PolyNode(a[i], i);
            curr = curr->next;
        }
    }
    // ? 
    return phantom.next;
}

// друк многочлену

std::ostream& operator<< (std::ostream& os, Polynomial p) {
    while (p != nullptr) {
        os << p->coef << "x^" << p->power << ' ';
        p = p->next;
    }
    return os;
}

// сума двох многочленів

Polynomial Add(Polynomial a, Polynomial b) {
    PolyNode phantom(0, 0);
    Polynomial curr = &phantom;
    while (a != nullptr && b != nullptr) {
        if (a->power == b->power) {
            double s = a->coef + b->coef;
            if (s != 0.0) {
                curr->next = new PolyNode(s, a->power);
                curr = curr->next;
            }
            a = a->next;
            b = b->next;
        }
        else if (a->power < b->power) {
            curr->next = new PolyNode(a->coef, a->power);
            curr = curr->next;
            a = a->next;
        }
        else {
            curr->next = new PolyNode(b->coef, b->power);
            curr = curr->next;
            b = b->next;
        }
    }
    while (a != nullptr) {
        curr->next = new PolyNode(a->coef, a->power);
        curr = curr->next;
        a = a->next;
    }
    while (b != nullptr) {
        curr->next = new PolyNode(b->coef, b->power);
        curr = curr->next;
        b = b->next;
    }
    return phantom.next;
}

// скорочує многочлен, не повертає значення, а одразу змінює оригінальну змінну

void Simplify(Polynomial& a) {
    Polynomial copyOfPolynomial = a;
    while (copyOfPolynomial != nullptr) {
        Polynomial nextStep = copyOfPolynomial->next;
        while (nextStep != nullptr) {
            if (copyOfPolynomial->power == nextStep->power) {
                copyOfPolynomial->coef += nextStep->coef;
                Polynomial copy_of_copy = copyOfPolynomial;
                while (copy_of_copy->next->power != nextStep->power) {
                    copy_of_copy = copy_of_copy->next;
                }
                copy_of_copy->next = nextStep->next;
                delete nextStep;
                nextStep = copyOfPolynomial->next;
                continue;
            }
            nextStep = nextStep->next;
        }
        if (copyOfPolynomial != nullptr) {
            copyOfPolynomial = copyOfPolynomial->next;
        }
    }
}

// множить два многочлени, але не скорочує їх після множення 
// приклад: (1 + x) * (2 + x) = 2 + x + 2x + x^2 - такий вигляд многочлену і залишиться
// для скорочення варто використати функцію Simplify, яка перетворить 2 + x + 2x + x^2 на 2 + 3х + x^2

Polynomial Multiply(Polynomial a, Polynomial b) {
    PolyNode phantom(0, 0);
    Polynomial curr = &phantom;
    while (a != nullptr) {
        Polynomial copy = b;
        while (copy != nullptr) {
            curr->next = new PolyNode((a->coef * copy->coef), (a->power + copy->power));
            curr = curr->next;
            copy = copy->next;
        }
        a = a->next;
    }
    return phantom.next;
}

// множення на скаляр

void MultiplyByScalar(Polynomial& a, const double scalar) {
    if (scalar == 0) {
        RemovePoly(a);
        a = nullptr;
        return;
    }
    Polynomial curr = a;
    while (curr != nullptr) {
        curr->coef *= scalar;
        curr = curr->next;
    }
}

// віднімання двох многочленів

Polynomial Minus(Polynomial a, Polynomial b) {
    PolyNode phantom(0, 0);
    Polynomial curr = &phantom;
    while (a != nullptr && b != nullptr) {
        if (a->power == b->power) {
            double s = a->coef - b->coef;
            if (s != 0.0) {
                curr->next = new PolyNode(s, a->power);
                curr = curr->next;
            }
            a = a->next;
            b = b->next;
        }
        else if (a->power < b->power) {
            curr->next = new PolyNode(a->coef, a->power);
            curr = curr->next;
            a = a->next;
        }
        else {
            curr->next = new PolyNode(-b->coef, b->power);
            curr = curr->next;
            b = b->next;
        }
    }
    while (a != nullptr) {
        curr->next = new PolyNode(a->coef, a->power);
        curr = curr->next;
        a = a->next;
    }
    while (b != nullptr) {
        curr->next = new PolyNode(-b->coef, b->power);
        curr = curr->next;
        b = b->next;
    }
    return phantom.next;
}

// порахувати значення поліному в точці

double CalcValue(Polynomial p, double x) {
    double result = 0;
    while (p != nullptr) {
        result += p->coef * pow(x, p->power);
        p = p->next;
    }
    return result;
}

// знайти похідну 

Polynomial Derivative(Polynomial a) {
    PolyNode phantom(0, 0);
    Polynomial curr = &phantom;
    while (a != nullptr) {
        if (a->coef * a->power != 0) {
            curr->next = new PolyNode(a->coef * a->power, a->power - 1);
            curr = curr->next;
        }
        a = a->next;
    }
    return phantom.next;
}

// обчислює визначений інтеграл

double DefiniteIntegral(Polynomial p, double a, double b) {
    Polynomial curr = p;
    while (curr != nullptr) {
        curr->coef /= (double)(curr->power + 1);
        curr->power += 1;
        curr = curr->next;
    }
    double result = 0;
    result = CalcValue(p, b) - CalcValue(p, a);
    return result;
}

// видалити поліном

void RemovePoly(Polynomial& p) {
    while (p != nullptr) {
        Polynomial victim = p;
        p = p->next;
        delete victim;
    }
}

// зчитати поліном з файлу

Polynomial ReadPoly(std::istream& is) {
    int n;
    is >> n;
    double* a = new double[n];
    for (int i = 0; i < n; ++i) {
        is >> a[i];
    }
    return CreatePoly(a, n);
}

// перевірка на тотожність

bool AreEqual(Polynomial a, Polynomial b) {
    while (a != nullptr && b != nullptr && a->coef == b->coef && a->power == b->power)
    {
        a = a->next;
        b = b->next;
    }
    return a == b;
}

void DrawFunctions(std::ofstream& os, const Polynomial& p, double start, double end, int steps) {
    for (int i = start; i <= end; i += (end - start) / (double)steps) {
        os << CalcValue(p, (int)(i * 100) / 100.) << ' ';
    }
}

// перетворює поліном на масив

double* PolyToArray(Polynomial a) {
    std::queue<double> elements;
    unsigned len = 0;
    int prev_index = 0;
    int curr_index;
    while (a != nullptr) {
        curr_index = a->power;
        for (unsigned i = prev_index; i < curr_index; ++i) {
            elements.push(0);
        }
        elements.push(a->coef);
        ++len;
        a = a->next;
        prev_index = curr_index + 1;
    }
    double* result = new double[len];
    for (unsigned i = 0; i < len; ++i) {
        result[i] = elements.front();
        elements.pop();
    }
    return result;
}
