#include <QtWidgets>
#include "widget/LineEntryWidget.hpp"

int main(int argc, char *argv[]){
    QApplication app(argc, argv);
    LOG_INFO("Starting the application");

    //Loading the main widget

    LOG_INFO("The application was loaded");
    return app.exec();
}
