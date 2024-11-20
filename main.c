#include "pf.h"

void	p_flt(char *pid, char **str)
{
	int	min_flt;
	int	maj_flt;

	min_flt = atoi(str[9]);
	maj_flt = atoi(str[11]);
	printf("PID: %s\n", pid);
	printf("Minor Page Faults (min_flt): %d\n", min_flt);
	printf("Major Page Faults (maj_flt): %d\n", maj_flt);
	printf("Summation of Page Faults : %d\n", maj_flt + min_flt);
}

void	free_2d(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	read_file(int *fd, int size, char **av)
{
	int		i;
	char	*buff;
	char	**data;

	i = 0;
	while (i < size)
	{
		if (fd[i] == -1)
		{
			printf("No PID: %s\n", av[i + 1]);
			i++;
			continue ;
		}
		buff = get_next_line(fd[i]);
		data = ft_split(buff, ' ');
		p_flt(av[i + 1], data);
		free_2d(data);
		free(buff);
		i++;
	}
}

void	open_file(int *fd, int size, char **av)
{
	int		i;
	char	*tmp;
	char	*path;

	i = 0;
	while (i < size)
	{
		tmp = ft_strjoin("/proc/", av[i + 1]);
		path = ft_strjoin(tmp, "/stat");
		fd[i] = open(path, O_RDONLY);
		free(tmp);
		free(path);
		i++;
	}
}

void	close_file(int *fd, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		close(fd[i]);
		i++;
	}
}

int	main(int ac, char **av)
{
	int		*fd;

	if (ac == 1)
	{
		printf("Please input 1 process minimum\n");
		return (0);
	}
	fd = malloc(sizeof(int) * (ac - 1));
	open_file(fd, ac - 1, av);
	read_file(fd, ac - 1, av);
	close_file(fd, ac - 1);
	free(fd);
	return (0);
}
