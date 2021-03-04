# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mizola@student.21-school.ru <mizola>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/29 22:01:11 by gbright           #+#    #+#              #
#    Updated: 2020/09/08 12:34:24 by gbright          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

N1 = philo_one
N2 = philo_two
N3 = philo_three

FLAGS = -Wall -Wextra -Werror
D_1 = ./philo_one/srcs/
F_1 = main.c utils.c

D_2 = ./philo_two/srcs/
F_2 = main.c utils.c

D_3 = ./philo_three/srcs/
F_3 = main.c utils.c

F1 = $(addprefix $(D_1), $(F_1))
F2 = $(addprefix $(D_2), $(F_2))
F3 = $(addprefix $(D_3), $(F_3))

all: 
	gcc  $(FLAGS) -pthread $(F1) -o $(N1)/$(N1)
	gcc  $(FLAGS) -pthread $(F2) -o $(N2)/$(N2)
	gcc  $(FLAGS) -pthread $(F3) -o $(N3)/$(N3)

fclean:
	rm -f $(N1)/$(N1) $(N2)/$(N2) $(N3)/$(N3)

re: fclean all

.PHONY: all clean fclean re
