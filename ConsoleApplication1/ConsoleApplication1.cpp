#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <chrono>
#include <thread>
#include <numeric>

using namespace std;

// Constants
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
int ARRAY_SIZE = 100; // Updated to allow user input
const int BAR_WIDTH = static_cast<int>(static_cast<float>(WINDOW_WIDTH) / ARRAY_SIZE);

// Function to draw bars representing the elements of the array
void drawBars(sf::RenderWindow& window, const vector<int>& array) {
    window.clear();

    for (int i = 0; i < ARRAY_SIZE; ++i) {
        sf::RectangleShape rect(sf::Vector2f(BAR_WIDTH, array[i]));
        rect.setPosition(i * BAR_WIDTH, WINDOW_HEIGHT - array[i]);
        rect.setFillColor(sf::Color::Blue);
        window.draw(rect);
    }

    window.display();
}

// Function to ask user for array size
void promptArraySize() {
    cout << "Enter the size of the array: ";
    cin >> ARRAY_SIZE;
    // Update BAR_WIDTH after ARRAY_SIZE changes
    const int BAR_WIDTH = static_cast<int>(static_cast<float>(WINDOW_WIDTH) / ARRAY_SIZE);
}

// Bubble Sort Algorithm Visualize code
void bubbleSort(vector<int>& array, sf::RenderWindow& window) {
    for (int i = 0; i < ARRAY_SIZE - 1; i++) {
        for (int j = 0; j < ARRAY_SIZE - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                swap(array[j], array[j + 1]);
                drawBars(window, array);
                this_thread::sleep_for(chrono::milliseconds(10)); // Delay for visualization
            }
        }
    }
}

// Selection Sort Algorithm Visualize code
void selectionSort(vector<int>& array, sf::RenderWindow& window) {
    for (int i = 0; i < ARRAY_SIZE - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < ARRAY_SIZE; j++) {
            if (array[j] < array[minIndex]) {
                minIndex = j;
            }
        }
        swap(array[i], array[minIndex]);
        drawBars(window, array);
        this_thread::sleep_for(chrono::milliseconds(10)); // Delay for visualization
    }
}

// Insertion Sort Algorithm visualize code
void insertionSort(vector<int>& array, sf::RenderWindow& window) {
    for (int i = 1; i < ARRAY_SIZE; i++) {
        int key = array[i];
        int j = i - 1;
        while (j >= 0 && array[j] > key) {
            array[j + 1] = array[j];
            j = j - 1;
        }
        array[j + 1] = key;
        drawBars(window, array);
        this_thread::sleep_for(chrono::milliseconds(10)); // Delay for visualization
    }
}

// Merge Sort Algorithm visualize code
void merge(vector<int>& array, int left, int middle, int right, sf::RenderWindow& window) {
    int n1 = middle - left + 1;
    int n2 = right - middle;

    vector<int> leftArray(n1);
    vector<int> rightArray(n2);

    for (int i = 0; i < n1; i++)
        leftArray[i] = array[left + i];
    for (int j = 0; j < n2; ++j)
        rightArray[j] = array[middle + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArray[i] <= rightArray[j]) {
            array[k] = leftArray[i];
            i++;
        }
        else {
            array[k] = rightArray[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        array[k] = leftArray[i];
        i++;
        k++;
    }

    while (j < n2) {
        array[k] = rightArray[j];
        j++;
        k++;
    }

    drawBars(window, array);
    this_thread::sleep_for(chrono::milliseconds(10)); // Delay for visualization
}

void mergeSort(vector<int>& array, int left, int right, sf::RenderWindow& window) {
    if (left < right) {
        int middle = left + (right - left) / 2;
        mergeSort(array, left, middle, window);
        mergeSort(array, middle + 1, right, window);
        merge(array, left, middle, right, window);
    }
}

// Quick Sort Algorithm visualize code
int partition(vector<int>& array, int low, int high, sf::RenderWindow& window) {
    int pivot = array[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (array[j] <= pivot) {
            i++;
            swap(array[i], array[j]);
        }
    }
    swap(array[i + 1], array[high]);
    drawBars(window, array);
    this_thread::sleep_for(chrono::milliseconds(10)); // Delay for visualization
    return i + 1;
}

void quickSort(vector<int>& array, int low, int high, sf::RenderWindow& window) {
    if (low < high) {
        int pi = partition(array, low, high, window);
        quickSort(array, low, pi - 1, window);
        quickSort(array, pi + 1, high, window);
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Sorting Algorithm Visualizer");

    vector<int> array(ARRAY_SIZE);
    iota(array.begin(), array.end(), 1); // Fill the array with numbers 1 to ARRAY_SIZE
    random_device rd;
    mt19937 g(rd());
    shuffle(array.begin(), array.end(), g); // Shuffle the array

    promptArraySize(); // Prompt the user for the size of the array

    cout << "Select sorting algorithm to visualize:\n";
    cout << "1. Bubble Sort\n";
    cout << "2. Selection Sort\n";
    cout << "3. Insertion Sort\n";
    cout << "4. Merge Sort\n";
    cout << "5. Quick Sort\n";

    int choice;
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
    case 1:
        bubbleSort(array, window);
        break;
    case 2:
        selectionSort(array, window);
        break;
    case 3:
        insertionSort(array, window);
        break;
    case 4:
        mergeSort(array, 0, ARRAY_SIZE - 1, window);
        break;
    case 5:
        quickSort(array, 0, ARRAY_SIZE - 1, window);
        break;
    default:
        cout << "Invalid choice!\n";
        return 1;
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }

    return 0;
}
