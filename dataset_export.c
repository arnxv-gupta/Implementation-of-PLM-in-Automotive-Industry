// 5) Batch Utility – dataset export 

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

// --- Program ---
#include"Header.h" 
 
int dataset_export(char* id) 
{ 
 if (id == NULL) 
 { 
  printf("\n\tPlease enter -id=(Item ID)"); 
  return 0; 
 } 
 int ifail,count,i,count1,j; 
 char *error, *sec_object_type,*ref_object_name,*path; 
 tag_t item,Rev, relation_type,*sec_object,*ref_object; 
 
 path = (char*)MEM_alloc(sizeof(char*)); 
 
 ifail = ITEM_find_item(id, &item); 
 ifail = ITEM_find_revision(item, "A", &Rev); 
 ifail = GRM_find_relation_type("IMAN_specification", &relation_type); 
 ifail = GRM_list_secondary_objects_only(Rev, relation_type, &count, &sec_object); 
 for (i = 0; i < count; i++) 
 { 
  ifail = WSOM_ask_object_type2(sec_object[i], &sec_object_type); 
  if (tc_strcmp(sec_object_type, "Text") == 0) 
  { 
AE_ask_all_dataset_named_refs2(sec_object[i], "Text", &count1, 
&ref_object); 
   for (j = 0; j < count1; j++) 
   { 
    IMF_ask_original_file_name2(ref_object[j], &ref_object_name); 
    tc_strcpy(path, ""); 
tc_strcpy(path, "D:\\Somnath_Do not 
Delete\\Somnath_ITK\\ITK_programs\\prog7_output\\"); 
    tc_strcat(path, ref_object_name); 
    ifail = AOM_refresh(sec_object[i], 1); 
    ifail = AE_export_named_ref(sec_object[i], "Text", path); 
    if (ifail == ITK_ok) 
    { 
printf("\n\t***Files linked with named ref. exported 
successfully = %s***",ref_object_name); 
    } 
     
 
 
else 
    { 
     EMH_ask_error_text(ifail, &error); 
     printf("\n\t%s", error); 
    } 
    ifail = AOM_refresh(sec_object[i], 0); 
   } 
   if (ref_object) 
    MEM_free(ref_object); 
  } 
  if (sec_object) 
   MEM_free(sec_object); 
 
 } 
 return 0; 
 
}
