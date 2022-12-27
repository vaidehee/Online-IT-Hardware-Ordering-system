/**********************************************************************************


FILENAME: func1.cpp
DESCRIPTION:This file is used to display the main menu to the user.

DATE            NAME              REASON
------------------------------------------------------------------
22/9/22        Group-4          This is done for creation of menu  	

 *********************************************************************************/
#ifndef FUNC1
#define FUNC1
#include <iostream>
#include <string>      //Includes string functions
#include <string.h>      //Includes string functions
#include <iomanip>
#include "header.hpp"
#include "validations.cpp"
#include <mutex>
#include <thread>
mutex accum_mutex;

/**********************************************************************************


FUNCTIONNAME: register_customer()
DESCRIPTION:This function  is used to register customer.

 *********************************************************************************/
int customer::register_customer()
{
	int id=0;
	if(cust.empty()) //Checting if customer list is empty.
	{
		id=1000;
	}
	for(customer c:cust) //Iterating through customer list.
	{
		if(id<c.customer_id)
		{
			id=c.customer_id;
		}
	}
	id+=1;
	customer c1;
	c1.customer_id=id;
	int count=0;
	cout<<endl<<"Enter Details for Customer Registration"<<endl;
	cout<<"-----------------------------------------------"<<endl;	
	while(1)
	{
		cout<<"Enter Customer Name: ";
		if(count==0)
		{
			cin.ignore(1,'\n');
			count++;
		}
		else
		{
			cin.ignore(0,'\n');
		}
		cin.getline(temp,40); //Taking customer name as input and validating it.
		if(validations::check_name(temp))
		{
			continue;
		}
		 strcpy(c1.customer_name,temp);
			break;
	}
	while(1)
	{
		cout<<"Enter Customer address: ";
		cin.ignore(0,'\n');
		cin.getline(temp,40);  //Taking customer address as input and validating it.
		if(validations::check_address(temp)) 
		{
			continue;
		}
		strcpy(c1.customer_address,temp);
		break;
	}
	while(1)
	{
		cout<<"Enter Customer Mobile number: ";
		cin>>temp;
		if(validations::check_mobile_number(temp)) //Taking mobile number as input and validating it.
		{
			continue;
		}
			c1.cmobile_no=atol(temp); 
			break;
	}
	cust.push_back(c1);  //Inserting customer details in customer list.
	cout<<"\nCustomer Added Successfully!!!"<<"\nCustomer Id is "<<c1.customer_id<<endl<<endl<<endl;
	return EXIT_SUCCESS;	
}

/**********************************************************************************


FUNCTIONNAME:edit_customer_details()
DESCRIPTION:This function  is used to edit custome details.

 *********************************************************************************/
int customer::edit_customer_details()
{
	cout<<endl<<"Enter Details for Editing Customer"<<endl;
	cout<<"---------------------------------------"<<endl;	
	int count=0;
	while(1)
	{
		cout<<"Enter Customer Name: ";
		if(count==0)
		{
			cin.ignore(1,'\n');
			count++;
		}
		else
		{
			cin.ignore(0,'\n');
		}
		cin.getline(temp,40);
		if(validations::check_name(temp)) //Taking customer name as input and validating it.
		{
			continue;
		}
			strcpy(this->customer_name,temp);
			break;
	}


	while(1)
	{
		cout<<"Enter Customer address: ";
		cin.ignore(0,'\n');
		cin.getline(temp,40);
		if(validations::check_address(temp))  //Taking customer address as input and validating it.
		{
			continue;
		}
		strcpy(this->customer_address,temp);
		break;
	}
	while(1)
	{
		cout<<"Enter Customer Mobile number: ";
		cin>>temp;
		if(validations::check_mobile_number(temp)) //Taking mobile number as input and validating it.
		{
			continue;
		}
			this->cmobile_no=atol(temp);
			break;
	}	
	cout<<endl<<"Details editted Successfully!!!\n\n";
	return EXIT_SUCCESS;	
}

/**********************************************************************************


FUNCTIONNAME: view_items()
DESCRIPTION:This function  is used to display items to the customer.

 *********************************************************************************/
int customer::view_items()
{
	if(prod.empty()) //Checling if product list is empty or not.
	{
		cout<<endl<<"Product List is Empty!!!"<<endl<<endl<<endl;
		return EXIT_FAILURE;
	}
	int count=1;
	cout<<"\n            Showing Product List";
	cout<<endl<<"-----------------------------------------"<<endl;
	cout<<"S.No  Product_id   Name   Cost "<<endl;
	cout<<"-----------------------------------------"<<endl;
	for(list<product>::iterator it=prod.begin();it!=prod.end();it++)
	{
		cout<<"  "<<count++<<"  "<<setw(5)<<it->get_product_id()<<" "<<setw(12)<<it->get_product_name()<<" "<<setw(7)<<it->get_cost()<<endl;  //Displaying product.
	}
	return EXIT_SUCCESS; 
}

/**********************************************************************************


FUNCTIONNAME: place_order()
DESCRIPTION:This function  is used by the customer  to place order.

 *********************************************************************************/
