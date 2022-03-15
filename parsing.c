/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imaalem <imaalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 14:24:29 by imaalem           #+#    #+#             */
/*   Updated: 2022/03/11 15:20:26 by imaalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	check_nb_is_digit(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (ft_isdigit(arg[i]) == 1)
			i++;
		else
		{
			printf("Error\nArgument must be a real number\n");
			return (1);
		}
	}
	return (0);
}

int	check_nb_is_positiv(char *arg)
{
	unsigned long long	nb;

	nb = ft_atol(arg);
	if (nb > 0)
		return (0);
	else
	{
		printf("Error\nArgument must be a positiv number\n");
		return (1);
	}
}

int	check_nb_is_enough(char *arg, int i)
{
	unsigned long long	nb;

	nb = ft_atol(arg);
	if (i == 1 || i == 5)
		return (0);
	if (nb > 60)
		return (0);
	else
	{
		printf("Error\ntime_to_die must be minimum 60 milli sec\n");
		return (1);
	}
}

int	print_error(int ac, int i)
{
	if (i == 1)
		ft_putstr_fd("NB_OF_PHILO is invalid\n", 2);
	else if (i == 2)
		ft_putstr_fd("TIME_TO_DIE is invalid\n", 2);
	else if (i == 3)
		ft_putstr_fd("TIME_TO_EAT is invalid\n", 2);
	else if (i == 4)
		ft_putstr_fd("TIME_TO_SLEEP is invalid\n", 2);
	else if (ac == 6 && i == 5)
		ft_putstr_fd("EACH_PHILOSOPHER_MUST_EAT is invalid\n", 2);
	if (i == ac)
		return (0);
	else
		return (-1);
}

void	*check_args(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac < 5 || ac > 6)
	{
		ft_putstr_fd("Error\nthere must be either 4 or 5 arguments\n", 2);
		return (NULL);
	}
	while (i < ac)
	{
		if (check_nb_is_digit(av[i]) != 0)
			break ;
		if (check_nb_is_positiv(av[i]) != 0)
			break ;
		if (check_nb_is_enough(av[i], i) != 0)
			break ;
		i++;
	}
	if (print_error(ac, i) < 0)
		return (NULL);
	else
		return (av);
}
