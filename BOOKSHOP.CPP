#include<dir.h>
#include<dos.h>
#include<bios.h>
#include<conio.h>
#include<string.h>
#include<fstream.h>
#include<iomanip.h>
#include<graphics.h>
#include<iostream.h>
#include<stdio.h>
#include<stdlib.h>

char knodes[100][100];
int count = 0;

class Book
{
	public:
	char isbn[20], bname[30], author[30], publr[30], pyear[10], genre[30], stock[5];
	Book()
	{
	  isbn[0]=0;
	  bname[0]=0;
	  author[0]=0;
	  publr[0]=0;
	  pyear[0]=0;
	  genre[0]=0;
	  stock[0]=0;
	}

	void Input();
	void Modify();
	void Display();
	void Assign();
	void Delete();
	void Index();
	void KeySort();
	void Indexdisplay(int );
	int  Binary(char*);
	void Secondary();
	void SecondSort();
	void Secondsearch(char*);
	void Invertprimary();
	void Invertsecondary();
	void Invertsecondarysort();
	void InvertSecondarySort();
	void CheckDup();
	int  InvertSecondSearch(char *);
};

int search(char*);

void pack(Book &b, fstream &file)
{
	int pos;
	int i,n;
	char buffer[140];

	/*for(i=0; i<140; i++)
	{
		buffer[i] = ' ';
	}
	*/
	strcpy(buffer, b.isbn);		strcat(buffer, "|");
	strcat(buffer, b.bname);	strcat(buffer, "|");
	strcat(buffer, b.author);	strcat(buffer, "|");
	strcat(buffer, b.publr);	strcat(buffer, "|");
	strcat(buffer, b.pyear);	strcat(buffer, "|");
	strcat(buffer, b.genre);	strcat(buffer, "|");
	strcat(buffer, b.stock);	strcat(buffer, "|");

	i = strlen(buffer);
	n = sizeof(buffer);

	for(;i<n; i++)
		buffer[i] = '_';
	buffer[i-1] = '#';
	buffer[i]='\0';

	file<<buffer;
}


int unpack(Book &b, fstream &file)
{
	char dummy[140];

	file.getline(b.isbn, 20, '|');
	if(file.eof())
		return 0;
	file.getline(b.bname, 30, '|');
	file.getline(b.author, 30, '|');
	file.getline(b.publr, 30, '|');
	file.getline(b.pyear, 10, '|');
	file.getline(b.genre, 30, '|');
	file.getline(b.stock, 10, '|');
	file.getline(dummy, 140, '#');
	return 1;
}


void Book::Input()
{
	int k,value;
	Book a;
	fstream file;
	clrscr();
	cout<<"\n\t--------------------------------------------------\n\n";
	cout<<"\n\tENTER THE ISBN NUMBER     :";;
	gets(isbn);
	while(search(isbn)==1)
	{
		cout<<"\n\nDuplicate Entry Re-Enter The URN Value: ";;
		cin>>isbn;
	}
	 cout<<"\n\tENTER THE BOOK NAME	      :";
	 gets(bname);
	 cout<<"\n\tENTER THE AUTHOR   	      :";
	 gets(author);
	 cout<<"\n\tENTER THE PUBLISHER	      :";
	 gets(publr);
	 cout<<"\n\tENTER THE YEAR     	      :";
	 gets(pyear);
	 cout<<"\n\tENTER THE GENERE   	      :";
	 gets(genre);
	 cout<<"\n\tENTER THE STOCK    	      :";
	 gets(stock);

	 file.open("list.txt",ios::app);
	 if(!file)
	 {
		cout<<endl<<"Unable to open file";
		getch();
		exit(0);
	 }
	 pack(*this,file);
	 file.close();
}