int customer::place_order()
{

	if(prod.empty()) //Checking if product list is empty.
	{
		cout<<endl<<"Product List is Empty order cannot be placed!!!"<<endl<<endl<<endl;
		return EXIT_FAILURE;
	}
	int count=0;
	int choice=1;
	int flag=0;
	int prod_id;
	int qty;
	int prod_cost;
	char prod_name[25];
	char product_1[25]="Nil";
	char product_2[25]="Nil";
	char product_3[25]="Nil";
	int amount=0;
	this->view_items();
	while(choice!=0)
	{
		if(count==3)
		{
			cout<<"You cannot buy more than 3 products!!!"<<endl<<endl;
			break;
		}
		while(1)
		{
			cout<<"\nEnter Product Id to purchase: ";
			cin>>temp; 
			if(validations::check_digit(temp)) //Taking product id as input and validating it.
			{
				cout<<"Product Id should be digits only\n";
				continue;
			}
			else
			{
				prod_id=atoi(temp);
				break;
			}
		}
		for(list<product>::iterator it=prod.begin();it!=prod.end();it++)
		{
			if(it->get_product_id()==prod_id)
			{
				while(1)
				{
					cout<<"Enter to Quantity: ";
					cin>>temp;
					if(validations::check_digit(temp)) //Taking quantity as input and validating it
					{
						cout<<"Quantity should be digits only\n";
						continue;
					}
					else
					{
						qty=stoi(temp);
						break;
					}
				}
				strcpy(prod_name,it->get_product_name());		
				prod_cost=it->get_cost();		
				if((qty>it->get_no_of_units())||qty<0)
				{
					cout<<"Sorry quantity insufficient!!!\nAvailable Quantity : "<<it->get_no_of_units()<<endl<<endl;
					flag=1;
					break;
				}
				accum_mutex.lock();
				it->set_no_of_units(it->get_no_of_units()-qty);
				it->set_units_sold(qty);
				if(count==0)
				{
					strcpy(product_1,prod_name);
				}
				else if(count==1)
				{
					strcpy(product_2,prod_name);
				}
				else
				{
					strcpy(product_3,prod_name);
				}
				amount=amount+(qty*prod_cost);
				accum_mutex.unlock();
				count++;
				flag=1;
				break;
			}
		}
		if(flag==0)
		{
			cout<<"Sorry Product with "<<prod_id<<" id not found!!!"<<endl<<endl;
		}
		flag=0;
		while(1)
		{
			cout<<"Press 0 to Stop Shopping or any other to continue: ";
			cin>>temp; //Taking user choice to continue shopping and validate it.
			if(validations::check_digit(temp))
			{
				cout<<"Choice should be digits only\n";
				continue;
			}
			else
			{
				choice=stoi(temp);
				break;
			}
		}
	}
	if(count>0)
	{
		transaction t;
		t.generate_bill(product_1,product_2,product_3,this->customer_id,amount);
		trans.push_back(t);
	}
	cout<<endl<<endl<<"Thank You For Visiting Our Shop!!! "<<endl<<endl;
	return EXIT_SUCCESS;
}

/**********************************************************************************


FUNCTIONNAME: view_transaction_history()
DESCRIPTION:This function  is used to view transaction history to the customer.

 *********************************************************************************/
int customer::view_transaction_history()
{
	if(trans.empty()) //Checking if transaction history is empty or not.
	{
		cout<<endl<<"No Previous Transaction Available!!!"<<endl<<endl<<endl;
		return EXIT_FAILURE;
	}
	int count=0;
	int flag=0;
	list<transaction>::iterator it=trans.begin();
	for(;it!=trans.end();it++)
	{
		if(it->get_cust_id()==this->customer_id)
		{
			if(count==0)
			{
				cout<<"\n                                Transaction History"<<endl; //Displaying transaction history of customer if available or not.
				cout<<"----------------------------------------------------------------------------------------------------------"<<endl;
				cout<<"Id    Cust_ID    Prod_1      Prod_2      Prod_3     Total_amount    Discount     Amount_Paid"<<endl;
				cout<<"----------------------------------------------------------------------------------------------------------"<<endl;
				count=1;
			}	
			it->view_transaction();
			flag=1;
		}
	}
	if(flag==0)
	{
		cout<<endl<<"No Previous Transaction Available!!!"<<endl<<endl<<endl;
	}
	return EXIT_SUCCESS;
}

/**********************************************************************************


FUNCTIONNAME: get_customer_id()
DESCRIPTION:This function will return customer id.

 *********************************************************************************/
int customer::get_customer_id()
{
	return this->customer_id;
}


/**********************************************************************************


FUNCTIONNAME: get_customer_name()
DESCRIPTION:This function  is used to get customer name.

 *********************************************************************************/
char* customer::get_customer_name()
{
	return this->customer_name;
}


/**********************************************************************************


FUNCTIONNAME: get_customer_address()
DESCRIPTION:This function  is used to get customer address.

 *********************************************************************************/
char* customer::get_customer_address()
{
	return this->customer_address;
}
 

/**********************************************************************************


FUNCTIONNAME: get_cmobile_no()
DESCRIPTION:This function  is used to get mobile number of customer.

 *********************************************************************************/
long int customer::get_cmobile_no()
{
	return this->cmobile_no;
}

/**********************************************************************************


FUNCTIONNAME: view_customer()
DESCRIPTION:This function  is used to display the details of the customer.

 *********************************************************************************/
int customer::view_customer()
{
	cout<<endl<<"\n   Showing Details of Customer"<<endl;
	cout<<"---------------------------------------"<<endl;	
	cout<<"\tCustomer Id: "<<this->customer_id<<endl;
	cout<<"\tCustomer Name: "<<this->customer_name<<endl;
	cout<<"\tCustomer Address: "<<this->customer_address<<endl;
	cout<<"\tCustomer Mobile: "<<this->cmobile_no<<endl<<endl;
	return EXIT_SUCCESS;
}


/**********************************************************************************


FUNCTIONNAME: get_cust_id()
DESCRIPTION:This function is used to get customer id.

 *********************************************************************************/

