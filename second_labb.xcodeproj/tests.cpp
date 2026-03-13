#include <iostream>
#include <stdexcept>
#include "tests.h"
#include "MutableArraySequence.h"
#include "ImmutableArraySequence.h"
#include "MutableListSequence.h"
#include "ImmutableListSequence.h"

using namespace std;

static int tests_passed = 0;
static int tests_failed = 0;

static void check(bool condition, const char* test_name) {
    if (condition) {
        cout << "  Тест комплитед " << test_name << "\n";
        tests_passed++;
    } else {
        cout << "  Ошибка(( " << test_name << "\n";
        tests_failed++;
    }
}

static int double_val(int x) { return x * 2; }
static bool is_even(int x) { return x % 2 == 0; }
static int sum(int acc, int x) { return acc + x; }


void test_mutable_array_sequence() {
    cout << "\n MutableArraySequence\n";


    {
        MutableArraySequence<int> seq;
        check(seq.GetLength() == 0, "Конструктор: длина пустой последовательности == 0");
    }

    {
        int data[] = {10, 20, 30};
        MutableArraySequence<int> seq(data, 3);
        check(seq.GetLength() == 3,  "Конструктор из массива: длина == 3");
        check(seq.Get(0) == 10,      "Конструктор из массива: Get(0) == 10");
        check(seq.Get(2) == 30,      "Конструктор из массива: Get(2) == 30");
        check(seq.GetFirst() == 10,  "GetFirst() == 10");
        check(seq.GetLast() == 30,   "GetLast() == 30");
        check(seq[1] == 20,          "operator[](1) == 20");
    }

    // Append
    {
        MutableArraySequence<int> seq;
        seq.Append(1);
        seq.Append(2);
        seq.Append(3);
        check(seq.GetLength() == 3, "Append: длина == 3");
        check(seq.GetFirst() == 1,  "Append: GetFirst() == 1");
        check(seq.GetLast() == 3,   "Append: GetLast() == 3");
    }

    // Prepend
    {
        MutableArraySequence<int> seq;
        seq.Append(2);
        seq.Prepend(1);
        check(seq.GetFirst() == 1, "Prepend: GetFirst() == 1");
        check(seq.GetLength() == 2, "Prepend: длина == 2");
    }

    // InsertAt
    {
        int data[] = {1, 3};
        MutableArraySequence<int> seq(data, 2);
        seq.InsertAt(2, 1);
        check(seq.Get(1) == 2, "InsertAt(2, 1): Get(1) == 2");
        check(seq.GetLength() == 3, "InsertAt: длина == 3");
    }

    // GetSubsequence
    {
        int data[] = {10, 20, 30, 40, 50};
        MutableArraySequence<int> seq(data, 5);
        Sequence<int>* sub = seq.GetSubsequence(1, 3);
        check(sub->GetLength() == 3,  "GetSubsequence: длина == 3");
        check(sub->Get(0) == 20,      "GetSubsequence: Get(0) == 20");
        check(sub->Get(2) == 40,      "GetSubsequence: Get(2) == 40");
        delete sub;
    }

    // GetSubsequence — невалидные индексы
    {
        int data[] = {1, 2, 3};
        MutableArraySequence<int> seq(data, 3);
        bool threw = false;
        try { seq.GetSubsequence(2, 1); } catch (const out_of_range&) { threw = true; }
        check(threw, "GetSubsequence(2,1): выбрасывает out_of_range");
    }

    // Concat
    {
        int d1[] = {1, 2};
        int d2[] = {3, 4};
        MutableArraySequence<int> a(d1, 2);
        MutableArraySequence<int> b(d2, 2);
        Sequence<int>* c = a.Concat(&b);
        check(c->GetLength() == 4, "Concat: длина == 4");
        check(c->Get(0) == 1,      "Concat: Get(0) == 1");
        check(c->Get(3) == 4,      "Concat: Get(3) == 4");
        delete c;
    }

    // Map
    {
        int data[] = {1, 2, 3};
        MutableArraySequence<int> seq(data, 3);
        Sequence<int>* mapped = seq.Map(double_val);
        check(mapped->Get(0) == 2, "Map: Get(0) == 2");
        check(mapped->Get(1) == 4, "Map: Get(1) == 4");
        check(mapped->Get(2) == 6, "Map: Get(2) == 6");
        delete mapped;
    }

    // Where
    {
        int data[] = {1, 2, 3, 4, 5};
        MutableArraySequence<int> seq(data, 5);
        Sequence<int>* filtered = seq.Where(is_even);
        check(filtered->GetLength() == 2, "Where: длина == 2");
        check(filtered->Get(0) == 2,      "Where: Get(0) == 2");
        check(filtered->Get(1) == 4,      "Where: Get(1) == 4");
        delete filtered;
    }

    // Reduce
    {
        int data[] = {1, 2, 3, 4, 5};
        MutableArraySequence<int> seq(data, 5);
        int result = seq.Reduce(sum, 0);
        check(result == 15, "Reduce(sum, 0) == 15");
    }
}


