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
    // Flags
    int dash;       // '-'
    int zero;       // '0'
    int dot;        // '.' (precisión)
    int hash;       // '#'
    int space;      // ' '
    int plus;       // '+'
    
    // Valores
    int width;      // Ancho mínimo
    int precision;  // Valor tras el punto
    char identifier;      // El conversor (c, s, d, etc.)
    
    int total_len;  // Contador acumulado para el return final
} t_print;


int	ft_printf(const char *, ...);