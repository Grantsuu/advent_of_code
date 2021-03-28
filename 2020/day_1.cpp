#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

/** Function to read the contents of a text file and add them to a vector.
 * @param file_name is the name of the file to read.
 * @returns a vector<int> containing all of the data from file_name.
 */
std::vector<int> ParseInput(std::string file_name) {
  // Open file.
  std::ifstream file(file_name);
  // Vector to hold contents of file.
  std::vector<int> v;
  // String to temporarily hold contents of line being read in file.
  std::string line;

  try {
    // Array index to add data from input.
    int i = 0;
    // Read in all of the lines in the file.
    while (getline(file, line)) {
      // Append the contents to the vector.
      // TODO: Make this more generic.
      v.push_back(std::stoi(line));
      ++i;
    }
  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
  }

  // Return the populated vector.
  return v;
}

/** Function to print out a container.
 * @param container is a STL container to print the contents of.
 */
template <class T>
void PrintContainer(T container) {
  for (int n : container) {
    std::cout << n << ", ";
  }

  std::cout << std::endl;
}

/** Part 1 Puzzle Algorithm
 * Can do a little better than brute force searching through the entire
 * container.
 * 1. First, sort the container into ascending order.
 * 2. Start with a pointer 'a' pointing to the first member of the container and
 * pointer 'b' pointing to the last member.
 * 3. If a and b are pointing to the same number then they've overlapped meaning
 * there's no solution or there is an error.
 * 4. Add the values a and b are pointing at together to get the sum c.
 * 5. If c is equal to 2020, then multiply the values a and b are pointing at
 * together to solve the puzzle.
 * 6. If c is greater than 2020, then decrement b.
 * 7. If c is less than 2020, then increment a.
 * 8. Repeat steps 3-7 until the condition 3 or 5 is met.
 * @param x is the target sum of the 2 values.
 * @param v is the vector which holds the numbers to search through.
 * @param a is the iterator pointer at the beginning of the vector v.
 * @param b is the iterator pointer at the end of vector v.
 * @returns -1 if no solution is found, otherwise the product of a * b whose sum
 * is x.
 */
int SolutionPartOne(int x, std::vector<int> v, std::vector<int>::iterator a,
                    std::vector<int>::iterator b) {
  // If pointers are pointing to the same address then there is either no
  // solution or an error has occured.
  if (a == b) {
    return -1;
  }

  // Calculate the product of a and b.
  int c = *a + *b;
  // std::cout << *a << " " << * b << " " << c << std::endl;

  if (c == x) {
    // C matches x so we can return the product of a and b.
    return *a * *b;
  } else if (c > x) {
    // C is greater than x so decrement b and run again.
    return SolutionPartOne(x, v, a, --b);
  } else {
    // C is less than x so increment a and run again.
    return SolutionPartOne(x, v, ++a, b);
  }
}

/** Part 2 Puzzle Algorithm
 * Can do a little better than brute force searching through the entire
 * container.
 * 1. First, sort the container into ascending order.
 * 2. Start with a pointer 'a' pointing to the first member of the container and
 * pointer 'b' pointing to the member after a and pointer 'c' pointing to the
 * last member.
 * 3. If a and c are pointing to the same number then they've overlapped meaning
 * there's no solution or there is an error.
 * 4. If b and c are pointing to the same number then they've overlapped meaning
 * the solution is not between a and c so increment a and reset b to a + 1.
 * 4. Add the values a, b and c are pointing at together to get the sum i.
 * 5. If i is equal to 2020, then multiply the values a, b, and c are pointing
 * at together to solve the puzzle.
 * 6. If i is greater than 2020 and a and b are the smallest two numbers in the
 * vector, then decrement c.
 * 7. Otherwise increment b.
 * 8. Repeat steps 4-7 until the condition 3 or 5 is met.
 * @param x is the target sum of the 2 values.
 * @param v is the vector which holds the numbers to search through.
 * @param a is the iterator pointer at the beginning of the vector v.
 * @param b is the iterator pointer at the end of vector v.
 * @returns -1 if no solution is found, otherwise the product of a * b whose sum
 * is x.
 */
int SolutionPartTwo(int x, std::vector<int> v, std::vector<int>::iterator a,
                    std::vector<int>::iterator b,
                    std::vector<int>::iterator c) {
  // If pointers are pointing to the same address then there is either no
  // solution or an error has occured.
  if (a == c) {
    return -1;
  }

  if (b == c) {
    return SolutionPartTwo(x, v, ++a, a + 1, c);
  }

  // Calculate the product of a, b, and c.
  int i = *a + *b + *c;
  std::cout << *a << " " << *b << " " << *c << std::endl;

  if (i == x) {
    return *a * *b * *c;
  } else if (i > x && a == b - 1) {
    return SolutionPartTwo(x, v, a, a + 1, --c);
  } else {
    return SolutionPartTwo(x, v, a, ++b, c);
  }
}

int main() {
  // List to hold puzzle input.
  std::vector<int> input = ParseInput("day_1_input.txt");

  // Sort the vector.
  std::sort(input.begin(), input.end());

  // Print out vector contents to double-check.
  PrintContainer<std::vector<int>>(input);

  // Calculate the solution to part 1 using the algorithm described in the
  // method above.
  int solution = SolutionPartOne(2020, input, input.begin(), --input.end());

  std::cout << "Part 1\n"
            << "The answer is: " << solution << std::endl;

  // Calculate the solution to part 2 using the algorithm described in the
  // method above.
  solution = SolutionPartTwo(2020, input, input.begin(), input.begin() + 1,
                             --input.end());

  std::cout << "Part 2\n"
            << "The answer is: " << solution << std::endl;
}

/** What I learned with this exercise:
 *
 * 3/10/21 - I definitely should have made each part of the solution its own
 * function so that I didn't run into the issue of having to reuse or rename
 * variable to solve part 2. Knowing how the puzzles work with two parts will
 * come in handy in the future.
 *
 * 3/27/21 - I updated the solution to use templates and the STL.
 *
 */