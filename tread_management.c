/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tread_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imaalem <imaalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 15:35:01 by imaalem           #+#    #+#             */
/*   Updated: 2022/03/15 13:12:32 by imaalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*init_n_join_threads(t_data *data, t_philo *tab)
{
	unsigned int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_create(&(data->thread[i]), NULL, &routine, &tab[i]) != 0)
		{
			free_data(data, tab, "Error\nphilo thread failed to create\n");
			return (NULL);
		}
		i++;
	}
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_join(data->thread[i], NULL) != 0)
		{
			free_data(data, tab, "Error\nphilo thread failed to join\n");
			return (NULL);
		}
		i++;
	}
	return (data);
}

void	destroy_mutexes(t_data *data, t_philo *tab_philo)
{
	unsigned int	i;

	i = 0;
	if (tab_philo != NULL)
	{
		while (i < data->nb_philo)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
	}
	pthread_mutex_destroy(&data->rip_mutex);
	pthread_mutex_destroy(&data->talk);
}