void Book::Modify()
{
	char key[20];
	int size=0,found=0;
	clrscr();
	cout<<"\n\tENTER THE SEARCH KEY(ISBN): ";
	cin>>key;
	fstream file("LIST.txt",ios::in|ios::out|ios::ate|ios::binary);
	file.seekg(0,ios::beg);
	while(unpack(*this,file))
	{
	    if(strcmpi(isbn,key)==0)
	    {
			found=1;
			break;
	    }
	    size=size+140;
	}

	if(found==1)
	{
		char choice[10];
		cout<<"\n\n\t\t\t\tRecord is found ...."<<endl<<endl;
		cout<<"\n\t\t\tDetails Of Record";
		cout<<"\n\t\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\n\n";
		cout<<"\n\t\t\tISBN      :"<<isbn<<endl;
		cout<<"\n\t\t\tNAME     :"<<bname<<endl;
		cout<<"\n\t\t\tAUTHOR  :"<<author<<endl;
		cout<<"\n\t\t\tPUBLISHER :"<<publr<<endl;
		cout<<"\n\t\t\tYEAR   :"<<pyear<<endl;
		cout<<"\n\t\t\tGENRE   :"<<genre<<endl;
		cout<<"\n\t\t\tSTOCK   :"<<stock<<endl;
		cout<<"\n\n\t\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\n\n";

		file.seekg(0, ios::beg);


		cout<<"\nDo You Want To Update ISBN(Y/N)       :";
		cin>>choice;
	    if(choice[0]=='y'||choice[0]=='Y')
	    {
		 cout<<"\n\t\tENTER THE ISBN           :";
		 cin>>isbn;
	    }

	    cout<<"\nDO You Want To Update BOOK NAME(Y/N)  :";
	    cin>>choice;
	    if(choice[0]=='y'||choice[0]=='Y')
	    {
		 cout<<"\n\t\tENTER THE BOOK NAME     :";
		 cin>>bname;
	    }

	    cout<<"\nDO You Want To Update AUTHOR(Y/N)     :";
	    cin>>choice;

	    if(choice[0]=='y'||choice[0]=='Y')
	    {
		  cout<<"\n\t\tENTER THE AUTHOR       :";
		  cin>>author;
	    }
	    cout<<"\nDO You Want To Update PUBLISHER(Y/N) :";
	    cin>>choice;

	    if(choice[0]=='y'||choice[0]=='Y')
	    {
		cout<<"\n\t\tENTER THE PUBLISHER    :";
		cin>>publr;
	    }
	    cout<<"\nDO You Want To Update YEAR(Y/N)       :";
	    cin>>choice;

	    if(choice[0]=='y'||choice[0]=='Y')
	    {
		  cout<<"\n\t\tENTER THE YEAR         :";
		  cin>>pyear;
	    }

	    cout<<"\nDO You Want To Update GENRE(Y/N)     :";
	    cin>>choice;

	    if(choice[0]=='y'||choice[0]=='Y')
	    {
		  cout<<"\n\t\tENTER THE GENRE        :";
		  cin>>genre;
	    }

	    cout<<"\nDO You Want To Update STOCK(Y/N)     :";
	    cin>>choice;

	    if(choice[0]=='y'||choice[0]=='Y')
	    {
		  cout<<"\n\t\tENTER THE STOCK        :";
		  cin>>stock;
	    }

	    file.seekp(size);
	    pack(*this, file);

	 }

    else
		cout<<setw(40)<<"\n\n\n\t\t\tRecord Not Found ....\n";

     file.close();
     getch();
}

/* Display function */

void Book :: Display()
{
	fstream file("list.txt",ios::in);
	if(!file)
	{
			clrscr();
			cout<<"\n\n\t\t\t\tRecord is not found ...."<<endl<<endl;
			getch();
			return;
	}
	file.seekg(0,ios::beg);
	while(unpack(*this,file))
	{
	   clrscr();
	   cout<<" "<<endl<<endl;
	   cout<<setw(25)<<" "<<"   DISPLAYING RECORD'S"<<endl<<endl;
	   for(int i=0;i<80;i++)   cout<<'*';   cout<<endl<<endl<<endl;
	   cout<<setw(20)<<" "<<"     ISBN NUMBER    :  "<<isbn<<endl<<endl;
	   cout<<setw(20)<<" "<<"     BOOK NAME      :  "<<bname<<endl<<endl;
	   cout<<setw(20)<<" "<<"     AUTHOR         :  "<<author<<endl<<endl;
	   cout<<setw(20)<<" "<<"     PUBLISHER      :  "<<publr<<endl<<endl;
	   cout<<setw(20)<<" "<<"     YEAR           :  "<<pyear<<endl<<endl;
	   cout<<setw(20)<<" "<<"     GENRE          :  "<<genre<<endl<<endl;
	   cout<<setw(20)<<" "<<"     STOCK          :  "<<stock<<endl<<endl<<endl;
	   for(i=0;i<80;i++) cout<<'*';
	   getch();
	}

	if(!(unpack(*this,file)))
	{
	   cout<<endl<<endl<<endl<<endl<<setw(40)<<"NO RECORDS FOUND ....";
	   getch();
	   return;
	}

	file.clear();
	file.close();
}

/*Function to search a key */

int search(char *key)
{
	int found=0;
	Book b1;
	fstream file("list.txt",ios::in||ios::out);
	file.seekg(0,ios::beg);
	while(unpack(b1,file))
		if(strcmpi(b1.isbn,key)==0)
			found=1;
	file.close();
	return found;
}

