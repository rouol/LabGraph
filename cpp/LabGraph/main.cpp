#include <iostream>
#include <random>
#include "Graph.h"

// random Numeric
template<typename Numeric, typename Generator = std::mt19937>
Numeric Random(Numeric from, Numeric to)
{
    thread_local static Generator gen(std::random_device{}());

    using dist_type = typename std::conditional
        <
        std::is_integral<Numeric>::value
        , std::uniform_int_distribution<Numeric>
        , std::uniform_real_distribution<Numeric>
        >::type;

    thread_local static dist_type dist;

    return dist(gen, typename dist_type::param_type{ from, to });
}

// random seq of Numeric
template<typename T, typename Numeric>
void RandomSequence(Sequence<T>& arr, Numeric from, Numeric to)
{
    for (size_t i = 0; i < arr.GetLength(); i++) {
        arr[i] = Random(from, to);
    }
}

int main()
{
    ///*
    int nVertex;
    std::cin >> nVertex;
    //ArraySequence<int> randomArray = ArraySequence<int>(N);;
    MatrixGraph<int> matrixGraph = MatrixGraph<int>(nVertex);
    
    int requestType, from, to, weight;
    while (true)
    {
        std::cin >> requestType;
        if (requestType == 1) {
            std::cin >> from >> to >> weight;
            matrixGraph.AddArc(from, to);
        }
        else if (requestType == 2) {
            std::cin >> from >> to;
            matrixGraph.RemoveArc(from, to);
        } else if (requestType == 3) {
            std::cin >> from >> to;
            ArraySequence<int> path = matrixGraph.DijkstraSearch(from, to);
            std::cout << &path << std::endl;
        }
    }
    //*/
    

    /*
    int N = 10;
    ArraySequence<int> randomArray = ArraySequence<int>(N);;
    RandomSequence(randomArray, -100, 100);
    std::cout << &randomArray << std::endl;

    MatrixGraph<int> matrixGraph = MatrixGraph<int>(randomArray);

	matrixGraph.AddArc(0, 1);
    matrixGraph.AddArc(0, 2);
    matrixGraph.AddArc(0, 8);
    matrixGraph.AddArc(2, 3);
    matrixGraph.AddArc(2, 5);
    matrixGraph.AddArc(2, 8);
    matrixGraph.AddArc(5, 7);
    ArraySequence<int> neighbors = matrixGraph.Neighbors(0);
	std::cout << &neighbors << std::endl;
    //std::cout << matrixGraph.DijkstraSearch(0, 7) << std::endl;
    ArraySequence<int> path = matrixGraph.DijkstraSearch(0, 7);
    std::cout << &path << std::endl;
    */

}