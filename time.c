/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imaalem <imaalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 14:16:42 by imaalem           #+#    #+#             */
/*   Updated: 2022/03/15 14:18:24 by imaalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*init_time(t_philo *philo)
{
	struct timeval			clock;

	if (gettimeofday(&clock, NULL) != 0)
		return (NULL);
	philo->time = (clock.tv_sec * 1000) + (clock.tv_usec / 1000);
	philo->delta_last_meal = 0;
	if ((philo->id + 1) % 2 == 0)
		usleep(1000);
	return (philo);
}

long long int	delta_t(t_philo *philo)
{
	long long int			delta_time;
	struct timeval			clock;
	long long int			t1;
	long long int			t2;

	if (gettimeofday(&clock, NULL) != 0)
		return (0);
	t1 = philo->time;
	t2 = clock.tv_sec * 1000 + clock.tv_usec / 1000;
	delta_time = t2 - t1;
	return (delta_time);
}

void	*ft_usleep(t_philo *philo, unsigned long long int chrono)
{
	int	nb_loop;
	int	i;

	nb_loop = chrono / 10;
	i = 0;
	while (i < nb_loop)
	{
		if (!routine_control(philo))
			return (NULL);
		usleep(10 * 1000);
		i++;
	}
	return (philo);
}
