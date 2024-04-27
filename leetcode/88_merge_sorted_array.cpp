#include <iostream>
#include <vector>

void merge(std::vector<int> &nums1, int m, std::vector<int> &nums2, int n) {
        int p = m - 1;
        int q = n - 1;
        int r = m + n - 1;

        while (q >= 0) {
                if (p >= 0 && nums1[p] > nums2[q]) {
                        nums1[r--] = nums1[p--];
                } else {
                        nums1[r--] = nums2[q--];
                }
        }
}

int main(int argc, char *argv[]) {
        std::vector<int> nums1{1, 2, 3, 0, 0, 0};
        int m = 3;
        std::vector<int> nums2{2, 5, 6};
        int n = 3;

        merge(nums1, m, nums2, n);

        for (auto it : nums1) {
                std::cout << it << " ";
        }

        std::cout << "\n";
        return 0;
}
