/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbright <gbright@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 12:42:01 by gbright           #+#    #+#             */
/*   Updated: 2020/09/08 12:57:16 by gbright          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <semaphore.h>

typedef struct		s_common
{
	int				n;
	int				ttd;
	int				tte;
	int				tts;
	int				start;
	int				ustart;
	int				simulation;
	int				n_eat;
	int				ready;
	pid_t			*pid;
	sem_t			*sem;
	sem_t			*op_sem;
	sem_t			*protect;
}					t_common;

typedef struct		s_philo
{
	int				phn;
	long			last_meal;
	int				ulast_meal;
	int				ate;
	t_common		*common;
	short			status;
}					t_philo;

long long			ft_atoll(const char *nptr);
int					get_args(t_common *philo, int ac, char **av);
void				ft_putnbr_fd(int n, int fd);
void				print_status(t_philo *ph, char *s);
void				*observer(void *obj);
int					dead(t_philo *ph);
#endif
