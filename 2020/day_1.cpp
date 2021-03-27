#include <algorithm>
#include <array>  // remove me
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

/** Function to read the contents of a text file and add them to a vector.
 * @param file_name is the name of the file to read.
 * @returns a vector<T> containing all of the data from file_name.
 */
template <class T>
std::vector<T> ParseInput(std::string file_name) {
  // Open file.
  std::ifstream file(file_name);
  // Vector to hold contents of file.
  std::vector<T> v;
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
int main() {
  // List to hold puzzle input.
  std::vector<int> input = ParseInput<int>("day_1_input.txt");

  // Sort the vector.
  std::sort(input.begin(), input.end());

  // Print out vector contents to double-check.
  PrintContainer<std::vector<int>>(input);

  // Calculate the solution using the algorithm described in the method above.
  int solution = SolutionPartOne(2020, input, input.begin(), --input.end());

  std::cout << "Part 1\n"
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
  /*
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
  */
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