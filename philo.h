/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchu <jchu@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 01:52:39 by jchu              #+#    #+#             */
/*   Updated: 2023/03/06 07:26:34 by jchu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

struct s_vault;

typedef struct s_philo
{
	int				philo_id;
	int				meals_needed;
	int				meals_eaten;
	int				time_to_eat;
	int				time_to_sleep;
	time_t			time_to_die;
	time_t			start_time;
	time_t			time_of_last_meal;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_vault	*args;
}	t_philo;

typedef struct s_count
{
	pthread_mutex_t	lock;	
	int				count;
}	t_count;

typedef struct s_vault
{
	int				nbr_philo;
	int				meals_required_check;
	t_count			philos_eaten_req_meals;
	int				died;
	pthread_mutex_t	*forks;
	pthread_t		*philo_threads;
	pthread_mutex_t print_key;
	t_philo			*philo_vault;
}	t_vault;

void	ftprint_reminder(void);
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
void	*process(void *args);
void	*philos_checkers(void *args);
int		check_input(int argc, char **argv);
long	get_time(void);
#endif