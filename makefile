build:
	gcc -Wall area.c -o area
	gcc -Wall perimeter.c -o perimeter
	gcc -Wall -pthread asg1.c -o asg1

run:
	./asg1 10 5 GoTigers

clean:
	rm -rf area perimeter asg1

