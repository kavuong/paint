paint.out: board.o commands.o inputValidation.o main.o
	gcc -g -Wall -Werror -o paint.out board.o commands.o inputValidation.o main.o

board.o: board.c board.h boardStruct.h
	gcc -g -Wall -Werror -c board.c

commands.o: commands.c board.h commands.h inputValidation.h lineTypeEnum.h
	gcc -g -Wall -Werror -c commands.c

inputValidation.o: inputValidation.c inputValidation.h lineTypeEnum.h
	gcc -g -Wall -Werror -c inputValidation.c

main.o: main.c board.h boardStruct.h commands.h inputValidation.h
	gcc -g -Wall -Werror -c main.c

clean:
	rm -f *.o *.out