/*Assign function*/

void Book :: Assign()
{
	char key[20];
	int size=0,found=0;
	clrscr();
	cout<<"\n\tENTER THE SEARCH KEY  :";
	cin>>key;
	fstream file("list.txt",ios::app|ios::in|ios::out|ios::ate|ios::binary);
	file.seekg(0,ios::beg);
	while(unpack(*this,file))
	{
	    if(strcmpi(isbn,key)==0)
	    {
		   found=1;
		   break;
	    }
	    size=size+75;
	}
	if(found==1)
	{
	  char choice[10];
	  cout<<"\n\n\t\t\t\tRecord is found ...."<<endl<<endl;
	  cout<<"\n\t\t\tDetails Of Record";
	  cout<<"\n\t\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\n\n";
	  cout<<"\n\t\t\tISBN      :"<<isbn<<endl;
	  cout<<"\n\t\t\tNAME     :"<<bname<<endl;
	  cout<<"\n\t\t\tAUTHOR  :"<<author<<endl;
	  cout<<"\n\t\t\tPUBLISHER :"<<publr<<endl;
	  cout<<"\n\t\t\tYEAR   :"<<pyear<<endl;
	  cout<<"\n\t\t\tGENRE   :"<<genre<<endl;
	  cout<<"\n\t\t\tSTOCK   :"<<stock<<endl;
	  cout<<"\n\n\t\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\vs\v\v\v\v\v\v\v\v\v\v\v\v\v\n\n";

	  cout<<"\n\t\tENTER THE ISBN NUMBER    :";
	  cin>>isbn;

	  while(search(isbn)==1)
	  {
		cout<<"\n\nDuplicate Entry Re-Enter The URN Value  :";
		cin>>isbn;
	  }

	  cout<<"\n\t\tENTER THE BOOK NAME      :";
	  cin>>bname;

	  cout<<"\nDO You Want To Update AUTHOR(Y/N)     :";
	  cin>>choice;

	  if(choice[0]=='y'||choice[0]=='Y')
	  {
		  cout<<"\n\t\tENTER THE AUTHOR       :";
		  cin>>author;
	  }
	  cout<<"\nDO You Want To Update PUBLISHER(Y/N) :";
	  cin>>choice;

	  if(choice[0]=='y'||choice[0]=='Y')
	  {
		 cout<<"\n\t\tENTER THE PUBLISHER    :";
		 cin>>publr;
	  }
	  cout<<"\nDO You Want To Update YEAR(Y/N)       :";
	  cin>>choice;

	  if(choice[0]=='y'||choice[0]=='Y')
	  {
		  cout<<"\n\t\tENTER THE YEAR         :";
		  cin>>pyear;
	  }

	  cout<<"\nDO You Want To Update GENRE(Y/N)     :";
	  cin>>choice;

	  if(choice[0]=='y'||choice[0]=='Y')
	  {
		  cout<<"\n\t\tENTER THE GENRE        :";
		  cin>>genre;
	  }

	  cout<<"\nDO You Want To Update STOCK(Y/N)     :";
	  cin>>choice;

	  if(choice[0]=='y'||choice[0]=='Y')
	  {
		  cout<<"\n\t\tENTER THE STOCK        :";
		  cin>>stock;
	  }

	  pack(*this, file);

	}

    else
	cout<<setw(40)<<"\n\n\n\t\t\tRecord Not Found ....\n";

    file.close();
    getch();
}


void Book::Delete()
{
	char key[20];
	int size=0, found=0;
	clrscr();
	cout<<"\nENTER THE RECORD KEY TO BE DELETED  :";
	cin>>key;
	found = search(key);
	if(found==1)
		cout<<"\n\n\n\t\t\tRecord Is Found ....";
	else
		cout<<"\n\n\n\t\t\tRecord Is Not Found ....";

	fstream file,file1;
	if(found==1)
	{
		file.open("list.txt",ios::app|ios::in|ios::out|ios::ate|ios::binary);
		file.seekg(0,ios::beg);
		file1.open("llist.txt",ios::out);
		file1.seekg(0,ios::beg);
		while(unpack(*this,file))
		{
		  if(strcmp(isbn,key)==0)
	      {
			cout<<"\n\n\n\n\t\tRecord Is Deleted ....\n";
	      }
	      else
	      {
			file1.seekp(size);
			pack(*this, file1);
			size=size+140;
	      }
		}
	}
	if(found==1)
	{
	  file1.close();
	  file.close();
	  unlink("list.txt");
	  rename("llist.txt","list.txt");
	}

	else
	{
		file1.close();
		file.close();
	}
	getch();
}

