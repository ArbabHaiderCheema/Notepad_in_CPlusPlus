#include < iostream >//C++ library
#include < conio.h >//Used to take input from the getch()
#include < windows.h >//Used for the gotoxy function for displaying the data
#include < fstream >//for filing, for saving data into txt file and for reading data from the file
#include < string >//for loading from the txt file
using namespace std;

//(1)8022-(2)8190

//using gotoxy to display the nodes data and the cursor etc
void gotoxy ( int x, int y )
{
	COORD coord;
	coord.X = x; coord.Y = y;
	SetConsoleCursorPosition( GetStdHandle (STD_OUTPUT_HANDLE), coord );
}

//Declaration of structure for node
struct node
{
	char data;// for storing data
	node *up;//for storing address of up node
	node *down;//for storing address of down node
	node *left;//for storing address of left node
	node *right;//for storing address of right node
};

class TwoDDLLADT
{
	//First is used to store the first most node ( the left most and the upmost )
	//while cursor is used for the traversing of the nodes
	node * first, * cursor;
	int x;//for the use of xy-cordinates
	int y;//for the use of xy-cordinates

	public:

	TwoDDLLADT ( );// constructor
	~TwoDDLLADT ( );// destructor

	//
	void Insert ( char );//for getting the input from the keyboard 
	void Print ( );//for printing the nodes in 2D
	void Save ( );//for saving the data with Ctrl+S
	void Load ( );//for loading our data into the nodes accordingly
	void Delete ( );//delete wherever the pointer cursor is pointing.

	// functions control the movement of the pointer cursor
	void Up ( ); 
	void Down ( ); 
	void Left ( );
	void Right ( ); 



	int getx( );//for getting x
	int gety( );//for getting y

	void newline ( );//to handel the enter condition
	void Deleteall( );//for deleting all the nodes
	void saveZ( );
	void revieve( );

};

void TwoDDLLADT::saveZ ( )
{
	//Stream class to write on files
	//has a pointer known as the put pointer that points to the location where the next element has to be written
	ofstream out; 

	out.open("Z.txt");//Open file for output operations.

	if( first != NULL )//checking if any node exists
	{
		//same as print just used out to write into the file instead of cout for displaying at console
		//and endl(\n) to get it to write at the next line 
		node *col = first;
		node *row = first;

		while( row  != NULL )
		{
			while ( col != NULL )
			{
				out<<col -> data;//writting the data part of the column into the file
				col = col -> right;
			}
			row = row -> down;
			col = row;
			
			if(row!=NULL)
			out<<'±';//to take it to the start of the next line, for writing further from next line
		}
		row = NULL;
		col = NULL;
		
	}
	out.close();//At the end, closing our file



}

void TwoDDLLADT::revieve( )
{
	system( "CLS" );
	ifstream in;
	ofstream out;

	
		Deleteall();

	string line;

	Insert(' ');
	node *temp = cursor;

	ifstream myfile ("Z.txt");
	bool check = true;
	if (myfile.is_open())
	{
		while ( getline (myfile,line) )
		{
			int length = line.length();

			for ( int i = 0; i < length ; i++ )
			{
				if ( line [i]!= '±' )
				{
					Insert ( line [i] );
					if( check == false )
					{
						while (cursor ->left != NULL )
							cursor = cursor ->left;
						if ( line[i]=='Ö')
							Delete();
							
						while (cursor ->right != NULL )
							cursor = cursor ->right;
						
						check = true;

					}
				}
				else
				{
					check = false;
					newline( );
				}

			}
		}
    myfile.close();
  }

	cursor = temp;
	x = 0;
	y = 0;

	Delete();
	

}

void TwoDDLLADT::Deleteall( )
{
	while ( first != NULL )
		Delete( );
}

