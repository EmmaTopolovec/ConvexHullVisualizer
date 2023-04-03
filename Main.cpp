#include "Points.cpp"

using namespace std;

int main() {
    Points p(5);

    printf("\nPoints:\n");
    p.printPoints();

    p.bruteHull();
    printf("\nBrute Hull:\n");
    p.printBruteHull();

    p.quickHull();
    printf("\nQuick Hull:\n");
    p.printQuickHull();

    return 0;
}
