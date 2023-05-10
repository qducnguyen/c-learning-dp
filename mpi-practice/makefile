EXECS?=mpi_hello_world
MPICC?=mpicc
MPICXX?=mpicxx

all: ${EXECS}

mpi_hello_world: 01_mpi_hello_world/mpi_hello_world.c
	${MPICC} -o mpi_hello_world 01_mpi_hello_world/mpi_hello_world.c
send_recv: 02_mpi_send_and_receive/send_recv.c
	${MPICC} -o send_recv 02_mpi_send_and_receive/send_recv.c
ping_pong: 02_mpi_send_and_receive/ping_pong.c
	${MPICC} -o ping_pong 02_mpi_send_and_receive/ping_pong.c

ring: 02_mpi_send_and_receive/ring.c
	${MPICC} -o ring 02_mpi_send_and_receive/ring.c
check_status: 03_mpi_probe_and_mpi_status/check_status.c
	${MPICC} -o check_status 03_mpi_probe_and_mpi_status/check_status.c
probe: 03_mpi_probe_and_mpi_status/probe.c
	${MPICC} -o probe 03_mpi_probe_and_mpi_status/probe.c
random_walk: 04_random_walk_application/random_walk.cc
	${MPICXX} -o random_walk 04_random_walk_application/random_walk.cc
my_bcast: 05_mpi_broadcast_and_collective_communication/my_bcast.c
	${MPICC} -o my_bcast 05_mpi_broadcast_and_collective_communication/my_bcast.c
compare_bcast: 05_mpi_broadcast_and_collective_communication/compare_bcast.c
	${MPICC} -o compare_bcast 05_mpi_broadcast_and_collective_communication/compare_bcast.c

clean:
	rm ${EXECS}