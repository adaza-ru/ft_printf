/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaza-ru <adaza-ru@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 12:20:47 by adaza-ru          #+#    #+#             */
/*   Updated: 2026/01/28 12:20:47 by adaza-ru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

void	apply_hierarchy(t_print *tab)
{
	if (tab->dash)
		tab->zero = 0;
	if (tab->plus)
		tab->space = 0;
	if (tab->dot && ft_strchr("diuxX", tab->identifier) && tab->precision >= 0)
		tab->zero = 0;
}

int	parse_value(const char **format)
{
	int	n;

	n = 0;
	while (ft_isdigit(**format))
	{
		n = (n * 10) + (**format - '0');
		(*format)++;
	}
	return (n);
}

void	parse_flags(const char **format, t_print *tab)
{
	if (**format == '-')
		tab->dash = 1;
	else if (**format == '0')
		tab->zero = 1;
	else if (**format == '#')
		tab->hash = 1;
	else if (**format == ' ')
		tab->space = 1;
	else if (**format == '+')
		tab->plus = 1;
	(*format)++;
}

void	parse_format(const char **format, t_print *tab)
{
	while (**format && ft_strchr("-0# +", **format))
		parse_flags(format, tab);
	if (ft_isdigit(**format))
		tab->width = parse_value(format);
	if (**format == '.')
	{
		(*format)++;
		tab->dot = 1;
		tab->precision = parse_value(format);
	}
	if (**format)
		tab->identifier = **format;
	apply_hierarchy(tab);
}
