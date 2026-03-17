#pragma once

#include <QWidget>

#include <vector>

class QLabel;
class QLineEdit;
class QListWidget;
class QPushButton;

class MainWindow : public QWidget {
public:
    MainWindow();

private:
    bool readInput(int& n, int& left, int& right);
    void updateStatus(const QString& text, bool isError);
    void onGenerateClicked();
    void onSolveClicked();
    void onClearClicked();

    QLineEdit* editSize;
    QLineEdit* editLeft;
    QLineEdit* editRight;
    QListWidget* sourceListWidget;
    QListWidget* resultListWidget;
    QLabel* labelLastOdd;
    QLabel* statusLabel;
    QPushButton* buttonGenerate;
    QPushButton* buttonSolve;
    QPushButton* buttonClear;
    QPushButton* buttonExit;

    std::vector<int> sourceArray;
    std::vector<int> resultArray;
};
