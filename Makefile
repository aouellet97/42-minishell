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
LIBRLINE	= $(LIBDIR)/libreadline.a
RLINE_V	=	readline-8.2
INCLUDES=	-I $(LIBDIR)/libft/lib -I $(INCDIR)
LIBS	=	$(LIBFT) $(LIBRLINE)

# Compiler and flags
CC		=	gcc
CFLAGS	=	-g -Wall -Werror -Wextra 
# CFLAGS +=	-Wunreachable-code -Ofast -fsanitize=address
RM		=	rm

# Sources
SRCS	:=	builtins.c			\
			builtins2.c			\
			builtin_export.c	\
			builtin_cd.c		\
			env.c				\
			env2.c				\
			errors.c			\
			execution.c			\
			execution_utils.c	\
			expands.c			\
			expand2.c			\
			heredocs.c			\
			main.c				\
			parsing.c			\
			parsing_utils.c		\
			signal.c			\
			tokens.c			\
			tokens_utils.c		\
			testing.c			\
			



B_SRCS	:=	$(SRCS:%=bonus_%)

# Objects
OBJDIR	=	obj/
OBJS		:=	$(SRCS:%.c=$(OBJDIR)%.o)
SRCS		:=	$(SRCS:%.c=$(SRCDIR)%.c)
DEPS		:=	$(OBJS:%.o=%.d)

T_SRCS		:= $(subst main,test,$(SRCS))
T_OBJS		:= $(subst main,test,$(OBJS))

#------------------------------------------------------------------------------#
#                                TARGETS                                       #
#------------------------------------------------------------------------------#

all : $(NAME)

exe :
	./$(NAME)


# Compile program
$(NAME) : $(LIBS) $(OBJS)
	@echo "$(GREEN)	Compiling $@ ... $(NC)"
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -lncurses -o $(NAME) -I. $(INCLUDES)

test: fclean $(LIBS) $(T_OBJS)
	@echo "$(GREEN)	Compiling $@ ... $(NC)"
	@$(CC) $(CFLAGS) $(T_OBJS) $(LIBS) -lncurses -o $@ -I. $(INCLUDES)
	./$@

# Compile objects
$(OBJDIR)%.o : $(SRCDIR)%.c
	@mkdir -p $(OBJDIR);
	$(CC) -c $(CFLAGS) -MMD -MP $< -o $@ $(INCLUDES)

-include $(DEPS)

$(LIBRLINE) :
	@if [ ! -f ./libs/readline/libreadline.a ]; then \
		curl -O https://ftp.gnu.org/gnu/readline/$(RLINE_V).tar.gz; \
		tar -xf $(RLINE_V).tar.gz && rm -rf $(RLINE_V).tar.gz; \
		cd $(RLINE_V) && bash configure; \
		echo "${BLUE}COMPILING READLINE ..." && make -s; \
		mv ./libreadline.a ../$(LIBDIR); \
		rm -rf ../$(RLINE_V); \
		echo "${GREEN}READLINE INSTALLED${NC}"; \
	fi

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
	@$(RM) -f $(LIB_RLINE)
	@echo "$(RED)	Removed executables 	$(NC)"

# Remake
re : fclean all

leak : re
	echo "$(BLUE)	Checking leaks ...	$(NC)"
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --track-origins=yes --trace-children=yes --suppressions=supp.txt ./$(NAME) $(ARGS)
	
.PHONY:
	all clean fclean re leak bonus