void TwoDDLLADT::Load ( )//for loading the data into the node from txt file
{
	system( "CLS" );
	ifstream in;
	ofstream out;

	
		Deleteall();

	string line;

	Insert(' ');
	node *temp = cursor;

	ifstream myfile ("save.txt");
	bool check = true;
	if (myfile.is_open())
	{
		while ( getline (myfile,line) )
		{
			int length = line.length();

			for ( int i = 0; i < length ; i++ )
			{
				if ( line [i]!= '±' )
				{
					Insert ( line [i] );
					if( check == false )
					{
						while (cursor ->left != NULL )
							cursor = cursor ->left;
						if ( line[i]=='Ö')
							Delete();
							
						while (cursor ->right != NULL )
							cursor = cursor ->right;
						
						check = true;

					}
				}
				else
				{
					check = false;
					newline( );
				}

			}
		}
    myfile.close();
  }

	cursor = temp;
	x = 0;
	y = 0;

	Delete();

}

TwoDDLLADT::TwoDDLLADT ( )
{
	//inatiliazing class members
	first= NULL;
	cursor = NULL;
	x = 0;
	y = 0;
}

TwoDDLLADT::~TwoDDLLADT ( )
{
	//for making cursor equal to the very first node
	cursor = first;

	//for checking if there any node present 
	if ( first != NULL )
	{
		//Outer loop for traversing the downward ( from only the very first node ( the left most ) )
		//until there is no node after that node
		while ( first  != NULL  )
		{
			//moving the cursor to the right most node of the current line ( line which is being traversed ) 
			while ( cursor -> right != NULL )
			{
				cursor = cursor -> right;//making cursor move to the next node
			}

			//As we have traversed cursor to the right most position
			//after that we start deleting the right most node until we reach the left most node
			//on which the first is pointing
			//first we check if there is node at the down of first :
			// *if true we move cursor to left which is pointed by the first ( leftmost node )
			// *then we traverse first to the down node which will also be the leftmost node
			// *then delete the last node of the line
			// *repeating the same process until first down is not true ( there is no node down first )
			//So if there is no node down first
			//**we traverse to the rightmost node
			//**start deleting the node
			//***when we reach first delete first
			//At the last, making first and cursor equal to NULL, So that they dont become dangling pointer 

			if ( cursor != first )//to check if cursor and the first are not pointing at the same node ( which is the leftmost node )
			{
				//traversing the cursor to the leftmost node ( which is pointed by first )
				//if not at first, deleting the node
				while ( cursor != first )
				{
					//declaring a pointer del (deleting pointer)
					//to do deleting by giving it the adress of the node which is being pointed by cursor
					//then traversing cursor towards the left
					//repeating this process until cursor is not equal to the leftmost node ( node pointed by first )
					node *del = cursor;
					cursor = cursor -> left; 
					delete del;
					del = NULL;
				}
				
				

				//traversing the first to the node under it 
				//which will also be the left most node its own line
				first = first ->down;

				
				//deleting the node which was the leftmost node of the previous node
				delete cursor;
				cursor = first;// again making cursor equal to the first
			}
			else
			{
				//when there is only leftmost node remaining ( All other nodes in the line are deleted ) checking for a node down it 
				//if there is node down it move first down to the next line's leftmost node
				// delete the previous node
				if ( first -> down != NULL )
				{
					cursor = first;
					first = first -> down;
					delete cursor;
					cursor = first;
				}
				else if ( first -> down == NULL )//if first is the only one node remaing, delete it. After that making the pointer NULL 
				{

					delete first;
					cursor = NULL;
					first = NULL;
				}			
			}
		}	
	}

}

