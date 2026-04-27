// 9) Batch Utility – Import_dataset 

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
#include<ss/ss_const.h>

// --- Program ---
#include"Header.h" 
 
int Import_dataset(char* id) 
{ 
 int ifail, count,i; 
 char* error,* object_type; 
 tag_t item, rev, rel_type,* sec_object; 
 
 ifail = ITEM_find_item(id, &item); 
 ifail = ITEM_find_revision(item, "A", &rev); 
 ifail = GRM_find_relation_type("IMAN_specification", &rel_type); 
 ifail = GRM_list_secondary_objects_only(rev, rel_type, &count, &sec_object); 
 for ( i = 0; i < count; i++) 
 { 
  WSOM_ask_object_type2(sec_object[i], &object_type); 
  if (tc_strcmp(object_type, "Text") == 0) 
  { 
   ifail = AOM_refresh(sec_object[i], 1); 
   ifail = AE_import_named_ref(sec_object[i], "Text", "D:\\sample\\new.txt", 
NULL, SS_TEXT); 
   if (ifail == ITK_ok) 
   { 
    printf("\n\t***Files imported to named ref. successfully***"); 
   } 
   else 
   { 
    printf("\n\t%d", ifail); 
    EMH_ask_error_text(ifail, &error); 
    printf("\n\t%s", error); 
   } 
   ifail = AE_save_myself(sec_object[i]); 
   ifail = AOM_refresh(sec_object[i], 0);    
  } 
 } 
 if (sec_object) 
  MEM_free(sec_object); 
 return 0; 
}
