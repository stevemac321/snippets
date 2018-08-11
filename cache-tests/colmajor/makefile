all:
	gcc test.c -O3 -std=c11 -DCOLMAJOR -o col
	gcc test.c -O3 -std=c11 -o row
	perf stat -e task-clock,cycles,instructions,cache-references,cache-misses ./col
	perf stat -e task-clock,cycles,instructions,cache-references,cache-misses ./row

clean:
	rm -rf col
	rm -rf row

	