int transaction::get_cust_id()
{
	return this->cust_id;
}


/**********************************************************************************


FUNCTIONNAME: view_transaction()
DESCRIPTION:This function  is used to display the transaction.

 *********************************************************************************/
int transaction::view_transaction()
{ 
	cout<<this->transaction_id<<" "<<setw(5)<<this->cust_id<<"  "<<setw(12)<<this->prod1<<" "<<setw(12)<<this->prod2<<" "<<setw(12)<<this->prod3<<" "<<setw(12)<<this->total_amount<<" "<<setw(12)<<this->discount<<" "<<setw(12)<<this->amount<<endl;
	return EXIT_SUCCESS;
}

/**********************************************************************************


FUNCTIONNAME: generate_bill()
DESCRIPTION:This function will generate bill and displayed to the customer.

 *********************************************************************************/
int transaction::generate_bill(char* product_1,char* product_2,char* product_3,int customer_id,int amount)
{

	int discount=0;
	int trans_id=0;
	if(trans.empty()) //Checking transaction if empty or not.
	{
		trans_id=3000;
	}
	for(transaction ts:trans) //Iterating through transaction list.
	{
		if(trans_id<ts.transaction_id)
		{
			trans_id=ts.transaction_id;
		}
	}
	trans_id+=1;
	if(amount>20000) //Calculating discount.
	{
		discount=(20*amount)/100;
	}
	else if(amount>10000&&amount<20000)
	{
		discount=(15*amount)/100;
	}
	else if(amount>5000&&amount<10000)
	{
		discount=(10*amount)/100;
	}
	else
	{
		discount=(5*amount)/100;
	}
	this->transaction_id=trans_id;
	this->cust_id=customer_id;
	strcpy(this->prod1,product_1);
	strcpy(this->prod2,product_2);
	strcpy(this->prod3,product_3);
	this->total_amount=amount;
	this->discount=discount;
	this->amount=amount-discount;
	system("clear");
	cout<<endl<<"Showing Bill Details"<<endl; //Displaying bill to the user.
	cout<<"--------------------"<<endl;
	cout<<"\tTransaction_id: "<<trans_id<<endl;
	cout<<"\tCustomer Id: "<<customer_id<<endl;
	cout<<"\tProduct 1: "<<product_1<<endl;
	cout<<"\tProduct 2: "<<product_2<<endl;
	cout<<"\tProduct 3: "<<product_3<<endl;
	cout<<"\tTotal_amount: Rs."<<amount<<endl;
	cout<<"\tDiscount: Rs."<<discount<<endl;
	cout<<"\tAmount: Rs."<<(amount-discount)<<endl;
	return EXIT_SUCCESS;
}




/**********************************************************************************


FUNCTIONNAME: register_supplier()
DESCRIPTION:This function  is used to register supplier.

 *********************************************************************************/
int supplier::register_supplier()
{
	int id=0;
	if(sup.empty()) //Checking if supplier list is empty or not.
	{
		id=100;
	}
	for(supplier s:sup) //Iterating to supplier list.
	{
		if(id<s.supplier_id)
		{
			id=s.supplier_id;
		}
	}
	id+=1;
	supplier s1;
	s1.supplier_id=id;
	int count=0;
	cout<<endl<<"Enter Details for Supplier Registration"<<endl;
	cout<<"---------------------------------------"<<endl;	
	while(1)
	{
		cout<<"Enter Supplier Name: ";
		if(count==0)
		{
			cin.ignore(1,'\n');
			count++;
		}
		else
		{
			cin.ignore(0,'\n');
		}
		cin.getline(temp,40); 
		if(validations::check_name(temp)) //Taking supplier name as input and validating it.
		{
			continue;
		}
			strcpy(s1.supplier_name,temp);
			break;
	}


	while(1)
	{
		cout<<"Enter Supplier address: ";
		cin.ignore(0,'\n');
		cin.getline(temp,40); 
		if(validations::check_address(temp))
		{
			continue;
		}
		strcpy(s1.supplier_address,temp);
		break;
	}
	while(1)
	{
		cout<<"Enter Supplier Mobile number: ";
		cin>>temp;
		if(validations::check_mobile_number(temp)) //Taking supplier mobile number as input and validating it.
		{
			continue;
		}
			s1.mobile_no=atol(temp);
			break;
	}
	sup.push_back(s1); //Inserting supplier details into supplier list.
	cout<<"\nSupplier Added Successfully!!!"<<"\nSupplier Id is "<<s1.supplier_id<<endl<<endl<<endl;
	return EXIT_SUCCESS;	
}


/**********************************************************************************


FUNCTIONNAME: add_product()
DESCRIPTION:This function  is used to add product.

 *********************************************************************************/

