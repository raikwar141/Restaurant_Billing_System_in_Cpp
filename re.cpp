#include <graphics.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <dos.h>
#include "conio2.h"

// Public Functions Required By Many Different Functions.
void statusbar(char[]);
void getlinedelchar(char *, int, int, int *);
void getline(char *, int);

// The Drawing Functions & The Main Screen.

void lineh(int, int, int, char);	// Drawing horizontal lines
void linev(int, int, int, char);	// Drawing vertical lines
void box(int, int, int, int, char);	// Drawing boxes
void mscreen();	// Main screen of the Restaurant program

// Functions For Drawing Main Menus
void main_menu();
int vertical_menu(char [] [20], int, int, int, int);
int horizontal_menu(char [] [20], int, int, int, int);
void help();     // Display some help messages

//  All The Fields Related To available restaurant items
struct restaurant
{
	int   itemcode, dd, mm, yy ;
	char  itemname[31], itemcat[31];
	float price;
};

// Fields related to order of a partcular bill no.
struct order
{
	int itemcode;
	int   billno, dd, mm, yy ;
	char  itemname[31];
	int   itemqty;
	float price;
};


int   fcode(int);	// Function to know the code is present
int billcode(int);	// Function to know the bill no. is exists or not.
int   date(int, int, int);	// Check a valid date
void  display1(char tcat[]);    // Displaying the categories
void  display(int);

//  All The Functions Related To restaurant

void  Item_add();   // Adding new items in restaurant
void  Order_add1();	// Adding the customers order
void  Item_modify();	// Modifying any item in the restaurant
void  Item_del();	// Deleting the item from the list
void  displaycode();	// Displaying the items
void  showlist();	// Showing the item list
void  Bill_slip();	// Printing the bill(s)
void  print(int, int, int, int);	// Activates the printer to print information

// FUNCTION : lineh
// DESCRIPTION : To Draw A Horizontal Line   (x1, x2, y)
void  lineh (int row1, int row2, int column, char c)
{
	for (row1; row1 <= row2; row1++)
	{
		gotoxy (row1, column) ;
		printf ("%c",c) ;
	}
}

// FUNCTION : linev
// DESCRIPTION : To Draw A Vertical Line (y1, y2, x)
void linev (int column1, int column2, int row, char c)
{
	for (column1; column1 <= column2; column1++ )
	{
		gotoxy (row, column1) ;
		printf ("%c",c) ;
	}
}

// FUNCTION : box
// DESCRIPTION : To Draw A Box  (x1, y1, x2, y2)
void  box(int row1, int column1, int row2, int column2, char c)
{
	char ch=218 ;
	char c1, c2, c3, c4 ;
	char l1=196, l2=179 ;
	if (c == ch)
	{
		c1 = 218 ;
		c2 = 191 ;
		c3 = 192 ;
		c4 = 217 ;
		l1 = 196 ;
		l2 = 179 ;
	}
	else
	{
		c1 = c ;
		c2 = c ;
		c3 = c ;
		c4 = c ;
		l1 = c ;
		l2 = c ;
	}
	gotoxy(row1,column1) ;
	printf ("%c",c1) ;
	gotoxy(row2,column1) ;
	printf ("%c",c2) ;
	gotoxy(row1,column2) ;
	printf ("%c",c3) ;
	gotoxy(row2,column2) ;
	printf ("%c",c4) ;
	row1++ ;
	row2-- ;
	lineh(row1, row2, column1, l1) ;
	lineh(row1, row2, column2, l1) ;
	row1-- ;
	row2++ ;
	column1++ ;
	column2-- ;
	linev(column1,column2,row1,l2) ;
	linev(column1,column2,row2,l2) ;
}

