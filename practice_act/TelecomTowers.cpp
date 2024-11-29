#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

struct Tower {
    int x, y;
    Tower(int _x, int _y) : x(_x), y(_y) {}
};


double distance(const Tower& t1, const Tower& t2) {
    return std::sqrt(std::pow(t1.x - t2.x, 2) + std::pow(t1.y - t2.y, 2));
}

//Solucion greedy checando distancia entre torres
int minimumTowersToRemove(std::vector<Tower>& towers, double d) {
    int n = towers.size();
    
    std::vector<bool> keep(n, true);
    
    // Complexity: O(n log n) as std sort is used
    std::sort(towers.begin(), towers.end(), 
        [](const Tower& a, const Tower& b) { return a.x < b.x; });
    
    // Complexity: O(n²) as nested loops are used
    for (int i = 0; i < n; ++i) {
        if (!keep[i]) continue;
        
        for (int j = i + 1; j < n; ++j) {
            // si la distancia entre torres es menor o igual a d, se marca para eliminar la torre j
            if (distance(towers[i], towers[j]) <= d) {
                keep[j] = false;
            }
        }
    }
    
    // contar las que se marcaron para eliminar
    return n - std::count(keep.begin(), keep.end(), true);
}

int main() {
    int n;
    double d;
    std::cin >> n >> d;
    

    std::vector<Tower> towers;
    for (int i = 0; i < n; ++i) {
        int x, y;
        std::cin >> x >> y;
        towers.emplace_back(x, y);
    }
    
    // torres minimas a eliminar
    std::cout << minimumTowersToRemove(towers, d) << std::endl;
    
    return 0;
}