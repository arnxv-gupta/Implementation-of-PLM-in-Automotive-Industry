// 13) Batch Utility – Change Ownership 

// --- Header Files ---
Use previous program’s header

// --- Program ---
//************************* single object ownership change ************************// 
 
#include"Header.h" 
 
int Change_Ownership(char* id) 
{ 
 int ifail; 
 char* error; 
 tag_t item, rev,new_user, new_group; 
 
 ifail = ITEM_find_item(id, &item); 
 ifail = ITEM_find_revision(item, "A", &rev); 
 
 ifail = SA_find_user2("admin", &new_user); 
 ifail = SA_find_group("Engineering", &new_group); 
 
 ifail = AOM_set_ownership(rev, new_user, new_group); 
 if (ifail == ITK_ok) 
 { 
  printf("\n\t***Ownership changed successfully***"); 
 } 
 else 
 { 
  EMH_ask_error_text(ifail, &error); 
  printf("\n\t%s", error); 
 } 
 return 0; 
} 
 
 
//******************* single Item & its revisions' ownership change *******************// 
 
#include"Header.h" 
 
int Change_Ownership(char* id) 
{ 
 int ifail, count, i; 
 char* error; 
 tag_t item, *revs, new_user, new_group; 
 
 ifail = ITEM_find_item(id, &item); 
 ifail = ITEM_list_all_revs(item, &count, &revs); 
 ifail = SA_find_user2("admin", &new_user); 
 ifail = SA_find_group("Engineering", &new_group); 
 ifail = AOM_set_ownership(item, new_user, new_group); 
 if (ifail == ITK_ok) 
 { 
  printf("\n\t***Ownership changed successfully for item***"); 
 } 
 else 
 { 
  EMH_ask_error_text(ifail, &error); 
  printf("\n\t%s", error); 
 } 
 
 for ( i = 0; i < count; i++) 
 { 
  ifail = AOM_set_ownership(revs[i], new_user, new_group); 
  if (ifail == ITK_ok) 
  { 
printf("\n\t***Ownership changed successfully for %d item revision 
***",i); 
  } 
  else 
  { 
   EMH_ask_error_text(ifail, &error); 
   printf("\n\t%s", error); 
  } 
 } 
  
 return 0; 
} 
 
 
//*** find multiple items with criteria and change their & their revisions' ownership ***// 
 
#include"Header.h" 
 
int Change_Ownership(char* id) 
{ 
 int ifail, count, i, count1,j; 
 char* error, *item; 
 tag_t * revs, new_user, new_group, *item_list; 
 WSO_search_criteria_t criteria; 
 
 ifail = WSOM_clear_search_criteria(&criteria); 
 tc_strcpy(criteria.class_name, "Item"); 
 tc_strcpy(criteria.name, "test3"); 
 WSOM_search(criteria, &count1, &item_list); 
 for ( j = 0; j < count1; j++) 
 { 
  ifail = ITEM_ask_id2(item_list[j], &item); 
  ifail = ITEM_list_all_revs(item_list[j], &count, &revs); 
  ifail = SA_find_user2("admin", &new_user); 
  ifail = SA_find_group("Engineering", &new_group); 
  ifail = AOM_set_ownership(item_list[j], new_user, new_group); 
  if (ifail == ITK_ok) 
  { 
   printf("\n\t***Ownership changed successfully for item***"); 
  } 
  else 
  { 
   EMH_ask_error_text(ifail, &error); 
   printf("\n\t%s", error); 
  } 
 
  for (i = 0; i < count; i++) 
  { 
   ifail = AOM_set_ownership(revs[i], new_user, new_group); 
   if (ifail == ITK_ok) 
   { 
printf("\n\t\t***Ownership changed successfully for %d item revision 
***", i); 
   } 
   else 
   { 
    EMH_ask_error_text(ifail, &error); 
    printf("\n\t%s", error); 
   } 
  } 
  if (revs) 
   MEM_free(revs); 
 } 
 if (item_list) 
  MEM_free(item_list); 
 
 return 0; 
}
