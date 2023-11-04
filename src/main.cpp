#include <QtWidgets>

#include "widget/EntriesWindow.hpp"
#include "widget/TopBarWidget.hpp"
#include "widget/MainFolderWidget.hpp"


int main(int argc, char *argv[]){
    QApplication app(argc, argv);
    LOG_INFO("Starting the application");

    EntriesWindow entriesWindow("/home/almthehedgehog");

    QWidget window;
    QVBoxLayout *layout = new QVBoxLayout;
    TopBarWidget topBar;
    MainFolderWidget mainFolder;
    layout->addWidget(&topBar);
    layout->addWidget(&mainFolder);
    layout->addWidget(&entriesWindow);
    layout->addStretch();
    
    window.setLayout(layout);
    window.show();

    LOG_INFO("The application was loaded");
    return app.exec();
}
