/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvan-den <nvan-den@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 19:18:42 by nick              #+#    #+#             */
/*   Updated: 2023/04/28 13:08:09 by nvan-den         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./header.h"

void sig_handler(int sig)
{
	static int	bit_pos;
	static char	character;

	if (sig == SIGUSR1)
	{
		character |= (1 << bit_pos);
		bit_pos++;
	}
	else if (sig == SIGUSR2)
		bit_pos++;
	else
		return;
	if (bit_pos == 8)
	{
		if (character == '\0')
			write(1, "\n", 1);
		else
			write(1, &character, 1);
		character = 0;
		bit_pos = 0;
	}
}

int	main(void)
{
	int pid;
	
	pid = getpid();
	ft_printf("server id: %i\n", pid);

	struct	sigaction sigact;
	sigemptyset(&sigact.sa_mask);
	sigact.sa_handler = &sig_handler;
	sigact.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sigact, NULL);
	sigaction(SIGUSR2, &sigact, NULL);

	while(1)
		pause();
	return(0);
}