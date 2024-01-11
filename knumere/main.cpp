#include <iostream>
#include <fstream>
#include <deque>

using namespace std;

ifstream fin("knumere.in");
ofstream fout("knumere.out");

deque<int> indexDeque;
int arraySize, windowSize, differences[1000001], minMaxDifference, currentElement, nextElement;

int main()
{
    fin >> arraySize >> windowSize;
    windowSize = arraySize - windowSize - 1;
    fin >> currentElement;
    minMaxDifference = 2e9;

    for (int currentIndex = 2; currentIndex <= arraySize; currentIndex++)
    {
        fin >> nextElement;
        differences[currentIndex - 1] = nextElement - currentElement;

        // Maintain a decreasing order deque of indices based on differences
        while (!indexDeque.empty() && differences[indexDeque.back()] <= differences[currentIndex - 1])
            indexDeque.pop_back();

        indexDeque.push_back(currentIndex - 1);

        // Remove indices outside the current window
        if (indexDeque.front() <= currentIndex - 1 - windowSize)
            indexDeque.pop_front();

        // Update minMaxDifference if the current window is reached
        if (currentIndex - 1 >= windowSize)
            minMaxDifference = min(minMaxDifference, differences[indexDeque.front()]);

        currentElement = nextElement;
    }

    fout << minMaxDifference;

    return 0;
}
