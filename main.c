/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imaalem <imaalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 15:22:43 by imaalem           #+#    #+#             */
/*   Updated: 2022/03/14 18:49:48 by imaalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	free_data(t_data *data, t_philo *tab_philo, char *error_message)
{
	if (error_message != NULL)
		ft_putstr_fd(error_message, 2);
	destroy_mutexes(data, tab_philo);
	if (data->tab != NULL)
		free(data->tab);
	if (data->thread != NULL)
		free(data->thread);
	if (data->forks != NULL)
		free(data->forks);
	if (tab_philo != NULL)
		free(tab_philo);
	if (data != NULL)
		free(data);
}

void	*routine_control(t_philo *philo)
{
	if (!check_time_out(philo))
		return (NULL);
	if (!check_full_belly(philo))
		return (NULL);
	if (!check_another_philo_passed_away(philo))
		return (NULL);
	return (philo);
}

void	*rip_single_philo(t_philo *philo)
{
	if (philo->data->nb_philo == 1)
	{
		usleep(philo->data->time_to_die * 1000);
		printf("%lld %d died\n", delta_t(philo), philo->id + 1);
		return (NULL);
	}
	else
		return (philo);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	init_time(philo);
	if (!rip_single_philo(philo))
		return (NULL);
	while (1)
	{
		if ((philo->id + 1) % 2 == 1)
		{
			if (!eat_odd(philo))
				return (NULL);
		}
		else
		{
			if (!eat_even(philo))
				return (NULL);
		}
		if (!fais_dodo(philo))
			return (NULL);
		if (!think(philo))
			return (NULL);
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_data	*data;
	t_philo	*tab_philo;

	tab_philo = NULL;
	if (!check_args(ac, av))
		return (0);
	data = extract_arg(ac, av);
	if (!data)
		return (0);
	if (!init_mutexes(data, tab_philo))
		return (0);
	tab_philo = init_philo_structures(data);
	if (!tab_philo)
		return (0);
	if (!init_n_join_threads(data, tab_philo))
		return (0);
	free_data(data, tab_philo, NULL);
	return (0);
}
