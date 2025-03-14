﻿//встановлюємо бібліотеки
#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <windows.h>

using namespace std;
//структура
struct Question {
    string text;
    vector<string> options;
    int correctAnswer;
};

//підключення кольорів для вінди
void setConsoleColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
//відповідає за красивий інтерфейс
void printLine(int width) {
    cout << "+";
    for (int i = 0; i < width; i++) cout << "-";
    cout << "+" << endl;
}
//відповідає за красивий інтерфейс
void printCentered(const string& text, int width) {
    int padding = (width - text.length()) / 2;
    cout << "|";
    for (int i = 0; i < padding; i++) cout << " ";
    cout << text;
    for (int i = 0; i < padding; i++) cout << " ";
    if (text.length() % 2 != width % 2) cout << " ";
    cout << "|" << endl;
}
//функція питаннь
void askQuestion(const Question& q, int& score, int index) {
    const int width = 60;
    printLine(width);
    printCentered(" ПИТАННЯ #" + to_string(index + 1), width);
    printLine(width);

    setConsoleColor(14);
    cout << q.text << endl;
    setConsoleColor(7);

    for (size_t i = 0; i < q.options.size(); i++) {
        cout << " " << i + 1 << ") " << q.options[i] << endl;
    }

    int answer;
    //обробник помилок відповіді
    while (true) {
        cout << "▶️ Ваша відповідь: ";
        if (!(cin >> answer)) {
            cin.clear();
            cin.ignore(10000, '\n');
            setConsoleColor(12);
            cout << "🚨 ПОМИЛКА! Введіть число! Спробуйте ще раз.\n";
            setConsoleColor(7);
            continue;
        }
        if (answer < 1 || answer > static_cast<int>(q.options.size())) {
            setConsoleColor(12);
            cout << "🚨 Неправильний номер! Введіть значення від 1 до " << q.options.size() << ". Спробуйте ще раз.\n";
            setConsoleColor(7);
            continue;
        }
        break;
    }

    if (answer == q.correctAnswer) {
        setConsoleColor(10);
        cout << "✅ Правильно!\n";
        score++;
    }
    else {
        setConsoleColor(12);
        cout << "❌ Неправильно! Вірна відповідь: " << q.correctAnswer << " - " << q.options[q.correctAnswer - 1] << endl;
    }

    setConsoleColor(7);
    cout << endl;
}
//виведення результатів вікторини 
void printResult(int score, int total) {
    printLine(60);
    printCentered("📊 РЕЗУЛЬТАТ", 60);
    printLine(60);
    setConsoleColor(11);
    cout << "🩵 Ваш підсумковий рахунок: " << score << " з " << total << endl;
    setConsoleColor(7);

    cout << "\nВаш рівень підготовки: ";
    if (score < 5) {
        setConsoleColor(12);
        cout << "Ти - шось середнє між санітаром і коматозною бабкою." << endl;
    }
    else if (score < 10) {
        setConsoleColor(14);
        cout << "Ти, сігма - фельдшер." << endl;
    }
    else if (score < 15) {
        setConsoleColor(10);
        cout << "Досить непогано! Ти - лікар швидкої допомоги." << endl;
    }
    else {
        setConsoleColor(9);
        cout << "Доктор Хаус, ти?" << endl;
    }
    setConsoleColor(7);
}

