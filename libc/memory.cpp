
extern "C" {

// this function will copy a memory from source to destination with size n
void *memcpy(char *dst, char *src, int n)
{
	char *p = dst;
	while (n--)
		*dst++ = *src++;
	return p;
}

// set the source memory with destination memory address
void *memset(char *dst,char src, int n)
{
	char *p = dst;
	while (n--)
		*dst++ = src;
	return p;
}

}
