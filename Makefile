# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmaluh <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/25 11:27:37 by tmaluh            #+#    #+#              #
#    Updated: 2019/11/05 12:35:13 by tmaluh           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := libwu.a
NPWD := $(CURDIR)/$(NAME)

UNAME_S := $(shell uname -s)
ECHO := echo
ifeq ($(UNAME_S),Linux)
	ECHO += -e
	LC := gcc-ar
endif
ifeq ($(UNAME_S),Darwin)
	LC := ar
endif

LC += rcs

CC_BASE := gcc -march=native -mtune=native

CC := $(CC_BASE) -Ofast -pipe -flto
CC_DEBUG := $(CC_BASE) -g3 -D DEBUG
CC_PROFILE := $(CC_BASE) -no-pie -pg -O0

CFLAGS := -Wall -Wextra -Werror -Wunused
INC := -I ~/.brew/include \
	-I $(CURDIR)/includes/ \
	-I $(CURDIR)/../libft/includes \
	-I $(CURDIR)/../libftsdl/includes \
	-I $(CURDIR)/../libvectors

SRCS := $(abspath $(wildcard srcs/wu_draw_line.c))
OBJS := $(SRCS:%.c=%.o)

DEL := rm -rf

WHITE := \033[0m
GREEN := \033[32m
RED := \033[31m
INVERT := \033[7m

SUCCESS = [$(GREEN)✓$(WHITE)]

all: $(NAME)

$(NAME): $(OBJS)
	@$(ECHO) "$(INVERT)"
	@$(ECHO) -n ' <=-=> | $(NPWD): '
	@$(LC) $(NAME) $(OBJS)
	@$(ECHO) "[$(GREEN)✓$(WHITE)$(INVERT)]$(WHITE)"
	@$(ECHO)

$(OBJS): %.o: %.c
	@$(ECHO) -n ' $@: '
	@$(CC) -c $(CFLAGS) $(INC) $< -o $@
	@$(ECHO) "$(SUCCESS)"

del:
	@$(DEL) $(OBJS)
	@$(DEL) $(NAME)

pre: del $(NAME)
	@$(ECHO) "$(INVERT)$(GREEN)Successed re-build.$(WHITE)"

set_cc_debug:
	@$(eval CC=$(CC_DEBUG))
debug_all: set_cc_debug pre
	@$(ECHO) "$(INVERT)$(NAME) $(GREEN)ready for debug.$(WHITE)"
debug: set_cc_debug all
	@$(ECHO) "$(INVERT)$(NAME) $(GREEN)ready for debug.$(WHITE)"

set_cc_profle:
	@$(eval CC=$(CC_PROFILE))
profile_all: set_cc_profle pre
	@$(ECHO) "$(INVERT)$(NAME) $(GREEN)ready for profile.$(WHITE)"
profile: set_cc_profle all
	@$(ECHO) "$(INVERT)$(NAME) $(GREEN)ready for profile.$(WHITE)"

clean:
	@$(DEL) $(OBJS)

fclean: clean
	@$(DEL) $(NAME)
	@$(ECHO) "$(INVERT)$(RED)deleted$(WHITE)$(INVERT): $(NPWD)$(WHITE)"

re: fclean all

norme:
	@$(ECHO) "$(INVERT)norminette for $(GREEN)$(NAME)$(WHITE)$(INVERT):$(WHITE)"
	@norminette includes/
	@norminette $(SRCS)

.PHONY: re fclean clean all norme del pre debug debug_all