int supplier::add_product()
{
	int id=0;
	if(prod.empty()) //Checking if product list is empty or not
	{
		id=9000;
	}
	for(product p:prod) //Iterating through the product list.
	{
		if(id<p.get_product_id())
		{
			id=p.get_product_id();
		}
	}
	if(sup.empty()) //Checking if supplier list is empty.
	{
		cout<<"\nNo Supplier so product cannot be supplied!!!\n\n";
		return EXIT_FAILURE;
	}
	id+=1;
	product p1;
	char temp[25];
	p1.set_product_id(id);
	cout<<endl<<"Enter Details of Product"<<endl;
	cout<<"---------------------------------------"<<endl;	
	while(1)
	{
		cout<<"Enter Product Name: ";
		cin>>temp; 
		if(validations::check_name(temp)) //Taking product name as input and validating it.
		{
			continue;
		}
			p1.set_product_name(temp);
			break;
	}
	while(1)
	{
		cout<<"Enter No of units: ";
		cin>>temp;
		if(validations::check_digit(temp)) //Taking unit as input and validating it.
		{
			cout<<"Units should be digits only!!!\n";
			continue;
		}
		p1.set_no_of_units(stoi(temp));
		if(p1.get_no_of_units()<10)
		{
			cout<<"Units should not be less than 10\n";
			continue;
		}
		break;
	}
	while(1)
	{
		cout<<"Enter Cost of each item: ";
		cin>>temp;
		if(validations::check_digit(temp)) //Taking cost as input and validating it.
		{
			cout<<"Cost should be digit only\n";
			continue;
		}
		p1.set_cost(stoi(temp));
		if(p1.get_cost()<500)
		{		
			cout<<"Cost cannot be less than RS.500!!!\n";
			continue;
		}
		else
		{
			break;
		}
	}
	p1.set_sup_id(this->supplier_id);
	p1.set_units_sold(0);
	prod.push_back(p1); //Inserting product details into the product list.
	cout<<"\nProduct Added Successfully!!!"<<"\nProduct Id is "<<p1.get_product_id()<<endl<<endl<<endl;
	return EXIT_SUCCESS;
}


/**********************************************************************************


FUNCTIONNAME: get_supplier_id()
DESCRIPTION:This function  is used to get supplier id.

 *********************************************************************************/

int supplier::get_supplier_id()
{
	return this->supplier_id;
}


/**********************************************************************************


FUNCTIONNAME: get_supplier_name()
DESCRIPTION:This function  is used to get supplier name.

 *********************************************************************************/
char* supplier::get_supplier_name()
{
	return this->supplier_name;
}



/**********************************************************************************


FUNCTIONNAME: get_supplier_address()
DESCRIPTION:This function  is used to get supplier address.

 *********************************************************************************/
char* supplier::get_supplier_address()
{
	return this->supplier_address;
}

/**********************************************************************************


FUNCTIONNAME: get_mobile_no()
DESCRIPTION:This function  is used to get mobile number.

 *********************************************************************************/
long int supplier::get_mobile_no()
{
	return this->mobile_no;
}


/**********************************************************************************


FUNCTIONNAME: view_supplier()
DESCRIPTION:This function  is used to view supplier details.

 *********************************************************************************/
int supplier::view_supplier()
{
	cout<<endl<<"Showing  Details of Supplier"<<endl;
	cout<<"---------------------------------------"<<endl;	
	cout<<"\tSupplier Id: "<<supplier_id<<endl;
	cout<<"\tSupplier Name: "<<supplier_name<<endl;
	cout<<"\tSupplier Address: "<<supplier_address<<endl;
	cout<<"\tSupplier Mobile: "<<mobile_no<<endl<<endl;
	return EXIT_SUCCESS;
}


/**********************************************************************************


FUNCTIONNAME: edit_supplier_details()
DESCRIPTION:This function  is used to edit the supplier details.

 *********************************************************************************/

int supplier::edit_supplier_details()
{

	cout<<endl<<"Enter Details for Editing Supplier"<<endl;
	cout<<"---------------------------------------"<<endl;	
	int count=0;
	while(1)
	{
		cout<<"Enter Supplier Name: ";
		if(count==0)
		{
			cin.ignore(1,'\n');
			count++;
		}
		else
		{
			cin.ignore(0,'\n');
		}
		cin.getline(temp,40);
		if(validations::check_name(temp)) //Taking supplier name as input and validating it.
		{
			continue;
		}
			strcpy(this->supplier_name,temp);
			break;
	}



	while(1)
	{
		cout<<"Enter Supplier address: ";
		cin.ignore(0,'\n');
		cin.getline(temp,40); //Taking supplier address as input and validating it.
		if(validations::check_address(temp))//Taking supplier address as input and validating it.
		{
			continue;
		}
		strcpy(this->supplier_address,temp);
		break;
	}
	while(1)
	{
		cout<<"Enter Supplier Mobile number: ";
		cin>>temp;
		if(validations::check_mobile_number(temp)) //Taking supplier mobile number as input and validating it.
		{
			continue;
		}
			this->mobile_no=stol(temp);
			break;
	}
	cout<<endl<<"Details editted Successfully!!!\n\n";
	return EXIT_SUCCESS;
}


/**********************************************************************************


FUNCTIONNAME: edit_product()
DESCRIPTION:This function  is used to edit product..

 *********************************************************************************/
int supplier::edit_product()
{

	int id;
	cout<<endl<<"Enter Details for Editing Product"<<endl;
	cout<<"---------------------------------------"<<endl;	
	while(1)
	{
		cout<<"Enter the Product Id to edit: ";
		cin>>temp;
		if(validations::check_digit(temp)) //Taking product id as input and validating it.
		{
			cout<<"Product Id should be digits only\n";
			continue;
		}
		else
		{
			id=stoi(temp);
			break;
		}
	}

	if(prod.empty()) //Checking if product list is empty or not.
	{
		cout<<"\nProduct List not exist!!!\n\n";
		return EXIT_FAILURE;
	}
	int flag=0;
	list<product>::iterator it=prod.begin();
	for(;it!=prod.end();it++)
	{
		if(it->get_product_id()==id && it->get_sup_id())
		{
			it->edit_product_details(); //Calling edit product details function.
			flag=1;
			break;
		}
	} 
	if(flag==1)
	{
		cout<<"Product edited successfully!!!\n\n";
	}
	else
	{
		cout<<"Product with "<<id<<" does not exist or not supplied by you!!!\n\n";
	}
	return EXIT_SUCCESS;
}


