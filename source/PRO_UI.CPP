#include "pro_process.cpp"
#include "pro_data.cpp"
#include "pro_admi.cpp"
int song_page_browse(int n,song m[],int key=0);
int ui_browse(int in=0);
void ui_cart();
int song_page_browse(int n,song m[],int key)
  {
     fflush(stdin);
    fflush(stdout);


     clrscr();
     ifstream d("OFFERS.OFF");
	 char* z;
	 d>>z;
	 float o=atof(z);
	 d>>z;
	 int g=atoi(z);
	 d.close();
     m[n].song_info(g,o);
     cout<<endl<<endl<<"Press E to buy this song. \nThis will add it to cart. \nYou can manage cart from main menu."<<endl<<"Press B to go back.";
     char ch=getch();
     if(ch=='e')
       {
	 clrscr();
	 textcolor(WHITE);
	 m[n].song_info(g,o);
	 cout<<endl<<endl;
	 cout<<"Quantity you want to buy : ";
	 int q;
	 cin>>q;
	 cout<<"Confirm Purchase (Y for yes/N for no) :";
	 char t =getch();
	 if(t=='y')
	   {
	     cart c;
	     if(m[n].sell(q)!=0)
	     {
	     c.input(m[n].return_id(),m[n].return_name(),m[n].return_fprice(),q);
	     ofstream g("CART.DAT",ios::binary | ios::app);
	      g.write((char*)&c,sizeof(c));
	      g.close();
	     cout<<endl<<"Added to Cart. Press any key to continue.";
	     notification_gen();
	     getch();
	     }
	    else
	     cout<<endl<<"An error occurred in transaction. Please try again later"<<endl;
	     notification_gen();
	     getch();
	   }
	 else
	   {
	     cout<<endl<<"Purchase Cancelled. Press any key to continue.";
	     getch();
	     while(n%9!=0)
	       n--;
	      ui_browse(n);
	   }

       }
     else
       {
	   cout<<endl<<"Press any key to continue.";
	     getch();
	     while(n%9!=0)
	       n--;
	       ui_browse(n);
       }
      ifstream jl("SONG.DAT",ios::binary);
      int count=0;
      song po;
      while(jl.read((char*)&po,sizeof(po)))
	count++;
      jl.close();
      ofstream r("SONG.DAT",ios::binary);
      for(int qz=0;qz<count;qz++)
	r.write((char*)&m[qz],sizeof(m[qz]));
      r.close();
  }
void banner(int n=0)
  { fflush(stdin);
    fflush(stdout);
    if(n==0)
      {
	clrscr();
	textcolor(YELLOW);
	cprintf("  SOUNDBIRDS");
	cout<<endl<<endl;
      }
     if(n==1)
      {
	  textcolor(YELLOW);
	  cprintf("  SOUNDBIRDS");
	  cout<<endl;
	  textcolor(LIGHTGRAY);
	  cprintf("  BROWSE");
	  cout<<endl<<endl;
	  textcolor(WHITE);
      }

    if(n==4)
     {
	textcolor(YELLOW);
	cprintf("  SOUNDBIRDS");
	cout<<endl;
	textcolor(LIGHTGRAY);
	cprintf("  CART");
	cout<<endl<<endl;
     }
  }
void view_offer()
  {
    fflush(stdin);
    fflush(stdout);
    ifstream f("OFFERS.OFF",ios::binary);
    float o_d;
    int o_g;
    char *c ;
    f>>c;
    o_d=atoi(c);
    f>>c;
    o_g=atoi(c);
    //cout<<o_d;
    textcolor(GREEN+BLINK);
    cprintf("  We give you ");
    cprintf("%f",o_d);
    cprintf(" \b\b\b\b\b\b percent discount on all ");
    cprintf("%s",main_genre[o_g]);
    cprintf(" songs in this session.");
    cout<<endl<<endl;
    textcolor(WHITE);
  }
