#ifndef BIT_SEQUENCE_H
#define BIT_SEQUENCE_H

#include <iostream>
#include "MutableArraySequence.h"

// Класс, представляющий отдельный бит (0 или 1)
class Bit {
private:
    bool value;

public:
    // Конструктор по умолчанию или из значения bool
    Bit(bool v = false);
    
    // Конструктор из int (преобразуется в логическое значение)
    Bit(int v);

    // Возвращает значение бита
    bool GetValue() const;

    // Перегрузка оператора побитового И (&)
    Bit operator&(const Bit &other) const;
    
    // Перегрузка оператора побитового ИЛИ (|)
    Bit operator|(const Bit &other) const;
    
    // Перегрузка оператора побитового ИСКЛЮЧАЮЩЕГО ИЛИ (^)
    Bit operator^(const Bit &other) const;
    
    // Перегрузка оператора логического отрицания (~)
    Bit operator~() const;

    // Перегрузка оператора сравнения на равенство (==)
    bool operator==(const Bit &other) const;

    // Перегрузка оператора вывода в поток (<<)
    friend std::ostream &operator<<(std::ostream &os, const Bit &b);
};

// Класс для работы с последовательностью битов
class BitSequence : public MutableArraySequence<Bit> {
public:
    // Конструктор по умолчанию
    BitSequence();

    // Выполняет побитовое И с другой последовательностью битов
    BitSequence *And(Sequence<Bit> *other) const;
    
    // Выполняет побитовое ИЛИ с другой последовательностью битов
    BitSequence *Or(Sequence<Bit> *other) const;
    
    // Выполняет побитовое ИСКЛЮЧАЮЩЕЕ ИЛИ с другой последовательностью битов
    BitSequence *Xor(Sequence<Bit> *other) const;
    
    // Инвертирует все биты в последовательности
    BitSequence *Not() const;
};

#endif // BIT_SEQUENCE_H