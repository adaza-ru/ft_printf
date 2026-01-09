/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaza-ru <adaza-ru@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 18:55:51 by adaza-ru          #+#    #+#             */
/*   Updated: 2025/12/22 18:55:51 by adaza-ru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//variaticas
#include <stdarg.h>
//write
#include <unistd.h>
//malloc, free
#include <stdlib.h>

typedef struct s_print
{
	int		left_justify;		/* '-' flag */
	int		zero_pad;			/* '0' flag */
	int		precision;			/* Precisión especificada */
	int		precision_set;		/* Si se estableció precisión */
	int		width;				/* Ancho mínimo */
	int		alternate;			/* '#' flag */
	int		space;				/* ' ' flag */
	int		plus;				/* '+' flag */
	int		neg_precision;		/* Para manejar precisión negativa */
	int		is_negative;		/* Para números negativos */
	int		length;				/* Modificadores: h, hh, l, ll */
	char	specifier;			/* c, s, p, d, i, u, x, X, % */
}	t_print;


int	ft_printf(const char *, ...);