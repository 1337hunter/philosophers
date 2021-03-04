/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbright <gbright@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 12:35:41 by gbright           #+#    #+#             */
/*   Updated: 2020/09/08 13:03:50 by gbright          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

int		dead(t_philo *ph)
{
	struct timeval	tval;
	long			d;
	int				md;

	gettimeofday(&tval, 0);
	d = tval.tv_sec - ph->last_meal;
	md = (tval.tv_usec - ph->ulast_meal) / 1000;
	while (--d >= 0)
		md += 1000;
	if (md > ph->common->ttd)
	{
		print_status(ph, "is dead");
		ph->status = 0;
		return (1);
	}
	return (0);
}

int		ph_eating(t_philo *ph)
{
	struct timeval	tv;
	int				lock_left;

	lock_left = (ph->phn - 1 < 0 ? ph->common->n - 1 : ph->phn - 1);
	pthread_mutex_lock(&ph->common->mutex[lock_left]);
	pthread_mutex_lock(&ph->common->mutex[ph->phn]);
	gettimeofday(&tv, 0);
	print_status(ph, "has taken a fork");
	print_status(ph, "is eating");
	ph->last_meal = tv.tv_sec;
	ph->ulast_meal = tv.tv_usec;
	usleep(ph->common->tte * 1000);
	pthread_mutex_unlock(&ph->common->mutex[lock_left]);
	pthread_mutex_unlock(&ph->common->mutex[ph->phn]);
	return (0);
}

void	*philosophers_life(void *obj)
{
	t_philo			*ph;
	struct timeval	tval;

	ph = (t_philo*)obj;
	gettimeofday(&tval, 0);
	ph->last_meal = tval.tv_sec;
	ph->ulast_meal = tval.tv_usec;
	while (ph->common->n_eat == -1 ? 1 : (++ph->ate < ph->common->n_eat))
	{
		ph_eating(ph);
		print_status(ph, "is sleeping");
		usleep(ph->common->tts * 1000);
		print_status(ph, "is thinking");
	}
	ph->common->ready++;
	return (0);
}

void	control(size_t n, t_philo *ph, t_common common)
{
	size_t	i;

	i = -1;
	while (++i < n)
		pthread_mutex_init(common.mutex + i, 0);
	pthread_mutex_init(&common.op_mutex, 0);
	i = -1;
	while (++i < n)
	{
		ph[i].common = &common;
		ph[i].phn = i;
		ph[i].status = 1;
		ph[i].ate = -1;
		pthread_create(&(common.pthread[i]), 0, philosophers_life, &(ph[i]));
	}
	i = -1;
	while (!usleep(6969 / n) && ph[++i % n].status)
		if (common.ready == common.n || dead(&ph[i % n]))
		{
			i = -1;
			while (++i < (size_t)common.n)
				pthread_mutex_destroy(&common.mutex[i]);
			pthread_mutex_destroy(&common.op_mutex);
			return ;
		}
}

int		main(int ac, char **av)
{
	t_philo			*ph;
	t_common		common;
	size_t			i;
	size_t			n;

	if (ac < 5)
		return (write(1, "Not enough arguments!\n", 22));
	n = ft_atoll(av[1]);
	if (!(ph = (t_philo*)malloc(n * sizeof(t_philo))) ||
	!(common.mutex = (pthread_mutex_t*)malloc(n * sizeof(pthread_mutex_t))) ||
	!(common.pthread = (pthread_t*)malloc(n * sizeof(pthread_t))))
		return (write(1, "malloc error\n", 12));
	get_args(&common, ac, av);
	common.ready = 0;
	i = -1;
	while (++i < n)
		pthread_mutex_init(common.mutex + i, 0);
	pthread_mutex_init(&common.op_mutex, 0);
	control(n, ph, common);
	return (0);
}
