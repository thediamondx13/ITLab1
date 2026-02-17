#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ITLab1.h"
#include "Crypter.h"

class ITLab1 : public QMainWindow
{
    Q_OBJECT

public:
    ITLab1(QWidget* parent = nullptr);
    ~ITLab1();

private:
    Ui::ITLab1Class ui;
    QString SanitizeText(const QString& text, const QString& alphabet);

private slots:
    void on_btnVigenereEncrypt_clicked();
    void on_btnVigenereDecrypt_clicked();
    void on_btnPlayfairEncrypt_clicked();
    void on_btnPlayfairDecrypt_clicked();
    void on_btnVigenereLoad_clicked();
    void on_btnVigenereSave_clicked();
    void on_btnPlayfairLoad_clicked();
    void on_btnPlayfairSave_clicked();
};