// FUNCTION : mscreen
// DESCRIPTION : To Paint The Screen With the The Opening Screen.
void mscreen()
{
	int gd=DETECT, gm ;
	int t,i;
	long int k,m,j;
	initgraph(&gd, &gm, "\\turboc3") ;

	setcolor(LIGHTGRAY) ;
	rectangle(0, 0, getmaxx(), getmaxy()) ;
	setfillstyle(SOLID_FILL, LIGHTGRAY) ;
	floodfill(getmaxx()/2, getmaxy()/2, LIGHTGRAY) ;

	for( t = 1; t < 115; t++)
	{
		setcolor(DARKGRAY) ;
		for( m = 0; m < 103000.0; m++) ;
			rectangle(getmaxx()/2-t-150, getmaxy()/2+t, getmaxx()/2+t+150, getmaxy()/2-t) ;
		floodfill(getmaxx()/2, getmaxy()/2, DARKGRAY) ;
	}

	setcolor(WHITE) ;
	settextstyle(GOTHIC_FONT, HORIZ_DIR, 7) ;
	settextjustify(CENTER_TEXT, CENTER_TEXT) ;
	outtextxy(getmaxx()/2, getmaxy()/2-60, "WELCOME" ) ;
	outtextxy(getmaxx()/2, getmaxy()/2+60, "YOU" ) ;
	for (j = 0; j < 500; j++)
		for( k = 0; k < 40000.0; k++) ;
			setcolor(BLACK) ;
	rectangle(0, 0, getmaxx(), getmaxy()) ;
	setfillstyle(SOLID_FILL, BLACK) ;
	floodfill(getmaxx()/2, getmaxy()/2, BLACK) ;
	for( i = 1; i < 150; i++)
	{
		setcolor(RED) ;
		settextstyle(GOTHIC_FONT, HORIZ_DIR, 7) ;
		settextjustify(CENTER_TEXT, CENTER_TEXT) ;
		outtextxy(160+i, 40+i, "McDonalds - RES" ) ;
		for(j = 0 ;j < 100; j++) ;
			setcolor(BLACK) ;
		settextstyle(GOTHIC_FONT, HORIZ_DIR, 7) ;
		settextjustify(CENTER_TEXT, CENTER_TEXT) ;
		outtextxy(160+i, 40+i, "McDonalds - RES" ) ;
	}
	setcolor(RED) ;
	settextstyle(GOTHIC_FONT, HORIZ_DIR, 7) ;
	settextjustify(CENTER_TEXT, CENTER_TEXT) ;
	outtextxy(160+i, 40+i, "McDonalds - RES" ) ;
	for(j = 0; j < 250; j++)
		for(k = 0; k < 40000.0; k++) ;
	for(k = i; k > 50; k--)
	{
		setcolor(RED) ;
		settextstyle(GOTHIC_FONT, HORIZ_DIR, 7) ;
		settextjustify(CENTER_TEXT, CENTER_TEXT) ;
		outtextxy(160+i, 40.0+k, "McDonalds - RES" ) ;
		for( j = 0; j < 100; j++) ;
		setcolor(BLACK) ;
		settextstyle(GOTHIC_FONT, HORIZ_DIR, 7) ;
		settextjustify(CENTER_TEXT, CENTER_TEXT) ;
		outtextxy(160+i, 40.0+k, "McDonalds - RES" ) ;
	}
	setcolor(RED) ;
	settextstyle(GOTHIC_FONT, HORIZ_DIR, 7) ;
	settextjustify(CENTER_TEXT, CENTER_TEXT) ;
	outtextxy(160+i, 40.0+k, "McDonalds - RES" ) ;
	for(j = 0; j < 250; j++)
		for(k = 0; k < 40000.0; k++) ;
	for(i = 1; i < 200; i++)
	{
		setcolor(LIGHTRED) ;
		settextstyle(GOTHIC_FONT, HORIZ_DIR, 5) ;
		settextjustify(CENTER_TEXT, CENTER_TEXT) ;
		outtextxy(0+i, getmaxy()/2-10, "Programmed by : " ) ;
		for( j = 0; j < 100; j++) ;
		setcolor(BLACK) ;
		settextstyle(GOTHIC_FONT, HORIZ_DIR, 5) ;
		settextjustify(CENTER_TEXT, CENTER_TEXT) ;
		outtextxy(0+i, getmaxy()/2-10, "Programmed by : " ) ;
	}
	setcolor(LIGHTRED) ;
	settextstyle(GOTHIC_FONT, HORIZ_DIR, 5) ;
	settextjustify(CENTER_TEXT, CENTER_TEXT) ;
	outtextxy(0+i, getmaxy()/2-10, "Programmed by : " ) ;
	for(j = 0; j < 250; j++)
		for(k = 0; k < 40000.0; k++);
	for(i = 1; i < 300; i++)
	{
		setcolor(GREEN);
		settextstyle(GOTHIC_FONT, HORIZ_DIR, 5);
		settextjustify(CENTER_TEXT, CENTER_TEXT);
		outtextxy(0+i, getmaxy()/2+50, "Reeta Sahoo" );
		for( j = 0; j < 100; j++);
		setcolor(BLACK);
		settextstyle(GOTHIC_FONT, HORIZ_DIR, 5);
		settextjustify(CENTER_TEXT, CENTER_TEXT);
		outtextxy(0+i, getmaxy()/2+50, "Reeta Sahoo" );
	}
	setcolor(GREEN);
	settextstyle(GOTHIC_FONT, HORIZ_DIR, 5);
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	outtextxy(0+i, getmaxy()/2+50, "Reeta Sahoo" );
	for(j = 0; j < 250; j++)
		for(k = 0; k < 40000.0; k++) ;
	for(i = 1; i < 315; i++)
	{
		setcolor(LIGHTRED) ;
		settextstyle(GOTHIC_FONT, HORIZ_DIR, 5) ;
		settextjustify(CENTER_TEXT, CENTER_TEXT) ;
		outtextxy(0+i, getmaxy()/2+95, "&" ) ;
		for( j = 0; j < 10000; j++) ;
		setcolor(BLACK) ;
		settextstyle(GOTHIC_FONT, HORIZ_DIR, 5) ;
		settextjustify(CENTER_TEXT, CENTER_TEXT) ;
		outtextxy(0+i, getmaxy()/2+95, "&" ) ;
	}
	setcolor(LIGHTRED) ;
	settextstyle(GOTHIC_FONT, HORIZ_DIR, 5) ;
	settextjustify(CENTER_TEXT, CENTER_TEXT) ;
	outtextxy(0+i, getmaxy()/2+95, "&"  ) ;
	for(j = 0; j < 250; j++)
		for(k = 0; k < 40000.0; k++) ;
	for(i = 1; i < 450; i++)
	{
		setcolor(GREEN) ;
		settextstyle(GOTHIC_FONT, HORIZ_DIR, 5) ;
		settextjustify(CENTER_TEXT, CENTER_TEXT) ;
		outtextxy(0+i, getmaxy()/2+140, "Gagan Sahoo" ) ;
		for( j = 0; j < 100; j++) ;
		setcolor(BLACK) ;
		settextstyle(GOTHIC_FONT, HORIZ_DIR, 5) ;
		settextjustify(CENTER_TEXT, CENTER_TEXT) ;
		outtextxy(0+i, getmaxy()/2+140, "Gagan Sahoo" ) ;
	}
	setcolor(GREEN) ;
	settextstyle(GOTHIC_FONT, HORIZ_DIR, 5) ;
	settextjustify(CENTER_TEXT, CENTER_TEXT) ;
	outtextxy(0+i, getmaxy()/2+140, "Gagan Sahoo" ) ;

	for(j = 0; j < 500; j++)
		for(k = 0; k < 40000.0; k++) ;
	for(i = 0; i < 550; i++)
	{
		for( j = 0; j < 50000.0; j++) ;
		setcolor(BLACK) ;
		rectangle(0+i, 0, 100+i, getmaxy()) ;
	}
	closegraph() ;
}

