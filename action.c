/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchu <jchu@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 07:32:46 by jchu              #+#    #+#             */
/*   Updated: 2023/03/06 07:37:59 by jchu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	taking_forks_else(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&philo->args->print_key);
	if (philo->args->died != 1)
	{
		printf("%ld %d has taken a fork\n", \
			ft_time() - philo->start_time, philo->philo_id + 1);
		printf("%ld %d has taken a fork\n", \
			ft_time() - philo->start_time, philo->philo_id + 1);
	}
	pthread_mutex_unlock(&philo->args->print_key);
}

void	taking_forks(t_philo *philo)
{
	if ((philo->philo_id) % 2 == 0 && philo->philo_id + 1 != philo->args->nbr_philo)
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(&philo->args->print_key);
		if (philo->args->died != 1)
		{
			printf("%ld %d has taken a fork\n", \
				ft_time() - philo->start_time, philo->philo_id + 1);
			printf("%ld %d has taken a fork\n", \
				ft_time() - philo->start_time, philo->philo_id + 1);
		}
		pthread_mutex_unlock(&philo->args->print_key);
	}
	else
		taking_forks_else(philo);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->print_key);
	printf("%ld %d is eating\n", \
		ft_time() - philo->start_time, philo->philo_id + 1);
	pthread_mutex_unlock(&philo->args->print_key);
	philo->meals_eaten += 1;
	philo->time_of_last_meal = ft_time();
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->print_key);
	printf("%ld %d is sleeping\n", \
		ft_time() - philo->start_time, philo->philo_id + 1);
	pthread_mutex_unlock(&philo->args->print_key);
	ft_usleep(philo->time_to_sleep);
}

void	thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->print_key);
	printf("%ld %d is thinking\n", \
		ft_time() - philo->start_time, philo->philo_id + 1);
	pthread_mutex_unlock(&philo->args->print_key);
}