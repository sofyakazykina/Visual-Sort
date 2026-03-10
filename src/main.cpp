#include "console_ui.hpp"
#include "bubble_sort.hpp"
#include "insertion_sort.hpp"
#include "selection_sort.hpp"
#include "quick_sort.hpp"
#include "merge_sort.hpp"
#include "heap_sort.hpp"
#include "shell_sort.hpp"
#include "counting_sort.hpp"

#include <iostream>
#include <memory>
#include <vector>
#include <random>

std::vector<int> generateArray(int size) {
    std::vector<int> arr(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(ui::MIN_VALUE, ui::MAX_VALUE);
    for (int& v : arr) v = distrib(gen);
    return arr;
}

std::unique_ptr<ISorter> createSorter(ui::MenuOption option) {
    switch (option) {
        case ui::MenuOption::BubbleSort:    return std::make_unique<BubbleSort>();
        case ui::MenuOption::InsertionSort: return std::make_unique<InsertionSort>();
        case ui::MenuOption::SelectionSort: return std::make_unique<SelectionSort>();
        case ui::MenuOption::QuickSort:     return std::make_unique<QuickSort>();
        case ui::MenuOption::MergeSort:     return std::make_unique<MergeSort>();
        case ui::MenuOption::HeapSort:      return std::make_unique<HeapSort>();
        case ui::MenuOption::ShellSort:     return std::make_unique<ShellSort>();
        case ui::MenuOption::CountingSort:  return std::make_unique<CountingSort>();
        default: return nullptr;
    }
}

int main() {
    ui::ConsoleUI ui;
    std::cout << "\nWelcome to Visual Sort!\n";
    ui.waitForEnter();

    while (true) {
        ui.clearScreen();
        ui.showMenu();

        auto choiceOpt = ui.getAlgorithmChoice();
        if (!choiceOpt) continue;

        if (*choiceOpt == ui::MenuOption::Exit) {
            std::cout << "\nGoodbye!\n";
            break;
        }

        auto sizeOpt = ui.getArraySize();
        if (!sizeOpt) { ui.waitForEnter(); continue; }

        std::vector<int> data = generateArray(*sizeOpt);
        std::vector<int> original = data;

        auto sorter = createSorter(*choiceOpt);
        if (!sorter) { ui.printMessage("Error!"); ui.waitForEnter(); continue; }

        ui.clearScreen();
        ui.printMessage("Sorting...\n");

        SortStats stats = sorter->sort(data,
            [&](const std::vector<int>& arr, int i, int j, const std::string& action) {
                ui.renderArray(arr, i, j, action);
            }
        );

        ui.showStats(sorter->getName(), stats, original, data);

        std::cout << "\nSave results: ";
        char save; std::cin >> save;
        if (save == 'y' || save == 'Y') {
            ui.saveResults("results.csv", sorter->getName(), *sizeOpt, stats);
        }

        ui.waitForEnter();
    }
    return 0;
}