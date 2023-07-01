#------------------------------------------------------------------------------#
#                                VARIABLES                                     #
#------------------------------------------------------------------------------#

ARGS	=	""
NAME	=	minishell

# Colors
GREEN	=	\033[0;32m
RED		=	\033[0;31m
BLUE	=	\033[0;34m
NC		=	\033[0m

# Directories
LIBDIR	=	lib/
INCDIR	=	include/
SRCDIR	=	src/

# Libraries
LIBFT	=	$(LIBDIR)/libft/libft.a
INCLUDES=	-I $(LIBDIR)/libft -I $(INCDIR)
LIBS	=	$(LIBFT)

# Compiler and flags
CC		=	gcc
CFLAGS	=	-Wall -Werror -Wextra
CFLAGS +=	-Wunreachable-code -Ofast
RM		=	rm

# Sources
SRCS	:=	main.c
B_SRCS	:=	$(SRCS:%=bonus_%)

# Objects
OBJDIR	=	obj/
OBJS		:=	$(SRCS:%.c=$(OBJDIR)%.o)
SRCS		:=	$(SRCS:%.c=$(SRCDIR)%.c)
DEPS		:=	$(OBJS:%.o=%.d)


#------------------------------------------------------------------------------#
#                                TARGETS                                       #
#------------------------------------------------------------------------------#

all : $(NAME)

# Compile program
$(NAME) : $(LIBFT) $(OBJS)
	@echo "$(GREEN)	Compiling $@ ... $(NC)"
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME) -I. $(INCLUDES)

# Compile objects
$(OBJDIR)%.o : $(SRCDIR)%.c
	@mkdir -p $(OBJDIR);
	$(CC) -c $(CFLAGS) -MMD -MP $< -o $@ $(INCLUDES)

-include $(DEPS)

# Compile libft
$(LIBFT):
	@ $(MAKE) -C $(LIBDIR)/libft -s

# Remove objects
clean :
	@$(RM) -rf $(OBJDIR)
	@$(RM) -rf $(NAME).dSYM
	@echo "$(RED)	Removed objects	$(NC)"

# Remove all
fclean : clean
	@$(RM) -f $(NAME) bonus
	@$(MAKE) fclean -C $(LIBDIR)/libft -s
	@echo "$(RED)	Removed executables and libft	$(NC)"

# Remake
re : fclean all

leak :
	echo "$(BLUE)	Checking leaks ...	$(NC)"
	valgrind --leak-check=full --show-leak-kinds=all --trace-children=no --track-fds=no ./$(NAME) $(ARGS)

.PHONY:
	all clean fclean re leak bonus