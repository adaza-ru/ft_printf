/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_numbers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaza-ru <adaza-ru@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 13:28:03 by adaza-ru          #+#    #+#             */
/*   Updated: 2026/01/28 13:28:03 by adaza-ru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int	print_num(t_print *tab, unsigned long long n, char *base, char *prefix)
{
	int	number_len;
	int	prefix_len;
	int	zeros;
	int	count;

	zeros = 0;
	count = 0;
	prefix_len = ft_strlen(prefix);
	number_len = calculate_len(n, ft_strlen(base));
	if (n == 0 && tab->dot && tab->precision == 0)
		number_len = 0;
	if (tab->precision > number_len)
		zeros = tab->precision - number_len;
	else if (tab->zero && !tab->dot && tab->width > (number_len + prefix_len))
		zeros = tab->width - (number_len + prefix_len);
	if (!tab->dash)
		count += fill((tab->width - (zeros + number_len + prefix_len)), ' ');
	count += write(1, prefix, prefix_len);
	count += fill(zeros, '0');
	if (number_len > 0)
		count += putnbr_base(n, base);
	if (tab->dash)
		count += fill((tab->width - count), ' ');
	return (count);
}

int	handle_integer(t_print *tab, va_list *args)
{
	long long			n;
	char				*prefix;
	int					count;

	count = 0;
	n = va_arg(*args, int);
	prefix = "";
	if (n < 0)
	{
		prefix = "-";
		n = -n;
	}
	else
	{
		if (tab->plus)
			prefix = "+";
		else if (tab->space)
			prefix = " ";
	}
	count += print_num(tab, (unsigned long long)n, "0123456789", prefix);
	return (count);
}

int	handle_unsigned(t_print *tab, va_list *args)
{
	unsigned int	n;
	int				count;

	count = 0;
	n = va_arg(*args, unsigned int);
	count += print_num(tab, (unsigned long long)n, "0123456789", "");
	return (count);
}

int	handle_hexadecimal(t_print *tab, va_list *args)
{
	unsigned int	n;
	char			*base;
	char			*prefix;
	int				count;

	count = 0;
	base = " ";
	n = va_arg(*args, unsigned int);
	prefix = "";
	if (tab->identifier == 'x')
		base = "0123456789abcdef";
	else if (tab->identifier == 'X')
		base = "0123456789ABCDEF";
	if (tab->hash && n != 0)
	{
		if (tab->identifier == 'x')
			prefix = "0x";
		else if (tab->identifier == 'X')
			prefix = "0X";
	}
	count += print_num(tab, (unsigned long long)n, base, prefix);
	return (count);
}

int	handle_pointer(t_print *tab, va_list *args)
{
	unsigned long long	ptr;
	int					count;
	int					print_len;

	count = 0;
	ptr = (unsigned long long)va_arg(*args, void *);
	print_len = calculate_len(ptr, 16) + 2;
	if (ptr == 0)
		print_len = 5;
	if (!tab->dash && tab->width > print_len)
		count += fill((tab->width - print_len), ' ');
	if (ptr == 0)
		count += write(1, "(nil)", 5);
	else
	{
		count += write(1, "0x", 2);
		count += putnbr_base(ptr, "0123456789abcdef");
	}
	if (tab->dash && tab->width > print_len)
		count += fill((tab->width - print_len), ' ');
	return (count);
}
