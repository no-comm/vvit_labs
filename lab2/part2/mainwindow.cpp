#include "mainwindow.h"
#include "array_utils.h"

#include <QGridLayout>
#include <QHBoxLayout>
#include <QIntValidator>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>

MainWindow::MainWindow()
    : editSize(new QLineEdit(this)),
      editLeft(new QLineEdit(this)),
      editRight(new QLineEdit(this)),
      sourceListWidget(new QListWidget(this)),
      resultListWidget(new QListWidget(this)),
      labelLastOdd(new QLabel("Последнее нечетное число x: -", this)),
      statusLabel(new QLabel("Введите параметры и сформируйте массив.", this)),
      buttonGenerate(new QPushButton("Сформировать", this)),
      buttonSolve(new QPushButton("Решить", this)),
      buttonClear(new QPushButton("Очистить", this)),
      buttonExit(new QPushButton("Выход", this)) {
    setWindowTitle("Часть 2. Обработка одномерной структуры");
    resize(820, 520);

    auto* mainLayout = new QVBoxLayout(this);
    auto* inputLayout = new QGridLayout();
    auto* listsLayout = new QHBoxLayout();
    auto* buttonsLayout = new QHBoxLayout();

    editSize->setValidator(new QIntValidator(1, 100000, this));
    editLeft->setValidator(new QIntValidator(-1000000, 1000000, this));
    editRight->setValidator(new QIntValidator(-1000000, 1000000, this));

    inputLayout->addWidget(new QLabel("Размер n:", this), 0, 0);
    inputLayout->addWidget(editSize, 0, 1);
    inputLayout->addWidget(new QLabel("Левая граница:", this), 1, 0);
    inputLayout->addWidget(editLeft, 1, 1);
    inputLayout->addWidget(new QLabel("Правая граница:", this), 2, 0);
    inputLayout->addWidget(editRight, 2, 1);

    auto* sourceLayout = new QVBoxLayout();
    sourceLayout->addWidget(new QLabel("Исходный массив", this));
    sourceLayout->addWidget(sourceListWidget);

    auto* resultLayout = new QVBoxLayout();
    resultLayout->addWidget(new QLabel("Новый массив", this));
    resultLayout->addWidget(resultListWidget);

    listsLayout->addLayout(sourceLayout);
    listsLayout->addLayout(resultLayout);

    buttonsLayout->addWidget(buttonGenerate);
    buttonsLayout->addWidget(buttonSolve);
    buttonsLayout->addWidget(buttonClear);
    buttonsLayout->addWidget(buttonExit);

    mainLayout->addLayout(inputLayout);
    mainLayout->addLayout(listsLayout);
    mainLayout->addWidget(labelLastOdd);
    mainLayout->addWidget(statusLabel);
    mainLayout->addLayout(buttonsLayout);

    sourceListWidget->setSelectionMode(QAbstractItemView::NoSelection);
    resultListWidget->setSelectionMode(QAbstractItemView::NoSelection);

    updateStatus("Введите параметры и сформируйте массив.", false);

    connect(buttonGenerate, &QPushButton::clicked, this, [this]() { onGenerateClicked(); });
    connect(buttonSolve, &QPushButton::clicked, this, [this]() { onSolveClicked(); });
    connect(buttonClear, &QPushButton::clicked, this, [this]() { onClearClicked(); });
    connect(buttonExit, &QPushButton::clicked, this, [this]() { close(); });
}

bool MainWindow::readInput(int& n, int& left, int& right) {
    bool okN = false;
    bool okLeft = false;
    bool okRight = false;

    n = editSize->text().toInt(&okN);
    left = editLeft->text().toInt(&okLeft);
    right = editRight->text().toInt(&okRight);

    if (!okN || !okLeft || !okRight) {
        updateStatus("Заполните все поля целыми числами.", true);
        return false;
    }

    if (n <= 0) {
        updateStatus("Размер n должен быть больше нуля.", true);
        return false;
    }

    if (left > right) {
        updateStatus("Левая граница не может быть больше правой.", true);
        return false;
    }

    return true;
}

void MainWindow::updateStatus(const QString& text, bool isError) {
    if (isError) {
        statusLabel->setStyleSheet("background-color: #ffd6d6; color: #7a0000; padding: 6px;");
    } else {
        statusLabel->setStyleSheet("background-color: #dff6dd; color: #124d12; padding: 6px;");
    }

    statusLabel->setText(text);
}

void MainWindow::onGenerateClicked() {
    int n = 0;
    int left = 0;
    int right = 0;

    if (!readInput(n, left, right)) {
        return;
    }

    if (!generateArray(sourceArray, n, left, right)) {
        updateStatus("Не удалось сформировать массив.", true);
        return;
    }

    resultArray.clear();
    outputArray(sourceArray, sourceListWidget);
    resultListWidget->clear();
    labelLastOdd->setText("Последнее нечетное число x: -");
    updateStatus("Исходный массив сформирован случайным образом.", false);
}

void MainWindow::onSolveClicked() {
    if (sourceArray.empty()) {
        updateStatus("Сначала сформируйте исходный массив.", true);
        return;
    }

    int lastOdd = 0;
    if (!buildResultArray(sourceArray, resultArray, lastOdd)) {
        resultListWidget->clear();
        labelLastOdd->setText("Последнее нечетное число x: -");
        updateStatus("В исходном массиве нет одновременно четных и нечетных чисел.", true);
        return;
    }

    outputArray(resultArray, resultListWidget);
    labelLastOdd->setText("Последнее нечетное число x: " + QString::number(lastOdd));
    updateStatus("Новый массив успешно построен.", false);
}

void MainWindow::onClearClicked() {
    editSize->clear();
    editLeft->clear();
    editRight->clear();
    sourceListWidget->clear();
    resultListWidget->clear();
    sourceArray.clear();
    resultArray.clear();
    labelLastOdd->setText("Последнее нечетное число x: -");
    updateStatus("Поля очищены.", false);
}
