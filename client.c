/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvan-den <nvan-den@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 19:18:28 by nick              #+#    #+#             */
/*   Updated: 2023/04/27 16:06:26 by nvan-den         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./header.h"

void sig_handler(int sig_num) {
    if (sig_num == SIGUSR1) {
        ft_printf("String received by server!\n");
    }
}

int	main(int argc, char **argv)
{
	int		i;
	int		pid;
	char	*string;
	char 	character;
	int		j;

	i = 0;
	j = 0;
	if (argc != 3) 
	{
        ft_printf("Usage: %s [server_pid] [string_to_send]\n", argv[0]);
        return 1;
	}
	pid = atoi(argv[1]);
	string = argv[2];

 	struct sigaction sigact;
	sigemptyset(&sigact.sa_mask);
	sigact.sa_handler = sig_handler;
	sigaction(SIGUSR1, &sigact, NULL);

	while (string[i])
	{
		character = string[i];
		while (j < 8)
		{
			if (character & (1 << j))
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			usleep(100);
			j++;
		}
		j = 0;
		i++;
	}
	kill(pid, SIGUSR1);
	return(0);
}