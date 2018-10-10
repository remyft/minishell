#include <termios.h>
#include <term.h>
#include "../libft/libft.h"


char        *ft_tgetstr(char *t)
{
	char            *tmp;

	if ((tmp = tgetstr(t, NULL)) == NULL)
	{
		ft_putstr_fd(t, 2);
		ft_putendl_fd(" not available", 2);
	}
	return (tmp);
}

int            ft_pchar(int nb)
{
	return (write(STDOUT_FILENO, &nb, 1));
}

void        ft_term_restore(struct termios save)
{
	tputs(ft_tgetstr("ei"), 1, ft_pchar);
	if (tcsetattr(0, TCSANOW, &save) == -1)
	{
		ft_putendl("Fatal restore error: tcsetattr().\n");
		exit(2);
	}
}

void		ft_define_new_term_cap(struct termios *save)
{
	struct termios	termios;

	if (tcgetattr(0, save) != 0)
	{
		ft_putendl("Fatal error: tcgetattr().\n");
		exit(2);
	}
	if (tcgetattr(0, &termios) != 0)
	{
		ft_putendl("Fatal error: tcgetattr().\n");
		exit(2);
	}
	termios.c_lflag &= ~(ICANON | ECHO | ISIG);
	termios.c_cc[VMIN] = 1;
	termios.c_cc[VTIME] = 0;
	tputs(ft_tgetstr("im"), 1, ft_pchar);
	if ((tcsetattr(0, TCSANOW, &termios)) == -1)
	{
		ft_putendl("Fatal error: tcsetattr().\n");
		exit(2);
	}
}


int		main(void)
{
	char	buff[10];
	struct termios	save;
	int		nb_read;
	int i;

	ft_define_new_term_cap(&save);
	nb_read = 0;
	signal(SIGINT, &sig_hdlr);
	while (1)
	{
		i = -1;
		nb_read = read(0, buff, 10);
		while (++i < nb_read)
		{
			ft_putchar(buff[i]);
			ft_putchar('\n');
		}
		if (buff[0] == 'c') {
			ft_term_restore(save);
			pid_t  pid = fork();
			if (pid == 0)
			{
				char *cmd[] = { "/sbin/ping", "google.fr", NULL };
				execve(cmd[0], cmd, NULL);
				exit(1);
			} else if (pid > 0) {
				int status;
				ft_putendl("waiting...");
				waitpid(pid, &status, 0);
				ft_putstr("ret=");
				ft_putnbr(status);
				ft_putchar('\n');
			}
			ft_define_new_term_cap(&save);
		}
		if (buff[0] == 'q')
			break;
	}
	ft_term_restore(save);
	return (0);
}
