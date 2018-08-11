all:
	clang++ -std=c++17 -O3 -o map map.cpp
	clang++ -std=c++17 -O3 -o unordered unordered.cpp
	clang++ -std=c++17 -O3 -o openmap open.cpp
	clang++ -std=c++17 -O3 -o vector vector.cpp
	clang++ -std=c++17 -O3 -o fast fast.cpp
	perf stat -e task-clock,cycles,instructions,cache-references,cache-misses ./map
	perf stat -e task-clock,cycles,instructions,cache-references,cache-misses ./unordered
	perf stat -e task-clock,cycles,instructions,cache-references,cache-misses ./vector
	perf stat -e task-clock,cycles,instructions,cache-references,cache-misses ./openmap
	perf stat -e task-clock,cycles,instructions,cache-references,cache-misses ./fast

prof:
	clang++ map.cpp -std=c++17 -g -pg -o map
	./map
	gprof map gmon.out > map.prof
	clang++ open.cpp -std=c++17 -g -pg -o openmap
	./openmap
	gprof openmap gmon.out  > openmap.prof
	clang++ unordered.cpp -std=c++17 -g -pg -o unordered
	./unordered
	gprof unordered gmon.out  > unordered.prof
	clang++ vector.cpp -std=c++17 -g -pg -o vector
	./vector
	gprof vector gmon.out > vector.prof

stress:
	clang++ -std=c++17 -O3 -DSTRESS -o openmap open.cpp
	clang++ -std=c++17 -O3 -DSTRESS -o unordered unordered.cpp
	clang++ -std=c++17 -O3 -DSTRESS -o fast fast.cpp
	perf stat -e task-clock,cycles,instructions,cache-references,cache-misses ./unordered
	perf stat -e task-clock,cycles,instructions,cache-references,cache-misses ./openmap
	perf stat -e task-clock,cycles,instructions,cache-references,cache-misses ./fast

debug:
	scan-build clang++ -std=c++17 -ggdb -fsanitize=address -o openmap open.cpp
cov:
	g++ -Wall -fprofile-arcs -ftest-coverage unordered.cpp -o unordered
	./unordered
	gcov unordered.cpp

clean:
	rm -f map
	rm -f unordered
	rm -f openmap
	rm -f vector
	rm -f fast
	rm -f openmap.prof
	rm -f unordered.prof
	rm -f vector.prof
	rm -f map.prof
	rm -f gmon.out
