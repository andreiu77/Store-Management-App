#include "Ui.h"
#include <iostream>
#include <regex>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QPushButton>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include "Validator/exception_validator.h"
#include <cstdlib>
#include <QMessageBox>
#include <QInputDialog>
#include <QShortcut>
#include <QKeySequence>
#include <Ui/cartWindow.h>


Ui::Ui(std::string repoType, QWidget* parent) : controller(Controller(repoType)), repoType(repoType), QWidget(parent)
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    this->resize(400, 300);
    QPushButton* adminModeButton = new QPushButton("Administrator Mode", this);
    QPushButton* userModeButton = new QPushButton("User Mode", this);
    adminModeButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    userModeButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    connect(adminModeButton, &QPushButton::clicked, this, &Ui::handleAdminMode);
    connect(userModeButton, &QPushButton::clicked, this, &Ui::handleUserMode);
    layout->addWidget(adminModeButton);
    layout->addWidget(userModeButton);

    setLayout(layout);
}

void Ui::handleAdminMode() {
    QDialog* adminWidget = new QDialog();
    adminWidget->setWindowTitle("Administrator Mode");
    adminWidget->resize(700, 300);

    QHBoxLayout* mainLayout = new QHBoxLayout();

    QVBoxLayout* layout = new QVBoxLayout();

    QLabel* label = new QLabel("Available commands:", adminWidget);
    label->setAlignment(Qt::AlignCenter);
    label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout->addWidget(label);

    QPushButton* showListButton = new QPushButton("Show table of trench coats");
    connect(showListButton, &QPushButton::clicked, this, &Ui::showListAdmin);
    layout->addWidget(showListButton);

    QPushButton* addButton = new QPushButton("Add a new trench coat", adminWidget);
    connect(addButton, &QPushButton::clicked, this, &Ui::addMenu);
    layout->addWidget(addButton);

    QPushButton* deleteButton = new QPushButton("Delete a trench coat", adminWidget);
    connect(deleteButton, &QPushButton::clicked, this, &Ui::deleteMenu);
    layout->addWidget(deleteButton);

    QPushButton* updateButton = new QPushButton("Update the information of a trench coat", adminWidget);
    connect(updateButton, &QPushButton::clicked, this, &Ui::updateMenu);
    layout->addWidget(updateButton);

    adminWidget->setLayout(mainLayout);
    mainLayout->addLayout(layout);
    QLabel* l = new QLabel();
    l->setText("List of trench coats");
    //display trench coats in a Qlist
    QListWidget* list = new QListWidget();
    std::vector<TrenchCoat> coats = controller.getList();
    for (const auto& coat : coats) {
        std::string price = std::to_string(coat.getPrice());
        price = price.substr(0, price.find('.') + 3);
		std::string item = coat.getSize() + " " + coat.getColour() + " " + price + " " + std::to_string(coat.getQuantity()) + " " + coat.getPhotograph();
		list->addItem(QString::fromStdString(item));
	}
    adminModeList = list;
    QVBoxLayout* listLayout = new QVBoxLayout();
    listLayout->addWidget(l);
    listLayout->addWidget(list);
    setFocusPolicy(Qt::StrongFocus);
    QPushButton* undoButton = new QPushButton("Undo");
    QPushButton* redoButton = new QPushButton("Redo");
    connect(undoButton, &QPushButton::clicked, this, &Ui::undo);
    connect(redoButton, &QPushButton::clicked, this, &Ui::redo);
    QShortcut* undoShortcut = new QShortcut(QKeySequence("Ctrl+Z"), adminWidget);
    QShortcut* redoShortcut = new QShortcut(QKeySequence("Ctrl+Y"), adminWidget);
    connect(undoShortcut, &QShortcut::activated, this, &Ui::undo);
    connect(redoShortcut, &QShortcut::activated, this, &Ui::redo);
    listLayout->addWidget(undoButton);
    listLayout->addWidget(redoButton);
    mainLayout->addLayout(listLayout);
    adminModeWidget = adminWidget;
    this->hide();
    adminWidget->exec();
    this->show();
}

