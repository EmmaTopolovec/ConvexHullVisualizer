#include <stdlib.h>
#include <time.h>
#include <vector>
#include <unordered_set>

using namespace std;

struct Point {
    int x;
    int y;
};

class Points {
    public:
        Points() { // default constructor
            n = 0;
        }

        Points(unsigned int n) {
            printf("\nPoints:\n");
            this->n = n;
            srand(time(NULL)); // seed
            for (unsigned int i = 0; i < n; i++) {
                Point* pt = new Point;
                pt->x = rand() % 2001 - 1000; // random x from -1000 to 1000
                pt->y = rand() % 2001 - 1000; // random y from -1000 to 1000
                printf("( %d,\t%d )\n", pt->x, pt->y);
                p.push_back(pt);
            }
        }

        ~Points() { // destructor
            for (unsigned int i = 0; i < n; i++) {
                delete p.at(i);
            }
        }

        void printPoint(unsigned int i) {
            printf("(%d,%d)\n", p.at(i)->x, p.at(i)->y);
            return;
        }

        void printPoints() {
            for (unsigned int i = 0; i < p.size(); i++) {
                printf("(%d,%d)\n", p.at(i)->x, p.at(i)->y);
            }
            return;
        }

        unsigned int size() {
            return n;
        }

        vector<Point*> bruteHull() { // Brute Force to find convex hull
            printf("\nConvex Hull:\n");
            vector<Point*> hull; // points on the hull
            for (unsigned int i = 0; i < n; i++) {
                for (unsigned int j = 0; j < n; j++) { // checking if the line from i to j is on the hull
                    if (i == j) continue;
                    bool oneLeft = false; // at least one point is to the left of the line
                    bool oneRight = false; // at least one point is to the right of the line
                    for (unsigned int k = 0; k < n; k++) {
                        if (k == i || k == j) continue;
                        int dist = distFromLine(p.at(i), p.at(j), p.at(k));
                        if (dist > 0) {
                            oneLeft = true;
                        } else if (dist < 0) {
                            oneRight = true;
                        }
                        if (oneRight && oneLeft) { // point is NOT on the hull
                            break;
                        }
                    }
                    if (!(oneRight && oneLeft)) { // point IS on the hull
                        hull.push_back(p.at(i)); // add i to hull -> j will be added later or is already added
                        printf("( %d,\t%d )\n", p.at(i)->x, p.at(i)->y);
                        break;
                    }
                }
            }
            return hull;
        }

        vector<Point*> quickHull() { // QuickHull algorithm to find convex hull
            vector<Point*> hull; // points on the hull
            sort(p.begin(), p.end(), sortByX);

            return hull;
        }

    private:
        unsigned int n; // number of points
        vector<Point*> p; // vector of points (x,y)

        static int distFromLine(Point* l1, Point* l2, Point* pt) {
            return ((pt->x - l1->x)*(l2->y - l1->y) - (pt->y - l1->y)*(l2->x - l1->x));
        }

        static bool sortByX(Point* p1, Point* p2) {
            return (p1->x < p2->x);
        }

};
