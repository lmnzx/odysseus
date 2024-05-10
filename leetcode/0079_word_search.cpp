#include <string>
#include <vector>

class Solution {
        bool visit(std::vector<std::vector<char>> &board,
                   std::vector<char> &word, int start, int x, int y, int n,
                   int m, std::vector<std::vector<bool>> &visited) {
                if (start == word.size()) {
                        return true;
                }

                if (x < 0 || x >= n || y < 0 || y >= m || visited[x][y]) {
                        return false;
                }

                if (word[start] != board[x][y]) {
                        return false;
                }

                visited[x][y] = true;

                bool found =
                    visit(board, word, start + 1, x + 1, y, n, m, visited) ||
                    visit(board, word, start + 1, x - 1, y, n, m, visited) ||
                    visit(board, word, start + 1, x, y + 1, n, m, visited) ||
                    visit(board, word, start + 1, x, y - 1, n, m, visited);

                visited[x][y] = false;

                return found;
        }

      public:
        bool exist(std::vector<std::vector<char>> &board, std::string word) {
                int n = board.size();
                int m = board[0].size();

                std::vector<std::vector<bool>> visited(
                    n, std::vector<bool>(m, false));

                std::vector<char> wordChar(word.begin(), word.end());

                if (wordChar.size() > n * m) {
                        return false;
                }

                std::vector<int> counts(256, 0);

                for (int i = 0; i < n; i++) {
                        for (int j = 0; j < m; j++) {
                                counts[board[i][j]]++;
                        }
                }

                int len = wordChar.size();
                for (int i = 0; i < len / 2; i++) {
                        if (counts[wordChar[i]] >
                            counts[wordChar[len - 1 - i]]) {
                                for (int j = 0; j < len / 2; j++) {
                                        char temp = wordChar[j];
                                        wordChar[j] = wordChar[len - 1 - j];
                                        wordChar[len - 1 - j] = temp;
                                }
                                break;
                        }
                }

                for (char c : wordChar) {
                        if (--counts[c] < 0) {
                                return false;
                        }
                }

                for (int i = 0; i < n; i++) {
                        for (int j = 0; j < m; j++) {
                                if (visit(board, wordChar, 0, i, j, n, m,
                                          visited)) {
                                        return true;
                                }
                        }
                }

                return false;
        }
};
