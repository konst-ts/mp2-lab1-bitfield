// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	BitLen = len;
	MemLen = (len + sizeof(TELEM) - 1) / sizeof(TELEM);
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++) { pMem[i] = 0; }
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++) { pMem[i] = bf.pMem[i]; }
}

TBitField::~TBitField()
{
	delete[] pMem;
	pMem = nullptr;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return n / sizeof(TELEM);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	TELEM x = 1;
	x << n % sizeof(TELEM);
	return x;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	pMem[GetMemIndex(n)] | GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
	pMem[GetMemIndex(n)] & (~GetMemMask(n));
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	TELEM x = pMem[GetMemIndex(n)];
	x >> n % sizeof(TELEM);
	x & GetMemMask(0);
	int y = x;
	return y;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (BitLen == bf.BitLen){
		for (int i = 0; i < MemLen; i++) {
			pMem[i] = bf.pMem[i];
		}
	}
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (BitLen == bf.BitLen) {
		for (int i = 0; i < MemLen; i++) {
			if ((pMem[i] ^ bf.pMem[i]) != 0) { return 0; }
		}
	}
	return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if (BitLen == bf.BitLen) {
		for (int i = 0; i < MemLen; i++) {
			if ((pMem[i] ^ bf.pMem[i]) != 0) { return 1; }
		}
	}
	return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	if (BitLen == bf.BitLen) {
		for (int i = 0; i < MemLen; i++) {
			pMem[i] = pMem[i] | bf.pMem[i];
		}
	}
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	if (BitLen == bf.BitLen) {
		for (int i = 0; i < MemLen; i++) {
			pMem[i] = pMem[i] & bf.pMem[i];
		}
	}
}

TBitField TBitField::operator~(void) // отрицание
{
	for (int i = 0; i < MemLen; i++) {
		pMem[i] = ~pMem[i];
	}
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	for (int i = 0; i < bf.MemLen; i++) {
		istr >> bf.pMem[i];
	}
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i = 0; i < bf.MemLen; i++) {
		ostr << bf.pMem[i];
	}
}
