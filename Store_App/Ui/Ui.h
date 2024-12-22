#pragma once
#include "Controller/Controller.h"
#include <QtWidgets/QWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QListWidget>
#include <Encryption/Encryption.h>

class Ui : public QWidget {
private:
	Controller controller;
	std::string repoType;
	QPushButton* adminModeButton;
	QDialog* adminModeWidget;
	QListWidget* adminModeList;
	QWidget* userModeWidget;
	std::string adminPassword = "admin";

private slots:
	void adminLogin();
	void registerNewAdmin();
	void handleAdminMode();
	void repopulate_list();
	void handleUserMode();
	void showListAdmin();
	void addMenu();
	void deleteMenu();
	void showListUser();
	void updateMenu();
	void openHTML();
	void openCSV();
	void showBasket();
	void undo();
	void redo();

public:
	Ui(std::string repoType, QWidget* parent);
	~Ui();
};