int Book::Binary(char *key)
{
	int mid=0,k,ptr1,low,high,i=0;
	low=0;
	high=count-1;
	char nname[20]="", recaddr[20], *endptr;
	int l=strlen(key);
	while(1)
	{   for(int j=0;j<20;j++)
		{
			nname[j]='\0';
			recaddr[j]='\0';
		}

		mid=(low+high)/2;

		if(low>high)
			return -1;

		for(i=0; knodes[mid][i]!='|'; i++)
			nname[i]=knodes[mid][i];
		i++;

		for(int n=0; knodes[mid][i]!='|'; i++)
			recaddr[n++]=knodes[mid][i];

		int num=atoi(recaddr);
		ptr1 = strnicmp(nname,key,l);

		if (ptr1 > 0)
		      high=mid-1;
		else if (ptr1 < 0)
			   low=mid+1;
		else if(ptr1==0)
			return num;

	}
}

void Book :: Indexdisplay(int size)
{
	fstream file("list.txt",ios::in);
	file.seekg(size,ios::beg);
	unpack(*this,file);
	clrscr();
	cout<<endl<<endl<<endl;
	cout<<setw(25)<<" "<<"DISPLAYING RECORD'S"<<endl<<endl<<endl<<endl;

   for(int i=0;i<80;i++)   cout<<'*';   cout<<endl<<endl<<endl;
   cout<<setw(20)<<" "<<"     ISBN NUMBER    :  "<<isbn<<endl<<endl;
   cout<<setw(20)<<" "<<"     BOOK NAME      :  "<<bname<<endl<<endl;
   cout<<setw(20)<<" "<<"     AUTHOR         :  "<<author<<endl<<endl;
   cout<<setw(20)<<" "<<"     PUBLISHER      :  "<<publr<<endl<<endl;
   cout<<setw(20)<<" "<<"     YEAR           :  "<<pyear<<endl<<endl;
   cout<<setw(20)<<" "<<"     GENRE          :  "<<genre<<endl<<endl;
   cout<<setw(20)<<" "<<"     STOCK          :  "<<stock<<endl<<endl<<endl;
   for(i=0;i<80;i++) cout<<'*';
   cout<<endl<<endl<<setw(39)<<" ";
	getch();
    file.clear();
    file.close();
}

/*Key sorting*/

void Book::KeySort()
{
	char Buffer[50],str1[30]="",str2[30]="";
	int ptr,i=0;
	fstream file("index.txt",ios::in);
	file.seekg(0,ios::beg);

	while(1)
	{
		file.getline(Buffer,40,'#');
		if(file.eof())
			break;
		for(int j=0;j<30;j++)
			knodes[i][j]=Buffer[j];

		i++;
	}

	for(int j=0;j<30;j++)
		knodes[i][j]=Buffer[j];

	file.close();

	for(i=0;i<count;i++)
	{
		for(int m=0;m<30;m++)
			str1[m]=knodes[i][m];
		j=i-1;

		a:
			for(m=0;m<30;m++)
				str2[m]=knodes[j][m];

			ptr=strnicmp(str1,str2,20);
			while(j>=0&&ptr<0)
			{
				 for(m=0;m<30;m++)
				 {
					knodes[j+1][m]=knodes[j][m];
				 }
				 j--;

				goto a;
			}

			for(m=0;m<30;m++)
			{
				knodes[j+1][m]=str1[m];
			}
	}

	knodes[i][j]=Buffer[j];
}

void  Book::Index()
{
	int size=0;
	char isbn[20]="0";
	char dummy[170]="";
	count=0;
	fstream ofile("list.txt",ios::in);
	fstream nfile("index.txt",ios::out);

	ofile.seekg(0,ios::beg);

	if(ofile.fail())
		 cout<<"File does not exist";
	else
		 while(1)
		  {
			 ofile.getline(isbn,20, '|');
			 if(ofile.fail())
				break;
			 ofile.getline(dummy, 140, '#');

			 count++;


			 if(size>0)
			 {
				nfile.seekp(size-1);
				nfile.put('#');
			 }

			 nfile.seekp(size);
			 nfile<<isbn<<"|"<<count<<"|";

			 size=size+30;
		  }
	 nfile.close();
	 ofile.close();
}


