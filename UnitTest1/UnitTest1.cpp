#include "pch.h"
#include "CppUnitTest.h"
#include "../SpareroomTestApp/SpareroomTestApp.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestBothDiscounts)
		{
			array<Product, 4> Basket = { Product('A', 3), Product('B', 2), Product('C', 1), Product('D', 1), };
			int total = 0;
			for (unsigned int i = 0; i < Basket.size(); i++) {
				total += Basket[i].GetPrice();
			};

			Assert::AreEqual(total, 237);
		}

		TEST_METHOD(TestExcessDiscounts)
		{
			array<Product, 4> Basket = { Product('A', 5), Product('B', 4), Product('C', 1), Product('D', 1), };
			int total = 0;
			for (unsigned int i = 0; i < Basket.size(); i++) {
				total += Basket[i].GetPrice();
			};

			Assert::AreEqual(total, 397);
		}

		TEST_METHOD(TestMultipleDiscounts)
		{
			array<Product, 4> Basket = { Product('A', 12), Product('B', 8), Product('C', 0), Product('D', 0), };
			int total = 0;
			for (unsigned int i = 0; i < Basket.size(); i++) {
				total += Basket[i].GetPrice();
			};

			Assert::AreEqual(total, 800);
		}

		TEST_METHOD(TestJSON)
		{
			array<Product, 4> Basket = { Product('A', 0), Product('B', 0), Product('C', 0), Product('D', 0), };
			int i = 0;
			auto j = json::parse("[{\"code\":\"A\",\"quantity\":0},{\"code\":\"B\",\"quantity\":0},{\"code\":\"C\",\"quantity\":1},{\"code\":\"D\",\"quantity\":2}]");
			for (json::iterator it = j.begin(); it != j.end(); ++it) { 
				json p = *it;
				Basket[i] = (Product(p["code"].get<string>().front(), p["quantity"].get<unsigned int>()));
				i++;
			}
			int total = 0;
			for (unsigned int i = 0; i < Basket.size(); i++) {
				total += Basket[i].GetPrice();
			};

			Assert::AreEqual(total, 49);
		}
	};
}
