/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_control.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imaalem <imaalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 14:16:00 by imaalem           #+#    #+#             */
/*   Updated: 2022/03/15 14:26:56 by imaalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*rip_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->rip_mutex);
	*philo->rip = true;
	pthread_mutex_unlock(philo->rip_mutex);
	return (NULL);
}

void	*check_time_out(t_philo *philo)
{
	long long int		delta;
	long long int		t1;
	long long int		t2;

	t1 = philo->delta_last_meal;
	t2 = delta_t(philo);
	delta = t2 - t1;
	if (delta >= (long long int)philo->data->time_to_die)
	{
		pthread_mutex_lock(philo->talk);
		printf("%lld %d died\n", delta_t(philo), philo->id + 1);
		pthread_mutex_unlock(philo->talk);
		rip_philo(philo);
		return (NULL);
	}
	return (philo);
}

void	*check_full_belly(t_philo *philo)
{
	if (philo->data->time_each_philo_must_eat == -1)
		return (philo);
	if (philo->eaten >= philo->data->time_each_philo_must_eat)
		return (NULL);
	else
		return (philo);
}

void	*check_another_philo_passed_away(t_philo *philo)
{
	pthread_mutex_lock(philo->rip_mutex);
	if (*philo->rip == true)
	{
		pthread_mutex_unlock(philo->rip_mutex);
		return (NULL);
	}
	else
	{
		pthread_mutex_unlock(philo->rip_mutex);
		return (philo);
	}
}
