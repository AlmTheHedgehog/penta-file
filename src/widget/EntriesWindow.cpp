#include "widget/EntriesWindow.hpp"

EntriesWindow::EntriesWindow(QString path, QWidget *parent):
                    QScrollArea(parent), entriesNumber(0){
    QWidget *container = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(container);
    setWidget(container);
    container->setLayout(layout);
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->setAlignment(Qt::AlignTop);
    setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setWidgetResizable(true);

    setNewPath(path);
}

EntriesWindow::~EntriesWindow(){
    clearEntiesList();
}

void EntriesWindow::addNewEntry(LineEntry *newEntry){
    lineEntries.push_back(newEntry);
    widget()->layout()->addWidget(newEntry);
    connect(newEntry, &LineEntry::setNewPath, this, &EntriesWindow::setNewPath);
}

void EntriesWindow::clearEntiesList(){
    for(auto eachline : lineEntries){
        delete eachline;
    }
    lineEntries.clear();
    LOG_INFO("Enties list was cleared");
}

void EntriesWindow::setNewPath(QString newPath){
    QFileInfo newDir(newPath);
    if ((!newDir.exists()) || (!newDir.isDir()) || (!newDir.isWritable())) {
        //TODO: make possible to work with read-only dirs
        LOG_ABNORMAL("Failed to set a new directory(%s). Emit wrongPath signal."
                    " Exists:%d, isDir:%d, isWritable:%d",
                    newPath.toLatin1().data(), newDir.exists(), newDir.isDir(), newDir.isWritable());
        emit wrongPath();
        return;
    }
    directory.setPath(newPath);
    clearEntiesList();
    for(auto entry:directory.entryInfoList(QDir::Filter::NoDotAndDotDot
                                            | QDir::Filter::Dirs
                                            | QDir::Filter::Files, 
                                            QDir::SortFlag::DirsFirst
                                            | QDir::SortFlag::Name
                                            | QDir::SortFlag::IgnoreCase)){
        if(entry.isDir()){
            addNewEntry(new LineEntry(LineEntry::LineType::DIRECTORY, entry.fileName(),
                                      entry.absoluteFilePath()));
        }else{
            addNewEntry(new LineEntry(LineEntry::LineType::FILE, entry.fileName(),
                                      entry.absoluteFilePath(), entry.size()));
        }
    }
    LOG_INFO("New path(%s) was set and entries were fetched", newPath.toLatin1().data());
}