void TwoDDLLADT::Insert ( char c )
{
	
	//for insertion for the very first time
	if( first == NULL && cursor == NULL )
	{
		first = new node;
		first->data = c;

		first->up = first->down = first->left = first->right = NULL;
		cursor = first;
		//x++;
	}//insertion first ending bracket
	else if ( cursor->data== 'Ö' )
	{
		cursor->data=c;
	}
	else if ( cursor -> left == NULL && cursor->right != NULL)//for inserting at first
	{
		
		node *copy = new node;
		copy -> data = c;
		copy -> up = copy -> down = copy -> left = copy -> right = NULL;

		

		cursor ->left = copy;
		copy ->right = cursor;

		if( cursor ==first )
		{
			
			first = cursor ->left;
		}

		node *up = NULL;
		node *down = NULL;

		if ( cursor->up !=NULL )
			up = cursor -> up;

		

		if ( cursor ->down != NULL )
			down = cursor -> down;

		node *temp = copy;

		bool check = true;

		if ( cursor -> up != NULL )
		{
			while ( check )
			{
				if ( up  != NULL  && temp != NULL )
				{
					up -> down = temp;
					temp ->up = up;
				}
				else if ( up   != NULL  && temp  == NULL ) 
				{
					up -> down = NULL;
				}
				else if ( up   == NULL  && temp  != NULL ) 
				{
					temp ->up = NULL;
				}
				else if ( up   == NULL  && temp  == NULL )
				{
					check = false;
				}

				if ( up  != NULL )
				up = up -> right;

				if ( temp  != NULL )
				temp = temp ->right;
			}
			
		}

		bool check2 = true;

		temp = copy;

		if ( cursor -> down != NULL )
		{
			while ( check2 )
			{
				if ( down != NULL  && temp != NULL )
				{
					down -> up = temp;
					temp ->down = up;
				}
				else if ( up   != NULL  && temp  == NULL ) 
				{
					down -> up = NULL;
				}
				else if ( up   == NULL  && temp  != NULL ) 
				{
					temp ->down = NULL;
				}
				else if ( up   == NULL  && temp == NULL )
				{
					check2 = false;
				}

				if ( down  != NULL )
				down = down -> right;

				if ( temp  != NULL )
				temp = temp ->right;
			}
			
		}

		cursor;
		x++;
		
	
	
	}
	else if( cursor -> right == NULL)//for insertion at the last
	{	
		//decalaring a node by pointer copy
		//NULLing its all links ( up, down, left, right)
		node *copy = new node;
		copy -> data = c;
		copy -> up = copy -> down = copy -> left = copy -> right = NULL;

		//As our cursor will be the last node of its line,
		//which means its right part will be NULL
		//so we assign the address of the newly created node to its right link
		//and also assign the new nodes left link to the last node
		cursor -> right = copy;
		copy -> left = cursor;
		copy -> right = NULL;//as it is to be the last node

		//Now as the connection is complete we NULL the copy pointer  
		copy = NULL;
		
		//Traversing cursor to the right node ( right most newly created node )
		cursor = cursor -> right;
		
		//if condition for checking by example:
		// 1	2	3
		// 4	5	*
		// 7	8	9
		// 1) first checking if the node at the position 2 exists ( cursor ->left -> up )
		//		and then at checking at 3 position ( cursor ->left -> up -> right )
		// 2) if true assign the down link of the 3 position to the *
		// 3) after 2) assign the * up link to the 3 position
		// and vice versa for the position 9
		// here * is our newly inserted node which is being pointed by cursor

		if ( cursor ->left -> up && cursor ->left -> up -> right  )
		{
			
				cursor -> left -> up -> right -> down = cursor;// point (3)
				cursor -> up = cursor ->left -> up -> right; // point (2)
			
		}

		if ( cursor ->left -> down && cursor ->left -> down -> right  )
		{	
															  
				cursor -> left -> down -> right -> up = cursor;  
				cursor -> down = cursor -> left -> down -> right;
			
		}


		x++;//incrementing x for gotoxy function
		
	}//insertion last ending bracket
	else if ( cursor -> right != NULL )//for insertion at the middle
	{

		//creating a newnode by the use of newnode pointer
		node *newnode = new node;
		newnode->data = c;
		newnode->left = newnode->right = newnode->down = newnode->up =  NULL;

		//creating a link b/w the newnode and node before it, which is being pointed by cursor
		newnode -> right = cursor -> right;
		cursor -> right -> left = newnode;

		//creating a link b/w the newnode and node befoe it
		newnode -> left = cursor;
		cursor -> right = newnode;
		
		//after linking new node is not needed any more, so making it NULL
		newnode = NULL;

		//if there is a line below the cursor
		if ( cursor -> down != NULL )
		{
			//creating a pointer low to create link after the insertion
			node *low = cursor -> down;

			//if there is a lower  line then :
			// 1	2	*	4	5
			// 6	7	8	9	10
			// 1)first creating  uplink b/w * and 8 by traversing from 7
			// 2)then creating downlink b/w * and 8 by traversing from 7
			// In above explanation * is the middle node
			//----------------------------------------------------------
			//NOTE : vice versa for uplinking

			while ( low -> right != NULL )//traverse to the end of the line, for creating new links after insertion
			{
				if ( low -> right -> up != NULL )
				{
					low -> right -> up = low -> up -> right;
					low -> up -> right -> down = low -> right;
				}
				else
				{
					low -> right -> up = NULL;
				}
				low = low -> right;
			}
			
		}

		//checking if there is a upline above the cursor
		if ( cursor -> up != NULL )
		{
			node *up = cursor -> up;
			while ( up -> right != NULL )
			{
				if ( up -> right -> down != NULL  )
				{
					up -> right -> down = up -> down -> right;
					up -> down -> right -> up = up -> right;
				}
				else
				{
					up -> right -> up = NULL;
				}
				up = up -> right;
			}
			
			
		}

	}
	
}

