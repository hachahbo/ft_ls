#ifndef FT_LS_H
# define FT_LS_H

# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <errno.h>

/* Flags */
# define FLAG_L (1 << 0)  // Long format
# define FLAG_A (1 << 1)  // Show hidden files
# define FLAG_R (1 << 2)  // Reverse order
# define FLAG_T (1 << 3)  // Sort by time
# define FLAG_REC (1 << 4) // Recursive

/* File information structure */
typedef struct s_file
{
	char			*name;
	char			*path;
	struct stat		stat;
	struct s_file	*next;
}	t_file;

/* Options structure */
typedef struct s_options
{
	int		flags;
	int		argc;
	char	**argv;
	int		arg_index;
}	t_options;

/* File list operations */
t_file		*file_new(const char *name, const char *path);
void		file_add(t_file **head, t_file *new);
void		file_free(t_file *head);
int			file_count(t_file *head);

/* Directory reading */
t_file		*read_directory(const char *path, t_options *opts);

/* Sorting */
void		sort_files(t_file **head, t_options *opts);
void		reverse_list(t_file **head);

/* Display */
void		display_files(t_file *files, t_options *opts);
void		display_long_format(t_file *files, t_options *opts);

/* Utilities */
int			ft_strcmp(const char *s1, const char *s2);
size_t		ft_strlen(const char *s);
char		*ft_strdup(const char *s);
char		*ft_strjoin(const char *s1, const char *s2);
void		error_msg(const char *prefix, const char *msg);

/* Argument parsing */
int			parse_options(int argc, char **argv, t_options *opts);

/* Recursive listing */
void		list_recursive(const char *path, t_options *opts);

/* Long format helpers */
void		format_permissions(mode_t mode, char *str);
char		*get_user_name(uid_t uid);
char		*get_group_name(gid_t gid);
void		format_time(time_t time, char *str);

#endif
