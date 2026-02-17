# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adaza-ru <adaza-ru@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/29 23:54:20 by adaza-ru          #+#    #+#              #
#    Updated: 2026/01/29 23:54:20 by adaza-ru         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = libftprintf.a
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -I.
RM          = rm -rf

SRCS_DIR    = src
BONUS_DIR   = src_bonus
OBJS_DIR    = obj

STATE_MAN   = .mandatory
STATE_BN    = .bonus

SRC         = ft_printf.c eval_and_handle_mandatory.c \
			utils.c handle_numbers_mandatory.c

BONUS_SRC   = ft_printf_bonus.c utils_bonus.c \
			eval_and_handle_bonus.c parse_bonus.c \
			handle_numbers_bonus.c bonus_utils_bonus.c

MAN_OBJS    = $(addprefix $(OBJS_DIR)/mandatory/, $(SRC:.c=.o))
BN_OBJS     = $(addprefix $(OBJS_DIR)/bonus/, $(BONUS_SRC:.c=.o))

.PHONY: all bonus clean fclean re

all: $(NAME)

$(NAME): $(STATE_MAN)

bonus: $(STATE_BN)

$(STATE_MAN): $(MAN_OBJS)
	@$(RM) $(STATE_BN)
	$(RM) $(NAME)
	ar rcs $(NAME) $(MAN_OBJS)
	@touch $(STATE_MAN)

$(STATE_BN): $(BN_OBJS)
	@$(RM) $(STATE_MAN)
	$(RM) $(NAME)
	ar rcs $(NAME) $(BN_OBJS)
	@touch $(STATE_BN)

$(OBJS_DIR)/mandatory/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR)/bonus/%.o: $(BONUS_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS_DIR) $(STATE_MAN) $(STATE_BN)

fclean: clean
	$(RM) $(NAME)

re: fclean all

