/** --- Day 2: Password Philosophy ---
Your flight departs in a few days from the coastal airport; the easiest way down
to the coast from here is via toboggan.

The shopkeeper at the North Pole Toboggan Rental Shop is having a bad day.
"Something's wrong with our computers; we can't log in!" You ask if you can take
a look.

Their password database seems to be a little corrupted: some of the passwords
wouldn't have been allowed by the Official Toboggan Corporate Policy that was in
effect when they were chosen.

To try to debug the problem, they have created a list (your puzzle input) of
passwords (according to the corrupted database) and the corporate policy when
that password was set.

For example, suppose you have the following list:

1-3 a: abcde
1-3 b: cdefg
2-9 c: ccccccccc
Each line gives the password policy and then the password. The password policy
indicates the lowest and highest number of times a given letter must appear for
the password to be valid. For example, 1-3 a means that the password must
contain a at least 1 time and at most 3 times.

In the above example, 2 passwords are valid. The middle password, cdefg, is not;
it contains no instances of b, but needs at least 1. The first and third
passwords are valid: they contain one a or nine c, both within the limits of
their respective policies.

How many passwords are valid according to their policies?

Your puzzle answer was 666.

The first half of this puzzle is complete! It provides one gold star: *

--- Part Two ---
While it appears you validated the passwords correctly, they don't seem to be
what the Official Toboggan Corporate Authentication System is expecting.

The shopkeeper suddenly realizes that he just accidentally explained the
password policy rules from his old job at the sled rental place down the street!
The Official Toboggan Corporate Policy actually works a little differently.

Each policy actually describes two positions in the password, where 1 means the
first character, 2 means the second character, and so on. (Be careful; Toboggan
Corporate Policies have no concept of "index zero"!) Exactly one of these
positions must contain the given letter. Other occurrences of the letter are
irrelevant for the purposes of policy enforcement.

Given the same example list from above:

1-3 a: abcde is valid: position 1 contains a and position 3 does not.
1-3 b: cdefg is invalid: neither position 1 nor position 3 contains b.
2-9 c: ccccccccc is invalid: both position 2 and position 9 contain c.
How many passwords are valid according to the new interpretation of the
policies?
Your puzzle answer was 670.*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

/** Function to read the contents of a text file and add them to a vector.
 * @param file_name is the name of the file to read.
 * @returns a vector<string> containing all of the data from file_name.
 */
std::vector<std::string> ReadFile(std::string file_name) {
  // Open file.
  std::ifstream file(file_name);
  // Vector to hold contents of file.
  std::vector<std::string> v;
  // String to temporarily hold contents of line being read in file.
  std::string line;

  try {
    // Array index to add data from input.
    int i = 0;
    // Read in all of the lines in the file.
    while (getline(file, line)) {
      // Append the contents to the vector.
      v.push_back(line);
      ++i;
    }
  } catch (const std::exception& e) {
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
  for (std::string n : container) {
    std::cout << n << ", ";
  }

  std::cout << std::endl;
}

/**
 * Class to hold properties of Passwords.
 */
class Password {
 public:
  Password(int a, int b, char p, std::string w) {
    min_number = a;
    max_number = b;
    policy = p;
    word = w;
  }

  int IsValidOne() {
    int n = std::count(word.begin(), word.end(), policy);
    if (n < min_number || n > max_number) {
      return 0;
    }
    return 1;
  }

  int IsValidTwo() {
    // Nor
    if (word[min_number - 1] == policy && word[max_number - 1] == policy) {
      return 0;
    }
    // Or
    if (word[min_number - 1] == policy || word[max_number - 1] == policy) {
      return 1;
    }
    return 0;
  }

 private:
  // Min number of times the poilcy character can appear in the Password.
  int min_number;

  // Max number of times the poilcy character can appear in the Password.
  int max_number;

  // The character/string with numerical requirements for the Password.
  char policy;

  // The password string content.
  std::string word;
};

Password ParsePassword(std::string s) {
  int i = s.find(':');
  std::string a = s.substr(0, i);
  std::string b = s.substr(i + 2, s.length());

  int j = a.find('-');
  int x = std::stoi(a.substr(0, j));
  int y = std::stoi(a.substr(j + 1, i - 1));
  char const* c = a.substr(a.length() - 1, a.length()).c_str();

  Password ret = Password(x, y, *c, b);
  return ret;
}

int main() {
  // Read in data from file.
  std::vector<std::string> input = ReadFile("day_2_input.txt");

  // Parse data into Passwords and count the number of valid Passwords
  int total = 0;
  for (auto i = input.begin(); i < input.end(); ++i) {
    total = total + ParsePassword(*i).IsValidOne();
  }

  std::cout << "Part 1 solution: " << total << std::endl;

  // Part 2
  total = 0;
  for (auto i = input.begin(); i < input.end(); ++i) {
    total = total + ParsePassword(*i).IsValidTwo();
  }

  std::cout << "Part 2 solution: " << total << std::endl;
}