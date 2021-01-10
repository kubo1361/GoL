CLIENT = Client/
SERVER = Server/
OUTPUTS = ${CLIENT}main ${SERVER}main
OUT_O = ${CLIENT}Connection.o ${CLIENT}Game.o ${CLIENT}Menu.o ${CLIENT}main.o ${SERVER}Connection.o ${SERVER}Game.o ${SERVER}ServerStorage.o  ${SERVER}main.o
CC = g++

all: ${OUT_O} ${OUTPUTS}

clean:
	rm -f ${OUTPUTS}
	rm -f ${CLIENT}*.o ${SERVER}*.o

.PHONY: all clean

%.o: %.cpp
	${CC} -c -o $@ $<

%: %.o
	${CC} -o $@ -lpthread $^
	${CC} -o $@ -lncurses $^
	${CC} -o $@ -lstdc++fs $^

${CLIENT}main: ${CLIENT}main.o $CLIENT}Spojenie.o
${SERVER}main: ${SERVER}main.o ${SERVER}Spojenie.o ${SERVER}Uzivatel.o ${SERVER}Server.o
