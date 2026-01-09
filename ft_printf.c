/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaza-ru <adaza-ru@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 19:40:18 by adaza-ru          #+#    #+#             */
/*   Updated: 2025/12/22 19:40:18 by adaza-ru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *, ...)
{
	// Implementación de ft_printf aquí
	return (0);
}

#include <stdio.h>

int main(void)
{
	printf("Caso 1: %k\n");      // Imprime: Caso 1: k
    printf("Caso 2: %0j!\n");    // Imprime: Caso 2: 0j!
    printf("Caso 3: %-10abc\n"); // Imprime: Caso 3: -10abc
	return (0);
}