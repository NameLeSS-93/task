Action()
{
	int temp;
	int radio_init_flag = 1;
	int len = 0;
	int radio_iter = 0;
	int p;
	int diff;
	int max_val = 0;
	char temp_arr[100];
	int l;
	int k;
	int flag_radio = 1;
	int flag_select = 1;
	int flag_select_diff = 0;
	char res_data[500];
	
	int radio_ptr_arr[50];
	char max_radio[30];
	char name_radio[30];
	
	int select_ptr_arr[50];
	char max_select[30];
	char name_select[30];
	
	int arr_iter = 3;
	int i = 0;
	int j;
	int q;
	int e;
	
	char text_param[17];
	
	char var_1[1000];
	
	char *start_ptr;
	char finish_test[50];
	int I = 1;
	
	web_set_max_html_param_len("3000");

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");
	web_add_auto_header("Conncection", 
		"keep-alive");
	
	web_url("test.youplace.net", 
		"URL=http://test.youplace.net/", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=", 
		"Snapshot=t1.inf", 
		"Mode=HTML", 
		LAST);
		
	
	web_reg_save_param("parags",
		"LB=<p>",
		"RB=</p>",
		"Ord=ALL",
		"NotFound=WARNING",
		"Search=Body",
		LAST);
	

	memset(res_data, 0, sizeof(res_data));


	web_url("test.youplace.net", 
		"URL=http://test.youplace.net/question/{q_num}", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://test.youplace.net/question/{q_num}", 
		"Snapshot=t1.inf", 
		"Mode=HTML", 
		LAST);


	
	do {
		
		sprintf(var_1, "{parags_%d}", arr_iter);
		// process radio buttons
		 if (strstr(lr_eval_string(var_1),"radio"))
         {
		 	lr_output_message("THERES A RADIO");
		 	lr_output_message("THIS IS IT!! %s", lr_eval_string(var_1));
		 	
		 	max_val = 0;
		 	start_ptr = lr_eval_string(var_1);
		 	diff = 0;
		 	i = 0;
		 	j = 0;
		 	while (1)
		 	{
		 		if ((*(start_ptr - 4) != 't' || *(start_ptr - 3) != 'y' || *(start_ptr - 2) != 'p') && *start_ptr == '=' && *(start_ptr + 1) == '"'){
		 			radio_ptr_arr[j] = i + 2;
		 			++j;
		 		}
		 		
		 		if ((*(start_ptr - 2) != 'i' || *(start_ptr - 1) != 'o') && *start_ptr == '"' && (*(start_ptr + 1) == '>' || *(start_ptr + 1) == ' ')){
		 			radio_ptr_arr[j] = i - 1;
		 			++j;
		 		}
		 		
		 		++start_ptr;
		 		++i;
		 		
		 		if (*start_ptr == '\0') {
		 			break;
		 		}
		 	}
		 	
 	
		 	start_ptr = lr_eval_string(var_1);
		 	i = 0;
		 	while (i < 50){
		 		radio_init_flag = 1;
		 		if ( radio_ptr_arr[i] ){
		 			k = radio_ptr_arr[i];
		 			
		 			l = 0;
		 			
		 			memset(temp_arr, 0, sizeof(temp_arr));
		 			while( k <= radio_ptr_arr[i + 1] ){
		 				if( i != 0 && flag_radio ){
		 					diff =  radio_ptr_arr[i + 1] - k;
		 					flag_radio = 0;
		 				}
		 				temp_arr[l] = *(start_ptr + k);
		 				++l;
		 				++k;
		 			}
		 			flag_radio = 1;
		 			
		 			if(i == 0){
		 				p = 0;
	 					while (temp_arr[p]){
	 						name_radio[p] = *(temp_arr + p);
	 						++p;
	 						
		 				}
		 				i += 2;
		 				radio_init_flag = 0;
		 			}
		 			//find max length radio button's name
		 			if (i != 0 && max_val < diff && radio_init_flag){
	 					max_val = diff;
	 					p = 0;
	 					memset(max_radio, 0, sizeof(max_radio));
	 					while (temp_arr[p]){
	 						max_radio[p] = *(temp_arr + p);
	 						++p;
	 					}
		 			}
		 		}
		 		if(radio_init_flag){
		 			i += 4;
		 		}
		 	}
 		/////////////////////
		/// 
		strcat(res_data, name_radio);
		if(name_radio){
			strcat(res_data, "=");
		}
		strcat(res_data, max_radio);
		strcat(res_data, "&");
		lr_output_message(lr_eval_string(name_radio));
		lr_output_message(lr_eval_string(max_radio));
		/////////////////
 	
		//new comment
        }
		 //process text field
		 if (strstr(lr_eval_string(var_1),"text"))
        {
		 	lr_output_message("THERES A TEXT");
		 	lr_output_message("THIS IS IT!! %s", lr_eval_string(var_1));

		 	
		 	start_ptr = lr_eval_string(var_1) + 25;
		 	
		 	i = 0;
		 	memset(text_param, 0, sizeof(text_param));
		 	while (*(start_ptr + i) != '"')
		 	{
		 		text_param[i] = *(start_ptr + i);
		 		++i;
		 	}
		 	
		 	
		 	///////////////////////////////
		 	
		 	strcat(res_data, text_param);
			if(text_param){
				strcat(res_data, "=");
			}
			strcat(res_data, "test");
			strcat(res_data, "&");
		 	
		 	lr_output_message(lr_eval_string(text_param));
		 	
		 	///////////////////////////////

        }
		 //process select
		 if (strstr(lr_eval_string(var_1),"select"))
        {
		 	lr_output_message("THERES A SELECT");
		 	lr_output_message("THIS IS IT!! %s", lr_eval_string(var_1));
		 	
		 	start_ptr = lr_eval_string(var_1);
		 	max_val = 0;
		 	i = 0;
		 	j = 0;
		 	diff = 0;
		 	memset(select_ptr_arr, 0, sizeof(select_ptr_arr));
		 	//parsing
		 	while (1)
		 	{
		 		if (*start_ptr == '=' && *(start_ptr + 1) == '"'){
		 			select_ptr_arr[j] = i + 2;
		 			++j;
		 		}
		 		
		 		if (*start_ptr == '"' && *(start_ptr + 1) == '>'){
		 			select_ptr_arr[j] = i - 1;
		 			++j;
		 		}
		 		
		 		++start_ptr;
		 		++i;
		 		
		 		if (*start_ptr == '\0') {
		 			break;
		 		}
		 	}
		 	
		 	start_ptr = lr_eval_string(var_1);
		 	i = 0;
		 	flag_select = 0;
		 	while (i < 50){
		 		if ( select_ptr_arr[i] ){
		 			k = select_ptr_arr[i];
		 			
		 			l = 0;

		 			memset(temp_arr, 0, sizeof(temp_arr));
//		 			q = 0;
		 			while( k <= select_ptr_arr[i + 1] ){
		 				
		 				if(i != 0 && flag_select){
		 					diff =  select_ptr_arr[i + 1] - k;
		 					flag_select = 0;
		 				}
		 				
		 				temp_arr[l] = *(start_ptr + k);
		 				
		 				++l;
		 				++k;

		 			}
		 			flag_select = 1;
		 			
		 			if(i == 0){
		 				p = 0;
		 				memset(name_select, 0, sizeof(name_select));
	 					while (temp_arr[p]){
	 						name_select[p] = *(temp_arr + p);
	 						++p;
		 				}
		 			}
		 			//find max length of select option
		 			if (i != 0 && max_val < diff){
		 				
	 					max_val = diff;
	 					
	 					p = 0;
	 					memset(max_select, 0, sizeof(max_select));
	 					while (temp_arr[p]){
	 						max_select[p] = *(temp_arr + p);
	 						++p;
	 					}
		 			}
		 		}
		 		i += 2;
		 	}
		 	/////////////////////
 			/// 
 			strcat(res_data, name_select);
			if(name_select){
				strcat(res_data, "=");
			}
			strcat(res_data, max_select);
			strcat(res_data, "&");
			
 			lr_output_message(lr_eval_string(name_select));
 			lr_output_message(lr_eval_string(max_select));
 			/////////////////
		 }
		
		++arr_iter;
	} while (arr_iter < lr_paramarr_len("parags"));
	
	
	
	lr_output_message(lr_eval_string(res_data));

	lr_save_string(lr_eval_string(res_data), "post_data");

	web_add_auto_header("Conncection", 
		"keep-alive");

	web_reg_save_param("finish_test",
		"LB=<h1>",
		"RB=</h1>",
		"Search=Body",
		"NotFound=WARNING",
		LAST);

	web_custom_request("q",
		"URL=http://test.youplace.net/question/{q_num}", 
		"Method=POST",	
		"RecContentType=text/html", 
		"Referer=http://test.youplace.net/question/{q_num}", 
		"Mode=HTML",
		"Body={post_data}",		
		LAST
	);
	
	sprintf(finish_test, "{finish_test}");

	if(strlen(finish_test) > 13){
		lr_output_message("SCRIPT FINISHED!");
		return 0;
	}
	return 0;
}