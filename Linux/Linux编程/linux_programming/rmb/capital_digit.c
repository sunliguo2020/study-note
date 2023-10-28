/*
 *	capital_digit.c
 */

#include <stdio.h>
#include <string.h>
//#include <assert.h>

#define LINE_SEPARATOR \
	"<------------------------------------------------------------------->\n"

#define PRINT_ERR printf("error(line:%d)\n",__LINE__);

//the Maxium of ºº×Ö
#define MAX_WORDS 100
	
enum digit{
	// digit
	ZERO = 0,
	ONE,
	TWO,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EIGHT,
	NINE,
	
	// base
	SHI,
	BAI,
	QIAN,
	
	// m_base
	WAN,
	YI,
	
	//measure
	YUAN,
	JIAO,
	FEN,
	ZHENG
};

enum type{
	DIGIT=0,
	BASE,
	M_BASE,
	MEASURE
};

struct digit_map{
	char *type_name;
	char type;
	int value;
	char *name;
}dm[]= 
{
	{"digit", DIGIT, ZERO, "Áã"},
	{"digit", DIGIT, ONE,  "Ò¼"},
	{"digit", DIGIT, TWO,  "·¡"},
	{"digit", DIGIT, THREE,"Èþ"},
	{"digit", DIGIT, FOUR, "ËÁ"},
	{"digit", DIGIT, FIVE, "Îé"},
	{"digit", DIGIT, SIX,  "Â½"},
	{"digit", DIGIT, SEVEN,"Æâ"},
	{"digit", DIGIT, EIGHT,"°Æ"},
	{"digit", DIGIT, NINE, "¾Á"},
	
	{"base",  BASE,  SHI,  "Ê°"},
	{"base",  BASE,  BAI,  "°Û"},
	{"base",  BASE,  QIAN, "Çª"},
	
	{"m_base",M_BASE, WAN, "Íò"},
	{"m_base",M_BASE, YI,  "ÒÚ"},
	
	{"measure",MEASURE,YUAN,"Ô²"},
	{"measure",MEASURE,JIAO,"½Ç"},
	{"measure",MEASURE,FEN, "·Ö"},
	{"measure",MEASURE,ZHENG,"Õû"},
	
	{NULL, -1, -1, NULL}
};

typedef struct{
	unsigned long long int_part;
	int dot_part;
} number_t;

/*=============================================================================
  inside functions
------------------------------------------------------------------------------*/
static int capital_2_number(char *str, number_t *number);
int generate_number(int data[], number_t *number);

static int number_2_capital(number_t number, char *buf, int buf_len);

static int char_query(char *str);
static char *str_trim(char *str);
static unsigned long long str2ull_10(char *str);
/*=============================================================================*/