// FUNCTION : vertical_menu
// DESCRIPTION : To Make Vertical Menu.
int  vertical_menu(char menu[] [20], int present, int end, int x, int y)
{
	int ex=0 ;
	int i;
	char ch;
	box(x + 9, y, x + strlen(menu[0]) + 12, y + end + 1, 218) ;
	for ( i=0; i<end; i++)
	{
		gotoxy(x + 10, y + i + 1) ;
		printf ("%s",menu[i]) ;
	}
	do
	{
		int tpresent = present ;
		textcolor(BLACK) ;
		textbackground(WHITE) ;
		gotoxy(x + 10,y + present) ;
		cprintf(menu[present - 1]) ;
		textcolor(WHITE) ;
		textbackground(BLACK) ;
		ch = getch() ;
		switch (ch)
		{
			case 75 :
				if (present == 1)
					present = end ;
				else
					present-- ;
					break ;

			case 77 :
				if (present == end)
					present = 1 ;
				else
					present++ ;
					break ;

			case 71 :
				present = 1 ;
				break ;

			case 79 :
				present = end ;
				break ;

			case 72 :
				if (present == 1)
					present = end ;
				else
					present-- ;
					break ;

			case 80 :
				if (present == end)
					present = 1 ;
				else
					present++ ;
					break ;

			case 13 :
				ex = 1 ;
				break ;

			case 27 :
				present = end ;
				ex = 1 ;
		}
		gotoxy(x + 10,y + tpresent) ;
		cprintf(menu[tpresent - 1]) ;
	} while(!ex) ;
	return(present) ;
}

// CLASS : menu
// FUNCTION : horizontal_menu
// DESCRIPTION : To Make Horizontal Menu.
int  horizontal_menu(char menu[] [20], int present, int end, int x, int y)
{
	int ex=0, i ;
	char ch;
	for (i = 0; i < end; i++)
	{
		gotoxy(x + (i + 2) * 10 - 5, y) ;
		printf ("%s",menu[i]);
	}
	lineh(1, 80, 2, 205) ;
	do
	{
		int tpresent = present ;
		textcolor(BLACK) ;
		textbackground(WHITE) ;
		gotoxy(x + (present + 1) * 10 - 5, y) ;
		cprintf(menu[present - 1]) ;
		textcolor(WHITE) ;
		textbackground(BLACK) ;
		ch = getch() ;
		switch (ch)
		{
			case 71 :
				present = 1 ;
				break ;

			case 79 :
				present = end ;
				break ;

			case 75 :
				if (present == 1)
					present = end ;
				else
					present-- ;
				break ;

			case 77 :
				if (present == end)
					present = 1 ;
				else
					present++ ;
				break ;

			case 72 :
				if (present == 1)
					present = end ;
				else
					present-- ;
				break ;

			case 80 :
				if (present == end)
					present = 1 ;
				else
					present++ ;
				break ;

			case 13 :
				ex = 1 ;
				break ;

			case 27 :
				present = end ;
				ex = 1 ;
		}
		gotoxy(x + (tpresent + 1) * 10 - 5, y) ;
		cprintf(menu[tpresent - 1]) ;
	} while(!ex) ;
	return(present) ;
}

// FUNCTION : help
// DESCRIPTION : To Print The Help Screen For Various Important
//               Operations.
void  help()
{
	clrscr();
	printf ("\n\n\n\t\t\tAbout McDonald's Restaurant Management ");
	printf ("\n\nThis is a instruction set program for the user, who can");
	printf ("\n utilize it for better development purpose.");
	printf ("\n\n\n 1) Important instructions are displayed at the status bar at the   ");
	printf ("\n    bottom of the screen.");
	printf ("\n\n 2) Press escape key to exit the immediate screen at any time");
	printf ("\n    during the program.");
	printf ("\n\n\n\n");
	printf ("\t\t\t\t\t\tReeta Sahoo");
	printf ("\n\t\t\t\t\t\tGagan Sahoo");
	getch();
	clrscr() ;
	return ;
}

// CLASS : menu
// FUNCTION : main
// DESCRIPTION : To Draw The Main Menu & Call Related Functions
/*	This menu displays its options on the top of the screen like
	FILE	EDIT	PRINT	HELP	EXIT
	and press enter to select any menu option with related menus

	Note : Select the PRINT menu when your printer is ON and the related items
		and bills are prepared.
*/
void  main_menu()
{
	int end=5, present=1, upperlim1=6, currentpos1=1, upperlim2=3, currentpos2=1, upperlim3=4, currentpos3=1;
	char main[] [20] = { " FILE ", " EDIT ", " PRINT ", " HELP ", " EXIT " } ;
	char sub1[] [20] = { "New item    ", "Display Info ", "Display List ", "Bill  ", "Order","Return       " } ;
	char sub2[] [20] = { "Modify item    ", "Delete item ", "Return          " } ;
	char sub3[] [20] = { "Item Info    ", "Item List ", "Bill   ", "Return        " } ;

	// Display a colourful menu
	mscreen() ;
	do
	{
		_setcursortype(_NOCURSOR) ;
		present = horizontal_menu(main, present, end, 3, 1) ;
		switch (present)
		{
			case 1 :
				currentpos1 = vertical_menu(sub1, currentpos1, upperlim1, 3, 3) ;
				switch (currentpos1)
				{
					case 1 :
						_setcursortype(_SOLIDCURSOR) ;
						Item_add() ;
						_setcursortype(_NOCURSOR) ;
						break ;
					case 2 :
						_setcursortype(_SOLIDCURSOR) ;
						displaycode() ;
						break ;
					case 3 :
						showlist() ;
						break ;
					case 4 :
						_setcursortype(_SOLIDCURSOR) ;
						Bill_slip() ;
						_setcursortype(_NOCURSOR) ;
						break ;
					case 5 :
						_setcursortype(_SOLIDCURSOR) ;
						Order_add1() ;
						_setcursortype(_NOCURSOR) ;
						break;
				}
				clrscr() ;
				break ;
			case 2 :
				currentpos2 = vertical_menu(sub2, currentpos2, upperlim2, 13, 3) ;
				switch(currentpos2)
				{
					case 1 :
						_setcursortype(_SOLIDCURSOR) ;
						Item_modify() ;
						_setcursortype(_NOCURSOR) ;
						break ;
					case 2 :
						_setcursortype(_NORMALCURSOR) ;
						Item_del() ;
						_setcursortype(_NOCURSOR) ;
						break ;
				}
				clrscr() ;
				break ;
			case 3 :
				currentpos3 = vertical_menu(sub3, currentpos3, upperlim3, 27, 3) ;
				switch(currentpos3)
				{
					case 1 :
						_setcursortype(_SOLIDCURSOR) ;
						displaycode() ;
						print(1,1,80,23) ;
						_setcursortype(_NOCURSOR) ;
						break ;
					case 2 :
						_setcursortype(_NORMALCURSOR) ;
						showlist() ;
						print(1,1,80,23) ;
						_setcursortype(_NOCURSOR) ;
						break ;
					case 3 :
						_setcursortype(_NORMALCURSOR) ;
						Bill_slip() ;
						print(1,1,80,23) ;
						_setcursortype(_NOCURSOR) ;
						break ;
				}
				clrscr() ;
				break ;
			case 4 :
				help() ;
				clrscr() ;
				break ;
		}
	} while (present != end);
}

