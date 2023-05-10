EXECS?=helloworldmpi
NUM_CPU?= 4
MPICC?=mpicc
MPIRUN?=mpirun

all: ${EXECS}

${EXECS}: ${EXECS}.c
	${MPICC} -o ${EXECS} ${EXECS}.c

run: ${EXECS}
	${MPIRUN} -n ${NUM_CPU} ./${EXECS}