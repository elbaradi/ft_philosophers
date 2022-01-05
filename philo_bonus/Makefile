# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: tel-bara <tel-bara@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/09/09 17:13:24 by tel-bara      #+#    #+#                  #
#    Updated: 2021/09/20 17:06:16 by tel-bara      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME	=	philo_bonus
SRCDIR	=	srcs
OBJDIR	=	objs
SRCS	=	$(SRCDIR)/death.c \
			$(SRCDIR)/input.c \
			$(SRCDIR)/main.c \
			$(SRCDIR)/prompt.c \
			$(SRCDIR)/routine.c \
			$(SRCDIR)/simulation.c \
			$(SRCDIR)/simulation2.c \
			$(SRCDIR)/specs.c \
			$(SRCDIR)/timestamp.c \
			$(SRCDIR)/utils.c
OBJS	=	$(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
CC		=	gcc
INCS	=	-Iincludes/
FLAGS	=	-O3 -Wall -Wextra -Werror
MSG		=	"Use ./$(NAME) number_of_philosophers time_to_die time_to_eat \
			time_to_sleep [number_of_times_each_philosopher_must_eat]"
BUILD_MSG	=	"Building objects... %-33.33s\r"
COMPILE_MSG	=	"All objects have been built. Compiling...\r"
DONE_MSG	=	"All objects have been built. Compiling done."
CLEAN_MSG	=	"Objects have been deleted."
FCLEAN_MSG	=	"Executable has been deleted."

all:		$(NAME)

$(NAME):	$(OBJS)
			@printf $(COMPILE_MSG)
			@$(CC) $(OBJS) $(FLAGS) -o $(NAME) -lpthread
			@echo $(DONE_MSG)
			@echo "\n"
			@echo $(MSG)

$(OBJDIR)/%.o:	$(SRCDIR)/%.c
				@mkdir -p $(OBJDIR)
				@printf $(BUILD_MSG) $@
				@$(CC) $(FLAGS) -c -o $@ $< $(INCS)

clean:
			@rm -rf $(OBJDIR)
			@echo $(CLEAN_MSG)

fclean:		clean
			@rm -rf $(NAME)
			@echo $(FCLEAN_MSG)

re:			fclean all

.PHONY:		all clean fclean re .c.o