void TwoDDLLADT::Print ( )
{
	if ( first != NULL )//checking if there is any node
	{
		//As our nodes are in 2D structure
		//So we make two pointer
		//one for traversing row
		//second for traversing column
		node *col = first;
		node *row = first;

		//Using x1 & y1 integer variable to print by notepad
		int x1=0;
		int y1=0;

		//Using two loops same as for 2D array
		//outer for row
		//innner for columns
		while( row  != NULL )//traversing until there is no row
		{		
			while ( col != NULL )//traverse until there is no column
			{
				gotoxy(x1,y1);//gotoxy for start printing from the start
				
				if( col->data != 'Ö' )
					cout << col -> data;//for displaying the data at the given gotoxy co-ordinate 
				
				col = col -> right;//traversing column further
				if ( x1 < 79 )
				x1++;//incrementing the x1, as it is for columns
			}
			row = row -> down;//traversing row further
			col = row;//to start from the firts column of the line
			y1++;//incementing the y1, as it is for row
			x1 = 0;//making the columsn zero for gotoxy
		}
		//Nulling the pointers for precaution
		row = NULL;
		col = NULL;
	}
}

void TwoDDLLADT::Save ( )
{
	//Stream class to write on files
	//has a pointer known as the put pointer that points to the location where the next element has to be written
	ofstream out; 

	out.open("save.txt");//Open file for output operations.

	if( first != NULL )//checking if any node exists
	{
		//same as print just used out to write into the file instead of cout for displaying at console
		//and endl(\n) to get it to write at the next line 
		node *col = first;
		node *row = first;

		while( row  != NULL )
		{
			while ( col != NULL )
			{
		
				out<<col -> data;//writting the data part of the column into the file
				
				col = col -> right;
			}
			row = row -> down;
			col = row;
			
			if( row!=NULL )
			out<<'±';//to take it to the start of the next line, for writing further from next line
		}
		row = NULL;
		col = NULL;
		
	}
	out.close();//At the end, closing our file
	
}

