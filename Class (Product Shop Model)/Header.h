#pragma once

class Customer {
protected:
	int salescard;
	const char* name;

public:
	int cash;

	Customer(const char* name, int cash, int sale);
	~Customer();

	int get_sale();
	const char* get_name();
};

class Product {
protected:
	const char* name;
	int price;

public:
	Product();
	Product(char* name, int price);
	~Product();

	virtual void Sell(Customer& C);
	virtual void print();

	int get_price();
	const char* get_name();
};

class MilkProduct : public Product {
protected:
	int expiration;
public:
	MilkProduct();
	MilkProduct(const char* n, int pr, int exp);

	virtual void Sell(Customer& C) override;
	void print() override;
};

class WeightedProduct : public Product {
protected:
	int mass;
public:
	WeightedProduct();
	WeightedProduct(const char* n, int pr, int m);

	virtual void Sell(Customer& C, int m);
	void print() override;
};

class Fruit : public WeightedProduct {
	int sale;
	int sale_from;
public:
	Fruit();
	Fruit(const char* n, int pr, int m, int s, int s_f);

	void Sell(Customer& C, int m) override;
};