void Ui::repopulate_list() 
{
    adminModeList->clear();
	std::vector<TrenchCoat> coats = controller.getList();
    for (const auto& coat : coats) {
        std::string price = std::to_string(coat.getPrice());
        price = price.substr(0, price.find('.') + 3);
		std::string item = coat.getSize() + " " + coat.getColour() + " " + price + " " + std::to_string(coat.getQuantity()) + " " + coat.getPhotograph();
		adminModeList->addItem(QString::fromStdString(item));
	}
}

void Ui::handleUserMode()
{
	QWidget* userWidget = new QWidget();
	userWidget->setWindowTitle("User Mode");
	userWidget->resize(400, 150);

	QVBoxLayout* layout = new QVBoxLayout(userWidget);

	QLabel* label = new QLabel("Available commands:", userWidget);
	layout->addWidget(label);

	QPushButton* showListButton = new QPushButton("Showcase coats of a specific size", userWidget);
	connect(showListButton, &QPushButton::clicked, this, &Ui::showListUser);
	layout->addWidget(showListButton);

	QPushButton* viewCartButton = new QPushButton("View shopping basket(html/csv)", userWidget);
    if(repoType == "html") connect(viewCartButton, &QPushButton::clicked, this, &Ui::openHTML);
	else connect(viewCartButton, &QPushButton::clicked, this, &Ui::openCSV);
	layout->addWidget(viewCartButton);

    QPushButton* viewCartButton2 = new QPushButton("View shopping basket in a table", userWidget);
    viewCartButton2->setStyleSheet("background-color: green");
    connect(viewCartButton2, &QPushButton::clicked, this, &Ui::showBasket);
    layout->addWidget(viewCartButton2);

	userWidget->setLayout(layout);
    this->userModeWidget = userWidget;
    this->close();
	userWidget->show();
}

void Ui::showBasket() {
    cartWindow* cart = new cartWindow(controller.getShoppingCart());

    QTableView* table = new QTableView();
    table->setModel(cart);
    table->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    table->show();
    
}

void Ui::undo()
{
    bool done = controller.undo();
    if (!done) QMessageBox::information(adminModeWidget, "Info", "No undos available");
    this->repopulate_list();
}

void Ui::redo()
{
    bool done = controller.redo();
    if (!done) QMessageBox::information(adminModeWidget, "Info", "No redos available");
    this->repopulate_list();
}

void Ui::showListAdmin()
{
    QDialog* showListWidget = new QDialog();
    showListWidget->setWindowTitle("List of trench coats");
    showListWidget->resize(800, 600);
    QVBoxLayout* layout = new QVBoxLayout(showListWidget);
    QTableWidget* table = new QTableWidget();
    table->setColumnCount(5);


    QStringList headers;
    headers << "Size" << "Colour" << "Price" << "Quantity" << "Photograph";
    table->setHorizontalHeaderLabels(headers);

    std::vector<TrenchCoat> list = controller.getList();
    table->setRowCount(list.size());
    for (int i = 0; i < list.size(); i++) {
        TrenchCoat coat = list.at(i);
        QTableWidgetItem* size = new QTableWidgetItem(QString::fromStdString(coat.getSize()));
        QTableWidgetItem* colour = new QTableWidgetItem(QString::fromStdString(coat.getColour()));
        QTableWidgetItem* price = new QTableWidgetItem(QString::number(coat.getPrice()));
        QTableWidgetItem* quantity = new QTableWidgetItem(QString::number(coat.getQuantity()));
        QTableWidgetItem* photograph = new QTableWidgetItem(QString::fromStdString(coat.getPhotograph()));

        table->setItem(i, 0, size);
        table->setItem(i, 1, colour);
        table->setItem(i, 2, price);
        table->setItem(i, 3, quantity);
        table->setItem(i, 4, photograph);
    }

    layout->addWidget(table);

    showListWidget->setLayout(layout);
    showListWidget->exec();
}

Ui::~Ui()
{
    
}



