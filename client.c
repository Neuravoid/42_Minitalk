/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ualkan <ualkan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 13:10:26 by ualkan            #+#    #+#             */
/*   Updated: 2025/01/23 10:19:40 by ualkan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile int	g_ack_received = 0;

static void	ack_handler(int signum)
{
	(void)signum;
	g_ack_received = 1;
}

static void	send_char_as_signal(int pid, unsigned char c)
{
	int	bit;

	bit = 7;
	while (bit >= 0)
	{
		if (c & (1 << bit))
		{
			if (kill(pid, SIGUSR2) == -1)
				exit(EXIT_FAILURE);
		}
		else
		{
			if (kill(pid, SIGUSR1) == -1)
				exit(EXIT_FAILURE);
		}
		g_ack_received = 0;
		while (!g_ack_received)
			pause();
		bit--;
	}
}

static void	send_message_as_signal(int pid, const char *message)
{
	while (*message)
	{
		send_char_as_signal(pid, (unsigned char)*message);
		message++;
	}
	send_char_as_signal(pid, '\0');
}

int	main(int argc, char **argv)
{
	int	server_pid;

	if (argc != 3)
		return (EXIT_FAILURE);
	server_pid = atoi(argv[1]);
	if (server_pid <= 0)
		return (EXIT_FAILURE);
	if (signal(SIGUSR1, ack_handler) == SIG_ERR)
		return (EXIT_FAILURE);
	send_message_as_signal(server_pid, argv[2]);
	return (EXIT_SUCCESS);
}