void Book::Secondsearch(char *key)
{
  char bkname[20]="", bisbn[20]="";
  int l,ptr1;
  Book bb;

  while(1)
  {
		for(int k=0;k<count;k++)
		{
			for(int s=0; s<20; s++)
			{
				bkname[s]='\0';
				bisbn[s]='\0';
			}

			for(int i=0;knodes[k][i]!='|';i++)
				bkname[i]=knodes[k][i];

			i++;

			l=strlen(key);

			for(int n=0;knodes[k][i]!='|';i++)
				bisbn[n++]=knodes[k][i];

			ptr1 = strnicmp(bkname,key,l);			//for match in first 'l' characters. i.e, even is Secondary key is longer than the key.
			//ptr1 = strcmp(bkname, key);			//for exact match of the key
			if(ptr1==0)
			{
			  bb.Index();
			  bb.KeySort();
			  int a= bb.Binary(bisbn);

				if(a==-1)
					cout<<"Record not found.......!";
				else
				{
						a=a-1;
						a=a*140;
					bb.Indexdisplay(a);
					cout<<"\n\n\nRecord found successfull ....  ";
					bb.Secondary();
					bb.SecondSort();
					//return;
				}
			}
	    }
	    break;

   }


}

void Book::SecondSort()
{
	char Buffer[60],str1[50]="",str2[50]="";
	int ptr,i=0;
	int j=0;
	fstream file("second.txt",ios::in);
	file.seekg(0,ios::beg);

	while(1)
	{
		file.getline(Buffer,60, '#');
		if(file.eof())
			break;

		strcpy(knodes[i],Buffer);
		i++;
	}

	strcpy(knodes[i],Buffer);
	file.close();

	for(i=0;i<count;i++)
	{
		j=0;
		strcpy(str1,knodes[i]);
		j=i-1;

		a:
		strcpy(str2,knodes[j]);
		ptr=strnicmp(str1,str2,50);

		while(j>=0&&ptr<0)
		{
			for(int m=0;m<50;m++)
				knodes[j+1][m]=knodes[j][m];
			j--;
			goto a;
		}

		strcpy(knodes[j+1],str1);
	}

	knodes[i][j]=Buffer[j];
}

void Book::Secondary()
{
	int size=0, length=140;
	char isbn[15]="0", bname[30]="0", dummy[140]="";
	count=0;
	fstream ofile("list.txt",ios::in);
	ofile.seekg(0,ios::beg);
	fstream nfile("Second.txt",ios::out);
	if(!ofile)
		 cout<<"File does not exist";
	else
		while(1)
		{
			ofile.getline(isbn,20, '|');
			if(ofile.eof())
				break;
			ofile.getline(bname,30, '|');
			ofile.getline(dummy, length, '#');

			count++;

			if(size>0)
			{
				nfile.seekp(size-1);
				nfile.put('#');
			}

			nfile.seekp(size);
			nfile<<bname<<"|"<<isbn<<"|";
			size=size+50;
		}
	 nfile.close();
	 ofile.close();
}

void Book::Invertprimary()
{
	int size=0,length=140;
	char isbn[20]="0";
	char dummy[140]="0";
	count=0;
	ifstream ofile("list.txt",ios::in);
	ofile.seekg(0,ios::beg);
	fstream nfile("index1.txt",ios::out);

	if(ofile.fail())
		 cout<<"File not exist";
	else
		while(1)
		{
			ofile.getline(isbn, 20, '|');
			if(ofile.eof())
				break;
			ofile.getline(dummy, length, '#');
			count++;

			if(size>0)
			{
					nfile.seekp(size-1);
					nfile.put('#');
			}
			nfile.seekp(size);
			nfile<<count<<"|"<<isbn<<"|"<<-1<<"|";
			size=size+30;
		}

	nfile.close();
	ofile.close();
}

void Book::Invertsecondary()
{
	int size=0; //length=140;
	char bisbn[20]="0", bkname[30]="", dummy[140]="";
    count=0;
    Book bk1;

	fstream ofile("list.txt",ios::in);
	ofile.seekg(0,ios::beg);
	fstream nfile("second1.txt",ios::out);

	if(ofile.fail())
		 cout<<"file not exist";
	else
		while(1)
		{
			 ofile.getline(bisbn, 20, '|');
			 if(ofile.fail())
				  break;

			 ofile.getline(bkname, 30, '|');
			 ofile.getline(dummy, 140, '#');

			 count++;

			 if(size>0)
			 {
				nfile.seekp(size-1);
				nfile.put('#');
			 }
			 nfile.seekp(size);
			 nfile<<bkname<<"|"<<count<<"|";
			 size=size+50;
		}
	 nfile.close();
	 ofile.close();
}

