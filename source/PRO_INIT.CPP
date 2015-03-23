#include "pro_data.cpp"
void write_song()
  {
    song s;
    ofstream f("SONG.DAT",ios::app | ios::binary);
    s.input();
    f.write((char*)&s,sizeof(s));
    f.close();
   }
void show_song(int g,float o)
   {
    song s;
    ifstream f1("SONG.DAT");
    while(f1.read((char*)&s,sizeof(s)))
    {


	s.song_info(g,o);
	getch();
    }
    f1.close();
    getch();
  }
void write_bank(float n)
  {
    ofstream f("BANK.DAT",ios::binary);
    bank b;
    b.input(n);
    f.write((char*)&b,sizeof(b));
    f.close();
  }
void main()
  {
     for(int i=0;i<20;i++)
	write_song();
  }