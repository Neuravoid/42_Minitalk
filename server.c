/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ualkan <ualkan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 13:06:39 by ualkan            #+#    #+#             */
/*   Updated: 2025/01/23 10:19:26 by ualkan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

static size_t	lenint(int n)
{
	size_t	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	size_t			len;
	char			*space;
	unsigned int	num;

	len = lenint(n);
	space = (char *)malloc((len + 1) * sizeof(char));
	if (!space)
		return (0);
	space[len] = '\0';
	num = n;
	if (n < 0)
	{
		space[0] = '-';
		num = -n;
	}
	while (num > 0)
	{
		space[--len] = (num % 10) + '0';
		num = num / 10;
	}
	if (n == 0)
		space[0] = '0';
	return (space);
}

void	handle_signal(int signum, siginfo_t *info, void *context)
{
	static int				bit_count = 0;
	static unsigned char	character = 0;

	(void)context;
	if (signum == SIGUSR2)
		character |= (1 << (7 - bit_count));
	bit_count++;
	if (bit_count == 8)
	{
		if (character == '\0')
			write(1, "\n", 1);
		else
			write(1, &character, 1);
		bit_count = 0;
		character = 0;
	}
	if (kill(info->si_pid, SIGUSR1) == -1)
		exit(EXIT_FAILURE);
}

int	main(void)
{
	struct sigaction	sa;
	char				*str_pid;

	str_pid = ft_itoa(getpid());
	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
		return (EXIT_FAILURE);
	write(1, "Server pid:", 12);
	write(1, str_pid, ft_strlen(str_pid));
	write(1, "\n", 1);
	free(str_pid);
	while (1)
		pause();
	return (EXIT_SUCCESS);
}
