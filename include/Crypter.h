#pragma once

#include <QString>
#include <cassert>

class Crypter
{
public:
    static const QString russian;
    static const QString english;

    static QString EncryptVigenere(QString source, const QString& alph, const QString& key);
    static QString DecryptVigenere(QString source, const QString& alph, const QString& key);

    static QString EncryptPlayfair(QString source, const QString& alph, const QString& keyTL, const QString& keyTR, const QString& keyBL, const QString& keyBR);
    static QString DecryptPlayfair(QString source, const QString& alph, const QString& keyTL, const QString& keyTR, const QString& keyBL, const QString& keyBR);

private:
    /* alphabets used for Playfair algorithm */
    static const QString englishPlayfair; // doesn't contain 'J'

    static QString PlayfairPrepString(QString str, const QString& alph);

    static QString GeneratePlayfairTable(const QString& key, const QString& plAlph);
};