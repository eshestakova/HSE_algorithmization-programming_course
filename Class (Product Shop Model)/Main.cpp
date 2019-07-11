#include "Header.h"

int main() {
	MilkProduct Butter("Butter", 50, 0);
	Butter.print();

	MilkProduct SourCream("Sour cream", 100, 1);
	SourCream.print();

	WeightedProduct Sugar;
	Sugar.print();

	Fruit Bananas("Bananas", 135, 10, 15, 5);
	Bananas.print();

	Customer Matt("Matthew Khylma", 1000, 5);

	Bananas.Sell(Matt, 15);
	Bananas.Sell(Matt, 6);
	SourCream.Sell(Matt);
	Sugar.Sell(Matt, 1);

	return 0;
}