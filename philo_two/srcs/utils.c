/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbright <gbright@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 12:38:08 by gbright           #+#    #+#             */
/*   Updated: 2020/09/08 12:38:09 by gbright          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <sys/time.h>

int			get_args(t_common *php, int ac, char **av)
{
	struct timeval	tv;

	php->n = ft_atoll(av[1]);
	php->ttd = ft_atoll(av[2]);
	php->tte = ft_atoll(av[3]);
	php->tts = ft_atoll(av[4]);
	if (ac > 5)
		php->n_eat = ft_atoll(av[5]);
	else
		php->n_eat = -1;
	gettimeofday(&tv, 0);
	php->start = tv.tv_sec;
	php->ustart = tv.tv_usec;
	return (0);
}

void		print_status(t_philo *ph, char *s)
{
	int				mtime;
	int				time;
	struct timeval	tv;

	gettimeofday(&tv, 0);
	mtime = (tv.tv_usec - ph->common->ustart) / 1000;
	time = tv.tv_sec - ph->common->start;
	while (--time >= 0)
		mtime += 1000;
	sem_wait(ph->common->op_sem);
	ft_putnbr_fd(mtime, 1);
	write(1, " ", 1);
	ft_putnbr_fd(ph->phn + 1, 1);
	write(1, " ", 1);
	while (*s)
		write(1, s++, 1);
	write(1, "\n", 1);
	sem_post(ph->common->op_sem);
}

long long	ft_atoll(const char *nptr)
{
	int			flag;
	long long	out;

	flag = 1;
	while (*nptr == ' ' || *nptr == '\t' || *nptr == '\r' ||
		*nptr == '\v' || *nptr == '\f' || *nptr == '\n')
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			flag = -1;
		nptr++;
	}
	out = 0;
	while (*nptr <= '9' && *nptr >= '0')
	{
		if (out * flag * 10 < out * flag)
			return (flag < 0 ? 0 : -1);
		out *= 10;
		out += flag * (*nptr++ - '0');
	}
	return (out);
}

void		ft_putnbr_fd(int n, int fd)
{
	char	str[10];
	int		i;

	i = 10;
	if (n < 0)
	{
		write(fd, "-", 1);
		if (n == ((-1) * 2147483648))
		{
			str[--i] = '8';
			n = n / 10;
		}
		n = -n;
	}
	if (n == 0)
		write(fd, "0", 1);
	while (n != 0)
	{
		str[--i] = '0' + (n % 10);
		n = n / 10;
	}
	while (i < 10)
		write(fd, &str[i++], 1);
}
