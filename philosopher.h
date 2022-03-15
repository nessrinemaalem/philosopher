/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imaalem <imaalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 15:29:14 by imaalem           #+#    #+#             */
/*   Updated: 2022/03/15 13:11:22 by imaalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include <stdbool.h>
# include <sys/time.h>

typedef struct s_data
{
	pthread_mutex_t			talk;
	unsigned int			nb_philo;
	unsigned long long int	time_to_die;
	unsigned long long int	time_to_eat;
	unsigned long long int	time_to_sleep;
	long long int			time_each_philo_must_eat;
	pthread_t				*thread;
	pthread_mutex_t			*forks;
	int						*tab;
	bool					rip;
	pthread_mutex_t			rip_mutex;
}	t_data;

typedef struct s_philo
{
	pthread_mutex_t			*talk;
	long long int			time;
	t_data					*data;
	pthread_mutex_t			*l_fork;
	pthread_mutex_t			*r_fork;
	int						id;
	long long int			delta_last_meal;
	pthread_mutex_t			*rip_mutex;
	bool					*rip;
	int						eaten;
}				t_philo;

unsigned long long	ft_atol(char *str);
int					ft_isdigit(int c);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				*check_args(int ac, char **av);
t_data				*extract_arg(int ac, char **av);
t_philo				*init_philo_structures(t_data *data);
void				*init_mutexes(t_data *data, t_philo *tab_philo);
void				*init_n_join_threads(t_data *data, t_philo *tab_philo);
void				*routine(void *arg);
void				destroy_mutexes(t_data *data, t_philo *tab_philo);
void				free_data(t_data *data, t_philo *tab_philo, char *error);
void				*eat_even(t_philo *philo);
void				*eat_odd(t_philo *philo);
void				*fais_dodo(t_philo *philo);
void				*think(t_philo *philo);
long long int		delta_t(t_philo *philo);
void				*init_meal_time(t_philo *philo);
void				*init_time(t_philo *philo);
void				*ft_usleep(t_philo *philo, unsigned long long int chrono);
void				*routine_control(t_philo *philo);
void				*rip_philo(t_philo *philo);
void				*check_time_out(t_philo *philo);
void				*check_full_belly(t_philo *philo);
void				*check_another_philo_passed_away(t_philo *philo);

#endif