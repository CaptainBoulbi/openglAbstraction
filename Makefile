PROJECTNAME=simpleGraphics
BIN=build/$(PROJECTNAME)
CC=g++

EXT=cpp
INCFOLDERS=include lib
INCDIRS=$(INCFOLDERS)

# make mode=release
ifeq ($(mode), release)
	OPT=-O3
else
	OPT=-Og -g
endif
DEPFLAGS=-MP -MD
MACROS=DEBUG=1
FLAGS=-Wall -Wextra $(foreach F,$(INCDIRS),-I$(F)) $(OPT) $(DEPFLAGS) $(foreach M,$(MACROS),-D$(M))
LDFLAGS=$(FLAGS) -lglfw3 -lX11 -Llib

APP=$(shell find . -name "*.$(EXT)" -path "./app/*")
APO=$(subst ./app/,./build/,$(APP:.$(EXT)=.o))
SRC=$(shell find . -name "*.$(EXT)" -path "./src/*")
OBJ=$(subst ./src/,./build/,$(SRC:.$(EXT)=.o))
TEST=$(shell find . -name "*.$(EXT)" -path "./test/*")
TESTO=$(subst ./test/,./build/,$(TEST:.$(EXT)=.t))
LIB=glad stb_image_imp
LIBO=$(foreach L,$(LIB),build/lib/$(L).l)

LIBIN=build/lib$(PROJECTNAME).a

$(shell mkdir -p build)


all : $(BIN)

$(BIN) : $(APO) $(LIBIN) #build/glad.o build/stb_image_imp.o
	$(CC) -o $@ $^ $(LDFLAGS)

-include $(OBJ:.o=.d)
#$(LIBO:.o=.d)

build/lib/%.l : lib/%.*
	@mkdir -p $(@D)
	$(CC) $(FLAGS) -o $@ -c $<

build/%.o : src/%.$(EXT)
	@mkdir -p $(@D)
	$(CC) $(FLAGS) -o $@ -c $<

build/%.o : app/%.$(EXT)
	@mkdir -p $(@D)
	$(CC) $(FLAGS) -o $@ -c $<

lib : $(LIBIN)

$(LIBIN) : $(OBJ) $(LIBO)
	ar rcs $@ $^

# make test file=testGenID.cpp
test : build/$(file).t
	./build/$(file).t

alltest : $(TESTO)
	@for i in $(TESTO); do echo $$i; $$i; done

build/%.t : test/%.$(EXT)
	@mkdir -p $(@D)
	$(CC) $(FLAGS) -o $@ $<

# make run input="program input"
run : $(BIN)
	./$< $(input)

clean :
	rm -rf build/*.o build/*.d build/*.t $(BIN) $(LIBIN)

clean-hard :
	rm -rf build/*

debug : $(BIN)
	gdb $< $(input)

asm : $(OBJ:.o=.s) $(BIN).s

build/%.s : src/%.$(EXT)
	@mkdir -p $(@D)
	$(CC) $(FLAGS) -S $< -o $@

$(BIN).s : $(BIN)
	objdump -drwC -Mintel -S $< > $<.s

# unzip : tar -xvf exemple.tgz
dist : clean
	$(info /!\ project folder has to be named $(PROJECTNAME) /!\ )
	cd .. && tar zcvf $(PROJECTNAME)/build/$(PROJECTNAME).tgz $(PROJECTNAME) >/dev/null

push :
	git push bbsrv master
	git push gh master

install :
	mv build/$(PROJECTNAME).tgz $$HOME/dev/opt/archive

info :
	$(info put what ever)
	@echo you want
	
check :
	cppcheck --enable=all --suppress=missingInclude missingIncludeSystem -Iinclude -Ilib/sg src lib/sg
	flawfinder src

# alias

r : run

t : test

c : clean

p : push

d : debug

.PHONY : all test t alltest run r clean c debug asm d dist push p install info check
