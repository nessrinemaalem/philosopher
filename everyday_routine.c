/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   everyday_routine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imaalem <imaalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 14:18:21 by imaalem           #+#    #+#             */
/*   Updated: 2022/03/15 13:19:55 by imaalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	print_eat_message(t_philo *philo)
{
	pthread_mutex_lock(philo->talk);
	printf("%lld %d has taken a fork\n", delta_t(philo), philo->id + 1);
	printf("%lld %d has taken a fork\n", delta_t(philo), philo->id + 1);
	printf("%lld %d is eating\n", delta_t(philo), philo->id + 1);
	pthread_mutex_unlock(philo->talk);
}

void	*eat_odd(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	pthread_mutex_lock(philo->l_fork);
	philo->data->tab[(philo->id + 1) % philo->data->nb_philo] -= 1;
	philo->data->tab[philo->id] -= 1;
	print_eat_message(philo);
	if (!ft_usleep(philo, philo->data->time_to_eat))
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		return (NULL);
	}
	philo->delta_last_meal = delta_t(philo);
	if (philo->data->time_each_philo_must_eat != -1)
		philo->eaten += 1;
	philo->data->tab[philo->id] += 1;
	philo->data->tab[(philo->id + 1)
		% philo->data->nb_philo] += 1;
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	return (philo);
}

void	*eat_even(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	pthread_mutex_lock(philo->r_fork);
	philo->data->tab[(philo->id + 1) % philo->data->nb_philo] -= 1;
	philo->data->tab[philo->id] -= 1;
	print_eat_message(philo);
	if (!ft_usleep(philo, philo->data->time_to_eat))
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		return (NULL);
	}
	philo->delta_last_meal = delta_t(philo);
	if (philo->data->time_each_philo_must_eat != -1)
		philo->eaten += 1;
	philo->data->tab[philo->id] += 1;
	philo->data->tab[(philo->id + 1)
		% philo->data->nb_philo] += 1;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	return (philo);
}

void	*fais_dodo(t_philo *philo)
{
	pthread_mutex_lock(philo->talk);
	printf("%lld %d is sleeping\n", delta_t(philo), philo->id + 1);
	pthread_mutex_unlock(philo->talk);
	if (!ft_usleep(philo, philo->data->time_to_sleep))
		return (NULL);
	return (philo);
}

void	*think(t_philo *philo)
{
	if (!routine_control(philo))
		return (NULL);
	pthread_mutex_lock(philo->talk);
	printf("%lld %d is thinking\n", delta_t(philo), philo->id + 1);
	pthread_mutex_unlock(philo->talk);
	return (philo);
}
