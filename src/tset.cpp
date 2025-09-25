// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(-1)
{
    MaxPower = mp;
    BitField = new TBitField(mp);
}

// конструктор копирования
TSet::TSet(const TSet &s) :
{
    MaxPower = s.MaxPower;
    delete BitField;
    BitField = new TBitField(s.BitField);
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) :
{
    MaxPower = bf.BitLen;
    BitField = new TBitField(bf);
}

TSet::operator TBitField()
{
    return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
    return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
    BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
    BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
    MaxPower = s.MaxPower;
    BitField = s.BitField;
    return &this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
    return BitField == s.BitField;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
    return BitField != s.BitField;
}

TSet TSet::operator+(const TSet &s) // объединение
{
    TSet x(MaxPower);
    x = BitField | s.BitField;
    return x;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    TSet x(MaxPower);
    x = BitField | x.SetBit(Elem);
    return x;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    TSet x(MaxPower);
    x = BitField & (~x.SetBit(Elem));
    return x;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
    TSet x(MaxPower);
    x = BitField & s.SetBit(Elem);
    return x;
}

TSet TSet::operator~(void) // дополнение
{
    TSet x(MaxPower);
    x = ~BitField;
    return x;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
    for (int i = 0; i < bf.MemLen; i++) {
        istr >> s.BitField.pMem[i];
    }
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
    for (int i = 0; i < bf.MemLen; i++) {
        ostr << s.BitField.pMem[i];
    }
}

