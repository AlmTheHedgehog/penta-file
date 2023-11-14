#include "widget/FileManager.hpp"

FileManager::FileManager(QWidget*parent) :
    QWidget(parent){

    connect(topBarWidget, &TopBarWidget::searchPath, this, &FileManager::updateTopBarPath);

    
    setWindowTitle("File Manager");
    setMinimumSize(800, 600);
    setMaximumSize(800, 600);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    setLayout(new QVBoxLayout(this));
    QVBoxLayout *topLayout = new QVBoxLayout;
    topLayout->setContentsMargins(0, 0, 0, 0);

    mainFolderWidget = new MainFolderWidget(this);
    topBarWidget = new TopBarWidget(this);

    topLayout->addWidget(topBarWidget);
    topLayout->addWidget(mainFolderWidget);
    
    
      
    EntriesWindow *window = new EntriesWindow;
    LineEntryWidget *line1 = new LineEntryWidget(LineEntryWidget::LineType::DIRECTORY, "My file1", 64);
    LineEntryWidget *line2 = new LineEntryWidget(LineEntryWidget::LineType::DIRECTORY, "My file2", 946);
    LineEntryWidget *line3 = new LineEntryWidget(LineEntryWidget::LineType::DIRECTORY, "My file3", 1024);
    LineEntryWidget *line4 = new LineEntryWidget(LineEntryWidget::LineType::DIRECTORY, "My file4", 842);
    LineEntryWidget *line5 = new LineEntryWidget(LineEntryWidget::LineType::DIRECTORY, "My file5", 64);
    LineEntryWidget *line6 = new LineEntryWidget(LineEntryWidget::LineType::DIRECTORY, "My file6", 845);
    LineEntryWidget *line7 = new LineEntryWidget(LineEntryWidget::LineType::DIRECTORY, "My file7", 55);
    LineEntryWidget *line8 = new LineEntryWidget(LineEntryWidget::LineType::DIRECTORY, "My file8", 8588);

    window->addNewEntry(line1);
    window->addNewEntry(line2);
    window->addNewEntry(line3);
    window->addNewEntry(line4);
    window->addNewEntry(line5);
    window->addNewEntry(line6);
    window->addNewEntry(line7);
    window->addNewEntry(line8);

    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(window);
}

void FileManager::updateTopBarPath(const QString &newPath) {
    topBarWidget->setPath(newPath);
}

FileManager::~FileManager(){
}