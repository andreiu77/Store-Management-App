#include "Domain.h"
#include <iostream>

TrenchCoat::TrenchCoat()
{
}

TrenchCoat::TrenchCoat(std::string size, std::string colour, float price, int quantity, std::string photograph)
{
	this->size = size;
	this->colour = colour;
	this->price = price;
	this->quantity = quantity;
	this->photograph = photograph;
}

std::string TrenchCoat::getSize() const
{
	return this->size;
}

std::string TrenchCoat::getColour() const
{
	return this->colour;
}

float TrenchCoat::getPrice() const
{
	return this->price;
}

int TrenchCoat::getQuantity() const
{
	return this->quantity;
}

std::string TrenchCoat::getPhotograph() const
{
	return this->photograph;
}

void TrenchCoat::setSize(std::string new_size)
{
	this->size = new_size;
}

void TrenchCoat::setColour(std::string new_colour)
{
	this->colour = new_colour;
}

void TrenchCoat::setPrice(float new_price)
{
	this->price = new_price;
}

void TrenchCoat::setQuantity(int new_quantity)
{
	this->quantity = new_quantity;
}

std::ostream& operator<<(std::ostream& os, const TrenchCoat& coat) {
	os << coat.getSize() << " " << coat.getColour() << " " << coat.getPrice() << " " << coat.getQuantity() << " " << coat.getPhotograph();
	return os;
}

std::istream& operator>>(std::istream& is, TrenchCoat& coat)
{
	if (is.rdbuf() == std::cin.rdbuf()) std::cout << "Enter size: ";
	std::string size;
	is >> size;

	if (is.rdbuf() == std::cin.rdbuf()) std::cout << "Enter colour: ";
	std::string colour;
	is >> colour;

	if (is.rdbuf() == std::cin.rdbuf()) std::cout << "Enter price: ";
	float price;
	is >> price;

	if (is.rdbuf() == std::cin.rdbuf()) std::cout << "Enter quantity: ";
	int quantity;
	is >> quantity;

	if (is.rdbuf() == std::cin.rdbuf()) std::cout << "Enter photograph: ";
	std::string photograph;
	is >> photograph;
	coat.setSize(size);
	coat.setColour(colour);
	coat.setPrice(price);
	coat.setQuantity(quantity);
	coat.photograph = photograph;
	return is;
}
