/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_others.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaza-ru <adaza-ru@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 13:27:57 by adaza-ru          #+#    #+#             */
/*   Updated: 2026/01/28 13:27:57 by adaza-ru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	handle_percent(void)
{
	ft_manage_buffer('%', WRITE);
}

void	handle_char(t_print *tab, va_list *args)
{
	unsigned char	c;

	c = (unsigned char)va_arg(*args, int);
	if (!tab->dash)
		fill(tab->width - 1, ' ');
	ft_manage_buffer(c, WRITE);
	if (tab->dash)
		fill(tab->width - 1, ' ');
}

void	handle_string(t_print *tab, va_list *args)
{
	char	*str;
	int		len;
	int		i;

	i = 0;
	str = va_arg(*args, char *);
	if (!str)
	{
		str = "(null)";
		len = 6;
		if (tab->dot && tab->precision < 6)
			len = 0;
	}
	else
	{
		len = ft_strlen(str);
		if (tab->dot && tab->precision < len)
			len = tab->precision;
	}
	if (!tab->dash)
		fill(tab->width - len, ' ');
	while (str[i] && i < len)
		ft_manage_buffer(str[i++], WRITE);
	if (tab->dash)
		fill(tab->width - len, ' ');
}

void	handle_format(t_print *tab, va_list *args)
{
	if (tab->identifier == 'c')
		handle_char(tab, args);
	else if (tab->identifier == 's')
		handle_string(tab, args);
	else if (tab->identifier == 'p')
		handle_pointer(tab, args);
	else if (tab->identifier == 'd' || tab->identifier == 'i')
		handle_integer(tab, args);
	else if (tab->identifier == 'u')
		handle_unsigned(tab, args);
	else if (tab->identifier == 'x' || tab->identifier == 'X')
		handle_hexadecimal(tab, args);
	else if (tab->identifier == '%')
		handle_percent();
}

void	eval_format(const char **format, va_list *args, int *err_mod)
{
	t_print	tab;

	init_print_struct(&tab);
	parse_format(format, &tab);
	if (tab.identifier == '\0' || !ft_strchr("cspdiuxX%", tab.identifier))
	{
		while (**format != '%')
			(*format)--;
		ft_manage_buffer('%', WRITE);
		*err_mod = -1;
	}
	else
		handle_format(&tab, args);
}