// ImmutableArraySequence


void test_immutable_array_sequence() {
    cout << "\nImmutableArraySequence\n";

    // Конструктор и GetLength
    {
        ImmutableArraySequence<int> seq;
        check(seq.GetLength() == 0, "Конструктор: длина пустой последовательности == 0");
    }

    // Конструктор из массива
    {
        int data[] = {5, 10, 15};
        ImmutableArraySequence<int> seq(data, 3);
        check(seq.GetLength() == 3, "Конструктор из массива: длина == 3");
        check(seq.Get(0) == 5,      "Get(0) == 5");
        check(seq.GetFirst() == 5,  "GetFirst() == 5");
        check(seq.GetLast() == 15,  "GetLast() == 15");
        check(seq[1] == 10,         "operator[](1) == 10");
    }

    // Append возвращает новую последовательность, оригинал не изменяется
    {
        int data[] = {1, 2};
        ImmutableArraySequence<int> original(data, 2);
        Sequence<int>* appended = original.Append(3);
        check(original.GetLength() == 2,  "Append: оригинал не изменяется");
        check(appended->GetLength() == 3, "Append: новая длина == 3");
        check(appended->GetLast() == 3,   "Append: последний элемент == 3");
        delete appended;
    }

    // Prepend возвращает новую последовательность
    {
        int data[] = {2, 3};
        ImmutableArraySequence<int> original(data, 2);
        Sequence<int>* prepended = original.Prepend(1);
        check(original.GetLength() == 2,    "Prepend: оригинал не изменяется");
        check(prepended->GetLength() == 3,  "Prepend: новая длина == 3");
        check(prepended->GetFirst() == 1,   "Prepend: первый элемент == 1");
        delete prepended;
    }

    // InsertAt
    {
        int data[] = {1, 3};
        ImmutableArraySequence<int> original(data, 2);
        Sequence<int>* inserted = original.InsertAt(2, 1);
        check(original.GetLength() == 2,  "InsertAt: оригинал не изменяется");
        check(inserted->Get(1) == 2,      "InsertAt: Get(1) == 2");
        check(inserted->GetLength() == 3, "InsertAt: новая длина == 3");
        delete inserted;
    }

    // GetSubsequence
    {
        int data[] = {10, 20, 30, 40};
        ImmutableArraySequence<int> seq(data, 4);
        Sequence<int>* sub = seq.GetSubsequence(1, 2);
        check(sub->GetLength() == 2, "GetSubsequence: длина == 2");
        check(sub->Get(0) == 20,     "GetSubsequence: Get(0) == 20");
        check(sub->Get(1) == 30,     "GetSubsequence: Get(1) == 30");
        delete sub;
    }

    // Concat
    {
        int d1[] = {1, 2};
        int d2[] = {3, 4};
        ImmutableArraySequence<int> a(d1, 2);
        ImmutableArraySequence<int> b(d2, 2);
        Sequence<int>* c = a.Concat(&b);
        check(c->GetLength() == 4, "Concat: длина == 4");
        check(c->Get(2) == 3,      "Concat: Get(2) == 3");
        delete c;
    }

    // Map
    {
        int data[] = {3, 6, 9};
        ImmutableArraySequence<int> seq(data, 3);
        Sequence<int>* mapped = seq.Map(double_val);
        check(mapped->Get(0) == 6,  "Map: Get(0) == 6");
        check(mapped->Get(1) == 12, "Map: Get(1) == 12");
        check(mapped->Get(2) == 18, "Map: Get(2) == 18");
        delete mapped;
    }

    // Where
    {
        int data[] = {1, 2, 3, 4};
        ImmutableArraySequence<int> seq(data, 4);
        Sequence<int>* filtered = seq.Where(is_even);
        check(filtered->GetLength() == 2, "Where: длина == 2");
        check(filtered->Get(0) == 2,      "Where: Get(0) == 2");
        delete filtered;
    }

    // Reduce
    {
        int data[] = {10, 20, 30};
        ImmutableArraySequence<int> seq(data, 3);
        int result = seq.Reduce(sum, 0);
        check(result == 60, "Reduce(sum, 0) == 60");
    }
}

