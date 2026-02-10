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
	@if [ -f .bonus ]; then $(RM) .bonus $(BN_OBJS); fi
	ar rcs $(NAME) $(COM_OBJS) $(MAN_OBJS)

bonus: .bonus

.bonus: $(COM_OBJS) $(BN_OBJS)
	@if [ ! -f .bonus ]; then $(RM) $(MAN_OBJS); fi
	ar rcs $(NAME) $(COM_OBJS) $(BN_OBJS)
	@touch .bonus

clean:
	$(RM) $(OBJS_DIR) .bonus

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re

/*
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

# --- REGLAS PRINCIPALES ---

all: $(NAME)

# Compilación de archivos del directorio src
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Compilación de archivos del directorio src_bonus
$(OBJS_DIR)/%.o: $(BONUS_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Regla Mandatory
$(NAME): $(COM_OBJS) $(MAN_OBJS)
	@$(RM) .bonus
	ar rcs $(NAME) $(COM_OBJS) $(MAN_OBJS)
	@echo "Librería creada (Mandatory)"

# Regla Bonus
bonus: .bonus

.bonus: $(COM_OBJS) $(BN_OBJS)
	@$(RM) $(NAME) # Borramos la librería para asegurar que no hay mezcla de funciones
	ar rcs $(NAME) $(COM_OBJS) $(BN_OBJS)
	@touch .bonus
	@echo "Librería creada (Bonus)"

# --- LIMPIEZA ---

clean:
	$(RM) $(OBJS_DIR) .bonus

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
*/

/*
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

# Compilación de objetos (sin cambios aquí)
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR)/%.o: $(BONUS_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Regla Mandatory: Si existe el archivo .bonus, borramos todo para limpiar el estado
$(NAME): $(COM_OBJS) $(MAN_OBJS)
	@if [ -f .bonus ]; then \
		echo "Cambiando de Bonus a Mandatory..."; \
		$(RM) .bonus $(NAME); \
	fi
	ar rcs $(NAME) $(COM_OBJS) $(MAN_OBJS)
	@echo "Librería Mandatory lista."

# Regla Bonus
bonus: .bonus

# .bonus depende de los objetos. Si cambias un .c, se disparará.
.bonus: $(COM_OBJS) $(BN_OBJS)
	@if [ ! -f .bonus ]; then \
		echo "Cambiando de Mandatory a Bonus..."; \
		$(RM) $(NAME); \
	fi
	ar rcs $(NAME) $(COM_OBJS) $(BN_OBJS)
	@touch .bonus
	@echo "Librería Bonus lista."

clean:
	$(RM) $(OBJS_DIR) .bonus

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
*/

/*
#include "ft_printf.h"
#include <stdio.h>

int main(void)
{
	int	ret_orig;
	int	ret_ft;

	char *str = "Prueba: %s | Numero: %d";
	char *arg_s = "42 Malaga";
	int arg_i = 42;

	printf("--- COMPARACIÓN DE SALIDA Y RETORNO ---\n\n");

	// 1. Test con printf original
	printf("Original  : [");
	ret_orig = printf(str, arg_s, arg_i);
	
	// ¡Vaciamos el buffer aquí!
	fflush(stdout); 
	
	printf("] -> Return: %d\n", ret_orig);
	fflush(stdout);

	// 2. Test con tu ft_printf
	printf("ft_printf : [");
	fflush(stdout); // Aseguramos que el prefijo se imprima antes de tu write
	
	ret_ft = ft_printf(str, arg_s, arg_i);
	
	printf("] -> Return: %d\n", ret_ft);
	fflush(stdout);

	printf("\n---------------------------------------\n");
	
	if (ret_orig == ret_ft)
		printf("✅ Los valores de retorno coinciden.\n");
	else
		printf("❌ Error: Los retornos son diferentes.\n");

	return (0);
}
*/