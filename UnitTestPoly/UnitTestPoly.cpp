#include "pch.h"
#include "CppUnitTest.h"
#include "../PolynomialLib/Polynomial.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestPolynomial
{
	TEST_CLASS(UnitTestPolynomial)
	{
	public:
		TEST_METHOD(_Are_Equal_)
		{
			double a[] = { -99.,1.,2.,1. };
			const int n = sizeof a / sizeof a[0];
			double b[] = { -99.,1.,2.,1. };
			const int m = sizeof b / sizeof b[0];
			Polynomial A = CreatePoly(a, n);
			Polynomial B = CreatePoly(b, m);
			Assert::IsTrue(AreEqual(A, B));

			double c[] = { -99.,1.,2.,1.,5.,0.,-4. };
			const int k = sizeof c / sizeof c[0];
			Polynomial C = CreatePoly(c, k);
			Assert::IsFalse(AreEqual(A, C));

			double d[] = { 75.,0.,-2.,-1.,0.,0.,4.,0.,1. };
			const int l = sizeof d / sizeof d[0];
			Polynomial D = CreatePoly(d, l);
			Assert::IsFalse(AreEqual(A, D));
			RemovePoly(A); RemovePoly(B); RemovePoly(C); RemovePoly(D);
		}
		TEST_METHOD(_Add_function_)
		{
			double a[] = { -99., 1., 2., 1. };
			Polynomial polyA = CreatePoly(a, 4);
			double b[] = { 5., 75., 2., 7., 9., 8. };
			Polynomial polyB = CreatePoly(b, 6);
			Polynomial sum = Add(polyA, polyB);
			Polynomial sum_rev = Add(polyB, polyA); // від перестановки доданків сума не повинна змінитися
			double correct[] = { -94., 76., 4., 8., 9., 8. };
			const int corSize = sizeof b / sizeof b[0];
			Polynomial correct_result = CreatePoly(correct, corSize);
			Assert::IsTrue(AreEqual(sum, correct_result));
			Assert::IsTrue(AreEqual(sum_rev, correct_result));
			++sum->coef;
			Assert::IsFalse(AreEqual(sum, correct_result));
			RemovePoly(polyA); RemovePoly(polyB); RemovePoly(sum); RemovePoly(sum_rev); RemovePoly(correct_result);
		}
		TEST_METHOD(_Add_function_2nd_part)
		{
			double pos[] = { 1.,2.,3.,4.,5. };
			double neg[] = { -1.,-2.,-3.,-4.,-5. };
			Polynomial A = CreatePoly(pos, 5);
			Polynomial B = CreatePoly(neg, 5);
			Assert::IsFalse(Add(A, B));
			RemovePoly(A); RemovePoly(B);
		}
		TEST_METHOD(_Remove_Poly_) {
			double a[] = { -99., 1., 2., 1. };
			const int aSize = sizeof a / sizeof a[0];
			Polynomial polyA = CreatePoly(a, aSize);
			RemovePoly(polyA);
			Assert::IsTrue(polyA == nullptr);
		}
		TEST_METHOD(_Test_Calc_Value_)
		{
			double a[] = { -16.,0.,0.,0.,1. };
			Polynomial A = CreatePoly(a, 5);
			Assert::AreEqual(0.0, CalcValue(A, 2.0));
			Assert::AreEqual(0.0, CalcValue(A, -2.0));
			Assert::AreEqual(-16.0, CalcValue(A, 0.0));
			Assert::AreEqual(-15.0, CalcValue(A, 1.0));
			RemovePoly(A);
		}
		TEST_METHOD(_Multiply_By_Zeroes_)
		{
			double a[] = { 0., 0., 0., 0. };
			double b[] = { 1., -1., 1., -1. };
			double c[] = { 2., -7., 6., 4., 9. };
			double d[] = { 0., -1., 14., 0., 9. };
			Polynomial zeroP = CreatePoly(a, 4);
			Polynomial plusMinus = CreatePoly(b, 4);
			Polynomial random = CreatePoly(c, 5);
			Polynomial randomWithZeroes = CreatePoly(d, 5);
			Polynomial empty = (0, 0);
			Polynomial test = Multiply(zeroP, plusMinus);
			Simplify(test);
			Assert::IsTrue(AreEqual(test, empty));
			RemovePoly(test);
			test = Multiply(zeroP, random);
			Simplify(test);
			Assert::IsTrue(AreEqual(test, empty));
			RemovePoly(test);
			test = Multiply(zeroP, randomWithZeroes);
			Simplify(test);
			Assert::IsTrue(AreEqual(test, empty));
			RemovePoly(test);
			test = Multiply(zeroP, empty);
			Simplify(test);
			Assert::IsTrue(AreEqual(test, empty));
			RemovePoly(test);
			RemovePoly(randomWithZeroes);
			RemovePoly(random);
			RemovePoly(plusMinus);
			RemovePoly(zeroP);
		}
		TEST_METHOD(_Multiply_)
		{
			double a[] = { 1., -1., 1., -1. };
			Polynomial plusMinus = CreatePoly(a, 4);
			Polynomial test = Multiply(plusMinus, plusMinus);
			double answer_plusMinus[] = { 1., -2., 3., -4., 3., -2., 1 };
			Polynomial answer = CreatePoly(answer_plusMinus, 7);
			Simplify(test);
			Assert::IsTrue(AreEqual(test, answer));
			RemovePoly(test);
			RemovePoly(plusMinus);
			RemovePoly(answer);
		}
		TEST_METHOD(_Multiply_By_Scalar_)
		{
			double a[] = { -99., 1., 2., 1. };
			Polynomial polyA = CreatePoly(a, 4);
			double b[] = { 5., 75., 2., 7., 9., 8. };
			Polynomial polyB = CreatePoly(b, 6);
			double b_answer[] = { 10., 150., 4., 14., 18., 16. };
			Polynomial answerB = CreatePoly(b_answer, 6);
			MultiplyByScalar(polyA, 0.);
			Simplify(polyA);
			Assert::IsTrue(AreEqual(polyA, nullptr));
			MultiplyByScalar(polyB, 2.);
			Assert::IsTrue(AreEqual(polyB, answerB));
			RemovePoly(polyA);
			RemovePoly(polyB);
			RemovePoly(answerB);
		}
		TEST_METHOD(_Derivative_)
		{
			double a[] = { -99., 1., 2., 1. };
			Polynomial polyA = CreatePoly(a, 4);
			double b[] = { 5., 75., 2., 7., 9., 8. };
			Polynomial polyB = CreatePoly(b, 6);
			double a_answer[] = { 1., 4., 3. };
			double b_answer[] = { 75., 4., 21., 36., 40. };
			Polynomial aAnswer = CreatePoly(a_answer, 3);
			Polynomial bAnswer = CreatePoly(b_answer, 5);
			Assert::IsTrue(AreEqual(Derivative(polyA), aAnswer));
			Assert::IsTrue(AreEqual(Derivative(polyB), bAnswer));
			RemovePoly(polyA);
			RemovePoly(polyB);
			RemovePoly(aAnswer);
			RemovePoly(bAnswer);
		}
		TEST_METHOD(_Poly_To_Array) {
			double a[] = { -99., 1., 2., 1. };
			Polynomial polyA = CreatePoly(a, 4);
			double* arr = PolyToArray(polyA);
			for (unsigned i = 0; i < 4; ++i) {
				Assert::IsTrue(a[i] == arr[i]);
			}
			double b[] = { 5., 75., 0., 0., 9., 8. };
			Polynomial polyB = CreatePoly(b, 6);
			double* arr2 = PolyToArray(polyB);
			for (unsigned i = 0; i < 4; ++i) {
				Assert::IsTrue(b[i] == arr2[i]);
			}
			delete[] arr;
			delete[] arr2;
			RemovePoly(polyA);
			RemovePoly(polyB);
		}
	};
}