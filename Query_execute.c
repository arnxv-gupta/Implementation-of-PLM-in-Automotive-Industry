// 6) Batch Utility – Query execute 

// --- Header Files ---
#include<conio.h> 
#include<stdio.h> 
#include<tcinit/tcinit.h> 
#include<tc/emh.h> 
#include<tc/tc_startup.h> 
#include<tccore/item.h> 
#include<sa/user.h> 
#include<tc/folder.h> 
#include<tccore/aom.h> 
#include<tccore/tctype.h> 
#include<ae/dataset.h> 
#include<ae/datasettype.h> 
#include<tccore/grm.h> 
#include<tccore/aom_prop.h> 
#include<tccore/workspaceobject.h> 
#include<fclasses/tc_string.h> 
#include<sa/tcfile.h> 
#include<base_utils/Mem.h> 
#include<qry/qry.h>

// --- Program ---
#include"Header.h" 
 
int Query_execute() 
{ 
 int ifail,count,i; 
 char *error,**entries,**values,*id; 
 tag_t qry,*object; 
 
 ifail = QRY_find2("TC_query", &qry); 
 if (ifail == ITK_ok) 
 { 
  printf("\n\t***Query found***"); 
 } 
 else 
 { 
  EMH_ask_error_text(ifail, &error); 
  printf("\n\t%s", error); 
 } 
 
 entries = (char**) MEM_alloc(sizeof(char*)); 
 entries[0] = (char*) MEM_alloc(sizeof(char*)); 
 tc_strcpy(entries[0], "ID"); 
 entries[1] = (char*) MEM_alloc(sizeof(char*)); 
 tc_strcpy(entries[1], "Name"); 
 
 values = (char**) MEM_alloc(sizeof(char*)); 
 values[0] = (char*) MEM_alloc(sizeof(char*)); 
 tc_strcpy(values[0], "*"); 
 values[1] = (char*) MEM_alloc(sizeof(char*)); 
 tc_strcpy(values[1], "TEST1"); 
 
 ifail = QRY_execute(qry, 2, entries, values, &count, &object); 
 if (ifail == ITK_ok) 
 { 
  printf("\n\t***Query execute completed***"); 
 } 
 else 
 { 
  EMH_ask_error_text(ifail, &error); 
  printf("\n\t%s", error); 
 } 
 
  
printf("\n\t Count = %d", count); 
 
 for ( i = 0; i < count; i++) 
 { 
  ITEM_ask_id2(object[i], &id); 
  printf("\n\t ID = %s", id); 
 } 
 return 0; 
 
}
