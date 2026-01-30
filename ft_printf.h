/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaza-ru <adaza-ru@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 02:10:21 by adaza-ru          #+#    #+#             */
/*   Updated: 2026/01/30 02:10:21 by adaza-ru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

char	*ft_strchr(const char *s, int c);
int		eval_format(const char **format, va_list *args);
int		ft_printf(const char *format, ...);
int		handle_char_mandatory(va_list *args);
int		handle_string_mandatory(va_list *args);
int		handle_integer_mandatory(va_list *args);
int		handle_unsigned_mandatory(va_list *args);
int		handle_hexadecimal_mandatory(va_list *args);
int		handle_pointer_mandatory(va_list *args);
int		putnbr_base(unsigned long long nbr, char *base);
size_t	ft_strlen(const char *s);

#endif