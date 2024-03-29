/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvan-den <nvan-den@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:45:37 by nvan-den          #+#    #+#             */
/*   Updated: 2023/05/02 14:45:50 by nvan-den         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./header_bonus.h"

int	print_signal(char *string, siginfo_t *siginfo, int i)
{
	if (string[i] == '\0')
	{
		ft_printf("%s\n", string);
		kill(siginfo->si_pid, SIGUSR1);
		i = 0;
	}
	else
		i++;
	return (i);
}

void	sig_handler(int sig, siginfo_t *siginfo, void *empty)
{
	static int	bit_pos;
	static char	character;
	static int	i;
	static char	*string;

	if (string == NULL && (empty || !empty))
		string = malloc(sizeof(char) * 1000);
	if (sig == SIGUSR1)
	{
		character |= (1 << bit_pos);
		bit_pos++;
	}
	else if (sig == SIGUSR2)
		bit_pos++;
	else
		return ;
	if (bit_pos == 8)
	{
		string[i] = character;
		i = print_signal(string, siginfo, i);
		character = 0;
		bit_pos = 0;
	}
}

int	main(void)
{
	int					pid;
	struct sigaction	sigact;

	pid = getpid();
	ft_printf("server id: %i\n", pid);
	sigemptyset(&sigact.sa_mask);
	sigact.sa_sigaction = &sig_handler;
	sigact.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sigact, NULL);
	sigaction(SIGUSR2, &sigact, NULL);
	while (1)
		pause();
	return (0);
}
