# include "iGraphics.h"
#include<string.h>
#include<stdio.h>

struct items
{
	char item[20];
	float price;
	int qty;
};

struct orders
{
	char customer[50];
	char date[50];

	int numOfItems;
	float paid;
	float due;
	struct items itm[50];
};
struct customers
{
	char customer[50];
	char phone_no[12];
	float due;
	float paid;
	char date[50];
};
//main variables
struct customers buyer;
struct orders ord;
int opt, n;

struct customers customer;
struct customers record;
struct orders order;

char saveBill = 'y', contFlag = 'y';
float total = 0;
float paid;

char name[50];
FILE *fp;
FILE *fp1;


//for home page
double left = 300, bottom = 700 - 150, dx = 300, dy = 50, x = 1000, y = 800;
int page = -1;
int rx1 = x*0.35;
int ry1 = y*0.80;

//for page 1 text input
char str[100], str2[100];
int len;
int mode;
int count; // for textbox input number

//for generate_bill of page 1

int position; // position in itm array
int items_bought;

int toggle_generate = 0;
int color = 0;

//for page 3
// found is initialized to values other than 0 or 1 because of conditions in functions
int found = 3;
int search_called = 0;

// for page 4
// for customer records
float buyer_paid = 0;
float buyer_due = 0;

// for searching reports

int num_reports = 0;  // number of orders in file
float daily_sold = 0; // variable for sum of prices
int quantity = 0;	  // total items sold that day
float daily_paid = 0; // total paid by buyers that day
float daily_due = 0;  // total of dues that day


// textbox
void drawTextBox(int x, int y)
{
	iSetColor(150, 150, 150);
	iRectangle(x, y, 400, 30);

}
void textbox(int x1, int y1, char str[])
{
	drawTextBox(x1, y1);
	if (mode == 1)
	{
		iSetColor(255, 255, 0);
		iRectangle(x1, y1, 400, 30);
		iSetColor(255, 255, 0);
		iText(x1, y1 + 30 * .5, str);
	}

	
}

