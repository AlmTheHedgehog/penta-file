#include <QtWidgets>

#include "widget/EntriesWindow.hpp"
#include "widget/LineEntryWidget.hpp"
#include "widget/TopBarWidget.hpp"
#include "widget/MainFolderWidget.hpp"
#include "widget/FileManager.hpp"


int main(int argc, char *argv[]){
    QApplication app(argc, argv);
    LOG_INFO("Starting the application");

    /*
    EntriesWindow window;
    LineEntryWidget *line1 = new LineEntryWidget(LineEntryWidget::LineType::DIRECTORY, "My file1", 64);
    LineEntryWidget *line2 = new LineEntryWidget(LineEntryWidget::LineType::DIRECTORY, "My file2", 946);
    LineEntryWidget *line3 = new LineEntryWidget(LineEntryWidget::LineType::DIRECTORY, "My file3", 1024);
    LineEntryWidget *line4 = new LineEntryWidget(LineEntryWidget::LineType::DIRECTORY, "My file4", 842);
    LineEntryWidget *line5 = new LineEntryWidget(LineEntryWidget::LineType::DIRECTORY, "My file5", 64);
    LineEntryWidget *line6 = new LineEntryWidget(LineEntryWidget::LineType::DIRECTORY, "My file6", 845);
    LineEntryWidget *line7 = new LineEntryWidget(LineEntryWidget::LineType::DIRECTORY, "My file7", 55);
    LineEntryWidget *line8 = new LineEntryWidget(LineEntryWidget::LineType::DIRECTORY, "My file8", 8588);

    window.addNewEntry(line1);
    window.addNewEntry(line2);
    window.addNewEntry(line3);
    window.addNewEntry(line4);
    window.addNewEntry(line5);
    window.addNewEntry(line6);
    window.addNewEntry(line7);
    window.addNewEntry(line8);
    window.show();
    */

    // QWidget window;
    // QVBoxLayout *layout = new QVBoxLayout;
    // TopBarWidget topBar;
    // MainFolderWidget mainFolder;
    // layout->addWidget(&topBar);
    // layout->addWidget(&mainFolder);
    // layout->addStretch();
    
    // window.setLayout(layout);
    // window.show();
    
    //Loading the main widget

    FileManager window;
    window.show();

    LOG_INFO("The application was loaded");
    return app.exec();
}
