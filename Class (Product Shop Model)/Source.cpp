#include "Header.h"
#include <iostream>

Customer::Customer(const char* name, int cash = 1000, int sale = 0) {
	this->cash = cash;
	this->name = name;
	salescard = sale;
}

Customer::~Customer() {
	delete name;
}

int Customer::get_sale() { return salescard; }
const char* Customer::get_name() { return name; }

Product::Product() {
	name = "bubblegum";
	price = 1;
}

Product::Product(char* name, int price) {
	this->name = name;
	this->price = price;
}

Product::~Product() {
	delete name;
}

int Product::get_price() { return price; }
const char* Product::get_name() { return name; }

void Product::Sell(Customer& C) {
	int cost = price * (100 - C.get_sale()) / 100;
	if (cost > C.cash) std::cout << "\nSorry, " << C.get_name() << " can not afford " << this->name << "\n\n";
	else {
		C.cash -= cost;
		std::cout << "\n" << C.get_name() << " bought " << name << ", " << C.cash << "$ left\n\n";
	}
}

void Product::print() {
	std::cout << "Product " << name << ":\nprice - " << price << "\n\n";
}

MilkProduct::MilkProduct() {
	name = "Milk";
	price = 100;
	expiration = 0;
}

MilkProduct::MilkProduct(const char* n, int pr, int exp) {
	name = n;
	price = pr;
	expiration = exp;
}

void MilkProduct::Sell(Customer& C) {
	if (expiration == 1) std::cout << "\nSorry, " << name << " has expired\n";
	else {
		int cost = price * (100 - C.get_sale()) / 100;
		if (cost > C.cash) std::cout << "\nSorry, " << C.get_name() << " can not afford " << this->name << "\n\n";
		else {
			C.cash -= cost;
			std::cout << "\n" << C.get_name() << " bought " << name << ", " << C.cash << "$ left\n\n";
		}
	}
}

void MilkProduct::print() {
	std::cout << "Milk product " << name << ":\nprice - " << price << "\n";
	if (expiration == 1) std::cout << "expired\n\n";
	else std::cout << "not expired\n\n";
}

WeightedProduct::WeightedProduct() {
	name = "sugar";
	price = 20;
	mass = 1;
}

WeightedProduct::WeightedProduct(const char* n, int pr, int m) {
	name = n;
	price = pr;
	mass = m;
}

void WeightedProduct::Sell(Customer& C, int m) {
	if (m > mass) std::cout << "\nSorry, there is only " << mass << "kg of " << name << "\n\n";
	else {
		int cost = m * price * (100 - C.get_sale()) / 100;
		if (cost > C.cash) std::cout << "\nSorry, " << C.get_name() << " can not afford " << m << "kg of " << name << "\n\n";
		else {
			C.cash -= cost;
			mass -= m;
			std::cout << "\n" << C.get_name() << " bought " << m << "kg of " << name << ", " << C.cash << "$ left\n";
		}
	}
}

void WeightedProduct::print() {
	std::cout << "Weighted product " << name << ":\nprice - " << price << "\nmass - " << mass << "\n\n";
}

Fruit::Fruit() {
	name = "apples";
	price = 20;
	mass = 5;
	sale = 0;
	sale_from = 0;
}

Fruit::Fruit(const char* n, int pr, int m, int s, int s_f) {
	name = n;
	price = pr;
	mass = m;
	sale = s;
	sale_from = s_f;
}

void Fruit::Sell(Customer& C, int m) {
	if (m > mass) std::cout << "\nSorry, there is only " << mass << "kg of " << name << "\n\n";
	else {
		int cost = m * price * (100 - C.get_sale()) / 100;
		if (m >= sale_from) {
			cost = cost * (100 - sale) / 100;
			std::cout << C.get_name() << " got a sale " << sale << "%, because he has bought >" << sale_from << "kg of " << name;
		}
		if (cost > C.cash) std::cout << "\nSorry, " << C.get_name() << " can not afford " << m << "kg of " << name << "\n\n";
		else {
			C.cash -= cost;
			mass -= m;
			std::cout << "\n" << C.get_name() << " bought " << m << "kg of " << name << ", " << C.cash << "$ left\n";
		}
	}
}
