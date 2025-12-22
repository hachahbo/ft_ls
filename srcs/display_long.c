#include "../includes/ft_ls.h"

void	format_permissions(mode_t mode, char *str)
{
	str[0] = S_ISDIR(mode) ? 'd' : '-';
	str[0] = S_ISLNK(mode) ? 'l' : str[0];
	str[1] = (mode & S_IRUSR) ? 'r' : '-';
	str[2] = (mode & S_IWUSR) ? 'w' : '-';
	str[3] = (mode & S_IXUSR) ? 'x' : '-';
	str[4] = (mode & S_IRGRP) ? 'r' : '-';
	str[5] = (mode & S_IWGRP) ? 'w' : '-';
	str[6] = (mode & S_IXGRP) ? 'x' : '-';
	str[7] = (mode & S_IROTH) ? 'r' : '-';
	str[8] = (mode & S_IWOTH) ? 'w' : '-';
	str[9] = (mode & S_IXOTH) ? 'x' : '-';
	str[10] = '\0';
}

char	*get_user_name(uid_t uid)
{
	struct passwd	*pwd;

	pwd = getpwuid(uid);
	if (pwd)
		return (pwd->pw_name);
	return (NULL);
}

char	*get_group_name(gid_t gid)
{
	struct group	*grp;

	grp = getgrgid(gid);
	if (grp)
		return (grp->gr_name);
	return (NULL);
}

void	format_time(time_t time, char *str)
{
	char	*time_str;
	int		i;

	time_str = ctime(&time);
	i = 4;
	while (i < 16)
	{
		str[i - 4] = time_str[i];
		i++;
	}
	str[12] = '\0';
}

static void	print_file_info(t_file *file)
{
	char	perms[11];
	char	time_str[13];

	format_permissions(file->stat.st_mode, perms);
	format_time(file->stat.st_mtime, time_str);
	printf("%s %3ld %-8s %-8s %8ld %s %s\n",
		perms,
		(long)file->stat.st_nlink,
		get_user_name(file->stat.st_uid),
		get_group_name(file->stat.st_gid),
		(long)file->stat.st_size,
		time_str,
		file->name);
}

void	display_long_format(t_file *files, t_options *opts)
{
	t_file	*curr;
	long	total;

	(void)opts;
	if (!files)
		return ;
	total = 0;
	curr = files;
	while (curr)
	{
		total += curr->stat.st_blocks;
		curr = curr->next;
	}
	printf("total %ld\n", total);
	curr = files;
	while (curr)
	{
		print_file_info(curr);
		curr = curr->next;
	}
}