// Input:from a file, filename gained from cmd_para
// Output: STDOUT
int main(int argc, char *argv[]){
	FILE *i_fp, *o_fp;
	char *i_file = NULL;
	char *o_file = "result.txt";
	char buf[1024] = "", *p_ch;
	int ret;
	number_t number;
	char read_buf[100];
	int i;
	
	switch(argc){
		case 2:
			i_file = argv[1];
			break;
		case 3:
			i_file = argv[1];
			o_file = argv[2];
			break;
		default:		
			printf("Usage:\n"
				   "  capital_digit <input_file_name> [output_file_name]\n"
				   "Note:\n"
				   "  default output_file_name:result.txt\n"
				  );
		return 0;
	}
	
	i_fp = fopen(i_file, "r");
	if(i_fp == NULL){
		printf("input:%s,output:%s\n", i_file, o_file);
		perror("fopen(input)");
		return -1;
	}
	o_fp = fopen(o_file, "w");
	if(o_fp == NULL){
		printf("input:%s,output:%s\n", i_file, o_file);
		perror("fopen(output)");
		fclose(i_fp);
		return -1;
	}
	
	while( fgets(buf, sizeof(buf), i_fp) ){
		int result;
		p_ch = str_trim(buf);
		if(p_ch == NULL){
			continue;
		}
		fprintf(o_fp,"%s", LINE_SEPARATOR);
		result = capital_2_number(p_ch, &number);
		if(result == -1){
			PRINT_ERR;
		}else{
			fprintf(o_fp,"%s", LINE_SEPARATOR);	
			fprintf(o_fp,
				"Original:\n"
			    "  %s\n", p_ch);
			fprintf(o_fp,
				"Result:\n"
			    "  %llu.%02u\n",number.int_part, number.dot_part);
			
		}
		
		fprintf(o_fp,"%s", LINE_SEPARATOR);	
		fprintf(o_fp,"\n");			
	}
	
	while(1){
		i=0;	
		memset(read_buf, 0, sizeof(read_buf));
		printf("Type a number:");
		scanf("%99s",read_buf);
		while( ( (read_buf[i] >= '0')&&(read_buf[i] <= '9')) ||
					 (read_buf[i] == '.')
				 )
		{
			i++;
		}
		read_buf[i] = 0;
		p_ch = index(read_buf, '.');
		if(p_ch != NULL){
			*p_ch = '\0';
			p_ch ++;
			if( strlen(p_ch)>2 ){
				*(p_ch+2) = '\0';
			}
			number.dot_part = atoi(p_ch);
		}else{
			number.dot_part = 0;
		}
		number.int_part = str2ull_10(read_buf);
		printf("read_buf=%s\n", read_buf);
		printf("number.int_part=%llu, number.dot_part=%u\n",
			number.int_part, number.dot_part);
		ret = number_2_capital(number, read_buf, sizeof(read_buf));
		if(ret != -1){
			fprintf(o_fp,"%s", LINE_SEPARATOR);	
			fprintf(o_fp,
				"Original:\n"
			    "  %llu.%02u\n", number.int_part, number.dot_part );
			fprintf(o_fp,
				"Result:\n"
			    "  %s\n",read_buf);
		}
		
		memset(read_buf, 0, sizeof(read_buf));
		printf("Do you want to quit?[Y/N]");
		scanf("%99s", read_buf);
		if( (read_buf[0] == 'Y') || (read_buf[0] == 'y') )
			break;
		
		if(strlen(read_buf) == 99)
			break;
	}
	fclose(i_fp);
	fclose(o_fp);
	
	return 0;
}
static int char_query(char *str){
	int i;
	
	if(str == NULL){
		return -1;
	}
//	printf("%#x %#x\n",str[0], str[1]);
	for(i=0;dm[i].name != NULL;i++){
		if(strncmp(str, dm[i].name, 2) == 0){
			return i;
		}
	}
	return -1;
	
}
static int number_2_capital(number_t number, char *buf, int buf_len){
	char num_str[25];
	char id_buf[100];
	int len, id_pos, i;
	
//	assert(buf);
	
	memset(num_str, 0, sizeof(num_str));
	memset(id_buf, -1, sizeof(id_buf));
	memset(buf, 0, sizeof(buf_len));
	
	snprintf(num_str, sizeof(num_str), 
		"%llu", number.int_part);
	printf("num_str:%s\n", num_str);
	len = strlen(num_str);
	id_pos = 0;
	i = 0;
	
	while(len > 0){
//		printf("len=%d\n", len);
		if(num_str[i] > '0'){
			id_buf[id_pos++] = num_str[i] - '0';
			switch((len-1) % 4){
				case 3:
					id_buf[id_pos++] = QIAN;
					break;
				case 2:
					id_buf[id_pos++] = BAI;
					break;
				case 1:
					id_buf[id_pos++] = SHI;
					break;
				default:
					break;
			}
			
		}else{
			if( (id_pos>0)&&(id_buf[id_pos-1] != ZERO) ){
				id_buf[id_pos++] = ZERO;
			}
		}
		if( (len > 4)&&(len%4 == 1) ){
			if(ZERO == id_buf[id_pos-1]){
				id_pos--;
			}
			if( (len/4)%2 == 1 ){
				id_buf[id_pos++] = WAN;
			}else{
				id_buf[id_pos++] = YI;
			}
		}
		
		i++;
		len--;
	}
	
	if(id_buf[id_pos-1] == ZERO){
		id_pos--;
	}
	id_buf[id_pos++] = YUAN;
	
	if(number.dot_part == 0){
		id_buf[id_pos] = ZHENG;
	}else{
		id_buf[id_pos++] = number.dot_part/10;
		id_buf[id_pos++] = JIAO;
		id_buf[id_pos++] = number.dot_part%10;
		id_buf[id_pos] = FEN;
	}
	
	i=0;
	while(id_buf[i] != -1){
		printf("id_buf[%d]=%d\n", i, id_buf[i]);
		if((i<<1) >= buf_len-1){
			PRINT_ERR;
			return -1;
		}
		memcpy( buf+(i<<1), dm[id_buf[i]].name, 2);
		i++;
	}
	
	return 0;
}
static int capital_2_number(char *str, number_t *number){
	int id;
	int i;
	int len;
	int data[MAX_WORDS+1];
	int data_pos=0;
	
	if(str == NULL){
		return 0;
	}
	
	for(i=0;i<=MAX_WORDS;i++){
		data[i] = -1;
	}
	
	len = strlen(str);
	for(i=0;i<len;i+=2){
		id = char_query(str+i);
		if(id == -1){
			printf("id=-1\n");
			return -1;
		}
		data[data_pos++] = id;
#ifdef DEBUG
		printf("%s:%s\n",dm[id].type_name, dm[id].name);
#endif
		
	}
#ifdef DEBUG
	for(i=0;i<MAX_WORDS;i++){
		printf("id=%d\n",data[i]);
	}	
#endif
	return generate_number(data, number);

}