void Ui::showListUser()
{
    //prompt the user to choose a size and showcase all coats of that size one by one
    //when showcasing, 3 buttons: add to cart, next coat, previous coat, stop browsing
    QString size = QInputDialog::getText(nullptr, "Size", "Enter the size of the coats you want to see:");
    std::string sizeString = size.toStdString();
    std::vector<TrenchCoat> filteredList = controller.getListBySize(sizeString);
    if (filteredList.empty()){
        QMessageBox::critical(nullptr, "Error", "No coats of that size found");
        return;
    }
    QDialog* showcaseWidget = new QDialog();
    showcaseWidget->setWindowTitle("Showcase");
    showcaseWidget->resize(400, 300);

    QVBoxLayout* layout = new QVBoxLayout(showcaseWidget);

    QLabel* label = new QLabel("Showcasing coats of size " + size, showcaseWidget);
    layout->addWidget(label);

    QLabel* coatSize = new QLabel("", showcaseWidget);
    layout->addWidget(coatSize);

    QLabel* coatColour = new QLabel("", showcaseWidget);
    layout->addWidget(coatColour);

    QLabel* coatPrice = new QLabel("", showcaseWidget);
    layout->addWidget(coatPrice);

    QLabel* coatQuantity = new QLabel("", showcaseWidget);
    layout->addWidget(coatQuantity);

    QLabel* coatPhotograph = new QLabel("", showcaseWidget);
    layout->addWidget(coatPhotograph);

    size_t index = 0;
    TrenchCoat currentCoat = filteredList.at(index);
    std::string price = std::to_string(currentCoat.getPrice());
    price = price.substr(0, price.find('.') + 3);
    coatSize->setText(QString::fromStdString("Size: " + currentCoat.getSize()));
    coatColour->setText(QString::fromStdString("Colour: " + currentCoat.getColour()));
    coatPrice->setText(QString::fromStdString("Price: " + price));
    coatQuantity->setText(QString::fromStdString("Quantity: " + std::to_string(currentCoat.getQuantity())));
    coatPhotograph->setText(QString::fromStdString("Photograph: " + currentCoat.getPhotograph()));

    QPushButton* addButton = new QPushButton("Add to cart", showcaseWidget);
    layout->addWidget(addButton);

    QPushButton* nextButton = new QPushButton("Next coat", showcaseWidget);
    layout->addWidget(nextButton);

    QPushButton* previousButton = new QPushButton("Previous coat", showcaseWidget);
    layout->addWidget(previousButton);

    QPushButton* stopButton = new QPushButton("Stop browsing", showcaseWidget);
    layout->addWidget(stopButton);
    
    connect(addButton, &QPushButton::clicked, [this, &filteredList, &currentCoat, &index, showcaseWidget, coatSize, coatColour, coatPrice, coatQuantity, coatPhotograph]() {
        try {
			controller.addCoatToCart(currentCoat);
            filteredList.at(index).setQuantity(filteredList.at(index).getQuantity() - 1);
            currentCoat = filteredList.at(index);
            std::string price = std::to_string(currentCoat.getPrice());
            price = price.substr(0, price.find('.') + 3);
            coatSize->setText(QString::fromStdString("Size: " + currentCoat.getSize()));
            coatColour->setText(QString::fromStdString("Colour: " + currentCoat.getColour()));
            coatPrice->setText(QString::fromStdString("Price: " + price));
            coatQuantity->setText(QString::fromStdString("Quantity: " + std::to_string(currentCoat.getQuantity())));
            coatPhotograph->setText(QString::fromStdString("Photograph: " + currentCoat.getPhotograph()));
            if(repoType == "html") controller.storeToFile("shopping_cart.html");
            else controller.storeToFile("shopping_cart.csv");
			QMessageBox::information(showcaseWidget, "Success", "Coat added to cart successfully");
		}
        catch (const ValidationException& e) {
			QMessageBox::critical(showcaseWidget, "Error", e.what());
		}
	});
    
    connect(nextButton, &QPushButton::clicked, [this, &index, &currentCoat, &filteredList, coatSize, coatColour, coatPrice, coatQuantity, coatPhotograph]() {
        if (index == filteredList.size() - 1) {
			index = 0;
		}
        else {
			index++;
		}
		currentCoat = filteredList.at(index);
		std::string price = std::to_string(currentCoat.getPrice());
		price = price.substr(0, price.find('.') + 3);
        coatSize->setText(QString::fromStdString("Size: " + currentCoat.getSize()));
        coatColour->setText(QString::fromStdString("Colour: " + currentCoat.getColour()));
        coatPrice->setText(QString::fromStdString("Price: " + price));
        coatQuantity->setText(QString::fromStdString("Quantity: " + std::to_string(currentCoat.getQuantity())));
        coatPhotograph->setText(QString::fromStdString("Photograph: " + currentCoat.getPhotograph()));

	});

    connect(previousButton, &QPushButton::clicked, [this, &index, &currentCoat, &filteredList, coatSize, coatColour, coatPrice, coatQuantity, coatPhotograph]() {
        if (index == 0) {
			index = filteredList.size() - 1;
		}
        else {
			index--;
		}
		currentCoat = filteredList.at(index);
		std::string price = std::to_string(currentCoat.getPrice());
		price = price.substr(0, price.find('.') + 3);
		std::string item = currentCoat.getSize() + " " + currentCoat.getColour() + " " + price + " " + std::to_string(currentCoat.getQuantity()) + " " + currentCoat.getPhotograph();
        coatSize->setText(QString::fromStdString("Size: " + currentCoat.getSize()));
        coatColour->setText(QString::fromStdString("Colour: " + currentCoat.getColour()));
        coatPrice->setText(QString::fromStdString("Price: " + price));
        coatQuantity->setText(QString::fromStdString("Quantity: " + std::to_string(currentCoat.getQuantity())));
        coatPhotograph->setText(QString::fromStdString("Photograph: " + currentCoat.getPhotograph()));
	});

    connect(stopButton, &QPushButton::clicked, [showcaseWidget]() {
		showcaseWidget->close();
	});

	showcaseWidget->setLayout(layout);
	showcaseWidget->exec();
}

