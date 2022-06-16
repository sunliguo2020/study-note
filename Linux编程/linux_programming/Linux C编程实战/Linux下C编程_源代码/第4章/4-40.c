char *strcpy(char *dest,char *src)
{
	if ( (dest==NULL) || (src==NULL) )
	{
		printf("arg wrong");
		return NULL;
	}
	char *ret_string = dest; 
	while((*dest++=*src++)!='\0'); 
	return ret_string;
}
