#include <algorithm>
#include <fstream>
#include <vector>
#include <iostream>

int32_t maximum_subarray(std::int32_t arr[], std::size_t size) {
  int32_t max_here = 0;
  int32_t max_so_far = INT32_MIN;
  for (size_t i = 0; i < size; ++i) {
    max_here = std::max(max_here + arr[i], 0);
    max_so_far = std::max(max_so_far, max_here);
  }
  return max_so_far;
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
  fout << maximum_subarray(arr, N);
  return 0;
}

