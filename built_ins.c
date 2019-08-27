#include "shell.h"

/**
 * simple_help - Display helpful information about builtin commands
 * @args: The list of user input arguments
 * @env: The environmental variables
 *
 * Return: On successful execution 0, on failure a status value
 */
int simple_help(char **args, list_t *env)
{
	char output[] = "These shell commands are defined internally.  Type ";
	char output2[] = "`help' to see this list.\nType `help name' to find ";
	char output3[] = "out more about the function `name'.\n";
	char output4[] = "alias\ncd\nenv\nexit\nhelp\nsetenv\nunsetenv\n";

	(void) env;
	if (args[1] == NULL)
	{
		write(STDOUT_FILENO, output, _strlen(output));
		write(STDOUT_FILENO, output2, _strlen(output2));
		write(STDOUT_FILENO, output3, _strlen(output3));
		write(STDOUT_FILENO, output4, _strlen(output4));
	}
	else
		which_help(args[1]);

	free_args(args);
	return (0);
}

/**
 * simple_history - Display the history list
 * @args: The list of user input arguments
 * @env: The environmental variables
 *
 * Return: On successful execution 0, on failure a status value
 */
int simple_history(char **args, list_t *env)
{
	(void) env;

	free_args(args);

	args[0] = _strdup("echo");
	args[1] = _strdup("$HISTFILE");

	return (0);
}

/**
 * simple_cd - changes current directory
 * @args: list of user input arguments
 * @env: the enviromental variables
 *
 * Return: On successful execution 0, on failure a status value
 */
int simple_cd(char **args, list_t *env)
{
	int exec_stat, is_sign = 0;
	char *input_dir = args[1];
	char *current_dir;
	char *error_msg;
	char buff[4096]; /* PATH_MAX = 4096 */

	if (input_dir == NULL)
		exec_stat = chdir(_getenv_value("HOME", env));
	else if (!_strcmp(input_dir, "-"))
		exec_stat = chdir(_getenv_value("OLDPWD", env)), is_sign = 1;
	else
		exec_stat = chdir(input_dir);

	if (exec_stat != 0)
	{
		error_msg = str_concat("can't cd to ", input_dir);
		print_error(args, env, error_msg);
		free(error_msg);
		free_args(args);
		return (2);
	}

	_setenv("OLDPWD", _getenv_value("PWD", env), &env);
	_setenv("PWD", getcwd(buff, 4096), &env);

	current_dir = _getenv_value("PWD", env);
	if (is_sign)
	{
		write(STDERR_FILENO, current_dir, _strlen(current_dir));
		write(STDERR_FILENO, "\n", 1);
	}
	free_args(args);
	return (0);
}

int _erratoi(char *s)
{
        int i = 0;
        unsigned long int result = 0;

        if (*s == '+')
                s++;
        for (i = 0;  s[i] != '\0'; i++)
        {
                if (s[i] >= '0' && s[i] <= '9')
                {
                        result *= 10;
                        result += (s[i] - '0');
                        if (result > 20000000)
                                return (-1);
                }
                else
                        return (-1);
        }
        return (result);
}

/**
 * simple_exit - cause a termination of simple shell
 * @args: list of user input arguments
 * @env: the enviromental variables
 *
 * Return: On successful execution 0, on failure a status value
 */
int simple_exit(char **args, list_t *env)
{
	int status = 0;
	char *error_msg;
	(void) env;

	if (args[1] != NULL)
	{
		status = _erratoi(args[1]);
		if (status == -1)
		{
			//error_msg = str_concat("Illegal number: ", args[1]);
			//print_error(args, env, error_msg);
			//free(error_msg);
			free_args(args);
			return (2);
		}
	}

	free_args(args);
	exit(status);
	return (0);
}

/**
 * not_built_in - handles the case if inputted command isn't a built-in
 * @args: list of user input arguments
 * @env: the enviromental variables
 *
 * Return: Always returns -1
 */
int not_built_in(char **args, list_t *env)
{
	(void) args;
	(void) env;

	return (-1);
}
