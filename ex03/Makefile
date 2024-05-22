NAME	:=	PmergeMe

FILES	:=	main	PmergeMe

HEADERS	:=	PmergeMe.hpp

SRCS	=	$(addsuffix .cpp, $(FILES))

OBJSDIR	:=	objsdir/

OBJS	=	$(addprefix $(OBJSDIR), $(SRCS:.cpp=.o))

CC		:=	c++

CFLAGS	:=	-Wall -Wextra -Werror -std=c++98 -g3

all: $(NAME)

$(NAME): $(HEADERS) $(OBJSDIR) $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

$(OBJSDIR):
	mkdir -p $@

$(OBJSDIR)%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJSDIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re