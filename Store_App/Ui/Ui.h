#pragma once
#include "Controller/Controller.h"
#include <QtWidgets/QWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QListWidget>
class Ui : public QWidget {
private:
	Controller controller;
	std::string repoType;
	QPushButton* adminModeButton;
	QDialog* adminModeWidget;
	QListWidget* adminModeList;
	QWidget* userModeWidget;

private slots:
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