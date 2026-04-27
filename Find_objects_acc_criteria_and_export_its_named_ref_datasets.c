// 10) Batch Utility – Find objects acc. criteria and export its named ref. datasets 

// --- Header Files ---
Use previous program’s header

// --- Program ---
#include"Header.h" 
 
int Find_objects_acc_criteria(char* u) 
{ 
 int ifail, count, i; 
 char* id; 
 tag_t user, * list; 
 
 WSO_search_criteria_t criteria; 
 ifail = SA_find_user2(u, &user); 
 ifail = WSOM_clear_search_criteria(&criteria); 
 tc_strcpy(criteria.class_name, "Item"); 
 tc_strcpy(criteria.name, "test2"); 
 criteria.owner = user; 
 ifail = WSOM_search(criteria, &count, &list); 
 printf("\n\tNo. of objects = %d", count); 
 
 if (ifail == ITK_ok) 
  for (i = 0; i < count; i++) 
  { 
   ifail = ITEM_ask_id2(list[i], &id); 
   printf("\n\tItem ID = %s", id); 
   find_all_rev(list,i); 
  } 
 if (list) 
  MEM_free(list); 
 
 return 0; 
} 
 
int find_all_rev(tag_t* list,int i) 
{ 
 int j, rev_count; 
 char* rev_id; 
 tag_t* rev_list; 
 ITEM_list_all_revs(list[i], &rev_count, &rev_list); 
 printf("\n\t\tItemRevision count = %d", rev_count); 
 for ( j = 0; j < rev_count; j++) 
 { 
  ITEM_ask_rev_id2(rev_list[j], &rev_id); 
  printf("\n\t\tItemRevision ID = %s", rev_id); 
  dataset_export(rev_list,j ); 
 } 
 if (rev_list) 
  MEM_free(rev_list); 
 return 0; 
} 
 
int dataset_export(tag_t* rev_list,int j) 
{ 
 
 int ifail1, count, k, count1, l; 
 char* error, * sec_object_type, * ref_object_name, * path; 
 tag_t relation_type, * sec_object, * ref_object; 
 
 path = (char*)MEM_alloc(sizeof(char*)); 
 
 ifail1 = GRM_find_relation_type("IMAN_specification", &relation_type); 
ifail1 = GRM_list_secondary_objects_only(rev_list[j], relation_type, &count, 
&sec_object); 
  
 
for (k = 0; k < count; k++) 
 { 
  ifail1 = WSOM_ask_object_type2(sec_object[k], &sec_object_type); 
  if (tc_strcmp(sec_object_type, "Text") == 0) 
  { 
AE_ask_all_dataset_named_refs2(sec_object[k], "Text", &count1, 
&ref_object); 
   for (l = 0; l < count1; l++) 
   { 
    IMF_ask_original_file_name2(ref_object[l], &ref_object_name); 
    tc_strcpy(path, ""); 
    tc_strcpy(path, "D:\\sample\\bulk\\"); 
    tc_strcat(path, ref_object_name); 
    ifail1 = AOM_refresh(sec_object[k], 1); 
    ifail1 = AE_export_named_ref(sec_object[k], "Text", path); 
    if (ifail1 == ITK_ok) 
    { 
printf("\n\t\t***Files linked with named ref. exported 
successfully = %s***", ref_object_name); 
    } 
    else 
    { 
     EMH_ask_error_text(ifail1, &error); 
     printf("\n\t%s", error); 
    } 
    ifail1 = AOM_refresh(sec_object[k], 0); 
   } 
   if (ref_object) 
    MEM_free(ref_object); 
  } 
   
 } 
 if (sec_object) 
  MEM_free(sec_object); 
 return 0; 
}