void TwoDDLLADT::Delete ( )
{
	if ( first != NULL )//checking if there is any node
	{		
			if ( cursor -> left == NULL && cursor ->right== NULL )//deleting a only-left node of the line
			{
				if ( cursor -> up == NULL && cursor -> down == NULL )//if there is no node above and below it, meams it is the only node
				{
					delete cursor ;
					cursor = NULL;
					first = NULL;
					
				}
				else if ( cursor -> up != NULL && cursor -> down == NULL )//if there is a line above the node
				{
					node *up = cursor ->up;

					delete cursor;

					cursor = up;

					while ( cursor ->right != NULL )
					{
						cursor= cursor->right;
						x++;
					}
					y--;

					while ( up != NULL )
					{
						up -> down = NULL;
						up = up -> right;
					}
				
					up = NULL;
				}
				else if ( cursor -> up == NULL && cursor -> down != NULL )//if there is a line below the node
				{
					node *low = cursor -> down;

					if ( cursor == first )
						first = low;

					delete cursor;

					cursor = low;
					
					while ( low != NULL )
					{
						low -> up = NULL;
						low = low -> right;
					}
					low = NULL;
				}
				else if ( cursor -> up != NULL && cursor -> down != NULL )//if there is a line above and below the node
				{
					node *low = NULL;
					node *up = NULL;	
					
					
						low = cursor -> down;
					
						up = cursor -> up;
					

					
						up -> down = low;
						low -> up = up;
					

					delete cursor;


						cursor = up;

						y--;
					
					bool check = true;
					while ( check )
					{
						if ( up != NULL && low != NULL )
						{
							up -> down = low;
							low -> up = up;
						}
						else if ( up  == NULL && low  == NULL )
						{
							check = false;
						}
						else if ( up  == NULL )
						{
							low -> up = NULL;
						}
						else if ( low  == NULL )
						{
							up -> down = NULL;
						}

						if( up  != NULL )
						up = up -> right;

						if( low  != NULL )
						low = low -> right;
						
					}
					up = NULL;
					low = NULL;
					
				}
					
				
			}
			else if ( cursor -> left != NULL && cursor -> right == NULL )//for deleting the last node
			{
				if ( cursor -> up != NULL )//if node aboce it exists
				{
					cursor -> up -> down = NULL;
				}

				if ( cursor -> down )//if node below it exists
				{
					cursor -> down -> up = NULL;
				}

				node *temp = cursor -> left;
				temp -> right = NULL;
				delete cursor;
				cursor = temp;
				x--;

			}
			else if ( cursor -> left == NULL && cursor -> right != NULL  )//for deletion at first character of the filled line
			{
				
				if ( cursor -> up == NULL && cursor -> down == NULL )//if there is no node above and below it
				{
					first = cursor -> right;
					first -> left = NULL;
					delete cursor;
					cursor = first;
				}
				else if ( cursor -> up != NULL && cursor -> down == NULL )//if there is node above it
				{
					node *up = cursor -> up;
					node *temp = cursor;
					cursor = cursor -> right;
					cursor -> left = NULL;
					delete temp;

					temp = cursor;

					bool check = true;
					while ( check )//while loop for traversing up and temp parallel to establish there links accordingly 
					{
						if ( up != NULL && temp != NULL )
						{
							up -> down = temp;
							temp -> up = up;	
						}
						else if ( up == NULL && temp != NULL )
						{
							temp -> up = NULL;
						}
						else if ( up != NULL && temp == NULL )
						{
							up ->down = NULL;
						}
						else if ( up == NULL && temp == NULL )
						{
							check = false;
						}

						if ( up  != NULL )
							up = up ->right;

						if ( temp != NULL )
							temp = temp ->right;	
					}

					
				}
				else if ( cursor -> up == NULL && cursor -> down != NULL )//if there is node below it
				{
					node *down = cursor -> down;
					node *temp = cursor;
					cursor = cursor -> right;


					cursor -> left = NULL;

					if ( temp == first )
						first = first ->right;

					delete temp;
					temp = cursor;

					bool check = true;
					while ( check )//while loop for traversing down and temp parallel to establish there links accordingly 
					{
						if ( down != NULL && temp != NULL )
						{
							down -> up = temp;
							temp -> down = down;	
						}
						else if ( down == NULL && temp != NULL )
						{
							temp -> down = NULL;
						}
						else if ( down != NULL && temp == NULL )
						{
							down -> up = NULL;
						}
						else if ( down == NULL && temp == NULL )
						{
							check = false;
						}

						if ( down  != NULL )
							down = down ->right;

						if ( temp != NULL )
							temp = temp ->right;	
					
					
					}	


					
				}
				else if ( cursor -> up != NULL && cursor -> down != NULL )//if there is node above and below it
				{
					//In this we use both while of up and down to extablish linking
					node *down = cursor -> down;
					node *temp = cursor;
					node *up = cursor->up;

					cursor = cursor -> right;
					cursor -> left = NULL;

					if(temp == first)
						first = first ->right;

					delete temp;
					temp = cursor;

					bool check = true;
					while ( check )//while loop for traversing down and temp parallel to establish there links accordingly 
					{
						if ( down != NULL && temp != NULL )
						{
							down -> up = temp;
							temp -> down = down;	
						}
						else if ( down == NULL && temp != NULL )
						{
							temp -> down = NULL;
						}
						else if ( down != NULL && temp == NULL )
						{
							down -> up = NULL;
						}
						else if ( down == NULL && temp == NULL )
						{
							check = false;
						}

						if ( down  != NULL )
							down = down ->right;

						if ( temp != NULL )
							temp = temp ->right;	
					
					
					}

					
					temp = cursor;

					bool check2 = true;
					while ( check2 )//while loop for traversing up and temp parallel to establish there links accordingly 
					{
						if ( up != NULL && temp != NULL )
						{
							up -> down = temp;
							temp -> up = up;	
						}
						else if ( up == NULL && temp != NULL )
						{
							temp -> up = NULL;
						}
						else if ( up != NULL && temp == NULL )
						{
							up ->down = NULL;
						}
						else if ( up == NULL && temp == NULL )
						{
							check2 = false;
						}

						if ( up  != NULL )
							up = up ->right;

						if ( temp != NULL )
							temp = temp ->right;	
					}
				
				
				up = NULL;
				temp = NULL;
				down = NULL;

					
				}

				
			}
			else //for deletion at middle
			{
				node *up = cursor -> up;
				node *down = cursor -> down;

				cursor -> right -> left = cursor -> left;
				cursor -> left -> right = cursor -> right; 
				
				node *temp = cursor;

				cursor = cursor -> right;
				
				delete temp;
				temp = NULL;

				temp = cursor;

					
				while ( up != NULL )
				{
					if ( temp !=NULL )
					{
						up -> down = temp;
						temp -> up = up;
					}
					else
					up -> down = NULL;

					if ( temp != NULL )
					temp = temp ->right;

					up = up -> right;
				}

				temp = cursor;

				while ( down != NULL )
				{
					if ( temp !=NULL )
					{
						down -> up = temp;
						temp -> down = down;
					}
					else
					down -> up = NULL;

					if ( temp != NULL )
					temp = temp ->right;	

					down = down -> right;
				}

				temp = NULL;

				
			}

	}

}