void Ui::addMenu()
{
    //adds a new coat to the list
    QDialog* addWidget = new QDialog();
    addWidget->setWindowTitle("Add a new trench coat");
    addWidget->resize(400, 300);

    QVBoxLayout* layout = new QVBoxLayout(addWidget);

    QLabel* sizeLabel = new QLabel("Size: ", addWidget);
    QLineEdit* sizeEdit = new QLineEdit(addWidget);
    layout->addWidget(sizeLabel);
    layout->addWidget(sizeEdit);

    QLabel* colourLabel = new QLabel("Colour: ", addWidget);
    QLineEdit* colourEdit = new QLineEdit(addWidget);
    layout->addWidget(colourLabel);
    layout->addWidget(colourEdit);

    QLabel* priceLabel = new QLabel("Price: ", addWidget);
    QLineEdit* priceEdit = new QLineEdit(addWidget);
    layout->addWidget(priceLabel);
    layout->addWidget(priceEdit);

    QLabel* quantityLabel = new QLabel("Quantity: ", addWidget);
    QLineEdit* quantityEdit = new QLineEdit(addWidget);
    layout->addWidget(quantityLabel);
    layout->addWidget(quantityEdit);

    QLabel* photographLabel = new QLabel("Photograph: ", addWidget);
    QLineEdit* photographEdit = new QLineEdit(addWidget);
    layout->addWidget(photographLabel);
    layout->addWidget(photographEdit);

    QPushButton* addButton = new QPushButton("Add", addWidget);
    addButton->setStyleSheet("background-color: green");
    layout->addWidget(addButton);
    connect(addButton, &QPushButton::clicked, [this, sizeEdit, colourEdit, priceEdit, quantityEdit, photographEdit, addWidget]() {
		std::string size = sizeEdit->text().toStdString();
		std::string colour = colourEdit->text().toStdString();
		std::string priceTemp = priceEdit->text().toStdString();
		std::string quantityTemp = quantityEdit->text().toStdString();
		std::string photograph = photographEdit->text().toStdString();
		float price;
		int quantity;
        try {
			Validator::validateNumbers(priceTemp);
			Validator::validateNumbers(quantityTemp);
            Validator::validateString(size);
            Validator::validateString(colour);
            Validator::validateString(photograph);
		}
        catch (const ValidationException& e) {
            QMessageBox::critical(addWidget, "Error", e.what());
			return;
		}
		price = std::stof(priceTemp);
		quantity = std::stoi(quantityTemp);
		TrenchCoat coat = TrenchCoat(size, colour, price, quantity, photograph);
        try {
            bool valid = controller.addCoat(coat);
            if (!valid) {
                QMessageBox::critical(addWidget, "Error", "A coat with that photograph already exists");
                addWidget->close();
            }
            else {
                QMessageBox::information(addWidget, "Success", "Coat added successfully");
                addWidget->close();
            }
        }
        catch (const RepoException& e) {
			QMessageBox::critical(addWidget, "Error", e.what());
			addWidget->close();
			return;
		}
        catch (const ValidationException& e) {
			QMessageBox::critical(addWidget, "Error", e.what());
			addWidget->close();
			return;
		}
	});

    addWidget->setLayout(layout);
    addWidget->exec();
    this->repopulate_list();
}

