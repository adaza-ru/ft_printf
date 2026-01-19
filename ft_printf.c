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
	va_list	args;
	t_print	*print_format;
	int		i;

	i = 0;
	va_start(args, format);
	print_format = NULL;

	return (i);
}

/*
#include <stdio.h>

int main(void)
{
	printf("ft_printf	|	printf original\n");

    ft_printf("Hello World!	|	");
	printf("Hellow World!\n");


		return (0);
}
*/