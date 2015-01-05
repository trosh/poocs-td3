#include <Tableau.hh>
#include <iostream>
#include <iomanip>
#include <cstdlib>

// Prototypes et macro pour activation conditionnelle suivant la directive DO_SAVE

#ifndef DO_SAVE
const int all_check_data[][320] = {
#include <stress_data.hh>
{} };
template<typename T> void test(const Tableau<T> & t, const char * msg, const int line);
#define TEST0(t,tabname) test(t,tabname,__LINE__)
#else /* DO_SAVE */
template<typename T> void print(const Tableau<T> & t);
#define TEST0(t,tabname) print(t);
#endif /* DO_SAVE */


// La fonction qui 'torture' le tableau en argument
template<typename T>
void stress(Tableau<T> & t, const char * tabname) {
  for(int i=0;i<20;++i) {
    t.ajoute(i);                      TEST0(t,tabname);
  }
  // reserve ne doit pas changer la taille si trop petite. N'influence que la capacité si trop petite.
  t.reserve(40);                      TEST0(t,tabname);
  for(int i=t.taille()-1;i>0;i-=3) {
    t.supprime(i);                    TEST0(t,tabname); 
  }
  for(int i=0;i<20;++i) { 
   t.ajoute(i);                       TEST0(t,tabname); 
  }
  t.reserve(20);                      TEST0(t,tabname);
  t.retaille(t.taille()/2);           TEST0(t,tabname);
  for(int i=t.taille()-1;i>0;i-=2) { 
    t.supprime(i);                    TEST0(t,tabname); 
  }
  t[3] = t[2]+5;
  t[5] = -1;                          TEST0(t,tabname);
  t.retaille(5);                      TEST0(t,tabname);
  t.retaille(6);                      TEST0(t,tabname);
  t[5] = -2;                          TEST0(t,tabname);
  for(int i=1;i<10;++i) {
    t.ajoute(t.taille());             TEST0(t,tabname);
  }
}

// Macro pour récupérer le nom du tableau passé en argument
#define TEST(t) TEST0(t,#t)
#define STRESS(t) stress(t,#t)

int main() 
{ 
  typedef int T;
  Tableau<T> * t1 = new Tableau<T>(); TEST(*t1);
  STRESS(*t1);                        TEST(*t1);
  Tableau<T> t2 = *t1;                TEST(t2); TEST(*t1);
  {
    Tableau<T> t3;                    TEST(t3);
    STRESS(t3);                       TEST(t3);
    t3 = *t1;                         TEST(t3); TEST(*t1);
    delete t1, t1 = NULL; // t2 and t3 are independant copies of t1;
    STRESS(t3);
  }
  STRESS(t2);
  
  {
    Tableau<T> t4;                      TEST(t4);
    t4.reserve(10);                     TEST(t4);
    t4.retaille(4);
    for(int i=0;i<4;++i) t4[i] = i;     TEST(t4);
  }
  {
    Tableau<T> t5;                      TEST(t5);
    t5.retaille(6);
    for(int i=0;i<6;++i) t5[i] = i;     TEST(t5);
    t5.reserve(10);                     TEST(t5);
  }
  {
    // Construction d'un tableau à partir d'une capacitée donnée (non précisé dans le sujet mais utile pour certains bouts de code fournis)
    Tableau<T> t6(40);                  TEST(t6);
    t6.retaille(20);
    for(int i=0;i<20;++i) t6[i] = i;    TEST(t6);
    t6.reserve(60);                     TEST(t6);
    t6.reserve(10);                     TEST(t6);
    t6.retaille(4);                     TEST(t6);
    for(int i=0;i<4;++i) t6[i] = -i;    TEST(t6);
  }
   t2.retaille(0);                      TEST(t2);
}

#ifdef DO_SAVE
template<typename T>
void print(const Tableau<T> & t) {
  // Ecrit au format C, la taille et le contenu du tableau en argument (à mettre dans data.hpp pour le mode test)
  std::cout << "{ " << t.taille();
  for(int i=0;i<t.taille();++i) { 
    std::cout << ", " << t[i];
  } 
  std::cout << " }, " << std::endl;
}
#else /* DO_SAVE */
template<typename T>
void test(const Tableau<T> & t, const char * msg, const int line) {
  static int idata = 0;
  std::cout << "Check " << std::setw(3) << msg << " #" << std::setw(3) << idata << " at line " << std::setw(3) << line <<  " : ";
  const int * data = all_check_data[idata];
  const int taille = data[0];
  ++data;
  if (t.taille() != taille) {
    std::cout << " FAILED : bad 'taille' " << t.taille() << " vs reference " << taille << std::endl;
    std::abort();
  }
  if (t.capacite() < t.taille()) {
    std::cout << " FAILED : bad 'capacite' " << t.capacite() << " lower than 'taille' " << t.taille() << std::endl;
    std::abort();
  }
  for(int i=0;i<t.taille();++i) { 
    if (t[i] != data[i]) {
      std::cout << " FAILED : bad value at position " << i << "; " << t[i] << " vs reference " << data[i] << std::endl;
      std::abort();
    }
  }
  std::cout << " OK" << std::endl;
  ++idata;
}
#endif /* DO_SAVE */
