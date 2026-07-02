/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaza-ru <adaza-ru@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 18:55:51 by adaza-ru          #+#    #+#             */
/*   Updated: 2025/12/22 18:55:51 by adaza-ru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif
# if BUFFER_SIZE <= 0
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# define WRITE 0
# define FLUSH 1
# define GET_TOTAL 2

typedef struct s_print
{
	int		dash;
	int		zero;
	int		dot;
	int		hash;
	int		space;
	int		plus;
	int		width;
	int		precision;
	char	identifier;
}	t_print;

char	*ft_strchr(const char *s, int c);
int		calculate_len(unsigned long long nbr, int base_len);
void	eval_format(const char **format, va_list *args, int *err_mod);
void	fill(int len, char c);
int		ft_isdigit(int c);
int		ft_printf(const char *format, ...);
void	handle_char(t_print *tab, va_list *args);
void	handle_format(t_print *tab, va_list *args);
void	handle_hexadecimal(t_print *tab, va_list *args);
void	handle_integer(t_print *tab, va_list *args);
void	handle_percent(void);
void	handle_pointer(t_print *tab, va_list *args);
void	handle_string(t_print *tab, va_list *args);
void	handle_unsigned(t_print *tab, va_list *args);
int		parse_value(const char **format);
void	print_num(t_print *tab, unsigned long long n, char *base, char *prefix);
void	putnbr_base(unsigned long long nbr, char *base);
int		ft_manage_buffer(char c, int mode);
size_t	ft_strlen(const char *s);
void	apply_hierarchy(t_print *tab);
void	init_print_struct(t_print *print_format);
void	parse_format(const char **format, t_print *tab);
void	parse_flags(const char **format, t_print *tab);
void	ft_putstr_buffer(char *str);

#endif