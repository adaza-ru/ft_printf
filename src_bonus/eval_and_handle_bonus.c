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

#include "ft_printf_bonus.h"

int	handle_percent(void)
{
	int	count;

	count = 0;
	count += write(1, "%", 1);
	return (count);
}

int	handle_char(t_print *tab, va_list *args)
{
	int				count;
	unsigned char	c;

	count = 0;
	c = (unsigned char)va_arg(*args, int);
	if (!tab->dash)
		count += fill(tab->width - 1, ' ');
	count += write(1, &c, 1);
	if (tab->dash)
		count += fill(tab->width - 1, ' ');
	return (count);
}

int	handle_string(t_print *tab, va_list *args)
{
	char	*str;
	int		len;
	int		count;

	count = 0;
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
		count += fill(tab->width - len, ' ');
	count += write(1, str, len);
	if (tab->dash)
		count += fill(tab->width - len, ' ');
	return (count);
}

int	handle_format(t_print *tab, va_list *args)
{
	int	len;

	len = 0;
	if (tab->identifier == 'c')
		len = handle_char(tab, args);
	else if (tab->identifier == 's')
		len = handle_string(tab, args);
	else if (tab->identifier == 'p')
		len = handle_pointer(tab, args);
	else if (tab->identifier == 'd' || tab->identifier == 'i')
		len = handle_integer(tab, args);
	else if (tab->identifier == 'u')
		len = handle_unsigned(tab, args);
	else if (tab->identifier == 'x' || tab->identifier == 'X')
		len = handle_hexadecimal(tab, args);
	else if (tab->identifier == '%')
		len = handle_percent();
	return (len);
}

int	eval_format(const char **format, va_list *args)
{
	t_print	tab;
	int		len;

	init_print_struct(&tab);
	parse_format(format, &tab);
	if (tab.identifier == '\0' || !ft_strchr("cspdiuxX%", tab.identifier))
	{
		while (**format != '%')
			(*format)--;
		len = write(1, "%", 1);
	}
	else
		len = handle_format(&tab, args);
	return (len);
}
