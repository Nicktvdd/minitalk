/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvan-den <nvan-den@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:44:40 by nvan-den          #+#    #+#             */
/*   Updated: 2023/05/02 14:44:49 by nvan-den         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./header_bonus.h"

int	signal_sender(char *string, int pid, int i)
{
	int		bit_pos;
	char	character;

	bit_pos = 0;
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
	return (i);
}

void	sig_handler(int sig)
{
	if (sig == SIGUSR1)
		ft_printf("String received by server!\n");
}

int	main(int argc, char **argv)
{
	int					i;
	int					pid;
	char				*string;
	struct sigaction	sigact;

	i = 0;
	pid = ft_atoi(argv[1]);
	string = argv[2];
	string[ft_strlen(string)] = '\0';
	sigemptyset(&sigact.sa_mask);
	sigact.sa_handler = sig_handler;
	sigaction(SIGUSR1, &sigact, NULL);
	while (string[i] && (argc))
		i = signal_sender(string, pid, i);
	signal_sender(string, pid, i);
	return (0);
}
