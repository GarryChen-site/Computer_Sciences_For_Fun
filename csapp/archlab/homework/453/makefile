

test:
	(cd ../../sim; make clean; make VERSION=nobypass)
	(cd ../../sim/ptest; make SIM=../pipe/psim TFLAGS=)

debug:
	(cd ../../sim; make clean; make psim VERSION=nobypass)
	(cd ../../sim/pipe; ./psim -g ../y86-code/asum.yo)