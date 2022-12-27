/**********************************************************************************


FILENAME: header.hpp
DESCRIPTION:This file is used to have function prototype and class definition.

DATE            NAME              REASON
------------------------------------------------------------------
19/9/22         Group-4          This is done for creation of function prototype and class definition 	

 *********************************************************************************/
#ifndef H_HEADER
#define H_HEADER
#include <iostream>
#include <string>
#include <list>
using namespace std;
class transaction        		//tranaction class definition
{
	protected:
		int transaction_id;
		int cust_id;
		char prod1[25];
		char prod2[25];
		char prod3[25];
		int total_amount;
		int discount;
		int amount;
	public:
		int view_transaction();                 // function prototype for view_customer
		int generate_bill(char*,char*,char*,int,int );  //function prototype for generating_bill
		int get_cust_id();		 	//function protype for get_cust_id
		int get_transaction_id();		//function prototype for get_transaction_id

};
class customer:public transaction     //customer class definition
{
	protected:
		int customer_id;
		char customer_name[25];
		long int cmobile_no;
		char customer_address[40];
	public:
		int register_customer();		//function prototype for register_customer
		int login_customer();			//function prototype for login_customer
		int view_customer();			//function prototype for view_customer
		int edit_customer_details();		//function prototype for edit_customer_details
		int view_items();			//function prototype for view_items
		int place_order();			//function prototype for place_order	
		int view_transaction_history();		//function prototype for view_transaction_history 
		int get_customer_id();			//function prototype for get_customer_id
		char* get_customer_name();		//function prototype for get_customer_name
		char* get_customer_address();		//function prototype for get_customer_address
		long int get_cmobile_no();		//function prototype for get_cmobile_no

};
class product    //product class definition
{
	protected:
		int product_id;
		char product_name[25];
		int no_of_units;
		int cost;
		int units_sold;
		int sup_id;
	public:	
		int view_product();			//function prototype for view_product
		int edit_product_details();		//function prototype for edit_product_details
		int get_product_id();			//function prototype for get_product_id
		int get_sup_id();			//function prototype for get_up_id
		int get_cost();				//function prototype for get_cost
		char* get_product_name();		//function prototype for get_product_name
		int get_no_of_units();			//function prototype for get_no_of_units
		int get_units_sold();			//function prototype for get_units_sold
		void set_no_of_units(int);		//function prototype for set_no_of_units
		void set_units_sold(int);		//function prototype for set_units_sold
		void set_cost(int);		//function prototype for set_units_sold
                void set_product_id(int);
                void set_product_name(char*);
                void set_sup_id(int);
};
class supplier:public product   //supplier class definition
{
	protected:
		int supplier_id;
		char supplier_name[25];
		char supplier_address[40];
		long int mobile_no;

	public:
		int register_supplier();		//function prototype for register_supplier
		int login_supplier();			//function prototype for login_supplier
		int edit_supplier_details();		//function prototype for edit_supplier_details
		int view_supplier();			//function prototype for view_supplier
		int products_supplied();		//function prototype for products_supplied
		int add_product();			//function prototype for add_product
		int edit_product();			//function prototype for edit_product
		int get_supplier_id();			//function prototype for get_supplier_id
		char* get_supplier_name();		//function prototype for get_supplier_name
		char* get_supplier_address();		//function prototype for get_supplier_address
		long int get_mobile_no();		//function prototype for get_mobile_no
};


class Admin:public customer,public supplier  	//defining Admin class which inehrits customer and supplier
{
	public:
		int maintain_supplier();		//function prototype for maintain_supplier
		int maintain_customer();		//function prototype for maintain customer
		int maintain_product();			//function protoype for maintain_product
		int remove_supplier();			//function prototype for remove_supplier
		int remove_customer();			//function prototype for remove_supplier
		int remove_product();			//function prototype for remove_product
		int view_supplier_list();		//function prototype for view_supplier_list
		int view_customer_list();		//function prototype for view_customer_list
		int view_product_list();		//function prototype for view_product_list
		int view_transactions();		//function prototype for view_transactions
		int adding_product();			//function prototype for add_product
		int edit_supplier();			//function prototype for edit_supplier
		int edit_customer();			//function prototype for edit_customer 
		int editing_product();			//function prototype for edit_product
		int order_stock();			//function prototype for order_stock
		int stock_report();			//function prototype for stock_report
		int top_three_product();			//function prototype for top_3_product
};


Admin ad;		//globally declaring admin object
char temp[40];		//globally declaring string
list<product> prod;	//globally creating product list
list<supplier> sup;	//globally creating supplier list
list<customer> cust;	//globally creating customer list
list<transaction> trans; //globally creating transaction list

int supplier_corner();  		//function prototype for supplier_corner
int customer_corner();  		//function prototype for customer_corner
int admin_corner();			//function prototype for admin_corner
int supplier_list_to_file();		//function prototype for supplier_list_to_file
int supplier_file_to_list(); 		//function prototype for supplier_file_to_list 
int customer_list_to_file();		//function prototype for customer_list_to_file
int customer_file_to_list(); 		//function prototype for customer_file_to_list
int product_list_to_file(); 		//function prototype for product_list_to_file
int product_file_to_list(); 		//function prototype for product_file_to_list
int transaction_list_to_file(); 	//function prototype for transaction_list_to_file
int transaction_file_to_list(); 	//function prototype for transaction_file_to_list
#endif