// FUNCTION : fcode
// DESCRIPTION : To Return 0 If The Given Code Is Not Found
/*	This function is used to find the code of an item i.e.; the item is
there in the database restaur.dat or not. If the item is there, the fcode()
function will return 1 otherwise it will return 0 to its called program.

*/
int  fcode(int code)
{
	FILE *file ;
	int found = 0 ;
	struct restaurant temp;
	file = fopen("restaur.Dat", "rb+") ;
	while (fread(&temp, sizeof(struct restaurant),1,file))
	{
		printf("\n%d",found);
		getch();
		if (temp.itemcode == code)
		{

			found = 1 ;
			break ;
		}
	}
	fclose(file) ;
	return(found) ;
}

// FUNCTION : billcode()
// DESCRIPTION : To Return 0 If The Given billno is Is Not Found
/*	This function is used to find the billno of an order no i.e.; the bill no. is
there in the database order.dat or not. If the order no. is there, the billcode()
function will return 1 otherwise it will return 0 to its called program.

*/

int  billcode(int code)
{
	FILE *file ;
	int found = 0 ;
	struct order temp;
	file = fopen("order.Dat", "rb+") ;
	while (fread(&temp, sizeof(struct order),1,file))
	{
		if (temp.billno == code)
		{

			found = 1 ;
			break ;
		}
	}
	fclose(file) ;
	return(found) ;
}

// FUNCTION : date
// DESCRIPTION : To Return '0' If The Date Received Is Invalid
int  date(int dd, int mm, int yy)
{
	int days=0, valid ;
	if ((yy>1980) && (yy<=1999))
		valid = 1 ;
	else
	{
		valid = 0 ;
		return(0) ;
	}

	switch (mm)
	{
		case 1 :
			days = 31 ;
			break ;
		case 2 :
			if (yy % 4 == 0)
				days = 29 ;			// leap year
			else
				days = 28 ;
				break ;
		case 3 :
			days = 31 ;
			break ;
		case 4 :
			days = 30 ;
			break ;
		case 5 :
			days = 30 ;
			break ;
		case 6 :
			days = 31 ;
			break ;
		case 7 :
			days = 31 ;
			break ;
		case 8 :
			days = 31 ;
			break ;
		case 9 :
			days = 30 ;
			break ;
		case 10 :
			days = 31 ;
			break ;
		case 11 :
			days = 30 ;
			break ;
		case 12 :
			days = 31 ;
			break ;
		default :
			valid = 0 ;
			break ;
	}
	if ((dd > 0) && (dd <= days))
		valid = 1 ;
	else
		valid = 0 ;
	return (valid) ;
}

// FUNCTION : display
// DESCRIPTION : To Display A Record From "restaur.Dat"
/*	This function is helpful to display the category wise items on the
screen or printer according to main menu. When you will be enter VEG or NON-VEG or any,
(according to your item entry) this menu will display category wise all the items with related option
from the restaur.dat database.

*/
void  display1(char  tcat[31])
{
	FILE *file ;
	struct restaurant t ;
	char *initial ;
	file = fopen("restaur.Dat", "rb+") ;
	while (fread(&t, sizeof(struct restaurant),1,file))
	{
		if (strcmp(t.itemcat,tcat)==0)
		{
			clrscr();
			gotoxy(28,2) ;
			printf ("CATEGORY WISE  INFORMATION");
			gotoxy(30,3) ;
			printf ("CATEGOEY   # %s",t.itemcat) ;
			lineh(2,79,4,240) ;
			gotoxy(20,6) ;
			printf ("Name              :    %s",t.itemname) ;
			gotoxy(20,8) ;
			printf ("Code              :    %d" ,t.itemcode );
			gotoxy(20,10) ;
			printf ("Price            : Rs. %.2f",t.price) ;
			lineh(2,79,22,240) ;
			getch();
		}
	}
	fclose(file) ;
}

// Function display()
// This function is used to display the item code if exist
// in the restaur.dat data file
/*	This function is helpful to display the item information on the
screen or printer according to main menu. When you will press Display Item from the FILE or PRINT menu
it will display all the items with related option from the restaur.dat database.

*/

void  display(int  code)
{
	FILE *file ;
	struct restaurant t ;
	char *initial ;
	file = fopen("restaur.Dat", "rb+") ;
	while (fread(&t, sizeof(struct restaurant),1,file))
	{
		if (t.itemcode==code)
		{
			gotoxy(28,2) ;
			printf ("ITEM  INFORMATION");
			gotoxy(30,3) ;
			printf ("restaurant CODE #   %d",t.itemcode) ;
			lineh(2,79,4,240) ;
			gotoxy(20,6) ;
			printf ("Name              :    %s",t.itemname) ;
			gotoxy(20,8) ;
			printf ("Category          :    %s" ,t.itemcat );
			gotoxy(20,10) ;
			printf ("Price            : Rs. %.2f",t.price) ;
			lineh(2,79,22,240) ;
		}
	}
	fclose(file) ;
}

