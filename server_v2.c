/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt < wcapt@student.42lausanne.ch >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 11:18:45 by wcapt             #+#    #+#             */
/*   Updated: 2025/02/20 13:45:40 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"

static char	g_temp[2] = {0, 0};

static void	put_in_string(unsigned char m, char **dest, pid_t pid_client)
{
	char		*new_dest;

	(void) pid_client;
	if (m == '\0')
	{
		if (*dest)
			ft_putstr_fd(*dest, 1);
		ft_putchar_fd('\n', 1);
		if (kill(pid_client, SIGUSR2) == -1)
			ft_printf("Error with the confirmation message.\n");
		free(*dest);
		*dest = NULL;
	}
	else
	{
		g_temp[0] = m;
		if (!*dest)
			*dest = ft_strdup(g_temp);
		else
		{
			new_dest = ft_strjoin(*dest, g_temp);
			free(*dest);
			*dest = new_dest;
		}
	}
}

void	get_signal(int signal, siginfo_t *info, void *context)
{
	static int				bit = 0;
	static unsigned char	m = 0;
	pid_t					pid_client;
	static char				*dest;

	(void)context;
	pid_client = info->si_pid;
	if (signal == SIGUSR2)
		m |= (1 << (7 - bit));
	bit++;
	if (bit == 8)
	{
		put_in_string(m, &dest, pid_client);
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
