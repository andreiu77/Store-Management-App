#pragma once
#include "Domain/Domain.h"
#include <vector>
#include <fstream>

class Repository {
protected:
	std::vector<TrenchCoat> coatsList;
	std::vector<TrenchCoat> shoppingCart;	

public:
	//Constructs a Repository object with randomly generated initial data
	Repository();

	//Destructor for Repository object
	~Repository();

	void addCoatToCart(TrenchCoat coat);

	//Adds a new trench coat to the repository
	//@param new_coat The trench coat to be added
	void addCoat(TrenchCoat new_coat);

	//Deletes a trench coat from the repository at the specified position
	//@param pos The position of the trench coat to be deleted
	void deleteCoat(int pos);

	//Updates the size of a trench coat in the repository
	//@param pos The position of the trench coat whose size is to be updated
	//@param new_size The new size to be updated
	void updateSize(int pos, std::string new_size);

	//Updates the colour of a trench coat in the repository
	void updateColour(int pos, std::string new_colour);

	//Updates the price of a trench coat in the repository
	void updatePrice(int pos, float new_price);

	//Updates the quantity of a trench coat in the repository
	void updateQuantity(int pos, int new_quantity);

	//Gets the position of a trench coat in the repository based on its photo
	int getPos(std::string photo);

	//Retrieves the trench coat at the specified position in the repository
	TrenchCoat getElemAt(int pos);

	//Gets a copy of the list of all trench coats in the repository
	std::vector<TrenchCoat> getList();

	std::vector<TrenchCoat>& getShoppingCart();
	
	float getTotalPrice();

	void storeData(std::string filename);

	void storeCart(std::string filename);

	virtual void storeToFile(std::string filename) = 0;

	void loadFromFile(std::string filename);

	void loadCart(std::string filename);
};

class CSVRepository : public Repository {
public:
	CSVRepository();
	void storeToFile(std::string filename) override;

};

class HTMLRepository : public Repository {
public:
	HTMLRepository();
	void storeToFile(std::string filename) override;
};