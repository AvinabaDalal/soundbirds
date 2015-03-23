#include "pro_include.cpp"
char main_genre[][60]={"Alternative","Blues","Classical","Electronic","Hip Hop","Inspirational","Jazz","Latin","Pop","R&B","Rock"};
class song
  {
    long int id;
     char name[30];
     char artist[30];
     int genre;
     long int stock;
     float price;
     int rating;
     int year;
    float discount;
     int sales;
    public:
    cart()
      {
	genre=0;
      }
    //float return_fprice();
    float restock(int n,int qty)
	{
	   if(n==id)
	   {
	     stock+=qty;
	     return 0.6*qty*price;
	   }
	   else
	    return 0;
	}

    void song_info(int g,float o)
      {
	   textcolor(WHITE);
	  if(g==genre)
		{
		  float x=o/100;
		  discount+=x;
		}
	cout<<"Name : ";
	puts(name);
	//cout<<endl;
	cout<<"Leading Artist : ";
	puts(artist);
	//cout<<endl;
	cout<<"Genre : "<<main_genre[genre]<<endl;
	cout<<"Rating : ";
	textcolor(LIGHTRED);
	for(int k=0;k<rating;k++)
	  cprintf("*");

	cout<<endl;
	cout<<"Year : "<<year<<endl;
	cout<<"Price : ";
	textcolor(YELLOW);
	cprintf("%f",price);
	cout<<endl;

	if(stock>0)
	  {
	    textcolor(LIGHTGREEN);
	    cprintf("IN STOCK\n\n");
	  }
	else
	 {
	   textcolor(RED);
	   cprintf("OUT OF STOCK\n\n");
	 }
	  textcolor(WHITE);
	if(discount>0.0)
	  {
	    cout<<endl<<"Discount(in %) : ";
	    textcolor(GREEN+BLINK);
	    cprintf("%f",discount*100);
	  }
	cout<<endl;
	cout<<"So you pay : ";
	textcolor(CYAN);
	cprintf("%f",return_fprice());
	 cout<<endl<<endl;
      }

    int sell(int qty)
      {
	if(stock-qty>=0)
	  {
	    stock-=qty;
	    sales++;
	    return 1;
	  }
	else
	  return 0;
      }
    int return_id()
     {
       return id;
     }
    int return_sales()
     {
       return sales;
     }
    int return_stock()
     {
       return stock;
     }
    char* return_name()
     {
       return name;
     }
    char* return_artist()
     {
       return artist;
     }
    int return_year()
     {
       return year;
     }
    int return_genre()
     {
       return (genre%11);
     }
    int return_rating()
     {
       return rating;
     }
    float return_fprice()
     {

	 return price*(1.0-(discount));
     }
    void input()
     {
       cout<<endl<<"ID : ";
       cin>>id;
       //cout<<id<<endl;
       cout<<"Name : ";
       gets(name);
       //puts(name);
       cout<<"\nArtists : ";
       gets(artist);
      // puts(artist);
       cout<<"\nGenre : ";
       cin>>genre;
       //cout<<genre<<endl;
       cout<<"Price : ";
       cin>>price;
       //cout<<price<<endl;
       cout<<"Discount : ";
       cin>>discount;
       //cout<<discount<<endl;
       cout<<"Rating : ";
       cin>>rating;
       //cout<<rating<<endl;
       cout<<"Stock : ";
       cin>>stock;
       //cout<<stock<<endl;
       cout<<"Year : ";
       cin>>year;
       //cout<<year;
       cout<<endl<<endl;
     }

  };
class bank
  {
    float cash;
    public:
    int cash_add(int amt)
      {
	float temp=amt;
	cash+=amt;
	return 1;
      }
    int cash_subtract(int amt)
      {
	if(cash-amt>=0)
	  {
	    cash-=amt;
	    return 1;
	  }
	else
	  return 0;

      }

    int show_cash()
     {
      return cash;
     }
    void input(float n)
      {
	cash=n;
      }
  };
class cart
  {
    int id;
    char name[30];
    int price;
    int qty;
    public:
    void input(int ID,char NAME[],int PRICE,int QTY)
      {
	id=ID;
	strcpy(name,NAME);
	price=PRICE;
	qty=QTY;
      }
    int return_id()
    {
      return id;
    }
    char* return_name()
      {
      return name;
      }
   float return_price()
    {
     return price;
    }
   int return_qty()
    {
     return qty;
   }
   float return_tprice()
    {
      return qty*price;
    }
  };
class notifications
  {
    int id;
    int status;
    public:
    void input(int ID,int s)
      {
	id=ID;
	status=s;
      }
    int return_id()
      {
	return id;
      }
    int return_status()
      {
	return status;
      }
  };
 void notification_gen()
  {
    ifstream f("SONG.DAT",ios::binary);
    song s;
    notifications n[50];
    int count=0;
    while(f.read((char*)&s,sizeof(s)))
      {
	 if(s.return_stock()==0)
	    {
	       n[count].input(s.return_id(),0);
	       count++;
	    }
	 if(s.return_stock()<10 && s.return_stock()!=0)
	   {
	       n[count].input(s.return_id(),1);
	       count++;

	   }
      }
    f.close();
    ofstream g("NOTIFICATION.DAT",ios::binary);
    for(int i=0;i<count;i++)
      {
	g.write((char*)&n[i],sizeof(n[i]));
      }
    g.close();

  }
