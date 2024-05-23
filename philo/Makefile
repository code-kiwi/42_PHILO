# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/11 15:58:10 by mhotting          #+#    #+#              #
#    Updated: 2024/05/23 11:00:42 by mhotting         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# GENERAL
NAME					=	philo
CC						=	cc
ifndef NOFLAGS
	CFLAGS				=	-Wall -Werror -Wextra
endif
HFLAGS					=	-I$(HEADERS_DIR)
PHILOFLAGS				=	-pthread -g
FSFLAGS					=	-fsanitize=address

# HEADERS
HEADERS_DIR				=	includes/
HEADERS_FILES			=	philo.h
HEADERS					=	$(addprefix $(HEADERS_DIR), $(HEADERS_FILES))

# SOURCES GENERAL
SRCS_MAIN_DIR			=	srcs/
SRCS_FILES				=	philo.c					\
							time_utils.c			\
							t_philo_data_utils.c	\
							args_validation.c		\
							utils.c
SRCS					=	$(addprefix $(SRCS_MAIN_DIR), $(SRCS_FILES))

# OBJECTS GENERAL
OBJS_MAIN_DIR			=	objs/
OBJS_FILES				=	$(SRCS_FILES:.c=.o)
OBJS					=	$(addprefix $(OBJS_MAIN_DIR), $(OBJS_FILES))

# DEPENDENCIES
DEPS_MAIN_DIR			=	deps/
DEPS_FILES				=	$(OBJS_FILES:.o=.d)
DEPS					=	$(addprefix $(DEPS_MAIN_DIR), $(DEPS_FILES))

#################################################

# RULES
all: $(NAME)

$(NAME): $(OBJS) 
	$(CC) $(CFLAGS) $(HFLAGS) $(OBJS) -o $@

$(OBJS_MAIN_DIR)%.o: $(SRCS_MAIN_DIR)%.c
	@mkdir -p $(@D)
	@mkdir -p $(DEPS_MAIN_DIR)$(dir $*)
	$(CC) $(CFLAGS) $(HFLAGS) -MP -MMD -MF $(DEPS_MAIN_DIR)$*.d -c $< -o $@ 

fsanitize: fclean $(OBJS)
	$(CC) $(CFLAGS) $(HFLAGS) $(FSFLAGS) $(OBJS) -o $(NAME)

-include $(DEPS)

clean:
	rm -rf $(OBJS_MAIN_DIR)
	rm -rf $(DEPS_MAIN_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re fsanitize