void TwoDDLLADT::Up ( )//for moving the cursor above if there is a line above its current line
{
	if ( cursor != NULL)//checking if cursor is not equal to NULL
	{
		if( cursor -> up != NULL ) //checking if cursor -> up exixts
		{
			/*if(y!=0)
			{*/
				cursor = cursor -> up;//traverse cursor towards up
				if( y >0 )
				{
					y--;//decrementing y, for previous row
				}
				gotoxy(x,y);//using gotoxy for displaying thecurrent loctaion off the cursor
			/*}*/
		}
		else
		{
			node *temp = cursor;

			while ( temp ->left != NULL )
			{
				temp = temp->left;
			}

			if( temp ->up != NULL )
			{
				temp = temp->up;

				x=0;

				while ( temp->right!= NULL )
				{

					temp=temp->right;
					x++;
				}
				
				cursor = temp;
				y--;
			
			}
		
		}
	}
}

void TwoDDLLADT::Down ( )
{
	if ( cursor != NULL)
	{
		if ( cursor -> down!= NULL)
		{
			cursor = cursor -> down;
			y++;
			gotoxy(x,y);
		}
		else
		{
			node *temp = cursor;
			
			while ( temp ->left != NULL )
			{
				temp = temp ->left;
			}

			if ( temp ->down != NULL)
			{
				temp = temp ->down;

			}

			cursor = temp;
			x=0;
			y++;
		}
	}
}

