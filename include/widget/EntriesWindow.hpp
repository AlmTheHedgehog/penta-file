#pragma once
#include <vector>
#include <string>
#include <QScrollArea>
#include <QDir>
#include <QProcess>
#include <QDirIterator>

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
        void copyAndReplaceFolderContents(const QString &fromDir, const QString &toDir, bool copyAndRemove = false);        unsigned int entriesNumber;
        std::vector<LineEntry*> lineEntries;
        QWidget *entriesContainer;
        QDir directory;
        LineEntry *selectedLine = nullptr;
        QFileInfo *copiedLine = nullptr;
        bool *isCut = new bool(false);

    public slots:
        void setNewPath(const QString &newPath);
        void selectLine(const QString &filePath);
        void copySelectedLine();
        void pasteSelectedLine(const QString &destinationPath);
        void cutSelectedLine();
        void deleteSelectedLine();
        void addNewFolder(const QString &destinationPath);
        void renameSelectedLine(const QString &newName);

    signals:
        void wrongPath();
        void setNewPathSignal(const QString &newPath);
        void setFileToPathSignal(const QString &filePath);
        void copiedLineSignal(const QString &filePath);

};
