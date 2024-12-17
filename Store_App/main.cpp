#include "Ui/Ui.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QInputDialog>
#include <QtWidgets/QMessageBox>
#include "Validator/exception_validator.h"

int main(int argc, char* argv[]) {
	QApplication app(argc, argv);

	QString repoType = QInputDialog::getText(nullptr, "Repository Type", "Enter the type of repository (csv/html):");

	if (repoType != "csv" && repoType != "html") {
		QMessageBox::critical(nullptr, "Error", "Invalid repository type");
		return 1;
	}

	std::string repoTypeString = repoType.toStdString();

	Ui ui = Ui(repoTypeString, nullptr);
	ui.setWindowTitle("Trench Coat Store");
	ui.show();
	//ui.showListAdmin();
	
	return app.exec();
}