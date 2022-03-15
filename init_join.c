/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_join.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imaalem <imaalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 11:53:44 by imaalem           #+#    #+#             */
/*   Updated: 2022/03/15 13:13:37 by imaalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

pthread_mutex_t	*init_forks_mutexes(t_data *data, t_philo *tab_philo)
{
	pthread_mutex_t	*tab_mutex;
	unsigned int	i;

	i = 0;
	tab_mutex = malloc(data->nb_philo * sizeof(pthread_mutex_t));
	if (tab_mutex == NULL)
	{
		free_data(data, tab_philo, "Error\nmalloc of *forks failed\n");
		return (NULL);
	}
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&tab_mutex[i], NULL) != 0)
		{
			free_data(data, tab_philo, "Error\nfork mutex have failed to init\n");
			return (NULL);
		}
		i++;
	}
	return (tab_mutex);
}

void	*init_mutexes(t_data *data, t_philo *tab_philo)
{
	data->forks = init_forks_mutexes(data, tab_philo);
	if (!data->forks)
		return (NULL);
	if (pthread_mutex_init(&data->rip_mutex, NULL))
	{
		free_data(data, tab_philo, "Error\nhave failed to create *rip_mutex\n");
		return (NULL);
	}
	if (pthread_mutex_init(&data->talk, NULL))
	{
		free_data(data, tab_philo, "Error\nhave failed to create *talk_mutex\n");
		return (NULL);
	}
	return (data);
}

t_philo	*init_philo_structures(t_data *data)
{
	unsigned int		i;
	t_philo				*tab_philo;

	i = 0;
	tab_philo = malloc(sizeof(t_philo) * data->nb_philo);
	data->thread = malloc(data->nb_philo * sizeof(pthread_t));
	if (tab_philo == NULL)
	{
		free_data(data, tab_philo, NULL);
		return (NULL);
	}
	while (i < data->nb_philo)
	{
		tab_philo[i].talk = &data->talk;
		tab_philo[i].rip_mutex = &data->rip_mutex;
		tab_philo[i].rip = &data->rip;
		tab_philo[i].l_fork = &data->forks[(i + 1) % data->nb_philo];
		tab_philo[i].r_fork = &data->forks[i];
		tab_philo[i].data = data;
		tab_philo[i].id = i;
		tab_philo[i].eaten = 0;
		i++;
	}
	return (tab_philo);
}
