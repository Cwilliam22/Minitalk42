/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt < wcapt@student.42lausanne.ch >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:07:20 by wcapt             #+#    #+#             */
/*   Updated: 2025/02/17 16:06:52 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"

volatile sig_atomic_t g_signal_received = 0;

void	get_confirmation(int signal)
{
	ft_printf("PID valide ! Sending in progress... \n");
	if (signal == SIGUSR2)
	{
		ft_printf("Message received ✅\n");
		g_signal_received = 1;
	}
}

int	pid_control(char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (*str < 48 || *str > 57)
			return (0);
		str++;
	}
	return (1);
}

int	get_bits(unsigned char octet, __pid_t pid_serveur)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		if ((octet >> i) & 1)
		{
			if (kill(pid_serveur, SIGUSR2) == -1)
				return (0);
		}
		else
		{
			if (kill(pid_serveur, SIGUSR1) == -1)
				return (0);
		}
		usleep(100);
		i--;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	pid_t	pid_serveur;

	if (argc == 3)
	{
		if (signal(SIGUSR2, get_confirmation) == SIG_ERR)
			return (ft_printf("Error during the get_confirmation.\n"), 1);
		pid_serveur = ft_atoi(argv[1]);
		if (pid_serveur < 2 || pid_serveur > 4194304)
			return (ft_printf("The PID is invalid. \n"), 1);
		while (*argv[2])
		{
			if (!get_bits(*argv[2], pid_serveur))
				return (1);
			argv[2]++;
		}
		get_bits('\0', pid_serveur);
		if (!g_signal_received)
			pause();
	}
	else
		return (ft_printf("The number of argument is incorrect.\n"), 1);
	return (0);
}

// Méthode atoi_base
// Méthode bits_shift