#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

#define MAX_SIZE 10000

typedef struct	s_buf
{
	char *s;
	int	len;
	int pos;
}				t_buf;

int ft_strlen(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	while (*str)
	{
		i++;
		str++;
	}
	return (i);
}

int ft_sizen(long long n)
{
	long long i;

	i= 0 ;
	if (n == 0)
		return(1);
	if (n < 0)
		i++;
	while(n)
	{
		n = n /10;
		i++;
	}
	return (i);
}

void *ft_calloc(size_t count, size_t size)
{
	char *p;
	char *pp;

	p = malloc(count *size);
	count = count *size;
	pp = p;
	while(count--)
		*p++=0;
	return(pp);


}


void	*ft_memcpy(void *dest, const void *source, int len)
{
	char *d;
	char *s;

	d = (char *)dest;
	s = (char *)source;
	if (len == 0 || dest == source)
		return (dest);
	while(len--)
		*d++ = *s++;
	return (dest);

}


t_buf	*more_size(t_buf *buffer)
{
	char *new_buffer;

	new_buffer= buffer->s;
	buffer->len = buffer->len + MAX_SIZE;
	buffer->s = ft_calloc(sizeof(char), buffer->len);
	buffer->s = ft_memcpy(buffer->s, new_buffer, buffer->pos);
	free(new_buffer);
	return(buffer);
}

void	fill_buffer(t_buf *buffer, char format)
{
	if (buffer->pos + 1 >= buffer->len)
		return(fill_buffer(more_size(buffer), format));
	*(buffer->s	+ buffer->pos) = format;
	buffer->pos++;	
}


t_buf	*init_buffer(void)
{
	t_buf *buffer;

	buffer = malloc(sizeof(t_buf));
	buffer->s = ft_calloc(sizeof(char), MAX_SIZE);
	buffer->len = MAX_SIZE;
	buffer->pos = 0;
	return (buffer);	

}

char	*ft_fillup(long long nb, char *str)
{
	char t;

	if(nb < 0)
	{
		*str++ = '-';
		nb = nb * -1;
	}
	if(nb > 9)
		str = ft_fillup(nb/10, str);
	t = (nb % 10 + '0');
	*str = t;
	return (++str);
}

char	*ft_fillup_unsigned(unsigned long long nb, char *str)
{
	char t;

	if(nb > 9)
		str = ft_fillup_unsigned(nb/10, str);
	t = (nb % 10 + '0');
	*str = t;
	return (++str);
}
char	*ft_fillup_hexl(unsigned long long result, char *str)
{
	unsigned long long	t;
	char				*tab;

	tab = "0123456789abcdef";
	if (result > 15)
		str = ft_fillup_hexl(result / 16, str);
	t = result % 16;
	*str = tab[t];
	return (++str);
}

char	*ft_fillup_hexh(unsigned long long result, char *str)
{
	unsigned long long	t;
	char				*tab;

	tab = "0123456789ABCDEF";
	if (result > 15)
		str = ft_fillup_hexh(result / 16, str);
	t = result % 16;
	*str = tab[t];
	return (++str);
}
void	int_conv(char conv, t_buf *buffer, va_list param)
{
	long long result;
	long long len_result;
	char *str;
	char *str_tmp;
	char *str_free;

	result = va_arg(param, int);
	len_result = ft_sizen(result);
	str = malloc(sizeof(char) * (ft_sizen(result)+1));
	str_tmp = str;
	str_free = str;
	str = ft_fillup(result, str);
	*str = '\0';
	while(*str_tmp)
	{

		fill_buffer(buffer, *str_tmp);
		str_tmp++;
	}
	free(str_free);
}

void unsigned_int_conv(char conv, t_buf *buffer, va_list param)
{
	unsigned long long result;
	char *str;
	char *str_tmp;
	char *str_free;
	
	result = va_arg(param, unsigned int);
	str = malloc(sizeof(char) * (ft_sizen(result)+1));
	str_tmp = str;
	str_free = str;
	if (conv == 'p' || conv == 'x')
		str = ft_fillup_hexl(result, str);
	else if (conv == 'X')
		str = ft_fillup_hexh(result, str);
	else
		str = ft_fillup_unsigned(result, str);
	*str = '\0';
	if(conv == 'p')
	{
		fill_buffer(buffer, '0');
		fill_buffer(buffer, 'x');
	}
	while (*str_tmp)
	{
		fill_buffer(buffer, *str_tmp);
		str_tmp++;
	}
	free(str_free);


}

void	ft_putbuffer(t_buf *buff)
{
	if (!*buff->s)
		return;
	write(1, buff->s, buff->pos);
}

int ft_printf(const char *format, ...)
{
	va_list param;
	t_buf	*buffer;
	int pos;
	char conv;

	va_start(param, format);
	buffer = init_buffer();
	while (*format)
	{
		if (*format != '%')
			fill_buffer(buffer, *format);
		else
		{
			format++;
			conv = *format;
			if (conv == 'd' || conv == 'i')
				int_conv(conv, buffer, param);
			else if (conv == '%')
				fill_buffer(buffer, *format);
			else if (conv == 'p' || conv == 'u' || conv == 'x' || conv == 'X')
				unsigned_int_conv(conv, buffer, param);
			//else if (conv == 'c' || conv == 's')
			//	char_conv(conv, buffer, param);
		}
		format++;
	}
	ft_putbuffer(buffer);
	va_end(param);
	pos = buffer->pos;
	free(buffer->s);
	free(buffer);
	return(pos);


}

int	main()
{
	unsigned int i = 74836594846545;
	printf("printf vaut %d\n",ft_printf("coucou %u\n", i));
	printf("printf vaut %d\n",printf("coucou %u\n", i));
	printf("%%%%\n");
	ft_printf("%%%%\n");
	printf("\n");
}
