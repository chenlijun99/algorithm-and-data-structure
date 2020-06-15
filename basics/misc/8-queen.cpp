#include <iostream>
#include <vector>

void print_solution(const std::vector<unsigned int> &solution) {
	for (unsigned int i = 0; i < solution.size(); ++i) {
		std::cout << "|";
		for (unsigned int j = 0; j < solution.size(); ++j) {
			if (solution[i] == j) {
				std::cout << "O";
			} else {
				std::cout << " ";
			}
			std::cout << "|";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void n_queen(unsigned int n, std::vector<unsigned int> rows, unsigned int &counts) {
	if (rows.size() == n) {
		counts++;
		print_solution(rows);
	}

	bool legal = true;
	unsigned int current_row = rows.size();
	for (unsigned int i = 0; i < n; ++i) {
		// for each column
		legal = true;
		for (unsigned int j = 0; j < current_row; ++j) {
			// for each previous rows

			// column already occupied
			if (rows[j] == i) {
				legal = false;
				break;
			}

			// already a queen on the diagonal (right-side)
			if (rows[j] == i + (current_row - j)) {
				legal = false;
				break;
			}

			// already a queen on the diagonal (left-side)
			if (rows[j] == i - (current_row - j)) {
				legal = false;
				break;
			}
		}

		if (legal) {
			rows.push_back(i);
			n_queen(n, rows, counts);
			rows.pop_back();
		}
	}
}

unsigned int n_queen(unsigned int n) {
	std::vector<unsigned int> rows;
	rows.reserve(n);
	unsigned int counts = 0;

	n_queen(n, rows, counts);
	return counts;
}

int main(int argc, char *argv[])
{
	unsigned int counts = n_queen(8);
	std::cout << counts << std::endl;
	return 0;
}
