#include "Points.cpp"
#include <chrono>
#include <cstdio>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("\nIncorrect arguments. Format as: ./convex-hull n_points visual\n");
    }
    Points p(atoi(argv[1]));
    bool visual = atoi(argv[2]);

    printf("\n%d points\n", atoi(argv[1]));

    if (visual) {
        printf("\nPoints:\n");
        p.printPoints();
    }

    chrono::time_point<chrono::high_resolution_clock> start = chrono::high_resolution_clock::now();
    p.bruteHull();
    double time = chrono::duration_cast<chrono::microseconds>(chrono::high_resolution_clock::now() - start).count() / 1000000.0;
	printf("Brute Hull Time:\t%fs\n", time);

    if (visual) {
        printf("\nBrute Hull:\n");
        p.printBruteHull();
    }

    start = chrono::high_resolution_clock::now();
    p.quickHull();
    time = chrono::duration_cast<chrono::microseconds>(chrono::high_resolution_clock::now() - start).count() / 1000000.0;
	printf("Quick Hull Time:\t%fs\n", time);

    if (visual) {
        printf("\nQuick Hull:\n");
        p.printQuickHull();
    }

    if (p.compareHulls()) {
        printf("Hulls are equivalent\n\n");
    } else {
        printf("Hulls are NOT equivalent\n\n");
    }

    return 0;
}
