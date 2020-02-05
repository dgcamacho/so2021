#pragma once

// see: https://en.cppreference.com/w/cpp/algorithm/unique

// removes consecutive duplicate elements in a range
template <class ForwardIt>
ForwardIt unique(ForwardIt first, ForwardIt last)
{
  if (first == last)
    return last;

  ForwardIt result = first;
  while (++first != last) {
    if (!(*result == *first) && ++result != first) {
      *result = *first; // or: ... = std::move(*first)
    }
  }
  return ++result;
}
