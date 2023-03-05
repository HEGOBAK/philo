/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchu <jchu@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 05:29:09 by jchu              #+#    #+#             */
/*   Updated: 2023/03/06 07:39:40 by jchu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_input(int argc, char **argv)
{
	int	i;

	if (argc != 5 || argc != 6)
	{
		ftprint_reminder();
		return (0);
	}
	i = 1;
	while (argv[i])
	{
		if (!is_digit(argv[i]) || !ft_atoi(argv[i]))
			return (0);
		i++;
	}
}

int	check_meals_eaten(t_vault *vault)
{
	pthread_mutex_lock(&vault->philos_eaten_req_meals.lock);
	if (vault->philos_eaten_req_meals.count == vault->nbr_philo)
		return (1);
	pthread_mutex_lock(&vault->philos_eaten_req_meals.lock);
	return (0);
}

void	*philos_checkers(void *args)
{
	int		i;
	long	time_now;
	int		philosophers_eaten_enough;
	t_philo	*philos;

	i = 0;
	philosophers_eaten_enough = 0;
	philos = (t_philo *)args;
	while (i < philos->args->nbr_philo)
	{
		if (philos[i].meals_eaten >= philos[i].meals_needed)
			philosophers_eaten_enough++;
		time_now = get_time();
		if (time_now - philos[i].time_of_last_meal < philos[i].time_to_die)
		{
			philos[i].args->died = 1;
			pthread_mutex_lock(&philos[i].args->print_key);
			printf("%ld %d died\n", ft_time() - philos[i].start_time, \
			philos[i].philo_id + 1);
			pthread_mutex_unlock(&philos[i].args->print_key);
			return (NULL);
		}
		i++;
	}
	pthread_mutex_lock(&philos[i].args->philos_eaten_req_meals.lock);
	philos[i].args->philos_eaten_req_meals.count = philosophers_eaten_enough;
	pthread_mutex_unlock(&philos[i].args->philos_eaten_req_meals.lock);
	return (NULL);
}

void	*process(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	philo->start_time = get_time();
	while (!philo->args->died)
	{
		if (philo->args->died || check_meals_eaten(philo->args))
			return (NULL);
		take_forks(philo);
		if (philo->args->died || check_meals_eaten(philo->args))
			return (NULL);
		eating(philo);
		if (philo->args->died || check_meals_eaten(philo->args))
			return (NULL);
		sleeping(philo);
		if (philo->args->died || check_meals_eaten(philo->args))
			return (NULL);
		thinking(philo);
	}
	return (NULL);
}
