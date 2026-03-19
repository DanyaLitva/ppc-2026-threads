#include "litvyakov_d_shell_sort/omp/include/ops_omp.hpp"

#include <cmath>
#include <cstdint>
#include <cstdio>
#include <utility>
#include <vector>

#include "litvyakov_d_shell_sort/common/include/common.hpp"

namespace litvyakov_d_shell_sort {

void LitvyakovDShellSortOMP::BaseShellSort(std::vector<int> &vec) {
  auto first = vec.begin();
  auto last = vec.end();

  for (auto dist = (last - first) / 2; dist != 0; dist /= 2) {
    for (auto i = first + dist; i != last; ++i) {
      for (auto j = i; j - first >= dist && (*j < *(j - dist)); j -= dist) {
        std::swap(*j, *(j - dist));
      }
    }
  }
}

void LitvyakovDShellSortOMP::Merge(std::vector<int> &left, const std::vector<int> &right, std::vector<int> &vec) {
  vec.clear();
  std::size_t i = 0;
  std::size_t j = 0;
  std::size_t left_size = left.size();
  std::size_t right_size = right.size();
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

void LitvyakovDShellSortOMP::ShellSortMerge(std::vector<int> &vec) {
  if (vec.size() <= 1) {
    return;
  }
  std::size_t mid = vec.size() / 2;
  std::vector<int> left(vec.begin(), vec.begin() + static_cast<int64_t>(mid));
  std::vector<int> right(vec.begin() + static_cast<int64_t>(mid), vec.end());
  BaseShellSort(left);
  BaseShellSort(right);
  Merge(left, right, vec);
}

LitvyakovDShellSortOMP::LitvyakovDShellSortOMP(const InType &in) {
  SetTypeOfTask(GetStaticTypeOfTask());
  GetInput() = in;
  GetOutput() = std::vector<int>();
}

bool LitvyakovDShellSortOMP::ValidationImpl() {
  const InType &vec = GetInput();
  return !vec.empty();
}

bool LitvyakovDShellSortOMP::PreProcessingImpl() {
  GetOutput() = GetInput();
  return true;
}

bool LitvyakovDShellSortOMP::RunImpl() {
  std::vector<int> &vec = GetOutput();
  ShellSortMerge(vec);
  return true;
}

bool LitvyakovDShellSortOMP::PostProcessingImpl() {
  return true;
}

}  // namespace litvyakov_d_shell_sort