/**********************************************************************************


FUNCTIONNAME: products_supplied()
DESCRIPTION:This function  is used to display the product supplied by the supplier.

 *********************************************************************************/

int supplier::products_supplied()
{
	if(prod.empty()) //Checking if products supplied is empty or not.
	{
		cout<<"Product list is empty\n\n";
		return EXIT_FAILURE;
	}
	int flag=0;
	int count=1;
	list<product>::iterator it=prod.begin();
	for(;it!=prod.end();it++)
	{
		if(it->get_sup_id()==this->supplier_id)
		{
			flag=1;
			if(count==1)
			{
				cout<<"		Products Supplied\n";
				cout<<"----------------------------------------------------\n";
				cout<<"Id        Name     Units   Price  Supplied_by\n";
				cout<<"----------------------------------------------------\n";
				count=0;
			}
			it->view_product(); //Calling view product function.
		}
	}
	if(flag==0)
	{
		cout<<endl<<"No products supplied by you!!!\n\n";
	}
	return EXIT_SUCCESS;
}


/**********************************************************************************


FUNCTIONNAME: get_product_id()
DESCRIPTION:This function  is used to get product id.

 *********************************************************************************/


int product::get_product_id()
{
	return this->product_id;
}


/**********************************************************************************


FUNCTIONNAME: get_product_name()
DESCRIPTION:This function  is used to get product name..

 *********************************************************************************/
char* product::get_product_name()
{
	return this->product_name;
}

/**********************************************************************************


FUNCTIONNAME: get_no__of_units()
DESCRIPTION:This function  is used to get number of units of products.

 *********************************************************************************/
int product::get_no_of_units()
{
	return this->no_of_units;
}


/**********************************************************************************


FUNCTIONNAME: get_cost()
DESCRIPTION:This function  is used to get the cost of the product.

 *********************************************************************************/
int product::get_cost()
{
	return this->cost;
}

/**********************************************************************************


FUNCTIONNAME: get_units_sold()
DESCRIPTION:This function  is used to get the units of product that has being sold

 *********************************************************************************/
int product::get_units_sold()
{
	return this->units_sold;
}

/**********************************************************************************


FUNCTIONNAME: set_no_of_units()
DESCRIPTION:This function  is used to set  the number of units.

 *********************************************************************************/
void product::set_no_of_units(int no_of_units)
{
	this->no_of_units=no_of_units;
}
/**********************************************************************************


FUNCTIONNAME: set_no_of_units()
DESCRIPTION:This function  is used to set  the number of units.

 *********************************************************************************/
void product::set_product_id(int product_id)
{
	this->product_id=product_id;
}
/**********************************************************************************


FUNCTIONNAME: set_units_sold()
DESCRIPTION:This function  is used to set the units sold of the product. 

 *********************************************************************************/
void product::set_units_sold(int units_sold)
{
	this->units_sold+=units_sold;
}

/**********************************************************************************


FUNCTIONNAME: view_product()
DESCRIPTION:This function  is used to display the products.

 *********************************************************************************/
int product::view_product()
{  
	cout<<this->product_id<<" "<<setw(12)<<this->product_name<<" "<<setw(5)<<this->no_of_units<<" "<<setw(7)<<this->cost<<" "<<setw(4)<<this->sup_id<<endl;
	return EXIT_SUCCESS;
}


/**********************************************************************************


FUNCTIONNAME: get_sup_id()
DESCRIPTION:This function  is used to get the supplier id.

 *********************************************************************************/
int product::get_sup_id()
{
	return this->sup_id;
}

void product::set_sup_id(int sup_id)
{
	this->sup_id=sup_id;
}

void product::set_cost(int cost)
{
	this->cost=cost;
}
/**********************************************************************************


FUNCTIONNAME: edit_product_details()
DESCRIPTION:This function  is used to edit the product details.

 *********************************************************************************/


int product::edit_product_details()
{

	char temp[25];
	cout<<endl<<"Enter Details for Editing Product"<<endl;
	cout<<"---------------------------------------"<<endl;	
	while(1)
	{
		cout<<"Enter Product Name: ";
		cin>>temp;
		if(validations::check_name(temp)) //Taking product name as input and validating it.
		{
			continue;
		}
			strcpy(this->product_name,temp);
			break;
	}
	while(1)
	{
		cout<<"Enter Cost of each item: ";
		cin>>temp;
		if(validations::check_digit(temp)) //Taking cost as input and validating it.
		{
			cout<<"Cost should be in digits only!!!\n";
			continue;
		}
		this->cost=stoi(temp);
		if(cost<500)
		{		
			cout<<"Cost cannot be less than RS.500!!!\n";
			continue;
		}
		else
		{
			break;
		}
	}
	return EXIT_SUCCESS;
}


/**********************************************************************************


FUNCTIONNAME: view_product_list()
DESCRIPTION:This function  is used to display the product list.

 *********************************************************************************/

int Admin::view_product_list()
{
	if(prod.empty()) //Checking if product list is empty.
	{
		cout<<"\nProduct list is empty!!!\n\n";
		return EXIT_FAILURE;
	}
	cout<<"\n----------Viewing Product List-----------------\n";
	cout<<"ID       Name     Units     Cost     Supplied_By\n";
	cout<<"-------------------------------------------------"<<endl;
	for(list<product>::iterator it=prod.begin();it!=prod.end();it++)
	{
		it->view_product(); //Calling view product function.
	}
	return EXIT_SUCCESS;
}


