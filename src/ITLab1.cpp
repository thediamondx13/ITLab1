#include "ITLab1.h"
#include <QTextStream>
#include <QFileDialog>
#include <QFile>

ITLab1::ITLab1(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}

ITLab1::~ITLab1()
{
}

/* Leaves only characters in the alphabet and uppercases them */
QString ITLab1::SanitizeText(const QString& text, const QString& alphabet)
{
    QString cleanText;
    for (const QChar& ch : text)
    {
        QChar upperCh = ch.toUpper();
        if (alphabet.contains(upperCh))
            cleanText.append(upperCh);
    }
    return cleanText;
}

/* Vigenere encrypt/decrypt */

void ITLab1::on_btnVigenereEncrypt_clicked()
{
    QString text = SanitizeText(ui.teVigenereInput->toPlainText(), Crypter::russian);
    QString key = SanitizeText(ui.leVigenereKey->text(), Crypter::russian);

    if (text.isEmpty())
    {
        ui.teVigenereOutput->setPlainText("Ошибка: Исходный текст пуст!");
        return;
    }

    if (key.isEmpty())
    {
        ui.teVigenereOutput->setPlainText("Ошибка: Ключ пуст!");
        return;
    }

    ui.teVigenereOutput->setPlainText(Crypter::EncryptVigenere(text, Crypter::russian, key));
}

void ITLab1::on_btnVigenereDecrypt_clicked()
{
    QString text = SanitizeText(ui.teVigenereInput->toPlainText(), Crypter::russian);
    QString key = SanitizeText(ui.leVigenereKey->text(), Crypter::russian);

    if (text.isEmpty())
    {
        ui.teVigenereOutput->setPlainText("Ошибка: Шифротекст пуст!");
        return;
    }

    if (key.isEmpty())
    {
        ui.teVigenereOutput->setPlainText("Ошибка: Ключ пуст!");
        return;
    }

    ui.teVigenereOutput->setPlainText(Crypter::DecryptVigenere(text, Crypter::russian, key));
}

/* Vigenere file I/O */

void ITLab1::on_btnVigenereLoad_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Открыть файл", "", "Текстовые файлы (*.txt)");
    if (!fileName.isEmpty())
    {
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream in(&file);
            ui.teVigenereInput->setPlainText(in.readAll());
            file.close();
        }
    }
}

void ITLab1::on_btnVigenereSave_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Сохранить файл", "", "Текстовые файлы (*.txt)");
    if (!fileName.isEmpty())
    {
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream out(&file);
            out << ui.teVigenereOutput->toPlainText();
            file.close();
        }
    }
}

/* Playfair encrypt/decrypt */

void ITLab1::on_btnPlayfairEncrypt_clicked()
{
    QString text = SanitizeText(ui.tePlayfairInput->toPlainText(), Crypter::english);

    QString kTL = SanitizeText(ui.lePlayfairKeyTL->text(), Crypter::english);
    QString kTR = SanitizeText(ui.lePlayfairKeyTR->text(), Crypter::english);
    QString kBL = SanitizeText(ui.lePlayfairKeyBL->text(), Crypter::english);
    QString kBR = SanitizeText(ui.lePlayfairKeyBR->text(), Crypter::english);

    if (text.isEmpty())
    {
        ui.tePlayfairOutput->setPlainText("Ошибка: Исходный текст пуст!");
        return;
    }

    ui.tePlayfairOutput->setPlainText(Crypter::EncryptPlayfair(text, Crypter::english, kTL, kTR, kBL, kBR));
}

void ITLab1::on_btnPlayfairDecrypt_clicked()
{
    QString text = SanitizeText(ui.tePlayfairInput->toPlainText(), Crypter::english);

    QString kTL = SanitizeText(ui.lePlayfairKeyTL->text(), Crypter::english);
    QString kTR = SanitizeText(ui.lePlayfairKeyTR->text(), Crypter::english);
    QString kBL = SanitizeText(ui.lePlayfairKeyBL->text(), Crypter::english);
    QString kBR = SanitizeText(ui.lePlayfairKeyBR->text(), Crypter::english);

    if (text.isEmpty())
    {
        ui.tePlayfairOutput->setPlainText("Ошибка: Шифротекст пуст!");
        return;
    }

    if (text.length() % 2 == 1)
    {
        ui.tePlayfairOutput->setPlainText("Ошибка: Длина шифротекста должна быть четной!");
        return;
    }

    ui.tePlayfairOutput->setPlainText(Crypter::DecryptPlayfair(text, Crypter::english, kTL, kTR, kBL, kBR));
}

/* Playfair file I/O */

void ITLab1::on_btnPlayfairLoad_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Открыть файл", "", "Текстовые файлы (*.txt)");
    if (!fileName.isEmpty())
    {
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream in(&file);
            ui.tePlayfairInput->setPlainText(in.readAll());
            file.close();
        }
    }
}

void ITLab1::on_btnPlayfairSave_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Сохранить файл", "", "Текстовые файлы (*.txt)");
    if (!fileName.isEmpty())
    {
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream out(&file);
            out << ui.tePlayfairOutput->toPlainText();
            file.close();
        }
    }
}