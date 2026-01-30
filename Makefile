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

COM_FILES   = ft_printf.c utils.c
MAN_FILES   = eval_and_handle_mandatory.c handle_numbers_mandatory.c
BN_FILES    = eval_and_handle_bonus.c parse_bonus.c \
				utils_bonus.c handle_numbers_bonus.c

COM_OBJS    = $(addprefix $(OBJS_DIR)/, $(COM_FILES:.c=.o))
MAN_OBJS    = $(addprefix $(OBJS_DIR)/, $(MAN_FILES:.c=.o))
BN_OBJS     = $(addprefix $(OBJS_DIR)/, $(BN_FILES:.c=.o))

all: $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR)/%.o: $(BONUS_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(COM_OBJS) $(MAN_OBJS)
	ar rcs $(NAME) $(COM_OBJS) $(MAN_OBJS)
	@$(RM) .bonus

bonus: .bonus

.bonus: $(COM_OBJS) $(BN_OBJS)
	ar rcs $(NAME) $(COM_OBJS) $(BN_OBJS)
	@touch .bonus

clean:
	$(RM) $(OBJS_DIR) .bonus

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re