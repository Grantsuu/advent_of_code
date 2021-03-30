/* --- Day 1: Report Repair ---
After saving Christmas five years in a row, you've decided to take a vacation at
a nice resort on a tropical island. Surely, Christmas will go on without you.

The tropical island has its own currency and is entirely cash-only. The gold
coins used there have a little picture of a starfish; the locals just call them
stars. None of the currency exchanges seem to have heard of them, but somehow,
you'll need to find fifty of these coins by the time you arrive so you can pay
the deposit on your room.

To save your vacation, you need to get all fifty stars by December 25th.

Collect stars by solving puzzles. Two puzzles will be made available on each day
in the Advent calendar; the second puzzle is unlocked when you complete the
first. Each puzzle grants one star. Good luck!

Before you leave, the Elves in accounting just need you to fix your expense
report (your puzzle input); apparently, something isn't quite adding up.

Specifically, they need you to find the two entries that sum to 2020 and then
multiply those two numbers together.

For example, suppose your expense report contained the following:

1721
979
366
299
675
1456
In this list, the two entries that sum to 2020 are 1721 and 299. Multiplying
them together produces 1721 * 299 = 514579, so the correct answer is 514579.

Of course, your expense report is much larger. Find the two entries that sum to
2020; what do you get if you multiply them together?

Your puzzle answer was 805731.

--- Part Two ---
The Elves in accounting are thankful for your help; one of them even offers you
a starfish coin they had left over from a past vacation. They offer you a second
one if you can find three numbers in your expense report that meet the same
criteria.

Using the above example again, the three entries that sum to 2020 are 979, 366,
and 675. Multiplying them together produces the answer, 241861950.

In your expense report, what is the product of the three entries that sum to
2020?

Your puzzle answer was 192684960. */

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