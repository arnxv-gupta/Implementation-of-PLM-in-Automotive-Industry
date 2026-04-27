// 1) Batch Utility – Login 

// --- Header Files ---
#include<conio.h> 
#include<stdio.h> 
#include<tcinit/tcinit.h> 
#include<tc/emh.h> 
#include<tc/tc_startup.h>

// --- Program ---
#include"Header.h" 
 
int ITK_user_main(int argc,char* argv[]) 
{ 
 char* u = ITK_ask_cli_argument("-u="); 
 char* p = ITK_ask_cli_argument("-p="); 
 char* g = ITK_ask_cli_argument("-g="); 
 char* h = ITK_ask_cli_argument("-h"); 
 
 int ifail; 
 char* error; 
 
 if (u == NULL || p == NULL || g == NULL || h) 
 { 
printf("\n\tPlease enter -u=(User ID) -p=(Password) -g=(Group) -h (For utility 
Help)"); 
  return 0; 
 } 
 ifail=ITK_init_module(u, p, g); 
 if (ifail == ITK_ok) 
 { 
  printf("\n\t***Login Successfully***"); 
 } 
 else 
 { 
  EMH_ask_error_text(ifail, &error); 
  printf("\n\t%s", error);  
 } 
 return 0; 
}
