/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvan-den <nvan-den@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 19:18:42 by nick              #+#    #+#             */
/*   Updated: 2023/04/27 14:48:04 by nvan-den         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./header.h"

void handle_sign(int sig)
{
	static int				bit_pos = 0;
	static unsigned char	character = 0;

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

	struct	sigaction sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = &handle_sign;
	sa.sa_flags = 0;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);

	pause();
	return(0);
}