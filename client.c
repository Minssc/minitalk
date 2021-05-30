/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 23:26:08 by minsunki          #+#    #+#             */
/*   Updated: 2021/05/30 13:35:18 by minsunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static int		slen(char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
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

static void		send(pid_t spid, char *str)
{
	int			i;
	char		c;

	while (1)
	{
		c = *str;
		i = 8;
		while (i--)
		{
			if (c & 0x1)
			{
				kill(spid, SIGUSR1);
				usleep(SIG_DELAY);
			}
			else
			{
				kill(spid, SIGUSR2);
				usleep(SIG_DELAY);
			}
			c >>= 1;
		}
		if (!*str++)
			break ;
	}
}

static void		awk(int sig)
{
	(void)sig;
	write(1, "server received msg\n", slen("server received msg\n"));
	exit(0);
}

int				main(int ac, char *av[])
{
	pid_t	spid;

	if (ac != 3)
	{
		write(1, "Usage: ", slen("Usage: "));
		write(1, av[0], slen(av[0]));
		write(1, " ", 1);
		write(1, "pid string\n", slen("pid string\n"));
		return (1);
	}
	signal(SIGUSR2, awk);
	spid = parse_pid(av[1]);
	usleep(SIG_DELAY);
	send(spid, av[2]);
	sleep(1);
	write(1, "server awk not received\n", slen("server awk not received\n"));
	return (0);
}
