/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imaalem <imaalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 15:15:18 by imaalem           #+#    #+#             */
/*   Updated: 2022/03/11 15:16:02 by imaalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	*lay_the_table_for_diner(int nb_philo, t_data *data)
{
	int		*tab;
	int		i;

	i = 0;
	tab = NULL;
	tab = (int *)malloc(sizeof(int) * nb_philo);
	if (tab == NULL)
	{
		free_data(data, NULL, "Error\nmalloc of table has failed\n");
		return (NULL);
	}
	while (i < nb_philo)
	{
		tab[i] = 1;
		i++;
	}
	return (tab);
}

t_data	*extract_arg(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
	{
		ft_putstr_fd("Error\nmalloc of data structure has failed\n", 2);
		return (NULL);
	}
	data->rip = false;
	data->nb_philo = ft_atol(av[1]);
	data->tab = lay_the_table_for_diner(data->nb_philo, data);
	if (!data->tab)
		return (NULL);
	data->time_to_die = ft_atol(av[2]);
	data->time_to_eat = ft_atol(av[3]);
	data->time_to_sleep = ft_atol(av[4]);
	if (ac == 6)
		data->time_each_philo_must_eat = ft_atol(av[5]);
	else
		data->time_each_philo_must_eat = -1;
	return (data);
}
