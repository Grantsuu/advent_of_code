#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <string>

/** Function to read the contents of a text file and add them to a list of
 * integers.
 * @param file_name is the name of the file to read.
 * @returns a list<int> containing all of the data from file_name.
 */
std::array<int, 200> ParseInput(std::string file_name) {
  // Open file.
  std::ifstream file(file_name);
  // List to hold contents of file.
  std::array<int, 200> l;
  // String to temporarily hold contents of line being read in file.
  std::string line;

  try {
    // Array index to add data from input.
    int i = 0;
    // Read in all of the lines in the file.
    while (getline(file, line)) {
      // Append the contents to the list.
      l[i] = std::stoi(line);
      ++i;
    }
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
  }

  // Return the populated list.
  return l;
}

int main() {
  // List to hold puzzle input.
  std::array<int, 200> input = ParseInput("day_1_1_input.txt");

  /** Puzzle Algorithm
   * Can do a little better than brute force searching through the entire list.
   * 1. First, sort the list into ascending order.
   * 2. Start with the first number in the list as a and the last number b.
   * 3. Add a and b together to get the sum c.
   * 4. If c is equal to 2020, then multiply a and b together to solve the
   * puzzle.
   * 5. If c is greater than 2020, then replace b with the number previous to it
   * in the list (the next largest).
   * 6. If c is less than 2020, then replace a with the number after it (the
   * next smallest), reset b to the last number in the list.
   * 7. Repeat steps 3-6 until the condition in step 4 is met to solve the
   * puzzle.
   */

  // Sort the list into ascending order.
  std::sort(input.begin(), input.end());

  // Print out list contents to double-check.
  for (int n : input) {
    std::cout << n << ", ";
  }

  std::cout << std::endl;

  // First array index.
  int first = 0;

  // Last array index.
  int last = input.size();

  // Set a equal to the first element.
  int a = input[first];

  // Set b equal to the last element.
  int b = input[last];

  // Sum of a and b.
  int c = a + b;

  // Target sum to end search at.
  int target = 2020;

  while (c != target) {
    if(c > target) {
      --last;
      b = input[last];
    } else {
      ++first;
      a = input[first];
      last = input.size();
      b = input[last];
    }
    c = a + b;
  }

  int solution = a * b;

  std::cout << "a = " << a << "\n"
            << "b = " << b << "\n"
            << "The answer is: " << solution << std::endl;
}
