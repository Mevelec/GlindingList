#include "pch.h"
#include "CppUnitTest.h"
#include <GlidingList.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GlidingTest
{
	TEST_CLASS(GlidingTest)
	{
	public:
		// [back/tail][.]...[.]...[center]...[.]...[.][front/head]
		TEST_METHOD(Test_push_back)
		{
			GlindingList<int> gl1;
			gl1.push_back(0);
			gl1.push_back(-1);
			gl1.push_back(-2);
			gl1.push_back(-3);
			//'        "
			//0,-1,-2,-3
			Assert::AreEqual(0, gl1.at(0), L"at(0)");
			Assert::AreEqual(-1, gl1.at(-1), L"at(-1)");
			Assert::AreEqual(-2, gl1.at(-2), L"at(-2)");
			Assert::AreEqual(-3, gl1.at(-3), L"at(-3)");
		}
		TEST_METHOD(Test_push_front)
		{
			GlindingList<int> gl1;
			gl1.push_front(0);
			gl1.push_front(1);
			gl1.push_front(2);
			gl1.push_front(3);
			//"     '
			//0,1,2,3
			Assert::AreEqual(0, gl1.at(0), L"at(0)");
			Assert::AreEqual(1, gl1.at(1), L"at(1)");
			Assert::AreEqual(2, gl1.at(2), L"at(2)");
			Assert::AreEqual(3, gl1.at(3), L"at(3)");
		}
		TEST_METHOD(Test_push_front_back)
		{
			GlindingList<int> gl1;
			gl1.push_front(0);
			gl1.push_front(1);
			gl1.push_front(2);
			gl1.push_front(3);
			gl1.push_back(-1);
			gl1.push_back(-2);
			gl1.push_back(-3);
			//"     '
			//0,1,2,3
			Assert::AreEqual(0, gl1.at(0), L"at(0)");
			Assert::AreEqual(1, gl1.at(1), L"at(1)");
			Assert::AreEqual(2, gl1.at(2), L"at(2)");
			Assert::AreEqual(3, gl1.at(3), L"at(3)");

			Assert::AreEqual(-1, gl1.at(-1), L"at(-1)");
			Assert::AreEqual(-2, gl1.at(-2), L"at(-2)");
			Assert::AreEqual(-3, gl1.at(-3), L"at(-3)");
		}
		TEST_METHOD(Test_operator_at)
		{
			// already tested
			GlindingList<int> gl1;
			gl1.push_front(0);
			gl1.push_front(1);
			gl1.push_front(2);
			gl1.push_front(3);
			gl1.push_back(-1);
			gl1.push_back(-2);
			gl1.push_back(-3);
			//"     '
			//0,1,2,3
			Assert::AreEqual(0, gl1[0], L"[0]");
			Assert::AreEqual(1, gl1[1], L"[1]");
			Assert::AreEqual(2, gl1[2], L"[2]");
			Assert::AreEqual(3, gl1[3], L"[3]");

			Assert::AreEqual(-1, gl1[-1], L"[-1]");
			Assert::AreEqual(-2, gl1[-2], L"[-2]");
			Assert::AreEqual(-3, gl1[-3], L"[-3]");
		}
		TEST_METHOD(Test_at)
		{
			GlindingList<int> gl1;
			gl1.push_front(0);
			gl1.push_front(1);
			gl1.push_front(2);
			gl1.push_front(3);
			gl1.push_back(-1);
			gl1.push_back(-2);
			gl1.push_back(-3);
			//"     '
			//0,1,2,3
			Assert::AreEqual(0, gl1.at(0), L"at(0)");
			Assert::AreEqual(1, gl1.at(1), L"at(1)");
			Assert::AreEqual(2, gl1.at(2), L"at(2)");
			Assert::AreEqual(3, gl1.at(3), L"at(3)");

			Assert::AreEqual(-1, gl1.at(-1), L"at(-1)");
			Assert::AreEqual(-2, gl1.at(-2), L"at(-2)");
			Assert::AreEqual(-3, gl1.at(-3), L"at(-3)");
		}

		TEST_METHOD(Test_equal) {
			GlindingList<int> gl1;
			GlindingList<int> gl2;
			Assert::IsTrue(gl1 == gl2, L"expect true");

			gl1.push_front(0);
			gl1.push_front(1);
			gl1.push_back(-1);
			Assert::IsFalse(gl1 == gl2, L"expect false");

			gl2.push_front(0);
			gl2.push_front(1);
			gl2.push_back(-1);
			Assert::IsTrue(gl1 == gl2, L"expect true");
		}
		TEST_METHOD(Test_not_equal) {
			GlindingList<int> gl1;
			GlindingList<int> gl2;
			Assert::IsFalse(gl1 != gl2, L"expect true");

			gl1.push_front(0);
			gl1.push_front(1);
			gl1.push_back(-1);
			Assert::IsTrue(gl1 != gl2, L"expect false");

			gl2.push_front(0);
			gl2.push_front(1);
			gl2.push_back(-1);
			Assert::IsFalse(gl1 != gl2, L"expect true");
		}
		TEST_METHOD(Test_canonique_form_copy)
		{
			//Test done in debug mode
			GlindingList<int> gl1;
			GlindingList<int> gl2(gl1);
			gl2.push_front(0);
			GlindingList<int> gl3(gl1);
			gl3.push_back(-1);


			Assert::IsFalse(gl1 == gl2);
			Assert::IsFalse(gl1 == gl3);
		}
	};

	TEST_CLASS(GlidingTest_with_max)
	{
	public:
		// [back/tail][.]...[.]...[center]...[.]...[.][front/head]
		TEST_METHOD(Test_push_back)
		{
			GlindingList<int> gl1(3);
			gl1.push_back(0);
			gl1.push_back(-1);
			gl1.push_back(-2);
			gl1.push_back(-3);
			//'        "
			//0,-1,-2,-3
			Assert::AreEqual(-3, gl1.at(0), L"at(0)");
			Assert::AreEqual(-1, gl1.at(-1), L"at(-1)");
			Assert::AreEqual(-2, gl1.at(-2), L"at(-2)");
			Assert::AreEqual(-3, gl1.at(-3), L"at(-3)");

		}
		TEST_METHOD(Test_push_front)
		{
			GlindingList<int> gl1(3);
			gl1.push_front(0);
			gl1.push_front(1);
			gl1.push_front(2);
			gl1.push_front(3);
			//"     '
			//0,1,2,3
			Assert::AreEqual(3, gl1.at(0), L"at(0)");
			Assert::AreEqual(1, gl1.at(1), L"at(1)");
			Assert::AreEqual(2, gl1.at(2), L"at(2)");
			Assert::AreEqual(3, gl1.at(3), L"at(3)");
		}
		TEST_METHOD(Test_push_front_back)
		{
			GlindingList<int> gl1(5);
			gl1.push_front(0);
			gl1.push_front(1);
			gl1.push_front(2);
			gl1.push_front(3);
			gl1.push_back(-1);
			gl1.push_back(-2);
			gl1.push_back(-3);
			//"     '
			//0,1,2,3
			Assert::AreEqual(0, gl1.at(0), L"at(0)");
			Assert::AreEqual(1, gl1.at(1), L"at(1)");
			Assert::AreEqual(2, gl1.at(2), L"at(2)");
			Assert::AreEqual(-3, gl1.at(3), L"at(3)");

			Assert::AreEqual(-1, gl1.at(-1), L"at(-1)");
			Assert::AreEqual(-2, gl1.at(-2), L"at(-2)");
			Assert::AreEqual(-3, gl1.at(-3), L"at(-3)");
		}
		TEST_METHOD(Test_operator_at)
		{
			// already tested
			GlindingList<int> gl1(5);
			gl1.push_front(0);
			gl1.push_front(1);
			gl1.push_front(2);
			gl1.push_front(3);
			gl1.push_back(-1);
			gl1.push_back(-2);
			gl1.push_back(-3);
			//"     '
			//0,1,2,3
			Assert::AreEqual(0, gl1[0], L"[0]");
			Assert::AreEqual(1, gl1[1], L"[1]");
			Assert::AreEqual(2, gl1[2], L"[2]");
			Assert::AreEqual(-3, gl1[3], L"[3]");

			Assert::AreEqual(-1, gl1[-1], L"[-1]");
			Assert::AreEqual(-2, gl1[-2], L"[-2]");
			Assert::AreEqual(-3, gl1[-3], L"[-3]");
		}
		TEST_METHOD(Test_equal) {
			GlindingList<int> gl1(2);
			GlindingList<int> gl2(2);
			Assert::IsTrue(gl1 == gl2, L"expect true");

			gl1.push_front(0);
			gl1.push_front(1);
			gl1.push_back(-1);
			Assert::IsFalse(gl1 == gl2, L"expect false");

			gl2.push_front(0);
			gl2.push_front(1);
			gl2.push_back(-1);
			Assert::IsTrue(gl1 == gl2, L"expect true");
		}
		TEST_METHOD(Test_not_equal) {
			GlindingList<int> gl1(2);
			GlindingList<int> gl2(2);
			Assert::IsFalse(gl1 != gl2, L"expect true");

			gl1.push_front(0);
			gl1.push_front(1);
			gl1.push_back(-1);
			Assert::IsTrue(gl1 != gl2, L"expect false");

			gl2.push_front(0);
			gl2.push_front(1);
			gl2.push_back(-1);
			Assert::IsFalse(gl1 != gl2, L"expect true");
		}
		TEST_METHOD(Test_canonique_form_copy)
		{
			//Test done in debug mode
			GlindingList<int> gl1(2);
			GlindingList<int> gl2(gl1);
			gl2.push_front(0);
			GlindingList<int> gl3(gl1);
			gl3.push_back(-1);


			Assert::IsFalse(gl1 == gl2);
			Assert::IsFalse(gl1 == gl3);
		}
	};

	TEST_CLASS(GlidingTest_iterator)
	{
		TEST_METHOD(Test_iterators_begin_back)
		{
			GlindingList<int> gl1;
			gl1.push_front(0);
			gl1.push_front(1);
			gl1.push_front(2);
			gl1.push_front(3);
			gl1.push_back(-1);
			gl1.push_back(-2);
			gl1.push_back(-3);

			auto it = gl1.front();
			Assert::AreEqual(3, *it, L"front()");
			it = gl1.back();
			Assert::AreEqual(-3, *it, L"back()");
		}

		TEST_METHOD(Test_iterators_increment_decrement) {
			GlindingList<int> gl1;
			gl1.push_front(0);
			gl1.push_front(1);
			gl1.push_front(2);
			gl1.push_front(3);
			gl1.push_back(-1);
			gl1.push_back(-2);
			gl1.push_back(-3);

			auto it = gl1.root()++;
			Assert::AreEqual(1, *it, L"front()");
			it = gl1.root()--;
			Assert::AreEqual(-1, *it, L"back()");

			it = ++gl1.root();
			Assert::AreEqual(1, *it, L"front()");
			it = --gl1.root();
			Assert::AreEqual(-1, *it, L"back()");
		}

		TEST_METHOD(Test_iterators_increment_decrement_n) {
			GlindingList<int> gl1;
			gl1.push_front(0);
			gl1.push_front(1);
			gl1.push_front(2);
			gl1.push_front(3);
			gl1.push_back(-1);
			gl1.push_back(-2);
			gl1.push_back(-3);

			auto it = gl1.root()+2;
			Assert::AreEqual(2, *it, L"front()");
			it = gl1.root()-2;
			Assert::AreEqual(-2, *it, L"back()");
		}

	};
}
