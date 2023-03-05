/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchu <jchu@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 01:52:41 by jchu              #+#    #+#             */
/*   Updated: 2023/03/06 07:12:51 by jchu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	fill_philos(t_vault *vault, char **argv)
{
	int		i;
	t_philo	*philos;

	i = 0;
	philos = malloc(sizeof(t_philo) * vault->nbr_philo);
	while (i < vault->nbr_philo)
	{
		philos[i].philo_id = i;
		philos[i].time_to_die = ft_atoi(argv[2]);
		philos[i].time_to_eat = ft_atoi(argv[3]);
		philos[i].time_to_sleep = ft_atoi(argv[4]);
		philos[i].left_fork = &vault->forks[i];
		philos[i].right_fork = &vault->forks[(i + 1) % vault->nbr_philo];
		philos[i].time_of_last_meal = get_time(); //to prevent variables not found in philos_checker
		philos[i].meals_eaten = 0;
		if (vault->meals_required_check)
			philos[i].meals_needed = ft_atoi(argv[5]);
		philos[i].args = vault;
		i++;
	}
	vault->philo_vault = philos;
}

int	initialization(t_vault *vault, int argc, char **argv)
{
	int				i;
	pthread_mutex_t	*mutexes;

	if (!check_input(argc, argv))
		return (0);
	if (argc == 6)
	{
		vault->meals_required_check = 1;
		vault->philos_eaten_req_meals.count = 0;
		pthread_mutex_init(&vault->philos_eaten_req_meals.lock, NULL);
	}
	else
		vault->meals_required_check = 0;
	vault->nbr_philo = ft_atoi(argv[1]);
	i = 0;
	mutexes = malloc(sizeof(pthread_mutex_t) * vault->nbr_philo);
	while (i < vault->nbr_philo)
		pthread_mutex_init(&mutexes[i], NULL);
	pthread_mutex_init(&vault->print_key, NULL);
	vault->forks = mutexes;
	fill_philos(vault, argv);
	vault->died = 0;
}

void	run_process(t_vault	*vault)
{
	int			i;
	pthread_t	*philo_threads;
	pthread_t	check_thread;

	i = 0;
	philo_threads = malloc(sizeof(pthread_t) * vault->nbr_philo);
	while (i < vault->nbr_philo)
		pthread_create(&philo_threads[i], NULL, \
		process, (void *)&vault->philo_vault[i]);
	pthread_create(&check_thread, NULL, \
	philos_checkers, (void *)vault->philo_vault);
	pthread_join(check_thread, NULL);
	vault->philo_threads = philo_threads;
}

void	end_process(t_vault *vault)
{
	int	i;

	i = 0;
	if (vault->nbr_philo == 1)
		pthread_mutex_unlock(&vault->forks[0]);
	while (i < vault->nbr_philo)
		pthread_join(vault->philo_threads[i++], NULL);
}

int	main(int argc, char **argv)
{
	t_vault	vault;

	if (!initialization(&vault, argc, argv))
		return (0);
	run_process(&vault);
	end_process(&vault);
}
