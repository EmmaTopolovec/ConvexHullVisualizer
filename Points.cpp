#include <stdlib.h>
#include <time.h>
#include <vector>
#include <unordered_set>
#include <set>
#include <cstdio>
#include <cmath>

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
            this->n = n;
            srand(time(NULL)); // seed
            for (unsigned int i = 0; i < n; i++) {
                Point* pt = new Point;
                pt->x = rand() % (2 * n + 1) - n; // random x from -n to n
                pt->y = rand() % (2 * n + 1) - n; // random y from -n to n
                p.push_back(pt);
            }
            do {
                set<Point*, set_comparator> s(p.begin(), p.end()); // makes sure there are no duplictes
                p = vector<Point*>(s.begin(), s.end());
                int more_points = n - s.size();
                for (int i = 0; i < more_points; i++) {
                    Point* pt = new Point;
                    pt->x = rand() % (2 * n + 1) - n; // random x from -n to n
                    pt->y = rand() % (2 * n + 1) - n; // random y from -n to n
                    p.push_back(pt);
                }
            } while (p.size() != n); // if there were duplicates
        }

        ~Points() { // destructor
            for (unsigned int i = 0; i < n; i++) {
                delete p.at(i);
            }
        }

        void printPoints() {
            for (unsigned int i = 0; i < p.size(); i++) {
                printf("(%d,%d)\n", p.at(i)->x, p.at(i)->y);
            }
            return;
        }

        void printBruteHull() {
            for (unsigned int i = 0; i < b_hull.size(); i++) {
                printf("(%d,%d)\n", b_hull.at(i)->x, b_hull.at(i)->y);
            }
            return;
        }

        void printQuickHull() {
            for (unsigned int i = 0; i < q_hull.size(); i++) {
                printf("(%d,%d)\n", q_hull.at(i)->x, q_hull.at(i)->y);
            }
            return;
        }

        unsigned int size() {
            return n;
        }

        void bruteHull() { // Brute Force to find convex hull
            b_hull.clear(); // resets vector just in case bruteHull was called before
            if (n < 4) {
                b_hull = p;
                set<Point*, set_comparator> b_set(b_hull.begin(), b_hull.end()); // remove dupes
                b_hull = vector<Point*>(b_set.begin(), b_set.end());
                return;
            }
            for (unsigned int i = 0; i < n; i++) {
                for (unsigned int j = 0; j < n; j++) { // checking if the line from i to j is on the hull
                    if (i == j) continue;
                    bool oneLeft = false; // at least one point is to the left of the line
                    bool oneRight = false; // at least one point is to the right of the line
                    for (unsigned int k = 0; k < n; k++) {
                        if (k == i || k == j) continue;
                        double dist = distFromLine(p.at(i), p.at(j), p.at(k));
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
                        b_hull.push_back(p.at(i)); // add i to hull -> j will be added later or is already added
                        // printf("Adding (%i, %i)\n", p.at(i)->x, p.at(i)->y);
                        break;
                    }
                }
            }
            set<Point*, set_comparator> b_set(b_hull.begin(), b_hull.end()); // remove dupes
            b_hull = vector<Point*>(b_set.begin(), b_set.end());
            return;
        }

        void quickHull() { // QuickHull algorithm to find convex hull
            q_hull.clear(); // resets vector just in case quickHull was called before
            // printf("quickHull()\n");
            if (n < 4) {
                q_hull = p;
                return;
            }
            Point* min_x = p.at(0);
            Point* max_x = p.at(0);
            for (unsigned int i = 0; i < n; i++) { // finds points with min x and max x
                if (p.at(i)->x > max_x->x) max_x = p.at(i);
                if (p.at(i)->x < min_x->x) min_x = p.at(i);
            }
            // ("quickHull(min_x(%i, %i), max_x(%i, %i), above)\n", min_x->x, min_x->y, max_x->x, max_x->y);
            quickHull(min_x, max_x, 1); // finds convex hull above the line
            // printf("quickHull(min_x(%i, %i), max_x(%i, %i), below)\n", min_x->x, min_x->y, max_x->x, max_x->y);
            quickHull(min_x, max_x, 0); // finds convex hull below the line
            // printf("Done\n");
            q_hull.assign(q_hull.begin(), q_hull.end());
            set<Point*, set_comparator> q_set(q_hull.begin(), q_hull.end()); // remove dupes
            q_hull = vector<Point*>(q_set.begin(), q_set.end());
            return;
        }

        bool compareHulls() {
            // set<Point*, set_comparator> b_set(b_hull.begin(), b_hull.end());
            // set<Point*, set_comparator> q_set(q_hull.begin(), q_hull.end());
            printf("b_set.size() = %lu\n", b_hull.size());
            printf("q_set.size() = %lu\n", q_hull.size());
            return (b_hull == q_hull);
        }

    private:
        unsigned int n; // number of points
        vector<Point*> p; // vector of points (x,y)
        vector<Point*> b_hull; // brute force
        vector<Point*> q_hull; // quick hull

        struct set_comparator { // custom comparator helps remove duplicate points
            bool operator() (Point* a, Point* b) const {
                if (a->x > b->x) return true;
                if (a->x == b->x) return (a->y > b->y);
                else return false;
            }
        };

        static double distFromLine(Point* l1, Point* l2, Point* pt) {
            return (double)((l2->y - l1->y) * pt->x + (l1->x - l2->x) * pt->y + ((l1->y - l2->y) * l1->x + (l2->x - l1->x) * l1->y)) / sqrt((l2->y - l1->y) * (l2->y - l1->y) + (l1->x - l2->x) * (l1->x - l2->x));
        }

        static bool sortByX(Point* p1, Point* p2) {
            return (p1->x < p2->x);
        }

        void quickHull(Point* p1, Point* p2, bool side) {
            double max_dist = 0;
            Point* max_p = nullptr;
            for (unsigned int i = 0; i < n; i++) {
                if (p.at(i) == p1 || p.at(i) == p2) continue;
                double dist = distFromLine(p1, p2, p.at(i));
                if (!side) dist *= -1;
                if (dist > max_dist) {
                    max_dist = dist;
                    max_p = p.at(i);
                }
            }
            if (max_p == nullptr) { // no point on this side of line found
                q_hull.push_back(p1);
                // printf("Adding (%i, %i)\n", p1->x, p1->y);
                q_hull.push_back(p2);
                // printf("Adding (%i, %i)\n", p2->x, p2->y);
                for (unsigned int i = 0; i < n; i++) {
                    if (p.at(i) == p1 || p.at(i) == p2) continue;
                    double dist = distFromLine(p1, p2, p.at(i));
                    if (dist == 0) {
                        q_hull.push_back(p.at(i));
                        // printf("Adding! (%i, %i)\n", p.at(i)->x, p.at(i)->y);
                    }
                }
                return;
            }
            // ("quickHull(p1(%i, %i), max_p(%i, %i), %i)\n", p1->x, p1->y, max_p->x, max_p->y, (distFromLine(p1, max_p, p2) < 0));
            quickHull(p1, max_p, (distFromLine(p1, max_p, p2) < 0));
            // printf("quickHull(p2(%i, %i), max_p(%i, %i), %i)\n", p2->x, p2->y, max_p->x, max_p->y, (distFromLine(p2, max_p, p1) < 0));
            quickHull(p2, max_p, (distFromLine(p2, max_p, p1) < 0));
            return;
        }

};
