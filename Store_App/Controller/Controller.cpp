#include "Controller.h"
#include <algorithm>
#include <iterator>
#include "Validator/exception_validator.h"

Controller::Controller(std::string repoType)
{
	if (repoType == "csv") {
		this->repository = new CSVRepository();
	}
	else if (repoType == "html") {
		this->repository = new HTMLRepository();
	}
	else {
		throw RepoException("Invalid repository type");
		exit(1);
	}
}

Controller::~Controller()
{
	
}

void Controller::addCoatToCart(TrenchCoat coat)
{
	Validator::validateQuantity(coat.getQuantity());
	repository->updateQuantity(repository->getPos(coat.getPhotograph()), coat.getQuantity() - 1);
	repository->addCoatToCart(coat);
}

bool Controller::undo()
{
	if(this->undoActions.empty())
		return false;
	this->undoActions.back()->executeUndo();
	this->redoActions.push_back(std::move(this->undoActions.back()));
	this->undoActions.pop_back();
	return true;
}

bool Controller::redo()
{
	if(this->redoActions.empty())
		return false;
	this->redoActions.back()->executeRedo();
	this->undoActions.push_back(std::move(this->redoActions.back()));
	this->redoActions.pop_back();
	return true;
}

bool Controller::addCoat(TrenchCoat coat)
{
	Validator::validateEntityInexistence(coat, *this->repository);
	repository->addCoat(coat);
	this->undoActions.push_back(std::make_unique<AddAction>(*repository, coat));
	this->redoActions.clear();
	return true;
}

bool Controller::deleteCoat(std::string photo)
{
	Validator::validateEntityExistence(photo, *this->repository);
	this->undoActions.push_back(std::make_unique<DeleteAction>(*repository, repository->getElemAt(repository->getPos(photo))));
	repository->deleteCoat(repository->getPos(photo));
	this->redoActions.clear();
	return true;
}

bool Controller::updateSize(std::string photo, std::string new_size)
{
	Validator::validateEntityExistence(photo, *this->repository);
	int pos = repository->getPos(photo);
	TrenchCoat oldCoat = repository->getElemAt(pos);
	repository->updateSize(pos, new_size);
	this->undoActions.push_back(std::make_unique<UpdateAction>(*repository, repository->getElemAt(pos), oldCoat));
	this->redoActions.clear();
	return true;
}

bool Controller::updateColour(std::string photo, std::string new_colour)
{
	Validator::validateEntityExistence(photo, *this->repository);
	int pos = repository->getPos(photo);
	TrenchCoat oldCoat = repository->getElemAt(pos);
	repository->updateColour(pos, new_colour);
	this->undoActions.push_back(std::make_unique<UpdateAction>(*repository, repository->getElemAt(pos), oldCoat));
	this->redoActions.clear();
	return true;
}

bool Controller::updatePrice(std::string photo, float new_price)
{
	Validator::validateEntityExistence(photo, *this->repository);
	int pos = repository->getPos(photo);
	TrenchCoat oldCoat = repository->getElemAt(pos);
	repository->updatePrice(pos, new_price);
	this->undoActions.push_back(std::make_unique<UpdateAction>(*repository, repository->getElemAt(pos), oldCoat));
	this->redoActions.clear();
	return true;
}

bool Controller::updateQuantity(std::string photo, int new_quantity)
{
	Validator::validateEntityExistence(photo, *this->repository);
	int pos = repository->getPos(photo);
	TrenchCoat oldCoat = repository->getElemAt(pos);
	repository->updateQuantity(pos, new_quantity);
	this->undoActions.push_back(std::make_unique<UpdateAction>(*repository, repository->getElemAt(pos), oldCoat));
	this->redoActions.clear();
	return true;
}

std::vector<TrenchCoat> Controller::getList() {
	return this->repository->getList();
}

std::vector<TrenchCoat>& Controller::getShoppingCart()
{
	return this->repository->getShoppingCart();
}

float Controller::getTotalPrice()
{
	return this->repository->getTotalPrice();
}

std::vector<TrenchCoat> Controller::getListBySize(std::string size)
{
	std::vector<TrenchCoat> originalList = repository->getList();
	std::vector<TrenchCoat> list;

	std::copy_if(originalList.begin(), originalList.end(), std::back_inserter(list),
		[&size](const TrenchCoat& coat) {
			return coat.getSize() == size || size.empty();
		});

	return list;
}

void Controller::storeToFile(std::string filename)
{
	this->repository->storeToFile(filename);
}

void Controller::storeData(std::string filename)
{
	this->repository->storeData(filename);
}

void Controller::storeCart(std::string filename)
{
	this->repository->storeCart(filename);
}

void Controller::loadCart(std::string filename)
{
	this->repository->loadCart(filename);
}
