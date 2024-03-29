#pragma once
#include <vector>
#include <string>
#include <QScrollArea>
#include <QDir>
#include <QProcess>
#include <QDirIterator>

#include "PopupWindowB.hpp"
#include "RenameWindow.hpp"
#include "ChecksumDialogWindow.hpp"
#include "NotificationWindow.hpp"
#include "PropertiesWindow.hpp"
#include "LineEntry.hpp"
#include "AgreeDialog.hpp"
#include "../macrologger.h"

class EntriesWindow : public QScrollArea {
    Q_OBJECT

    public:
        EntriesWindow(QString path = "", QWidget *parent = nullptr);
        virtual ~EntriesWindow();

    private:
        void addNewEntry(LineEntry* newEntry);
        void clearEntiesList();
        void copyAndReplaceFolderContents(const QString &fromDir, const QString &toDir, bool copyAndRemove = false);
        unsigned int entriesNumber;
        void initPopupWindow(PopupWindowB* window);
        void addFileLinesToVector(QDir directory, const QString &hash);
        void deselectLine();
        std::vector<LineEntry*> lineEntries;
        std::vector<PopupWindowB*> dialogWindows;
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
        void deletePopupWindow(PopupWindowB *windowPtr);
        void createNewChecksumVerificationWindow();
        void searchByHash(const QString &hash);
        void createPropertiesWindow();
        void createRenameWindow();
        void updateEntry();

    signals:
        void wrongPath();
        void setNewPathSignal(const QString &newPath);
        void setFileToPathSignal(const QString &filePath);
        void copiedLineSignal(const QString &filePath);
        void turnOnChecksumVerificationForSelectedLineSignal(bool status);
        void turnOnPropertiesForSelectedLineSignal(bool status);
        void turnOnEditButtonSignal(bool status);
    
    protected:
         void mousePressEvent(QMouseEvent *event) override;
};