void TwoDDLLADT::Left ( )
{
	if ( cursor != NULL)
	{
		if( cursor -> left != NULL )
		{
			if(x>=0)
			{
				cursor = cursor -> left;
				x--;
				gotoxy(x,y);
			}
		}
		else 
		{
			node *temp = cursor;

			while ( temp ->left != NULL )
			{
				temp = temp ->left;
			}

			

			if ( temp -> up != NULL )
			{
				temp = temp ->up;
				x=0;
				while (temp ->right != NULL)
				{x++;
					temp = temp ->right;
					
				}

				cursor =temp;
				y--;
			}
		
		
		}
	}
}

void TwoDDLLADT::Right ( )
{
	if ( cursor != NULL)
	{
		if( cursor -> right != NULL )
		{
			//if(x<79)
			//{
				cursor = cursor -> right;
				x++;
				gotoxy(x,y);
			//}
		}
		else
		{
			node *temp = cursor;
			while ( temp ->left != NULL )
			{
				temp = temp ->left;
			}
			if ( temp ->down != NULL ) 
			{
				cursor = temp ->down;
				x=0;
				y++;
			}
		
		
		}
	}
}

void TwoDDLLADT::newline ( )
{
	if ( cursor != NULL )
	{
		if ( cursor -> left  != NULL && cursor -> right == NULL )// for enter at the end of the line to create a newline
		{
			bool down = false;

			while ( cursor -> left != NULL )
			{
			
				if ( cursor -> down != NULL )
				{
					down = true;
					if ( cursor -> left -> down ->left /*!= NULL*/ )
					{
						cursor -> down = NULL;
					}
				}
				cursor = cursor -> left;
			}

			if ( down == true )
			{
				node *down = cursor -> down;
				
				node *first_down = down;

				while ( down -> right != NULL )
				{
					down -> up = NULL;
					down = down -> right;
				}

				down = NULL;

					node *newnode = new node;
					newnode -> data = 'Ö';
					newnode -> up = newnode -> down = newnode -> left = newnode -> right = NULL;

					first_down -> up = newnode;
					newnode -> down = first_down;

					cursor -> down = newnode;
					newnode -> up = cursor;

					cursor = newnode;
					newnode = NULL;

					x = 0;
					y++;
			}
			else
			{
				node *newnode = new node;
				newnode -> data = 'Ö';
				newnode -> up = newnode -> down = newnode -> left = newnode -> right = NULL;

				cursor ->down = newnode;
				newnode -> up = cursor;

				cursor = newnode;
				newnode = NULL;

				x = 0;
				y++;
			}
		}
		else if ( cursor -> left != NULL && cursor -> right != NULL )
		{
			node *temp = cursor;
			node *cposition = cursor;
			

			while ( temp ->left != NULL )
			{
				temp = temp ->left;	
			}

			node *fc = temp;

			
			node *down = fc->down;

			if ( cursor -> up != NULL )
			{
				node *up = cursor ->up;
				while ( up != NULL )
				{
					up -> down = NULL;
					up = up ->right;
				}
			}

			cursor -> left -> right = NULL;
			cursor -> left = NULL;
			
			bool track = true;

			while( track )
			{
				if ( temp != NULL && cposition != NULL )
				{
					cposition -> up = temp;

				}
				else if ( temp == NULL && cposition != NULL  )
				{
					cposition ->up = NULL;
				}
				else if ( temp == NULL && cposition == NULL  )
				{
					track = false;
				}

				if ( temp != NULL )
					temp = temp ->right;

				if ( cposition != NULL )
					cposition = cposition ->right;
				
			}

			track = true;
			cposition = cursor;
			temp = fc;

			while ( track )
			{
				
					if ( temp != NULL && cposition != NULL )
					{
						if ( temp != NULL )
						{
							cposition ->down=temp ->down;
							temp ->down = cposition;
							cposition ->up = temp;
						}
						else
						{ 
							cposition ->down = NULL;
							temp ->down = cposition;
						}
					}
					else if ( temp == NULL && cposition != NULL )
					{
						cposition ->up = NULL;
					}
					else if ( cposition == NULL && temp != NULL )
					{
						temp ->down = NULL;	
					}
					else if ( cposition == NULL && temp == NULL )
					{
						track = false;
					}

					if ( temp != NULL )
						temp = temp ->right;

					if ( cposition != NULL )
						cposition = cposition ->right;
					
			}

			track = false;
			cposition = cursor;

			if ( down != NULL )
			{
				while( track)
				{
					if (down != NULL && cposition != NULL )
					{
						down ->up = cposition;
						cposition ->down = down;
					}
					else if ( down == NULL && cposition != NULL )
					{
						cposition ->down = NULL;
					}
					else if ( down != NULL && cposition == NULL )
					{
						down ->up = NULL;
					}
					else if ( down == NULL && cposition == NULL ) 
					{
						track = false;
					}
			
					if ( cposition != NULL )
						cposition = cposition ->right;

					if ( down != NULL )
						down = down ->right;
			
				}

				
			}

			x = 0;
			
			
		}
		


	}
	

	
}

