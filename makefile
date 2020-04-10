all: sorter coach0 coach1 coach2 coach3 mysort

sorter: sorter.c quick.c heap.c
	gcc -o sorter sorter.c quick.c heap.c

coach0: coach0.c 
	gcc -o coach0 coach0.c 

coach1: coach1.c merge.c
	gcc -o coach1 coach1.c merge.c

coach2: coach2.c merge.c
	gcc -o coach2 coach2.c merge.c

coach3: coach3.c merge.c
	gcc -o coach3 coach3.c merge.c

mysort: coordinator.c
	gcc -o mysort coordinator.c

clean:
	rm -f sorter coach0 coach1 coach2 coach3 mysort
