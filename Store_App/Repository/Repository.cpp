#include "Repository.h"
#include <ctime>
#include "Validator/exception_validator.h"

Repository::Repository() : coatsList(std::vector<TrenchCoat>()), shoppingCart(std::vector<TrenchCoat>())
{
	/*srand(time(NULL));
	std::vector<std::string> sizes = { "XS", "S", "M", "L", "XL" };
	std::vector<std::string> colours = { "Black", "Brown", "Beige", "Navy", "Grey", "White"};
	std::vector<float> prices = { 99.99f, 149.99f, 199.99f, 249.99f, 299.99f };
	for (int i = 0; i < 10; ++i) {
		std::string size = sizes[rand() % 5];
		std::string colour = colours[rand() % 6];
		float price = prices[rand() % 5];
		int quantity = rand() % 5;
		std::string photograph = "coat" + std::to_string(i + 1);
		TrenchCoat coat(size, colour, price, quantity, photograph);
		this->coatsList.push_back(coat);
	}*/

	loadFromFile("database.txt");
	loadCart("shopping_cart.txt");
}

Repository::~Repository()
{
	
}

void Repository::addCoatToCart(TrenchCoat coat)
{
	this->shoppingCart.push_back(coat);
	this->storeCart("shopping_cart.txt");
}

void Repository::addCoat(TrenchCoat new_coat)
{
	this->coatsList.push_back(new_coat);
	this->storeData("database.txt");
}

void Repository::deleteCoat(int pos)
{
	this->coatsList.erase(coatsList.begin() + pos);
	this->storeData("database.txt");
}

void Repository::updateSize(int pos, std::string new_size)
{
	this->coatsList.at(pos).setSize(new_size);
	this->storeData("database.txt");
}

void Repository::updateColour(int pos, std::string new_colour)
{
	this->coatsList.at(pos).setColour(new_colour);
	this->storeData("database.txt");
}

void Repository::updatePrice(int pos, float new_price)
{
	this->coatsList.at(pos).setPrice(new_price);
	this->storeData("database.txt");
}

void Repository::updateQuantity(int pos, int new_quantity)
{
	this->coatsList.at(pos).setQuantity(new_quantity);
	this->storeData("database.txt");
}

int Repository::getPos(std::string photo)
{
	int index = 0;
	for (const auto& coat : coatsList) {
		if (coat.getPhotograph() == photo)
			return index;
		index++;
	}
	return -1;
}

TrenchCoat Repository::getElemAt(int pos)
{
	return this->coatsList.at(pos);
}

std::vector<TrenchCoat> Repository::getList() {
	return this->coatsList;
}

std::vector<TrenchCoat>& Repository::getShoppingCart()
{
	return this->shoppingCart;
}

float Repository::getTotalPrice()
{
	float price = 0;
	for (const auto& coat : shoppingCart) {
		price += coat.getPrice();
	}
	return price;
}

void Repository::storeData(std::string filename)
{
	std::ofstream file(filename);
	if (!file.is_open())
		throw RepoException("The file could not be opened");
	for (const auto& coat : coatsList) {
		file << coat << "\n";
	}
	file.close();
}

void Repository::storeCart(std::string filename)
{
	std::ofstream file(filename);
	if (!file.is_open())
		throw RepoException("The file could not be opened");
	for (const auto& coat : shoppingCart) {
		file << coat << "\n";
	}
	file.close();
}

void Repository::loadFromFile(std::string filename)
{
	std::ifstream file(filename);
	if (!file.is_open())
		throw RepoException("The file could not be opened!");

	coatsList.clear();

	TrenchCoat coat;
	while (file >> coat) {
		coatsList.push_back(coat);
	}

	file.close();
}

void Repository::loadCart(std::string filename)
{
	std::ifstream file(filename);
	if (!file.is_open())
		throw RepoException("The file could not be opened!");

	shoppingCart.clear();

	TrenchCoat coat;
	while (file >> coat) {
		shoppingCart.push_back(coat);
	}

	file.close();
}

CSVRepository::CSVRepository() : Repository()
{
}

void CSVRepository::storeToFile(std::string filename)
{
	std::ofstream file(filename);
	if (!file.is_open()) {
		std::cerr << "Error: Unable to open file " << filename << " for writing." << std::endl;
		return;
	}

	file << "Size,Colour,Price,Photograph\n";

	for (const auto& coat : shoppingCart) {
		file << coat.getSize() << "," << coat.getColour() << "," << coat.getPrice() << "," << coat.getPhotograph() << "\n";
	}

	file.close();
}

HTMLRepository::HTMLRepository() : Repository()
{
}

void HTMLRepository::storeToFile(std::string filename)
{
	std::ofstream file(filename);
	if (!file.is_open()) {
		std::cerr << "Error: Unable to open file " << filename << " for writing." << std::endl;
		return;
	}

	file << "<html>\n<head>\n<title>Trench Coats</title>\n</head>\n<body>\n<table border=\"1\">\n";
	file << "<tr><th>Photo</th><th>Size</th><th>Colour</th><th>Price</th></tr>\n";

	for (const auto& coat : shoppingCart) {
		file << "<tr><td>" << coat.getPhotograph() << "</td><td>" << coat.getSize() << "</td><td>" << coat.getColour() << "</td><td>" << coat.getPrice() << "</td></tr>\n";
	}

	file << "</table>\n</body>\n</html>";

	file.close();
}
