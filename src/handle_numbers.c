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

#include "ft_printf.h"

void	print_num(t_print *tab, unsigned long long n, char *base, char *prefix)
{
	int	number_len;
	int	prefix_len;
	int	zeros;

	zeros = 0;
	prefix_len = ft_strlen(prefix);
	number_len = calculate_len(n, ft_strlen(base));
	if (n == 0 && tab->dot && tab->precision == 0)
		number_len = 0;
	if (tab->precision > number_len)
		zeros = tab->precision - number_len;
	else if (tab->zero && !tab->dot && tab->width > (number_len + prefix_len))
		zeros = tab->width - (number_len + prefix_len);
	if (!tab->dash)
		fill((tab->width - (zeros + number_len + prefix_len)), ' ');
	ft_putstr_buffer(prefix);
	fill(zeros, '0');
	if (number_len > 0)
		putnbr_base(n, base);
	if (tab->dash)
		fill((tab->width - (zeros + number_len + prefix_len)), ' ');
}

void	handle_integer(t_print *tab, va_list *args)
{
	long long			n;
	char				*prefix;

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
	print_num(tab, (unsigned long long)n, "0123456789", prefix);
}

void	handle_unsigned(t_print *tab, va_list *args)
{
	unsigned int	n;

	n = va_arg(*args, unsigned int);
	print_num(tab, (unsigned long long)n, "0123456789", "");
}

void	handle_hexadecimal(t_print *tab, va_list *args)
{
	unsigned int	n;
	char			*base;
	char			*prefix;

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
	print_num(tab, (unsigned long long)n, base, prefix);
}

void	handle_pointer(t_print *tab, va_list *args)
{
	unsigned long long	ptr;
	int					print_len;

	ptr = (unsigned long long)va_arg(*args, void *);
	print_len = calculate_len(ptr, 16) + 2;
	if (ptr == 0)
		print_len = 5;
	if (!tab->dash && tab->width > print_len)
		fill((tab->width - print_len), ' ');
	if (ptr == 0)
		ft_putstr_buffer("(nil)");
	else
	{
		ft_putstr_buffer("0x");
		putnbr_base(ptr, "0123456789abcdef");
	}
	if (tab->dash && tab->width > print_len)
		fill((tab->width - print_len), ' ');
}
