#include "console_ui.hpp"
#include <iostream>
#include <memory>
#include <vector>
#include <cstdlib>
#include <chrono>
#include <ctime>
#include <random>

class StubGenerator : public IArrayGenerator {
public:
    std::vector<int> generate(int size, int min_val, int max_val) override {
        std::vector<int> arr(size);
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(min_val, max_val);
        for (int i = 0; i < size; ++i) {
            arr[i] = distrib(gen);
        }
        return arr;
    }
};

class StubSorter : public ISorter {
    std::string name;
public:
    StubSorter(std::string n) : name(std::move(n)) {}
    std::string getName() const override { return name; }

    SortStats sort(std::vector<int>& array, StepCallback callback) override {
        auto start = std::chrono::high_resolution_clock::now();
        long long comparisons = 0;
        long long swaps = 0;

        for (size_t i = 0; i < array.size(); ++i) {
            for (size_t j = 0; j < array.size() - 1 - i; ++j) {
                comparisons++;
                if (callback) callback(array, static_cast<int>(j), static_cast<int>(j + 1));
                if (array[j] > array[j + 1]) {
                    std::swap(array[j], array[j + 1]);
                    swaps++;
                }
            }
        }

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration = end - start;
        return {comparisons, swaps, duration.count()};
    }
};

std::unique_ptr<ISorter> createSorter(ui::MenuOption option) {
    switch (option) {
        case ui::MenuOption::BubbleSort:
            return std::make_unique<StubSorter>("Bubble Sort");
        case ui::MenuOption::InsertionSort:
            return std::make_unique<StubSorter>("Insertion Sort");
        case ui::MenuOption::SelectionSort:
            return std::make_unique<StubSorter>("Selection Sort");
        case ui::MenuOption::QuickSort:
            return std::make_unique<StubSorter>("Quick Sort");
        case ui::MenuOption::MergeSort:
            return std::make_unique<StubSorter>("Merge Sort");
        case ui::MenuOption::HeapSort:
            return std::make_unique<StubSorter>("Heap Sort");
        case ui::MenuOption::ShellSort:
            return std::make_unique<StubSorter>("Shell Sort");
        case ui::MenuOption::CountingSort:
            return std::make_unique<StubSorter>("Counting Sort");
        default:
            return nullptr;
    }
}

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    ui::ConsoleUI ui;
    std::unique_ptr<IArrayGenerator> generator = std::make_unique<StubGenerator>();
    const std::string logFile = "results.csv";

    std::cout << "\nWelcome to Visual Sort!\n";
    ui.waitForEnter();

    while (true) {
        ui.clearScreen();
        ui.showMenu();

        auto choiceOpt = ui.getAlgorithmChoice();
        if (!choiceOpt) continue;

        ui::MenuOption choice = *choiceOpt;
        if (choice == ui::MenuOption::Exit) {
            ui.printMessage("\nGoodbye!");
            break;
        }

        auto sizeOpt = ui.getArraySize();
        if (!sizeOpt) {
            ui.waitForEnter();
            continue;
        }
        int size = *sizeOpt;

        std::vector<int> data = generator->generate(size, ui::MIN_VALUE, ui::MAX_VALUE);
        std::vector<int> originalData = data;

        std::unique_ptr<ISorter> sorter = createSorter(choice);
        if (!sorter) {
            ui.printMessage("Error: Could not create sorter!");
            ui.waitForEnter();
            continue;
        }

        ui.clearScreen();
        ui.printMessage("Sorting in progress...\n");

        SortStats stats = sorter->sort(data,
            [&](const std::vector<int>& arr, int i, int j) {
                ui.clearScreen();
                ui.printMessage("Sorting in progress...\n");
                ui.renderArray(arr, i, j);
            }
        );

        ui.clearScreen();
        ui.showStats(sorter->getName(), stats, originalData, data);

        char saveChoice;
        std::cout << "\nSave results to file? (y/n): ";
        std::cin >> saveChoice;
        if (saveChoice == 'y' || saveChoice == 'Y') {
            ui.saveResults(logFile, sorter->getName(), size, stats);
        }

        ui.waitForEnter();
    }

    return 0;
}