// FUNCTION : Item_add()
// DESCRIPTION : To Get Data About New restaurant
/*	This function is used to input items and the related information
with proper validation. Here the itemcode will generate automatically when
you will continue for next item at any time.	*/
void  Item_add()
{
	struct restaurant t ;
	struct restaurant te ;
	FILE *file ;
	char ch, choice='Y';
	char d[3], m[3], y[5], price[10];
	int  code=0, valid ;
	do
	{
		clrscr() ;
		_setcursortype(_SOLIDCURSOR) ;
		gotoxy(28,2) ;
		printf ("ADDITION OF NEW ITEM");
		lineh(20,59,3,240) ;
		gotoxy(31,4) ;
		printf ("Item Code # ");
		gotoxy(29,5) ;
		printf ("~~~~~~~~~~~~~~~~~~~~~");
		gotoxy(5,8) ;
		printf ("Name         : .............................");
		gotoxy(5,10) ;
		printf ("Catagory      : .............................");
		gotoxy(5,12) ;
		printf ("Price    (Rs) :  .........");

		file = fopen("restaur.Dat", "rb+") ;

		// Steps to generate automatic code after incrementing 1 with the
		// reataur.dat file(s) itemcode
		while (fread(&te, sizeof(struct restaurant),1,file)==1)
			code = te.itemcode ;
		fclose(file) ;
		code++ ;
		t.itemcode = code ;
		gotoxy(47,4) ;
		printf ("%d",t.itemcode) ;

		do
		{
			valid = 1 ;
			statusbar(" ENTER THE NAME OF THE ITEM") ;
			_setcursortype(_SOLIDCURSOR) ;
			gotoxy(20,8) ;
			printf ("                     ");
			gotoxy(20,8) ;
			getline(t.itemname, 29) ;
			if (t.itemname[0] == '0')
				return ;
			if (strlen(t.itemname) < 1)
			{
				valid = 0 ;
				statusbar("\a ENTER CORRECTLY (LENGTH : 1..30)") ;
				getch() ;
				_setcursortype(_SOLIDCURSOR) ;

			}
		} while (!valid) ;

		do
		{
			valid = 1 ;
			statusbar(" ENTER CATEGORY OF THE ITEM") ;
			_setcursortype(_SOLIDCURSOR) ;
			gotoxy(20,10) ;
			printf ("                     ");
			gotoxy(20,10) ;
			getline(t.itemcat, 29) ;
			if (t.itemcat[0] == '0')
				return ;
			if (strlen(t.itemcat) < 1)
			{
				valid = 0 ;
				statusbar("\a ENTER CORRECTLY (LENGTH : 1..30)") ;
				getch() ;
				_setcursortype(_SOLIDCURSOR) ;
			}
		} while (!valid) ;

		do
		{
			valid = 1 ;
			statusbar(" ENTER PRICE OF THE ITEM") ;
			_setcursortype(_SOLIDCURSOR) ;
			gotoxy(20,12) ;
			clreol() ;
			getline(price,9) ;
			t.price = atof(price) ;
			if (price[0] == 27)
				return ;
			if ((strlen(price) == 0) || (t.price>100000.0))
			{
				valid = 0;
				statusbar("\a SHOULD NOT BE GREATER THAN 100000") ;
				getch() ;
				_setcursortype(_SOLIDCURSOR) ;
			}
		} while (!valid) ;

		do
		{
			statusbar("\a Do you wish to save (y/n) : ") ;
			ch = getch() ;
			ch = toupper(ch) ;
			if (ch == '0'|| ch == 27)
				return ;
		} while (ch != 'Y' && ch != 'N') ;
		if (ch == 'N')
			return ;

		file = fopen("restaur.Dat", "ab+") ;
		fwrite(&t, sizeof(struct restaurant),1,file) ;
		fclose(file) ;

		statusbar("\a Add any more (y/n) : ") ;
		do
		{
			choice = getch() ;
			choice = toupper(choice) ;
			if (choice == 13)
				choice = 'Y' ;
			if (choice == 27)
				choice = 'N' ;
		} while((choice != 'Y') && (choice !='N'));
	} while(choice == 'Y');
}

// FUNCTION : Order_add1()
// DESCRIPTION : To Get Data About Order place
/*	When any customer came into the restaurant, you have to take the order, and make
a order list in your computer to produce a proper bill for record purposes. You can
take any type of order and place to the customers accordingly. */
void  Order_add1()
{
	struct order o ;
	struct restaurant te ;
	FILE *file ;
	char ch, choice='Y';
	char d[3], m[3], y[5], price[10];
	int  code=0, valid = 0 ;

	do
	{
		clrscr() ;
		code = 0;
		valid = 0;
		_setcursortype(_SOLIDCURSOR) ;
		gotoxy (28,2) ;
		printf ("PLACING THE ORDER");
		lineh(20,59,3,240) ;
		gotoxy (31,4) ;
		printf ("Item Code # ");
		gotoxy (47,4) ;
		scanf ("%d",&o.itemcode) ;
		file = fopen("restaur.Dat", "rb+") ;

		while (fread(&te, sizeof(struct restaurant),1,file)==1)
		{
			if(o.itemcode==te.itemcode)
			{
				strcpy(o.itemname,te.itemname);
				o.price = te.price;
				valid = 1;
			}
		}
		if (valid == 0)
		{
			printf (" Item not found");
			printf ("~~~~~~~~~~~~~~~~~~~~~");
			break;
		}

		gotoxy(5,8) ;
		printf ("Name         : .............................");
		gotoxy(5,12) ;
		printf ("Price    (Rs) :  .........");
		gotoxy(22,8);
		printf ("%s",o.itemname);
		gotoxy (22,12);
		printf ("%.2f",o.price);
		gotoxy (60,3);
		printf (" Bill Number :  ....");
		gotoxy (76,3);
		scanf  (" %d",&o.billno);
		gotoxy (5,14);
		printf ("Quantity      :  ...........");
		gotoxy (22,14);
		scanf  ("%d",&o.itemqty);
		fclose(file);

		do
		{
			statusbar("\a Do you wish to save (y/n) : ") ;
			ch = getch() ;
			ch = toupper(ch) ;
			if (ch == '0'|| ch == 27)
				return ;
		} while (ch != 'Y' && ch != 'N') ;
		if (ch == 'N')
			return ;

		file = fopen("order.dat", "ab+") ;
		fwrite(&o, sizeof(struct order),1,file) ;
		fclose(file) ;

		statusbar("\a Add any more (y/n) : ") ;
		do
		{
			choice = getch() ;
			choice = toupper(choice) ;
			if (choice == 13)
				choice = 'Y' ;
			if (choice == 27)
				choice = 'N' ;
		} while((choice != 'Y') && (choice !='N'));
	} while(choice == 'Y');
}