int generate_number(int data[], number_t *number){
	int i=0;
	int id;
	long long result=0;
	int thousand=0;
	int digit=0;
	int dot = 0;
	char yuan_flag = 0,jiao_flag = 0, fen_flag = 0;
	
	if( (number == NULL) || (data == NULL) ){
		printf("number=%p,data=%p\n", number, data);
		return -1;
	}
	while(data[i] != -1){
		id = data[i];
		switch( dm[id].type){
			case DIGIT:
				digit = dm[id].value;
				break;
			case BASE:
				switch(dm[id].value){
					case SHI:
						digit *= 10;
						break;
					case BAI:
						digit *= 100;
						break;
					case QIAN:
						digit *= 1000;
						break;
					default:
						PRINT_ERR;
						return -1;
				}
				thousand += digit;
				digit = 0;
				break;
			case M_BASE:
				thousand += digit;
				digit = 0;
				switch(dm[id].value){
					case WAN:
						thousand *= 10000;
						result += thousand;
						thousand = 0;
						break;
					case YI:
						if(thousand != 0){
							result += thousand;
							thousand = 0;
						}
						result *= 100000000;
						break;
					default:
						PRINT_ERR;
						return -1;
				}
				break;
			case MEASURE:
				switch(dm[id].value){
					case YUAN:
						thousand += digit;
						digit = 0;
						result += thousand;
						thousand = 0;
						yuan_flag = 1;
						break;
					case JIAO:
						if(thousand != 0){
							result += thousand;
							thousand = 0;
						}
						yuan_flag = 1;
						dot = digit*10;
						digit = 0;
						
						break;
					case FEN:
						if(thousand != 0){
							result += thousand;
							thousand = 0;
						}
						yuan_flag = 1;
						dot += digit;
						digit = 0;
						break;
					case ZHENG:
						thousand += digit;
						digit = 0;
						if(thousand != 0){
							result += thousand;
							thousand = 0;
						}
						number->int_part = result;
						number->dot_part = 0;
						return 0;
					default:
						PRINT_ERR;
						return -1;
				}
				break;
			default:
				printf("data[i]=%d\n", data[i]);
				PRINT_ERR;
				return -1;
		}
		i++;
	}
	if(yuan_flag == 0){
		thousand += digit;
		digit = 0;
		result += thousand;	
	}
	if(digit != 0){
		dot = digit*10;
	}
	number->int_part = result;
	number->dot_part = dot;

	return 0;
}


static char *str_trim(char *str){
	int len;
	
	if(str == NULL){
		return str;
	}	
	len = strlen(str);
	//ignore the leading space
	while((len>=0)&&(isspace(*str))){
		str++;
		len--;
	}
	//cut the tailing space
	while(len > 0){
		if(isspace(str[len-1])){
			str[len-1] = '\0';
			len--;
		}else{
			break;
		}
	}
	if(len == 0)
		str = NULL;
	return str;	
}


static unsigned long long str2ull_10(char *str){
	unsigned long long tmp = 0;
	
	if(str == NULL){
		return 0;
	}
	while(isdigit(*str)){
//		printf("tmp=%llu\n",tmp);
		tmp = tmp*10 + *str - '0';
		str++; 
	}
	return tmp;
}
