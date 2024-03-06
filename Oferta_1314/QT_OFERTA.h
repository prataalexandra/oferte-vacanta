#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QT_OFERTA.h"

class QT_OFERTA : public QMainWindow
{
    Q_OBJECT

public:
    QT_OFERTA(QWidget* parent = nullptr);
    ~QT_OFERTA();

private:
    Ui::QT_OFERTAClass ui;
};
