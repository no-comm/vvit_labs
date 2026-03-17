#pragma once

#include <vector>

class QListWidget;

bool generateArray(std::vector<int>& numbers, int n, int left, int right);
bool buildResultArray(const std::vector<int>& source, std::vector<int>& result, int& lastOdd);
void outputArray(const std::vector<int>& numbers, QListWidget* listWidget);