void Ui::deleteMenu()
{
    //deletes a coat from the list by photograph
    QDialog* deleteWidget = new QDialog();
    deleteWidget->setWindowTitle("Delete a trench coat");
    deleteWidget->resize(400, 100);

    QVBoxLayout* layout = new QVBoxLayout(deleteWidget);

    QLabel* photographLabel = new QLabel("Enter photo: ", deleteWidget);
    QLineEdit* photographEdit = new QLineEdit(deleteWidget);
    layout->addWidget(photographLabel);
    layout->addWidget(photographEdit);

    QPushButton* deleteButton = new QPushButton("Delete", deleteWidget);
    deleteButton->setStyleSheet("background-color: red");
    layout->addWidget(deleteButton);

    connect(deleteButton, &QPushButton::clicked, [this, photographEdit, deleteWidget]() {
		std::string photograph = photographEdit->text().toStdString();
        try {
			bool valid = controller.deleteCoat(photograph);
            if (!valid) {
				QMessageBox::critical(deleteWidget, "Error", "A coat with that photograph doesn't exist");
				deleteWidget->close();
			}
            else {
				QMessageBox::information(deleteWidget, "Success", "Coat deleted successfully");
				deleteWidget->close();
			}
		}
        catch (const RepoException& e) {
			QMessageBox::critical(deleteWidget, "Error", e.what());
			deleteWidget->close();
			return;
		}
        catch (const ValidationException& e) {
			QMessageBox::critical(deleteWidget, "Error", e.what());
			deleteWidget->close();
			return;
		}
	});

    deleteWidget->setLayout(layout);
	deleteWidget->exec();
	this->repopulate_list();
}

