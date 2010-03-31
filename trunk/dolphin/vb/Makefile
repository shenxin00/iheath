echo "=========make start========="
#
#    VxmlI Makefile
#	Test xerces-c module
#    OM/sunyan 2007/11/19
#                    

MAKEFILE		= Makefile

CC				= g++

CXX				= g++

STRIP			= strip

TOP		    	=

COMMON_DIR		=

XERCES_DIR		=

#########################################################

LIBS			= -lxerces-c

OBJS			= simlib.o \
					VxmlSAXHandler.o VxmlBuilder.o \
					VxmlMenu.o VxmlPrompt.o \
					VxmlAbsComponte.o VxmlDocument.o \
					VxmlObject.o  VxmlPlatForm.o\
					VxmlChoice.o VxmlInterpreter.o VxmlParser.o \
#					VxmlTag.o

#########################################################
SIM_TARGET		= sim
SB_TARGET		= sb


#########################################################
SRCS			= sim.c sb.c simlib.c \
					VxmlSAXHandler.cpp VxmlBuilder.cpp \
					VxmlMenu.cpp VxmlPrompt.cpp \
					VxmlAbsComponte.cpp VxmlDocument.cpp \
					VxmlObject.cpp  VxmlPlatForm.cpp\
					VxmlChoice.cpp VxmlInterpreter.cpp VxmlParser.cpp \
#					VxmlTag.cpp \

HEADERS			= simlib.h comm.h \
					VxmlSAXHandler.h VxmlBuilder.h \
					VxmlAbsComponte.h VxmlComponte.h \
					VxmlAbsInterpreter.h VxmlPlatForm.h VxmlAbsPlatForm.h\
					VxmlInterpreter.h VxmlParser.h \

#########################################################

INCLUDES		= -I. -I./include \

DEBUG			= -g

CFLAGS			= $(DEBUG)

LFLAGS			= -pthread 


#
# Compile Menu
#

.PHONY		: all
all		: ${SB_TARGET}

.PHONY		: clean
clean		:
	rm -f ${SIM_TARGET} ${SB_TARGET} *.o

#${SIM_TARGET}	: OBJS
#	${CC} -o ${SIM_TARGET} ${SIM_TARGET}.o ${OBJS} ${LFLAGS} ${LIBS}
	
${SB_TARGET}	: OBJS
	${CC} -o ${SB_TARGET} ${SB_TARGET}.o ${OBJS}  ${LFLAGS} ${LIBS}

.PHONY		: OBJS
OBJS		: ${SRCS} ${HEADERS}
	${CC} -c ${SRCS} ${CFLAGS} ${INCLUDES}
	
	
	

