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

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (2048);
	else
		return (0);
}

void	fill(int len, char c)
{
	while (len > 0)
	{
		ft_manage_buffer(c, WRITE);
		len--;
	}
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

int	calculate_len(unsigned long long nbr, int base_len)
{
	int	len;

	len = 1;
	while (nbr >= (unsigned long long)base_len)
	{
		nbr /= base_len;
		len++;
	}
	return (len);
}
