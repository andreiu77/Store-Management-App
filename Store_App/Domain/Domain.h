#pragma once
#include <string>
class TrenchCoat {
private:
	std::string size;
	std::string colour;
	float price;
	int quantity;
	std::string photograph;

public:
	TrenchCoat();
	TrenchCoat(std::string size, std::string colour, float price, int quantity, std::string photograph);
	//getters
	std::string getSize() const;
	std::string getColour() const;
	float getPrice() const;
	int getQuantity() const;
	std::string getPhotograph() const;
	//setters
	void setSize(std::string new_size);
	void setColour(std::string new_colour);
	void setPrice(float new_price);
	void setQuantity(int new_quantity);
	
	friend std::ostream& operator<<(std::ostream& os, const TrenchCoat& coat);
	friend std::istream& operator>>(std::istream& is, TrenchCoat& coat);
};