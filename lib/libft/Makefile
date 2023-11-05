#------------------------------------------------------------------------------#
#                                VARIABLES                                     #
#------------------------------------------------------------------------------#

SDIR=src/
ODIR=obj/
LDIR=lib/

CC=gcc
CFLAGS=-Wall -Werror -Wextra

NAME= libft.a
DEPS = $(LDIR)/libft.h

# TODO: DELETE WILD CARD !!!!!
SRCS = $(wildcard $(SDIR)/ft_*.c)
OBJS = $(patsubst $(SDIR)/%.c, $(ODIR)/%.o, $(SRCS))

# Colors
GREEN	=	\033[0;32m
RED		=	\033[0;31m
BLUE	=	\033[0;34m
NC		=	\033[0m

#------------------------------------------------------------------------------#
#                                TARGETS                                       #
#------------------------------------------------------------------------------#

all : $(NAME)

$(ODIR)/%.o : $(SDIR)/%.c $(DEPS)
	mkdir -p $(ODIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I$(LDIR)

$(NAME) : $(OBJS)
	@echo "$(BLUE)	Compiling libft ...	$(NC)"
	ar -rcs $@ $^

main: $(OBJS) $(NAME)
	$(CC) $(CFLAGS) -o $@ -L$(LDIR) -lft

clean :
	rm -f $(ODIR)/*.o

fclean : clean
	rm -f $(NAME) main

re : fclean all

.PHONY : all re clean fclean