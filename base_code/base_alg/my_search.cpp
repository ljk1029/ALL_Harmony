#include <iostream>
#include <queue>
#include <vector>

/**
 * 路径搜索
 */

class MySearch {
    using vector2 = std::vector<std::vector<int>>;

private:
    int m, n;
    vector2 judge;
    std::vector<std::pair<int, int>> path;
    std::vector<std::vector<int>> array;

public:
    void init_search() {
        judge.clear();
        path.clear();
        array.clear();
    }

    // 深度搜索，优先找到最深
    bool DFSUtil(int x, int y, const vector2 &array, std::vector<std::pair<int, int>> &path) {
        // 最后一个点
        if (x == n - 1 && y == m - 1) {
            judge[x][y] = 1;
            if (array[x][y] == 1) {
                path.push_back({x, y});
                return true;
            } else {
                return false;
            }
        }
        // 超出范围或者是不可访问的点
        if (x < 0 || x >= n || y < 0 || y >= m || array[x][y] == 0 || judge[x][y] == 1) {
            return false;
        }

        // 标记当前节点为路径的一部分
        judge[x][y] = 1;
        path.push_back({x, y});

        // 向右移动
        if (DFSUtil(x + 1, y, array, path))
            return true;

        // 向下移动
        if (DFSUtil(x, y + 1, array, path))
            return true;

        // 如果这条路线不成功，反标记[x][y]并从路径中移除
        judge[x][y] = 0;
        path.pop_back();

        // 如果没有找到路径，返回失败
        return false;
    }

    // 深度搜素，用于查找是否联通等
    bool DFS_search(vector2 array) {
        bool find_flag = false;
        if ((n = array.size()) == 0 || (m = array[0].size()) == 0) {
            std::cout << "输入矩阵尺寸错误\n";
            return false;
        }
        judge = std::vector<std::vector<int>>(n, std::vector<int>(m, 0));
        // judge.assign(n, std::vector<int>(m, 0));

        find_flag = DFSUtil(0, 0, array, path);
        print_path(path);

        return find_flag;
    }

    // 广度搜素，用于查找最优解
    bool BFS_search(vector2 array) {
        bool find_flag = false;
        if ((n = array.size()) == 0 || (m = array[0].size()) == 0) {
            std::cout << "输入矩阵尺寸错误\n";
            return false;
        }

        judge = std::vector<std::vector<int>>(n, std::vector<int>(m, 0));
        std::queue<std::pair<int, int>> q;

        // 添加起点进入队列
        if (array[0][0] == 0)
            return false;
        q.push({0, 0});
        judge[0][0] = 1;

        // 方向数组，表示相邻的四个方向（上下左右）
        int dirs[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

        while (!q.empty()) {
            auto p = q.front();
            q.pop();
            int x = p.first, y = p.second;
            path.push_back(p);

            // 如果到达终点
            if (x == n - 1 && y == m - 1) {
                find_flag = true;
                break;
            }

            // 探索相邻节点
            for (auto &dir : dirs) {
                int next_x = x + dir[0];
                int next_y = y + dir[1];

                // 检查新位置是否可访问并且未被访问过
                if (next_x >= 0 && next_x < n && next_y >= 0 && next_y < m && array[next_x][next_y] == 1 &&
                    judge[next_x][next_y] == 0) {
                    q.push({next_x, next_y});
                    judge[next_x][next_y] = 1;
                }
            }
        }
        if (!find_flag)
            path.clear();
        print_path(path);
        return find_flag;
    }

    bool print_path(std::vector<std::pair<int, int>> path) {
        if (path.size() == 0) {
            std::cout << "没有找到路径" << std::endl;
            return false;
        } else {
            std::cout << "发现路径:\n";
            for (const auto &p : path) {
                std::cout << '(' << p.first << ',' << p.second << ") -> ";
            }
            std::cout << "END" << std::endl;
            return true;
        }
    }

    int get_rand_num(int start = 0, int end = 2) {
        int t = rand() % (end - start) + start;
        return t;
    }

    std::vector<std::vector<int>> genrate_rand_array(int n = 0, int m = 0) {
        // 使用当前时间作为随机数生成器的种子
        srand((unsigned)time(NULL));

        n = (n == 0) ? get_rand_num(1, 20) : n;
        m = (m == 0) ? get_rand_num(1, 20) : m;
        std::cout << "n: " << n << " m: " << m << std::endl;
        array.resize(n);
        std::cout << "{\n";
        for (int i = 0; i < n; i++) {
            std::cout << "  { ";
            array[i].reserve(m);
            for (int j = 0; j < m; j++) {
                array[i].push_back(get_rand_num());
                std::cout << array[i].back();
                if (j != m - 1)
                    std::cout << ", ";
                else
                    std::cout << " ";
            }
            std::cout << "}" << std::endl;
        }
        std::cout << "}" << std::endl;
        return array;
    }
};

// 算法测试
void test_DFS_BFS() {
    MySearch my_search;

#if 1
    std::vector<std::vector<int>> array = my_search.genrate_rand_array(5, 4);
#else
    std::vector<std::vector<int>> array = {
        {1, 1, 1, 0, 1, 1, 0},
        {1, 1, 1, 1, 1, 0, 0},
        {0, 0, 0, 1, 0, 1, 0},
        {1, 0, 0, 1, 0, 0, 0},
        {0, 1, 0, 1, 1, 1, 1}
    };
    std::vector<std::vector<int>> array1 = {
        {1, 0, 1, 1, 0, 1, 0},
        {0, 1, 1, 1, 1, 0, 1},
        {0, 0, 0, 1, 1, 1, 1},
        {0, 1, 1, 0, 1, 1, 1},
        {1, 0, 1, 1, 0, 0, 0}
    };
#endif
    std::cout << std::boolalpha << std::endl;
    std::cout << "DFS find path result: " << my_search.DFS_search(array) << std::endl;
    std::cout << "BFS find path result: " << my_search.BFS_search(array) << std::endl;
    std::cout << std::noboolalpha << std::endl;
}

// 测试函数入口
int main(int argc, char *argv[]) {
    test_DFS_BFS();
    return 0;
}