// FUNCTION : Item_modify
// DESCRIPTION : To Provide With Necessary Data Required For
//               Modification Of A Given Record
/*	Modify your items information like, change the price, change
the name of item etc. when necessary. When the screen appears in front
of you, you just enter the item code and then it will display the information
of the existing item and will speak for modification. If you won't modify
any item the previous information of that will remain in the item code in your
restaur.dat database. */
void  Item_modify()
{
	FILE *file ;
	struct restaurant t ;
	struct restaurant te ;
	FILE *file1 ;
	int   code, valid ;
	char  ch, house='N', conv='N', choice='Y' ;
	char  categ[31];
	char  tprice[10] ;
	float price=0 ;
	clrscr() ;
	do
	{
		gotoxy(72,2) ;
		printf ("Esc=EXIT");
		gotoxy(5,5) ;
		printf ("Enter code of the item : ");
		scanf ("%d",&code) ;
		if (code == 0)
			return ;
		clrscr() ;
		// Steps to find either the billno is exist or not.
		if (!billcode(code))
		{
			gotoxy(30,24) ;
			printf ("\a Record not found");
			getch() ;
			return ;
		}
		display(code) ;
		gotoxy(72,2) ;
		printf ("<0>=EXIT");
		gotoxy(24,2) ;
		printf ("MODIFICATION OF restaurant RECORD");
		do
		{
			statusbar("\a Do you wish to modify this record (y/n) ") ;
			ch = getch() ;
			ch = toupper(ch) ;
			if (ch == '0')
				return ;
			if (ch == 13 )
				ch = 'Y' ;
			if (ch == 27 )
				ch = 'N' ;
		} while (ch != 'Y' && ch != 'N') ;
		if (ch == 'N')
			return ;
		clrscr() ;

		file = fopen("restaur.Dat", "rb+") ;
		while (fread(&t, sizeof(struct restaurant),1,file)==1)
		{
			if (t.itemcode == code)
				break ;
		}

		gotoxy(72,2) ;
		printf ("Esc=EXIT");
		gotoxy(26,2) ;
		printf ("MODIFICATION OF ITEMS");
		lineh(20,59,3,240) ;
		gotoxy(31,4) ;
		printf ("Item Code # %d ",code) ;
		gotoxy(29,5) ;
		printf ("~~~~~~~~~~~~~~~~~~~~~");
		gotoxy(5,8) ;
		printf ("Name         : ");
		gotoxy(5,10) ;
		printf ("Catogray      : .............................");
		lineh(3,78,14,196);
		gotoxy(5,12) ;
		printf ("Price       (Rs) :  .........");
		gotoxy(20,8) ;
		printf ("%s",t.itemname) ;

		do
		{
			valid = 1 ;
			statusbar(" ENTER Category OF THE Item OR PRESS <enter> FOR NO CHANGE") ;
			_setcursortype(_SOLIDCURSOR) ;
			gotoxy(21,9) ;
			printf ("                     ");
			gotoxy(21,10) ;
			getline(categ, 29) ;
			if (categ[0] == '0')
				return ;
			if (strlen(categ) > 30)
			{
				valid = 0 ;
				statusbar("\a Enter correctly (Range: 1..30)") ;
				getch() ;
				_setcursortype(_SOLIDCURSOR) ;
			}
		} while (!valid) ;
		if (strlen(categ) == 0)
		{
			strcpy(categ, t.itemcat) ;
			gotoxy(20,10) ;
			printf ("%s",categ) ;
		}

		do
		{
			valid = 1 ;
			statusbar(" ENTER PRICE OF THE ITEM");
			_setcursortype(_SOLIDCURSOR) ;
			gotoxy(25,12) ;
			clreol() ;
			getline(tprice,9) ;
			price = atof(tprice) ;
			if (price > 100000.0)
			{
				valid = 0 ;
				statusbar("\a SHOULD NOT BE GREATER THAN 100000") ;
				getch() ;
				_setcursortype(_SOLIDCURSOR) ;
			}
		} while (!valid) ;
		if (strlen(tprice) == 0)
		{
			price = t.price ;
			gotoxy(32,12) ;
			printf ("%.2f",price) ;
		}

		strcpy(t.itemcat, categ) ;
		t.itemcode = code ;
		t.price = price ;

		file = fopen("restaur.Dat", "rb+") ;
		file1 = fopen("Tempmod.Dat", "wb+") ;
		while (fread(&te, sizeof(struct restaurant),1,file)==1)
		{
			if (t.itemcode != te.itemcode)
				fwrite(&te, sizeof(struct restaurant),1,file1) ;
			else
				break ;
		}

		fwrite(&t, sizeof(struct restaurant),1,file1) ;
		while (fread(&te, sizeof(struct restaurant),1,file)==1)
			fwrite(&te, sizeof(struct restaurant),1,file1) ;
		fclose(file) ;
		fclose(file1) ;

		file = fopen("restaur.Dat", "wb+") ;
		file1 = fopen("Tempmod.Dat", "rb+") ;
		while (fread(&t, sizeof(struct restaurant),1,file1)==1)
		{
			fwrite(&t, sizeof(struct restaurant),1,file) ;
		}
		fclose(file) ;
		fclose(file1) ;

		gotoxy(5,25) ;
		clreol() ;
		do
		{
			statusbar("\a Do you wish to save (y/n) ") ;
			ch = getch() ;
			ch = toupper(ch) ;
			if (ch == '0')
				return ;
		} while (ch != 'Y' && ch != 'N') ;
		if (ch == 'N')
			return ;
		statusbar(" Record Modified.") ;
		getch() ;
		statusbar("\a Modify any more (y/n) : ") ;
		do
		{
			choice = getch() ;
			choice = toupper(choice) ;
			if (choice == 13)
				choice = 'Y' ;
			if (choice == 27)
				choice = 'N' ;
		} while((choice != 'Y') && (choice !='N'));
	} while(choice == 'Y');
}

