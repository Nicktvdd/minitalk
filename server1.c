/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 15:00:08 by nick              #+#    #+#             */
/*   Updated: 2023/04/19 15:07:14 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

static void sig_usr(int);

int main(void)
{
	printf("pid = %i", getpid());
	if (signal(SIGUSR1, sig_usr) == SIG_ERR)
		perror("Can't catch signal");
	if (signal(SIGUSR2, sig_usr) == SIG_ERR)
		perror("Can't catch signal");

	for(;;)
		pause();
}

static void	sig_usr(int signo)
{
	if (signo == SIGUSR1)
		printf("\n Terminal Call- received SIGUSR1\n");
	else if (signo == SIGUSR2)
		printf("\n Terminal call- received SIGUSR2\n");
	
	else
		perror("received signal error");
}