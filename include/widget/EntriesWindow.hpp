#pragma once
#include <vector>
#include <QScrollArea>
#include <QVBoxLayout>

#include "LineEntryWidget.hpp"
#include "../macrologger.h"

class EntriesWindow : public QScrollArea {
    Q_OBJECT

    public:
        EntriesWindow(QWidget *parent = nullptr);
        virtual ~EntriesWindow();
        void addNewEntry(LineEntryWidget* newEntry);


    private:
        unsigned int entriesNumber;
        std::vector<LineEntryWidget*> lineEntries;
        QWidget *entriesContainer;

};