/**********************************************************************************


FUNCTIONNAME: view_customer_list()
DESCRIPTION:This function  is used to display the customer list.

 *********************************************************************************/

int Admin::view_customer_list()
{
	if(cust.empty()) //Checking if customer list is empty
	{
		cout<<"\nCustomer list is empty!!!\n\n";
		return EXIT_FAILURE;
	}
	cout<<"\n----------Viewing Customer List-----------------\n";
	cout<<"ID       Name       Mobile        Address\n";
	cout<<"--------------------------------------------------"<<endl;
	for(list<customer>::iterator it=cust.begin();it!=cust.end();it++)
	{
		cout<<it->get_customer_id()<<" "<<setw(12)<<it->get_customer_name()<<" "<<setw(12)<<it->get_cmobile_no()<<" "<<setw(15)<<it->get_customer_address()<<endl;
	}
	return EXIT_SUCCESS;
}


/**********************************************************************************


FUNCTIONNAME: view_transactions()
DESCRIPTION:This function  is used to display the transaction.

 *********************************************************************************/
int Admin::view_transactions()
{
	if(trans.empty()) //Checking if transaction list is empty or not.
	{
		cout<<"\nNo Previous Transactions Available!!!\n\n";
		return EXIT_FAILURE;
	}
	cout<<"\n---------------------------------------Viewing Transactions-----------------------------------------\n";
	cout<<"Id    Cust_ID      Prod_1       Prod_2       Prod_3     Total_amount     Discount    Amount_Paid"<<endl;
	cout<<"------------------------------------------------------------------------------------------------------"<<endl;
	for(list<transaction>::iterator it=trans.begin();it!=trans.end();it++)
	{
		it->view_transaction(); //Calling view transaction function.
	}
	return EXIT_SUCCESS;
}


/**********************************************************************************


FUNCTIONNAME: view_supplier_list()
DESCRIPTION:This function  is used to display the supplier list.

 *********************************************************************************/
int Admin::view_supplier_list()
{
	if(sup.empty()) //Checking if supplier list is empty or not.
	{
		cout<<"\nSupplier list is empty!!!\n\n";
		return EXIT_FAILURE;
	}
	cout<<"\n---------Viewing Supplier-----------------\n";
	cout<<"ID      Name       Mobile        Address\n";
	cout<<"--------------------------------------------"<<endl;
	for(list<supplier>::iterator it=sup.begin();it!=sup.end();it++)
	{
		cout<<it->get_supplier_id()<<" "<<setw(12)<<it->get_supplier_name()<<" "<<setw(12)<<it->get_mobile_no()<<" "<<setw(15)<<it->get_supplier_address()<<endl;
	}
	return EXIT_SUCCESS;
}

/**********************************************************************************


FUNCTIONNAME: remove_supplier()
DESCRIPTION:This function  is used to remove the supplier.

 *********************************************************************************/

int Admin::remove_supplier()
{
	int id; 
	if(sup.empty()) //Checking if remove supplier list is empty or not.
	{
		cout<<"\nSupplier List not exist!!!\n\n";
		return EXIT_FAILURE;
	}

	while(1)
	{
		cout<<"Enter the Supplier Id to remove: ";
		cin>>temp;
		if(validations::check_digit(temp)) //Taking supplier id as input and validating it.
		{
			cout<<"Supplier Id should be digits only\n";
			continue;
		}
		else
		{
			id=stoi(temp);
			break;
		}
	}


	int flag=0;
	std::list<supplier>::iterator it=sup.begin();
	for(;it!=sup.end();it++)
	{
		if(it->get_supplier_id()==id)
		{
			it=sup.erase(it); //If supplier id matches , then deleting it from supplier list.
			flag=1;
			break;
		} 
	}
	if(flag==1)
	{
		cout<<"\nSupplier removed successfully!!!\n\n";
	}
	else
	{
		cout<<"\nSupplier with "<<id<<" does not exist!!!\n\n";
	}
	return EXIT_SUCCESS;
}


/**********************************************************************************


FUNCTIONNAME: remove_customer()
DESCRIPTION:This function  is used to remove the customer.

 *********************************************************************************/

int Admin::remove_customer()
{

	int id;
	if(cust.empty()) //Checking if customer list is empty or not.
	{
		cout<<"\nNo Customer Registered!!!\n\n";
		return EXIT_FAILURE;
	}
	while(1)
	{
		cout<<"\nEnter the Customer Id to remove: ";
		cin>>temp;
		if(validations::check_digit(temp)) //Taking customer id as input and validating it.
		{
			cout<<"Customer Id should be digits only\n";
			continue;
		}
		else
		{
			id=stoi(temp);
			break;
		}
	}

	int flag=0;
	list<customer>::iterator it=cust.begin();
	for(;it!=cust.end();it++)
	{
		if(it->get_customer_id()==id)
		{
			it=cust.erase(it);
			flag=1;
			break;
		}
	} 
	if(flag==1)
	{
		cout<<"\nCustomer removed successfully!!!\n\n";
	}
	else
	{
		cout<<"\nCustomer with "<<id<<" does not exist!!!\n\n";
	}
	return EXIT_SUCCESS;

}

void product::set_product_name(char* product_name)
{
	strcpy(this->product_name,product_name);
}
/**********************************************************************************


FUNCTIONNAME: remove_product()
DESCRIPTION:This function  is used to remove product.

 *********************************************************************************/