void Book::Invertsecondarysort()
{
	char Buffer[50],str1[50]="",str2[50]="";
	int ptr,i=0;

	fstream file("second1.txt",ios::in);
	file.seekg(0,ios::beg);

	for(int j=0;j<50;j++)
		knodes[i][j]='\0';

	while(1)
	{

		for(int j=0;j<50;j++)
			Buffer[j]='\0';

		file.getline(Buffer, 60, '#');

		if(file.eof())
			break;

		for( j=0;j<50;j++)
			knodes[i][j]=Buffer[j];
		i++;
	}

	for( j=0;j<50;j++)
		knodes[i][j]=Buffer[j];

	file.close();

	for(i=0;i<count;i++)
	{
		j=0;
		for(int m=0;m<50;m++)
			str1[m]=knodes[i][m];
		j=i-1;

		a:
			for(m=0;m<50;m++)
				str2[m]=knodes[j][m];
			ptr=strnicmp(str1,str2,30);

			while(j>=0&&ptr<0)
			{
				for(m=0;m<50;m++)
					knodes[j+1][m]=knodes[j][m];
				j--;
				goto a;
			}

			for(m=0;m<50;m++)
				knodes[j+1][m]=str1[m];
	}

	knodes[i][j]=Buffer[j];

}

void Book::CheckDup()
{
	  int found,size=0;
	  char nbname[25]="",kbname[20]="", klen[5]="", *endptr, dummy[140]="", nisbn[20]="";
	  Book bbb;
	  fstream qfile("second3.txt",ios::out);
	  qfile.seekp(0,ios::beg);
	  fstream ffile("second2.txt",ios::out);
	  ffile.seekp(0,ios::beg);
	  fstream file("second1.txt",ios::in|ios::out);
	  file.seekg(0,ios::beg);

	  found=count;
	  int i=0;

	while(i<count)
	{
		for(int m=0;m<20;m++)
			 kbname[m]='\0';

		for(int j=0;knodes[i][j]!='|';j++)
			kbname[j]=knodes[i][j];

		j++;

		for(int n=0;knodes[i][j]!='|';j++)
			klen[n++]=knodes[i][j];

		int p=strlen(kbname);
		int  ptr=strnicmp(kbname,nbname,p);

		if(ptr==0)
		{
			ffile<<klen<<"|";
			fstream nfile("list.txt",ios::in);
			nfile.seekg(0,ios::beg);

			int  num=strtol(klen,&endptr,10);

			num=num-1;
			num=num*140;

			nfile.seekg(num);

			nfile.getline(nisbn, 20, '|');
			nfile.getline(dummy, 140, '#');

			qfile<<nisbn<<"|";

			found=found+1;
			nfile.close();
		}

	    if(ptr>0)
		{
			ffile.seekp(size);
			strcpy(nbname,kbname);

			ffile<<kbname<<"|"<<klen<<"|";

			fstream nfile("list.txt",ios::in);

			nfile.seekg(0,ios::beg);
			int  num=strtol(klen,&endptr,10);
			num=num-1;
			num=num*140;
			nfile.seekg(num);

			nfile.getline(nisbn, 20, '|');
			nfile.getline(dummy, 140, '#');

			if(size>0)
			{
					qfile.seekp(size-1);
					qfile.put('#');
			}
			qfile.seekp(size);
			qfile<<kbname<<"|"<<nisbn<<"|";
			nfile.close();

			size=size+50;
		}

		i++;
	    found--;
	}
	ffile.close();
	file.close();
}



void Book::InvertSecondarySort()
{
	char Buffer[50],str1[50]="",str2[50]="";
	int ptr,i=0;
	fstream file("second3.txt",ios::in);
	file.seekg(0,ios::beg);

	while(1)
	{
		file.getline(Buffer,60, '#');
		if(file.eof())
			break;

		for(int j=0;j<50;j++)
			knodes[i][j]=Buffer[j];
		i++;
	}

	for(int j=0;j<50;j++)
		knodes[i][j]=Buffer[j];
	file.close();

	for(i=0;i<count;i++)
	{
		j=0;
		for(int m=0;m<50;m++)
			str1[m]=knodes[i][m];
		j=i-1;

		a:
		for(m=0;m<50;m++)
			str2[m]=knodes[j][m];
		ptr=strnicmp(str1,str2,10);

		while(j>=0&&ptr<0)
		{
			 for(m=0;m<50;m++)
				 knodes[j+1][m]=knodes[j][m];
			 j--;
		 goto a;
		}

		for(m=0;m<50;m++)
			knodes[j+1][m]=str1[m];
	}

	knodes[i][j]=Buffer[j];

	for(i=0;i<count;i++)
		 for(j=0;j<50;j++)
			cout<<knodes[i][j];
}


