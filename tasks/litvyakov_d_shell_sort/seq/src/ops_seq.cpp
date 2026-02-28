#include "litvyakov_d_shell_sort/seq/include/ops_seq.hpp"

#include <cmath>
#include <complex>
#include <tuple>
#include <vector>

#include "litvyakov_d_shell_sort/common/include/common.hpp"

namespace litvyakov_d_shell_sort {

// wikipedia realization of shell sort
void LitvyakovDShellSortSEQ::BaseShellSort(std::vector<int> &vec) {
  auto first = vec.begin();
  auto last = vec.end();

  for (auto d = (last - first) / 2; d != 0; d /= 2) {
    for (auto i = first + d; i != last; ++i) {
      for (auto j = i; j - first >= d && (*j < *(j - d)); j -= d) {
        std::swap(*j, *(j - d));
      }
    }
  }
}

void LitvyakovDShellSortSEQ::merge(std::vector<int> &left, const std::vector<int> &right, std::vector<int> &vec) {
  vec.clear();
  std::size_t i = 0, j = 0;
  std::size_t left_size = left.size(), right_size = right.size();
  while (i < left_size && j < right_size) {
    if (left[i] <= right[j]) {
      vec.push_back(left[i++]);
    } else {
      vec.push_back(right[j++]);
    }
  }
  while (i < left_size) {
    vec.push_back(left[i++]);
  }
  while (j < right_size) {
    vec.push_back(right[j++]);
  }
}

void LitvyakovDShellSortSEQ::ShellSortMerge(std::vector<int> &vec) {
  if (vec.size() <= 1) {
    return;
  }
  std::size_t mid = vec.size() / 2;
  std::vector<int> left(vec.begin(), vec.begin() + mid);
  std::vector<int> right(vec.begin() + mid, vec.end());
  BaseShellSort(left);
  BaseShellSort(right);
  merge(left, right, vec);
}

LitvyakovDShellSortSEQ::LitvyakovDShellSortSEQ(const InType &in) {
  SetTypeOfTask(GetStaticTypeOfTask());
  GetInput() = in;
  GetOutput() = std::vector<int>();
}

bool LitvyakovDShellSortSEQ::ValidationImpl() {
  const InType &vec = GetInput();
  return vec.size() > 0;
}

bool LitvyakovDShellSortSEQ::PreProcessingImpl() {
  GetOutput() = GetInput();
  return true;
}

bool LitvyakovDShellSortSEQ::RunImpl() {
  std::vector<int> &vec = GetOutput();
  ShellSortMerge(vec);
  return true;
}

bool LitvyakovDShellSortSEQ::PostProcessingImpl() {
  return true;
}

}  // namespace litvyakov_d_shell_sort