// MutableListSequence


void test_mutable_list_sequence() {
    cout << "\n MutableListSequence\n";

    // Конструктор
    {
        MutableListSequence<int> seq;
        check(seq.GetLength() == 0, "Конструктор: длина пустой последовательности == 0");
    }

    // Конструктор из массива
    {
        int data[] = {7, 14, 21};
        MutableListSequence<int> seq(data, 3);
        check(seq.GetLength() == 3,  "Конструктор из массива: длина == 3");
        check(seq.Get(0) == 7,       "Get(0) == 7");
        check(seq.GetFirst() == 7,   "GetFirst() == 7");
        check(seq.GetLast() == 21,   "GetLast() == 21");
        check(seq[1] == 14,          "operator[](1) == 14");
    }

    // Append
    {
        MutableListSequence<int> seq;
        seq.Append(100);
        seq.Append(200);
        check(seq.GetLength() == 2,  "Append: длина == 2");
        check(seq.GetFirst() == 100, "Append: GetFirst() == 100");
        check(seq.GetLast() == 200,  "Append: GetLast() == 200");
    }

    // Prepend
    {
        MutableListSequence<int> seq;
        seq.Append(2);
        seq.Prepend(1);
        check(seq.GetFirst() == 1,  "Prepend: GetFirst() == 1");
        check(seq.GetLength() == 2, "Prepend: длина == 2");
    }

    // InsertAt
    {
        int data[] = {1, 3};
        MutableListSequence<int> seq(data, 2);
        seq.InsertAt(2, 1);
        check(seq.Get(1) == 2,      "InsertAt(2, 1): Get(1) == 2");
        check(seq.GetLength() == 3, "InsertAt: длина == 3");
    }

    // GetSubsequence
    {
        int data[] = {10, 20, 30, 40, 50};
        MutableListSequence<int> seq(data, 5);
        Sequence<int>* sub = seq.GetSubsequence(1, 3);
        check(sub->GetLength() == 3, "GetSubsequence: длина == 3");
        check(sub->Get(0) == 20,     "GetSubsequence: Get(0) == 20");
        check(sub->Get(2) == 40,     "GetSubsequence: Get(2) == 40");
        delete sub;
    }

    // GetSubsequence — невалидные индексы
    {
        int data[] = {1, 2, 3};
        MutableListSequence<int> seq(data, 3);
        bool threw = false;
        try { seq.GetSubsequence(3, 1); } catch (const out_of_range&) { threw = true; }
        check(threw, "GetSubsequence(3,1): выбрасывает out_of_range");
    }

    // Concat
    {
        int d1[] = {1, 2};
        int d2[] = {3, 4};
        MutableListSequence<int> a(d1, 2);
        MutableListSequence<int> b(d2, 2);
        Sequence<int>* c = a.Concat(&b);
        check(c->GetLength() == 4, "Concat: длина == 4");
        check(c->Get(0) == 1,      "Concat: Get(0) == 1");
        check(c->Get(3) == 4,      "Concat: Get(3) == 4");
        delete c;
    }

    // Map
    {
        int data[] = {5, 10, 15};
        MutableListSequence<int> seq(data, 3);
        Sequence<int>* mapped = seq.Map(double_val);
        check(mapped->Get(0) == 10, "Map: Get(0) == 10");
        check(mapped->Get(1) == 20, "Map: Get(1) == 20");
        check(mapped->Get(2) == 30, "Map: Get(2) == 30");
        delete mapped;
    }

    // Where
    {
        int data[] = {1, 2, 3, 4, 5, 6};
        MutableListSequence<int> seq(data, 6);
        Sequence<int>* filtered = seq.Where(is_even);
        check(filtered->GetLength() == 3, "Where: длина == 3");
        check(filtered->Get(0) == 2,      "Where: Get(0) == 2");
        check(filtered->Get(2) == 6,      "Where: Get(2) == 6");
        delete filtered;
    }

    // Reduce
    {
        int data[] = {1, 2, 3, 4, 5};
        MutableListSequence<int> seq(data, 5);
        int result = seq.Reduce(sum, 0);
        check(result == 15, "Reduce(sum, 0) == 15");
    }
}


// ImmutableListSequence


