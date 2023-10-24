#include "widget/EntriesWindow.hpp"

EntriesWindow::EntriesWindow(QWidget *parent):
                    QScrollArea(parent), entriesNumber(0){
    QWidget *container = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(container);
    setWidget(container);
    container->setLayout(layout);
    layout->setMargin(0);
    layout->setAlignment(Qt::AlignTop);
    setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setWidgetResizable(true);
}

EntriesWindow::~EntriesWindow(){
    for(auto eachline : lineEntries){
        delete eachline;
    }
}
void EntriesWindow::addNewEntry(LineEntryWidget *newEntry){
    lineEntries.push_back(newEntry);
    widget()->layout()->addWidget(newEntry);
}
