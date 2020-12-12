#pragma once
#include <map>
#include "Sequence.h"
#include "PriorityQueue.h"

//template <typename T>
//using Matrix = ArraySequence<ArraySequence<T>>;
using MatrixInt = ArraySequence<ArraySequence<int>>;

class Graph {
public:
	virtual ~Graph() {}
	virtual int CountVertex() const = 0;
	virtual void AddArc(int from, int to, int weight = 1) = 0;
	virtual void RemoveArc(int from, int t) = 0;
	virtual int HasArc(int from, int to) const = 0;
};

ArraySequence<int> reconstructPath(int goal, std::map<int, int> cameFrom) {
	ArraySequence<int> path = ArraySequence<int>();
	int current = goal;
	while (cameFrom[current] != -1) {
		path.Append(current);
		current = cameFrom[current];
	}
	path.Append(current);
	return path;
}

template <typename T>
class MatrixGraph : public Graph {
private:

	ArraySequence<T>* Values;
	MatrixInt* AdjacencyMatrix;
	MatrixInt* WeightMatrix;

	int nVertex;

public:

	/*
	MatrixGraph() {
		this->nVertex = 0;
		this->ValueMatrix = new Matrix<T>();
		this->AdjacencyMatrix = new MatrixInt();
		this->WeightMatrix = new MatrixInt();
	}
	*/
	MatrixGraph(int n) {
		this->nVertex = n;
		this->Values = new ArraySequence<T>(n, NULL);
		this->AdjacencyMatrix = new MatrixInt(n, ArraySequence<int>(n, 0));
		this->WeightMatrix = new MatrixInt(n, ArraySequence<int>(n, 0));
	}
	MatrixGraph(ArraySequence<T> arraySequence) {
		this->nVertex = arraySequence.GetLength();
		this->Values = new ArraySequence<T>(arraySequence);
		this->AdjacencyMatrix = new MatrixInt(this->nVertex, ArraySequence<int>(this->nVertex, 0));
		this->WeightMatrix = new MatrixInt(this->nVertex, ArraySequence<int>(this->nVertex, 0));
	}

	int CountVertex() const override {
		return this->nVertex;
	}
	void AddArc(int from, int to, int weight = 1) override {
		// check if can be arc
		if ((0 <= from < this->nVertex) && (0 <= to < this->nVertex)) {
			(*(this->AdjacencyMatrix))[from][to] = 1;
			(*(this->WeightMatrix))[from][to] = weight;
		}
		else {
			throw std::exception("ImpossibleArcException");
		}
	}
	void RemoveArc(int from, int to) override {
		// check if can be arc
		if ((0 <= from < this->nVertex) && (0 <= to < this->nVertex)) {
			(*(this->AdjacencyMatrix))[from][to] = 0;
			(*(this->WeightMatrix))[from][to] = 0;
		}
		else {
			throw std::exception("ImpossibleArcException");
		}
	}
	int HasArc(int from, int to) const override {
		// check if can be arc
		if ((0 <= from && from < this->nVertex) && (0 <= to && to < this->nVertex)) {
			return (*(this->AdjacencyMatrix))[from][to];
		}
		else {
			throw std::exception("ImpossibleArcException");
		}
	}
	ArraySequence<T> Neighbors(int index) const {
		ArraySequence<T> neighbors = ArraySequence<T>();
		ArraySequence<int> line = (*(this->AdjacencyMatrix))[index];
		for (size_t i = 0; i < line.GetLength(); i++) {
			if (line[i] == 1) {
				neighbors.Append((*(this->Values))[i]);
			}
		}
		return neighbors;
	}
	ArraySequence<int> NeighborVertexs(int index) const {
		ArraySequence<int> neighbors = ArraySequence<T>();
		ArraySequence<int> line = (*(this->AdjacencyMatrix))[index];
		for (size_t i = 0; i < line.GetLength(); i++) {
			if (line[i] == 1) {
				neighbors.Append(i);
			}
		}
		return neighbors;
	}
	ArraySequence<int> DijkstraSearch(int start, int goal) const {
		PriorityQueue<int> frontier = PriorityQueue<int>();
		frontier.Enqueue(start, 0);
		std::map<int, int> cameFrom = std::map<int, int>();
		cameFrom[start] = -1;
		std::map<int, int> costSoFar = std::map<int, int>();
		costSoFar[start] = 0;

		while (!frontier.IsEmpty()) {
			int current = frontier.Dequeue();
			if (current == goal) {
				return reconstructPath(goal, cameFrom);
			}
			ArraySequence<int> neighborVertexs = this->NeighborVertexs(current);
			for (size_t i = 0; i < neighborVertexs.GetLength(); i++) {
				int next = neighborVertexs[i];
				if (next == goal) {
					cameFrom[goal] = current;
					return reconstructPath(goal, cameFrom);
				}
				int newCost = costSoFar[current] + (*(this->WeightMatrix))[current][next];
				if ((cameFrom.count(next) == 0) || (newCost < costSoFar[next])) {
					costSoFar[next] = newCost;
					frontier.Enqueue(next, newCost);
					cameFrom[next] = current;
				}
			}
		}
		return NULL;
	}

	~MatrixGraph() {
		delete this->Values;
		delete this->AdjacencyMatrix;
		delete this->WeightMatrix;
	}
};

