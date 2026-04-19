#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// ==============================
// 工具函式
// ==============================
void printArray(const vector<int>& arr) {
    for (int x : arr) {
        cout << x << " ";
    }
    cout << "\n";
}

void printTitle(const string& title) {
    cout << "\n==============================\n";
    cout << title << "\n";
    cout << "==============================\n";
}

// ==============================
// 1. Selection Sort
// ==============================
void selectionSort(vector<int>& arr) {
    int n = arr.size();
    // 1. 外圈從 i = 0 到 n-2
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        // 2. 在未排序區間中找最小值的位置 minIndex
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        // 3. 將 arr[i] 與 arr[minIndex] 交換
        swap(arr[i], arr[minIndex]);
    }
}

// ==============================
// 2. Insertion Sort
// ==============================
void insertionSort(vector<int>& arr) {
    int n = arr.size();
    // 1. 外圈從 i = 1 到 n-1
    for (int i = 1; i < n; i++) {
        // 2. 設 key = arr[i]
        int key = arr[i];
        int j = i - 1;
        
        // 3. 將比 key 大的元素往右移
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        // 4. 把 key 插入正確位置
        arr[j + 1] = key;
    }
}

// ==============================
// 3. Bubble Sort
// ==============================
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        // 1. 每一輪把最大值往右推 (已經推到右邊的不用再比，所以是 n-i-1)
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        // 2. 可使用 swapped 變數判斷是否提早結束
        if (!swapped) {
            break;
        }
    }
}

// ==============================
// 4. Shell Sort
// ==============================
void shellSort(vector<int>& arr) {
    int n = arr.size();

    // 1. gap 先設為 n/2
    // 2. 每次 gap /= 2
    for (int gap = n / 2; gap > 0; gap /= 2) {
        
        // 3. 對每個 gap 做類似 insertion sort
        // 從索引 gap 開始，逐一把元素插入到它所屬的組別中正確的位置
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            
            // 在同一個組別內（索引間距為 gap）往前找，把比 temp 大的往後挪
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            // 把 temp 放入正確的位置
            arr[j] = temp;
        }
    }
}

// ==============================
// 5. Merge Sort
// ==============================
void merge(vector<int>& arr, int left, int mid, int right) {
    // 1. 先建立 leftArr 與 rightArr
    int n1 = mid - left + 1;
    int n2 = right - mid;
    vector<int> leftArr(n1), rightArr(n2);
    
    for (int i = 0; i < n1; i++) leftArr[i] = arr[left + i];
    for (int j = 0; j < n2; j++) rightArr[j] = arr[mid + 1 + j];

    // 2. 比較兩邊元素，小的先放回 arr
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k++] = leftArr[i++];
        } else {
            arr[k++] = rightArr[j++];
        }
    }

    // 3. 最後把剩餘元素補回 arr
    while (i < n1) arr[k++] = leftArr[i++];
    while (j < n2) arr[k++] = rightArr[j++];
}

void mergeSort(vector<int>& arr, int left, int right) {
    // 1. 終止條件：left >= right
    if (left >= right) return;
    
    // 2. 找中間 mid (避免 left + right 溢位)
    int mid = left + (right - left) / 2;
    
    // 3. 遞迴排序左半部
    mergeSort(arr, left, mid);
    // 4. 遞迴排序右半部
    mergeSort(arr, mid + 1, right);
    
    // 5. 呼叫 merge()
    merge(arr, left, mid, right);
}

