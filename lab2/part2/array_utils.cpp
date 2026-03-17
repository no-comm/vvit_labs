#include "array_utils.h"

#include <QListWidget>

#include <random>

using namespace std;

bool generateArray(vector<int>& numbers, int n, int left, int right) {
    if (n <= 0 || left > right) {
        return false;
    }

    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<int> distribution(left, right);

    numbers.clear();
    for (int i = 0; i < n; ++i) {
        numbers.push_back(distribution(generator));
    }

    return true;
}

bool buildResultArray(const vector<int>& source, vector<int>& result, int& lastOdd) {
    bool hasEven = false;
    bool hasOdd = false;

    for (int value : source) {
        if (value % 2 == 0) {
            hasEven = true;
        } else {
            hasOdd = true;
            lastOdd = value;
        }
    }

    if (!hasEven || !hasOdd) {
        result.clear();
        return false;
    }

    result.clear();
    for (int value : source) {
        if (value % 2 == 0) {
            result.push_back(value - lastOdd);
        }
    }

    return true;
}

void outputArray(const vector<int>& numbers, QListWidget* listWidget) {
    listWidget->clear();

    for (int value : numbers) {
        listWidget->addItem(QString::number(value));
    }
}
