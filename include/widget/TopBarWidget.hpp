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
       
    private slots:
        void cut();
        void copy();
        void paste();
        void undo();
        void redo();
        void addNewFolder();
        void addNewFile();
        void deleteItem();

    signals:
        void newPathSignal(const QString &newPath);
   
    
    private:
        void createActions();
        void createMenus(QMenuBar *menuBar);
        void createSearchField(QLineEdit *pathField, QPushButton *searchButton);

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

        QLabel *undoIconLabel;
        QLabel*redoIconLabel;

        
        QLineEdit *pathField;
        QPushButton *searchButton;
};

