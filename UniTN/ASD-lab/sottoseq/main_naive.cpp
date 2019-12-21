#include <fstream>
#include <vector>
#include <iostream>

int32_t maximum_subarray(std::int32_t arr[], std::size_t size) {
  int32_t max = INT32_MIN;
  int32_t sum;
  for (size_t i = 0; i < size; ++i) {
    sum = 0;
    for (size_t j = 0; j + i < size; ++j) {
      sum += arr[i + j];
      if (max < sum) {
        max = sum;
      }
    }
  }
  return max;
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
