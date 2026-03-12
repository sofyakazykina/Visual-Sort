#include <iostream>
#include <vector>
#include <random>
#include <variant>
#include "sorter.hpp"
#include "console_ui.hpp"
#include "logger.hpp"

#include "bubble_sort.hpp"
#include "insertion_sort.hpp"
#include "selection_sort.hpp"
#include "quick_sort.hpp"
#include "merge_sort.hpp"
#include "heap_sort.hpp"
#include "shell_sort.hpp"
#include "counting_sort.hpp"

void printSortResult(const SortResult& result) {
    std::visit([](auto&& arg) {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, SortStats>) {
            std::cout << "Sort completed: " << arg.comparisons << " comparisons\n";
        } else if constexpr (std::is_same_v<T, std::string>) {
            std::cout << "Sort failed: " << arg << "\n";
        }
    }, result);
}

int main() {
    try {
        ui::ConsoleUI ui;
        Logger logger("results.csv");

        ui.clearScreen();
        ui.showMenu();

        std::optional<int> sizeOpt;
        try {
            sizeOpt = ui.getArraySize();
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << "\n";
            ui.printMessage("Using default array size: 10");
            sizeOpt = 10;
        }

        if (!sizeOpt) {
            ui.printMessage("Invalid array size!");
            return 1;
        }
        int size = *sizeOpt;

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(ui::MIN_VALUE, ui::MAX_VALUE);

        std::vector<int> original(size);
        for (int i = 0; i < size; ++i) {
            original[i] = dist(gen);
        }

        std::optional<ui::MenuOption> algoOpt;
        try {
            algoOpt = ui.getAlgorithmChoice();
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << "\n";
            ui.printMessage("Using default algorithm: Bubble Sort");
            algoOpt = ui::MenuOption::BubbleSort;
        }

        if (!algoOpt || *algoOpt == ui::MenuOption::Exit) {
            ui.printMessage("Goodbye!");
            return 0;
        }

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

        std::vector<int> arr = original;

        auto startTime = std::chrono::high_resolution_clock::now();

        SortResult result;
        try {
            SortStats stats = sorter->sort(arr,
                                           [&](const std::vector<int>& a, int i, int j) {
                                               ui.renderArray(a, i, j);
                                           }
            );
            result = stats;
        } catch (const std::exception& e) {
            result = std::string("Sorting failed: ") + e.what();
        }

        auto endTime = std::chrono::high_resolution_clock::now();

        printSortResult(result);

        SortStats stats;
        if (std::holds_alternative<SortStats>(result)) {
            stats = std::get<SortStats>(result);
            stats.duration_ms = std::chrono::duration<double, std::milli>(endTime - startTime).count();

            ui.showStats(sorter->getName(), stats, original, arr);

            logger.logResult(sorter->getName(), stats);
        }


    } catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Unknown fatal error occurred!" << std::endl;
        return 1;
    }

    return 0;
}