int  Book::InvertSecondSearch(char *key)
{
	clrscr();
	char str1[30]="";
	int found=0;
	char Buffer[30];
	int ptr,i=0;
	int length = 50;
	fstream file("second3.txt",ios::in);
	file.seekg(0,ios::beg);

	while(1)
	{
		file.read(Buffer,length);
		if(file.fail())
		break;
		for(int j=0;j<30;j++)
			knodes[i][j]=Buffer[j];
		i++;
	}

	for(int j=0;j<30;j++)
	knodes[i][j]=Buffer[j];

	for( i=0;i<count;i++)
	{
	 for(int j=0;knodes[i][j]!='|';j++)
		 str1[j]=knodes[i][j];
		 str1[j]='\0';
		 int l=strlen(key);
		 int ptr=strnicmp(str1,key,l);
		 if(ptr==0)
		 {
		found=1;
		break;
		 }
	 }

	if(found==1)

	{
		for(int j=0;j<30;j++)
			cout<<knodes[i][j];
	return 1;
	}
		else
			return -1;
}



//Prototypes of Graphic related functions
void drawdoublelinebox(int, int, int, int);
void drawsinglelinebox(int ,int ,int, int);
void homescreen();
void normal();
void screen1();
void screen2();


void main()
{
	int choice, ch;
	char key[15];
	Book b;
	clrscr();
	do
	{
		homescreen();

		cout<<"PLEASE ENTER YOUR CHOICE [1-3] :	";
		cin>>ch;
		switch(ch)
		{
			case 1: do
				{
				  screen1();
				  cout<<"     PLEASE ENTER YOUR CHOICE [1-6]  : ";
				  cin>>choice;
				  switch(choice)
				  {
				    case 1: b.Input();
					    break;

				    case 2: b.Modify();
					    break;

				    case 3: b.Display();
					    break;

				    case 4: b.Assign();
					    break;

				    case 5: b.Delete();
					    break;

				    case 6: clrscr();
					    break;

				    default: sound(100);delay(500);nosound();break;
				  }

				}while(choice!=6);
				break;

			case 2: do{
						screen2();
						cout<<"     PLEASE ENTER YOUR CHOICE [1-2]  : ";
						cin>>choice;

						switch(choice)
						{
							
							case 2: int a;
								clrscr();
								cd:
								b.Index();
								b.KeySort();
								gotoxy(20,25);
								drawsinglelinebox(20,15,40,15);
								gotoxy(25,20);
								cprintf("Enter the Primary key: ");
								cin>>key;
								a=b.Binary(key);
								if(a==-1)
								{
									gotoxy(25,40);
									cout<<"Record not found....!";
								}
								else
								{
									//int b=a;
									a=a-1;
									a=a*140;
									b.Indexdisplay(a);
									cout<<"\n\n\nSuccessfull search......  :";
								}
								getch();
								break;

							case 3: clrscr();
									b.Secondary();
									b.SecondSort();
									gotoxy(20,25);
									drawsinglelinebox(20,15,40,15);
									gotoxy(25,20);
									cprintf("Enter the Secondary key: ");
									gets(key);

									a=b.Binary(key);
									//cout<<a;
									if(a==-1)
									{
										gotoxy(25,40);
										cout<<"Record not found....!";
										getch();
										break;
									}

									b.Secondsearch(key);

									getch();
									break;
								
								
								case 1: b.Invertprimary();
									b.Invertsecondary();
									b.Invertsecondarysort();
									b.CheckDup();
									clrscr();
									drawsinglelinebox(20,15,40,15);
									gotoxy(25,20);
									cout<<"Enter the Secondary key: ";
									cin>>key;
									a=b.Binary(key);
									if(a==-1)
									{
										gotoxy(25,40);
										cout<<"Record not found....!";
									}
									b.InvertSecondarySort();
									int c=b.InvertSecondSearch(key);
									if(c == 1)
										goto cd;
									else
									{
										clrscr();
										gotoxy(20,25);
										cout<<"Record not found...!";
									}

									getch();
									break;

								default: clrscr();
						}
					}while(choice!=4);
					break;
			case 3:	exit(0);

			default: sound(100);delay(500);nosound();break;
		}

	}while(ch!=3);
}

/*Double line box design*/
void drawdoublelinebox(int x, int y, int len, int bdt)
{
		// (x,y) : co.ord. of 1st tip
		// len : length of box
		// bdt : breadth of box

		// four corners of the box
		gotoxy(x,y);
		cprintf("ษ");

		gotoxy(x,y+bdt);
		cprintf("ศ");

		gotoxy(x+len, y);
		cprintf("ป");

		gotoxy(x+len, y+bdt);
		cprintf("ผ");

		//horizontal lines
		for(int i=x+1; i<x+len; i++)
		{
			gotoxy(i,y);				//top line
			cprintf("อ");
			gotoxy(i, y+bdt);			//bottom line
			cprintf("อ");
		}

		//vertical lines
		for(int j=y+1; j<y+bdt; j++)
		{
			gotoxy(x,j);				//left vertical line
			cprintf("บ");
			gotoxy(x+len, j);			//right vertical line
			cprintf("บ");
		}
}

