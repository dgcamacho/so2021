#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main()
{
  std::string text = "Assume that line is a std::vector. Rewrite the for statement so it instead steps through line using a vector iterator";
  std::vector<char> line(text.begin(), text.end());

  // variant 1, using iterators directly
  int space_count = 0;
  for (auto it = line.begin(); it != line.end(); ++it)
    if (*it == ' ')
      space_count++;
  std::cout << space_count << '\n';

  // variant 2, using range-based for-loops
  space_count = 0;
  for (char c : line)
    if (c == ' ')
      space_count++;
  std::cout << space_count << '\n';

  // variant 3, using std algorithms
  space_count = std::count_if(line.begin(), line.end(), [](char c) { return c == ' '; });
  std::cout << space_count << '\n';
}
