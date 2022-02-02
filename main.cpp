#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <stdexcept>

std::vector<int> inputArray();
int minimumSwaps(std::vector<int>& q);

int main()
{
    std::vector<int> inputVector = inputArray();
    int a = minimumSwaps(inputVector);
    return 0;
}

std::vector<int> inputArray() {
    int n = 0, temp = 0; std::vector<int> q;
    std::cout << "Input array size: " << std::endl; std::cin >> n;
    std::cout << "Input array integers" << std::endl;
    for (int i = 0; i < n; i++) {
        std::cin >> temp; q.push_back(temp);
    }
    temp = q.size();
    try {
        if (temp < 1 || temp > 100000 || std::cin.fail()) {
            throw std::invalid_argument("Too large queue");
        }
    }
    catch (std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }
    return q;
};

int minimumSwaps(std::vector<int>& q) {
    int j,cycle_size, minimumAmountOfSwaps = 0; std::map<int, int> qPos;

    //wektor, kt�ry pozwoli sprawdzi� czy dany element by� odwiedzany
    std::vector<bool> visitedElements(q.size(), false);

    //wstawianie element�w do mapy, celem sortowania element�w po kluczu. 
    //Chodzi o to, by po sortowaniu indexy zosta�y niezmienione wzgl�dem pocz�tku
    for (j = 0; j < static_cast<int> (q.size()); j++) {
        qPos.insert(std::pair<int, int>(q[j], j));
    }

    for (int i = 0; i < static_cast<int> (q.size()); i++) {

        //je�li w danym elemencie ju� byli�my, albo warto�� elementu pokrywa si� z aktualnym elementem iteracji
        if (visitedElements[i] || (qPos[i+1]) == i+1) {
            continue;
        } 
        cycle_size = 0; j = i;
        //pocz�wszy od i-tej iteracji traktujemy wartos� elementu jako index dla nast�pnego.
        while (!visitedElements[j]) {
            visitedElements[j] = 1;
            j = qPos[j+1];
            cycle_size++;
        }
        if (cycle_size > 0) {
            minimumAmountOfSwaps += cycle_size - 1; 
        }
    }
    std::cout << minimumAmountOfSwaps;
    return minimumAmountOfSwaps;
}