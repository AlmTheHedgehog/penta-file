#pragma once
#include <vector>
#include <string>
#include <QScrollArea>
#include <QDir>

#include "LineEntry.hpp"
#include "../macrologger.h"

class EntriesWindow : public QScrollArea {
    Q_OBJECT

    public:
        EntriesWindow(QString path = "", QWidget *parent = nullptr);
        virtual ~EntriesWindow();

    private:
        void addNewEntry(LineEntry* newEntry);
        void clearEntiesList();
        unsigned int entriesNumber;
        std::vector<LineEntry*> lineEntries;
        QWidget *entriesContainer;
        QDir directory;

    public slots:
        void setNewPath(QString newPath);
    signals:
        void wrongPath();

};
