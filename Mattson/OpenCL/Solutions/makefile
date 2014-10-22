#
#  USAGE:
#     make          ... to build the program
#     make test     ... to run the default test case
#     make clean    ... remove object and executable files.
#

# verify that you are including the right make.def file for the platform
include ../make.def

COMMON      = ../Cpp_common

EXES     = vadd_chain$(EXE) vadd_abc$(EXE) pi_ocl$(EXE) \
           matmul_par$(EXE)

MMULOBJS = matmul_par.$(OBJ) matrix_lib.$(OBJ)

COMM_OBJS = $(COMMON)/wtime.$(OBJ) $(COMMON)/err_code.$(OBJ) \

all: $(EXES)

vadd_chain$(EXE): vadd_chain.$(OBJ) $(COMM_OBJS) 
	$(CLINKER) $(CFLAGS) $(OPENCLFLAGS) -o vadd_chain$(EXE) \
                         vadd_chain.$(OBJ) $(COMM_OBJS) $(LIBS)

vadd_abc$(EXE): vadd_abc.$(OBJ) $(COMM_OBJS) 
	$(CLINKER) $(CFLAGS) $(OPENCLFLAGS) -o vadd_abc$(EXE) \
                         vadd_abc.$(OBJ) $(COMM_OBJS) $(LIBS)

pi_ocl$(EXE): pi_ocl.$(OBJ) $(COMM_OBJS) 
	$(CLINKER) $(CFLAGS) $(OPENCLFLAGS) -o pi_ocl$(EXE) \
                         pi_ocl.$(OBJ) $(COMM_OBJS) $(LIBS)

matmul_par$(EXE): $(MMULOBJS) $(COMM_OBJS) 
	$(CLINKER) $(CFLAGS) $(OPENCLFLAGS) -o matmul_par$(EXE) \
                   $(MMULOBJS) $(COMM_OBJS) $(LIBS)

$(COMMON)/wtime.$(OBJ): $(COMMON)/wtime.c
	$(CC) -c $(CFLAGS) -o $(COMMON)/wtime.$(OBJ)  $(COMMON)/wtime.c

$(COMMON)/err_code.$(OBJ): $(COMMON)/err_code.c
	$(CC) -c $(CFLAGS) -o $(COMMON)/err_code.$(OBJ)  $(COMMON)/err_code.c

test: $(EXES)
	$(PRE)vadd_chain$(EXE)
	$(PRE)vadd_abc$(EXE)
	$(PRE)matmul_par$(EXE)
	$(PRE)pi_ocl$(EXE)
clean:
	$(RM) $(EXES) *.$(OBJ) $(COMM_OBJS)

veryclean:
	$(RM) $(EXES) $(COMM_OBJS) *.$(OBJ)

.SUFFIXES:
.SUFFIXES: .c .cpp .$(OBJ)

.c.$(OBJ):
	$(CC) $(CFLAGS) -c $<

.cpp.$(OBJ):
	$(CC) $(CFLAGS) -c $<

