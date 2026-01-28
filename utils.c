/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaza-ru <adaza-ru@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 13:29:51 by adaza-ru          #+#    #+#             */
/*   Updated: 2026/01/28 13:29:51 by adaza-ru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	fill(int len, char c)
{
	int	count;

	count = 0;
	while (len > 0)
	{
		count += write(1, &c, 1);
		len--;
	}
	return (count);
}

void	init_print_struct(t_print *print_struct)
{
	print_struct->dash = 0;
	print_struct->zero = 0;
	print_struct->dot = 0;
	print_struct->hash = 0;
	print_struct->space = 0;
	print_struct->plus = 0;
	print_struct->width = 0;
	print_struct->precision = -1;
	print_struct->identifier = '\0';
}
