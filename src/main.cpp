#include <QtWidgets>

#include "widget/AppWidget.hpp"

int main(int argc, char *argv[]){
    QApplication app(argc, argv);
    LOG_INFO("Starting the application");

    AppWidget appWidget("/home");
    appWidget.show();

    LOG_INFO("The application was loaded");
    return app.exec();
}