void test_immutable_list_sequence() {
    cout << "\nImmutableListSequence\n";

    // Конструктор
    {
        ImmutableListSequence<int> seq;
        check(seq.GetLength() == 0, "Конструктор: длина пустой последовательности == 0");
    }

    // Конструктор из массива
    {
        int data[] = {3, 6, 9};
        ImmutableListSequence<int> seq(data, 3);
        check(seq.GetLength() == 3, "Конструктор из массива: длина == 3");
        check(seq.Get(0) == 3,      "Get(0) == 3");
        check(seq.GetFirst() == 3,  "GetFirst() == 3");
        check(seq.GetLast() == 9,   "GetLast() == 9");
        check(seq[1] == 6,          "operator[](1) == 6");
    }

    // Append возвращает новую последовательность
    {
        int data[] = {1, 2};
        ImmutableListSequence<int> original(data, 2);
        Sequence<int>* appended = original.Append(3);
        check(original.GetLength() == 2,  "Append: оригинал не изменяется");
        check(appended->GetLength() == 3, "Append: новая длина == 3");
        check(appended->GetLast() == 3,   "Append: последний элемент == 3");
        delete appended;
    }

    // Prepend возвращает новую последовательность
    {
        int data[] = {2, 3};
        ImmutableListSequence<int> original(data, 2);
        Sequence<int>* prepended = original.Prepend(1);
        check(original.GetLength() == 2,   "Prepend: оригинал не изменяется");
        check(prepended->GetLength() == 3, "Prepend: новая длина == 3");
        check(prepended->GetFirst() == 1,  "Prepend: первый элемент == 1");
        delete prepended;
    }

    // InsertAt
    {
        int data[] = {1, 3};
        ImmutableListSequence<int> original(data, 2);
        Sequence<int>* inserted = original.InsertAt(2, 1);
        check(original.GetLength() == 2,  "InsertAt: оригинал не изменяется");
        check(inserted->Get(1) == 2,      "InsertAt: Get(1) == 2");
        check(inserted->GetLength() == 3, "InsertAt: новая длина == 3");
        delete inserted;
    }

    // GetSubsequence
    {
        int data[] = {5, 10, 15, 20};
        ImmutableListSequence<int> seq(data, 4);
        Sequence<int>* sub = seq.GetSubsequence(0, 2);
        check(sub->GetLength() == 3, "GetSubsequence: длина == 3");
        check(sub->Get(0) == 5,      "GetSubsequence: Get(0) == 5");
        check(sub->Get(2) == 15,     "GetSubsequence: Get(2) == 15");
        delete sub;
    }

    // Concat
    {
        int d1[] = {1, 2};
        int d2[] = {3, 4};
        ImmutableListSequence<int> a(d1, 2);
        ImmutableListSequence<int> b(d2, 2);
        Sequence<int>* c = a.Concat(&b);
        check(c->GetLength() == 4, "Concat: длина == 4");
        check(c->Get(0) == 1,      "Concat: Get(0) == 1");
        check(c->Get(3) == 4,      "Concat: Get(3) == 4");
        delete c;
    }

    // Map
    {
        int data[] = {1, 2, 3};
        ImmutableListSequence<int> seq(data, 3);
        Sequence<int>* mapped = seq.Map(double_val);
        check(mapped->Get(0) == 2, "Map: Get(0) == 2");
        check(mapped->Get(1) == 4, "Map: Get(1) == 4");
        check(mapped->Get(2) == 6, "Map: Get(2) == 6");
        delete mapped;
    }

    // Where
    {
        int data[] = {2, 3, 4, 5, 6};
        ImmutableListSequence<int> seq(data, 5);
        Sequence<int>* filtered = seq.Where(is_even);
        check(filtered->GetLength() == 3, "Where: длина == 3");
        check(filtered->Get(0) == 2,      "Where: Get(0) == 2");
        check(filtered->Get(2) == 6,      "Where: Get(2) == 6");
        delete filtered;
    }

    // Reduce
    {
        int data[] = {1, 2, 3, 4, 5};
        ImmutableListSequence<int> seq(data, 5);
        int result = seq.Reduce(sum, 0);
        check(result == 15, "Reduce(sum, 0) == 15");
    }
}


// Запуск всех тестов


void run_all_tests() {
    tests_passed = 0;
    tests_failed = 0;

    test_mutable_array_sequence();
    test_immutable_array_sequence();
    test_mutable_list_sequence();
    test_immutable_list_sequence();

    cout << "\n";
    cout << "Пройдено: " << tests_passed << "\n";
    cout << "Провалено: " << tests_failed << "\n";
    if (tests_failed == 0) {
        cout << "Все тесты пройдены!\n";
    } else {
        cout << "Есть ошибки\n";
    }
    cout << "\n";
}
