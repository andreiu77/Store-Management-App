#pragma once
#include "Repository/Repository.h"
#include "Repository/Action.h"

class Controller {
private:
	Repository* repository;
	std::vector<std::unique_ptr<Action>> undoActions;
	std::vector<std::unique_ptr<Action>> redoActions;
	
public:
	/*Constructs a Controller object*/
	Controller(std::string repoType);

	/*Destructor for Controller object*/
	~Controller();

	void addCoatToCart(TrenchCoat coat);

	//return True if undo/redo was successful, false otherwise
	bool undo();
	bool redo();

	/*Adds a new trench coat to the repository
	* @param size The size of the trench coat
	* @param colour The colour of the trench coat
	* @param price The price of the trench coat
	* @param quantity The quantity of the trench coat
	* @param photo The photo of the trench coat
	* @return true if the trench coat is added successfully, false otherwise*/
	bool addCoat(TrenchCoat);
	
	/*Deletes a trench coat from the repository
	* @param photo The photo of the trench coat to be deleted
	* @return True if the trench coat is deleted successfully, false otherwise*/
	bool deleteCoat(std::string photo);
	
	/*Updates the size of a trench coat in the repository
	* @param photo The photo of the trench coat whose size is to be updated
	* @param new_size The new size to be updated
	* @return True if the size is updated successfully, false otherwise*/
	bool updateSize(std::string photo, std::string new_size);

	/*Updates the colour of a trench coat in the repository
	* @param photo The photo of the trench coat whose colour is to be updated
	* @param new_colour The new colour to be updated
	* @return True if the colour is updated successfully, false otherwise*/
	bool updateColour(std::string photo, std::string new_colour);
	
	/*Updates the quantity of a trench coat in the repository
	* @param photo The photo of the trench coat whose quantity is to be updated
	* @param new_quantity The new quantity to be updated
	* @return True if the quantity is updated successfully, false otherwise*/
	bool updatePrice(std::string photo, float new_price);
	
	/*Updates the quantity of a trench coat in the repository
	* @param photo The photo of the trench coat whose quantity is to be updated
	* @param new_quantity The new quantity to be updated
	* @return True if the quantity is updated successfully, false otherwise*/
	bool updateQuantity(std::string photo, int quantity);
	
	//Gets the list of all trench coats in the repository
	//* @return A DynamicArray of TrenchCoat objects representing the list of all trench coats
	std::vector<TrenchCoat> getList();;

	std::vector<TrenchCoat>& getShoppingCart();

	float getTotalPrice();

	//Gets the list of trench coats filtered by size
	//* @param size The size by which to filter the list of trench coats.If empty, returns all trench coats
	//* @return A DynamicArray of TrenchCoat objects representing the filtered list of trench coats
	std::vector<TrenchCoat> getListBySize(std::string size);

	void storeToFile(std::string filename);

	void storeData(std::string filename);

	void storeCart(std::string filename);

	void loadCart(std::string filename);

	//void sortBySizeAndColor(DynamicArray<TrenchCoat>& list);
};