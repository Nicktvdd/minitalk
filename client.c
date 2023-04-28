/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvan-den <nvan-den@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 19:18:28 by nick              #+#    #+#             */
/*   Updated: 2023/04/28 14:13:38 by nvan-den         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./header.h"

void sig_handler(int sig) 
{
    if (sig == SIGUSR1) 
        ft_printf("String received by server!\n");
}

int	main(int argc, char **argv)
{
	int		i;
	int		pid;
	char	*string;
	char 	character;
	int		bit_pos;

	i = 0;
	bit_pos = 0;
	if (argc != 3) 
	{
        ft_printf("Usage: %s [server_pid] [string_to_send]\n", argv[0]);
        return(1);
	}
	pid = ft_atoi(argv[1]);
	string = argv[2];
	string[ft_strlen(string) + 1] = '\0';

 	struct sigaction sigact;
	sigemptyset(&sigact.sa_mask);
	sigact.sa_handler = sig_handler;
	sigaction(SIGUSR1, &sigact, NULL);
	
	while (string[i])
	{
		character = string[i];
		while (bit_pos < 8)
		{
			if (character & (1 << bit_pos))
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			usleep(100);
			bit_pos++;
		}
		bit_pos = 0;
		i++;
	}
	return(0);
}