// ==============================
// 6. Quick Sort
// ==============================
int partitionArray(vector<int>& arr, int low, int high) {
    // 1. pivot = arr[high]
    int pivot = arr[high];
    // 2. i = low - 1 (i 代表目前小於 pivot 的最後一個元素的索引)
    int i = low - 1;
    
    // 3. 掃描 j = low 到 high - 1
    for (int j = low; j < high; j++) {
        // 4. 若 arr[j] < pivot，則交換到左側
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    // 5. 最後將 pivot 放到正確位置 (i+1)
    swap(arr[i + 1], arr[high]);
    
    // 6. 回傳 pivot 的索引
    return i + 1;
}

void quickSort(vector<int>& arr, int low, int high) {
    // 1. 若 low < high
    if (low < high) {
        // 2. 呼叫 partitionArray() 取得分割點
        int pi = partitionArray(arr, low, high);
        
        // 3. 遞迴排序左半部與右半部
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// ==============================
// 7. Radix Sort
// 僅處理非負整數
// ==============================
void countingSortByDigit(vector<int>& arr, int exp) {
    int n = arr.size();
    vector<int> output(n); // 用來暫存排序結果的陣列
    int count[10] = {0};   // 因為數字只有 0~9，長度 10 即可

    // 1. digit = (arr[i] / exp) % 10  count[10] 紀錄各數字出現次數
    for (int i = 0; i < n; i++) {
        int digit = (arr[i] / exp) % 10;
        count[digit]++;
    }

    // 3. 轉成累計次數
    // 這樣 count[i] 的值就會代表：數字 i 在 output 陣列中「最後出現的位置 + 1」
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    // 4. 由右往左放入 output，保持穩定性
    // 從陣列尾端開始掃描原陣列，根據累計次數放進 output，放完後次數減 1
    for (int i = n - 1; i >= 0; i--) {
        int digit = (arr[i] / exp) % 10;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }

    // 5. 將 output 複製回 arr
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
}
void radixSort(vector<int>& arr) {
    int n = arr.size();
    if (n == 0) return;

    // 1. 找出最大值 maxVal
    int maxVal = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > maxVal) {
            maxVal = arr[i];
        }
    }

    // 2. 從個位數開始 exp = 1
    // 3. 每次乘以 10，直到 maxVal / exp == 0
    for (int exp = 1; maxVal / exp > 0; exp *= 10) {
        // 4. 每次呼叫 countingSortByDigit(arr, exp)
        countingSortByDigit(arr, exp);
    }
}
// ==============================
// 8. Heap Sort
// ==============================
void heapify(vector<int>& arr, int n, int i) {
    // 1. largest = i
    int largest = i;
    // 2. left = 2*i + 1, right = 2*i + 2
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // 3. 找出三者中最大者
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    // 4. 若最大者不是 i，交換後遞迴 heapify
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(vector<int>& arr) {
    int n = arr.size();

    // 1. 先建立 max heap (從最後一個非葉子節點開始倒著往上推)
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    // 2. 再把堆頂元素和最後元素交換
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        // 3. 縮小 heap 範圍後重新 heapify (每次範圍少 1，所以傳入 i)
        heapify(arr, i, 0);
    }
}

// ==============================
// 執行單一排序並輸出
// ==============================
void runSingleTest(const string& sortName, void (*sortFunc)(vector<int>&), const vector<int>& data) {
    vector<int> arr = data;
    cout << sortName << "\n";
    cout << "Before: ";
    printArray(arr);
    sortFunc(arr);
    cout << "After : ";
    printArray(arr);
    cout << "\n";
}

void runMergeSortTest(const vector<int>& data) {
    vector<int> arr = data;
    cout << "Merge Sort\n";
    cout << "Before: ";
    printArray(arr);
    mergeSort(arr, 0, arr.size() - 1);
    cout << "After : ";
    printArray(arr);
    cout << "\n";
}

void runQuickSortTest(const vector<int>& data) {
    vector<int> arr = data;
    cout << "Quick Sort\n";
    cout << "Before: ";
    printArray(arr);
    quickSort(arr, 0, arr.size() - 1);
    cout << "After : ";
    printArray(arr);
    cout << "\n";
}

// ==============================
// 主程式
// ==============================
int main() {
    vector<int> bestCase1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    vector<int> bestCase2 = {1, 2, 3, 4, 6, 5, 7, 8, 9, 10};
    vector<int> worstCase1 = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    vector<int> worstCase2 = {100, 90, 80, 70, 60, 50, 40, 30, 20, 10};
    vector<int> radixCase  = {329, 457, 657, 839, 436, 720, 355};
    vector<int> mixedCase  = {42, 17, 93, 8, 23, 55, 4, 16, 77, 61};

    printTitle("Test Data 1: Best Case - Sorted");
    runSingleTest("Selection Sort", selectionSort, bestCase1);
    runSingleTest("Insertion Sort", insertionSort, bestCase1);
    runSingleTest("Bubble Sort", bubbleSort, bestCase1);
    runSingleTest("Shell Sort", shellSort, bestCase1);
    runMergeSortTest(bestCase1);
    runQuickSortTest(bestCase1);
    runSingleTest("Radix Sort", radixSort, bestCase1);
    runSingleTest("Heap Sort", heapSort, bestCase1);

    printTitle("Test Data 2: Near Best Case - Almost Sorted");
    runSingleTest("Selection Sort", selectionSort, bestCase2);
    runSingleTest("Insertion Sort", insertionSort, bestCase2);
    runSingleTest("Bubble Sort", bubbleSort, bestCase2);
    runSingleTest("Shell Sort", shellSort, bestCase2);
    runMergeSortTest(bestCase2);
    runQuickSortTest(bestCase2);
    runSingleTest("Radix Sort", radixSort, bestCase2);
    runSingleTest("Heap Sort", heapSort, bestCase2);

    printTitle("Test Data 3: Worst Case - Reverse Sorted");
    runSingleTest("Selection Sort", selectionSort, worstCase1);
    runSingleTest("Insertion Sort", insertionSort, worstCase1);
    runSingleTest("Bubble Sort", bubbleSort, worstCase1);
    runSingleTest("Shell Sort", shellSort, worstCase1);
    runMergeSortTest(worstCase1);
    runQuickSortTest(worstCase1);
    runSingleTest("Radix Sort", radixSort, worstCase1);
    runSingleTest("Heap Sort", heapSort, worstCase1);

    printTitle("Test Data 4: Another Reverse Large Values");
    runSingleTest("Selection Sort", selectionSort, worstCase2);
    runSingleTest("Insertion Sort", insertionSort, worstCase2);
    runSingleTest("Bubble Sort", bubbleSort, worstCase2);
    runSingleTest("Shell Sort", shellSort, worstCase2);
    runMergeSortTest(worstCase2);
    runQuickSortTest(worstCase2);
    runSingleTest("Radix Sort", radixSort, worstCase2);
    runSingleTest("Heap Sort", heapSort, worstCase2);

    printTitle("Test Data 5: Radix Test");
    runSingleTest("Selection Sort", selectionSort, radixCase);
    runSingleTest("Insertion Sort", insertionSort, radixCase);
    runSingleTest("Bubble Sort", bubbleSort, radixCase);
    runSingleTest("Shell Sort", shellSort, radixCase);
    runMergeSortTest(radixCase);
    runQuickSortTest(radixCase);
    runSingleTest("Radix Sort", radixSort, radixCase);
    runSingleTest("Heap Sort", heapSort, radixCase);

    printTitle("Test Data 6: Random Mixed");
    runSingleTest("Selection Sort", selectionSort, mixedCase);
    runSingleTest("Insertion Sort", insertionSort, mixedCase);
    runSingleTest("Bubble Sort", bubbleSort, mixedCase);
    runSingleTest("Shell Sort", shellSort, mixedCase);
    runMergeSortTest(mixedCase);
    runQuickSortTest(mixedCase);
    runSingleTest("Radix Sort", radixSort, mixedCase);
    runSingleTest("Heap Sort", heapSort, mixedCase);

    return 0;
}
