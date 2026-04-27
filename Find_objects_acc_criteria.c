// 7) Batch Utility – Find_objects_acc_criteria 

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
 
int Find_objects_acc_criteria(char *u) 
{ 
 int ifail,count,i; 
 char*id; 
 tag_t user,*list; 
 
 WSO_search_criteria_t criteria; 
 ifail = SA_find_user2(u, &user); 
 ifail = WSOM_clear_search_criteria(&criteria); 
 tc_strcpy(criteria.class_name, "Item"); 
 tc_strcpy(criteria.name, "*"); 
 criteria.owner = user; 
 ifail = WSOM_search(criteria, &count, &list); 
 printf("\n\tNo. of objects = %d", count); 
 
 if (ifail==ITK_ok) 
  for (i = 0; i < count; i++) 
  { 
   ifail = ITEM_ask_id2(list[i], &id); 
   printf("\n\tID = %s", id); 
  } 
 if (list) 
  MEM_free(list); 
 
 return 0; 
}