// FUNCTION : del
// DESCRIPTION : To Delete A Record In "restaur.Dat"
/* You can delete an item when there is no required or not available in
your restaurant */
void  Item_del()
{
	struct restaurant t ;
	FILE *file ;
	FILE *file1 ;
	char ch ;
	int code ;
	clrscr() ;
	gotoxy(72,2) ;
	printf ("<0>=EXIT");
	gotoxy(5,5) ;
	printf ("Enter code of the ITEM : ");
	scanf ("%d",&code) ;
	if (code == 0)
		return ;
	clrscr() ;
	if (!fcode(code))
	{
		gotoxy(30,24) ;
		printf ("\a Record not found");
		getch() ;
		return ;
	}
	gotoxy(72,2) ;
	printf ("<0>=EXIT");
	gotoxy(23,1) ;
	printf ("DELETION OF THE restaurant RECORD");
	display(code) ;
	do
	{
		statusbar("\a Do you wish to remove this record (y/n) ") ;
		ch = getch() ;
		if (ch == 27)
			return ;
		if (ch == 13)
			ch = 'y' ;
		ch = toupper(ch) ;
		if (ch == '0')
			return ;
	} while (ch != 'Y' && ch != 'N') ;
	if (ch == 'N')
		return ;

	file = fopen("restaur.Dat", "rb+") ;
	file1 = fopen("Tempdel.Dat", "wb+") ;
	while (fread(&t, sizeof(struct restaurant),1,file)==1)
	{
		if (t.itemcode != code)
			fwrite(&t, sizeof(struct restaurant),1,file1) ;
	}
	fclose(file) ;
	fclose(file1) ;

	file = fopen("restaur.Dat", "wb+") ;
	file1 = fopen("Tempdel.Dat", "rb+") ;
	while (fread(&t, sizeof(struct restaurant),1,file1)==1)
	{
		fwrite(&t, sizeof(struct restaurant),1,file) ;
	}
	fclose(file) ;
	fclose(file1) ;

	clrscr() ;
	statusbar("\a Record Deleted") ;
	getch() ;
	statusbar("   Press any key to continue...") ;
	getch() ;
}

// FUNCTION : displaycode
// DESCRIPTION : To Obtain Code For Displaying A Record
void  displaycode()
{
	char  tcat[31] ;
	clrscr() ;
	gotoxy(72,2) ;
	printf ("<0>=EXIT");
	gotoxy(5,5) ;
	_setcursortype(_SOLIDCURSOR) ;
	printf ("Enter Category of the items : ");
	scanf ("%s", tcat) ;
	clrscr() ;
	display1(tcat) ;
	statusbar("   Press any key to continue...") ;
	getch() ;
}

