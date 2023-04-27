/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 19:18:28 by nick              #+#    #+#             */
/*   Updated: 2023/04/20 13:33:12 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./header.h"

int	main(int argc, char **argv)
{
	int	i;
	int	pid;
	char character;

	i = 0;
	pid = atoi(argv[1]);

/* 	struct sigaction sigact;
	sigemptyset(&sigact.sa_mask);
	sigact.sa_handler = sig_handler;
	sigaction(SIGUSR1, &sigact, NULL);
 */
	while (argv[2][i])
	{
		character = argv[2][i];
		while (character)
		{
			if (character & 1)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			character >>= 1;
			usleep(100);
		}
		i++;
	}
	kill(pid, SIGUSR1);
	return(0);
}