/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt < wcapt@student.42lausanne.ch >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:07:38 by wcapt             #+#    #+#             */
/*   Updated: 2025/02/13 16:30:23 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"

#include <unistd.h>
#include <stdio.h>

void	get_signal(int signal, siginfo_t *info, void *context)
{
	static int				bit = 0;
	static unsigned char	m = 0;
	pid_t					pid_client;

	(void)context;
	pid_client = info->si_pid;
	if (signal == SIGUSR2)
		m |= (1 << (7 - bit));
	bit++;
	if (bit == 8)
	{
		if (m == 0)
		{
			ft_printf("\n");
			if (kill(pid_client, SIGUSR2) == -1)
				ft_printf("Error with the confirmation message.\n");
		}
		else
			ft_printf("%c", m);
		bit = 0;
		m = 0;
	}
}

int	main(int argc, char **argv)
{
	pid_t				pid;
	struct sigaction	sig;

	pid = getpid();
	(void)argv;
	if (argc != 1)
		return (ft_printf("Too many arguments. Try again !!!\n"), 1);
	ft_printf("PID : %d\n", pid);
	ft_printf("Waiting for the message ...\n");
	sig.sa_flags = SA_SIGINFO;
	sig.sa_sigaction = get_signal;
	sigemptyset(&sig.sa_mask);
	while (argc == 1)
	{
		if (sigaction(SIGUSR2, &sig, NULL) == -1)
			return (ft_printf("Error, failed to get the signal.\n"), 1);
		if (sigaction(SIGUSR1, &sig, NULL) == -1)
			return (ft_printf("Error, failed to get the siganl.\n"), 1);
	}
	return (0);
}
