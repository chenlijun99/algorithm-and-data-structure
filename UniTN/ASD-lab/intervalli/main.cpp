#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <utility>
#include <vector>

using interval_delimiter = uint64_t;
using interval = std::pair<interval_delimiter, interval_delimiter>;

interval get_max_uncovered_interval(std::vector<interval> &intervals) {
	std::sort(intervals.begin(), intervals.end(),
			[](const interval &a, const interval &b) { return a.first < b.first; });

	interval_delimiter last_end = intervals[0].first;
	interval uncovered_interval(0, 0);
	for (const auto &interval : intervals) {
		if (last_end < interval.first &&
				interval.first - last_end >
				uncovered_interval.second - uncovered_interval.first) {
			uncovered_interval.first = last_end;
			uncovered_interval.second = interval.first;
		}
		// in case a subsequent range is inside a previous range
		if (interval.second > last_end) {
			last_end = interval.second;
		}
	}
	return uncovered_interval;
}

int main(int argc, char *argv[]) {
	std::ifstream fin("input.txt");
	std::ofstream fout("output.txt");

	uint32_t N;
	fin >> N;
	std::vector<interval> intervals;
	intervals.reserve(N);
	{
		interval_delimiter start;
		interval_delimiter end;
		for (uint32_t i = 0; i < N; ++i) {
			fin >> start >> end;
			intervals.push_back(std::make_pair(start, end));
		}
	}

	interval uncovered_interval = get_max_uncovered_interval(intervals);
	if (uncovered_interval.first == 0) {
		fout << 0;
	} else {
		fout << uncovered_interval.first << " " << uncovered_interval.second;
	}
	return 0;
}
