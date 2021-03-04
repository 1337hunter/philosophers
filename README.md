# Philosophers - Interesting task with multithreading
# I’ve never thought philosophy would be so deadly.

After make run:
./philo_<one|two|three>/philo_<one,two,three> <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]

◦ number_of_philosophers: is the number of philosophers and also the number
of forks
◦ time_to_die: is in milliseconds, if a philosopher doesn’t start eating ’time_to_die’
milliseconds after starting his last meal or the beginning of the simulation, it dies
◦ time_to_eat: is in milliseconds and is the time it takes for a philosopher to
eat. During that time he will need to keep the two forks.
◦ time_to_sleep: is in milliseconds and is the time the philosopher will spend
sleeping.
◦ number_of_times_each_philosopher_must_eat: argument is optional, if all
philosophers eat at least ’number_of_times_each_philosopher_must_eat’ the
simulation will stop. If not specified, the simulation will stop only at the death
of a philosopher.
