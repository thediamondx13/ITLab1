#include "Crypter.h"

const QString Crypter::russian = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
const QString Crypter::english = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

/* Internal (private) */
const QString Crypter::englishPlayfair = "ABCDEFGHIKLMNOPQRSTUVWXYZ";

QString Crypter::EncryptVigenere(QString source, const QString& alph, const QString& key)
{
    if (source.isEmpty()) return "";
    assert(!key.isEmpty() && "Key string must not be empty for Vigenere");

    qsizetype alphLen = alph.length();
    qsizetype keyLen = key.length();

    for (qsizetype i = 0; i < source.length(); i++)
    {
        assert(alph.contains(source.at(i)) && "Source string contains invalid character(s)");
        assert(alph.contains(key.at(i % keyLen)) && "Key string contains invalid character(s)");

        qsizetype srcIndex = alph.indexOf(source.at(i));
        qsizetype keyIndex = alph.indexOf(key.at(i % keyLen));
        qsizetype resIndex = (srcIndex + keyIndex) % alphLen;
        source[i] = alph.at(resIndex);
    }

    return source;
}

QString Crypter::DecryptVigenere(QString source, const QString& alph, const QString& key)
{
    if (source.isEmpty()) return "";
    assert(!key.isEmpty() && "Key string must not be empty for Vigenere");

    qsizetype alphLen = alph.length();
    qsizetype keyLen = key.length();

    for (qsizetype i = 0; i < source.length(); i++)
    {
        assert(alph.contains(source.at(i)) && "Source string contains invalid character(s)");
        assert(alph.contains(key.at(i % keyLen)) && "Key string contains invalid character(s)");

        qsizetype srcIndex = alph.indexOf(source.at(i));
        qsizetype keyIndex = alph.indexOf(key.at(i % keyLen));
        qsizetype resIndex = (srcIndex - keyIndex + alphLen) % alphLen;
        source[i] = alph.at(resIndex);
    }
    return source;
}

QString Crypter::EncryptPlayfair(QString source, const QString& alph,
    const QString& keyTL, const QString& keyTR,
    const QString& keyBL, const QString& keyBR)
{
    assert(alph == Crypter::english && "Only english is supported");

    /* Swap 'J' with 'I' and add 'X' if the length is odd */
    source = PlayfairPrepString(source, alph);
    if (source.length() % 2 == 1) source.append('X');
    
    //if (alph == Crypter::english)
    //{
        const QString& plAlph = Crypter::englishPlayfair;
        constexpr qsizetype tableSide = 5;
    //}

    /* Generate the tables */
    QString sqTL = GeneratePlayfairTable(PlayfairPrepString(keyTL, alph), plAlph);
    QString sqTR = GeneratePlayfairTable(PlayfairPrepString(keyTR, alph), plAlph);
    QString sqBL = GeneratePlayfairTable(PlayfairPrepString(keyBL, alph), plAlph);
    QString sqBR = GeneratePlayfairTable(PlayfairPrepString(keyBR, alph), plAlph);

    for (qsizetype i = 0; i < source.length(); i += 2)
    {
        /* First character index in the top-left table */
        qsizetype i1 = sqTL.indexOf(source.at(i));
        qsizetype row1 = i1 / tableSide;
        qsizetype col1 = i1 % tableSide;

        /* Second character index in the bottom-right table */
        qsizetype i2 = sqBR.indexOf(source.at(i + 1));
        qsizetype row2 = i2 / tableSide;
        qsizetype col2 = i2 % tableSide;

        /* Append the corresponding character from
         the top-right and bottom-left tables */
        source[i + 1] = sqBL.at(row2 * tableSide + col1);
        source[i] = sqTR.at(row1 * tableSide + col2);
    }

    return source;
}

QString Crypter::DecryptPlayfair(QString source, const QString& alph,
    const QString& keyTL, const QString& keyTR,
    const QString& keyBL, const QString& keyBR)
{
    assert(source.length() % 2 == 0 && "Source string length must be even");

    assert(alph == Crypter::english && "Only english is supported");

    //if (alph == Crypter::english)
    //{
        const QString& plAlph = Crypter::englishPlayfair;
        constexpr qsizetype tableSide = 5;
    //}
    
    source = PlayfairPrepString(source, alph);

    QString sqTL = GeneratePlayfairTable(PlayfairPrepString(keyTL, alph), plAlph);
    QString sqTR = GeneratePlayfairTable(PlayfairPrepString(keyTR, alph), plAlph);
    QString sqBL = GeneratePlayfairTable(PlayfairPrepString(keyBL, alph), plAlph);
    QString sqBR = GeneratePlayfairTable(PlayfairPrepString(keyBR, alph), plAlph);

    for (qsizetype i = 0; i < source.length(); i += 2)
    {
        /* First character index in the top-left table */
        qsizetype i1 = sqTR.indexOf(source.at(i));
        qsizetype row1 = i1 / tableSide;
        qsizetype col1 = i1 % tableSide;

        /* Second character index in the bottom-right table */
        qsizetype i2 = sqBL.indexOf(source.at(i + 1));
        qsizetype row2 = i2 / tableSide;
        qsizetype col2 = i2 % tableSide;

        /* Append the corresponding character from
         the top-right and bottom-left tables */
        source[i + 1] = sqBR.at(row2 * tableSide + col1);
        source[i] = sqTL.at(row1 * tableSide + col2);
    }

    return source;
}

QString Crypter::PlayfairPrepString(QString str, const QString& alph)
{
    assert(alph == Crypter::english && "Only english is supported");

    //if (alph == Crypter::english)
    {
        for (QChar& c : str)
        {
            assert(alph.contains(c) && "Source string contains invalid character(s)");
            if (c == 'J') c = 'I';
        }
    }

    return str;
}

QString Crypter::GeneratePlayfairTable(const QString& key, const QString& plAlph)
{
    QString used{};
    QString square{};

    for (const QChar& c : key)
    {
        assert(plAlph.contains(c) && "Crypter internal error: key string contains invalid character(s)");

        if (!used.contains(c))
        {
            square.append(c);
            used.append(c);
        }
    }

    for (const QChar& c : plAlph)
        if (!used.contains(c))
            square.append(c);

    return square;
}