int main() {
    system("chcp 1251 > null");
//масив з питаннями, відповідями та правильними варіантами відповіді.
    vector<Question> quiz = {
{"Що таке тріаж у медицині катастроф?",
 {"Сортування постраждалих", "Зупинка кровотечі", "Відновлення дихання", "Надання психологічної допомоги"}, 1},

{"Що роблять у першу чергу при зупинці серця?",
 {"Масаж серця", "Штучне дихання", "Перевіряють пульс", "Викликають лікаря"}, 1},

{"Який колір маркування отримують постраждалі з легкими травмами під час триажу?",
 {"Червоний", "Жовтий", "Зелений", "Чорний"}, 3},

{"Яке головне завдання першої медичної допомоги при сильній кровотечі?",
 {"Дати води постраждалому", "Накласти джгут або тугу пов'язку", "Заспокоїти потерпілого", "Викликати швидку допомогу"}, 2},

{"Який головний симптом шоку?",
 {"Висока температура", "Сильний біль у грудях", "Блідість, холодний піт, слабкість", "Нудота"}, 3},

{"Що таке гіпотермія?",
 {"Перегрів тіла", "Переохолодження тіла", "Зневоднення", "Порушення дихання"}, 2},

{"Що потрібно зробити при опіках першого ступеня?",
 {"Прикласти лід", "Змазати олією", "Промити холодною водою", "Протерти спиртом"}, 3},

{"Який з цих факторів найнебезпечніший при переломі відкритого типу?",
 {"Біль", "Інфекція", "Синець", "Оніміння"}, 2},

{"Що слід зробити при ураженні електричним струмом?",
 {"Доторкнутися до потерпілого", "Негайно відірвати його від джерела струму", "Знеструмити джерело і викликати швидку", "Дати води"}, 3},

{"Яку допомогу надають при сонячному ударі?",
 {"Дати гарячий чай", "Перемістити в тінь, охолодити тіло", "Застосувати зігріваючий компрес", "Дати солодке"}, 2},

{"Що потрібно зробити при потраплянні стороннього предмета в дихальні шляхи?",
 {"Викликати швидку і чекати", "Нахилити потерпілого вперед і поплескати по спині", "Зробити штучне дихання", "Напоїти водою"}, 2},

{"Який головний спосіб уникнути переохолодження у холодну пору?",
 {"Одягати багатошаровий одяг", "Пити алкоголь", "Частіше бігати", "Дихати через рот"}, 1},

{"Що заборонено робити при сильній кровотечі?",
 {"Піднімати поранену кінцівку", "Прикладати холод", "Видаляти сторонні предмети з рани", "Накладати тугу пов’язку"}, 3},

{"Що є першою ознакою перелому кістки?",
 {"Підвищення температури", "Набряк і сильний біль", "Почервоніння шкіри", "Запаморочення"}, 2},

{"Який тип опіків вважається найважчим?",
 {"Першого ступеня", "Другого ступеня", "Третього ступеня", "Сонячний"}, 3},

{"Що таке компресійна травма?",
 {"Травма, спричинена сильним ударом", "Здавлення тканин важким предметом", "Перелом кінцівки", "Глибоке поранення"}, 2},

{"Як допомогти людині, яка втратила свідомість?",
 {"Дати нашатирний спирт", "Підняти ноги вище голови", "Полити холодною водою", "Зробити штучне дихання"}, 2},

{"Що робити при підозрі на інсульт?",
 {"Дати таблетку від головного болю", "Вкласти постраждалого і викликати швидку", "Змусити рухати ураженою кінцівкою", "Дати склянку води"}, 2},

{"Що перш за все слід зробити при вивиху суглоба?",
 {"Спробувати вправити самостійно", "Зафіксувати суглоб і звернутися до лікаря", "Прикласти тепло", "Масажувати місце травми"}, 2},

{"Що робити при масовому ураженні людей в результаті катастрофи?",
 {"Негайно почати евакуацію", "Почати сортування постраждалих", "Дочекатися швидкої допомоги", "Накласти пов’язки всім постраждалим"}, 2}
    };

    int score = 0;
    printLine(60);
    printCentered("🩺 ТЕСТ З МЕДИЦИНИ КАТАСТРОФ 🏥", 60);
    printLine(60);

    //цикл для питаннь
    for (size_t i = 0; i < quiz.size(); i++) {
        askQuestion(quiz[i], score, i);
    }

    printResult(score, quiz.size());

    return 0;
}