#pragma once
#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QString>
#include <QPixmap>
#include <QtGlobal>
#include <QMenu>
#include <QMenuBar>
#include <QMainWindow>
#include <QAction>
#include <QLineEdit>
#include <QPushButton>
#include <QDir>
#include <QInputDialog>


#include "../rosourcesPaths.hpp"
#include "../macrologger.h"

class TopBarWidget : public QWidget {
    Q_OBJECT

    public:
        TopBarWidget(QWidget *parent = nullptr);
        virtual ~TopBarWidget();

    protected:

    public slots:
        void setPath(const QString &newPath);
        void searchPath();
        void turnOnVerifyChecksumButton(bool status);
        void turnOnPropertiesButton(bool status);
        void turnOnEditButtons(bool status);
       
    private slots:
        void cut();
        void copy();
        void paste();
        void undo();
        void redo();
        void addNewFolder();
        void addNewFile();
        void deleteItem();
        void checksumVerification();
        void searchByHash();
        void properties();
        void renameItem();

    signals:
        void newPathSignal(const QString &newPath);
        void copySignal();
        void pasteSignal(const QString &destinationPath);
        void cutSignal();
        void deleteSignal();
        void addNewFolderSignal(const QString &destinationPath);
        void checksumVerificationSignal();
        void searchByHashSignal(const QString &searchHash);
        void propertiesSignal();
        void renameSignal();
    
    private:
        void createActions();
        void createMenus(QMenuBar *menuBar);
        void createSearchField(QLineEdit *pathField, QPushButton *goToPathButton);
        void createHashSearchField(QLineEdit *hashSearchField, QPushButton *hashSearchButton);

        QMenuBar *menuBar;
        QMenu *fileMenu;
        QMenu *editMenu;
        QMenu *helpMenu;
        

        QAction *cutAct;
        QAction *copyAct;
        QAction *pasteAct;
        QAction *undoAct;
        QAction *redoAct;
        QAction *addNewFolderAct;
        QAction *addNewFileAct;
        QAction *deleteAct;
        QAction *renameAct;
        QAction *checksumVerificationAct;
        QAction *propertiesAct;
        QLabel *undoIconLabel;
        QLabel*redoIconLabel;

        
        QLineEdit *pathField;
        QPushButton *goToPathButton;
        QLineEdit *hashSearchField;
        QPushButton *hashSearchButton;

        bool *isCut = new bool(false);
};