int Admin::remove_product()
{

	int id;
	if(prod.empty()) //checking remove product list is empty or not.
	{
		cout<<"\nProduct List not exist!!!\n\n";
		return EXIT_FAILURE;
	}
	while(1)
	{
		cout<<"\nEnter the Product Id to remove: ";
		cin>>temp;
		if(validations::check_digit(temp)) //Taking product id as input and validating it.
		{
			cout<<"Product Id should be digits only\n";
			continue;
		}
		else
		{
			id=stoi(temp);
			break;
		}
	}
	int flag=0;
	list<product>::iterator it=prod.begin();
	for(;it!=prod.end();it++)
	{
		if(it->get_product_id()==id)
		{
			it=prod.erase(it);
			flag=1;
			break;
		}
	} 
	if(flag==1)
	{
		cout<<"\nProduct removed successfully!!!\n\n";
	}
	else
	{
		cout<<"\nProduct with "<<id<<" does not exist!!!\n\n";
	}
	return EXIT_SUCCESS;

}


/**********************************************************************************


FUNCTIONNAME: add_product()
DESCRIPTION:This function  is used to add product in the list.

 *********************************************************************************/
int Admin::adding_product()
{
	int id=0;
	if(prod.empty()) //Checking if product list is empty or not.
	{
		id=9000;
	}
	for(product p:prod)
	{
		if(id<p.get_product_id())
		{
			id=p.get_product_id();
		}
	}
	if(sup.empty()) //Checking if supplier list is empty or not. 
	{
		cout<<"\nNo Supplier present in the list, so product cannot be supplied!!!\n\n";
		return EXIT_FAILURE;
	}
	id+=1;
	product p1;
	p1.set_product_id(id);
	while(1)
	{
		cout<<"Enter Product Name: ";
		cin>>temp;
		if(validations::check_name(temp)) //Taking product name as input and validating it.
		{
			continue;
		}
			p1.set_product_name(temp);
			break;
	}

	while(1)
	{
		cout<<"Enter No of units: ";
		cin>>temp;
		if(validations::check_digit(temp)) //Taking units as input and validating it.
		{
			cout<<"Units should not be less than 10\n";
			continue;
		}
		p1.set_no_of_units(stoi(temp));
		if(p1.get_no_of_units()<10)
		{
			cout<<"Units should not be less than 10\n";
			continue;
		}
		break;
	}
	while(1)
	{
		cout<<"Enter Cost of each item: ";
		cin>>temp;
		if(validations::check_digit(temp)) //Taking cost as input and validating it.
		{
			cout<<"Units should not be less than 10\n";
			continue;
		}
		p1.set_cost(stoi(temp));
		if(p1.get_cost()<500)
		{		
			cout<<"Cost cannot be less than RS.500!!!\n";
			continue;
		}
		else
		{
			break;
		}
	}

	int max=0;
	for(supplier s:sup) //Iterating through the supplier list.
	{
		if(max<s.get_supplier_id())
		{
			max=s.get_supplier_id();
		}
	}
	int min=max;
	for(supplier s:sup) //Iterating through the supplier list.
	{
		if(min>s.get_supplier_id())
		{
			min=s.get_supplier_id();
		}
	}
	while(1)
	{
		cout<<"Enter Supplier Id: ";
		cin>>temp;
		if(validations::check_digit(temp)) //Taking supplier id as input and validating it.
		{
			cout<<"Supplier should be digits only\n";
			continue;
		}
		p1.set_sup_id(stoi(temp));
		if( (p1.get_sup_id()<min) || (p1.get_sup_id()>max))
		{		
			cout<<"Supplier Id should be between "<<min<<"-"<<max<<" !!!\n";
			continue;
		}
		else
		{
			break;

		}
	}
	p1.set_units_sold(0);
	prod.push_back(p1); //Inserting product details into product list.
	cout<<"\nProduct Added Successfully!!!"<<"\nProduct Id is "<<p1.get_product_id()<<endl<<endl<<endl;
	return EXIT_SUCCESS;

}


/**********************************************************************************


FUNCTIONNAME: edit_supplier()
DESCRIPTION:This function  is used to edit the supplier details

 *********************************************************************************/

int Admin::edit_supplier()
{

	int id;
	if(sup.empty()) //Checking if supplier list is empty or not.
	{
		cout<<"\nSupplier List not exist!!!\n\n";
		return EXIT_FAILURE;
	}
	while(1)
	{
		cout<<"\nEnter the Supplier Id to edit: ";
		cin>>temp;
		if(validations::check_digit(temp)) //Taking supplier id as input and validating it.
		{
			cout<<"Supplier Id should be digits only\n";
			continue;
		}
		else
		{
			id=stoi(temp);
			break;
		}
	}
	int flag=0;
	list<supplier>::iterator it=sup.begin();
	for(;it!=sup.end();it++)
	{
		if(it->get_supplier_id()==id)
		{
			it->view_supplier(); //Calling view supplier 
			it->edit_supplier_details();//Calling edit supplier details.
			flag=1;
			break;
		}
	} 
	if(flag==0)
	{
		cout<<"\nSupplier with "<<id<<" does not exist!!!\n\n";
	}
	return EXIT_SUCCESS;

}

/**********************************************************************************


FUNCTIONNAME: edit_customer()
DESCRIPTION:This function  is used to edit the details of the customer.

 *********************************************************************************/

