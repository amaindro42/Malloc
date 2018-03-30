# Malloc

This project is implementing a dynamic memory allocation
mechanism.

## Getting Started

### Installing

Clone the project and compile it

```
git clone https://github.com/amaindro42/Malloc.git && make -C Malloc
```

## Running tests

### Create testing files

Create c files allocating memory

```
int	main()
{
	int		i;
	char*	addr;

	i = 0;
	while (i < 1024)
	{
		addr = malloc(1024);
		addr[0] = 42;
		i++;
	}
	return (0);
}
```

Compile it

```
gcc test1.c -o test1
```

### Test the files

Run the created files using our library

```
./run.sh ./test1
```

You can also use know more informations about the allocations the library did

```
./run.sh /usr/bin/time -l ./tests/test1
```
