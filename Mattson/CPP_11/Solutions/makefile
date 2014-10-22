# 

include ../make.def

EXES=pi_threads$(EXE) pi_lambda_guard$(EXE) \
     pi_lambda$(EXE) 

all: $(EXES)

pi_threads$(EXE): pi_threads.$(OBJ) 
	$(CLINKER) $(OPTFLAGS) -o pi_threads pi_threads.$(OBJ) $(LIBS)

pi_lambda$(EXE): pi_lambda.$(OBJ) 
	$(CLINKER) $(OPTFLAGS) -o pi_lambda pi_lambda.$(OBJ) $(LIBS)

pi_lambda_guard$(EXE): pi_lambda_guard.$(OBJ) 
	$(CLINKER) $(OPTFLAGS) -o pi_lambda_guard pi_lambda_guard.$(OBJ) $(LIBS)

test: $(EXES)
	$(PRE)pi_threads$(EXE) 
	$(PRE)pi_lambda$(EXE) 
	$(PRE)pi_lambda_guard$(EXE) 

clean:
	$(RM) $(EXES) *.$(OBJ)

.SUFFIXES:
.SUFFIXES: .c .cpp .$(OBJ)

.c.$(OBJ):
	$(CC) $(CFLAGS) -c $<

.cpp.$(OBJ):
	$(CC) $(CFLAGS) -c $<
