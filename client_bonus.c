/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 23:26:08 by minsunki          #+#    #+#             */
/*   Updated: 2021/05/30 18:45:21 by minsunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client_bonus.h"

int				g_awk;

static void		putstr(char *str)
{
	int			i;

	i = 0;
	while (str[i])
		i++;
	write(1, str, i);
}

static pid_t	parse_pid(char *str)
{
	pid_t		ret;

	ret = 0;
	while (*str)
	{
		if (*str < '0' || '9' < *str)
			break ;
		ret = ret * 10 + (*str - '0');
		str++;
	}
	return (ret);
}

static int		send(pid_t spid, char c)
{
	int			bi;
	int			wc;
	int			rt;

	bi = 0;
	rt = 0;
	while (rt++ < RETRY_LIM)
	{
		wc = 0;
		g_awk = 0;
		kill(spid, ((c & (1 << bi)) ? SIGUSR1 : SIGUSR2));
		while (++wc < AWK_WAIT)
		{
			if (g_awk)
			{
				++bi;
				rt = 0;
				break ;
			}
			usleep(1);
		}
		if (bi == 8)
			return (1);
	}
	return (0);
}

static void		awk(int sig)
{
	(void)sig;
	g_awk = 1;
}

int				main(int ac, char *av[])
{
	pid_t		spid;

	if (ac != 3)
	{
		putstr("Usage: ");
		putstr(av[0]);
		putstr(" pid string\n");
		return (1);
	}
	signal(SIGUSR1, awk);
	signal(SIGUSR2, awk);
	spid = parse_pid(av[1]);
	while (1)
	{
		if (!send(spid, *av[2]))
		{
			send(spid, '\0');
			putstr("failed to send msg :<\n");
			return (1);
		}
		if (!*(av[2]++))
			break ;
	}
	putstr("msg send success\n");
	return (0);
}