int ui_main(int status=0)
  {
    banner();
    fflush(stdin);
    fflush(stdout);
    if(status==0)
      {
	fflush(stdin);
	cout<<"  Welcome to SOUNDBIRDS, a 8-bit music store.\n  You can check and virtually buy songs from here.\n  Also enjoy the the 'real' and 'sophisticated User Interface Approach.\n  We value customers, so we give away discounts to them which can surprise them   as much as us.\n  Press B to Browse Songs."<<endl<<endl;
	view_offer();
	cout<<endl<<endl<<"  Press B to Browse Songs\n  Press C to open up Shopping Cart\n  Press E to Exit";
	char ch=getch();
	if(ch=='b')
	  ui_browse();
	if(ch=='c')
	  ui_cart();
	  if(ch=='e')
	 exit(1);
	  if(ch=='a');
	   login();

      }
    if(status==1)
      {
	fflush(stdin);
	cout<<"  SOUNDBIRD features a Shopping Cart.\n  There you can find all songs that you wished to buy.\n  You can finalize transaction there.\n  You can even remove some items from cart.\n  Press C to go there now."<<endl<<endl;
	view_offer();
	cout<<endl<<endl<<"  Press B to Browse Songs\n  Press C to open up Shopping Cart\n  Press E to Exit";
	char ch=getch();
	if(ch=='b')
	  ui_browse();
	if(ch=='c')
	  ui_cart();
	  if(ch=='e')
	 exit(1);
	  if(ch=='a');
	   login();

      }
    if(status==2)
      {
	fflush(stdin);
	cout<<"  Finished Shopping?\n  You can exit by pressing E.\n  You can even continue browsing for songs.\n  Press B to do so."<<endl<<endl;
	view_offer();
	cout<<endl<<endl<<"  Press B to Browse Songs\n  Press C to open up Shopping Cart\n  Press E to Exit";
	char ch=getch();
	if(ch=='b')
	  ui_browse();
	if(ch=='c')
	  ui_cart();
	  if(ch=='e')
	 exit(1);
	  if(ch=='a');
	   login();

      }
  }
int derive_object(istream &f,song s,song n[],int op=0)
  {
     int count=0;
     while(f.read((char*)&s,sizeof(s)))
       {
	  n[count]=s;
	  count++;
       }
     return count;
  }
int ui_browse(int in)
  {

    fflush(stdin);
    fflush(stdout);
    ifstream f("SONG.DAT",ios::binary);
    song s,n[200];
    int co=derive_object(f,s,n);
    int m=co;
    int fi;
    in=0;

    int x=0;
    while(1)
    {
    fi=in+9;
    clrscr();
    //ifstream f("SONG.DAT",ios::binary);
    //f.seekg(0L,ios::beg);
    banner(1);
    cout<<endl;
    textcolor(WHITE);
    int h;
    if(in+9>m)
      {
	h=m;
      }
    else
     h=in+9;
    if(m==0)
    cout<<"   Showing no items."<<endl<<endl;
    else
    cout<<"   Showing "<<in+1<<" to "<<h<<" of "<<m<<" results"<<endl<<endl;
    cout<<"   Sl Name                          Artist                        Price"<<endl<<endl;
    //cout<<in;
    int c=0;

    for(int i=0;i<fi && x<m;i++)
      {
	  textcolor(WHITE);
	  int l=0;
	  cout<<"   "<<i<<"  ";
	  l=strlen(n[in].return_name());
	  cout<<n[in].return_name();
	  for(int sp=0;sp<(30-l);sp++)
	    cout<<" ";
	  cout<<n[in].return_artist();
	  l=strlen(n[in].return_artist());
	  for(sp=0;sp<(30-l);sp++)
	    cout<<" ";
	  cout<<(int)n[in].return_fprice()<<endl;
	  x++;
	  in++;
	  c++;
       }
      cout<<endl<<endl<<"  Press A to go to previous page."<<endl<<"  Press D to go to next page."<<endl<<"  Press the designated serial no to know details about song."<<endl<<"  Press B to go to back.";

       //cout<<in;
	  char ch=getch();
	  if(ch=='a')
	    {
	      in=in-18;

	      if(in<0)
		in=0;
	      while(in%9!=0)
		{
		  in++;
		}
	      x=in;
	    }
	  if(ch=='d')
	    {

	      if(x>=m)
		{
		  in-=c;
		  x-=c;
		}
	      continue;
	    }
	  if(ch=='b')
	    {
	       ui_main(1);
	    }
	  if(ch=='0')
	    {
	       free(n);
	       song_page_browse(in-c+0,n);
	    }
	  if(ch=='1')
	    {
	      free(n);
	      song_page_browse(in-c+1,n);
	    }
	  if(ch=='2')
	    {
	       free(n);
	       song_page_browse(in-c+2,n);
	    }
	  if(ch=='3')
	    {
		free(n);
	       song_page_browse(in-c+3,n);
	    }
	  if(ch=='4')
	    {
	       free(n);
	       song_page_browse(in-c+4,n);
	    }
	  if(ch=='5')
	    {
	       free(n);
	       song_page_browse(in-c+5,n);
	    }
	  if(ch=='6')
	    {
	       free(n);
	       song_page_browse(in-c+6,n);
	    }
	  if(ch=='7')
	    {
	       free(n);
	       song_page_browse(in-c+7,n);
	    }
	  if(ch=='8')
	    {
	       free(n);
	       song_page_browse(in-c+8,n);
	    }
	  if(ch=='9')
	    {
	       free(n);
	       song_page_browse(in-c+9,n);
	    }
    }
  }
