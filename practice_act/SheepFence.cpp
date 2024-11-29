#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <limits>

struct Point {
    int x, y, index;
    Point(int _x = 0, int _y = 0, int _index = 0) : x(_x), y(_y), index(_index) {}
    
    bool operator<(const Point& p) const {
        return y < p.y || (y == p.y && x < p.x);
    }
};

// producto cruz para oritnacion de 3 puntos
int cross_product(const Point& o, const Point& a, const Point& b) { // Complextiy: O(1)
    //std::cout << "Cross product between : " << o.index << " " << a.index << " " << b.index  << std::endl;
    return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}

// Euclidean distance
double distance(const Point& a, const Point& b) {
    return std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2));
}

std::vector<Point> convex_hull(std::vector<Point>& points) { // Complextiy: O(n log n)
    int n = points.size();
    if (n <= 1) return points;
    
    // primero el punto de abajo de la izquierda
    std::sort(points.begin(), points.end()); // This first sort is O(n log n), because the std sort is used
    Point start = points[0];

    /*
    for (int i = 0; i < points.size(); i++){
        std::cout << points[i].index << " ";
    }
    std::cout << std::endl;
    */
    
    std::sort(points.begin() + 1, points.end(), // the same as the first sort
        [&start](const Point& a, const Point& b) {
            int cross = cross_product(start, a, b);
            return cross > 0 || (cross == 0 && distance(start, a) < distance(start, b));
        });

    
    
    // Graham's scan
    std::vector<Point> hull;
    hull.push_back(points[0]);
    
    for (int i = 1; i < n; ++i) { //O(n)
        while (hull.size() > 1 && 
            (cross_product(hull[hull.size()-2], hull.back(), points[i]) < 0 || //giro a la izquierda, y luego checamos el indice por si estan donde mismo (ultimo caso)
            (cross_product(hull[hull.size()-2], hull.back(), points[i]) == 0 && hull.back().index > points[i].index))) {

            hull.pop_back();
        }
        hull.push_back(points[i]);
    }

    // the algorithm general complexity is O(n log n) because the sorting is the most expensive operation
    
    return hull;
}

int main() {
    int t;
    std::cin >> t;
    
    for (int test = 0; test < t; ++test) {
        int n;
        std::cin >> n;
        
        std::vector<Point> points(n);
        for (int i = 0; i < n; ++i) {
            std::cin >> points[i].x >> points[i].y;
            points[i].index = i + 1;
        }
        

        if (n == 1) {
            std::cout << "0.00\n" << points[0].index << std::endl;
            continue;
        }
        

        std::vector<Point> hull = convex_hull(points);
        
        // Perimetro
        double perimeter = 0;
        int k = hull.size();
        for (int i = 0; i < k; ++i) {
            perimeter += distance(hull[i], hull[(i+1)%k]);
        }
        
        std::cout << std::fixed << std::setprecision(2) << perimeter << std::endl;
        for (const auto& point : hull) {
            std::cout << point.index << " ";
        }
        std::cout << std::endl << std::endl;
    }
    
    return 0;
}
