#pragma once
#include <Repository/Repository.h>
#include <Domain/Domain.h>
//design undo redo action for add, delete and update

class Action {
public:
    virtual void executeUndo() = 0;
    virtual void executeRedo() = 0;
};

class AddAction : public Action {
private:
    Repository& repo;
    TrenchCoat addedCoat;

public:
    AddAction(Repository& repo, const TrenchCoat& addedCoat) : repo{ repo }, addedCoat{ addedCoat } {}

    void executeUndo() override {
		repo.deleteCoat(repo.getPos(addedCoat.getPhotograph()));
	}

    void executeRedo() override {
		repo.addCoat(addedCoat);
	}
};

class DeleteAction : public Action {
private:
    Repository& repo;
	TrenchCoat deletedCoat;

public:
    DeleteAction(Repository& repo, const TrenchCoat& deletedCoat) : repo{ repo }, deletedCoat{ deletedCoat } {}

    void executeUndo() override {
		repo.addCoat(deletedCoat);
	}

    void executeRedo() override {
		repo.deleteCoat(repo.getPos(deletedCoat.getPhotograph()));
	}
};

class UpdateAction : public Action {
private:
    Repository& repo;
	TrenchCoat updatedCoat;
	TrenchCoat oldCoat;

public:
    UpdateAction(Repository& repo, const TrenchCoat& updatedCoat, const TrenchCoat& oldCoat) : repo{ repo }, updatedCoat{ updatedCoat }, oldCoat{ oldCoat } {}

    void executeUndo() override {
		repo.updateSize(repo.getPos(updatedCoat.getPhotograph()), oldCoat.getSize());
		repo.updateColour(repo.getPos(updatedCoat.getPhotograph()), oldCoat.getColour());
		repo.updatePrice(repo.getPos(updatedCoat.getPhotograph()), oldCoat.getPrice());
		repo.updateQuantity(repo.getPos(updatedCoat.getPhotograph()), oldCoat.getQuantity());
	}

	void executeRedo() override {
		repo.updateSize(repo.getPos(updatedCoat.getPhotograph()), updatedCoat.getSize());
		repo.updateColour(repo.getPos(updatedCoat.getPhotograph()), updatedCoat.getColour());
		repo.updatePrice(repo.getPos(updatedCoat.getPhotograph()), updatedCoat.getPrice());
		repo.updateQuantity(repo.getPos(updatedCoat.getPhotograph()), updatedCoat.getQuantity());
	}
};