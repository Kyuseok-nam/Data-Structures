//
// Created by kyu on 3/10/2021.
//

#include <iostream>

int find_paths(int start_x, int start_y) {
    if (start_x == 0 && start_y == 0) {
        return 1;
    } else if (start_x == 0 && start_y > 0) {
        return find_paths(0, start_y - 1);
    } else if (start_x > 0 && start_y == 0) {
        return find_paths(start_x - 1, 0);
    } else {
        return find_paths(start_x, start_y - 1) + find_paths(start_x - 1, start_y);
    }
}


int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << argv[0] << std::endl;
        return 1;
    } else {
        std::cout << find_paths(atoi(argv[1]), atoi(argv[2])) << "path(s)" << std::endl;
    }
}
