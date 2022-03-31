/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arendon- <arendon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 11:24:01 by arendon-          #+#    #+#             */
/*   Updated: 2022/02/11 19:12:48 by arendon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include "./libft/includes/libft.h"

static void	handler(int sig)
{
	if (sig == SIGUSR1)
		ft_printf("<<message received>>\n");
	if (sig == SIGUSR2)
		ft_printf("<<something went wrong>>\n");
}

static void	free_str(char *s1, char *s2, char *s3)
{
	free(s1);
	free(s2);
	free(s3);
}

static void	send_char(pid_t pid_server, char c)
{
	int	bit;

	bit = 7;
	while (bit >= 0)
	{
		if (c & (1 << bit))
			kill(pid_server, SIGUSR1);
		else
			kill(pid_server, SIGUSR2);
		usleep(50);
		bit--;
	}
}

static void	send_str(pid_t pid_server, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		send_char(pid_server, str[i]);
		i++;
	}
	send_char(pid_server, '\0');
}

int	main(int argc, char **argv)
{
	pid_t				pid;
	char				*pid_c;
	char				*pid_f;
	char				*pid_str;
	struct sigaction	sa;

	if (argc != 3 || !ft_strlen(argv[2]))
	{
		ft_printf("Wrong input");
		return (1);
	}
	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	pid = getpid();
	pid_c = ft_itoa(pid);
	pid_f = ft_strjoin(pid_c, "$");
	pid = ft_atoi(argv[1]);
	pid_str = ft_strjoin(pid_f, argv[2]);
	send_str(pid, pid_str);
	free_str(pid_c, pid_f, pid_str);
	return (0);
}

/* "ABC 123 😀😎😀😎😀😀😎😀😎😀😀😎😀😎😀😀😎😀😎😀😀��😀😎😀😀😎😀😎😀 holaA "
./client <Pid-server> "`cat Makefile`" */