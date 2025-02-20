/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt < wcapt@student.42lausanne.ch >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:07:38 by wcapt             #+#    #+#             */
/*   Updated: 2025/02/20 13:48:35 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"

#define BUFFER_SIZE 65000

static void	utils(pid_t pid_client)
{
	ft_putchar_fd('\n', 1);
	if (kill(pid_client, SIGUSR2) == -1)
		ft_printf("Error with the confirmation message.\n");
}

static void	put_in_string(unsigned char m, pid_t pid_client)
{
	static char		buffer[BUFFER_SIZE];
	static size_t	len = 0;

	if (m == '\0')
	{
		if (len > 0)
		{
			write(1, buffer, len);
			len = 0;
		}
		utils(pid_client);
	}
	else
	{
		if (len < BUFFER_SIZE - 1)
		{
			buffer[len++] = m;
		}
		else
		{
			write(1, buffer, len);
			len = 0;
			buffer[len++] = m;
		}
	}
}

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
		put_in_string(m, pid_client);
		bit = 0;
		m = 0;
	}
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	sig;

	pid = getpid();
	ft_printf("PID : %d\n", pid);
	ft_printf("Waiting for the message ...\n");
	sig.sa_flags = SA_SIGINFO;
	sig.sa_sigaction = get_signal;
	sigemptyset(&sig.sa_mask);
	if (sigaction(SIGUSR2, &sig, NULL) == -1)
		return (ft_printf("Error, failed to get the signal.\n"), 1);
	if (sigaction(SIGUSR1, &sig, NULL) == -1)
		return (ft_printf("Error, failed to get the siganl.\n"), 1);
	while (1)
	{
		pause();
	}
	return (0);
}
