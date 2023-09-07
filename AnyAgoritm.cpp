#include <iostream>
#include <random>

std::random_device rd;
std::mt19937 gen(rd());
int* data;

using std::cout;

void printArray(int* origin, size_t size) {
    for (int i = 0; i < size; ++i)
        cout << data[i] << " ";
    cout << std::endl;
}

int random(int low, int high)
{
    std::uniform_int_distribution<> dist(low, high);
    return dist(gen);
}

void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void bubleSort(int* origin, size_t size) { // Пузырьковая сортировка
    for (size_t i = size - 1; i > 0; --i)
        for (size_t j = 0; j < i; ++j)
            if (*(origin + j) > *(origin + j + 1))
                swap((origin + j), (origin + j + 1));
}

void selectSort(int* origin, size_t size) { // Сортировка выбором
    for (size_t i = 0; i < size; ++i) {
        int* minItemInd = origin + i;
        for (size_t j = i; j < size; ++j)
            if (*minItemInd > *(origin + j))
                minItemInd = origin + j;
        if ((origin + i) != minItemInd)
            swap(origin + i, minItemInd);
    }
}

void insertSort(int* origin, size_t size) { // Сортировка вставкой
    for (size_t i = 0; i < size; ++i) {
        int* currentPosition = origin + i;
        for (size_t j = i; j < size; ++j)
            if (*currentPosition > *(origin + j))
                swap(origin + j, currentPosition);           
    }
}

void quickSort(int* origin, size_t startPos, size_t endPos) { // Быстрая сортивка
    if (startPos == endPos)
        return;
    size_t curentPosition = startPos;
    size_t pivotIndex = endPos;
    for (size_t i = startPos; i < endPos; ++i) {
        if (*(origin + i) < *(origin + pivotIndex)) {
            swap(origin + i, origin + curentPosition);
            ++curentPosition;
        }
    }
    swap(origin + pivotIndex, origin + curentPosition);
    //printArray(origin, 100);
    if (curentPosition > startPos)
        quickSort(origin, startPos, curentPosition - 1);
    if (curentPosition < endPos)
        quickSort(origin, curentPosition + 1, endPos);
}

void quickSort(int* origin, size_t size) {
    quickSort(origin, 0, size - 1);
}

void heapify(int* origin, size_t size, size_t rootIndex) {
    size_t largestIndex = rootIndex;
    size_t leftChild = 2 * largestIndex + 1;
    size_t rightChild = 2 * largestIndex + 2;
    if (leftChild < size && *(origin + leftChild) > *(origin + largestIndex)) {
        largestIndex = leftChild;
    }
    if (leftChild < size && *(origin + rightChild) > *(origin + largestIndex)) {
        largestIndex = rightChild;
    }
    if (largestIndex != rootIndex) {
        swap(origin + rootIndex, origin + largestIndex);
        heapify(origin, size, largestIndex);
    }
}

void hepifySort(int* origin, size_t size) {
    for (int i = size / 2 - 1; i >= 0; i--)
        heapify(origin, size, i);
    for (int i = size - 1; i >= 0; i--) {
        swap(origin, origin + i);
        heapify(origin, i, 0);
    }
}

int main()
{
    size_t arraySize = 25;
	data = new int[arraySize];
    for (int i = 0; i < arraySize; ++i) {
        data[i] = random(1, 100);
    }
    printArray(data, arraySize);
    //bubleSort(data, arraySize);
    //selectSort(data, arraySize);
    //insertSort(data, arraySize);
    //quickSort(data, arraySize);
    hepifySort(data, arraySize);

    printArray(data, arraySize);
    delete[] data;
}