void ui_cart()
  {
    fflush(stdin);
    fflush(stdout);
    clrscr();
    ifstream f("CART.DAT",ios::binary);
    cart w;
    cart n[200];
    int k=0;
    int sum=0;
    while(f.read((char*)&w,sizeof(w)))
      {
	    n[k]=w;
	    k++;
	    sum+=w.return_tprice();
      }
    f.close();
    int m=k;
    int in,fi;
    in=0;

    int x=0;
    while(1)
    {
    fi=in+9;
    clrscr();
    banner(4);
    cout<<endl;
    textcolor(WHITE);
    int h;

    if(in+10>m)
      {
	h=in+m-10+1;
	if(h<0)
	  h+=9;
      }
    else
     h=in+10;
    if(m==0)
    cout<<"   Showing no items."<<endl<<endl;
    else
    cout<<"   Showing "<<in+1<<" to "<<h<<" of "<<m<<" items"<<endl<<endl;
    cout<<"   Sl  ID    Name                          Quantity        Price      T.Price"<<endl<<endl;
    int c=0;

    for(int i=0;i<fi && x<m;i++)
      {
	  textcolor(WHITE);
	  int l;
	  cout<<"   "<<i<<"  "<<n[in].return_id()<<"   ";
	  l=strlen(n[in].return_name());
	  cout<<n[in].return_name();
	  for(int sp=0;sp<(30-l);sp++)
	    cout<<" ";
	  if(n[in].return_qty()<10)
	    cout<<"0"<<n[in].return_qty();
	  else
	     cout<<n[in].return_qty();
	     if(n[in].return_price()<10)
		cout<<"              0000"<<n[in].return_price()<<"      "<<n[in].return_tprice()<<endl;
	     else if(n[in].return_price()<100)
		cout<<"              000"<<n[in].return_price()<<"      "<<n[in].return_tprice()<<endl;
	     else if(n[in].return_price()<1000)
		cout<<"              00"<<n[in].return_price()<<"      "<<n[in].return_tprice()<<endl;
	     else if(n[in].return_price()<10000)
		cout<<"              0"<<n[in].return_price()<<"      "<<n[in].return_tprice()<<endl;
	     else
		cout<<"              "<<n[in].return_price()<<"      "<<n[in].return_tprice()<<endl;
	  x++;
	  in++;
	  c++;
       }
      cout<<endl<<"  Total : "<<sum;
      cout<<endl<<endl<<"  Press A to go to previous page (if any)."<<endl<<"  Press D to go to next page (if any)."<<endl<<"  Press the designated serial no to delete the entry."<<endl<<"  Press E to buy and check out."<<endl<<"  Press B to go to back.";
       //cout<<in;
	  char ch=getch();
	  if(ch=='a')
	    {
	      in=in-18;

	      if(in<0)
		in=0;
	      while(in%9!=0)
		{
		  in++;
		}
	      x=in;
	    }
	  if(ch=='d')
	    {

	      if(x>=m)
		{
		  in-=c;
		  x-=c;
		}
	      continue;
	    }
	  if(ch=='b')
	    {
	       ui_main(2);
	    }
	  if(ch=='0')
	    {
	       free(n);
	       ofstream g("TEMP.DAT",ios::binary);
	       for(i=0;i<m;i++)
		 {
		   if(i!=in-c+0)
		    {
		     g.write((char*)&n[i],sizeof(n[i]));


		    }
		 }
		g.close();
		remove("CART.DAT");
		rename("TEMP.DAT","CART.DAT");
		ui_cart();
	    }
	  if(ch=='1')
	    {
	      free(n);
	      ofstream g("TEMP.DAT",ios::binary);
	       for(i=0;i<m;i++)
		 {
		   if(i!=in-c+1)
		    {
		     g.write((char*)&n[i],sizeof(n[i]));


		    }
		 }
		g.close();
		remove("CART.DAT");
		rename("TEMP.DAT","CART.DAT");
		ui_cart();
	    }
	  if(ch=='2')
	    {
	       free(n);
	       ofstream g("TEMP.DAT",ios::binary);
	       for(i=0;i<m;i++)
		 {
		   if(i!=in-c+2)
		    {
		     g.write((char*)&n[i],sizeof(n[i]));


		    }
		 }
		g.close();
		remove("CART.DAT");
		rename("TEMP.DAT","CART.DAT");
		ui_cart();
	    }
	  if(ch=='3')
	    {
		free(n);
		ofstream g("TEMP.DAT",ios::binary);
	       for(i=0;i<m;i++)
		 {
		   if(i!=in-c+3)
		    {
		     g.write((char*)&n[i],sizeof(n[i]));


		    }
		 }
		g.close();
		remove("CART.DAT");
		rename("TEMP.DAT","CART.DAT");
		ui_cart();
	    }
	  if(ch=='4')
	    {
	       free(n);
	       ofstream g("TEMP.DAT",ios::binary);
	       for(i=0;i<m;i++)
		 {
		   if(i!=in-c+4)
		    {
		     g.write((char*)&n[i],sizeof(n[i]));


		    }
		 }
		g.close();
		remove("CART.DAT");
		rename("TEMP.DAT","CART.DAT");
		ui_cart();
	    }
	  if(ch=='5')
	    {
	       free(n);
	       ofstream g("TEMP.DAT",ios::binary);
	       for(i=0;i<m;i++)
		 {
		   if(i!=in-c+5)
		    {
		     g.write((char*)&n[i],sizeof(n[i]));


		    }
		 }
		g.close();
		remove("CART.DAT");
		rename("TEMP.DAT","CART.DAT");
		ui_cart();
	    }
	  if(ch=='6')
	    {
	       free(n);
	       ofstream g("TEMP.DAT",ios::binary);
	       for(i=0;i<m;i++)
		 {
		   if(i!=in-c+6)
		    {
		     g.write((char*)&n[i],sizeof(n[i]));


		    }
		 }
		g.close();
		remove("CART.DAT");
		rename("TEMP.DAT","CART.DAT");
		ui_cart();
	    }
	  if(ch=='7')
	    {
	       free(n);
	       ofstream g("TEMP.DAT",ios::binary);
	       for(i=0;i<m;i++)
		 {
		   if(i!=in-c+7)
		    {
		     g.write((char*)&n[i],sizeof(n[i]));


		    }
		 }
		g.close();
		remove("CART.DAT");
		rename("TEMP.DAT","CART.DAT");
		ui_cart();
	    }
	  if(ch=='8')
	    {
	       free(n);
	       ofstream g("TEMP.DAT",ios::binary);
	       for(i=0;i<m;i++)
		 {
		   if(i!=in-c+8)
		    {
		     g.write((char*)&n[i],sizeof(n[i]));


		    }
		 }
		g.close();
		remove("CART.DAT");
		rename("TEMP.DAT","CART.DAT");
		ui_cart();
	    }
	  if(ch=='9')
	    {
	       free(n);
	       ofstream g("TEMP.DAT",ios::binary);
	       for(i=0;i<m;i++)
		 {
		   if(i!=in-c+9)
		    {
		     g.write((char*)&n[i],sizeof(n[i]));


		    }
		 }
		g.close();
		remove("CART.DAT");
		rename("TEMP.DAT","CART.DAT");
		ui_cart();
	    }
	 if(ch=='e')
	   {
	     cout<<endl<<"  For security reasons, we request you to enter captcha to complete transaction."<<endl;
	     while(1)
	       {

		 int captcha=captcha_gen();
		 cout<<"  "<<captcha<<" : ";
		 int entry;
		 cin>>entry;
		 if(entry==captcha)
		   break;
		 else
		  {
		    cout<<"  Captcha verification failed. You need to try again."<<endl;
		  }
	       }
	     ifstream f("BANK.DAT",ios::binary);
	     bank b;
	     f.read((char*)&b,sizeof(b));
	     f.close();
	     b.cash_add(sum);
	     ofstream g("TEMP1.DAT",ios::binary);
	     g.write((char*)&b,sizeof(b));
	     g.close();
	     remove("BANK.DAT");
	     rename("TEMP1.DAT","BANK.DAT");
	     remove("CART.DAT");
	     fstream f1("BANK.DAT",ios::in | ios::out);
	     f1.read((char*)&b,sizeof(b));
	     b.cash_add(sum);
	     f1.write((char*)&b,sizeof(b));
	     f1.close();
	     cout<<endl<<"  Transaction Successfull. Press any key to continue";
	     getch();
	     notification_gen();
	     ui_main(2);
	   }
  }
}
