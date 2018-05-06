# compile degawongImageProcess
CC	=	g++

OBJNAME	= degaImage
INCLUDE_1 = ./
INCLUDE_2 = ./cImageMerge/
INCLUDE_3 = ./cImageFilter/

# add include directory
INCLUDE_ALL = $(patsubst %, -I %, $(wildcard ${INCLUDE_1} ${INCLUDE_2} ${INCLUDE_3}))
# add all of the src file
SRCFILE_ALL = $(wildcard ${INCLUDE_1}*.cpp ${INCLUDE_2}*.cpp ${INCLUDE_3}*.cpp)
# add all of the obj file
OBJECTS_ALL = $(patsubst %.cpp, %.o, $(SRCFILE_ALL))

CXXFLAGS    = 	-g -Wall

LIBOPENCV =	`pkg-config --libs --cflags opencv`

# make all
all:
# ${OBJNAME}:${OBJECTS_ALL}
	${CC} -o ${OBJNAME} ${INCLUDE_ALL} ${SRCFILE_ALL} ${LIBOPENCV} 
# dependence
%.o : %.cpp






# make clean
clean:
	rm -rf ${OBJNAME} ${OBJECTS_ALL}