// FUNCTION : showlist
// DESCRIPTION : To Display The List Of restaurants
void  showlist()
{
	struct restaurant t ;
	FILE *file ;
	int row = 6, found=0, flag=0 ;
	int d1, m1, y1 ;
	char ch ;
	struct date d;
	getdate(&d) ;
	d1 = d.da_day ;
	m1 = d.da_mon ;
	y1 = d.da_year ;
	clrscr() ;
	gotoxy(23,2) ;
	printf ("LIST OF ITEMS AS ON %d  . %d  .%d",d1,m1,y1) ;
	lineh(1,80,3,240) ;
	gotoxy(12,4) ;
	printf ("CODE #              NAME                   PRICE");
	gotoxy(1,5) ;
	lineh(11,72,5,205) ;
	linev(4,22,10,186) ;
	linev(4,22,19,186) ;
	linev(4,22,51,186) ;
	linev(4,22,72,186) ;
	lineh(1,80,23,240) ;

	file = fopen("restaur.dat", "rb+") ;
	while (fread(&t, sizeof(struct restaurant),1,file)==1)
	{
		flag = 0 ;
		found = 1 ;
		gotoxy(12,row) ;
		printf ("%d",t.itemcode) ;
		gotoxy(21,row) ;
		printf ("%s",t.itemname) ;
		gotoxy(53,row) ;
		printf ("%.2f",t.price) ;
		if (row == 18)
		{
			flag = 1 ;
			row = 6 ;
			statusbar(" Press any key to continue or Press <ESC> to exit") ;
			ch = getch() ;
			if (ch == 27)
				break ;
			clrscr() ;
			gotoxy(31,2) ;
			printf ("LIST OF ITEMS");
			lineh(1,90,3,240);
			gotoxy(2,4) ;
			printf ("CODE #            NAME                            PRICE");
			gotoxy(1,5) ;
			printf ("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
		}
		else
			row++ ;
	}
	if (!found)
	{
		gotoxy(26,14) ;
		printf ("\a Records not found");
	}
	if (!flag)
	{
		statusbar("   Press any key to continue...") ;
		getch() ;
	}
	fclose (file) ;
}

// FUNCTION : slip
// DESCRIPTION : To Print The Salary Slip Of An restaurant On The Screen
/* This function is used to display the bill of an order by enter the order no.
When you enter the order no. or bill no. a proper bill format with the ordered items
will display on the screen. You can also take its print out by selecting the this
option in PRINT menu. */
void Bill_slip()
{
	FILE *file ;
	struct order t ;
	float total=0, nettotal=0 ;
	long float da = 0;
	int   code, valid=0, try;
	int   year ;
	int row;
	char  tdays[3], thours[4], tadvance[6], month[10] ;
	int d1, m1, y1 ;
	struct date d;
	getdate(&d) ;
	d1 = d.da_day ;
	m1 = d.da_mon ;
	y1 = d.da_year ;
	clrscr() ;
	gotoxy(5,5) ;
	printf ("Enter Bill number  : ");
	scanf ("%d",&code) ;

	if (code == 0)
		return ;

	if (!billcode(code))
	{
		clrscr() ;
		gotoxy(30,25) ;
		printf ("\a Record not found");
		getch() ;
		return ;
	}

	lineh(1,80,1,223) ;
	linev(1,23,1,222) ;
	linev(1,23,79,222) ;
	lineh(1,80,23,223) ;
	// Printing the bill messages
	gotoxy(32,2) ;
	printf ("McDonalds Restaurant");
	lineh(3,78,3,175) ;
	gotoxy (4,4) ;
	printf ("BILL NUMBER : %d",code) ;
	gotoxy (50,4);
	printf ("DATE : ");
	printf ("%d - %d - %d",d1,m1,y1);
	lineh(3,78,5,196) ;
	linev(6,21,22,186) ;
	linev(6,21,37,186) ;
	linev(6,21,55,186) ;
	gotoxy(5,6) ;
	printf ("ITEM NAME");
	gotoxy(30,6) ;
	printf ("PRICE");
	gotoxy(42,6) ;
	printf ("QUANTITY");
	gotoxy(65,6);
	printf ("TOTAL");
	lineh(3,78,7,196) ;
	// Opens the order.dat file to read the records for a particular bill no.
	file = fopen("order.Dat", "rb+") ;
	row = 8;
	while (fread(&t, sizeof(struct order),1,file)==1)
	{
		if (t.billno == code)
		{
			gotoxy(5,row);
			printf ("%s",t.itemname);
			gotoxy(30,row);
			printf ("%.2f",t.price);
			gotoxy(42,row);
			printf ("%d",t.itemqty);
			total = t.itemqty * t.price;
			nettotal = nettotal + total;
			gotoxy(65,row);
			printf ("%.2f",total);
			row++;
		}
	}
	fclose(file) ;

	gotoxy(54,22) ;
	printf (" NET  :  ");
	printf ("%.2f",nettotal) ;
	lineh(3,77,21,196) ;
	gotoxy(2,1) ;
	getch() ;
}
// FUNCTION : print
// DESCRIPTION : To Read The Characters On The Screen & Save It
//               To A Temp Variable And Then Send It To The Printer.

void  print(int x1, int y1, int x2, int y2)
{
	const SEGMENT = 0xB800 ;
	unsigned norow = y2 - y1 + 1, nocol = x2 - x1 + 1 ;
	unsigned i = 0, noele = norow * nocol, *ptr ;
	unsigned row,col,offset;
	unsigned char ch;
	int count = 0 ;
	FILE *prn;
	prn = fopen ("PRN","w");
	ptr = ((unsigned *)malloc(noele) ) ;
	statusbar(" PRINTING PRINTING PRINTING PRINTING PRINTING PRINTING PRINTING PRINTING PRINTI") ;

	for ( row=y1; row<=y2; row++)
	{
		for( col=x1; col<=x2; col++)
		{
			offset = 2*col + 160*row - 162 ;
			ptr[i++] = peek(SEGMENT,offset) ;
		}
	}

	for(i=0; i<noele; i++, count++)
	{
		ch = ptr[i] % 256 ;
		putc (ch,prn) ;
		if (count == 80)
		{
			fputs("\n",prn);
			count = 0 ;
		}
	}
	fclose(prn);
}

// The Main Menu, where the restaurant program starts
void main(void)
{
	main_menu() ;
}


// FUNCTION : statusbar
// DESCRIPTION : To make the status bar at prefixed coordinates at
//               the bottom of the screen.
void statusbar(char m[])
{
	_setcursortype(_NOCURSOR) ;
	window(1,24,80,25) ;
	textcolor(BLACK) ;
	textbackground(WHITE) ;
	cprintf(m) ;
	clreol() ;
	window(1,1,80,24) ;
	textcolor(WHITE) ;
	textbackground(BLACK) ;
}

// FUNCTION : getlinedelchar
// DESCRIPTION : To Delete A Character For Getline

void getlinedelchar(char *s, int col, int p, int *len)
{
	int i ;
	for (i=p; i<len; i++)
		s[i - 1] = s[i] ;
	gotoxy(col + p - 1,wherey()) ;
	len-- ;
	for (i=p - 1; i<len; i++)
		printf ( "%s",s[i]) ;
	printf ( "." );
}

// FUNCTION : getline
// DESCRIPTION : To Add Online Editing For Inputing A Line.
void getline(char *s , int limit)
{
	int i, curx, done, col ;
	col = wherex() ;
	for (i = 0; i<limit; i++)
		printf (".") ;
	gotoxy(col,wherey()) ;
	done = 0 ;
	curx = 0 ;
	i = 0 ;
	do
	{
		char ch = getch() ;
		ch = toupper(ch) ;
		switch (ch)
		{
			case 0 :
				ch = getch();
				switch (ch)
				{
					case 75 : if (curx>0)
						{
							curx-- ;
							gotoxy(wherex()-1,wherey()) ;
						}
						break ;

					case 77 : if (curx<i)
						{
							curx++ ;
							gotoxy(wherex()+1,wherey()) ;
						}
						break ;
					case 83 : if (i>0)
						{
							if (curx<i)
							{
								getlinedelchar(s,col,curx + 1,&i) ;
								gotoxy(col + curx,wherey()) ;
								if (i == 0)
									s[i] = 0 ;
							}
						}
				}
				break ;

			case 8  :
				if (curx>0)
				{
					getlinedelchar(s,col,curx,&i) ;
					gotoxy(col + curx - 1,wherey()) ;
					curx-- ;
					if (i == 0)
						s[i] = 0 ;
				}
				break ;

			case 13 :
				done = 1 ;
				s[i] = 0 ;
				break ;

			case 27 :
				done = 1 ;
				s[0] = '0' ;
				break ;

			default :
				if (i < limit)
				{
					if (curx < i)
					{
						s[curx] = ch ;
						printf ("%c",ch) ;
						curx++ ;
					}
					else
					{
						s[i] = ch ;
						printf ("%c",ch) ;
						i++ ;
						curx = i ;
					}
				}
				else
					s[i] = 0 ;
		}
	} while (!done) ;
	printf ("\n");
}
