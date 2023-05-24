#include "utils/main.h"

/**
  * _getline - a function that gets the input
	* from the terminal and stores it in a buffer
  * @line_addr: parameter of type char **.
  * @n: parameter of type size_t *.
  * @stream: parameter of type FILE *.
	* could be a desciptor or a stream
  * Return: ssize_t .
 */
ssize_t _getline(char **line_addr, size_t *n, FILE *stream)
{
	char *buffer = NULL, read_c = '\0';
	static ssize_t count;
	int read_n = 0, ret, i = 0;

	if (count == 0)
		fflush(stream);
	else
		return (-1);
	count = 0;
	buffer = malloc(120 * sizeof(char));
	if (!buffer)
		return (-1);
	while (read_c != '\n')
	{
		read_n = read(STDIN_FILENO, &read_c, 1);
		if (read_n == -1 || (!read_n && !count))
		{
			free(buffer), buffer = NULL;
			return (-1);
		}
		if (!read_n && count)
		{
			count++;
			break;
		}
		if (count >= 120)
			buffer = _realloc(buffer, _al_len_(buffer), _al_len_(buffer) + 1);
		if (buffer == NULL)
			return (-1);
		buffer[count] = read_c;
		count++;
	}
	buffer[count] = '\0';
	if (read_c == '\n')
		_memcpy(buffer, *line_addr, count);
	ret = count;
	if (read_n)
		count = 0;
	return (ret);
}
