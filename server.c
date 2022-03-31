/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arendon- <arendon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 13:59:27 by arendon-          #+#    #+#             */
/*   Updated: 2022/02/11 16:41:22 by arendon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include "./libft/includes/libft.h"

/*
30    SIGUSR1      terminate process    User defined signal 1
31    SIGUSR2      terminate process    User defined signal 2
*/

int	g_pid = 0;

typedef struct s_hand{
	char	buf;
	int		bit;
	int		flag;
	int		size_pib;
	int		buf_del;
}	t_hand;

void	get_pid(char *str, int *pid)
{
	char	*str_pid;
	int		i;

	i = 0;
	str_pid = (char *)ft_calloc(12, 1);
	if (str_pid == NULL)
	{
		ft_printf("Calloc failed\n");
		exit (1);
	}
	while (str[i] != '$')
	{
		str_pid[i] = str[i];
		i++;
	}
	*pid = ft_atoi(str_pid);
	free(str_pid);
}

void static	reset_bit(char *str_pid, t_hand *hand)
{
	hand->bit = 7;
	if (hand->flag == 0)
	{
		str_pid[hand->size_pib] = hand->buf;
		hand->size_pib++;
	}
	if (hand->buf == '$' && hand->flag == 0)
	{
		get_pid(str_pid, &g_pid);
		hand->flag = 1;
	}
	if (hand->buf == '$' && hand->flag == 1)
		hand->buf_del++;
	if (hand->buf != '$' && hand->flag == 1)
		ft_printf("%c", hand->buf);
	else if (hand->buf == '$' && hand->buf_del > 1)
		ft_printf("%c", hand->buf);
	if (hand->buf == '\0')
	{
		kill(g_pid, SIGUSR1);
		g_pid = 0;
	}
	hand->buf = '\0';
}

static void	handler(int sig)
{
	static t_hand	hand;
	static char		*str_pid;

	if (g_pid == 0)
	{
		str_pid = (char *)ft_calloc(12, 1);
		if (str_pid == NULL)
		{
			ft_printf("Calloc failed\n");
			exit (1);
		}
		hand.bit = 7;
		hand.flag = 0;
		hand.size_pib = 0;
		hand.buf_del = 0;
		g_pid = 1;
		hand.buf = '\0';
	}
	if (sig == SIGUSR1)
		hand.buf |= (1 << hand.bit);
	hand.bit --;
	if (hand.bit == -1)
		reset_bit(str_pid, &hand);
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	sa;

	pid = getpid();
	ft_printf("server pid: %d\n", pid);
	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
	{
		pause();
	}
	return (0);
}
