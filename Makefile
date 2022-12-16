#-----------------------------------------------------------------------
# Makefile
# Authors: Andrew Appel and Bob Dondero
#-----------------------------------------------------------------------

# This is not a proper Makefile.  It does not maintain .o files.

all: dataB testminiassembler.out dataA dataAplus

clean:
	rm -f dataB dataA dataAplus
	rm -f createdataB createdataA createdataAplus
	rm -f testminiassembler testminiassembler.out

dataB: createdataB
	./createdataB

dataA: createdataA
	./createdataA

dataAplus: createdataAplus
	./createdataAplus

createdataB: createdataB.c
	gcc217 createdataB.c -o createdataB

testminiassembler.out: testminiassembler
	./testminiassembler > testminiassembler.out

testminiassembler: testminiassembler.c miniassembler.c miniassembler.h
	gcc217 testminiassembler.c miniassembler.c -o testminiassembler

createdataA: createdataA.c miniassembler.c miniassembler.h
	gcc217 createdataA.c miniassembler.c -o createdataA

createdataAplus: createdataAplus.c miniassembler.c miniassembler.h
	gcc217 createdataAplus.c miniassembler.c -o createdataAplus
