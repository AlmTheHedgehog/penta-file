#include <QtWidgets>
#include "widget/LineEntryWidget.hpp"
#include "widget/TopBarWidget.hpp"

int main(int argc, char *argv[]){
    QApplication app(argc, argv);
    LOG_INFO("Starting the application");


    // LineEntryWidget line(LineEntryWidget::LineType::DIRECTORY, "test", 64);
    // line.show();
    TopBarWidget topBar;
    topBar.show();
    //Loading the main widget

    LOG_INFO("The application was loaded");
    return app.exec();
}
