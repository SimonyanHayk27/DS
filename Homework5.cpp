#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <list>

template<typename T>
class PriorityQueue {
private:
    std::vector<T> heap;
    void heapifyUp() {
        int index = static_cast<int>(heap.size()) - 1;
        while (index > 0 && heap[parent(index)] < heap[index]) {
            std::swap(heap[index], heap[parent(index)]);
            index = parent(index);
        }
    }

   void heapifyDown(int index) {
    while (leftChild(index) < static_cast<int>(heap.size())) {
        int maxChild = getMaxChild(index);
        if (heap[index] < heap[maxChild]) {
            std::swap(heap[index], heap[maxChild]);
            index = maxChild;
        } else {
            break;
        }
    }
}


    int parent(int i) const {
        return (i - 1) / 2;
    }

    int leftChild(int i) const {
        return 2 * i + 1;
    }

    int rightChild(int i) const {
        return 2 * i + 2;
    }

    int getMaxChild(int i) const {
        int left = leftChild(i);
        int right = rightChild(i);

        if (right < static_cast<int>(heap.size()) && heap[right] > heap[left]) {
            return right;
        } else {
            return left;
        }
    }

public:
    PriorityQueue() = default;

    template<typename InputIt>
PriorityQueue(InputIt first, InputIt last) : heap(first, last) {
    for (int i = static_cast<int>(heap.size()) / 2 - 1; i >= 0; --i) {
        heapifyDown(i);
    }
}


    bool empty() const {
        return heap.empty();
    }

    size_t size() const {
        return heap.size();
    }

    void push(const T &value) {
        heap.push_back(value);
        heapifyUp();
    }

    void pop() {
    if (!empty()) {
        std::swap(heap.front(), heap.back());
        heap.pop_back();
        if (!empty()) {
            heapifyDown(0);
        }
    }
}


    const T &top() const {
        return heap.front();
    }
};

struct Point {
    int x{};
    int y{};

    double dist() const {
        return std::sqrt(x * x + y * y);
    }

    friend bool operator<(const Point &lhs, const Point &rhs) {
        return lhs.dist() < rhs.dist();
    }

    friend bool operator>(const Point &lhs, const Point &rhs) {
        return lhs.dist() > rhs.dist();
    }
};

std::vector<std::list<int>> mergeKLists(const std::vector<std::list<int>> &lists) {
    PriorityQueue<int> minHeap;

    for (const auto &lst : lists) {
        for (int value : lst) {
            minHeap.push(value);
        }
    }

    std::vector<std::list<int>> result;
    while (!minHeap.empty()) {
        result.emplace_back(1, minHeap.top());
        minHeap.pop();
    }

    return result;
}

int minStonesLeft(const std::vector<int> &piles, int k) {
    PriorityQueue<int> maxHeap(piles.begin(), piles.end());

    for (int i = 0; i < k; ++i) {
        int maxPile = maxHeap.top();
        maxHeap.pop();
        int newPile = maxPile - maxPile / 2;
        maxHeap.push(newPile);
    }

    int result = 0;
    while (!maxHeap.empty()) {
        result += maxHeap.top();
        maxHeap.pop();
    }

    return result;
}

int furthestBuilding(std::vector<int> &heights, int bricks, int ladders) {
    const int n = static_cast<int>(heights.size());

    PriorityQueue<int> maxHeap;

    for (int i = 0; i < n - 1; ++i) {
        int diff = heights[i + 1] - heights[i];

        if (diff > 0) {
            if (ladders > 0) {
                maxHeap.push(diff);
                --ladders;
            } else if (!maxHeap.empty() && diff > maxHeap.top()) {
                bricks -= maxHeap.top();
                maxHeap.pop();
                maxHeap.push(diff);
            } else {
                bricks -= diff;
            }

            if (bricks < 0) {
                return i;
            }
        }
    }

    return n - 1;
}

std::vector<Point> kClosestPoints(std::vector<Point> &points, int k) {
    PriorityQueue<Point> minHeap(points.begin(), points.end());

    std::vector<Point> result;
    for (int i = 0; i < k; ++i) {
        result.push_back(minHeap.top());
        minHeap.pop();
    }

    return result;
}

int main() {
    std::vector<int> piles1 = {5, 4, 9};
    int k1 = 2;
    std::cout << minStonesLeft(piles1, k1) << std::endl;  // Output: 12

    std::vector<int> piles2 = {4, 3, 6, 7};
    int k2 = 3;
    std::cout << minStonesLeft(piles2, k2) << std::endl;  // Output: 12

    std::vector<int> heights = {4, 2, 7, 6, 9, 14, 12};
    int bricks = 5;
    int ladders = 1;
    std::cout << furthestBuilding(heights, bricks, ladders) << std::endl;  // Output: 4

    std::vector<std::list<int>> lists = {{1, 4, 5}, {1, 3, 4}, {2, 6}};
    std::vector<std::list<int>> mergedList = mergeKLists(lists);
    for (const auto &lst : mergedList) {
        for (int value : lst) {
            std::cout << value << " ";
        }
    }
    std::cout << std::endl;  // Output: 1 1 2 3 4 4 5 6

    std::vector<Point> points = {{3, 3}, {5, -1}, {-2, 4}};
    int k3 = 2;
    std::vector<Point> closestPoints = kClosestPoints(points, k3);
    for (const auto &point : closestPoints) {
        std::cout << "[" << point.x << "," << point.y << "] ";
    }
    std::cout << std::endl;  // Output: [3,3] [-2,4]

    return 0;
}
