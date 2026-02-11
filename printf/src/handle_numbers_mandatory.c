/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_numbers_mandatory.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaza-ru <adaza-ru@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 02:40:55 by adaza-ru          #+#    #+#             */
/*   Updated: 2026/01/30 02:40:55 by adaza-ru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	handle_integer_mandatory(va_list *args)
{
	long long			n;
	int					count;

	count = 0;
	n = va_arg(*args, int);
	if (n < 0)
	{
		count += write(1, "-", 1);
		n = -n;
	}
	count += putnbr_base((unsigned long long)n, "0123456789");
	return (count);
}

int	handle_unsigned_mandatory(va_list *args)
{
	unsigned int	n;
	int				count;

	count = 0;
	n = va_arg(*args, unsigned int);
	count += putnbr_base((unsigned long long)n, "0123456789");
	return (count);
}

int	handle_hexadecimal_mandatory(va_list *args, char c)
{
	unsigned int	n;
	int				count;

	count = 0;
	n = va_arg(*args, unsigned int);
	if (c == 'x')
		count += putnbr_base((unsigned long long)n, "0123456789abcdef");
	else if (c == 'X')
		count += putnbr_base((unsigned long long)n, "0123456789ABCDEF");
	return (count);
}

int	handle_pointer_mandatory(va_list *args)
{
	unsigned long long	ptr;
	int					count;

	count = 0;
	ptr = (unsigned long long)va_arg(*args, void *);
	if (ptr == 0)
		count += write(1, "(nil)", 5);
	else
	{
		count += write(1, "0x", 2);
		count += putnbr_base(ptr, "0123456789abcdef");
	}
	return (count);
}
