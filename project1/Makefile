# sample Makefile that you can quickly adapt to your needs
# set compiler options here
CPPFLAGS=-g -Wall -g3 -std=c++11

# set the name of the executable file to compile here
program=vaccineMonitor

# list object files needed to compile the program
objects=main.o InputManager.o IsValid.o Free.o CitizenRecord.o CitizenVirus.o List.o BloomFilter.o VirusBloom.o SkipList.o VirusSkip.o

# arguments to run the program
args = -c inputA.txt -b 102400

# this makes the program. It's the first rule so it will be executed if you give just 'make'
$(program) : $(objects)
	g++ $(CPPFLAGS) $(objects) -o $(program)

# list .h dependencies for each .o (dependency on .c is automatically set by make!)
main.o : Interface.h
InputManager.o : Interface.h
IsValid.o : Interface.h
Free.o : Interface.h
CitizenRecord.o : CitizenRecord.h
CitizenVirus.o : CitizenVirus.h
List.o : List.h
BloomFilter.o : BloomFilter.h
VirusBloom.o : VirusBloom.h
SkipList.o : SkipList.h
VirusSkip.o : VirusSkip.h

# this allows to quickly remove all generated files with 'make clean'
clean:
	rm $(program) $(objects) inputFile.txt

# run the program with 'make run'. Sometimes useful to avoid rewriting long commands.
run: $(program)
	./$(program) $(args)	

valgrind: $(program)
	valgrind --track-origins=yes ./$(program) $(args)