int Admin::edit_customer()
{

	int id;
	if(cust.empty()) //Checking if customer list is empty or not.
	{
		cout<<"\nCustomer List not exist!!!\n\n";
		return EXIT_FAILURE;
	}
	while(1)
	{
		cout<<"\nEnter the Customer Id to edit: ";
		cin>>temp;
		if(validations::check_digit(temp)) //Taking customer id as input and validating it.
		{
			cout<<"Customer Id should be digits only\n";
			continue;
		}
		else
		{
			id=stoi(temp);
			break;
		}
	}
	int flag=0;
	list<customer>::iterator it=cust.begin();
	for(;it!=cust.end();it++)
	{
		if(it->get_customer_id()==id)
		{
			it->view_customer();
			it->edit_customer_details();
			flag=1;
			break;
		}
	} 
	if(flag==0)
	{
		cout<<"Customer with "<<id<<" does not exist!!!\n\n";
	}
	return EXIT_SUCCESS;
}


/**********************************************************************************


FUNCTIONNAME: edit_product()
DESCRIPTION:This function  is used to edit the details of the product.

 *********************************************************************************/
int Admin::editing_product()
{

	int id;
	if(prod.empty()) //Checking if product list is empty or not.
	{
		cout<<"\nProduct List not exist!!!\n\n";
		return EXIT_FAILURE;
	}
	while(1)
	{
		cout<<"\nEnter the Product Id to edit: ";
		cin>>temp;
		if(validations::check_digit(temp)) //Taking product id as input and validating it.
		{
			cout<<"Product Id should be digits only\n";
			continue;
		}
		else
		{
			id=stoi(temp);
			break;
		}
	}
	int flag=0;
	list<product>::iterator it=prod.begin();
	for(;it!=prod.end();it++)
	{
		if(it->get_product_id()==id)
		{
			it->edit_product_details();
			flag=1;
			break;
		}
	} 
	if(flag==1)
	{
		cout<<"Product edited successfully!!!\n\n";
	}
	else
	{
		cout<<"Product with "<<id<<" does not exist!!!\n\n";
	}
	return EXIT_SUCCESS;
}


/**********************************************************************************


FUNCTIONNAME: order_stock()
DESCRIPTION:This function  is used to order the stock of the product.

 *********************************************************************************/

int Admin::order_stock()
{
	if(prod.empty()) //Checking if product list is empty or  not.
	{
		cout<<"\nProduct List not exist!!!\n\n";
		return EXIT_FAILURE;
	}
	int flag=0;
	int count=0;
	int no_of_units=0;
	list<product>::iterator it=prod.begin();
	for(;it!=prod.end();it++)
	{
		if(it->get_no_of_units()==0)
		{
			while(1)
			{
				cout<<"\nEnter no of units for Product Id: "<<it->get_product_id()<<", Name: "<<it->get_product_name()<<": ";
				cin>>temp;
				if(validations::check_digit(temp)) //Taking number of units as input and validating it.
				{
					cout<<"No of Units should be digits only\n";
					continue;
				}
				else
				{
					count++;
					no_of_units=stoi(temp);
					break;
				}
			}
			it->set_no_of_units(no_of_units);
			flag=1;
		}
	} 
	if(flag==1)
	{
		cout<<endl<<"\n"<<count<<" Product Stocked Successfully!!!\n\n";
	}
	else
	{
		cout<<"\nAll Products are in stock already!!!\n\n";
	}
	return EXIT_SUCCESS;

}


/**********************************************************************************


FUNCTIONNAME: stock_report()
DESCRIPTION:This function  is used to display the stock report.

 *********************************************************************************/
int Admin::stock_report()
{
	if(prod.empty()) //Checking if product list is empty or not.
	{
		cout<<"\nProduct List not exist!!!\n\n";
		return EXIT_FAILURE;
	}
	list<product>::iterator it=prod.begin();
	cout<<"                      STOCK REPORT"<<endl;
	cout<<"---------------------------------------------------------"<<endl;
	cout<<"Id      Name       Units  Units_Sold     Price"<<endl;
	cout<<"---------------------------------------------------------"<<endl;
	for(;it!=prod.end();it++)
	{
		cout<<it->get_product_id()<<" "<<setw(12)<<it->get_product_name()<<" "<<setw(6)<<it->get_no_of_units()<<" "<<setw(6)<<it->get_units_sold()<<"    "<<setw(7)<<it->get_cost()<<endl;
	} 
	return EXIT_SUCCESS;
}


/**********************************************************************************


FUNCTIONNAME: top_3_product()
DESCRIPTION:This function  is used to display the top 3 products.

 *********************************************************************************/
int Admin::top_three_product()
{
	if(prod.empty()) //Checking if product list is empty or not.
	{
		cout<<"\nNo Product Sold till now!!!\n\n";
		return EXIT_FAILURE;
	}
	if(trans.empty()) //Checking if product list is empty or not.
	{
		cout<<"\nNo Product Sold till now!!!\n\n";
		return EXIT_FAILURE;
	}
	int flag=0;
	int count=0;
	list<product>::iterator it=prod.begin();
	cout<<"           Top Three Selling Products"<<endl;
	cout<<"----------------------------------------------"<<endl;
	cout<<"Id     Name    Units_Sold    Price"<<endl;
	cout<<"----------------------------------------------"<<endl;
	prod.sort([](product &p1 ,product &p2){ return p1.get_units_sold()>p2.get_units_sold();});	
	for(int i=0;i!=3&&it!=prod.end();i++,it++)
	{
		if(it->get_units_sold()>0)
		{
			cout<<it->get_product_id()<<" "<<setw(9)<<it->get_product_name()<<"  "<<setw(6)<<it->get_units_sold()<<" "<<setw(7)<<it->get_cost()<<endl;
		}
	}
	prod.sort([](product &p1 ,product &p2){ return p1.get_product_id()<p2.get_product_id();});	
	return EXIT_SUCCESS;

}
#endif

