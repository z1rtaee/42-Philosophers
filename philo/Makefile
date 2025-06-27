### COLOURS ###
PINK 	= \e[1;35m
PURPLE	= \e[0;95m
WHITE   = \e[1;37m
DEFAULT = \e[0m

### VARIABLES ###
NAME			= philo

CC				= cc
CFLAGS			= -Wall -Wextra -Werror -g
INCLUDE			= -I inc/

### MINISHELL SRCS ###
SRCS	 		= main.c free_exit_error.c parser.c mutex_manager.c philo.c utils.c init.c monitor.c
SRC_PATH		= src/

TOTAL_SRCS		= $(words $(SRCS))
FILES			= 0

### OBJECTS ###
OBJS_PATH		= obj/
OBJS 			= $(SRCS:%.c=$(OBJS_PATH)%.o)
ALL_OBJ			= $(OBJS_PATH)*.o

vpath %.c $(SRC_PATH) 

### RULES ###
all: 			$(NAME)

$(OBJS_PATH)%.o: %.c | $(OBJS_PATH)
				@$(CC) $(CFLAGS) $(INCLUDE) -pthread -c $< -o $@ && \
				$(eval FILES=$(shell echo $$(($(FILES) + 1)))) \
				$(call PRINT_PROGRESS, $(TOTAL_SRCS),$(PINK), $(WHITE)Compiling$(DEFAULT) $@)

$(OBJS_PATH):
				@mkdir -p $@

$(NAME): 		$(OBJS) $(OBJS_PATH)
				@echo "$(WHITE)Bringing $(PINK)$(NAME)$(WHITE) to life!$(DEFAULT)"
				@echo "$(WHITE)Creating $(PINK)$(NAME)'s$(WHITE) executable...$(DEFAULT)"
				@$(CC) $(CFLAGS) $(OBJS) -o $@
				@echo "$(PINK)$(NAME) was born!$(DEFAULT)"

### CLEAN RULES ###
clean:
				@rm -rf $(OBJS)
				@rm -rf obj
				@echo "$(WHITE)✩°｡⋆ $(PINK)Files Cleaned$(WHITE) ⋆｡°✩ \n \
	(\ (\    \n \
( ~_•)    \n \
(っ▄︻▇〓▄︻┻┳═ ─ ҉.  \n \
 /　 )  / \    \n \
(/￣∪  /   \ $(DEFAULT)"

fclean: 		clean
				@rm -f $(NAME)
				@echo "$(WHITE)⋆˚࿔ Executable Killed˚⋆♡$(DEFAULT)"

re: 			fclean all

.PHONY: 		all clean fclean re

define PRINT_PROGRESS
    if [ "$(FILES)" -eq "1" ]; then \
        printf "\033[0K$(3)\n["; \
    else \
        printf "\033[0K\033[1F\033[0K$(3)\n["; \
    fi
    @for i in `seq 1 $(shell expr $(FILES) \* 70 / $(1))`; do \
        printf "$(2)=\033[0m"; \
    done
    @for i in `seq 1 $(shell expr 70 - $(FILES) \* 70 / $(1))`; do \
        printf " "; \
    done
    @printf "] $(shell echo $$(($(FILES) * 100 / $(1))))%%"
	if [ "$(FILES)" -eq "$(1)" ]; then \
        printf "\n"; \
	fi
endef