int TwoDDLLADT::getx ( )
{
	return x;
}

int TwoDDLLADT::gety ( )
{
	return y;
}

int main()
{
	TwoDDLLADT obj;
	
	char key = ' ';
	bool check = true;
	bool wheel = true;

	 system("color 5E");

	while(wheel)
	{
		key = getch();

		if(key == -32)// for those keys that generate two keys -32 after that another key accorrding to key pressed
		{
			key= getch();
			if(key == 'H')
			obj.Up( );
			if(key == 'K')
			obj.Left( );	
			if(key == 'M')
			obj.Right( );	
			if(key == 'P')
			obj.Down( );
			if(key== 'S')
			obj.Delete( );

		}
		else if ( key == 13 )// enter statement 
		{
			obj.newline( );
			check =true;
		}
		else if ( key == 8  )// for back-space
		{
			check = false;
			obj.Delete ( );
		}
		else if ( key == 27 )// for escape to exit
		{
			wheel = false;
		}
		else if ( key == 19 )// ctrl+s for save 
		{
			obj.Save();
		}
		else if ( key == 12 )
		{
			obj.Load( );
		}
		else if ( key == 26 )
		{
			obj.revieve( );
		}
		else if ( key == 4 )//for control Z// 4 is for control D delete all
		{
			obj.saveZ ( );
			check = false;
			obj.Deleteall();
		}
		else 
		{
			if ( key >= 32 && key <= 126 )// to filter the input
			{
				obj.Insert( key );
			}
			else if ( key == 9 )// statement for tab
			{
				for(int i=0; i<3 ;i++ )			
				obj.Insert(' ');
			}
		}

		if ( check != false )
		{
			obj.saveZ ( );
		}
		
		system("CLS");// for clearing the screen
		obj.Print();// for printing the nodes
		gotoxy(obj.getx ( ),obj.gety ( ));
	}

	system("pause");

return 0;}