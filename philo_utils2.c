#include "philo.h"

static void time(int flag)
{
    static int time;
    struct time
    
    if (!flag)
    {
        gettimeofday();
    }
}

static void    eat(t_main *m, int i)
{
    t_philo philo;

    philo = m->philo[i];
    pthread_mutex_lock(&philo.r_fork);
    printf("timestamp_in_ms %d has taken a fork\n", i);
    pthread_mutex_lock(&philo.l_fork);
    printf("timestamp_in_ms %d has taken a fork\n", i);
    printf("timestamp_in_ms %d is eating\n", i);
}

void    routing(t_main *m)
{
    t_philo *philos;
    int     i;

    philos = m->philo;
    i = 0;
    while (i < m->sdata.number_of_philo)
    {
        if (i % 2 == 0)
            eat(m, i);
    }
}
