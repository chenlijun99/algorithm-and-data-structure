#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

int32_t max_crossmid_subarray(std::int32_t arr[], std::size_t left,
                              std::size_t right, std::size_t mid) {
  int32_t sum = 0;
  int32_t left_max = INT32_MIN;
  for (ssize_t i = mid; i >= (ssize_t)left; --i) {
    sum += arr[i];
    if (left_max < sum) {
      left_max = sum;
    }
  }

  sum = 0;
  int32_t right_max = INT32_MIN;
  for (size_t i = mid + 1; i <= right; ++i) {
    sum += arr[i];
    if (right_max < sum) {
      right_max = sum;
    }
  }
  return right_max + left_max;
}

int32_t maximum_subarray(std::int32_t arr[], std::size_t left,
                         std::size_t right) {
  if (left == right) {
    return arr[left];
  } else {
    size_t mid = (left + right) / 2;
    int32_t max_left = maximum_subarray(arr, left, mid);
    int32_t max_right = maximum_subarray(arr, mid + 1, right);
    int32_t max_mid = max_crossmid_subarray(arr, left, right, mid);
    return std::max({max_left, max_right, max_mid});
  }
}

int main(int argc, char *argv[]) {
  const char *input = "input.txt";
  if (argc == 2) {
    input = argv[1];
  }

  std::ifstream fin(input);

  size_t N;
  fin >> N;

  int32_t arr[N];

  for (int i = 0; i < N; i++) fin >> arr[i];

  std::ofstream fout("output.txt");
  fout << maximum_subarray(arr, 0, N - 1);
  return 0;
}
