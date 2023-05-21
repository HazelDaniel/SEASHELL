#include "utils/main.h"

ssize_t _getline(char **line_addr, size_t *n, FILE *stream)
{
	char *buffer = NULL, read_c = '\0';
	static ssize_t count;
	int read_n = 0, ret, i = 0;

	if (count == 0)
		fflush(stream);
	else
		return(-1);

	count = 0;

	buffer = malloc(120 * sizeof(char));
	if (!buffer)
		return (-1);

	while (read_c != '\n')
	{
		read_n = read(STDIN_FILENO, &read_c, 1);
		if (read_n == -1 || (!read_n && !count))
		{
			/* NOTHING IS TYPED IN */
			// puts("here");
			free(buffer);
			buffer = NULL;
			return (-1);
		}
		if (!read_n && count)
		{
			// puts("read some stuffs tho");
			/*normal end of stream*/
			count++;
			break;
		}
		// puts("reading stuff");
		if (count >= 120)
			buffer = _realloc(buffer, _al_len_(buffer), _al_len_(buffer) + 1);
		if (buffer == NULL)
			return (-1);
		buffer[count] = read_c;
		count++;
		// printf("count is :%zu\n", count);
	}
	buffer[count] = '\0';

	if (read_c == '\n')
	{
		// printf("buffer is :%s\t", buffer);
		// printf("and count is :%zu\n", count);
		_memcpy(buffer, *line_addr, count);
	}

	// puts("round up");

	ret = count;
	if (read_n)
		count = 0;
	return (ret);
}
