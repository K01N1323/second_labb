#include "BitSequence.h"

// Конструктор по умолчанию или из значения bool
Bit::Bit(bool v) : value(v) {}

// Конструктор из int (преобразуется в логическое значение)
Bit::Bit(int v) : value(v != 0) {}

// Возвращает значение бита
bool Bit::GetValue() const { 
    return value; 
}

// Перегрузка оператора побитового И (&)
Bit Bit::operator&(const Bit &other) const {
    return Bit(this->value && other.value);
}

// Перегрузка оператора побитового ИЛИ (|)
Bit Bit::operator|(const Bit &other) const {
    return Bit(this->value || other.value);
}

// Перегрузка оператора побитового ИСКЛЮЧАЮЩЕГО ИЛИ (^)
Bit Bit::operator^(const Bit &other) const {
    return Bit(this->value != other.value);
}

// Перегрузка оператора логического отрицания (~)
Bit Bit::operator~() const { 
    return Bit(!this->value); 
}

// Перегрузка оператора сравнения на равенство (==)
bool Bit::operator==(const Bit &other) const { 
    return this->value == other.value; 
}

// Перегрузка оператора вывода в поток (<<)
std::ostream &operator<<(std::ostream &os, const Bit &b) { 
    os << b.value;
    return os;
}

// Конструктор по умолчанию
BitSequence::BitSequence() : MutableArraySequence<Bit>() {}

// Выполняет побитовое И с другой последовательностью битов
BitSequence* BitSequence::And(Sequence<Bit> *other) const {
    BitSequence *new_bit_sequence = new BitSequence();

    int elements_to_change = (this->GetLength() < other->GetLength())
                                 ? this->GetLength()
                                 : other->GetLength();

    for (int index = 0; index < elements_to_change; index++) {
        new_bit_sequence->Append(this->Get(index) & other->Get(index));
    }

    return new_bit_sequence;
}

// Выполняет побитовое ИЛИ с другой последовательностью битов
BitSequence* BitSequence::Or(Sequence<Bit> *other) const {
    BitSequence *new_bit_sequence = new BitSequence();

    int elements_to_change = (this->GetLength() < other->GetLength())
                                 ? this->GetLength()
                                 : other->GetLength();

    for (int index = 0; index < elements_to_change; index++) {
        new_bit_sequence->Append(this->Get(index) | other->Get(index));
    }

    return new_bit_sequence;
}

// Выполняет побитовое ИСКЛЮЧАЮЩЕЕ ИЛИ с другой последовательностью битов
BitSequence* BitSequence::Xor(Sequence<Bit> *other) const {
    BitSequence *new_bit_sequence = new BitSequence();

    int elements_to_change = (this->GetLength() < other->GetLength())
                                 ? this->GetLength()
                                 : other->GetLength();

    for (int index = 0; index < elements_to_change; index++) {
        new_bit_sequence->Append(this->Get(index) ^ other->Get(index));
    }

    return new_bit_sequence;
}

// Инвертирует все биты в последовательности
BitSequence* BitSequence::Not() const {
    BitSequence *new_bit_sequence = new BitSequence();

    for (int index = 0; index < this->GetLength(); index++) {
        new_bit_sequence->Append(~this->Get(index));
    }

    return new_bit_sequence;
}
