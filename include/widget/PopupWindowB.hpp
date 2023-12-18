#pragma once
#include <QWidget>

#include "../rosourcesPaths.hpp"
#include "../macrologger.h"

class PopupWindowB : public QWidget {
    Q_OBJECT

    public:
        PopupWindowB(QWidget *parent = nullptr): QWidget(parent){};
        virtual ~PopupWindowB(){emit windowDestroyed(this);};

    signals:
        void windowDestroyed(PopupWindowB* window);
    
};
