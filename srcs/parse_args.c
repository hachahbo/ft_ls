#include "../includes/ft_ls.h"

static int	is_flag_char(char c)
{
	return (c == 'l' || c == 'a' || c == 'r' || c == 't' || c == 'R');
}

static int	parse_flag(char c, t_options *opts)
{
	if (c == 'l')
		opts->flags |= FLAG_L;
	else if (c == 'a')
		opts->flags |= FLAG_A;
	else if (c == 'r')
		opts->flags |= FLAG_R;
	else if (c == 't')
		opts->flags |= FLAG_T;
	else if (c == 'R')
		opts->flags |= FLAG_REC;
	else
	{
		error_msg("invalid option", NULL);
		write(2, "usage: ft_ls [-lartR] [file ...]\n", 34);
		return (0);
	}
	return (1);
}

static int	parse_flags(char *arg, t_options *opts)
{
	int	i;

	i = 1;
	while (arg[i])
	{
		if (!is_flag_char(arg[i]))
			return (0);
		if (!parse_flag(arg[i], opts))
			return (0);
		i++;
	}
	return (1);
}

int	parse_options(int argc, char **argv, t_options *opts)
{
	int	i;

	opts->flags = 0;
	opts->argc = argc;
	opts->argv = argv;
	opts->arg_index = 1;
	i = 1;
	while (i < argc && argv[i][0] == '-' && argv[i][1] != '\0')
	{
		if (!parse_flags(argv[i], opts))
			return (0);
		i++;
		opts->arg_index = i;
	}
	return (1);
}
