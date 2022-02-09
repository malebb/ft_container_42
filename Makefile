SRCS_FT = ./srcs/main.cpp

OBJS_FT = ${SRCS_FT:.cpp=.o}

SRCS_STL = ./srcs/main_stl.cpp

OBJS_STL = ${SRCS_STL:.cpp=.o}

DEP = ${SRCS_FT:.cpp=.d} ${SRCS_STL:.cpp=.d}

CC = clang++

CFLAGS = -Wall -Wextra -Werror -std=c++11 -I ./incl/containers/ -I ./incl/iterator/

NAME = ft_containers
NAME2 = stl_containers
RM	= rm -rf

.PHONY:		all
all:		${NAME} ${NAME2}

$(NAME):	${OBJS_FT}
			${CC} ${OBJS_FT} -o ${NAME} 

$(NAME2):	${OBJS_STL}
			${CC} ${OBJS_STL} -o ${NAME2}

-include ${DEP}

%.o:%.cpp Makefile
		${CC} -MMD -MP -o $@ -c $< ${CFLAGS}

.PHONY:		clean
clean:
			${RM} ${OBJS_FT} ${OBJS_STL} ${DEP}

.PHONY:		fclean
fclean:		clean
			${RM} ${NAME} ${NAME2}

.PHONY:		re
re:			fclean all