/*Single line box design*/
void drawsinglelinebox(int x,int y,int len,int bdt)
{
										// (x,y) : co.ord. of 1st tip
	gotoxy(x,y);                        // len : length of box
	cprintf("ฺ");                        // bdt : breadth of box
	gotoxy(x,y+bdt);
	cprintf("ภ");
	gotoxy(x+len,y);
	cprintf("ฟ");
	gotoxy(x+len,y+bdt);
	cprintf("ู");

	for(int i=x+1;i<x+len;i++)
	{
		gotoxy(i,y);
		cprintf("ฤ");
		gotoxy(i,y+bdt);
		cprintf("ฤ");
	}
	for(int j=y+1;j<y+bdt;j++)
	{
		gotoxy(x,j);
		cprintf("ณ");
		gotoxy(x+len,j);
		cprintf("ณ");
	}
}

void normal()  // to obtain normal background
{
	textattr(WHITE); 				// textattr sets text attributes for text-window functions
	textcolor(WHITE);				// textcolor selects a new character color in text mode
	textbackground(BLACK);			//textbackground selects a new text background color
	_setcursortype(_NORMALCURSOR); 	/* sets cursor type to normal underscore type cursor  */
}

void homescreen()
{
	//Home Screen
	int g=19,h=10;
     clrscr();					//clear screen before drawing a new box
     textbackground(BLUE);
     gotoxy(25,3);
     textcolor(YELLOW);
     cprintf("        FILE STRUCTURE        ");
     gotoxy(25,4);
     cprintf(" ออออออออออออออออออออออออออออ ");
     drawdoublelinebox(17,7,44,14);
     gotoxy(28,7);
     textbackground(RED);
	 textcolor(YELLOW);
	 cprintf("Û  M A I N    M E N U Û" );
     normal();
     textcolor(WHITE);
     gotoxy(g,h++);
     cout<<"   1 - BOOK RECORDS";
     gotoxy(g,h++);
     cout<<"   2 - INDEXING";
     gotoxy(g,h++);
     cout<<"   3 - QUIT";
     gotoxy(g,h++);
     gotoxy(g,h++);
     gotoxy(g,h++);
     normal();
}

void screen1()
{
	//screen for BOOK RECORDS
	clrscr();
	textbackground(BLACK);
	gotoxy(25,3);
	textcolor(YELLOW);
	cprintf("        BOOK RECORDS         ");
	gotoxy(25,4);
	cprintf(" ออออออออออออออออออออออออออออ ");
	int z=19,q=10;
	textcolor(YELLOW);
	drawdoublelinebox(17,7,44,14);
	gotoxy(28,7);
	textbackground(BLUE);
	textcolor(YELLOW);
	cprintf("Û  M A I N    M E N U Û" );
	normal();
	textcolor(WHITE);
	gotoxy(z, q++);
	cout<<"		1 - INSERT";
	gotoxy(z, q++);
	cout<<"		2 - UPDATE";
	gotoxy(z, q++);
	cout<<"		3 - DISPLAY ALL";
	gotoxy(z, q++);
	cout<<"		4 - ASSIGN";
	gotoxy(z, q++);
	cout<<"		5 - DELETE";
	gotoxy(z, q++);
	cout<<"		6 - QUIT";
	gotoxy(z,q++);
	gotoxy(z,q++);
	gotoxy(z,q++);
}

void screen2()
{
	int b,g=19,h=10;
    clrscr();
    textbackground(BLUE);
    gotoxy(25,3);
    textcolor(YELLOW);
    cprintf("           INDEXING           ");
    gotoxy(25,4);
    cprintf(" ออออออออออออออออออออออออออออ ");
	drawdoublelinebox(17,7,44,14);
	gotoxy(28,7);
	textbackground(RED);
	textcolor(YELLOW);
	cprintf("Û  M A I N    M E N U Û" );
	normal();
	textcolor(WHITE);
	gotoxy(g,h++);
	/*
	cout<<"1- SIMPLE INDEX";
	gotoxy(g,h++);
	cout<<"2- SECONDARY KEY";
	gotoxy(g,h++);
	*/
	cout<<"1- INVERTED LIST";
	gotoxy(g,h++);
	cout<<"2- QUIT";
	gotoxy(g,h++);
	gotoxy(g,h++);
	gotoxy(g,h++);
}
















