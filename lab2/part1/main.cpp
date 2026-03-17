#include <iostream>
#include <list>

using namespace std;

bool inputList(list<int>& numbers, int n) {
    cout << "Введите " << n << " целых чисел: ";

    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        if (!cin) {
            return false;
        }
        numbers.push_back(x);
    }

    return true;
}

void findMaxSublist(list<int>& numbers, list<int>::iterator& bestBegin, list<int>::iterator& bestEnd, int& maxSum) {
    auto currentBegin = numbers.begin();
    bestBegin = numbers.begin();
    bestEnd = next(numbers.begin());

    int currentSum = 0;
    maxSum = *numbers.begin();

    for (auto it = numbers.begin(); it != numbers.end(); ++it) {
        if (currentSum <= 0) {
            currentSum = *it;
            currentBegin = it;
        } else {
            currentSum += *it;
        }

        if (currentSum > maxSum) {
            maxSum = currentSum;
            bestBegin = currentBegin;
            bestEnd = next(it);
        }
    }
}

void printList(const list<int>& numbers) {
    for (int x : numbers) {
        cout << x << ' ';
    }
    cout << '\n';
}

void printSublist(list<int>::iterator begin, list<int>::iterator end) {
    for (auto it = begin; it != end; ++it) {
        cout << *it << ' ';
    }
    cout << '\n';
}

int main() {
    setlocale(LC_ALL, "rus");

    int n;
    cout << "Введите количество элементов списка: ";
    cin >> n;

    if (!cin || n <= 0) {
        cout << "Некорректный ввод\n";
        return 1;
    }

    list<int> numbers;
    if (!inputList(numbers, n)) {
        cout << "Некорректный ввод\n";
        return 1;
    }

    auto bestBegin = numbers.begin();
    auto bestEnd = numbers.end();
    int maxSum = 0;
    findMaxSublist(numbers, bestBegin, bestEnd, maxSum);

    cout << "Список: ";
    printList(numbers);
    cout << "Максимальная сумма: " << maxSum << '\n';
    cout << "Подсписок: ";
    printSublist(bestBegin, bestEnd);

    return 0;
}
