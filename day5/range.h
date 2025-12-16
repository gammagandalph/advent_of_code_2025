#include <exception>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace day5_range {

enum OverlapType { Right, Left, Inside, Around, None };

/// a class for inclusive ranges
template <class T> class Range {
private:
  T start_;
  T end_;

public:
  /// start and end define start and end of an inclusive range
  Range(T start, T end);
  /// returns the starting value
  T start() const;
  /// returns the ending value
  T end() const;
  /// returns true if element in range
  bool contains(T element);
  /// size of the range
  T length() const;
  /// returns the overlap type
  OverlapType overlapType(const Range<T> &compare);
  /// is Range compare overlapping
  bool overlap(const Range<T> &compare);
  /// number of overlapping elements
  T overlapSize(const Range<T> &compare);
  /// get a string representation
  std::string toString() const;
  /// combine two ranges to a new one, only works if they overlap
  Range<T> combineWith(const Range<T> &range);
};

template <class T> Range<T>::Range(T start, T end) {
  if (start > end)
    throw std::exception();

  start_ = start;
  end_ = end;
}
template <class T> T Range<T>::start() const { return start_; }
template <class T> T Range<T>::end() const { return end_; }

template <class T> bool Range<T>::contains(T element) {
  return element <= end_ && element >= start_;
}

template <class T> T Range<T>::length() const { return end_ - start_ + 1; }

template <class T> OverlapType Range<T>::overlapType(const Range<T> &compare) {
  T cStart = compare.start();
  T cEnd = compare.end();

  if (cStart < start_ && cEnd >= start_ && cEnd <= end_)
    return Left;
  if (cStart >= start_ && cEnd <= end_)
    return Inside;
  if (cStart <= end_ && cStart >= start_ && cEnd > end_)
    return Right;
  if (cStart < start_ && cEnd > end_)
    return Around;
  else
    return None;
}

template <class T> bool Range<T>::overlap(const Range<T> &compare) {
  return overlapType(compare) != None;
}

template <class T> T Range<T>::overlapSize(const Range<T> &overlapping) {
  if (!overlap(overlapping))
    return 0;

  T oStart = overlapping.start();
  T oEnd = overlapping.end();

  switch (overlapType(overlapping)) {
  case Left:
    return oEnd - start_ + 1;
  case Right:
    return end_ - oStart + 1;
  case Inside:
    return overlapping.length();
  case Around:
    return length();
  case None:
    return 0;
  }
}

template <class T> std::string Range<T>::toString() const {
  std::stringstream ss;
  ss << start_ << '-' << end_;
  return ss.str();
}

template <class T> Range<T> Range<T>::combineWith(const Range<T> &range) {
  switch (overlapType(range)) {
  case Left:
    return Range<T>(range.start(), end_);
  case Right:
    return Range<T>(start_, range.end());
  case Inside:
    return Range<T>(start_, end_);
  case Around:
    return Range<T>(range.start(), range.end());
  case None:
    throw std::exception();
  }
}

template <typename T> bool operator<(const Range<T> &a, const Range<T> &b) {
  return a.start() < b.start();
}

template <typename T> void printRanges(std::vector<Range<T>> ranges) {
  for (auto range : ranges) {
    std::cout << range.toString() << std::endl;
  }
}
} // namespace day5_range
