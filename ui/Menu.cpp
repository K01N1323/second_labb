#include <iostream>
#include <limits>

#include "Sequence.h"
#include "BitSequence.h"
#include "ImmutableArraySequence.h"
#include "ImmutableListSequence.h"
#include "MutableArraySequence.h"
#include "MutableListSequence.h"
#include "Menu.h"
#include "Tests.h"

using namespace std;

// Вспомогательная функция для безопасного чтения целого числа из cin
// При некорректном вводе выводит сообщение и повторяет запрос
static int SafeReadInt(const char *prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Некорректный ввод! Введите целое число.\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

// Умножает число на 10
int MultiplyBy10(const int &x) { return x * 10; }

// Проверяет, является ли число четным
bool IsEven(const int &x) { return x % 2 == 0; }

// Складывает два числа
int Sum(const int &x, const int &y) { return x + y; }

// Функция для вывода последовательности на экран
template <typename T> void PrintSequence(Sequence<T> *seq) {
  cout << "[ ";
  for (int index = 0; index < seq->GetLength(); index++) {
    cout << seq->Get(index) << " ";
  }
  cout << "]\n";
}

// Функция для вывода BitSequence на экран
static void PrintBitSequence(BitSequence *bs) {
  cout << "[ ";
  for (int index = 0; index < bs->GetLength(); index++) {
    cout << bs->Get(index) << " ";
  }
  cout << "]\n";
}

// Универсальная функция для ручного тестирования последовательностей
void TestManualSequence(Sequence<int> *&seq, const char *name, bool is_mutable) {
  int choice = -1;
  while (choice != 0) {
    cout << "\nТестирование: " << name << "\n";
    cout << "Текущее состояние: ";
    PrintSequence(seq);
    cout << "1. Append (В конец)\n";
    cout << "2. Prepend (В начало)\n";
    cout << "3. InsertAt (По индексу)\n";
    cout << "4. Get (Получить по индексу)\n";
    cout << "5. GetSubsequence (Подпоследовательность)\n";
    cout << "6. Map (MultiplyBy10)\n";
    cout << "7. Where (IsEven)\n";
    cout << "8. Reduce (Sum)\n";
    cout << "0. Назад\n";
    choice = SafeReadInt("Выбор: ");

    try {
      if (choice == 1 || choice == 2 || choice == 3) {
        int val = SafeReadInt("Введи число: ");
        int idx = 0;
        if (choice == 3) {
          idx = SafeReadInt("Введи индекс: ");
        }

        Sequence<int> *old = seq;
        if (choice == 1)
          seq = seq->Append(val);
        else if (choice == 2)
          seq = seq->Prepend(val);
        else
          seq = seq->InsertAt(val, idx);

        if (!is_mutable && old != seq)
          delete old;
      } else if (choice == 4) {
        int idx = SafeReadInt("Введи индекс: ");
        cout << "Значение: " << seq->Get(idx) << "\n";
      } else if (choice == 5) {
        int start = SafeReadInt("Start index: ");
        int end = SafeReadInt("End index: ");
        Sequence<int> *sub = seq->GetSubsequence(start, end);
        cout << "Результат: ";
        PrintSequence(sub);
        delete sub;
      } else if (choice == 6) {
        Sequence<int> *res = seq->Map(MultiplyBy10);
        cout << "Результат: ";
        PrintSequence(res);
        delete res;
      } else if (choice == 7) {
        Sequence<int> *res = seq->Where(IsEven);
        cout << "Результат: ";
        PrintSequence(res);
        delete res;
      } else if (choice == 8) {
        if (seq->GetLength() > 0)
          cout << "Сумма: " << seq->Reduce(Sum, 0) << "\n";
        else
          cout << "Пусто!\n";
      }
    } catch (const exception &e) {
      cout << "Ошибка: " << e.what() << "\n";
    }
  }
}

// Тестирование последовательности битов
void TestBitSequence() {
  BitSequence *bits1 = new BitSequence();
  BitSequence *bits2 = new BitSequence();

  int choice = -1;
  while (choice != 0) {
    cout << "\nBitSequence Testing\n";
    cout << "Маска 1: ";
    PrintBitSequence(bits1);
    cout << "Маска 2: ";
    PrintBitSequence(bits2);
    cout << "1. Добавить бит в Маску 1\n";
    cout << "2. Добавить бит в Маску 2\n";
    cout << "3. Побитовое И (AND)\n";
    cout << "4. Побитовое ИЛИ (OR)\n";
    cout << "5. Инверсия Маски 1 (NOT)\n";
    cout << "0. Назад\n";
    choice = SafeReadInt("Выбор: ");

    if (choice == 1 || choice == 2) {
      int val = SafeReadInt("Введи 0 или 1: ");
      if (choice == 1)
        bits1->Append(Bit(val));
      else
        bits2->Append(Bit(val));
    } else if (choice == 3) {
      BitSequence *res = bits1->And(bits2);
      cout << "Результат AND: ";
      PrintBitSequence(res);
      delete res;
    } else if (choice == 4) {
      BitSequence *res = bits1->Or(bits2);
      cout << "Результат OR: ";
      PrintBitSequence(res);
      delete res;
    } else if (choice == 5) {
      BitSequence *res = bits1->Not();
      cout << "Результат NOT: ";
      PrintBitSequence(res);
      delete res;
    }
  }

  delete bits1;
  delete bits2;
}

// Запуск главного меню программы
void RunMenu() {
  int main_choice = -1;

  while (main_choice != 0) {
    cout << "\nГЛАВНОЕ МЕНЮ\n";
    cout << "1. MutableArraySequence\n";
    cout << "2. MutableListSequence\n";
    cout << "3. ImmutableArraySequence\n";
    cout << "4. ImmutableListSequence\n";
    cout << "5. BitSequence\n";
    cout << "6. Запустить все автотесты\n";
    cout << "0. Выход из программы\n";
    cout << "\n";
    main_choice = SafeReadInt("Введи номер пункта: ");

    Sequence<int> *s = nullptr;
    switch (main_choice) {
    case 1:
      s = new MutableArraySequence<int>();
      TestManualSequence(s, "MutableArraySequence", true);
      delete s;
      break;
    case 2:
      s = new MutableListSequence<int>();
      TestManualSequence(s, "MutableListSequence", true);
      delete s;
      break;
    case 3:
      s = new ImmutableArraySequence<int>();
      TestManualSequence(s, "ImmutableArraySequence", false);
      delete s;
      break;
    case 4:
      s = new ImmutableListSequence<int>();
      TestManualSequence(s, "ImmutableListSequence", false);
      delete s;
      break;
    case 5:
      TestBitSequence();
      break;
    case 6:
      run_all_tests();
      break;
    case 0:
      break;
    default:
      cout << "Неверный ввод!\n";
    }
  }
}