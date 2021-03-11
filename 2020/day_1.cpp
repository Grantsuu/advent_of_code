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
  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
  }

  // Return the populated list.
  return l;
}

int main() {
  // List to hold puzzle input.
  std::array<int, 200> input = ParseInput("day_1_input.txt");

  /** Part 1 Puzzle Algorithm
   * Can do a little better than brute force searching through the entire list.
   * 1. First, sort the list into ascending order.
   * 2. Start with the first number in the list as a and the last number b.
   * 3. Add a and b together to get the sum c.
   * 4. If c is equal to 2020, then multiply a and b together to solve the
   * puzzle.
   * 5. If c is greater than 2020, then replace b with the number previous to it
   * in the list (the next smallest).
   * 6. If c is less than 2020, then replace a with the number after it in the
   * list (the next largest) and reset b to the last number in the list.
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
    if (c > target) {
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

  std::cout << "Part 1\n"
            << "a = " << a << "\n"
            << "b = " << b << "\n"
            << "The answer is: " << solution << std::endl;

  /** Part 2 Puzzle Algorithm
   * Using the sorted list we can do a little better than brute force again.
   * 1. First, sort the list into ascending order.
   * 2. Start with a as the first in the list, b as the second, and c as the
   * last.
   * 3. Add a, b, and c together to get the sum d.
   * 4. If d is equal to 2020, then multiply a, b, and c together to solve the
   * puzzle.
   * 5. If d is greater than 2020, then replace c with the number previous to it
   * in the list (the next smallest).
   * 6. If d is less than 2020, then replace b with the number after it in the
   * list (the next largest).
   * 7. Repeat steps 5 and 6 until a solution is reached or b equals c.
   * 8. If a solution isn't found, replace a with b and b with the number after
   * it in the list. Reset c with the last number in the list then repeat
   * steps 6-8.
   * 9. Repeat steps 3-8 until the condition in step 4 is met to solve the
   * puzzle.
   */

  int second = first + 1;
  last = input.size();

  a = input[first];
  b = input[second];
  c = input[last];
  int d = a + b + c;
  // Target is still 2020.

  while (d != target) {
    if (d > 2020) {
      --last;
      c = input[last];
    } else {
      ++second;
      b = input[second];
    }

    if (b == c) {
      second = ++first;
      a = b;
      b = input[second];
      last = input.size();
      c = input[last];
    }
    d = a + b + c;
    std::cout << d << std::endl;
  }

  solution = a * b * c;

  std::cout << "Part 2\n"
            << "a = " << a << "\n"
            << "b = " << b << "\n"
            << "c = " << c << "\n"
            << "The answer is: " << solution << std::endl;
}

/** What I learned with this exercise:
 *
 * I definitely should have made each part of the solution its own function so
 * that I didn't run into the issue of having to reuse or rename variable to
 * solve part 2. Knowing how the puzzles work with two parts will come in handy
 * in the future.
 *
 */