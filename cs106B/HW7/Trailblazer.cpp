#include "Trailblazer.h"
#include "queue.h"
#include "pqueue.h"
#include "hashset.h"
using namespace std;

static const double SUFFICIENT_DIFFERENCE = 0.2;

Path breadthFirstSearch(const RoadGraph& graph, RoadNode* start, RoadNode* end) {
    Queue<Path> paths;
    HashSet<RoadNode*> visited;
    paths.enqueue(Path(1, start));
    start->setColor(Color::YELLOW);
    while (!paths.isEmpty() && !visited.contains(end)) {
        Path possiblePath = paths.dequeue();
        RoadNode* toVisit = possiblePath[possiblePath.size() - 1];
        if (!visited.contains(toVisit)) {
            visited.add(toVisit);
            toVisit->setColor(Color::GREEN);
            if (toVisit == end) {
                return possiblePath;
            }
            for (RoadNode* neighbor: graph.neighborsOf(toVisit)) {
                if (!visited.contains(neighbor)) {
                    paths.enqueue(possiblePath + Path(1, neighbor));
                    neighbor->setColor(Color::YELLOW);
                }
            }
        }
    }
    return Path();

}

Path dijkstrasAlgorithm(const RoadGraph& graph, RoadNode* start, RoadNode* end) {
    PriorityQueue<Path> paths;
    HashSet<RoadNode*> visited;
    paths.enqueue(Path(1, start), 0);
    start->setColor(Color::YELLOW);
    while (!paths.isEmpty() && !visited.contains(end)) {
        double pathCost = paths.peekPriority();
        Path possiblePath = paths.dequeue();
        RoadNode* toVisit = possiblePath[possiblePath.size() - 1];
        visited.add(toVisit);
        toVisit->setColor(Color::GREEN);
        if (toVisit == end) {
            return possiblePath;
        }
        for (RoadNode* neighbor: graph.neighborsOf(toVisit)) {
            if (!visited.contains(neighbor)) {
                paths.enqueue(possiblePath + Path(1, neighbor),
                              pathCost + graph.edgeBetween(toVisit, neighbor)->cost());
                neighbor->setColor(Color::YELLOW);
            }
        }
    }
    return Path();
}

double timeHeuristic(const RoadGraph& graph, RoadNode* start, RoadNode* end) {
    return graph.crowFlyDistanceBetween(start, end) / graph.maxRoadSpeed();
}

Path aStar(const RoadGraph& graph, RoadNode* start, RoadNode* end) {
    PriorityQueue<Path> paths;
    HashSet<RoadNode*> visited;
    paths.enqueue(Path(1, start), timeHeuristic(graph, start, end));
    start->setColor(Color::YELLOW);
    while (!paths.isEmpty() && !visited.contains(end)) {
        double pathCost = paths.peekPriority();
        Path possiblePath = paths.dequeue();
        RoadNode* toVisit = possiblePath[possiblePath.size() - 1];
        pathCost -= timeHeuristic(graph, toVisit, end);
        visited.add(toVisit);
        toVisit->setColor(Color::GREEN);
        if (toVisit == end) {
            return possiblePath;
        }
        for (RoadNode* neighbor: graph.neighborsOf(toVisit)) {
            if (!visited.contains(neighbor)) {
                paths.enqueue(possiblePath + Path(1, neighbor), pathCost +
                              graph.edgeBetween(toVisit, neighbor)->cost() +
                              timeHeuristic(graph, neighbor, end));
                neighbor->setColor(Color::YELLOW);
            }
        }
    }
    return Path();
}

HashSet<RoadNode*> setFromPath(Path &path) {
    HashSet<RoadNode*> set;
    for (RoadNode* node: path) {
        set.add(node);
    }
    return set;
}

double getPathDifference(Path &path1, Path &path2) {
    HashSet<RoadNode*> set1 = setFromPath(path1);
    HashSet<RoadNode*> set2 = setFromPath(path2);
    return (set2 - set1).size() / (double) set2.size();
}


Path alternativeRoute(const RoadGraph& graph, RoadNode* start, RoadNode* end) {
    Path bestPath = aStar(graph, start, end);
    Path bestAlternativePath;
    double minPathCost = 0;
    for (int i = 1; i < bestPath.size(); i++) {
        PriorityQueue<Path> paths;
        HashSet<RoadNode*> visited;
        paths.enqueue(Path(1, start), timeHeuristic(graph, start, end));
        start->setColor(Color::YELLOW);
        while (!paths.isEmpty() && !visited.contains(end)) {
            double pathCost = paths.peekPriority();
            Path possiblePath = paths.dequeue();
            RoadNode* toVisit = possiblePath[possiblePath.size() - 1];
            pathCost -= timeHeuristic(graph, toVisit, end);
            visited.add(toVisit);
            toVisit->setColor(Color::GREEN);
            if (toVisit == end && (minPathCost == 0 || pathCost < minPathCost) &&
                    getPathDifference(possiblePath, bestPath) > SUFFICIENT_DIFFERENCE) {
                bestAlternativePath = possiblePath;
                minPathCost = pathCost;
            }
            RoadEdge* edgeToIgnore = graph.edgeBetween(bestPath[i - 1], bestPath[i]);
            for (RoadNode* neighbor: graph.neighborsOf(toVisit)) {
                RoadEdge* edgeToVisit = graph.edgeBetween(toVisit, neighbor);
                if (!visited.contains(neighbor) && edgeToVisit != edgeToIgnore) {
                    paths.enqueue(possiblePath + Path(1, neighbor), pathCost +
                                  graph.edgeBetween(toVisit, neighbor)->cost() +
                                  timeHeuristic(graph, neighbor, end));
                    neighbor->setColor(Color::YELLOW);
                }
            }
        }
    }
    return bestAlternativePath;
}
