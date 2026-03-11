#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include "sorter.hpp"
#include "console_ui.hpp"
#include "logger.hpp"

// Алгоритмы
#include "bubble_sort.hpp"
#include "insertion_sort.hpp"
#include "selection_sort.hpp"
#include "quick_sort.hpp"
#include "merge_sort.hpp"
#include "heap_sort.hpp"
#include "shell_sort.hpp"
#include "counting_sort.hpp"

int main() {
    ui::ConsoleUI ui;
    Logger logger("results.csv");
    
    ui.clearScreen();
    ui.showMenu();
    
    // Выбор размера массива
    auto sizeOpt = ui.getArraySize();
    if (!sizeOpt) {
        ui.printMessage("Invalid array size!");
        return 1;
    }
    int size = *sizeOpt;
    
    // Генерация массива
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(ui::MIN_VALUE, ui::MAX_VALUE);
    
    std::vector<int> original(size);
    for (int i = 0; i < size; ++i) {
        original[i] = dist(gen);
    }
    
    // Выбор алгоритма
    auto algoOpt = ui.getAlgorithmChoice();
    if (!algoOpt || *algoOpt == ui::MenuOption::Exit) {
        ui.printMessage("Goodbye!");
        return 0;
    }
    
    // Создание сортировщика
    std::unique_ptr<ISorter> sorter;
    switch (*algoOpt) {
        case ui::MenuOption::BubbleSort:
            sorter = std::make_unique<BubbleSort>();
            break;
        case ui::MenuOption::InsertionSort:
            sorter = std::make_unique<InsertionSort>();
            break;
        case ui::MenuOption::SelectionSort:
            sorter = std::make_unique<SelectionSort>();
            break;
        case ui::MenuOption::QuickSort:
            sorter = std::make_unique<QuickSort>();
            break;
        case ui::MenuOption::MergeSort:
            sorter = std::make_unique<MergeSort>();
            break;
        case ui::MenuOption::HeapSort:
            sorter = std::make_unique<HeapSort>();
            break;
        case ui::MenuOption::ShellSort:
            sorter = std::make_unique<ShellSort>();
            break;
        case ui::MenuOption::CountingSort:
            sorter = std::make_unique<CountingSort>();
            break;
        default:
            ui.printMessage("Invalid algorithm!");
            return 1;
    }
    
    // Запуск сортировки с анимацией
    std::vector<int> arr = original;
    
    auto startTime = std::chrono::high_resolution_clock::now();
    
    SortStats stats = sorter->sort(arr, 
        [&](const std::vector<int>& a, int i, int j) {
            ui.renderArray(a, i, j);
        }
    );
    
    auto endTime = std::chrono::high_resolution_clock::now();
    stats.duration_ms = std::chrono::duration<double, std::milli>(endTime - startTime).count();
    
    // Показ результатов
    ui.showStats(sorter->getName(), stats, original, arr);
    
    // Логирование
    logger.logResult(sorter->getName(), stats);
    
    ui.waitForEnter();
    
    return 0;
}
