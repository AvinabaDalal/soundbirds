#include "pro_include.cpp"
int captcha_gen()
  {
    int c;
    srand(time(NULL));
    c=rand()%8000+2000;
    return c;
  }
void offer_gen()
  {
    int r ;
    srand(time(NULL));
    r=rand() %24+1;

    int c;
    srand(time(NULL));
    c=rand()%11+0;
    ofstream f_offer("offers.off");
    //f_offer.write((char*)&r,sizeof(r));
    //f_offer.write((char*)&c,sizeof(c));
    f_offer<<r<<"\n"<<c;
    f_offer.close();
  }
