c写cgi cookies 设置与读取
验证用户登录后，把用户名和密码写入cookies:
int checkadminlogin()
{
  char name[81];
  char pass[81];

  char tempUserName[81];
  char tempUserPass[81];
  cgiFormStringNoNewlines("username", name, 81);
  cgiFormStringNoNewlines("password", pass, 81);

  printf("Set-Cookie:username=%s;path=/\r\n",name);
  printf("Set-Cookie:pass=%s;path=/\r\n",pass);
  cgiHeaderContentType("text/html");
}

读出cookies：（利用了cgic库）

void Cookies()
{
char **array, **arrayStep;
char value[255];
char cname[255];
char cpass[255];
int count=0;
if (cgiCookies(&array) != cgiFormSuccess) {
return;
}
arrayStep = array;
//fprintf(cgiOut, "<table border=1>\n");
//fprintf(cgiOut, "<tr><th>Cookie<th>Value</tr>\n");
//printf("arrayStep=%d\n",arrayStep);
while (*arrayStep) {
char value[1024];
//fprintf(cgiOut, "<tr>");
//fprintf(cgiOut, "<td>");
//cgiHtmlEscape(*arrayStep);
//fprintf(cgiOut, "<td>");
cgiCookieString(*arrayStep, value, sizeof(value));
  //printf("value=%s\n",value);
//cgiHtmlEscape(value);
//fprintf(cgiOut, "\n");
if(count==0)
{
  strcpy(cname,value);
}
if(count==1)
{
  strcpy(cpass,value);
}
arrayStep++;
count++;
}
//fprintf(cgiOut, "</table>\n");
//printf("cname=%s\n",cname);
//printf("cpass=%s\n",cpass);
cgiStringArrayFree(array);
}

修改cookies和写入一样，重新用一样的，重新写入一次即可，cookie里面的对应的名称不能改变，比如这个里面的name,pass.
