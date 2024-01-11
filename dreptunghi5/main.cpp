#include <iostream>
#include <fstream>
#include <stack>

using namespace std;

ifstream fin("dreptunghiuri5.in");
ofstream fout("dreptunghiuri5.out");

// Function to set the border of the matrix with 1s
void setBorder(bool matrix[1005][1005], int rows, int cols) {
    for (int i = 0; i <= rows + 1; i++) {
        matrix[i][0] = 1;
        matrix[i][cols + 1] = 1;
    }
    for (int j = 0; j <= cols + 1; j++) {
        matrix[0][j] = 1;
        matrix[rows + 1][j] = 1;
    }
}

int main() {
    int rows, cols;
    fin >> rows >> cols;

    bool matrix[1005][1005];
    stack<pair<int, int>> heightStack;

    setBorder(matrix, rows, cols); // Setting the border of the matrix

    // Reading matrix values from the input file
    for (int i = 1; i <= rows; i++)
        for (int j = 1; j <= cols; j++)
            fin >> matrix[i][j];

    int countRectangles = 0, start, end;
    int heights[1005] = {0};

    for (int i = 1; i <= rows; i++) {
        while (!heightStack.empty())
            heightStack.pop();
        heightStack.push(make_pair(0, 0));
        end = 0;

        for (int j = 1; j <= cols; j++) {
            // Updating heights array for each column based on '0' values
            if (matrix[i][j] != 0)
                heights[j] = 0;
            else
                heights[j]++;

            start = j;
            while (heightStack.top().first > heights[j]) {
                // Calculating and counting the rectangles
                if (end >= heightStack.top().second)
                    countRectangles++;
                start = heightStack.top().second;
                heightStack.pop();
            }

            // Pushing new heights to the stack if not same as top
            if (heightStack.top().first != heights[j])
                heightStack.push(make_pair(heights[j], start));

            // Updating 'end' based on the next row's value
            if (matrix[i + 1][j] != 0)
                end = j;
        }

        // Calculating rectangles from the remaining heights in the stack
        while (heightStack.top().first != 0) {
            if (end >= heightStack.top().second)
                countRectangles++;
            heightStack.pop();
        }
    }

    fout << countRectangles;
    return 0;
}