void Ui::updateMenu()
{
    //prompts the user to enter the photograph of the coat to be updated and the field to be updated
    //and the new value
    QDialog* updateWidget = new QDialog();
    updateWidget->setWindowTitle("Update a trench coat");
    updateWidget->resize(400, 100);

    QVBoxLayout* layout = new QVBoxLayout(updateWidget);

    QLabel* photographLabel = new QLabel("Enter photo: ", updateWidget);
    QLineEdit* photographEdit = new QLineEdit(updateWidget);
    layout->addWidget(photographLabel);
    layout->addWidget(photographEdit);

    //choose what to update through buttons
    QPushButton* sizeButton = new QPushButton("Update size", updateWidget);
    QPushButton* colourButton = new QPushButton("Update colour", updateWidget);
    QPushButton* priceButton = new QPushButton("Update price", updateWidget);
    QPushButton* quantityButton = new QPushButton("Update quantity", updateWidget);
    QHBoxLayout* buttonsLayout = new QHBoxLayout();
    buttonsLayout->addWidget(sizeButton);
    buttonsLayout->addWidget(colourButton);
    buttonsLayout->addWidget(priceButton);
    buttonsLayout->addWidget(quantityButton);
    layout->addLayout(buttonsLayout);

    //update size
    connect(sizeButton, &QPushButton::clicked, [this, photographEdit, updateWidget]() {
        QDialog* sizeWidget = new QDialog();
        sizeWidget->setWindowTitle("Update size");
        sizeWidget->resize(400, 100);

        QVBoxLayout* sizeLayout = new QVBoxLayout(sizeWidget);

        QLabel* sizeLabel = new QLabel("Enter new size: ", sizeWidget);
        QLineEdit* sizeEdit = new QLineEdit(sizeWidget);
        sizeLayout->addWidget(sizeLabel);
        sizeLayout->addWidget(sizeEdit);

        QPushButton* updateButton = new QPushButton("Update", sizeWidget);
        sizeLayout->addWidget(updateButton);

        connect(updateButton, &QPushButton::clicked, [this, photographEdit, sizeEdit, sizeWidget]() {
            std::string photograph = photographEdit->text().toStdString();
            std::string size = sizeEdit->text().toStdString();
            try {
                bool valid = controller.updateSize(photograph, size);
                if (!valid) {
                    QMessageBox::critical(sizeWidget, "Error", "A coat with that photograph doesn't exist");
                    sizeWidget->close();
                }
                else {
                    QMessageBox::information(sizeWidget, "Success", "Size updated successfully");
                    sizeWidget->close();
                }
            }
            catch (const RepoException& e) {
                QMessageBox::critical(sizeWidget, "Error", e.what());
                sizeWidget->close();
                return;
            }
            catch (const ValidationException& e) {
                QMessageBox::critical(sizeWidget, "Error", e.what());
                sizeWidget->close();
                return;
            }
            });

        sizeWidget->setLayout(sizeLayout);
        sizeWidget->exec();
        this->repopulate_list();
        });

    //update colour
    connect(colourButton, &QPushButton::clicked, [this, photographEdit, updateWidget]() {
        QDialog* colourWidget = new QDialog();
        colourWidget->setWindowTitle("Update colour");
        colourWidget->resize(400, 100);

        QVBoxLayout* colourLayout = new QVBoxLayout(colourWidget);

        QLabel* colourLabel = new QLabel("Enter new colour: ", colourWidget);
        QLineEdit* colourEdit = new QLineEdit(colourWidget);
        colourLayout->addWidget(colourLabel);
        colourLayout->addWidget(colourEdit);

        QPushButton* updateButton = new QPushButton("Update", colourWidget);
        colourLayout->addWidget(updateButton);

        connect(updateButton, &QPushButton::clicked, [this, photographEdit, colourEdit, colourWidget]() {
            std::string photograph = photographEdit->text().toStdString();
            std::string colour = colourEdit->text().toStdString();
            try {
                bool valid = controller.updateColour(photograph, colour);
                if (!valid) {
                    QMessageBox::critical(colourWidget, "Error", "A coat with that photograph doesn't exist");
                    colourWidget->close();
                }
                else {
                    QMessageBox::information(colourWidget, "Success", "Colour updated successfully");
                    colourWidget->close();
                }
            }
            catch (const RepoException& e) {
                QMessageBox::critical(colourWidget, "Error", e.what());
                colourWidget->close();
                return;
            }
            catch (const ValidationException& e) {
                QMessageBox::critical(colourWidget, "Error", e.what());
                colourWidget->close();
                return;
            }
            });

        colourWidget->setLayout(colourLayout);
        colourWidget->exec();
        this->repopulate_list();
        });

    //update price
    connect(priceButton, &QPushButton::clicked, [this, photographEdit, updateWidget]() {
        QDialog* priceWidget = new QDialog();
        priceWidget->setWindowTitle("Update price");
        priceWidget->resize(400, 100);

        QVBoxLayout* priceLayout = new QVBoxLayout(priceWidget);

        QLabel* priceLabel = new QLabel("Enter new price: ", priceWidget);
        QLineEdit* priceEdit = new QLineEdit(priceWidget);
        priceLayout->addWidget(priceLabel);
        priceLayout->addWidget(priceEdit);

        QPushButton* updateButton = new QPushButton("Update", priceWidget);
        priceLayout->addWidget(updateButton);

        connect(updateButton, &QPushButton::clicked, [this, photographEdit, priceEdit, priceWidget]() {
            std::string photograph = photographEdit->text().toStdString();
            std::string priceTemp = priceEdit->text().toStdString();
            float price;
            try {
                Validator::validateNumbers(priceTemp);
                price = std::stof(priceTemp);
                bool valid = controller.updatePrice(photograph, price);
                if (!valid) {
                    QMessageBox::critical(priceWidget, "Error", "A coat with that photograph doesn't exist");
                    priceWidget->close();
                }
                else {
                    QMessageBox::information(priceWidget, "Success", "Price updated successfully");
                    priceWidget->close();
                }
            }
            catch (const RepoException& e) {
                QMessageBox::critical(priceWidget, "Error", e.what());
                priceWidget->close();
                return;
            }
            catch (const ValidationException& e) {
                QMessageBox::critical(priceWidget, "Error", e.what());
                priceWidget->close();
                return;
            }
            });

        priceWidget->setLayout(priceLayout);
        priceWidget->exec();
        this->repopulate_list();
        });

    //update quantity
    connect(quantityButton, &QPushButton::clicked, [this, photographEdit, updateWidget]() {
        QDialog* quantityWidget = new QDialog();
        quantityWidget->setWindowTitle("Update quantity");
        quantityWidget->resize(400, 100);

        QVBoxLayout* quantityLayout = new QVBoxLayout(quantityWidget);

        QLabel* quantityLabel = new QLabel("Enter new quantity: ", quantityWidget);
        QLineEdit* quantityEdit = new QLineEdit(quantityWidget);
        quantityLayout->addWidget(quantityLabel);
        quantityLayout->addWidget(quantityEdit);

        QPushButton* updateButton = new QPushButton("Update", quantityWidget);
        quantityLayout->addWidget(updateButton);

        connect(updateButton, &QPushButton::clicked, [this, photographEdit, quantityEdit, quantityWidget]() {
            std::string photograph = photographEdit->text().toStdString();
            std::string quantityTemp = quantityEdit->text().toStdString();
            int quantity;
            try {
                Validator::validateNumbers(quantityTemp);
                quantity = std::stoi(quantityTemp);
                bool valid = controller.updateQuantity(photograph, quantity);
                if (!valid) {
                    QMessageBox::critical(quantityWidget, "Error", "A coat with that photograph doesn't exist");
                    quantityWidget->close();
                }
                else {
                    QMessageBox::information(quantityWidget, "Success", "Quantity updated successfully");
                    quantityWidget->close();
                }
            }
            catch (const RepoException& e) {
                QMessageBox::critical(quantityWidget, "Error", e.what());
                quantityWidget->close();
                return;
            }
            catch (const ValidationException& e) {
                QMessageBox::critical(quantityWidget, "Error", e.what());
                quantityWidget->close();
                return;
            }
            });
        quantityWidget->setLayout(quantityLayout);
        quantityWidget->exec();
        this->repopulate_list();
        });
    updateWidget->setLayout(layout);
    updateWidget->exec();
    this->repopulate_list();
}



void Ui::openHTML()
{
    std::string filename("C:\\Users\\Andrei\\Desktop\\lab8-9 oop\\shopping_cart.html");
    controller.storeToFile(filename);
    std::cout << "Opening HTML file: " << filename << std::endl;
    std::string command = "start chrome \"" + filename + "\"";
    system(command.c_str());
}

void Ui::openCSV()
{
	std::string filename("C:\\Users\\Andrei\\Desktop\\lab8-9 oop\\shopping_cart.csv");
    controller.storeToFile(filename);
	std::cout << "Opening CSV file: " << filename << std::endl;
	std::string command = "start excel \"" + filename + "\"";
	system(command.c_str());
}