/*
function iDraw() is called again and again by the system.

*/
//bill functions
void BillHeader(char name[50], char date[30])
{
	printf("\n____________ HEADER __________\n\n");
	iText(rx1 + 150, ry1 + 50, "BILL", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(rx1, ry1 - 10, " -----------------", GLUT_BITMAP_HELVETICA_18);
	iText(rx1, ry1 - 20 * 1.5, "DATE:", GLUT_BITMAP_HELVETICA_18);
	iText(rx1 + 75, ry1 - 20 * 1.5, date, GLUT_BITMAP_HELVETICA_18);
	iText(rx1, ry1 - 30 * 1.5, "Invoice to:", GLUT_BITMAP_HELVETICA_18);
	iText(rx1 + 75 * 1.5, ry1 - 30 * 1.5, name, GLUT_BITMAP_HELVETICA_18);
	iText(rx1, ry1 - 40 * 1.5, "---------------------------------------", GLUT_BITMAP_HELVETICA_18);
	iText(rx1, ry1 - 50 * 1.5, "Items", GLUT_BITMAP_HELVETICA_18);
	iText(rx1 + 80 * 1.5, ry1 - 50 * 1.5, "Qty", GLUT_BITMAP_HELVETICA_18);
	iText(rx1 + 80 * 4.5, ry1 - 50 * 1.5, "Total", GLUT_BITMAP_HELVETICA_18);
	iText(rx1 + 80 * 3, ry1 - 50 * 1.5, "Unit Price", GLUT_BITMAP_HELVETICA_18);
	//iText(rx1, ry1 - 80*1.5, "---------------------------------------", GLUT_BITMAP_HELVETICA_18);

}
void BillBody(char item[30], int qty, float price)
{
	char str_qty[100];
	char str_price[100];
	char str_uprice[100];

	sprintf(str_qty, "%d", qty);
	sprintf(str_uprice, "%.2f",price);
	sprintf(str_price, "%.2f", qty*price);


	iText(rx1, ry1 - 60 * 1.5, item, GLUT_BITMAP_HELVETICA_18);
	iText(rx1 + 80 * 1.5, ry1 - 60 * 1.5, str_qty, GLUT_BITMAP_HELVETICA_18);
	iText(rx1 + 80 * 4.5, ry1 - 60 * 1.5, str_price, GLUT_BITMAP_HELVETICA_18);
	iText(rx1 + 80 * 3, ry1 - 60 * 1.5, str_uprice, GLUT_BITMAP_HELVETICA_18);
	printf("\n%s\t\t", item);
	printf("%d\t\t", qty);
	printf("%.2f\t\t", qty * price);
	printf("\n");
}
void BillFooter(float total, float paid)
{
	


	char str_total[100];
	char str_bepaid[100];
	char str_due[100];
	char str_paid[100];

	sprintf(str_paid, "%f", paid);
	sprintf(str_total, "%f", total);
	sprintf(str_due, "%f", total - paid);
	sprintf(str_bepaid, "%f", paid - total);
	iText(rx1, ry1 - 255, "---------------------------------------", GLUT_BITMAP_HELVETICA_18);
	iText(rx1 + 40 * 2, ry1 - 90 * 3, "-------", GLUT_BITMAP_HELVETICA_18);
	iText(rx1, ry1 - 90 * 3, "Net Total", GLUT_BITMAP_HELVETICA_18);
	iText(rx1 + 40 * 6, ry1 - 90 * 3, str_total, GLUT_BITMAP_HELVETICA_18);
	iText(rx1, ry1 - 90 * 3 - 30, "Paid", GLUT_BITMAP_HELVETICA_18);
	iText(rx1 + 40 * 6, ry1 - 90 * 3 - 30, str_paid, GLUT_BITMAP_HELVETICA_18);
	iText(rx1 + 40 * 2, ry1 - 90 * 3 - 30, "-------", GLUT_BITMAP_HELVETICA_18);
	//iText(rx1 , ry1 - 110, "---------------------------------------", GLUT_BITMAP_HELVETICA_18);
	iText(rx1, ry1 - 315, "---------------------------------------", GLUT_BITMAP_HELVETICA_18);
	if (paid >= total)
	{
		iText(rx1, ry1 - 90 * 3 - 60, "Amount to be returned :", GLUT_BITMAP_HELVETICA_18);
		iText(rx1 + 40 * 6, ry1 - 90 * 3 - 60, str_bepaid, GLUT_BITMAP_HELVETICA_18);
	}
	else
	{
		iText(rx1, ry1 - 90 * 3 - 60, "Due Amount: ", GLUT_BITMAP_HELVETICA_18);

		iText(rx1 + 40 * 6, ry1 - 90 * 3 - 60, str_due, GLUT_BITMAP_HELVETICA_18);

	}
}


//customer
void customerrecord()
{

	fp1 = fopen("information.txt", "r");
	
	
	buyer_paid = 0;
	buyer_due = 0;
	while (fread(&record, sizeof(struct customers), 1, fp1))
	{
		buyer_paid += record.paid;
		buyer_due += record.due;

		found = 1;
	}

	printf("\n\t\t\t\t Total paid     : %f", buyer_paid);

	if (buyer_due > 0)
	{
		printf("\n\t\t\t\t Due    : %f", buyer_due);
	}
	else
	{
		printf("\n\t\t\t\t\tNo Due\n");
	}

	printf("\n\t\t\t\t ________________________________\n");

	if (found == 3)
	{
		printf("\n\t\t\tRecords not found\n");
	}

	fclose(fp1);
}

void generate_bills()
{
	

	// input 
	ord.due = total - ord.paid;
	buyer.paid = ord.paid;
	buyer.due = ord.due;


	// saving bill
	fp = fopen("Bill.txt", "a+");

	fwrite(&ord, sizeof(struct orders), 1, fp);

	fclose(fp);

	//saving customer record
	fp1 = fopen("information.txt", "a+");
	fwrite(&buyer, sizeof(struct customers), 1, fp1);

	fclose(fp1);

}

void Search_bill()

{
	//input
	fp = fopen("Bill.txt", "r");

	float tot = 0;
	
	while (fread(&order, sizeof(struct orders), 1, fp))
	{
		if (!strcmp(order.customer, name))
		{
			for (int i = 0; i < order.numOfItems; i++)
			{
				
				tot += order.itm[i].qty * order.itm[i].price;
			}
			found = 1;
			break;
		}
		else
		{
			found = 0;
		}
	}


	total = tot;

	fclose(fp);

}

void searchcustomer()
{

	fp = fopen("information.txt", "r");



	while (fread(&customer, sizeof(struct customers), 1, fp))
	{
		if (strcmp(customer.customer, name) == 0)
		{
			found = 1;

			// converting to string
			char str_total[100];
			char str_bpaid[100];
			char str_bdue[100];
			sprintf(str_bpaid, "%.2f", total);
			sprintf(str_bdue, "%.2f", customer.due);

			

			break;
		}
		else
		{
			found = 0;
		}

	}


	fclose(fp);


}

void daily_report()
{

	fp = fopen("Bill.txt", "r");

	

	while (fread(&order, sizeof(struct orders), 1, fp))
	{

		if (strcmp(order.date,__DATE__) == 0)
		{
			num_reports++;
			quantity += order.numOfItems;
			daily_paid += order.paid;
			daily_due += order.due;
			found = 1;

			
			for (int i = 0; i < order.numOfItems; i++)
			{
				daily_sold += order.itm[i].qty * order.itm[i].price;

				
			}

			
		}


	}

	

	fclose(fp);


}

void show_bills()
{
     daily_sold = 0;
	fp = fopen("Bill.txt", "r");

	
	while (fread(&order, sizeof(struct orders), 1, fp))
	{


		num_reports++;
		quantity += order.numOfItems;
		daily_paid += order.paid;
		daily_due += order.due;
		found = 1;

		for (int i = 0; i < order.numOfItems; i++)
		{
			daily_sold += order.itm[i].qty * order.itm[i].price;

			
		}

		

	}

	

	fclose(fp);


}
/*void changepaid()
{
	fp = fopen("information.txt", "r");

	//input

	while (fread(&customer, sizeof(struct customers), 1, fp))
	{
		if (strcmp(customer.customer, name) == 0)
		{
			found = 1;
			//in ikeyboard
			//in idraw
			if (found == 1)
			{
				iText(rx1, ry1 + 40, " Enter Paid Amount.", GLUT_BITMAP_TIMES_ROMAN_24);
			}
			// to check in console
			char str_total[100];
			char str_bpaid[100];
			char str_bdue[100];
			sprintf(str_bpaid, "%.2f", total);
			sprintf(str_bdue, "%.2f", customer.due);

			printf("\n\t\t\t\t Date           : %s", customer.date);
			printf("\n\t\t\t\t customer Name  : %s", customer.customer);
			printf("\n\t\t\t\t phone NO       : %s", customer.phone_no);
			printf("\n\t\t\t\t Paid   : %f", customer.paid);
			if (customer.due > 0)
			{
				printf("\n\t\t\t\t Due    : %f", customer.due);
			}
			else
			{
				printf(" No Due \n");
			}

			printf("\n\t\t\t\t ________________________________\n");

			break;
		}
		else
		{
			found = 0;
		}

}*/


void home_page()
{
	
	iSetColor(149, 33, 246);
	iRectangle(0, 0, x, y);
	iFilledRectangle(0, 0, x, y);
	int rx1 = x*0.40;
	int ry1 = y*0.50;
	iSetColor(255, 255, 0);
	iRectangle(rx1, ry1, dx, dy);
	iRectangle(rx1, ry1 + 80, dx, dy);
	iRectangle(rx1, ry1 + 160, dx, dy);
	iRectangle(rx1, ry1 + 240, dx, dy);
	iRectangle(rx1, ry1 - 80, dx, dy);
	iRectangle(rx1, ry1 - 160, dx, dy);
	iRectangle(rx1, ry1 - 240, dx, dy);
	iSetColor(255, 255, 0);
	//menu
	iText(rx1+40, ry1+325, "HAALKHATA", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(rx1 + 37, ry1 + 247, "1.Generate Bill", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(rx1 + 37, ry1 + 166, "2.Bill Statistics", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(rx1 + 37, ry1 + 87, "3.Search Bills", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(rx1 + 37, ry1 + 7, "4.Customers Records", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(rx1 + 37, ry1 - 73, "5.Search Customer", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(rx1 + 37, ry1 - 153, "6.Daily Report", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(rx1 + 37, ry1 - 233, "7.Exit", GLUT_BITMAP_TIMES_ROMAN_24);

}



void page_7()
{
	iSetColor(149, 33, 246);
	iRectangle(0, 0, x, y);
	iSetColor(255, 255, 0);
	iText(rx1 + 50, ry1, "Thanks for using haalkhata", GLUT_BITMAP_TIMES_ROMAN_24);
	exit(0);
}
void back_button()
{
	//iShowBMP(rx1+425, ry1 -425, "home1.bmp");
	iRectangle(rx1 + 420, ry1 - 435, 80, 35);
	iSetColor(149, 33, 246);
	iText(rx1 + 425, ry1 - 425, "Home", GLUT_BITMAP_TIMES_ROMAN_24);
	
}


void iDraw() {
	//place your drawing codes here
	iClear();
	iSetColor(20, 200, 200);

	//iRectangle( left, bottom, dx,  dy);
	if (page == -1)
	{
		iShowBMP(rx1-200, ry1-175, "haalkhata.bmp");
		iSetColor(149, 33, 246);
		iRectangle(0, 0, x, y);
		iText(rx1, ry1 - 500, "Press right arrow to go to menu.", GLUT_BITMAP_TIMES_ROMAN_24);


		
	}
	if (page == 0)
	{
		home_page();
	}
	if (page == 1)
	{
		iSetColor(149, 33, 246);
		iRectangle(0, 0, x, y);

		iRectangle(rx1 + 420, ry1, 80, 35);
		textbox(rx1, ry1, str);
		
		iText(rx1 + 425, ry1 + 10, "Enter", GLUT_BITMAP_TIMES_ROMAN_24);
		back_button();
		if (color == 1)
		{
			iSetColor(135, 206, 235);
			iRectangle(rx1 + 420, ry1, 80, 35);

		}
		iText(rx1-50, ry1 - 500, "Press enter to save and Click enter to go to next page.", GLUT_BITMAP_TIMES_ROMAN_24);

		if (count == 0)
		{
			
			iText(rx1, ry1+40, " Please enter the name of the customer.", GLUT_BITMAP_TIMES_ROMAN_24);
		}
		if (count == 1)
		{
			iText(rx1, ry1 +40, " Please enter the phone no of the customer.", GLUT_BITMAP_TIMES_ROMAN_24);
		}
		if (count == 2)
		{
			iText(rx1, ry1+ 40, " Please enter the number of items.", GLUT_BITMAP_TIMES_ROMAN_24);
		}

		if (count == 3)
		{
			iText(rx1, ry1+ 40, " Please enter the item.", GLUT_BITMAP_TIMES_ROMAN_24);
		}

		if (count == 4)
		{
			iText(rx1, ry1 + 40, " Please enter the quantity.", GLUT_BITMAP_TIMES_ROMAN_24);
		}
		if (count == 5)
		{
			iText(rx1, ry1 + 40, " Please enter the unit price.", GLUT_BITMAP_TIMES_ROMAN_24);
		}
		if (count == 6)
		{
			iText(rx1, ry1 + 40, " Enter Paid Amount.", GLUT_BITMAP_TIMES_ROMAN_24);
		}
		if (count == 7)
		{
			iSetColor(149, 33, 246);
			iRectangle(0, 0, x, y);
			iText(rx1 + 425, ry1 + 10, "Enter", GLUT_BITMAP_TIMES_ROMAN_24);
			iText(rx1, ry1 + 40, " Paid. Press enter.", GLUT_BITMAP_TIMES_ROMAN_24);
			iSetColor(0, 0, 0);
			iRectangle(rx1,ry1, 400, 30);

		}

		if (count == 8)
		{
			int ry1_store = ry1;
			iSetColor(0, 0, 0);
			iFilledRectangle(0, 0, x, y);
			iSetColor(149, 33, 246);

			BillHeader(ord.customer, ord.date);

			for (int i = 0; i < ord.numOfItems; i++)
			{
				BillBody(ord.itm[i].item, ord.itm[i].qty, ord.itm[i].price);
				ry1 -= 30;
			}

			BillFooter(total, ord.paid);
			ry1 = ry1_store;
			back_button();
			//iText(rx1, ry1 - 500, "Press left arrow to go to home page.", GLUT_BITMAP_TIMES_ROMAN_24);
		}

	}
	//page2
	if (page == 2)
	{

		iText(rx1-100,ry1, "=======TOTAL BILLS STATISTICS=======", GLUT_BITMAP_TIMES_ROMAN_24);

		if (found == 3)
		{
			iText(rx1 + 80, ry1-100, "Records not found", GLUT_BITMAP_TIMES_ROMAN_24);
		}

		if (found == 1)
		{
			char str_total[100];
			char str_paid[100];
			char str_due[100];
			char str_reports[100];

			sprintf(str_total, "%.2f", daily_sold);
			sprintf(str_paid, "%.2f", daily_paid);
			sprintf(str_due, "%.2f", daily_due);
			sprintf(str_reports, "%d", num_reports);



			iText(rx1 + 40, ry1 - 3 * 30, "Total orders:      ", GLUT_BITMAP_HELVETICA_18);
			iText(rx1 + 60 * 3, ry1 - 3* 30, str_reports, GLUT_BITMAP_HELVETICA_18);

			iText(rx1 + 40, ry1 - 4 * 30, "Total:", GLUT_BITMAP_HELVETICA_18);
			iText(rx1 + 60 * 3, ry1 - 4* 30, str_total, GLUT_BITMAP_HELVETICA_18);


			iText(rx1 + 40, ry1 - 5 * 30, "Paid:", GLUT_BITMAP_HELVETICA_18);
			iText(rx1 + 60 * 3, ry1 - 5 * 30, str_paid, GLUT_BITMAP_HELVETICA_18);

			if (daily_due > 0)
			{
				iText(rx1 + 40, ry1 - 6 * 30, "Due:", GLUT_BITMAP_HELVETICA_18);
				iText(rx1 + 60 * 3, ry1 - 6 * 30, str_due, GLUT_BITMAP_HELVETICA_18);
			}
			else
			{
				iText(rx1 + 80, ry1 - 7 * 30, "No Due", GLUT_BITMAP_HELVETICA_18);
			}
			iText(rx1, ry1 - 400, "________________________", GLUT_BITMAP_TIMES_ROMAN_24);
		}

		back_button();
	}

	// page3
	if (page == 3)
	{
		iSetColor(149, 33, 246);
		iRectangle(0, 0, x, y);

		if (search_called == 0)
		{
			iRectangle(rx1 + 420, ry1, 80, 35);
			textbox(rx1, ry1, str);
			iText(rx1, ry1 + 40, " Please enter the name of the customer.", GLUT_BITMAP_TIMES_ROMAN_24);
			iText(rx1 + 425, ry1 + 10, "Enter", GLUT_BITMAP_TIMES_ROMAN_24);
			iText(rx1 - 50, ry1 - 500, "Press enter to save and Click enter to go to next page.", GLUT_BITMAP_TIMES_ROMAN_24);
		}


		if (found == 0)
		{
			iText(rx1 - 10, ry1, "Sorry the bill does not exist for", GLUT_BITMAP_TIMES_ROMAN_24);
			iText(rx1 + 100 + 50 * 4, ry1, name, GLUT_BITMAP_TIMES_ROMAN_24);
			
		}

		if (found == 1)
		{
			int ry1_store = ry1;
			iSetColor(0, 0, 0);
			iFilledRectangle(0, 0, x, y);
			iSetColor(149, 33, 246);

			BillHeader(order.customer, order.date);

			for (int i = 0; i < order.numOfItems; i++)
			{
				BillBody(order.itm[i].item, order.itm[i].qty, order.itm[i].price);
				ry1 -= 30;
			}

			BillFooter(total, order.paid);
			ry1 = ry1_store;
			back_button();

			//iText(rx1, ry1 - 500, "Press left arrow to go to home page.", GLUT_BITMAP_TIMES_ROMAN_24);

		}
		back_button();



	}
	//page 4
	if (page == 4)
	{

		iText(rx1, ry1, "=======CUSTOMERS RECORD=======", GLUT_BITMAP_TIMES_ROMAN_24);


		if (found == 3)
		{
			iText(rx1 + 80, ry1-100, "Records not found", GLUT_BITMAP_TIMES_ROMAN_24);
		}

		if (found == 1)
		{
			char str_total[100];
			char str_bpaid[100];
			char str_bdue[100];
			sprintf(str_bpaid, "%.2f", buyer_paid);
			sprintf(str_bdue, "%.2f", buyer_due);

			//iText(rx1 + 80, ry1 - 6 * 30, "RECORDS :", GLUT_BITMAP_HELVETICA_18);
			//iText(rx1 + 80 * 3, ry1 - 6 * 30, "___________", GLUT_BITMAP_HELVETICA_18);


			iText(rx1 + 80, ry1 - 3 * 30, "Paid:", GLUT_BITMAP_HELVETICA_18);
			iText(rx1 + 80 * 3, ry1 - 3 * 30, str_bpaid, GLUT_BITMAP_HELVETICA_18);


			if (buyer_due > 0)
			{
				iText(rx1 + 80, ry1 - 4 * 30, "Due:", GLUT_BITMAP_HELVETICA_18);
				iText(rx1 + 80 * 3, ry1 - 4 * 30, str_bdue, GLUT_BITMAP_HELVETICA_18);
			}
			else
			{
				iText(rx1 + 80, ry1 - 5 * 30, "No Due", GLUT_BITMAP_HELVETICA_18);
			}
			iText(rx1+50, ry1 - 400, "________________________", GLUT_BITMAP_TIMES_ROMAN_24);
		}
		back_button();
	}
	//page 5 customer search
	if (page == 5)
	{
		iSetColor(149, 33, 246);
		iRectangle(0, 0, x, y);

		if (search_called == 0)
		{
			iText(rx1 - 100, ry1 + 100, "=======SEARCH customer RECORD=======", GLUT_BITMAP_TIMES_ROMAN_24);
			iText(rx1, ry1 + 40, "Enter the Customer Name : ", GLUT_BITMAP_HELVETICA_18);
			iRectangle(rx1 + 420, ry1, 80, 35);
			textbox(rx1, ry1, str);
			
			iText(rx1 + 425, ry1 + 10, "Enter", GLUT_BITMAP_TIMES_ROMAN_24);
			back_button();
			iText(rx1 - 50, ry1 - 500, "Press enter to save and Click enter to go to next page.", GLUT_BITMAP_TIMES_ROMAN_24);
			
		}


		if (found == 0)
		{
			iText(rx1 - 10, ry1, "Sorry no such customer exists.", GLUT_BITMAP_TIMES_ROMAN_24);
			iText(rx1 + 80, ry1 + 2 * 30, " NOT FOUND ", GLUT_BITMAP_HELVETICA_18);
			back_button();
		}

		if (found == 1)
		{

			char str_total[100];
			char str_bpaid[100];
			char str_bdue[100];
			sprintf(str_bpaid, "%.2f",customer.paid);
			sprintf(str_bdue, "%.2f", customer.due);

			iText(rx1 + 80, ry1 - 2 * 30,"Date            ", GLUT_BITMAP_HELVETICA_18);
			iText(rx1 + 80 * 3, ry1 - 2 * 30, customer.date, GLUT_BITMAP_HELVETICA_18);
			iText(rx1 + 80, ry1 - 3 * 30,"Customer Name  ", GLUT_BITMAP_HELVETICA_18);
			iText(rx1 + 80 * 3, ry1 - 3 * 30, customer.customer, GLUT_BITMAP_HELVETICA_18);
			iText(rx1 + 80, ry1 - 4 * 30,"Phone NO        ", GLUT_BITMAP_HELVETICA_18);
			iText(rx1 + 80 * 3, ry1 - 4 * 30, customer.phone_no, GLUT_BITMAP_HELVETICA_18);
			iText(rx1 + 80, ry1 - 5 * 30,"Paid            ", GLUT_BITMAP_HELVETICA_18);
			iText(rx1 + 80 * 3, ry1 - 5 * 30, str_bpaid, GLUT_BITMAP_HELVETICA_18);

			if (customer.due > 0)
			{
				iText(rx1 + 80, ry1 - 6 * 30, "Due        ", GLUT_BITMAP_HELVETICA_18);
				iText(rx1 + 80 * 3, ry1 - 6 * 30, str_bdue, GLUT_BITMAP_HELVETICA_18);
			}
			else
			{
				iText(rx1 + 80, ry1 - 7 * 30, " No Due", GLUT_BITMAP_HELVETICA_18);
			}

			iText(rx1, ry1 - 8 * 30, "_______________________________________ ", GLUT_BITMAP_HELVETICA_18);
			back_button();
			//iText(rx1, ry1 - 500, "Press left arrow to go to home page.", GLUT_BITMAP_TIMES_ROMAN_24);
			
		}

   

	}

	if (page == 6)
	{

		if (search_called == 0)
		{
			iText(rx1, ry1+100, "=======Daily Report=======", GLUT_BITMAP_TIMES_ROMAN_24);

		}

		if (found == 3)
		{
			iText(rx1 + 80, ry1, "Record not found", GLUT_BITMAP_TIMES_ROMAN_24);
		}

		if (found == 1)
		{
			char str_total[100];
			char str_paid[100];
			char str_due[100];
			char str_reports[100];

			sprintf(str_total, "%.2f", daily_sold);
			sprintf(str_paid, "%.2f", daily_paid);
			sprintf(str_due, "%.2f", daily_due);
			sprintf(str_reports, "%d", num_reports);



			iText(rx1 + 80, ry1 - 3 * 30, "Date:      ", GLUT_BITMAP_HELVETICA_18);
			iText(rx1 + 80 * 3, ry1 - 3 * 30,__DATE__, GLUT_BITMAP_HELVETICA_18);

			iText(rx1 + 80, ry1 - 4 * 30, "Total orders today:      ", GLUT_BITMAP_HELVETICA_18);
			iText(rx1 + 80 * 3, ry1 - 4 * 30, str_reports, GLUT_BITMAP_HELVETICA_18);

			iText(rx1 + 80, ry1 - 5 * 30, "Total:", GLUT_BITMAP_HELVETICA_18);
			iText(rx1 + 80 * 3, ry1 - 5 * 30, str_total, GLUT_BITMAP_HELVETICA_18);


			iText(rx1 + 80, ry1 - 6 * 30, "Paid:", GLUT_BITMAP_HELVETICA_18);
			iText(rx1 + 80 * 3, ry1 - 6 * 30, str_paid, GLUT_BITMAP_HELVETICA_18);

			if (daily_due > 0)
			{
				iText(rx1 + 80, ry1 - 7 * 30, "Due:", GLUT_BITMAP_HELVETICA_18);
				iText(rx1 + 80 * 3, ry1 - 7 * 30, str_due, GLUT_BITMAP_HELVETICA_18);
			}
			else
			{
				iText(rx1 + 80, ry1 - 7 * 30, "No Due", GLUT_BITMAP_HELVETICA_18);
			}
			
			//iText(rx1, ry1 - 400, "________________________", GLUT_BITMAP_TIMES_ROMAN_24);
		}

		back_button();
	}
	if (page == 7)
	{
		page_7();
	}

	//iFilledRectangle(10, 30, 20, 20);
	//iText(350,640, "HAALKHATA", GLUT_BITMAP_TIMES_ROMAN_24);
}


/*
function iMouseMove() is called when the user presses and drags the mouse.
(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my) {
	//printf("xj = %d, y= %d\n",mx,my);
	//place your codes here
}

/*
function iMouse() is called when the user presses/releases the mouse.
(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		//for home page
		if (page == 0)
		{
			if (mx >= 400 && mx <= 700 && my >= 640 && my <= 690)
			{
				page = 1;
				
			}
			else if (mx >= 400 && mx <= 700 && my >= 560 && my <= 610)
			{
				page = 2;
				found = 3;
				show_bills();
				
			}
			else if (mx >= 400 && mx <= 700 && my >= 480 && my <= 530)
			{
				page = 3;
				search_called = 0;
				found = 3;
				
			}
			else if (mx >= 400 && mx <= 700 && my >= 400 && my <= 450)
			{
				page = 4;
				found = 3;
				buyer_paid = 0;
				buyer_due = 0;
				customerrecord();
				
			}
			else if (mx >= 400 && mx <= 700 && my >= 320 && my <= 370)
			{
				page = 5;
				search_called = 0;
				found = 3;
				
			}
			else if (mx >= 400 && mx <= 700 && my >= 240 && my <= 290)
			{
				page = 6;
				found = 3;
				num_reports = 0;  // number of orders in file
				daily_sold = 0; // variable for sum of prices
				quantity = 0;	  // total items sold that day
				daily_paid = 0; // total paid by buyers that day
				daily_due = 0;  // total of dues that day
				daily_report();
				
			}
			else if (mx >= 400 && mx <= 700 && my >= 160 && my <= 210)
			{
				page = 7;
				
			}
		}

		/// for page 1
		if (page == 1)
		{
			if (mx >= 400 && mx <= 700 && my >= 640 && my <= 690 && mode == 0)
			{
				mode = 1;
				
			}

			if (mx >= rx1 + 420 && mx <= rx1 + 500 && my >= ry1 && my <= ry1 + 35)
			{
				count++;
				color = 1;
				if (count == 1)
				{
					
					strcpy(ord.customer, str2);
					strcpy(buyer.customer, ord.customer);
				}

				if (count == 2)
				{
					strcpy(buyer.phone_no, str2);
					
				}

				strcpy(ord.date, __DATE__);
				strcpy(buyer.date, __DATE__);

				if (count == 3)
				{
					ord.numOfItems = atoi(str2);
					
				}

				if (position < ord.numOfItems)
				{
					if (count == 4)
					{
						strcpy(ord.itm[position].item, str2);
						
					}

					if (count == 5)
					{
						ord.itm[position].qty = atoi(str2);
						
					}
					if (count == 6)
					{
						
						ord.itm[position].price = atof(str2);
						total += ord.itm[position].qty * ord.itm[position].price;
						items_bought++;
						// count++;
						if (items_bought < ord.numOfItems)
						{
							position++;
							count = 3;
						}
					}

					if (count == 7)
					{
						
						ord.paid = atof(str2);
						buyer.paid = ord.paid;
						
						toggle_generate = 1;
						position = 0;
						generate_bills();
						// count++;
					}
				}
			}
		}

		if (page == 3)
		{
			if (mx >= 400 && mx <= 700 && my >= 640 && my <= 690)
			{
				mode = 1;
				
			}
			if (mx >= rx1 + 420 && mx <= rx1 + 500 && my >= ry1 && my <= ry1 + 35)
			{
				search_called = 1;
				Search_bill();
			}
		}

		if (page == 4)
		{
			if (mx >= 400 && mx <= 700 && my >= 640 && my <= 690)
			{
				mode = 1;
				
			}
			if (mx >= rx1 + 420 && mx <= rx1 + 500 && my >= ry1 && my <= ry1 + 35)
			{
				search_called = 1;
				daily_report();
			}
		}
		// page5
		if (page == 5)
		{
			if (mx >= 400 && mx <= 700 && my >= 640 && my <= 690)
			{
				mode = 1;
				
			}
			if (mx >= rx1 + 420 && mx <= rx1 + 500 && my >= ry1 && my <= ry1 + 35)
			{
				search_called = 1;
				searchcustomer();
			}
		}
		//back button
		if (page!= 0)
		{
			if (mx >= rx1 + 420 && mx <= rx1 +500 && my >= ry1-435 && my <= ry1-400)
			{
				page = 0;
				total = 0;
				toggle_generate = 0;
				count = 0;
				items_bought = 0;
				 buyer_paid = 0;
				 buyer_due = 0;
				search_called = 0;
				found = 3;
				num_reports = 0; // number of orders in file
				daily_sold = 0;     // variable for sum of prices
				quantity = 0;     // total items sold that day
				daily_paid = 0;     // total paid by buyers that day
				daily_due = 0;
				total = 0;
				

			}
		}


	}


	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		//place your codes here
		//x -= 10;
		//y -= 10;
	}
}

/*
function iKeyboard() is called whenever the user hits a key in keyboard.
key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{
	if (page == 1)
	{

		int i;
		if (mode == 1)
		{
			if (key == '\r')
			{

				// mode = 0;
				strcpy(str2, str);
				for (i = 0; i < len; i++)
					str[i] = 0;
				len = 0;

				
			}
			else
			{
				str[len] = key;
				len++;
			}
		}
	}
	if (page == 3)
	{
		name[0] = NULL;
		int i;
		if (mode == 1)
		{

			if (key == '\r')
			{

				mode = 0;
				strcpy(str2, str);

				for (i = 0; i < len; i++)
					str[i] = 0;
				len = 0;
				strcpy(name, str2);
				
			}
			else
			{
				str[len] = key;
				len++;
			}
		}
	}

	if (page == 5)
	{

		int i;
		if (mode == 1)
		{
			if (key == '\r')
			{

				mode = 0;
				strcpy(str2, str);
				for (i = 0; i < len; i++)
					str[i] = 0;
				len = 0;
				strcpy(name, str2);
				
			}
			else
			{
				str[len] = key;
				len++;
			}
		}
	}

	if (key == 'x')
	{
		// do something with 'x'
	}

	// place your codes for other keys here
}

/*
function iSpecialKeyboard() is called whenver user hits special keys like-
function keys, home, end, pg up, pg down, arraows etc. you have to use
appropriate constants to detect them. A list is:
GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/
void iSpecialKeyboard(unsigned char key) {
	//for start page
	if (page == -1)
	{
		if (key == GLUT_KEY_RIGHT){ page = 0; }
	}
	if (key == GLUT_KEY_END) {
		exit(0);
	}
	/*if (key == GLUT_KEY_LEFT)
	{
		page = 0;
		total = 0;
		toggle_generate = 0;
		count = 0;
		items_bought = 0;

		search_called = 0;
		found = 3;
		num_reports = 0; // number of orders in file
		daily_sold = 0;     // variable for sum of prices
		quantity = 0;     // total items sold that day
		daily_paid = 0;     // total paid by buyers that day
		daily_due = 0;

		total = 0;
	}*/
	//place your codes for other keys here
}

int main() {
	//place your own initialization codes here.
	iInitialize(1000, 800, "HAALKHATA");
	return 0;
}

